#include "stdafx.h"

#include "CashChildFrame.h"
#include "Interface.h"



IMPLEMENT_DYNCREATE(CCashChildFrame, CUsualChildFrame)

BEGIN_MESSAGE_MAP(CCashChildFrame, CUsualChildFrame)
	//{{AFX_MSG_MAP(CCashChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CCashChildFrame::CCashChildFrame()
{

}
// End of CCashChildFrame()


CCashChildFrame::~CCashChildFrame()
{

}
// End of ~CCashChildFrame()


BOOL CCashChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	//cs.style&=~(LONG)FWS_ADDTOTITLE;

	return TRUE;
}


void CCashChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return;     // leave child window alone!

	CInterfaceDoc* pDocument = ((CInterfaceApp*)AfxGetApp())->GetActiveDoc();
		if (bAddToTitle)
		{
			TCHAR szText[256+_MAX_PATH] = "";

			if ( !pDocument )
				lstrcpy(szText, m_strTitle);
			else
			{
				lstrcat(szText, CString("Выручка - ") + pDocument->GetMasterManager()->GetClubState()->GetClubName().c_str());
			}
			//if (m_nWindow > 0)
				//wsprintf(szText + lstrlen(szText), _T(":%d"), m_nWindow);

			// set title
			SetWindowText(szText);

				/*if ( AfxGetMainWnd() )
					AfxGetMainWnd()->SetWindowText(szText);*/
		}
}
// End of OnUpdateFrameTitle
