#if !defined(AFX_PSWRDDIALOG_H__58F696CD_2562_4F79_B980_9881D2325658__INCLUDED_)
#define AFX_PSWRDDIALOG_H__58F696CD_2562_4F79_B980_9881D2325658__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PswrdDialog.h : header file
//

#include "string"


class CPasswordDialogState
{
	private:
	protected:
		int m_iOperatorNumber;
	public:
		CPasswordDialogState() {m_iOperatorNumber = 0;bIsLogged=false;};

		// Обертки
		inline void SetOperatorNumber(int iNew) {m_iOperatorNumber = iNew;};
		inline int GetOperatorNumber() {return m_iOperatorNumber;};

		inline bool IsLogged() const {return bIsLogged;};
		inline void SetLogged(const bool& a_bLogged)
			{ bIsLogged = a_bLogged; };
	// for log off
	protected:
		bool bIsLogged;
};

class CPswrdDialog : public CDialog
{
	protected:
		CComboBox* m_pOperatorCombo;
		CClubState* m_pClubState;
		CEdit* m_pPswrdEdit;
		CPasswordDialogState* m_pDialogState;
		CPermission m_Permission;

		void DoIncreaseHeight(CComboBox* pBox);

		//{{AFX_MSG(CPswrdDialog)
		virtual void OnOK();
		afx_msg void OnOperatorComboSelectionChange();
		//}}AFX_MSG

		DECLARE_MESSAGE_MAP()

	public:
		CPswrdDialog(CWnd* pParent, CClubState* pState, CPasswordDialogState* pDialogState, const CPermission &a_Permission);

		virtual BOOL OnInitDialog();

		//{{AFX_DATA(CPswrdDialog)
		enum { IDD = IDD_PSWRD_DIALOG };
		//}}AFX_DATA

		//{{AFX_VIRTUAL(CPswrdDialog)
		public:
		protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		//}}AFX_VIRTUAL
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSWRDDIALOG_H__58F696CD_2562_4F79_B980_9881D2325658__INCLUDED_)
