#include "stdafx.h"
#include "Interface.h"

#include "ChildFrmWithoutClose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrameWithoutClose, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrameWithoutClose, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrameWithoutClose)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrameWithoutClose::CChildFrameWithoutClose()
{
}

CChildFrameWithoutClose::~CChildFrameWithoutClose()
{
}

BOOL CChildFrameWithoutClose::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrameWithoutClose::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrameWithoutClose::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers


int CChildFrameWithoutClose::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CMenu *pSysMenu = GetSystemMenu(FALSE);
	ASSERT(pSysMenu != NULL);
	VERIFY(pSysMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND));

	return CMDIChildWnd::OnCreate(lpCreateStruct);
}
// End of OnCreate


void CChildFrameWithoutClose::OnSysCommand(UINT nID, LPARAM lParam)
{
		if(nID == SC_CLOSE)
			return;

	CMDIChildWnd::OnSysCommand(nID, lParam);
}
