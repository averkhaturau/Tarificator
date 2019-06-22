#ifndef __CLIENTPAYBACKDIALOG_H__
#define __CLIENTPAYBACKDIALOG_H__

#include "resource.h"

#include "IntEdit.h"
#include "..\DataStructures\ClubSettings\BusyInterval.h"

//const UINT ClientPaybackDialogIDD = IDD_CLIENT_PAYBACK_DIALOG;


// ����� �������, ������������ ��������� ������� � ���������� ���
// ������� � ��������. ���� ������� ��������� ������� �� Price,
// � �� ��������������� �� ��������� ������ �������� ��� ���������
// �������.
class CClientPaybackDialog : public CDialog
{
	private:
	protected:
		CStatic* m_pOldPriceStatic;
		CStatic* m_pNewPriceStatic;
		CStatic* m_pSumStatic;
		CStatic* m_pChangeStatic;

		CIntEdit m_MoneyEdit;

		//CButton* m_pPaybackEnded;
		CButton* m_pOKButton;
		CButton* m_pCancelButton;

		virtual BOOL OnInitDialog();

		CBusyInterval* m_pOldBusyInterval;
		CBusyInterval* m_pNewBusyInterval;

		//{{AFX_MSG(CClientPaybackDialog)
		afx_msg void OnMoneyEditChange();
		//afx_msg void OnPaybackEndedClick();
		//}}AFX_MSG
		void DoSetTabOrders();

		virtual void OnOK();

		// ���������, �� ������ �� ��� ������ ����� ���������� ������
		// ��������� � ������� ��������. ��� ���� ������� ������ �����%����
		// �������, ������� �� ���� ���������� ����� ������...
		bool CheckIfPaybackIsAlreadyInvalid();
		// ��������� ������ OK, ���� ����. true, ���� ���������.
		bool DoDisableOKButtonIfNeeded();

		DECLARE_MESSAGE_MAP()
	public:
		CClientPaybackDialog();
		virtual ~CClientPaybackDialog();

		void DoCancel() {OnCancel();};

		// ���������, ���� �� ��� ������� ������ OK �����������.
		// ���������� ����������� �� ������� �� NewIntervalDialog.
		// true, ���� ������ OK ��� ������ ���� ���������.
		bool OnTimer();

		// �������

		// ��������� ��� ���� �� ����������, � ������������ ������
		// ��������� �� ���, �.�. ���� ��� � ���������� ����� ����� ��
		// ������, ��� � ����� �������. ����������� NULL.
		void SetOldBusyInterval(CBusyInterval* pNew) {m_pOldBusyInterval = pNew;};
		CBusyInterval* GetOldBusyInterval() {return m_pOldBusyInterval;};
		void SetNewBusyInterval(CBusyInterval* pNew) {m_pNewBusyInterval = pNew;};
		CBusyInterval* GetNewBusyInterval() {return m_pNewBusyInterval;};

		//{{AFX_DATA(CTakeOfDlg)
			enum { IDD = IDD_CLIENT_PAYBACK_DIALOG };
		// NOTE: the ClassWizard will add data members here
		//}}AFX_DATA

};


#endif // __CLIENTPAYBACKDIALOG_H__
