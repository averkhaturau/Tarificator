#ifndef __MASHINENAMECONTROL_H__
#define __MASHINENAMECONTROL_H__

#include <string>

#include "LineControl.h"


class CMashineNameControl : public CLineControl
{

protected:
	std::string m_sMashineName;
	// Параметры шрифта. Нужно задавать до вызова Create.
	LOGFONT m_LogFont;
	CFont m_Font;
	// Цвет текста
	COLORREF m_TextColor;
	// Отступ слева от текста в пикселах
	DWORD m_dwLeftSpace;

	//{{AFX_MSG(CMashineNameControl)
	afx_msg void OnPaint();
	// Тут создается Font
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	// Конструктор
	CMashineNameControl();
	// Деструктор
	virtual ~CMashineNameControl();

	// Обертки
	std::string* GetMashineName() {return &m_sMashineName;};
	LOGFONT* GetLogFont() {return &m_LogFont;};
	void SetLeftSpace(DWORD dwNew) {m_dwLeftSpace = dwNew;};
	DWORD GetLeftSpace() {return m_dwLeftSpace;};
	void SetTextColor(COLORREF New) {m_TextColor = New;};
	COLORREF GetTextColor() {return m_TextColor;};
};


#endif // __MASHINENAMECONTROL_H__