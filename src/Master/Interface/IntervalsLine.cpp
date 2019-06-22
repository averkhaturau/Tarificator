#include "StdAfx.h"

#include "IntervalsLine.h"
#include "..\DataStructures\Saving\MasterRegistryStorer.h"
#include "..\DataStructures\ClubSettings\IntervalAddition.h"
#include "..\DataStructures\ClubSettings\ColoredInterval.h"
#include "Interface.h"

#include "InterfaceDoc.h"

BEGIN_MESSAGE_MAP(CIntervalsLine, CLineControl)
	//{{AFX_MSG_MAP(CIntervalsLine)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CIntervalsLine::CIntervalsLine()
{
	m_pMashineData = 0;

	m_ClientInterval.SetColor(ciDefaultFreeColor);

	m_dwCurrentTimeLinePosition = 0;
	m_dwOldCurrentTimeLinePosition = 0;

		try
		{
			HINSTANCE hInst = AfxGetInstanceHandle();
			WNDCLASS wc;
				if ( !GetClassInfo(hInst, cIntervalsLineControlClassName, &wc) )
				{
					// Беру инфу о классе STATIC
					GetClassInfo(hInst, "STATIC", &wc);

					wc.lpfnWndProc = ::DefWindowProc;
					wc.lpszClassName = cIntervalsLineControlClassName;

					// Регистрю LineControl
					AfxRegisterClass(&wc);
				}

			((CInterfaceApp*)AfxGetApp())->GetStorer()->ReadWorkingInterval(&m_ClientInterval);
		}
		catch(CAnyLogableException& Error){
			std::string ErrorString = "An error occured in CIntervalsLineControl::CIntervalsLineControl: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CIntervalsLineControl::CIntervalsLineControl", bDoNotWriteDuplicates);
		}
}
// End of CIntervalsLineControl()


CIntervalsLine::~CIntervalsLine()
{

}
// End of ~CIntervalsLineControl()

void CIntervalsLine::OnPaint()
{
	CPaintDC DC(this);

	CRect ClientRect;
	GetClientRect(&ClientRect);

	DC.FillSolidRect(ClientRect, GetMainInterval()->GetColor());

	for (CColoredIntervalsCollection::iterator Iter =
		GetIntervalsCollection()->GetData()->begin();
		Iter != (GetIntervalsCollection()->GetData()->end()); ++Iter)
	{
		DoDrawInterval(Iter, &DC);
	}

	if ( (m_dwCurrentTimeLinePosition > ClientRect.left) &&
				(m_dwCurrentTimeLinePosition < ClientRect.right) )
	{
		CPen Pen;
		if ( !Pen.CreatePen(PS_DOT, 0, RGB(0xff, 0xff, 0xff)) )
			return;

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

	// Рисование линии текущего времени
	{
		CheckCurrentTimeUpdate();
	}
}


CTimeStorage CIntervalsLine::PointToTime(DWORD dwPoint)
{
	CRect ClientRect;
	GetClientRect(&ClientRect);
	DWORD dwClientWidth = ClientRect.Width();

	CTimeContainer Result = (m_ClientInterval.GetLength().GetTime() *
				(CTimeContainer)dwPoint / dwClientWidth);
	Result += m_ClientInterval.GetStartTime().GetTime();

	return Result;
}
// End of PointToTime


signed long int CIntervalsLine::TimeToPoint(CTimeContainer Time)
{
	CRect ClientRect;
	GetClientRect(&ClientRect);
	DWORD dwClientWidth = ClientRect.Width();

		if ( Time > m_ClientInterval.GetFinishTime() )
			return ClientRect.right + 10;
		if ( Time < m_ClientInterval.GetStartTime() )
			return ClientRect.left - 10;

	CTimeContainer Start = m_ClientInterval.GetStartTime().GetTime();
	CTimeContainer Length = m_ClientInterval.GetLength().GetTime();

	DWORD dwResult = 1 + dwClientWidth * (Time - Start) / Length;

	return dwResult;
}
// End of TimeToPoint


void CIntervalsLine::DoDrawInterval(CColoredIntervalsCollection::iterator Iter, CDC* pDC)
{
	CRect _Rect;
	GetClientRect(_Rect);

	signed int
	siValue = TimeToPoint((*Iter)->GetStartTime().GetTime());
	
	if (siValue > _Rect.left)
		_Rect.left = siValue;

	siValue = TimeToPoint((*Iter)->GetFinishTime().GetTime());

	if (siValue < _Rect.right)
		_Rect.right = siValue;
	else
	{
		_Rect.right += 1;
		_Rect.right -= 1;
	}

	if (_Rect.right < _Rect.left)
		return;

	pDC->FillSolidRect(_Rect, (*Iter)->GetColor());
	pDC->FrameRect(_Rect, &m_BorderBrush);
}
// End of DoDrawInterval


void CIntervalsLine::CheckCurrentTimeUpdate()
{
	// рисование линии текущего времени
	SetCurrentTimeLinePosition(TimeToPoint(CurrentTime().GetTime()));

	if (m_dwOldCurrentTimeLinePosition != m_dwCurrentTimeLinePosition)
	{
		Invalidate();
		m_dwOldCurrentTimeLinePosition = m_dwCurrentTimeLinePosition;
	}
}
// End of CheckCurrentTimeUpdate()


void CIntervalsLine::OnMouseMove(UINT nFlags, CPoint point)
{
		try
		{
				if (!m_pMashineData)
					return;

			CInterfaceDoc* pDoc = ((CInterfaceApp*)AfxGetApp())->GetActiveDoc();

			CTimeStorage Current = CurrentTime();
			CTimeStorage MouseTime = PointToTime(point.x);

			CBusyInterval* pInterval = 0;

			CInterval FreeInterval;
			FreeInterval.SetStartTime(m_ClientInterval.GetStartTime());
			FreeInterval.SetFinishTime(m_ClientInterval.GetFinishTime());

			CBusyIntervalsCollection::iterator Iter = m_pMashineData->GetBusyIntervalsCollection()->GetData()->begin(),
						EndIter = m_pMashineData->GetBusyIntervalsCollection()->GetData()->end();
				for (; Iter != EndIter; ++Iter)
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

			CString Text = CString(m_pMashineData->GetMashineName().c_str()) + ": ";
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

					CMasterManager* pMasterManager = pDoc->GetMasterManager();

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

			pDoc->SetStatusBarText(Text);

			CLineControl::OnMouseMove(nFlags, point);
		}
		catch(...)
		{
		}
}
// End of OnMouseMove
