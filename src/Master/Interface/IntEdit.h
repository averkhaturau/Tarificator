#if !defined(AFX_DOUBLEEDIT_H__49CDB961_BEEE_11D4_8C02_942FB9EB3411__INCLUDED_)
#define AFX_DOUBLEEDIT_H__49CDB961_BEEE_11D4_8C02_942FB9EB3411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ��� ��� �� DoubleEdit. � ���� ������ ������� �����, �. ������������
// ��������� ������ ������ �� 9 �������� ������ ������������. 
class CIntEdit : public CEdit
{
private:
protected:
	//{{AFX_MSG(CIntEdit)
	/* ���������� ��� ������� �������. ��������� ������� ���-����,
	����� ����, ����� � ��������� ������. */
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	CIntEdit();

	virtual ~CIntEdit();

	/* ��������������� ��������� ������ � m_EnteredNumber,
	� ������������ ���������� ���. */
	virtual DWORD Convert();

	// ����������� Data � ������ � ���������� �� � Edit
	virtual void FillEdit(DWORD Data);

	//{{AFX_VIRTUAL(CIntEdit)
	//}}AFX_VIRTUAL
};


//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DOUBLEEDIT_H__49CDB961_BEEE_11D4_8C02_942FB9EB3411__INCLUDED_)
