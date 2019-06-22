#if !defined(AFX_TAKEOFDLG_H__0BD06293_201C_4699_A9FE_32BC8D3FD787__INCLUDED_)
#define AFX_TAKEOFDLG_H__0BD06293_201C_4699_A9FE_32BC8D3FD787__INCLUDED_


#include "..\DataStructures\ClubSettings\CashDesk.h"
#include "IntEdit.h"


class CTakeOfDlg : public CDialog
{
private:
	void DoDeleteEverything();
public:
	CTakeOfDlg(CCashdesk *pCash, const std::string &OperName, CPermission a_Permission);
	virtual ~CTakeOfDlg() {DoDeleteEverything();};

// Dialog Data
	//{{AFX_DATA(CTakeOfDlg)
	enum { IDD = IDD_TAKE_OFF_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTakeOfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DoSetTabOrder();
	CIntEdit m_LeaveMoneyEdit;
	CIntEdit m_TakenMoneyEdit;

	CButton* m_pOKButton;
	CButton* m_pCancelButton;


	virtual BOOL OnInitDialog();

	CCashdesk *m_pCashdesk;
	// Уровень разрешения оператора, который залогинился для снятия
	// кассы. Если меньше требуемого для снятия - ему можно будет
	// только посмотреть на кассу.
	CPermission m_Permission;

	std::string m_OperatorName;

	// Generated message map functions
	//{{AFX_MSG(CTakeOfDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAKEOFDLG_H__0BD06293_201C_4699_A9FE_32BC8D3FD787__INCLUDED_)
