#ifndef _LX_INTERVALSCELL_H__
#define _LX_INTERVALSCELL_H__

#include "GridCtrlSource\GridCell.h"
#include "IntervalsLine.h"

class CIntervalsCell : public CGridCell
{
protected:
	CIntervalsLine m_IntervalsLine;

	DECLARE_DYNCREATE(CIntervalsCell)

public:
	CIntervalsCell();
	virtual ~CIntervalsCell();

	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

	CIntervalsLine *GetIntervalsLine() { return &m_IntervalsLine; };
};

#endif //_LX_INTERVALSCELL_H__
