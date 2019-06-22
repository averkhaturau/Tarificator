#ifndef __CLINETEXCHANGEDIALOG_H__
#define __CLINETEXCHANGEDIALOG_H__

#include "resource.h"

#include "..\DataStructures\ClubSettings\BusyInterval.h"


class CClientExchangeDialog : public CDialog
{
	private:
	protected:
		CStatic* m_pNewClientStatic;
		CStatic* m_pOldClientStatic;

		CBusyInterval m_OldInterval;
		CBusyInterval m_NewInterval;

		virtual BOOL OnInitDialog();
		virtual void OnOK();

		DECLARE_MESSAGE_MAP()
	public:
		CClientExchangeDialog(CBusyInterval* pOldInterval,
					CBusyInterval* pNewInterval, CWnd* pWnd);
		~CClientExchangeDialog();
};

#endif // __CLINETEXCHANGEDIALOG_H__