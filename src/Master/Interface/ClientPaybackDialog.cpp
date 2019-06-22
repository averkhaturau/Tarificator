#include "stdafx.h"

#include "ClientPaybackDialog.h"
#include "..\..\Slave\Slave\Exceptions.h"
#include "AdditionalResource.h"
#include "Interface.h"

#include <string>


BEGIN_MESSAGE_MAP(CClientPaybackDialog, CDialog)
	//{{AFX_MSG_MAP(CClientPaybackDialog)
	ON_EN_CHANGE(IDC_MONEY_EDIT_IN_CLIENT_PAYBACK, OnMoneyEditChange)
	//ON_BN_CLICKED(IDC_PAYBACK_ENDED_CHECK, OnPaybackEndedClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CClientPaybackDialog::CClientPaybackDialog() : CDialog(IDD_CLIENT_PAYBACK_DIALOG)
{
	m_pOldPriceStatic = 0;
	m_pNewPriceStatic = 0;
	m_pSumStatic = 0;
	m_pChangeStatic = 0;
}
// End of CClientPaybackDialog()


CClientPaybackDialog::~CClientPaybackDialog()
{

}
// End of ~CClientPaybackDialog()


BOOL CClientPaybackDialog::OnInitDialog()
{
		try
		{
			CDialog::OnInitDialog();

				if ( !(m_pOldPriceStatic = (CStatic*)GetDlgItem(IDC_OLD_PRICE_STATIC)) )
					throw CAnyLogableException("Can't get OldPriceStatic from ClientPaybackDialog", bDoNotWriteDuplicates);
				if ( !(m_pNewPriceStatic = (CStatic*)GetDlgItem(IDC_NEW_PRICE_STATIC)) )
					throw CAnyLogableException("Can't get NewPriceStatic from ClientPaybackDialog", bDoNotWriteDuplicates);
				if ( !(m_pSumStatic = (CStatic*)GetDlgItem(IDC_SUM_STATIC)) )
					throw CAnyLogableException("Can't get SumStatic from ClientPaybackDialog", bDoNotWriteDuplicates);
				if ( !(m_pChangeStatic = (CStatic*)GetDlgItem(IDC_CHANGE_STATIC)) )
					throw CAnyLogableException("Can't get ChangeStatic from ClientPaybackDialog", bDoNotWriteDuplicates);
				/*if ( !(m_pPaybackEnded = (CButton*)GetDlgItem(IDC_PAYBACK_ENDED_CHECK)) )
					throw CAnyLogableException("Can't get PaybackEnded from ClientPaybackDialog", bDoNotWriteDuplicates);*/
				if ( !(m_pOKButton = (CButton*)GetDlgItem(IDOK)) )
					throw CAnyLogableException("Can't get OK button from ClientPaybackDialog", bDoNotWriteDuplicates);
				if ( !(m_pCancelButton = (CButton*)GetDlgItem(IDCANCEL)) )
					throw CAnyLogableException("Can't get Cancel button from ClientPaybackDialog", bDoNotWriteDuplicates);

			CStatic* pClientMoneyStatic = 0;
				if ( !(pClientMoneyStatic = (CStatic*)GetDlgItem(IDC_CLIENT_MONEY_STATIC)) )
					throw CAnyLogableException("Can't get ClientMoneyStatic from ClientPaybackDialog", bDoNotWriteDuplicates);

			CRect Rect;
			CRect StaticRect;
			pClientMoneyStatic->GetWindowRect(&StaticRect);
			ScreenToClient(&StaticRect);
			Rect.top = StaticRect.top;
			Rect.bottom = StaticRect.bottom;

			m_pSumStatic->GetWindowRect(&StaticRect);
			ScreenToClient(&StaticRect);
			Rect.left = StaticRect.left;
			Rect.right = StaticRect.right;

			m_MoneyEdit.CreateEx(
						WS_EX_CLIENTEDGE, // Styles
						"EDIT", // Control class name
						"0", // Window name
						ES_RIGHT | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER, //Styles
						Rect, // Rect
						this, // Parent
						IDC_MONEY_EDIT_IN_CLIENT_PAYBACK);

			char cBuffer[100];
			std::string Price;

			CCurrency OldPrice = 0, NewPrice = 0;

				if (m_pOldBusyInterval)
				{
					OldPrice = m_pOldBusyInterval->GetPrice();
				}
			Price = _itoa(OldPrice, &(cBuffer[0]), 10);
			m_pOldPriceStatic->SetWindowText(Price.c_str());

				if (m_pNewBusyInterval)
				{
					NewPrice = m_pNewBusyInterval->GetPrice();
				}
			Price = _itoa(NewPrice, &(cBuffer[0]), 10);
			m_pNewPriceStatic->SetWindowText(Price.c_str());

			Price = _itoa(NewPrice - OldPrice, &(cBuffer[0]), 10);
			m_pSumStatic->SetWindowText(Price.c_str());

			DoSetTabOrders();
		}
		catch(CAnyLogableException &Error)
		{
			// Тут нельзя делать throw, т.к. исключения в OnInitDialog
			// не ловятся и получается хрен знает что
			//throw CAnyLogableException((std::string)"An error occured in CClientPaybackDialog::CClientPaybackDialog: " + Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(std::exception &Error)
		{
			//throw CAnyLogableException((std::string)"An error occured in CClientPaybackDialog::CClientPaybackDialog: " + Error.what(), bDoNotWriteDuplicates);
		}
		catch(...)
		{
			//throw CAnyLogableException("An unknown error occured in CClientPaybackDialog::CClientPaybackDialog: ", bDoNotWriteDuplicates);
		}

	return TRUE;
}
// End of OnInitDialog()


void CClientPaybackDialog::OnMoneyEditChange()
{
	CCurrency OldPrice = 0, NewPrice = 0;

		if (m_pOldBusyInterval)
		{
			OldPrice = m_pOldBusyInterval->GetPrice();
		}

		if (m_pNewBusyInterval)
		{
			NewPrice = m_pNewBusyInterval->GetPrice();
		}

	CCurrency ClientGot = m_MoneyEdit.Convert();

	CCurrency Change = ClientGot - (NewPrice - OldPrice);

	char cBuffer[100];
	std::string String;

		if ( (((NewPrice - OldPrice) >= 0) && (Change >= 0)) ||
					(((NewPrice - OldPrice) < 0) && (Change <= 0)) )
		{
			String = _itoa(Change, &(cBuffer[0]), 10);
				if (!OnTimer())
					m_pOKButton->EnableWindow(true);
			//m_pPaybackEnded->EnableWindow(true);
		}
		else
		{
			String = "";
			m_pOKButton->EnableWindow(false);
			//m_pPaybackEnded->EnableWindow(false);
		}

	m_pChangeStatic->SetWindowText(String.c_str());
}
// End of OnMoneyEditChange()


/*void CClientPaybackDialog::OnPaybackEndedClick()
{
		if ( (m_pPaybackEnded->GetCheck()) && (!CheckIfPaybackIsAlreadyInvalid()))
		{
			m_pOKButton->EnableWindow(true);
		}
		else
		{
			m_pOKButton->EnableWindow(false);
		}
}*/
// End of OnPaybackEndedClick()


void CClientPaybackDialog::DoSetTabOrders()
{
	// Этот кошмар - для установки Tab Order'ов

	CRect WindowRect;

	m_MoneyEdit.GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_MoneyEdit.SetWindowPos(&wndTop, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	/*m_pPaybackEnded->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pPaybackEnded->SetWindowPos(&m_MoneyEdit, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);*/

	m_pOKButton->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pOKButton->SetWindowPos(&m_MoneyEdit, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pCancelButton->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pCancelButton->SetWindowPos(m_pOKButton, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);
}
// End of DoSetTabOrders()

void CClientPaybackDialog::OnOK()
{
	char cBuf[100];
		CCurrency OldPrice = 0, NewPrice = 0;

		if (m_pOldBusyInterval)
		{
			OldPrice = m_pOldBusyInterval->GetPrice();
		}

		if (m_pNewBusyInterval)
		{
			NewPrice = m_pNewBusyInterval->GetPrice();
		}


	std::string sText = m_pOldBusyInterval!=0?(std::string)"Отредактирован интервал":(std::string)"Создан интервал";
	sText += " оператором " +
		((CInterfaceApp*)AfxGetApp())->GetActiveDoc()->
		GetMasterManager()->GetClubState()->
			GetOperatorsCollection()->operator [](
				((CInterfaceApp*)AfxGetApp())->GetActiveDoc()->m_PasswordDialogState.GetOperatorNumber()).GetName();

	((CInterfaceApp*)AfxGetApp())->GetActiveDoc()->
		GetMasterManager()->GetCash()->
		AddSum((NewPrice - OldPrice), sText.c_str(), m_pNewBusyInterval->GetCreationTime());

		if ( !OnTimer() )
			CDialog::OnOK();
}
// End of OnOK


bool CClientPaybackDialog::CheckIfPaybackIsAlreadyInvalid()
{
	CTimeStorage CurrTime = CurrentTime();

	return (CurrTime > m_pNewBusyInterval->GetFinishTime()) &&
					((CurrTime - m_pNewBusyInterval->GetFinishTime()) > A_Minute);
}
// End of CheckIfPaybackIsAlreadyInvalid()


bool CClientPaybackDialog::OnTimer()
{
	return DoDisableOKButtonIfNeeded();
}
// End of OnTimer()


bool CClientPaybackDialog::DoDisableOKButtonIfNeeded()
{
	bool bValueToReturn = CheckIfPaybackIsAlreadyInvalid();
		if ( bValueToReturn )
		{
			m_pOKButton->EnableWindow(false);
		}

	return bValueToReturn;
}
