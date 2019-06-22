#if !defined(AFX_DOUBLEEDIT_H__49CDB961_BEEE_11D4_8C02_942FB9EB3411__INCLUDED_)
#define AFX_DOUBLEEDIT_H__49CDB961_BEEE_11D4_8C02_942FB9EB3411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Это уже не DoubleEdit. У него нельзя вводить точку, е. Воспринимает
// введенные строки только до 9 символов длиной включительно. 
class CIntEdit : public CEdit
{
private:
protected:
	//{{AFX_MSG(CIntEdit)
	/* Вызывается при нажатии клавиши. Запрещает вводить что-либо,
	кроме цифр, точки и служебных клавиш. */
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	CIntEdit();

	virtual ~CIntEdit();

	/* Преобразовывает введенную строку в m_EnteredNumber,
	и одновременно возвращает его. */
	virtual DWORD Convert();

	// Преобразует Data в строку и закидывает ее в Edit
	virtual void FillEdit(DWORD Data);

	//{{AFX_VIRTUAL(CIntEdit)
	//}}AFX_VIRTUAL
};


//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DOUBLEEDIT_H__49CDB961_BEEE_11D4_8C02_942FB9EB3411__INCLUDED_)
