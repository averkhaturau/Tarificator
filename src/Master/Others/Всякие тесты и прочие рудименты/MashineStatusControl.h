#ifndef __MASHINESTATUSCONTROL_H__
#define __MASHINESTATUSCONTROL_H__

#include "LineControl.h"
#include "BusyView.h"


// Predefinitions
class CMashineLineControl;


class CMashineStatusControl : public CLineControl
{
	friend void CBusyView::OnCalcCurrentTimeLine();

private:
	void DoDeleteEverything();
protected:
	// Отступ слева от текста в пикселах
	DWORD m_dwLeftSpace;
	// Параметры шрифта. Можно задавать когда угодно.
	LOGFONT m_LogFont;
	CFont* m_pFont;
	// Свободна ли машина. Заполняется в CheckStatusUpdate
	bool m_bFree;
	// Ответственность снаружи
	CMashineLineControl* m_pMashineLineControl;
	// Для опеределения, надо ли перерисовывать Control
	SYSTEMTIME m_LastShownTime;
	// Цвет текста
	COLORREF m_TextColor;

	// Вызывается по таймеру из BusyView. Проверяет, надо ли
	// перерисовать контрол из-за изменившегося состояния.
	void CheckStatusUpdate(SYSTEMTIME* Time);

	DECLARE_MESSAGE_MAP()
public:
	// Конструктор
	CMashineStatusControl();
	// Деструктор
	virtual ~CMashineStatusControl();

	//{{AFX_MSG(CMashineStatusControl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	// Обертки
	void SetMashineLineControl(CMashineLineControl* pNew) {m_pMashineLineControl = pNew;};
	LOGFONT* GetLogFont() {return &m_LogFont;};
	CMashineLineControl* GetMashineLineControl() {return m_pMashineLineControl;};
	void SetLeftSpace(DWORD dwNew) {m_dwLeftSpace = dwNew;};
	DWORD GetLeftSpace() {return m_dwLeftSpace;};
	void SetTextColor(COLORREF New) {m_TextColor = New;};
	COLORREF GetTextColor() {return m_TextColor;};
};


#endif // __MASHINESTATUSCONTROL_H__