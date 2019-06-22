#include "stdafx.h"
#include "COMMCTRL.H"
#include <math.h>
//#include "afximpl.h"

#include "Interface.h"
#include "InterfaceDoc.h"
#include "BusyView.h"
#include "..\DataStructures\ClubSettings\TimeStorage.h"
#include "AdditionalResource.h"
#include <commctrl.h>
#include "..\DataStructures\Constants.h"
#include "LineControlsCollection.h"
#include "IntervalsLineControl.h"
#include "..\DataStructures\SpecDaysCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CBusyView, CScrollView)

BEGIN_MESSAGE_MAP(CBusyView, CScrollView)
//{{AFX_MSG_MAP(CBusyView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_GETRANDOMINTERVALS, OnTest)
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_NOTIFY(HDN_ENDTRACK, dwHeaderID, OnEndTrack)
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY(HDN_REALMOVE, dwHeaderID, OnEndTrack)
	ON_COMMAND(ID_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CBusyView::CBusyView()
{
	try{

		m_dwLineHeight = 22;
		m_dwHeaderHeight = 16;
		m_dwOldScrollLines = 0;

		m_CurrentTimeLogPen.lopnStyle = PS_DOT;
		POINT Width;
		Width.x = 0;
		Width.y = 0;
		m_CurrentTimeLogPen.lopnWidth = Width;
		m_CurrentTimeLogPen.lopnColor = RGB(255, 255, 255);

		m_pHeaderControl = 0;
		m_pLineControlsCollection = 0;

		try{
			m_pHeaderControl = new CRealDragHeaderControl;
			m_pLineControlsCollection = new CLineControlsCollection;

		}catch(...){
			DoDeleteEverything();
			throw;
		}

	}catch(CAnyLogableException& e){
		throw CAnyLogableException(((CString)
			"An error occured in CBusyView::CBusyView(): "
				+ (CString)e.what()).operator LPCSTR(), e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An error occured in CBusyView::CBusyView()", bDoNotWriteDuplicates);
	}
}


CBusyView::~CBusyView()
{
	DoDeleteEverything();
}


void CBusyView::DoDeleteEverything()
{
	if (m_pHeaderControl)
	{
		delete m_pHeaderControl;
		m_pHeaderControl = 0;
	}
	if (m_pLineControlsCollection)
	{
		delete m_pLineControlsCollection;
		m_pLineControlsCollection = 0;
	}
}
// End of DoDeleteEverything()


void CBusyView::OnDestroy()
{
	try{
		if (m_uiTimerIdentifier)
			KillTimer(m_uiTimerIdentifier);

		CScrollView::OnDestroy();

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(
			(CString)"An error occured in CBusyView::OnDestroy: "
				+(CString)e.what(), e.GetWriteDuplicatesToLog());
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry(
			(CString)"An error occured in CBusyView::OnDestroy",
				bDoNotWriteDuplicates);
	}

}
// End of DestroyWindow()


BOOL CBusyView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CBusyView::OnInitialUpdate()
{
	try{ // перестраXYемся
		m_uiTimerIdentifier = SetTimer(dwViewTimerID, GetDocument()->GetMasterManager()->GetTimerPeriod(), 0);
			if ( !(m_uiTimerIdentifier) )
				throw CAnyLogableException("can't create timer", bDoNotWriteDuplicates);

		WNDCLASS wc;
		HINSTANCE hInst = AfxGetInstanceHandle();
		// Беру инфу о классе STATIC
		GetClassInfo(hInst, "STATIC", &wc);

		wc.lpfnWndProc = ::DefWindowProc;
		wc.lpszClassName = "LineControl";

		// Регистрю LineControl
		AfxRegisterClass(&wc);

		CScrollView::OnInitialUpdate();

		// Разберёмся с хедером
		CreateHeaderControl();
		ReSizeHeader();
		// разобрались а хедером

		// Разберёмся с ЛайнсКонтролКоллекшн
		m_pLineControlsCollection->resize(
			GetDocument()->GetMasterManager()->
				GetClubState()->GetMashinesCollection()->size());

		CMashinesCollection* pMashinesCollection = GetDocument()->
					GetMasterManager()->GetClubState()->GetMashinesCollection();

		for(DWORD dwNumber = 0; dwNumber < m_pLineControlsCollection->size(); ++dwNumber)
		{
			(*m_pLineControlsCollection)[dwNumber].SetMashineData( &((*pMashinesCollection)[dwNumber]) );
			CreateLineControl(&((*m_pLineControlsCollection)[dwNumber]),
						dwLinesBaseID + dwNumber, dwNumber);
		}

		ReSizeControls();

		CRect ClientRect;
		GetClientRect(&ClientRect);

		// Задание режимов скроллинга
		CSize TotalSize;
		TotalSize.cx = 0;
		TotalSize.cy = m_dwLineHeight * (m_pLineControlsCollection->size()) + m_dwHeaderHeight;
		CSize PageSize;
		PageSize.cx = 1;
		PageSize.cy = m_dwLineHeight - 1;
		SetScrollSizes(MM_TEXT, TotalSize, PageSize, PageSize);


		// А теперь кэшн изобразим
		GetParent()->SetWindowText(GetDocument()->GetMasterManager()->
				GetClubState()->GetClubName().c_str()); 

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(&e);
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry("Unknown error in CBusyView::OnInitialUpdate", bDoNotWriteDuplicates);
	}
}
// End of OnInitialUpdate


// CBusyView diagnostics

#ifdef _DEBUG
void CBusyView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CBusyView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CInterfaceDoc* CBusyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInterfaceDoc)));
	return (CInterfaceDoc*)m_pDocument;
}
#endif //_DEBUG


