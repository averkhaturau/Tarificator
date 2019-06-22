#if !defined(AFX_SHUTDOWNDIALOG_H__F30BFEA0_D724_421C_8964_B29830BC1F0D__INCLUDED_)
#define AFX_SHUTDOWNDIALOG_H__F30BFEA0_D724_421C_8964_B29830BC1F0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MashinesSelectionControl.h"

class CShutdownDialog : public CDialog
{
private:
	void DoDeleteEverything();
public:
	CShutdownDialog(CWnd* pParent = NULL);

	CShutdownDialog(CMashinesCollection* a_AllMashines, CMashinesCollection* a_SelectedMashines);

	virtual ~CShutdownDialog(){DoDeleteEverything();};


	CMashinesSelectionControl m_MashinesSelectionControl;
	CMashinesCollection* m_pSelectedMashines;

	//{{AFX_DATA(CShutdownDialog)
	enum { IDD = IDD_SHUTDOWN_DIALOG };
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CShutdownDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	virtual BOOL OnInitDialog();

	//{{AFX_MSG(CShutdownDialog)
	afx_msg void OnShutdown();
	afx_msg void OnReboot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUTDOWNDIALOG_H__F30BFEA0_D724_421C_8964_B29830BC1F0D__INCLUDED_)
