#ifndef __NEWINTERVALDIALOG_H__
#define __NEWINTERVALDIALOG_H__

#include "resource.h"

#include "..\DataStructures\ClubSettings\TimeStorage.h"
#include "IntEdit.h"
#include "..\DataStructures\ClubSettings\ClubState.h"
#include "..\DataStructures\ClubSettings\ColoredInterval.h"
#include "..\DataStructures\ClubSettings\ColoredIntervalsCollection.h"
#include "ClientPaybackDialog.h"
#include "..\DataStructures\Saving\MasterRegistryStorer.h"
#include "..\DataStructures\FinantialHistoryLogger.h"
#include "MashinesSelectionControl.h"


const UINT IDD = IDD_NEW_INTERVAL_DIALOG;


// Predefinitions
class CBusyView;


// ���������� �������
class CDialogState
{
	private:
	protected:
		// ������� � ComboBox'��
		DWORD m_dwOperatorIndex;
		DWORD m_dwMashineIndex;
		DWORD m_dwTarifPlanIndex;
	public:
		CDialogState()
		{
			m_dwOperatorIndex = 0;
			m_dwMashineIndex = 0;
			m_dwTarifPlanIndex = 0;
		};
		~CDialogState() {};

		// �������
		void SetOperatorIndex(DWORD dwNew) {m_dwOperatorIndex = dwNew;};
		DWORD GetOperatorIndex() {return m_dwOperatorIndex;};
		void SetMashineIndex(DWORD dwNew) {m_dwMashineIndex = dwNew;};
		DWORD GetMashineIndex() {return m_dwMashineIndex;};
		void SetTarifPlanIndex(DWORD dwNew) {m_dwTarifPlanIndex = dwNew;};
		DWORD GetTarifPlanIndex() {return m_dwTarifPlanIndex;};
};


// ��������� ����������� ��������� IntervalCombo � TarifCombo
// (ComboState)
const DWORD csDefault = 0;
const DWORD csFrom_m_DialogState = 1;
const DWORD csDontChange = 2;

// ��������� ������ �������� � m_pActionCombo � CNewIntervalDialog
const int iNewInterval = 0;
const int iEditInterval = 1;

class CNewIntervalDialog : public CDialog
{
	private:
		void DoDeleteEverything();
	protected:
		// ������ ��� ����������� �������������. � ���� �����������
		// ��������� ��������.
		CClubState* m_pState;

		// ��������� �� � ������������, � ��� ������������� �������������,
		// �.�. � OnOK. ��� �� � ���������.
		CClientPaybackDialog* m_pPaybackDialog;

		CFinantialHistoryLogger* m_pFinantialLogger;

		CIntervalsStorage<CInterval>* m_pFreeIntervals;

		CDialogState* m_pDialogState;

		CFont* m_pFont;

		CDateTimeCtrl* m_pFromTime;
		CDateTimeCtrl* m_pLengthTime;
		CIntEdit* m_pLengthMoney;
		// �� �� �e������ Create, � ������ GetDlgItem
		CComboBox* m_pActionCombo;
		CComboBox* m_pIntervalChoiceCombo;
		CComboBox* m_pMashineCombo;
		CComboBox* m_pTarifCombo;
		CButton* m_pFromTimeCurrentRadio;
		CButton* m_pFromTimeAsSoonAsRadio;
		CButton* m_pFromTimeTimeRadio;
		CButton* m_pLengthTimeRadio;
		CButton* m_pLengthMoneyRadio;
		CButton* m_pStopRightNow;
		CEdit* m_pClientNameEdit;
		CStatic* m_pTotalStatic;
		CStatic* m_pAdditionalTotalStatic;
		CStatic* m_pOldOperatorStatic;
		CMashinesSelectionControl* m_pMashinesSelection;

		// ������ ��������� ��������� � ����� ��������� �������
		// ����������
		CColoredInterval* m_pPreviouslySelected;
		// ��� ��������� ��������� ����������
		CColoredIntervalsCollection* m_pHighlightedColoredCollection;

