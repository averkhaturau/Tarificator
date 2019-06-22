#include "stdafx.h"
#include "Interface.h"

#include "UsualChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CUsualChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CUsualChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CUsualChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CUsualChildFrame::CUsualChildFrame()
{
}

CUsualChildFrame::~CUsualChildFrame()
{
}

BOOL CUsualChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	//cs.style&=~(LONG)FWS_ADDTOTITLE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CUsualChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CUsualChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
