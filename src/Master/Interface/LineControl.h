#if !defined(AFX_LINECONTROL_H__7EBB4C6D_F3AB_4EAF_A277_042A5EB64465__INCLUDED_)
#define AFX_LINECONTROL_H__7EBB4C6D_F3AB_4EAF_A277_042A5EB64465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\DataStructures\ClubSettings\ColoredIntervalsCollection.h"


class CLineControl : public CWnd
{
	friend class CIntervalsCell;
protected:
	// Brush, которой рисуются все разделительные линии
	CBrush m_BorderBrush;
	COLORREF m_BackgroundColor;

public:
	// Конструктор
	CLineControl();
	// Деструктор
	virtual ~CLineControl();

	// Обертки
	CBrush* GetBrush() {return &m_BorderBrush;};
	COLORREF GetBackgroundColor() {return m_BackgroundColor;};
	void SetBackgroundColor(COLORREF New) {m_BackgroundColor = New;};
};

#endif // !defined(AFX_LINECONTROL_H__7EBB4C6D_F3AB_4EAF_A277_042A5EB64465__INCLUDED_)
