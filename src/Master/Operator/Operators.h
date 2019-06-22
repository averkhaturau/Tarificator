// Operator.h : main header file for the OPERATOR application
//

#if !defined(AFX_OPERATOR_H__3F4EEF51_23EC_11D6_8C03_0080AD8DE6D2__INCLUDED_)
#define AFX_OPERATOR_H__3F4EEF51_23EC_11D6_8C03_0080AD8DE6D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COperatorApp:
// See Operator.cpp for the implementation of this class
//

#include "..\DataStructures\ClubSettings\OperatorsCollection.h"

class COperatorApp : public CWinApp
{
public:
	COperatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COperatorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATOR_H__3F4EEF51_23EC_11D6_8C03_0080AD8DE6D2__INCLUDED_)