void CBusyView::CreateLineControl(CMashineLineControl* pLine, UINT uiLineID,
					DWORD dwRow)
{
	CRect _Rect(0,0,0,0);

	try{
		if (m_pHeaderControl->m_hWnd) // e.g. created
			m_pHeaderControl->GetWindowRect(&_Rect);

		DWORD dwNewX =0, dwNewY;
		dwNewY = (m_dwLineHeight-1) * dwRow + _Rect.Height();

		// Создаю новый Line
		pLine->CreateEx(
			0, // Window Style
			"LineControl", // Имя зарегистрированного класса контрола
			"", // Window Name
			WS_CHILD | WS_VISIBLE, //Styles
			CRect(dwNewX, dwNewY, _Rect.right - _Rect.left, dwNewY + m_dwLineHeight),
			this, // Parent
			uiLineID // ID
		);

	}catch(CAnyLogableException &e){
		throw CAnyLogableException((std::string)"CreateLineControl faild: "
			+ (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("CreateLineControl faild", bDoNotWriteDuplicates);
	}
}
// End of CreateLineControl


void CBusyView::CreateHeaderControl()
{
	int iLenths[3] = {120, 0, 80};
	try{
		CRect ClientRect;
		GetClientRect(&ClientRect);

		m_pHeaderControl->CreateEx(
			0, // Extended Styles
			WC_HEADER, // Имя зарегистрированного класса контрола
			"", // Window Name
			CCS_BOTTOM | HDS_FULLDRAG | WS_CHILD | WS_VISIBLE, //Styles
			CRect(0, 0, ClientRect.right, m_dwHeaderHeight),
			this, // Parent
			dwHeaderID // ID
		);

		// Чтобы добавлять элементы в HeaderControl
		HDITEM _hdiStructure = {HDI_TEXT, 0,0,0,0, HDF_LEFT | HDF_STRING | HDF_RTLREADING};

		for (int i=0; i<3; ++i)
		{
			_hdiStructure.cxy = iLenths[i];
			_hdiStructure.pszText = (char*)_cHeaders[i].c_str();
			_hdiStructure.cchTextMax = sizeof (_hdiStructure.pszText);

			m_pHeaderControl->InsertItem(i, &_hdiStructure);
		}

	}catch(...){
		throw CAnyLogableException("Error creating HeaderControl", bDoNotWriteDuplicates);
	}
}
// End of CreateHeaderControl()


void CBusyView::OnSize(UINT nType, int cx, int cy) 
{
	try{
		CScrollView::OnSize(nType, cx, cy);

		if (!m_pHeaderControl->m_hWnd)
			return;

		//OnScroll();

		ReSizeHeader();
		ReSizeControls();

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(&e);
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry(
			"Exception in CBusyView::OnSize", bDoNotWriteDuplicates);
	}
}
// End of OnSize


void CBusyView::ReSizeHeader(int iItem)
{
	try{

		CRect ClientRect;
		GetClientRect(ClientRect);
		int cx = ClientRect.Width();

		CRect Rect;
		DWORD dwOldSize = 0;
		for (int i = 0; i < 3; ++i)
		{
			m_pHeaderControl->GetItemRect(i, Rect);
			dwOldSize += Rect.Width();
		}

		if (m_pHeaderControl->m_hWnd)
			m_pHeaderControl->SetWindowPos(0, 0, ClientRect.left, cx, m_dwHeaderHeight, SWP_NOZORDER | SWP_NOMOVE);

		HDITEM Item;
		Item.mask = HDI_WIDTH;

		if ( (iItem == 0) || (iItem == 2) )
		{
			m_pHeaderControl->GetItemRect(1, &Rect);
			Item.cxy = Rect.Width() + cx - dwOldSize;
			m_pHeaderControl->SetItem(1, &Item);
		}

		if ( iItem == 1 )
		{
			m_pHeaderControl->GetItemRect(2, &Rect);
			Item.cxy = Rect.Width() + cx - dwOldSize;
			m_pHeaderControl->SetItem(2, &Item);
		}

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry((CString)
			"Exception in CBusyView::ReSizeHeader: "
				+ (CString)e.what(), e.GetWriteDuplicatesToLog());
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry(
			"Exception in CBusyView::ReSizeHeader",
				bDoNotWriteDuplicates);
	}
}
// End of ReSizeHeader


void CBusyView::OnDraw(CDC* pDC) 
{
}


void CBusyView::ReSizeControls()
{
	try{
		if (m_pHeaderControl->m_hWnd) // e.g. created
		{
			// вспомогательные переменные для ускорения
			CRect _Rect;
			int _aiLengths[3]; // число 3 - не "магическая цифра", она контекстно неизменяема
			signed int i; // помогает достичь некоторого рода совместимости MS & Borland
			for (i = 0; i < 3; ++i)
			{
				m_pHeaderControl->GetItemRect(i, _Rect);
				_aiLengths[i] = _Rect.Width();
			}

			for (CLineControlsCollection::iterator
					_Iter = m_pLineControlsCollection->GetData()->begin();
				_Iter != m_pLineControlsCollection->GetData()->end(); ++_Iter)
			{
				(*_Iter)->SetNameLength(_aiLengths[0]);
				(*_Iter)->SetIntervalsLength(_aiLengths[1]);
				(*_Iter)->SetStatusLength(_aiLengths[2]);
			}
		}// if (m_pHeaderControl->m_hWnd) // e.g. created

	}catch(CAnyLogableException &e){
		throw CAnyLogableException(((CString)
			"Exception in CBusyView::ReSizeControls: "
				+ (CString)e.what()).operator LPCSTR(), e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("Exception in CBusyView::ReSizeControls",
				bDoNotWriteDuplicates);
	}
}
// End of ReSizeControls


LRESULT CBusyView::OnEndTrack(WPARAM wParam, LPARAM lParam)
{
	try{

		LPNMHEADER phdn = (LPNMHEADER)wParam;
		ReSizeHeader(phdn->iItem);

		ReSizeControls();
		Invalidate();

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(&e);
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry("Error in OnEndTrack", bDoNotWriteDuplicates);
	}

	return 0;
}
// End of OnEndTrack


void CBusyView::OnTest() 
{
/*	CSpecDaysCollection TestColl;

	//((CInterfaceApp*)AfxGetApp())->GetStorer()->ReadSpecDays(&TestColl);

	CSpecialTimeInterval Sunday;
	Sunday.GetTimeMask()->wDayOfWeek = 1;
	Sunday.SetType(sdHoliday);
	TestColl.AddResident(&Sunday);

	CSpecialTimeInterval Saturday;
	Saturday.GetTimeMask()->wDayOfWeek = 7;
	Saturday.SetType(sdHoliday);
	TestColl.AddResident(&Saturday);


	CSpecialTimeInterval The1OfMay;
	The1OfMay.GetTimeMask()->wDay = 1;
	The1OfMay.GetTimeMask()->wMonth = 5;
	The1OfMay.SetType(sdHoliday);

	TestColl.AddResident(&The1OfMay);

	((CInterfaceApp*)AfxGetApp())->GetStorer()->SaveSpecDays(&TestColl);

	try{
		const char* HumanNames[29] = {"Филипп", "Толя", "Коля", "Петя", "Вася", "Маша", "Лариса", "Лида", "Валентин", "Петя", "Ипподром", "Тузик", "Вова", "Саша", "Инга", "Анестезия", "Верочка", "Серёжа", "Василиса", "Игорь", "Ксения", "Митахондрия", "Антропогенез", "Администратор", "Оболтус", "Бешеный Hacker", "Порсер", "Гипоталамус", "Рыжий"};

		CClubState *_pClubState = GetDocument()->GetMasterManager()->GetClubState();
		CMashinesCollection *_pMashinesCollection =
				_pClubState->GetMashinesCollection();

		CInterval _Today;
		_Today.SetStartTime(_pClubState->GetWorkingInterval()->
				GetStartTime());

		_Today.SetLengthFromStart(_pClubState->GetWorkingInterval()->
				GetLength());

		srand(CurrentTime().GetTime()&0xffffffff);

		for (int i = 0; i<_pMashinesCollection->size(); ++i)
		{
			(_pMashinesCollection->operator [](i)).GetBusyIntervalsCollection()->Clear();
			CBusyInterval _AccidentInterval;
			_AccidentInterval.SetFinishTime(_Today.GetStartTime());

			int _numint = (3+rand())%17;

			int iRealIntervalNumber = 0;

			for (int j = 0; j < _numint; ++j)
			{
				_AccidentInterval.SetStartTime(CTimeStorage(
						_AccidentInterval.GetFinishTime().GetTime() + 
						(rand() % 7 ) * A_Minute.GetTime() * 10 ));

				_AccidentInterval.SetLengthFromStart(CTimeStorage(
						(A_Minute.GetTime()*(rand()+10)) % (3*An_Hour.GetTime()) ));

				_AccidentInterval.SetClientName(HumanNames[rand()%28]);

				_AccidentInterval.SetOperatorNumber(rand()
						% _pClubState->GetOperatorsCollection()->size());

				COperator* pOperator = &((*_pClubState->GetOperatorsCollection())
							[_AccidentInterval.GetOperatorNumber()]);


				{ // установка тарифного плана
					CMashineData::CTarifPlansNumbers*
						_pTarifPlansNumbers =
							_pMashinesCollection->operator [](i).
								GetTarifPlansNumbers();

					// Подсчет числа разрешенных планов
					int iTotalAllowedPlansNumber = 0;
					CMashineData::CTarifPlansNumbers::iterator Iter =
								_pTarifPlansNumbers->begin();
					for (; Iter != _pTarifPlansNumbers->end(); ++Iter)
							if (((*_pClubState->GetTarifPlansCollection())[*Iter]).GetPermission()
										<= (pOperator->GetPermission()))
								++iTotalAllowedPlansNumber;

					// Собственно выбор нужного плана
					int iRandomPlanNumber = rand() % iTotalAllowedPlansNumber;
					int iCurrentAllowedPlanNumber = 0;
					Iter = _pTarifPlansNumbers->begin();
					for (; Iter != _pTarifPlansNumbers->end(); ++Iter)
						if (((*_pClubState->GetTarifPlansCollection())[*Iter]).GetPermission()
									<= (pOperator->GetPermission()))
						{
							if (iCurrentAllowedPlanNumber == iRandomPlanNumber)
							{
								_AccidentInterval.SetTarifPlanNumber(*Iter);
								break;
							}
							++iCurrentAllowedPlanNumber;
						}
				}

				_AccidentInterval.SetCreationTime(CurrentTime());

					// Чтобы добавлялись только те интервалы, цена которых
					// может нормально вычислиться
					try
					{
						if (!_AccidentInterval.IsValidTimeInterval())
							throw CAnyLogableException("Bad interval", bDoNotWriteDuplicates);
						_AccidentInterval.SetPrice( _pClubState->CalcIntervalPrice(&_AccidentInterval) );
						(_pMashinesCollection->operator [](i)).GetBusyIntervalsCollection()->AddInterval(_AccidentInterval, iRealIntervalNumber);
						++iRealIntervalNumber;
					}
					catch(...)
					{

					}
			}
		}

		for(DWORD dwNumber = 0; dwNumber < m_pLineControlsCollection->size(); ++dwNumber)
		{
			((*m_pLineControlsCollection)[dwNumber]).SetMashineData(
				&((*GetDocument()->GetMasterManager()->GetClubState()->
					GetMashinesCollection())[dwNumber]) );
		}

		RefreshAllLineData();
		Invalidate();

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(&e);
	}catch(std::exception &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(e.what(), bDoNotWriteDuplicates);
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry("Uncknown error in test function", bDoNotWriteDuplicates);
	}*/
}


void CBusyView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	/*if ( (nSBCode == SB_THUMBPOSITION) || (nSBCode == SB_THUMBTRACK) )
	{
		OnScroll(true, nPos);
	}
	else
	{*/
		CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
		/*OnScroll();
	}*/
}
// End of OnVScroll


BOOL CBusyView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CScrollView::OnMouseWheel(nFlags, zDelta, pt);

	//OnScroll();

	return 0;
}
// End of OnMouseWheel


void CBusyView::OnScroll(bool bCheckInvalidate, signed long int sliPos)
{
	try{

		CSize Position;
			if ( (bCheckInvalidate) && (sliPos >= 0))
				Position.cy = sliPos;
			else
				Position = GetDeviceScrollPosition();

		DWORD dwScrollLines = floor((double)Position.cy / (double)(m_dwLineHeight - 1));

		POINT ScrollTo;
		ScrollTo.x = 0;
		ScrollTo.y = dwScrollLines * (m_dwLineHeight - 1);
		if ( (m_dwOldScrollLines != dwScrollLines) || (!bCheckInvalidate) )
		{
			ScrollToPosition(ScrollTo);

			ReSizeHeader();
			Invalidate();
		}
		m_dwOldScrollLines = dwScrollLines;

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(std::string(
			(std::string)"CBusyView::OnScroll failed: " +
			(std::string)e.what()).c_str(), e.GetWriteDuplicatesToLog());
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry(
			"CBusyView::OnScroll failed", bDoNotWriteDuplicates);
	}
}
// End of OnScroll()


void CBusyView::OnTimer(UINT nIDEvent)
{
	OnCalcCurrentTimeLine();

	GetDocument()->GetMasterManager()->OnTimerEvent();

		if (GetDocument()->OnTimer())
		{
			RefreshAllLineData();
			Invalidate();
		}

	DWORD dwRedMashinesNumber = 0;
	CMashinesCollection* pCollection = GetDocument()->GetMasterManager()->GetClubState()->GetMashinesCollection();
		for (int i = 0; i < pCollection->size(); ++i)
		{
				if ( (*pCollection)[i].GetLastSuccessCommunication()->IsTimeExpired() )
				{
					++dwRedMashinesNumber;
					(*m_pLineControlsCollection)[i].GetMashineNameControl()->SetTextColor(RGB(255, 0, 0));
				}
				else
				{
					(*m_pLineControlsCollection)[i].GetMashineNameControl()->SetTextColor(RGB(0, 0, 0));
				}
			(*m_pLineControlsCollection)[i].GetMashineNameControl()->Invalidate();
		}

		//if ( dwRedMashinesNumber >= 6 )
		//	((CInterfaceApp*)AfxGetApp())->GetActiveDoc()->GetMasterManager()->GetCommunicator()->SetDebug(true);
}
// End of OnTimer


void CBusyView::OnCalcCurrentTimeLine()
{
	try{

		if ( !(m_pLineControlsCollection->size()) )
			throw CAnyLogableException("m_pLineControlsCollection is empty in OnCalcCurrentTimeLine", bDoNotWriteDuplicates);

	CTimeStorage Current = CurrentTime();

	DWORD dwLineControlCoords = (*m_pLineControlsCollection)[0].
				GetIntervalsLineControl()->TimeToPoint(Current.GetTime());

	SYSTEMTIME CurrentSystemTime;
	Current.GetTime(&CurrentSystemTime);

		for (CLineControlsCollection::iterator Iter = m_pLineControlsCollection->GetData()->begin();
			Iter < m_pLineControlsCollection->GetData()->end(); ++Iter)
		{
			(*Iter)->GetIntervalsLineControl()->SetCurrentTimeLinePosition(dwLineControlCoords);
			(*Iter)->GetIntervalsLineControl()->CheckCurrentTimeUpdate();
			(*Iter)->GetMashineStatusControl()->CheckStatusUpdate(&CurrentSystemTime);
		}

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(&e);
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry("Error in OnCalcCurrentTimeLine", bDoNotWriteDuplicates);
	}
}
// End of OnCalcCurrentTimeLine()


void CBusyView::RefreshAllLineData()
{
		CLineControlsCollection::iterator Iter = m_pLineControlsCollection->GetData()->begin(),
					EndIter = m_pLineControlsCollection->GetData()->end();
		for (; Iter < EndIter; ++Iter)
		{
			(*Iter)->RefreshLineData();
		}
}
// End of RefreshAllLineData
