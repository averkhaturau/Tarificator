#ifndef __INTERVALSLINECONTROL_H__
#define __INTERVALSLINECONTROL_H__

#include "LineControl.h"
#include "BusyView.h"
#include "IntervalsLine.h"

// Predefinitions
class CMashineLineControl;
class CBusyView;

class CIntervalsLineControl
		: public CIntervalsLine
{
protected:
	// MashineLineControl, который содержит этот контрол
	CMashineLineControl* m_pMashineLineControl;

	//{{AFX_MSG(CIntervalsLineControl )
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	// Конструктор по умолчанию
	CIntervalsLineControl();
	// Деструктор
	virtual ~CIntervalsLineControl();

	void SetMashineLineControl(CMashineLineControl* pNew) {m_pMashineLineControl = pNew;};
	CMashineLineControl* GetMashineLineControl() {return m_pMashineLineControl;};
};


#endif // __INTERVALSLINECONTROL_H__