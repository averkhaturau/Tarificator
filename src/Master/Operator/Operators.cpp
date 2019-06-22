// Operator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Operators.h"
#include "OperatorDlg.h"

#include "..\DataStructures\Saving\MasterRegistryStorer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// COperatorApp

BEGIN_MESSAGE_MAP(COperatorApp, CWinApp)
	//{{AFX_MSG_MAP(COperatorApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

// COperatorApp construction

COperatorApp::COperatorApp()
{
}

// The one and only COperatorApp object

COperatorApp theApp;

// COperatorApp initialization

BOOL COperatorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	try{
		CMasterRegistryStorer _Storer;
		COperatorsCollection OperatorsCollection(&_Storer);

		COperatorDlg dlg(&OperatorsCollection);
		m_pMainWnd = &dlg;

		int nResponse = dlg.DoModal();

		if (nResponse == IDOK)
		{
		// Тут надо вставить запись на место в реестр коллекции операторов
		// или одного оператора
			_Storer.SaveOperatorsChanged(&OperatorsCollection);
		}

		if (nResponse == IDCANCEL)
		{
		}

	}catch(CAnyLogableException &e){
		MessageBox(GetDesktopWindow(), //"Не существыет ни одного оператора, а программа ещё не умеет создавать новых"
			std::string((std::string)"Программа выдала исключение:\n"
			+ (std::string)e.what()).c_str(), "Извините, ошибочка вышла", MB_ICONERROR);
		return FALSE;
	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

