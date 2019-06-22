// Interface.h : main header file for the INTERFACE application

#if !defined(AFX_INTERFACE_H__6948C2E2_48FD_4922_91C7_B934BB9ABC29__INCLUDED_)
#define AFX_INTERFACE_H__6948C2E2_48FD_4922_91C7_B934BB9ABC29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "..\..\Slave\Slave\ErrorsLogger.h"
#include "InterfaceDoc.h"
#include "..\DataStructures\Saving\MasterRegistryStorer.h"
#include "..\DataStructures\WindowsVersionDefiner.h"

// CInterfaceApp:
// See Interface.cpp for the implementation of this class
//

class CInterfaceApp : public CWinApp
{
public:
	CInterfaceApp();
	virtual ~CInterfaceApp();

	CErrorsLogger* GetErrorsLogger();

	CInterfaceDoc* GetActiveDoc();

	CMasterRegistryStorer* GetStorer();

	CWindowsVersionDefiner m_Definer;

	CDocTemplate* GetBusyViewDocTemplate();

	CDocTemplate* GetCashViewDocTemplate();

	CDocTemplate* GetBusyViewLXDocTemplate();

	// Обертки
	CWindowsVersionDefiner* GetDefiner() {return &m_Definer;};

	void OnFileNew();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CInterfaceApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	HANDLE m_hMutex;
	CErrorsLogger* m_pLogger;

	CMasterRegistryStorer* m_pStorer;

	afx_msg LRESULT OnConnectionAccepted(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDataReceived(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReCheckStateRequest(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnLockFail(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLockSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUnLockFail(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUnLockSuccess(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnAcknowledge(DWORD dwMessage, WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnWriteDebugMessage(WPARAM wParam, LPARAM lParam);

private:
	void DoDeleteEverything();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACE_H__6948C2E2_48FD_4922_91C7_B934BB9ABC29__INCLUDED_)
