// Interface.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Interface.h"

#include "MainFrm.h"
#include "CashChildFrame.h"
#include "BusyChildFrame.h"
#include "InterfaceDoc.h"
#include "CashView.h"
#include "BusyView.h"
#include "..\DataStructures\Constants.h"

#include "..\..\Slave\Slave\MasterMessages.h"
#include "..\..\Slave\Slave\NetworkConstants.h"

#include "..\Logon\SSPLogon.h"
#include "..\DataStructures\Cryptography\Cryptor.h"
#include "..\Logon\DomainNameDefiner.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CInterfaceApp

BEGIN_MESSAGE_MAP(CInterfaceApp, CWinApp)
	//{{AFX_MSG_MAP(CInterfaceApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_MESSAGE(WM_CONNECTIONACCEPTED, OnConnectionAccepted)
	ON_MESSAGE(WM_WRITE_DEBUG_MESSAGE, OnWriteDebugMessage)
	ON_MESSAGE(WM_CONNECTED, OnConnected)
	ON_MESSAGE(WM_DATARECEIVED, OnDataReceived)
	ON_MESSAGE(WM_RE_CHECK_STATE_REQUEST, OnReCheckStateRequest)
	ON_MESSAGE(WM_LOCK_FAIL_ACKNOWLEDGE, OnLockFail)
	ON_MESSAGE(WM_LOCK_SUCCESS_ACKNOWLEDGE, OnLockSuccess)
	ON_MESSAGE(WM_UNLOCK_FAIL_ACKNOWLEDGE, OnUnLockFail)
	ON_MESSAGE(WM_UNLOCK_SUCCESS_ACKNOWLEDGE, OnUnLockSuccess)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CInterfaceApp construction

CInterfaceApp::CInterfaceApp()
{
	m_pLogger = 0;
	m_hMutex = 0;
	m_pStorer = 0;
}

CInterfaceApp::~CInterfaceApp()
{
	DoDeleteEverything();
	Sleep(2000);
}


CInterfaceApp theApp;


