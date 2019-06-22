#include "stdafx.h"

#include "MashineNameControl.h"


BEGIN_MESSAGE_MAP(CMashineNameControl, CWnd)
	//{{AFX_MSG_MAP(CMashineNameControl)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMashineNameControl::CMashineNameControl()
{
	m_sMashineName = "";

	NONCLIENTMETRICS MyNCM;
	MyNCM.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, MyNCM.cbSize, &MyNCM, 0);

	m_LogFont = MyNCM.lfMessageFont;

	m_TextColor = RGB(0, 0, 0);

	m_dwLeftSpace = 3;
}
// End of CMashineNameControl()


CMashineNameControl::~CMashineNameControl()
{
	m_Font.DeleteObject();
}
// End of ~CMashineNameControl()


int CMashineNameControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_Font.CreateFontIndirect(&m_LogFont);

	return 0;
}
// End of OnCreate


void CMashineNameControl::OnPaint()
{
	CPaintDC DC(this);

	CRect ClientRect;
	GetClientRect(&ClientRect);

	DC.FillSolidRect(&ClientRect, m_BackgroundColor);
	DC.FrameRect(&ClientRect, &m_BorderBrush);

	DC.SelectObject(m_Font);
	DC.SetTextColor(m_TextColor);

	std::string Out = m_sMashineName;

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
