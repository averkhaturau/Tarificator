#include "stdafx.h"

#include "CashView.h"
#include "InterfaceDoc.h"
#include "..\..\Slave\Slave\Exceptions.h"


IMPLEMENT_DYNCREATE(CCashView, CScrollView)


BEGIN_MESSAGE_MAP(CCashView, CScrollView)
	//{{AFX_MSG_MAP(CBusyView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




CCashView::CCashView()
{

}
// End of CCashView()


CCashView::~CCashView()
{

}
// End of ~CCashView()


void CCashView::OnDraw(CDC* pDC)
{

}
// End of OnDraw


void CCashView::OnInitialUpdate()
{
		try
		{
			CScrollView::OnInitialUpdate();

			SIZE Size = {100, 100}, Page = {1, 1}, Line = {1, 1};
			SetScrollSizes(MM_TEXT, Size, Page, Line);
		}
		catch(CAnyLogableException &e)
		{
			GetDocument()->GetErrorsLogger()->AddLogEntry(&e);
		}
		catch(...)
		{
			GetDocument()->GetErrorsLogger()->AddLogEntry("Unknown error in CBusyView::OnInitialUpdate", bDoNotWriteDuplicates);
		}
}
// End of OnInitialUpdate


inline CInterfaceDoc* CCashView::GetDocument()
{
	return (CInterfaceDoc*)m_pDocument;
}
// End of GetDocument()