		// ��������� �� View. �����, ����� ���������� ����������� � �.�..
		CBusyView* m_pView;

		// ��������� � ComboBox ���� � ���������
		void DoAddBusyIntervalToCombo(CBusyInterval* pInterval, DWORD dwNumber);
		void DoAddFreeIntervalToCombo(CInterval* pInterval, DWORD dwNumber);

		void DoCheckFromTimeCurrent();
		void DoCheckFromTimeAsSoonAs();
		void DoCheckFromTimeTime();
		void DoCheckLengthMoney();
		void DoCheckLengthTime();

		void DoFillActionCombo();
		void DoFillMashineCombo();
		void DoFillIntervalCombo(DWORD dwRememberState = csDefault);
		void DoFillTarifCombo(DWORD dwRememberState = csDefault);
		void DoSetTabOrders();
		// �������� ��� ��������, ����� ActionCombo. ����������
		// �� OnInitDialog().
		void DoDisableControls();
		// �������� FromTime � Length Radio Button'� � ���, ��� � ����
		// �������
		void DoDisableFromTimeLengthControls();
		void DoFillFreeIntervals(CTarifPlan* pPlan, CMashineData* pMashine);
		// ���������� �� ClientNameKillFocus � �� OnDTNotify
		void DoRecalcLengthByPrice();

		// ���������� ������������ �������� ��� ������������ ������
		// FreeIntervals
		void DoCalcMaxInterval(CInterval* pReqInterval, CTarifPlan* pPlan);
		// ���������� ������������ �������� ��� ���������� �
		// ComboBox ���������
		void DoGetMaxInterval(CInterval* pMaxInterval);

		// ������� ��������� � ���������� ���������
		void DoUnHighlightInterval();

		virtual BOOL OnInitDialog();

		afx_msg void OnActionComboSelectionChange();
		afx_msg void OnIntervalChoiceComboSelectionChange();
		afx_msg void OnMashineComboSelectionChange();
		afx_msg void OnTarifComboSelectionChange();

		afx_msg void OnFromTimeCurrentClick();
		afx_msg void OnFromTimeAsSoonAsClick();
		afx_msg void OnFromTimeTimeClick();

		afx_msg void OnLengthMoneyClick();
		afx_msg void OnLengthTimeClick();
		afx_msg void OnStopRightNowClick();

		// ���� ClientName Edit ������ �����. �����, ����� �����������
		// Total.
		afx_msg void ClientNameKillFocus();
		// ���� LengthMoney Edit ������ �����
		afx_msg void LengthMoneyKillFocus();

		// �� DateTimeNotify
		afx_msg void OnDTNotify(NMHDR* pNotifyStruct, LRESULT* result);

		// ������������� Total. ���� ���������� bNormalizationRequired,
		// �� � ��������� ��� ����������� MaxInterval.
		void DoRecalcTotal(bool bNormalizationRequired = 0);
		// ���������� �������������� ��������. �� ��������� ���
		// ����, �.�. ������ ��� ����� ������������, �����
		// �� ����� �� ������� ��������� �����.
		void DoGetEnteredInterval(CBusyInterval* pInterval);

		// ����� ��������� ����� ��������� � ���������� ����
		void DoIncreaseHeight(CComboBox* pBox);

		virtual void OnOK();
		virtual void OnCancel();

		DECLARE_MESSAGE_MAP()
	public:
		// �����������
		CNewIntervalDialog(CDialogState* pDialogState, CMasterRegistryStorer* pStorer,
					CClubState* pState);
		// ����������
		virtual ~CNewIntervalDialog();

		// ���������� �� CInterfaceDoc
		void OnTimer();

		// ���������� ����� ��� � ������ ������� ����
		CTimeContainer GetFromTime();

		virtual int DoModal();

		void DoCancel() {OnCancel();};
};


#endif // __NEWINTERVALDIALOG_H__