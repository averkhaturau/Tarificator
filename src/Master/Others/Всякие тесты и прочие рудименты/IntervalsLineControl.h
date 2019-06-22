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
	// MashineLineControl, ������� �������� ���� �������
	CMashineLineControl* m_pMashineLineControl;

	//{{AFX_MSG(CIntervalsLineControl )
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	// ����������� �� ���������
	CIntervalsLineControl();
	// ����������
	virtual ~CIntervalsLineControl();

	void SetMashineLineControl(CMashineLineControl* pNew) {m_pMashineLineControl = pNew;};
	CMashineLineControl* GetMashineLineControl() {return m_pMashineLineControl;};
};


#endif // __INTERVALSLINECONTROL_H__