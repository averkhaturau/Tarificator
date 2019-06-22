// OperatorDlg.h : header file
//

#if !defined(AFX_OPERATORDLG_H__3F4EEF53_23EC_11D6_8C03_0080AD8DE6D2__INCLUDED_)
#define AFX_OPERATORDLG_H__3F4EEF53_23EC_11D6_8C03_0080AD8DE6D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COperatorDlg dialog


// Predefinition
class COperatorsCollection;

class COperatorDlg : public CDialog
{
	private:
	protected:
		HICON m_hIcon;

		COperatorsCollection* m_pOperatorsCollection;

		CComboBox* m_pOperatorsCombo;
		CEdit* m_pPasswordEdit;

		void DoIncreaseHeight(CComboBox* pBox);

		virtual void OnOK();

		virtual BOOL OnInitDialog();
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();

		DECLARE_MESSAGE_MAP()

		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	public:
		COperatorDlg(COperatorsCollection* pOperatorsCollection, CWnd* pParent = NULL);

	enum { IDD = IDD_OPERATOR_DIALOG };
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATORDLG_H__3F4EEF53_23EC_11D6_8C03_0080AD8DE6D2__INCLUDED_)
