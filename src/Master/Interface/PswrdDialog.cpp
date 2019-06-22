// PswrdDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "PswrdDialog.h"
#include <string>
#include "..\DataStructures\Cryptography\Hasher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CPswrdDialog::CPswrdDialog(CWnd* pParent, CClubState* pState, CPasswordDialogState* pDialogState, const CPermission &a_Permission)
	: CDialog(CPswrdDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPswrdDialog)
	//}}AFX_DATA_INIT
	m_pPswrdEdit = 0;
	m_pOperatorCombo = 0;
	if (!pState)
		throw CAnyLogableException("NULL pState delivered to CPswrdDialog::CPswrdDialog", bDoNotWriteDuplicates);

	m_pClubState = pState;
	m_pDialogState = pDialogState;
	m_Permission = a_Permission;
}


void CPswrdDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPswrdDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPswrdDialog, CDialog)
	//{{AFX_MSG_MAP(CPswrdDialog)
	ON_CBN_SELCHANGE(IDC_OPERATOR_COMBO, OnOperatorComboSelectionChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CPswrdDialog::OnInitDialog()
{
	try
	{
		// for log on
		if (m_pDialogState->IsLogged())
			CDialog::OnOK();


		BOOL _return = CDialog::OnInitDialog();
		m_pOperatorCombo = (CComboBox*)GetDlgItem(IDC_OPERATOR_COMBO);
		m_pPswrdEdit = (CEdit*)GetDlgItem(IDC_PSWRD_EDIT);
		m_pPswrdEdit->SetWindowText("");

		DoIncreaseHeight(m_pOperatorCombo);
		m_pOperatorCombo->ResetContent();

		int ItemIndex = 0;
		int i = 0;
		COperatorsCollection::iterator End = m_pClubState->GetOperatorsCollection()->GetData()->end();
		COperatorsCollection::iterator Iter = m_pClubState->GetOperatorsCollection()->GetData()->begin();
		for (; Iter != End; ++Iter, ++i)
		{
			if ((*Iter)->GetPermission() >= m_Permission)
			{
				ItemIndex = m_pOperatorCombo->AddString( (*Iter)->GetName().c_str() );
				m_pOperatorCombo->SetItemData(ItemIndex, i);
			}
		}
		if (m_pOperatorCombo->GetCount())
				if (m_pDialogState)
						for (int i = 0; i < m_pOperatorCombo->GetCount(); ++i)
						{
								if (m_pOperatorCombo->GetItemData(i) == m_pDialogState->GetOperatorNumber())
								{
									m_pOperatorCombo->SetCurSel(i);
									break;
								}
						}
				else
					m_pOperatorCombo->SetCurSel(0);
		//((CButton*)GetDlgItem(IDC_LOGON_CHECK))->SetCheck(
		//	m_pDialogState->IsLogged());
		m_pPswrdEdit->SetFocus();

		return false;
	}
	catch(CAnyLogableException &e)
	{
		throw CAnyLogableException(
			(std::string)"CPswrdDialog::OnInitDialog failed: " +
			(std::string)e.what(), e.GetWriteDuplicatesToLog());
	}
	catch(...)
	{
		throw CAnyLogableException("CPswrdDialog::OnInitDialog failed",
			bDoNotWriteDuplicates);
	}
}// end of BOOL CPswrdDialog::OnInitDialog()

void CPswrdDialog::OnOK() 
{
	// тонка€ вещь, изменив которую можно
	// добитьса неправильной работы диалога,
	// что позволит обойти ввод парол€
	COperator* pOperator =
		&((*m_pClubState->GetOperatorsCollection())
			[m_pOperatorCombo->GetItemData(m_pOperatorCombo->GetCurSel())]);

	char _PswrdBuff[0xff];
	if (!m_pPswrdEdit)
	{
		CDialog::OnCancel();
		return;
	}

	m_pPswrdEdit->GetWindowText(_PswrdBuff, 0xff);

	// “ут должна быть проверка парол€
	if (CHasher::Str2i64((std::string)_PswrdBuff
			+ pOperator->GetName()) == pOperator->GetPasswordHash())
	{
		// ≈сли пароль набран правильно
		m_pDialogState->SetLogged(
			((CButton*)GetDlgItem(IDC_LOGON_CHECK))->GetCheck());
		CDialog::OnOK();
	}
	else
	{
		// ≈сли набран неправильно
		CDialog::OnCancel();
	}
}


void CPswrdDialog::DoIncreaseHeight(CComboBox* pBox)
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


void CPswrdDialog::OnOperatorComboSelectionChange()
{
	m_pDialogState->SetOperatorNumber(m_pOperatorCombo->GetItemData(m_pOperatorCombo->GetCurSel()));
}
// End of OnOperatorComboSelectionChange()
