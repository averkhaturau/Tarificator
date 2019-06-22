// OperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operators.h"
#include "OperatorDlg.h"

#include "..\DataStructures\ClubSettings\OperatorsCollection.h"
#include "..\..\Slave\Slave\Exceptions.h"
#include "..\DataStructures\Cryptography\Hasher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// COperatorDlg dialog

COperatorDlg::COperatorDlg(COperatorsCollection* pOperatorsCollection,
			CWnd* pParent)
	: CDialog(COperatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COperatorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pOperatorsCollection = pOperatorsCollection;
}

void COperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperatorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COperatorDlg, CDialog)
	//{{AFX_MSG_MAP(COperatorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// COperatorDlg message handlers

BOOL COperatorDlg::OnInitDialog()
{
	try{
		CDialog::OnInitDialog();

		SetIcon(m_hIcon, TRUE);
		SetIcon(m_hIcon, FALSE);

		m_pOperatorsCombo = 0;
		m_pPasswordEdit = 0;

		try
		{
			m_pOperatorsCombo = (CComboBox*)GetDlgItem(IDC_OPERATOR_COMBO);
			m_pPasswordEdit = (CEdit*)GetDlgItem(IDC_PSWRD_EDIT);

				if ( !(m_pOperatorsCombo && m_pPasswordEdit) )
					throw CAnyLogableException("can't get dialog item 8-/", bDoNotWriteDuplicates);

			m_pPasswordEdit->SetWindowText("");

				if (m_pOperatorsCollection)
				{
					int iIndex = 0, i = 0;
					COperatorsCollection::iterator Iter = m_pOperatorsCollection->GetData()->begin(),
								EndIter = m_pOperatorsCollection->GetData()->end();
						for (; Iter < EndIter; ++Iter, ++i)
						{
							iIndex = m_pOperatorsCombo->AddString((*Iter)->GetName().c_str());
							m_pOperatorsCombo->SetItemData(iIndex, i);
						}

						if (m_pOperatorsCombo->GetCount() >= 1)
							m_pOperatorsCombo->SetCurSel(0);
				}

			DoIncreaseHeight(m_pOperatorsCombo);

			m_pOperatorsCombo->SetFocus();
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException((std::string)"An error occured in COperatorDlg::OnInitDialog():\n" + Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in COperatorDlg::OnInitDialog()", bDoNotWriteDuplicates);
		}

		return false;
	}catch(CAnyLogableException &e){
		MessageBox(std::string(
			(std::string)"Возникла ошибка:\n" + (std::string)e.what()).c_str(),
			"Извините, произошла досадная ошибка", MB_ICONERROR);
		return true;
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COperatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR COperatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void COperatorDlg::DoIncreaseHeight(CComboBox* pBox)
{
		if (!pBox)
			return;

	CRect Rect;
	pBox->GetDroppedControlRect(&Rect);
	ScreenToClient(&Rect);
	Rect.bottom += 100;
	pBox->MoveWindow(&Rect);
}
// End of DoIncreaseHeight


void COperatorDlg::OnOK()
{
	COperator* pSelectedOperator = 0;
	if (m_pOperatorsCombo->GetCurSel() != CB_ERR)
	{
		pSelectedOperator = &((*m_pOperatorsCollection)[m_pOperatorsCombo->GetItemData(m_pOperatorsCombo->GetCurSel())]);
	}

	// Тут надо вставить реальное вычисление и изменение password hash
	// выбранного оператора
	if (pSelectedOperator)
	{
		CString _Str;
		m_pPasswordEdit->GetWindowText(_Str);
		pSelectedOperator->SetPasswordHash(CHasher::Str2i64(
			(std::string)_Str +
			(std::string)pSelectedOperator->GetName()
		));
	}

	CDialog::OnOK();
}
// End of OnOK()
