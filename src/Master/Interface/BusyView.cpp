// BusyView.cpp : implementation file


#include "stdafx.h"
#include "Interface.h"
#include "BusyView.h"
#include "AdditionalResource.h"
#include "InterfaceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CBusyView, CView)

CBusyView::CBusyView()
{
	m_uiTimerIdentifier = 0;
}

CBusyView::~CBusyView()
{
}


BEGIN_MESSAGE_MAP(CBusyView, CView)
	//{{AFX_MSG_MAP(CBusyView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CBusyView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
}

// CBusyView diagnostics

#ifdef _DEBUG
void CBusyView::AssertValid() const
{
	CView::AssertValid();
}

void CBusyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

CInterfaceDoc* CBusyView::GetDocument()
{
#ifdef _DEBUG
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInterfaceDoc)));
#endif
	return (CInterfaceDoc*)m_pDocument;
}

void CBusyView::OnInitialUpdate()
{
	CRect MyRect;
	GetClientRect(MyRect);
	m_Grid.CreateEx(
				0, // Ex window Style
				GRIDCTRL_CLASSNAME, // Имя зарегистрированного класса контрола
				"", // Window Name
				WS_CHILD | WS_VISIBLE, //Styles
				MyRect,
				this, // Parent
				GridCtrlID // ID
	);

	NONCLIENTMETRICS MyNCM;
	MyNCM.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, MyNCM.cbSize, &MyNCM, 0);

	MyNCM.lfMessageFont.lfHeight = -16;
	MyNCM.lfMessageFont.lfWeight = FW_BOLD;
	strcpy(MyNCM.lfMessageFont.lfFaceName, "MS Sans Serif");

	CFont MyFont;
	MyFont.CreateFontIndirect(&MyNCM.lfMessageFont);
	
	m_Grid.SetFont(&MyFont);
	
	//m_Grid.SetTextBkColor(RGB(0xAE, 0xE0, 0xAE));
	
	m_Grid.SetMashinesCollection(GetDocument()->
		GetMasterManager()->GetClubState()->GetMashinesCollection());

	m_Grid.SetTarifPlansCollection(GetDocument()->
		GetMasterManager()->GetClubState()->GetTarifPlansCollection());

	m_ImageList.Create(MAKEINTRESOURCE(IDB_BMP_MASHINES_CONNECTED), 16, 1, RGB(255,255,255));
	m_Grid.SetImageList(&m_ImageList);

	m_Grid.DisplayMashines();
	m_Grid.Refresh();

	m_uiTimerIdentifier = SetTimer(dwViewLXTimerID, GetDocument()->GetMasterManager()->GetTimerPeriod(), 0);
}


void CBusyView::OnSize(UINT nType, int cx, int cy)
{
	try{
		CView::OnSize(nType, cx, cy);

		DoReLayOut();

	}catch(CAnyLogableException &e){
		GetDocument()->GetErrorsLogger()->AddLogEntry(&e);
	}catch(...){
		GetDocument()->GetErrorsLogger()->AddLogEntry(
			"Exception in CBusyViewLX::OnSize", bDoNotWriteDuplicates);
	}
}
//end of OnSize

void CBusyView::DoReLayOut()
{
	if (m_Grid.m_hWnd != 0 )
	{
		CRect MyRect;
		GetClientRect(MyRect);
		m_Grid.MoveWindow(MyRect);
	}
}
//end of DoReLayOut

void CBusyView::OnTimer(UINT nIDEvent)
{
	static bool bIsWorking = false;
	if (!bIsWorking)
	{
		bIsWorking = true;
		m_Grid.OnTimer(nIDEvent);

		GetDocument()->GetMasterManager()->OnTimerEvent();

		if (GetDocument()->OnTimer())
		{
			Invalidate();
		}
	}

	bIsWorking = false;
}
//end of OnTimer

void CBusyView::OnDestroy() 
{
	if (m_uiTimerIdentifier)
		KillTimer(m_uiTimerIdentifier);
	CView::OnDestroy();
}

void CBusyView::GetSelectedMashines(CMashinesCollection* a_pSelectedMashines)
{
	a_pSelectedMashines->Clear();
	m_Grid.AddSelectedMashines(a_pSelectedMashines);
}
//end of GetSelectedMashines


void CBusyView::Refresh()
{
	DoReLayOut();
	m_Grid.DoRelayout();
}
// End of Refresh()
