#include "stdafx.h"

#include "MashineStatusControl.h"
#include "MashineLineControl.h"


BEGIN_MESSAGE_MAP(CMashineStatusControl, CWnd)
	//{{AFX_MSG_MAP(CMashineStatusControl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMashineStatusControl::CMashineStatusControl()
{
	m_pMashineLineControl = 0;
	(CTimeStorage((CTimeContainer)0)).GetTime(&m_LastShownTime);

	m_bFree = true;
	m_dwLeftSpace = 3;
	m_TextColor = RGB(0, 0, 0);

	NONCLIENTMETRICS MyNCM;
	MyNCM.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, MyNCM.cbSize, &MyNCM, 0);

	m_LogFont = MyNCM.lfMessageFont;

	m_pFont = 0;
		try
		{
			m_pFont = new CFont;

			m_pFont->CreateFontIndirect(&m_LogFont);
		}
		catch(...)
		{
			DoDeleteEverything();
			throw;
		}
}
// End of CMashineStatusControl()


CMashineStatusControl::~CMashineStatusControl()
{
	DoDeleteEverything();
}
// End of ~CMashineStatusControl()


void CMashineStatusControl::DoDeleteEverything()
{
		if (m_pFont)
		{
			m_pFont->DeleteObject();
			delete m_pFont;
			m_pFont = 0;
		}
}
// End of DoDeleteEverything();


void CMashineStatusControl::OnPaint()
{
	CPaintDC DC(this);

	CRect ClientRect;
	GetClientRect(&ClientRect);

	DC.FillSolidRect(&ClientRect, m_BackgroundColor);
	DC.FrameRect(&ClientRect, &m_BorderBrush);

	DC.SelectObject(*m_pFont);
	DC.SetTextColor(m_TextColor);

	std::string Out;
		if (m_bFree)
			Out = "Свободен";
		else
		{
			Out = "Осталось ";
			char cBuffer[50];
				if ( (m_LastShownTime.wHour == 0) && (m_LastShownTime.wMinute == 0) )
				{
					Out += CString(_itoa(m_LastShownTime.wSecond, &(cBuffer[0]), 10))
					+ " секунд";
				}
				else
				{
					Out += CString(_itoa(m_LastShownTime.wHour, &(cBuffer[0]), 10)) + ":"
					+ CString(_itoa(m_LastShownTime.wMinute, &(cBuffer[0]), 10));
				}
		}

	CSize TextSize = DC.GetTextExtent(Out.c_str(), strlen(Out.c_str()));

	// Чтобы отцентровать текст
	signed long int dwY = ClientRect.Height() - TextSize.cy;
		if (dwY < 0)
			dwY = 0;
	dwY /= 2;

	DWORD dwTextLength = strlen(Out.c_str());

	signed long int i = dwTextLength - 3;
		for (;(i >= 0) && ((TextSize.cx + m_dwLeftSpace + 1 >
					ClientRect.Width())); --i)
		{
			Out[i] = '.';
			Out[i + 1] = '.';
			Out[i + 2] = '.';
			Out[i + 3] = '\0';

			TextSize = DC.GetTextExtent(Out.c_str(), strlen(Out.c_str()));
		}

		if (i >= 0)
			DC.TextOut(m_dwLeftSpace, dwY, Out.c_str(), strlen(Out.c_str()));
}
// End of OnPaint()


void CMashineStatusControl::CheckStatusUpdate(SYSTEMTIME* Time)
{
		if (!m_pMashineLineControl)
			return;

	// Свободна ли машина
	bool bOldFree = m_bFree;
	m_bFree = true;

	CTimeStorage _Time(Time);
	CTimeStorage FinishTime, TimeToShow;
	SYSTEMTIME SystemTimeToShow;
	CBusyIntervalsCollection::iterator End = m_pMashineLineControl->GetMashineData()->GetBusyIntervalsCollection()->GetData()->end();
		for (CBusyIntervalsCollection::iterator Iter = m_pMashineLineControl->GetMashineData()->GetBusyIntervalsCollection()->GetData()->begin();
					Iter != End; ++Iter)
		{
				if ( (*Iter)->GetCurrentInterval()->IsTimeInInterval(_Time) )
				{
					FinishTime = (*Iter)->GetCurrentInterval()->GetFinishTime();
					TimeToShow = FinishTime - _Time;
					TimeToShow.GetTime(&SystemTimeToShow);
					m_bFree = false;

							// Если что-либо изменилось:
							if ( (SystemTimeToShow.wHour != m_LastShownTime.wHour) ||
										(SystemTimeToShow.wMinute != m_LastShownTime.wMinute) ||
										((SystemTimeToShow.wHour == 0) &&
										(SystemTimeToShow.wMinute == 0) &&
										(SystemTimeToShow.wSecond != m_LastShownTime.wSecond)) )
							{
								m_LastShownTime = SystemTimeToShow;
								Invalidate();
							}
				}
		}

		if (m_bFree != bOldFree)
		{
			Invalidate();
		}
}
// End of CheckStatusUpdate
