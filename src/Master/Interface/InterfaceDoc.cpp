// InterfaceDoc.cpp
//

#include "stdafx.h"
#include "Interface.h"

#include "InterfaceDoc.h"
#include "MainFrm.h"
#include "AdditionalResource.h"
#include "BusyView.h"
#include "CashView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CInterfaceDoc

IMPLEMENT_DYNCREATE(CInterfaceDoc, CDocument)

BEGIN_MESSAGE_MAP(CInterfaceDoc, CDocument)
	//{{AFX_MSG_MAP(CInterfaceDoc)
	ON_COMMAND(ID_INTERVALS_NEW, OnNewInterval)
	ON_COMMAND(ID_MENU_TAKEOFF, OnTakeOff)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_VIEW_SHOW_BUSY_VIEW, OnShowBusyView)
	ON_COMMAND(ID_VIEW_SHOW_CASH_VIEW, OnShowCashView)
	ON_COMMAND(ID_LOGGED_OFF, OnLogOffClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Свободные функции

// Проверяет. является ли pView CBusyView
static BOOL TestBusyView(const CView* pView)
{
	return pView->IsKindOf(RUNTIME_CLASS(CBusyView));
}
// End of TestBusyView


// Проверяет. является ли pView CCashView
static BOOL TestCashView(const CView* pView)
{
	return pView->IsKindOf(RUNTIME_CLASS(CCashView));
}
// End of TestCashView


// CInterfaceDoc construction/destruction
CInterfaceDoc::CInterfaceDoc()
{
	m_pMasterManager = 0;
	m_pNewIntervalDialog = 0;
	m_pTakeOfDialog = 0;

	try{
		try{
			m_pMasterManager = new CMasterManager(((CInterfaceApp*)AfxGetApp())->GetStorer());
		}catch(...){
			MessageBox(0, "Ошибка при создании документа. См. логфайл, если он есть :-)", "Фатальная ошибка", MB_ICONERROR);
			DoDeleteEverything();
			throw;
		}

	}catch(CAnyLogableException &e){
		throw CAnyLogableException(((CString)"Can't create document: "+(CString)e.what()).operator LPCSTR(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("Can't create document: unknown exception", bDoNotWriteDuplicates);;
	}
}

CInterfaceDoc::~CInterfaceDoc()
{
#ifdef LOG_LOADINGANDTERMINATINGOFPROGRAM
	if (GetErrorsLogger())
		GetErrorsLogger()->AddLogEntry("Document destroing", bWriteDuplicates);
#endif

	DoDeleteEverything();
}

void CInterfaceDoc::DoDeleteEverything()
{
	if (m_pMasterManager)
	{
		delete m_pMasterManager;
		m_pMasterManager = 0;
	}
}
// End of DoDeleteEverything()

BOOL CInterfaceDoc::OnNewDocument()
{
#ifdef LOG_LOADINGANDTERMINATINGOFPROGRAM
	GetErrorsLogger()->AddLogEntry("New document created", bWriteDuplicates);
#endif

	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

// CInterfaceDoc serialization
void CInterfaceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}


// CInterfaceDoc diagnostics
#ifdef _DEBUG
void CInterfaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInterfaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CInterfaceDoc commands

CMasterManager* CInterfaceDoc::GetMasterManager()
{
	return m_pMasterManager;
}

CErrorsLogger* CInterfaceDoc::GetErrorsLogger()
{
	return ((CInterfaceApp*)AfxGetApp())->GetErrorsLogger();
}

// Чтобы переопределить поведение при сохранении
BOOL CInterfaceDoc::DoFileSave()
{
	BOOL whattoreturn;
	if (m_pMasterManager)
	{
		try{

			((CInterfaceApp*)AfxGetApp())->GetStorer()->
					SaveCash(GetMasterManager()->GetCash());

			whattoreturn = ((CInterfaceApp*)AfxGetApp())->GetStorer()->
					SaveClubStateToHistory(GetMasterManager()->GetClubState(),
					CurrentTime() - GetMasterManager()->GetTimeSplitHist() );

			((CInterfaceApp*)AfxGetApp())->GetStorer()->
					SaveMashinesCollection(GetMasterManager()->
						GetClubState()->GetMashinesCollection());

			((CInterfaceApp*)AfxGetApp())->GetStorer()->FlushCurrToFile();
		}catch(CAnyLogableException &e){
			GetErrorsLogger()->AddLogEntry(((CString)"OnSaveDocument failed: "+(CString)e.what()), e.GetWriteDuplicatesToLog());
			whattoreturn = FALSE;
		}catch(...){
			GetErrorsLogger()->AddLogEntry("OnSaveDocument failed", bDoNotWriteDuplicates);
			whattoreturn = FALSE;
		}
	}

	return whattoreturn;
}
// End of DoFileSave()


void CInterfaceDoc::SetStatusBarText(CString Text)
{
	// Главный фрейм всего приложения
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->GetMainWnd());

	// Запихиваю строку в первую часть Status Bar
	pMainFrame->GetStatusBar()->SetWindowText(Text);
}
// End of SetStatusBarText


void CInterfaceDoc::OnNewInterval()
{
	try
	{
		if ( !DoOperatorAuthentication(0) )
			return;

		m_DialogState.SetOperatorIndex(m_PasswordDialogState.GetOperatorNumber());

		m_pNewIntervalDialog = new CNewIntervalDialog(&m_DialogState, ((CInterfaceApp*)AfxGetApp())->GetStorer(),
					m_pMasterManager->GetClubState());
		try
		{
			if (!m_pNewIntervalDialog)
				return;

			int iReturn = m_pNewIntervalDialog->DoModal();

			GetBusyView()->Refresh();

			switch(iReturn)
			{
				case -1:
					throw CAnyLogableException("Can't create dialog!: returned -1", bDoNotWriteDuplicates);

				case IDABORT:
					throw CAnyLogableException("Can't create dialog!: returned IDABORT", bDoNotWriteDuplicates);


				case IDOK:

				break;

				case IDCANCEL:

				break;
			}

		}catch(...){
			m_pNewIntervalDialog->DoCancel();
			MessageBox(NULL, "Произошла ошибка при работе диалога \nредактирования интервалов. \nПодробности см. в файле отчета об ошибках.", "Ошибка", MB_OK);
			throw;
		}
	}
	catch(CAnyLogableException &e)
	{
		GetErrorsLogger()->AddLogEntry(std::string(
			(std::string)"OnNewInterval failed: "
			+ (std::string)e.what()).c_str(), e.GetWriteDuplicatesToLog());
	}
	catch(...)
	{
		GetErrorsLogger()->AddLogEntry(
			"CInterfaceDoc::OnNewInterval failed", bDoNotWriteDuplicates);
	}

	if (m_pNewIntervalDialog)
	{
		delete m_pNewIntervalDialog;
		m_pNewIntervalDialog = 0;
	}
}
// End of OnNewInterval()


CView* CInterfaceDoc::GetViewOfType(TestTheView* TestFunction)
{
	POSITION Pos = GetFirstViewPosition();
	CView* pTempView;

		while ( (Pos) )
		{
			pTempView = GetNextView(Pos);
				if ( TestFunction(pTempView) )
				{
					return pTempView;
				}
		}

	return NULL;
}
// End of GetViewOfType


CBusyView* CInterfaceDoc::GetBusyView()
{
	return (CBusyView*)GetViewOfType(TestBusyView);
}
// End of GetBusyView()


bool CInterfaceDoc::OnTimer()
{
	BOOL whattoreturn = TRUE;

	if (m_pMasterManager)
	{
		try{
			((CInterfaceApp*)AfxGetApp())->GetStorer()->
				SaveCash(GetMasterManager()->GetCash());

			if (
			whattoreturn = ((CInterfaceApp*)AfxGetApp())->GetStorer()->
					SaveClubStateToHistory(GetMasterManager()->GetClubState(),
					CurrentTime() - GetMasterManager()->GetTimeSplitHist() )
			)
			{

				((CInterfaceApp*)AfxGetApp())->GetStorer()->
					SaveMashinesCollection(GetMasterManager()->
						GetClubState()->GetMashinesCollection());

				((CInterfaceApp*)AfxGetApp())->GetStorer()->FlushCurrToFile();
			}

		}catch(CAnyLogableException &e){
			GetErrorsLogger()->AddLogEntry(((CString)"OnSaveDocument failed: "+(CString)e.what()), e.GetWriteDuplicatesToLog());
			whattoreturn = FALSE;
		}catch(...){
			GetErrorsLogger()->AddLogEntry("OnSaveDocument failed", bDoNotWriteDuplicates);
			whattoreturn = FALSE;
		}

		try
		{
				if (m_pNewIntervalDialog)
				{
					m_pNewIntervalDialog->OnTimer();
				}
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CInterfaceDoc::OnTimer(): ";
			ErrorString += Error.what();
			GetErrorsLogger()->AddLogEntry(ErrorString.c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			GetErrorsLogger()->AddLogEntry("An unknown error occured in CInterfaceDoc::OnTimer()", bDoNotWriteDuplicates);
		}
	}

	return whattoreturn;
}
//end of bool CInterfaceDoc::OnTimer()


bool CInterfaceDoc::DoOperatorAuthentication(CPermission a_Permission)
{
	CPswrdDialog PasswordDialog(NULL, m_pMasterManager->GetClubState(), &m_PasswordDialogState, a_Permission);
		if (PasswordDialog.DoModal() != IDOK)
			return false;

	return true;
}
// End of DoOperatorAuthentication()

void CInterfaceDoc::OnTakeOff()
{
	m_pTakeOfDialog = 0;

	try
	{
		if ( !DoOperatorAuthentication(0/*m_pMasterManager->GetCash()->GetPermission()*/) )
			return;

		COperator* pOperator = &(GetMasterManager()->GetClubState()->GetOperatorsCollection()->operator [](m_PasswordDialogState.GetOperatorNumber()));
		std::string sOperName = pOperator->GetName();

		m_pTakeOfDialog = new CTakeOfDlg(m_pMasterManager->GetCash(), sOperName, pOperator->GetPermission());
		
		try{
			if (!m_pTakeOfDialog)
				return;

			int iReturn = m_pTakeOfDialog->DoModal();

			switch(iReturn)
			{
				case -1:
					throw CAnyLogableException("Can't create dialog!: returned -1", bDoNotWriteDuplicates);

				case IDABORT:
					throw CAnyLogableException("Can't create dialog!: returned IDABORT", bDoNotWriteDuplicates);

				case IDOK:
				break;

				case IDCANCEL:
				break;
			}

		}catch(...){
			MessageBox(NULL, "Произошла ошибка при работе диалога \nснятия кассы. \nПодробности см. в файле отчета об ошибках.", "Ошибка", MB_OK);
			throw;
		}

		if (m_pTakeOfDialog)
		{
			delete m_pTakeOfDialog;
			m_pTakeOfDialog = 0;
		}

	}
	catch(CAnyLogableException &e)
	{
		GetErrorsLogger()->AddLogEntry(std::string(
			(std::string)"OnTakeOff failed: "
			+ (std::string)e.what()).c_str(), e.GetWriteDuplicatesToLog());
	}
	catch(...)
	{
		GetErrorsLogger()->AddLogEntry(
			"OnTakeOff failed", bDoNotWriteDuplicates);
	}

	if (m_pTakeOfDialog)
	{
		delete m_pTakeOfDialog;
		m_pTakeOfDialog = 0;
	}
}
// End of OnTakeOff()


void CInterfaceDoc::OnShutdownHosts()
{
	m_pShutdownDialog = 0;

	try
	{
		if ( !DoOperatorAuthentication(0/*установить ещё один GetPermission()*/) )
			return;

		CMashinesCollection SelectedMashines(false);
		GetBusyView()->GetSelectedMashines(&SelectedMashines);

		m_pShutdownDialog = new CShutdownDialog(
			GetMasterManager()->GetClubState()->GetMashinesCollection(),
			&SelectedMashines);
		
		try{
			if (!m_pShutdownDialog)
				return;

			int iReturn = m_pShutdownDialog->DoModal();

			switch(iReturn)
			{
				case -1:
					throw CAnyLogableException("Can't create dialog!: returned -1", bDoNotWriteDuplicates);

				case IDABORT:
					throw CAnyLogableException("Can't create dialog!: returned IDABORT", bDoNotWriteDuplicates);

				case IDOK:
				break;

				case IDCANCEL:
				break;
			}

		}catch(...){
			MessageBox(NULL, "Произошла ошибка при работе диалога \nснятия кассы. \nПодробности см. в файле отчета об ошибках.", "Ошибка", MB_OK);
			throw;
		}
	}
	catch(CAnyLogableException &e)
	{
		GetErrorsLogger()->AddLogEntry(std::string(
			(std::string)"OnTakeOff failed: "
			+ (std::string)e.what()).c_str(), e.GetWriteDuplicatesToLog());
	}
	catch(...)
	{
		GetErrorsLogger()->AddLogEntry(
			"OnTakeOff failed", bDoNotWriteDuplicates);
	}

	if (m_pShutdownDialog)
	{
		delete m_pShutdownDialog;
		m_pShutdownDialog = 0;
	}
}
// end of OnShutdownHosts()


void CInterfaceDoc::OnShowBusyView()
{
	// Взял BusyView, если такой имеется
	CBusyView* pView = (CBusyView*)GetViewOfType(TestBusyView);

	// Шаблон документа. Нужен, чтобы ассоциировать класс документа
	// CInterfaceDoc с классом CBusyView.
	CInterfaceApp* pApp = (CInterfaceApp*)AfxGetApp();
	CDocTemplate* pTemplate = pApp->GetBusyViewDocTemplate();

	OnShowAnyView(pView, pTemplate);
}
// End of OnShowBusyView()


void CInterfaceDoc::OnShowCashView()
{
	// Взял CashView, если такой имеется
	CCashView* pView = (CCashView*)GetViewOfType(TestCashView);

	// Шаблон документа. Нужен, чтобы ассоциировать класс документа
	// CInterfaceDoc с классом CCashView.
	CInterfaceApp* pApp = (CInterfaceApp*)AfxGetApp();
	CDocTemplate* pTemplate = pApp->GetCashViewDocTemplate();

	OnShowAnyView(pView, pTemplate);
}
// End of OnShowCashView()


void CInterfaceDoc::OnShowAnyView(CView* pView, CDocTemplate* pTemplate)
{
		// Если нет ни одного View - создаю его
		if (!pView)
		{
			CInterfaceDoc* pDoc = this;

			POSITION Pos = GetFirstViewPosition();
			/* Это только чтобы выколупать класс фрейма, чтобы у всех
			Views были одинаковые классы фрейма. Хотя можно просто
			поставить NULL в CreateNewFrame. */
			CView* pTempView = GetNextView(Pos);

			CFrameWnd* pTempFrame;
			pTempFrame = pTemplate->CreateNewFrame(pDoc, pTempView->GetParentFrame());

			// Это чтобы были Untitled views
			//pTempFrame->ModifyStyle(FWS_ADDTOTITLE, 0);

			pTemplate->InitialUpdateFrame(pTempFrame, pDoc, true);
		}
		else
		{
			// Если есть хотя бы 1 View - показываю его
			pView->GetParentFrame()->BringWindowToTop();
		}
}
// End of OnShowAnyView

void CInterfaceDoc::OnLogOffClick() 
{
	if (DoOperatorAuthentication(0))
		m_PasswordDialogState.SetLogged(
			!m_PasswordDialogState.IsLogged());
}

void CInterfaceDoc::OnIdle()
{
	bool bIsLogged = m_PasswordDialogState.IsLogged();
	char NewText[226];
	std::string sMenuItemText;

	CMainFrame* MainFrm = ((CMainFrame*)(AfxGetApp()->GetMainWnd()));
	{//Menu
	HWND hMainWnd = MainFrm->GetSafeHwnd();
	HMENU hMenu = 0;
	hMenu = GetMenu( hMainWnd );
	MENUITEMINFO MenuItemInfo;
	MenuItemInfo.fMask = MIIM_STRING;
	MenuItemInfo.cbSize = sizeof(MenuItemInfo);
	MenuItemInfo.dwTypeData = 0;
	GetMenuItemInfo(hMenu, ID_LOGGED_OFF, FALSE, &MenuItemInfo);
	sMenuItemText.resize(++MenuItemInfo.cch);
	MenuItemInfo.dwTypeData = sMenuItemText.begin();
	GetMenuItemInfo(hMenu, ID_LOGGED_OFF, FALSE, &MenuItemInfo);
	LoadString(AfxGetInstanceHandle(),bIsLogged?
		IDS_LOGOFF_MENUITEMSTR:IDS_LOGON_MENUITEMSTR, NewText, 225);
	MenuItemInfo.dwTypeData = NewText;
	SetMenuItemInfo(hMenu, ID_LOGGED_OFF, FALSE, &MenuItemInfo);
	}
	{//Button
		int iState = MainFrm->GetToolBar()->GetToolBarCtrl().
					GetState(ID_LOGGED_OFF) | TBSTATE_CHECKED;
		if (!bIsLogged) iState ^= TBSTATE_CHECKED;
		MainFrm->GetToolBar()->GetToolBarCtrl().
			SetState(ID_LOGGED_OFF, iState);
	}
}
