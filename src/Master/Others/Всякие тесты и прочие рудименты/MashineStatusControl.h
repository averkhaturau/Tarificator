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
	// ������ ����� �� ������ � ��������
	DWORD m_dwLeftSpace;
	// ��������� ������. ����� �������� ����� ������.
	LOGFONT m_LogFont;
	CFont* m_pFont;
	// �������� �� ������. ����������� � CheckStatusUpdate
	bool m_bFree;
	// ��������������� �������
	CMashineLineControl* m_pMashineLineControl;
	// ��� ������������, ���� �� �������������� Control
	SYSTEMTIME m_LastShownTime;
	// ���� ������
	COLORREF m_TextColor;

	// ���������� �� ������� �� BusyView. ���������, ���� ��
	// ������������ ������� ��-�� ������������� ���������.
	void CheckStatusUpdate(SYSTEMTIME* Time);

	DECLARE_MESSAGE_MAP()
public:
	// �����������
	CMashineStatusControl();
	// ����������
	virtual ~CMashineStatusControl();

	//{{AFX_MSG(CMashineStatusControl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	// �������
	void SetMashineLineControl(CMashineLineControl* pNew) {m_pMashineLineControl = pNew;};
	LOGFONT* GetLogFont() {return &m_LogFont;};
	CMashineLineControl* GetMashineLineControl() {return m_pMashineLineControl;};
	void SetLeftSpace(DWORD dwNew) {m_dwLeftSpace = dwNew;};
	DWORD GetLeftSpace() {return m_dwLeftSpace;};
	void SetTextColor(COLORREF New) {m_TextColor = New;};
	COLORREF GetTextColor() {return m_TextColor;};
};


#endif // __MASHINESTATUSCONTROL_H__