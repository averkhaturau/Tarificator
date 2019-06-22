#ifndef __MASHINENAMECONTROL_H__
#define __MASHINENAMECONTROL_H__

#include <string>

#include "LineControl.h"


class CMashineNameControl : public CLineControl
{

protected:
	std::string m_sMashineName;
	// ��������� ������. ����� �������� �� ������ Create.
	LOGFONT m_LogFont;
	CFont m_Font;
	// ���� ������
	COLORREF m_TextColor;
	// ������ ����� �� ������ � ��������
	DWORD m_dwLeftSpace;

	//{{AFX_MSG(CMashineNameControl)
	afx_msg void OnPaint();
	// ��� ��������� Font
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	// �����������
	CMashineNameControl();
	// ����������
	virtual ~CMashineNameControl();

	// �������
	std::string* GetMashineName() {return &m_sMashineName;};
	LOGFONT* GetLogFont() {return &m_LogFont;};
	void SetLeftSpace(DWORD dwNew) {m_dwLeftSpace = dwNew;};
	DWORD GetLeftSpace() {return m_dwLeftSpace;};
	void SetTextColor(COLORREF New) {m_TextColor = New;};
	COLORREF GetTextColor() {return m_TextColor;};
};


#endif // __MASHINENAMECONTROL_H__