#include "stdafx.h"

#include "BusyChildFrame.h"
#include "InterfaceDoc.h"
#include "Interface.h"



IMPLEMENT_DYNCREATE(CBusyChildFrame, CChildFrameWithoutClose)

BEGIN_MESSAGE_MAP(CBusyChildFrame, CChildFrameWithoutClose)
	//{{AFX_MSG_MAP(CBusyChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CBusyChildFrame::CBusyChildFrame()
{

}
// End of CBusyChildFrame()


CBusyChildFrame::~CBusyChildFrame()
{

}
// End of ~CBusyChildFrame()


BOOL CBusyChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	//cs.style&=~(LONG)FWS_ADDTOTITLE;

	return TRUE;
}


void CBusyChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
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
				lstrcat(szText, CString("Занятые машины - ") + pDocument->GetMasterManager()->GetClubState()->GetClubName().c_str());
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
