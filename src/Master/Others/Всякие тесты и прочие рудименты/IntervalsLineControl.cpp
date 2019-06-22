#include "stdafx.h"

#include "IntervalsLineControl.h"
#include "..\DataStructures\Saving\MasterRegistryStorer.h"
#include "BusyView.h"
#include "..\DataStructures\ClubSettings\IntervalAddition.h"
#include "..\DataStructures\ClubSettings\ColoredInterval.h"
#include "Interface.h"

#include "InterfaceDoc.h"


BEGIN_MESSAGE_MAP(CIntervalsLineControl, CWnd)
	//{{AFX_MSG_MAP(CIntervalsLineControl)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CIntervalsLineControl::CIntervalsLineControl()
{
}
// End of CIntervalsLineControl()


CIntervalsLineControl::~CIntervalsLineControl()
{
}
// End of ~CIntervalsLineControl()

void CIntervalsLineControl::OnPaint()
{
	CPaintDC DC(this);

	CRect ClientRect;
	GetClientRect(&ClientRect);

	DC.FillSolidRect(&ClientRect, m_BackgroundColor);
	DC.FillSolidRect(ClientRect, m_ClientInterval.GetColor());

	for (CColoredIntervalsCollection::iterator Iter = m_ColoredIntervalsCollection.GetData()->begin();
		Iter != (m_ColoredIntervalsCollection.GetData()->end()); ++Iter)
	{
		DoDrawInterval(Iter, &DC);
	}

	DC.FrameRect(&ClientRect, &m_BorderBrush);

		if ( (m_dwCurrentTimeLinePosition > ClientRect.left) &&
					(m_dwCurrentTimeLinePosition < ClientRect.right) )
		{
			CPen Pen;
			if ( !Pen.CreatePenIndirect( ((CBusyView*)m_pMashineLineControl->GetParent())->GetCurrentTimeLogPen() ) )
				throw CAnyLogableException("can't create pen 8-/", bDoNotWriteDuplicates);

			CPen* pOldPen = DC.SelectObject(&Pen);

			DC.SetBkMode(TRANSPARENT);

			POINT Point;
			Point.x = m_dwCurrentTimeLinePosition;
			Point.y = ClientRect.top;

			DC.MoveTo(Point);
			Point.y = ClientRect.bottom;
			DC.LineTo(Point);

			DC.SelectObject(pOldPen);
		}

	((CBusyView*)m_pMashineLineControl->GetParent())->OnCalcCurrentTimeLine();
}
// End of OnPaint()


void CIntervalsLineControl::OnMouseMove(UINT nFlags, CPoint point)
{
	try
	{
		CTimeStorage Current = CurrentTime();
		CTimeStorage MouseTime = PointToTime(point.x);

		CBusyInterval* pInterval = 0;

		CInterval FreeInterval;
		FreeInterval.SetStartTime(m_ClientInterval.GetStartTime());
		FreeInterval.SetFinishTime(m_ClientInterval.GetFinishTime());

		/*SYSTEMTIME Test;
		m_ClientInterval.GetStartTime().GetTime(&Test);
		m_ClientInterval.GetFinishTime().GetTime(&Test);*/

		for (CBusyIntervalsCollection::iterator Iter =
				m_pMashineLineControl->GetMashineData()->
				GetBusyIntervalsCollection()->GetData()->begin();
			Iter != (m_pMashineLineControl->GetMashineData()->
				GetBusyIntervalsCollection()->GetData()->end());
			++Iter)
		{
			if ((*Iter)->GetCurrentInterval()->IsTimeInInterval(MouseTime))
			{
				pInterval = (*Iter)->GetCurrentInterval();
				break;
			}
			if ( ((*Iter)->GetCurrentInterval()->GetFinishTime() < MouseTime) &&
						((*Iter)->GetCurrentInterval()->GetFinishTime() > FreeInterval.GetStartTime()) )
			{
				FreeInterval.SetStartTime((*Iter)->GetCurrentInterval()->GetFinishTime());
			}
			if ( ((*Iter)->GetCurrentInterval()->GetStartTime() > MouseTime) &&
						((*Iter)->GetCurrentInterval()->GetStartTime() < FreeInterval.GetFinishTime()) )
			{
				FreeInterval.SetFinishTime((*Iter)->GetCurrentInterval()->GetStartTime());
			}
		}
		if (FreeInterval.GetStartTime() < Current)
			FreeInterval.SetStartTime(Current);

		CString Text = CString(m_pMashineLineControl->GetMashineData()->GetMashineName().c_str()) + ": ";
		if (pInterval)
		{
			char cBuffer[100];

			Text += " занят ";
			Text += IntervalAddition::DescribeInterval_In_Russian(pInterval).c_str();
			Text += ". Цена ";
			Text += _itoa(pInterval->GetPrice(), &(cBuffer[0]), 10);
			Text += " рублей, клиент ";
				if ( pInterval->GetClientName().c_str() == "" )
				{
					Text += "неизвестный";
				}
				else
				{
					Text += CString(pInterval->GetClientName().c_str());
				}

			CMasterManager* pMasterManager = ((CBusyView*)m_pMashineLineControl->GetParent())->GetDocument()->GetMasterManager();

			Text += ", тариф ";
			Text += CString( ((*pMasterManager->GetClubState()->GetTarifPlansCollection())[pInterval->GetTarifPlanNumber()]).GetName().c_str() );

			Text += ", оператор ";
			Text += CString( ((*pMasterManager->GetClubState()->GetOperatorsCollection())[pInterval->GetOperatorNumber()]).GetName().c_str() );
		}
		else
		{
				if (MouseTime > Current)
				{
					Text += " свободен ";
					Text += IntervalAddition::DescribeInterval_In_Russian(&FreeInterval).c_str();
				}
				else
				{
					Text = "";
				}
		}

		((CBusyView*)m_pMashineLineControl->GetParent())->GetDocument()->SetStatusBarText(Text);

		CLineControl::OnMouseMove(nFlags, point);
	}
	catch(...)
	{
		((CBusyView*)m_pMashineLineControl->GetParent())->GetDocument()->GetErrorsLogger()->
			AddLogEntry("Error in CIntervalsLineControl::OnMouseMove", bDoNotWriteDuplicates);
	}
}
// End of OnMouseMove