BOOL CInterfaceApp::InitInstance()
{
	if (m_hMutex) return FALSE; // It seems to me, that is impossible

	try{
		if ( m_Definer.GetVersion() != WinNT )
		{
			MessageBox(0, "Данная программа не реализует некоторые важные функции под Windows9x.\nНастоятельно рекомендуется использовать Windows NT/2000.", "Tarificator", MB_ICONERROR);
		}
		else
		{
			TCHAR User[dwUNLength + 1];
			TCHAR Domain[dwDNLength + 1];
			DWORD cchUser = dwDNLength;
			DWORD cchDomain = dwDNLength;

			if(!GetUserAndDomainName(User, &cchUser, Domain, &cchDomain))
			{
				throw CAnyLogableException("Can't define user and domain name!", bDoNotWriteDuplicates);
			};

			CCryptor _Cryptor;
			// логинимся в домен Domain																																																				логин "Tarificator", пароль "0xBE9807490B"
			if( !SSP::SSPLogonUser(Domain,
					(char*)_Cryptor.EncryptString((std::string)
					"\x67\xa0\xd8\xc0\x4d\x7a\x21\x11\x17\x67\xa2").c_str(),
					(char*)_Cryptor.EncryptString((std::string)
					"\x03\xB9\xE8\xEC\x12\x2B\x72\x47\x57\x31\xE0\x80").c_str()) )
			{
				DWORD dwLastError = GetLastError();
				char cBuff[10];
				std::string sError = 
						(std::string)"Last error is "+
						(std::string)_itoa(dwLastError, cBuff, 10);
				switch (dwLastError)
				{
				case ERROR_LOGON_TYPE_NOT_GRANTED:
					sError += "\nLogon failure: the user has not been granted the requested logon type at this computer.";
					break;
				case ERROR_TRUST_FAILURE:
					sError += "\nThe network logon failed. Trust falture.";
					break;
				case ERROR_ACCOUNT_EXPIRED:
					sError += "\nThe user's account has expired.";
					break;
				case ERROR_LOGON_FAILURE:
					sError += "\nLogon failure: unknown user name or bad password.";
					break;
				default:;
				}
				throw CAnyLogableException(
					std::string((std::string)"SSP LOGON FAILED! "+
					sError).c_str(),
						bDoNotWriteDuplicates);
			}
		};

		m_pStorer = new CMasterRegistryStorer;
		if (!m_pStorer)
			throw CAnyLogableException("Can not create MasterRegistryStorer", bDoNotWriteDuplicates);

		m_pLogger = new CErrorsLogger(GetStorer());

		m_hMutex = CreateMutex(NULL, true, sMainMutexName.c_str());
		if ( (GetLastError() == ERROR_ALREADY_EXISTS) || (m_hMutex == 0))
		{
			m_hMutex = 0;
			throw CAnyLogableException("One program copy is already running", bWriteDuplicates);
		}

	#ifdef _AFXDLL
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif


		SetRegistryKey(_T("_LX"));

		LoadStdProfileSettings();  // Load standard INI file options (including MRU)

		// Register document templates

		/* Темплейт для ассоциирования CInterfaceDoc и CBusyView, т.е. 
		BusyViewDocTemplate */
		CMultiDocTemplate* pDocTemplate;
		pDocTemplate = new CMultiDocTemplate(
			IDR_INTERFTYPE,
			RUNTIME_CLASS(CInterfaceDoc),
			RUNTIME_CLASS(CBusyChildFrame), // custom MDI child frame
			RUNTIME_CLASS(CBusyView));
		AddDocTemplate(pDocTemplate);

		/* Темплейт для ассоциирования CCashView и CInterfaceDoc, т.е.
		CashViewDocTemplate */
		pDocTemplate = new CMultiDocTemplate(
			IDR_INTERFTYPE,										// Меню
			RUNTIME_CLASS(CInterfaceDoc),				// Класс документа
			RUNTIME_CLASS(CCashChildFrame),			// Класс фрейма
			RUNTIME_CLASS(CCashView));	// Класс View
		AddDocTemplate(pDocTemplate);


		{// Чтобы проинить конролы для работы со временем и датой
		INITCOMMONCONTROLSEX icc;
	    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icc.dwICC = ICC_DATE_CLASSES;
		InitCommonControlsEx(&icc);
		}

		// create main MDI Frame window
		CMainFrame* pMainFrame = new CMainFrame;
		if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
			throw CAnyLogableException("Error while pMainFrame->LoadFrame(IDR_MAINFRAME)", bWriteDuplicates);
		m_pMainWnd = pMainFrame;

		// Parse command line for standard shell commands, DDE, file open
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		// Это чтобы при запуске приложения не создавался пустой файл
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			throw CAnyLogableException("Error while ProcessShellCommand(cmdInfo)", bWriteDuplicates);
		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();

		OnFileNew();

		return TRUE;

	}catch(CAnyLogableException &e){
		if (m_pLogger) 
			m_pLogger->AddLogEntry(e.what(), bDoNotWriteDuplicates);
		else
			MessageBox(0, (std::string("Фатальная ошибка при инициализации приложения\n") + std::string(e.what())).c_str(), "", MB_ICONERROR);

		return FALSE;
	}catch(...){
		return FALSE;
	}
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CInterfaceApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CInterfaceApp message handlers


CErrorsLogger* CInterfaceApp::GetErrorsLogger()
{
	return m_pLogger;
}

void CInterfaceApp::DoDeleteEverything()
{
	if (m_pLogger)
	{
		delete m_pLogger;
		m_pLogger = 0;
	}

	if (m_hMutex)
	{
		ReleaseMutex(m_hMutex);
		m_hMutex = 0;
	}

	if (m_pStorer)
	{
		delete m_pStorer;
		m_pStorer = 0;
	}
}
// End of DoDeleteEverything()


LRESULT CInterfaceApp::OnConnectionAccepted(WPARAM wParam, LPARAM lParam)
{
	CTCP_IP_SocketHolder TempSocketHolder;
	DWORD dwIP = 0;
	CMashineData* pMashine = 0;
	CInterfaceDoc* pDoc = GetActiveDoc();
		if (!pDoc)
			return 0;

	TempSocketHolder.SetSocket(wParam);
	dwIP = TempSocketHolder.ObtainIP();
	TempSocketHolder.SetSocket(INVALID_SOCKET);

	pMashine = pDoc->GetMasterManager()->GetClubState()->
				GetMashinesCollection()->FindMashine(dwIP);

		if (pMashine)
		{
			//pMashine->GetAcceptingSocket()->CloseSocket();
			pMashine->GetAcceptingSocket()->SetSocket(wParam);
			pMashine->GetAcceptingSocket()->GetOpenConnectionManager()->OnBegin();
			pDoc->GetMasterManager()->GetCommunicator()->SetSocketToReceiveFrom(wParam);
			pDoc->GetMasterManager()->GetCommunicator()->DoReceive(dwBufferLength);
			pMashine = 0;
		}

	return 0;
}
// End of OnConnectionAccepted


LRESULT CInterfaceApp::OnConnected(WPARAM wParam, LPARAM lParam)
{
	CTCP_IP_SocketHolder TempSocketHolder;
	DWORD dwIP = 0;
	CMashineData* pMashine = 0;
	CInterfaceDoc* pDoc = GetActiveDoc();
		if (!pDoc)
			return 0;

		if ( (lParam != SOCKET_ERROR) )
		{
			TempSocketHolder.SetSocket(wParam);
			dwIP = TempSocketHolder.ObtainIP();
			TempSocketHolder.SetSocket(INVALID_SOCKET);

			pMashine = pDoc->GetMasterManager()->GetClubState()->
						GetMashinesCollection()->FindMashine(dwIP);

				if (pMashine)
				{
					//pMashine->GetConnectingSocket()->CloseSocket();
					pMashine->GetConnectingSocket()->SetSocket(wParam);
					::PostThreadMessage(GetCurrentThreadId(), WM_RE_CHECK_STATE_REQUEST, wParam, 0);
				}
		}
		else
		{

		}

	return 0;
}
// End of OnConnected


LRESULT CInterfaceApp::OnDataReceived(WPARAM wParam, LPARAM lParam)
{
	DWORD dwIP = 0;
	CMashineData* pMashine = 0;
	CInterfaceDoc* pDoc = GetActiveDoc();
		if (!pDoc)
			return 0;

	CReceiveParameters* pParameters = (CReceiveParameters*)wParam;
		if ( lParam )
		{
			pDoc->GetMasterManager()->GetCommunicator()->OnDataReceived(pParameters->GetBuffer(), pParameters->GetSize(), pParameters->GetSocket(), 0);
			pParameters->SetUsed(false);

		}
		else
		{
			pParameters->SetUsed(false);
		}

	return 0;
}
// End of OnDataReceived


LRESULT CInterfaceApp::OnAcknowledge(DWORD dwMessage, WPARAM wParam, LPARAM lParam)
{
	CTCP_IP_SocketHolder TempSocketHolder;
	DWORD dwIP = 0;
	CMashineData* pMashine = 0;
	CInterfaceDoc* pDoc = GetActiveDoc();
		if (!pDoc)
			return 0;

	TempSocketHolder.SetSocket(wParam);
	dwIP = TempSocketHolder.ObtainIP();
	TempSocketHolder.SetSocket(INVALID_SOCKET);

	pMashine = pDoc->GetMasterManager()->GetClubState()->
				GetMashinesCollection()->FindMashine(dwIP);

		if (pMashine)
		{
				if ( (dwMessage == WM_LOCK_SUCCESS_ACKNOWLEDGE)
							|| (dwMessage == WM_UNLOCK_SUCCESS_ACKNOWLEDGE))
				{
						//if (wParam == pMashine->GetConnectingSocket()->GetSocket())
					pMashine->GetLastSuccessCommunication()->OnBegin();
				}

				if (dwMessage == WM_LOCK_FAIL_ACKNOWLEDGE)
				{
					// Application-specific обработка
				}
				if (dwMessage == WM_UNLOCK_FAIL_ACKNOWLEDGE)
				{
					// Application-specific обработка
				}


				if (wParam == pMashine->GetAcceptingSocket()->GetSocket())
					pMashine->GetAcceptingSocket()->CloseSocket();
				if (wParam == pMashine->GetConnectingSocket()->GetSocket())
					pMashine->GetConnectingSocket()->CloseSocket();

			pMashine = 0;
		}
		else
		{
			TempSocketHolder.SetSocket(wParam);
			TempSocketHolder.CloseSocket();
		}

	return 0;
}
// End of OnAcknowledge


LRESULT CInterfaceApp::OnLockFail(WPARAM wParam, LPARAM lParam)
{
	return OnAcknowledge(WM_LOCK_FAIL_ACKNOWLEDGE, wParam, lParam);
}
// End of OnLockFail


LRESULT CInterfaceApp::OnLockSuccess(WPARAM wParam, LPARAM lParam)
{
	return OnAcknowledge(WM_LOCK_SUCCESS_ACKNOWLEDGE, wParam, lParam);
}
// End of OnLockSuccess


LRESULT CInterfaceApp::OnUnLockFail(WPARAM wParam, LPARAM lParam)
{
	return OnAcknowledge(WM_UNLOCK_FAIL_ACKNOWLEDGE, wParam, lParam);
}
// End of OnUnLockFail


LRESULT CInterfaceApp::OnUnLockSuccess(WPARAM wParam, LPARAM lParam)
{
	return OnAcknowledge(WM_UNLOCK_SUCCESS_ACKNOWLEDGE, wParam, lParam);
}
// End of OnUnLockSuccess


LRESULT CInterfaceApp::OnReCheckStateRequest(WPARAM wParam, LPARAM lParam)
{
	CTCP_IP_SocketHolder TempSocketHolder;
	DWORD dwIP = 0;
	CMashineData* pMashine = 0;
	CInterfaceDoc* pDoc = GetActiveDoc();
		if (!pDoc)
			return 0;

	TempSocketHolder.SetSocket(wParam);
	dwIP = TempSocketHolder.ObtainIP();
	TempSocketHolder.SetSocket(INVALID_SOCKET);
	pMashine = pDoc->GetMasterManager()->GetClubState()->
				GetMashinesCollection()->FindMashine(dwIP);
	CTarifPlansCollection* pTarifsCollection = pDoc->GetMasterManager()->GetClubState()->GetTarifPlansCollection();
		if (pMashine)
		{
			pDoc->GetMasterManager()->GetCommunicator()->SetSocketToSendTo(wParam);

			CBusyIntervalHist **ppBusyIntervalHist = 0;
				if (pMashine->IsMashineBusy())
				{
					ppBusyIntervalHist = pMashine->GetBusyIntervalsCollection()->GetIntervalAtTime(CurrentTime());
						if (ppBusyIntervalHist != pMashine->GetBusyIntervalsCollection()->GetData()->end())
							pDoc->GetMasterManager()->GetCommunicator()->SendUnLockOrder((*ppBusyIntervalHist)->GetCurrentInterval(), &(*pTarifsCollection)[(*ppBusyIntervalHist)->GetCurrentInterval()->GetTarifPlanNumber()]);
				}
				else
				{
					ppBusyIntervalHist = pMashine->GetBusyIntervalsCollection()->GetPreviousInterval(CurrentTime());
						if (ppBusyIntervalHist != pMashine->GetBusyIntervalsCollection()->GetData()->end())
							pDoc->GetMasterManager()->GetCommunicator()->SendLockOrder((*ppBusyIntervalHist)->GetCurrentInterval());
						else
							pDoc->GetMasterManager()->GetCommunicator()->SendLockOrder(0);
				}
			pMashine = 0;

			pDoc->GetMasterManager()->GetCommunicator()->SetSocketToReceiveFrom(wParam);
			pDoc->GetMasterManager()->GetCommunicator()->DoReceive(dwBufferLength);
		}

	return 0;
}
// End of OnReCheckStateRequest


CInterfaceDoc* CInterfaceApp::GetActiveDoc()
{
	CMDIChildWnd* pChild =
				((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

		if ( !pChild )
			return NULL;

	CDocument* pDoc = pChild->GetActiveDocument();

		if ( !pDoc )
			return NULL;

		// Fail if doc is of wrong kind
		if ( ! pDoc->IsKindOf( RUNTIME_CLASS(CInterfaceDoc) ) )
			return NULL;

	return (CInterfaceDoc*) pDoc;
}
// End of GetActiveDoc()


CMasterRegistryStorer* CInterfaceApp::GetStorer()
{
	return m_pStorer;
}

void CInterfaceApp::OnAppExit() 
{
	SendMessage(AfxGetMainWnd()->m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
}


CDocTemplate* CInterfaceApp::GetBusyViewDocTemplate()
{
	CDocTemplate* pResultTemplate;
	POSITION Position;
	Position = GetFirstDocTemplatePosition();
	pResultTemplate = GetNextDocTemplate(Position);

	return(pResultTemplate);
}
// End of GetBusyViewDocTemplate()


CDocTemplate* CInterfaceApp::GetCashViewDocTemplate()
{
	CDocTemplate* pResultTemplate;
	POSITION Position;
	Position = GetFirstDocTemplatePosition();
	pResultTemplate = GetNextDocTemplate(Position);
	pResultTemplate = GetNextDocTemplate(Position);

	return(pResultTemplate);
}
// End of GetCashViewDocTemplate()

CDocTemplate* CInterfaceApp::GetBusyViewLXDocTemplate()
{
	CDocTemplate* pResultTemplate;
	POSITION Position;
	Position = GetFirstDocTemplatePosition();
	pResultTemplate = GetNextDocTemplate(Position);
	pResultTemplate = GetNextDocTemplate(Position);
	pResultTemplate = GetNextDocTemplate(Position);

	return(pResultTemplate);
}
// End of GetCashViewDocTemplate()


void CInterfaceApp::OnFileNew()
{
	CDocTemplate* pDocTemplate = GetBusyViewDocTemplate();

	pDocTemplate->OpenDocumentFile(NULL);
}
// End of OnFileNew()


LRESULT CInterfaceApp::OnWriteDebugMessage(WPARAM wParam, LPARAM lParam)
{
	/*char cFirstBuffer[20], cSecondBuffer[20];
	_itoa(wParam, &(cFirstBuffer[0]), 10);
	_itoa(lParam, &(cSecondBuffer[0]), 10);
		if ( (GetErrorsLogger()) && (GetActiveDoc()->GetMasterManager()->GetCommunicator()->GetDebug()) )
		{
			GetErrorsLogger()->AddLogEntry( ((std::string)"Debug Message: " + cFirstBuffer + ", " + cSecondBuffer).c_str(), bWriteDuplicates );
		}*/

	return 0;
}
// End of OnWriteDebugMessage

BOOL CInterfaceApp::OnIdle(LONG lCount) 
{
	GetActiveDoc()->OnIdle();
	return CWinApp::OnIdle(lCount);
}
