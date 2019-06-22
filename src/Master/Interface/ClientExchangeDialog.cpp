#include "stdafx.h"

#include "ClientExchangeDialog.h"
#include "..\..\Slave\Slave\Exceptions.h"
#include "Interface.h"


BEGIN_MESSAGE_MAP(CClientExchangeDialog, CDialog)
END_MESSAGE_MAP()


CClientExchangeDialog::CClientExchangeDialog(CBusyInterval* pOldInterval,
			CBusyInterval* pNewInterval, CWnd* pWnd)
			: CDialog(IDD_CLIENT_EXCHANGE_DIALOG, pWnd)
{
	m_pOldClientStatic = 0;
	m_pNewClientStatic = 0;

		if (pOldInterval)
			m_OldInterval = *pOldInterval;
		if (pNewInterval)
			m_NewInterval = *pNewInterval;
}
// End of CClientExchangeDialog()


CClientExchangeDialog::~CClientExchangeDialog()
{

}
// End of ~CClientExchangeDialog()


BOOL CClientExchangeDialog::OnInitDialog()
{
		try
		{
			CDialog::OnInitDialog();

				if ( !(m_pOldClientStatic = (CStatic*)GetDlgItem(IDC_OLD_CLIENT_STATIC)) )
					throw CAnyLogableException("Can't get OldClientStatic from ClientExchangeDialog", bDoNotWriteDuplicates);
				if ( !(m_pNewClientStatic = (CStatic*)GetDlgItem(IDC_NEW_CLIENT_STATIC)) )
					throw CAnyLogableException("Can't get OldClientStatic from ClientExchangeDialog", bDoNotWriteDuplicates);

			std::string Str = "Закончилось время у клиента ";
			Str += m_OldInterval.GetClientName();
			m_pOldClientStatic->SetWindowText(Str.c_str());

			Str = "Началось время клиента ";
			Str += m_NewInterval.GetClientName();
			m_pNewClientStatic->SetWindowText(Str.c_str());
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


void CClientExchangeDialog::OnOK()
{
		if ( ((CInterfaceApp*)AfxGetApp())->GetActiveDoc()->DoOperatorAuthentication() )
			CDialog::OnOK();
}
// End of OnOK();
