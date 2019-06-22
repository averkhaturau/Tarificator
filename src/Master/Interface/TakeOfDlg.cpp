// TakeOfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "TakeOfDlg.h"
#include "AdditionalResource.h"
#include "..\DataStructures\ClubSettings\Cashdesk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CTakeOfDlg::CTakeOfDlg(CCashdesk *pCash, const std::string &OperName, CPermission a_Permission)
	: CDialog(CTakeOfDlg::IDD)
{
	m_pCashdesk = pCash;
	m_OperatorName = OperName;
	m_Permission = a_Permission;
	//{{AFX_DATA_INIT(CTakeOfDlg)
	//}}AFX_DATA_INIT
}

void CTakeOfDlg::DoDeleteEverything()
{
}


void CTakeOfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTakeOfDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTakeOfDlg, CDialog)
	//{{AFX_MSG_MAP(CTakeOfDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CTakeOfDlg::OnInitDialog()
{
	try
	{
		char cBuf[250];
		CDialog::OnInitDialog();

		CStatic *MyStatic1 = (CStatic*)GetDlgItem(IDC_STATIC_CL1);
		CStatic *MyStatic2 = (CStatic*)GetDlgItem(IDC_STATIC_CL2);

		m_pOKButton = (CButton*)GetDlgItem(IDOK);
		m_pCancelButton = (CButton*)GetDlgItem(IDCANCEL);

		CRect Rect1, Rect2;
		MyStatic1->GetWindowRect(&Rect1);
		ScreenToClient(&Rect1);
		MyStatic2->GetWindowRect(&Rect2);
		ScreenToClient(&Rect2);

		m_LeaveMoneyEdit.CreateEx(
					WS_EX_CLIENTEDGE, // Styles
					"EDIT", // Control class name
					_itoa(m_pCashdesk->GetSum(), cBuf, 10), // Window name
					ES_READONLY | ES_RIGHT | ES_AUTOHSCROLL | /*WS_TABSTOP |*/ WS_CHILD | WS_VISIBLE | WS_BORDER, //Styles
					Rect1, // Rect
					this,// Parent
					IDC_MONEY_EDIT1_IN_TAKEOFF);

		m_TakenMoneyEdit.CreateEx(
					WS_EX_CLIENTEDGE, // Styles
					"EDIT", // Control class name
					_itoa(m_pCashdesk->GetSum(), cBuf, 10),
					ES_RIGHT | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER, //Styles
					Rect2, // Rect
					this,//Parent
					IDC_MONEY_EDIT2_IN_TAKEOFF);

			if ( m_Permission < m_pCashdesk->GetPermission() )
			{
				m_TakenMoneyEdit.EnableWindow(false);
				m_TakenMoneyEdit.SetWindowText("0");
				m_pOKButton->EnableWindow(false);
			}

		//DoSetTabOrder();
	}catch(...){
		return FALSE;
	}

	return TRUE;
}

void CTakeOfDlg::OnOK() 
{
		if ( m_Permission < m_pCashdesk->GetPermission() )
			return;

	bool bIsPossibleOperation = true;
	try{
		m_pCashdesk->AddSum(-m_TakenMoneyEdit.Convert(), std::string((std::string)"Забрано из кассы оператором "+m_OperatorName).c_str(), CurrentTime());
	}catch(std::logic_error &e){
		bIsPossibleOperation = false;
		MessageBox(e.what(), "Tarificator", MB_ICONEXCLAMATION);
	}

	if (bIsPossibleOperation)
		CDialog::OnOK();
}

void CTakeOfDlg::DoSetTabOrder()
{
	CRect WindowRect;

/*	m_LeaveMoneyEdit.GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_LeaveMoneyEdit.SetWindowPos(&wndTop, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);
*/
	m_TakenMoneyEdit.GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_TakenMoneyEdit.SetWindowPos(&m_LeaveMoneyEdit, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pOKButton->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pOKButton->SetWindowPos(&m_TakenMoneyEdit, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pCancelButton->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pCancelButton->SetWindowPos(m_pOKButton, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_TakenMoneyEdit.SetFocus();
}
