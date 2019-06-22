#ifndef __CLIENTPAYBACKDIALOG_H__
#define __CLIENTPAYBACKDIALOG_H__

#include "resource.h"

#include "IntEdit.h"
#include "..\DataStructures\ClubSettings\BusyInterval.h"

//const UINT ClientPaybackDialogIDD = IDD_CLIENT_PAYBACK_DIALOG;


// Класс диалога, организующий интерфейс мастера с оператором для
// расчета с клиентом. Цена старого интервала берется из Price,
// а не пересчитывается во избежание всяких приколов при изменении
// тарифов.
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

		// Проверяет, не прошла ли уже минута между окончанием нового
		// интервала и текущим временем. Это есть затычка против хитро%опых
		// админов, которым не лень заниматься такой ботвой...
		bool CheckIfPaybackIsAlreadyInvalid();
		// Выключает кнопку OK, если надо. true, если выключает.
		bool DoDisableOKButtonIfNeeded();

		DECLARE_MESSAGE_MAP()
	public:
		CClientPaybackDialog();
		virtual ~CClientPaybackDialog();

		void DoCancel() {OnCancel();};

		// Проверяет, пора ли уже сделать кнопку OK выключенной.
		// Вызывается естественно по таймеру из NewIntervalDialog.
		// true, если кнопка OK уже должна быть выключена.
		bool OnTimer();

		// Обертки

		// Интервалы при этом не копируются, а записываются только
		// указатели на них, т.е. надо еще и обеспечить время жизни не
		// меньше, чем у этого диалога. Допускается NULL.
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
