
#include "StdAfx.h"

#include "IntervalsCell.h"
#include "AdditionalResource.h"



IMPLEMENT_DYNCREATE(CIntervalsCell, CGridCell)


CIntervalsCell::CIntervalsCell()
{
}

CIntervalsCell::~CIntervalsCell()
{
}


BOOL CIntervalsCell::Draw(CDC* pDC, int nRow, int nCol, CRect rect,  BOOL bEraseBkgnd /*=TRUE*/)
{
	//CGridCell::Draw(pDC, nRow, nCol, rect, FALSE);
	if (!m_IntervalsLine.m_hWnd)
	{
		// ¬ ID записываетс€ упакованные номер строки и столба, чтобы
		// разбиратьс€, на какую именно кнопку нажали.
		m_IntervalsLine.CreateEx(
					0, // Ex window Style
					cIntervalsLineControlClassName, // »м€ зарегистрированного класса контрола
					"", // Window Name
					WS_CHILD | WS_VISIBLE, //Styles
					rect,
					(CWnd*)GetGrid(), // Parent
					dwINTERVALSLINE_ID+nRow // ID
		);
	}

	if (m_IntervalsLine.m_hWnd)
	{
		m_IntervalsLine.MoveWindow(&rect);
		m_IntervalsLine.Invalidate();
	}

	return TRUE;
}
// End of Draw
