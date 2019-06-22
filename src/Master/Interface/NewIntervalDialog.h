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


// Сосотояние диалога
class CDialogState
{
	private:
	protected:
		// Индексы в ComboBox'ах
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

		// Обертки
		void SetOperatorIndex(DWORD dwNew) {m_dwOperatorIndex = dwNew;};
		DWORD GetOperatorIndex() {return m_dwOperatorIndex;};
		void SetMashineIndex(DWORD dwNew) {m_dwMashineIndex = dwNew;};
		DWORD GetMashineIndex() {return m_dwMashineIndex;};
		void SetTarifPlanIndex(DWORD dwNew) {m_dwTarifPlanIndex = dwNew;};
		DWORD GetTarifPlanIndex() {return m_dwTarifPlanIndex;};
};


// Константы запоминания состояний IntervalCombo и TarifCombo
// (ComboState)
const DWORD csDefault = 0;
const DWORD csFrom_m_DialogState = 1;
const DWORD csDontChange = 2;

// Константы выбора элемента в m_pActionCombo в CNewIntervalDialog
const int iNewInterval = 0;
const int iEditInterval = 1;

class CNewIntervalDialog : public CDialog
{
	private:
		void DoDeleteEverything();
	protected:
		// Только для внутреннего использования. В него добавляется
		// созданный интервал.
		CClubState* m_pState;

		// Создается не в конструкторе, а при необходимости использования,
		// т.е. в OnOK. Там же и убивается.
		CClientPaybackDialog* m_pPaybackDialog;

		CFinantialHistoryLogger* m_pFinantialLogger;

		CIntervalsStorage<CInterval>* m_pFreeIntervals;

		CDialogState* m_pDialogState;

		CFont* m_pFont;

		CDateTimeCtrl* m_pFromTime;
		CDateTimeCtrl* m_pLengthTime;
		CIntEdit* m_pLengthMoney;
		// Им не дeлается Create, а просто GetDlgItem
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

		// Просто временное хранилище в целях подсветки занятых
		// интервалов
		CColoredInterval* m_pPreviouslySelected;
		// Для подсветки свободных интервалов
		CColoredIntervalsCollection* m_pHighlightedColoredCollection;

		// Указатель на View. Нужен, чтобы заказывать перерисовки и т.п..
		CBusyView* m_pView;

		// Добавляет в ComboBox инфу о интервале
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
		// Вырубает все контролы, кроме ActionCombo. Вызывается
		// из OnInitDialog().
		void DoDisableControls();
		// Вырубает FromTime и Length Radio Button'ы и все, что с ними
		// связано
		void DoDisableFromTimeLengthControls();
		void DoFillFreeIntervals(CTarifPlan* pPlan, CMashineData* pMashine);
		// Вызывается из ClientNameKillFocus и из OnDTNotify
		void DoRecalcLengthByPrice();

		// Возвращает максимальный интервал для последующего поиска
		// FreeIntervals
		void DoCalcMaxInterval(CInterval* pReqInterval, CTarifPlan* pPlan);
		// Возвращает максимальный интервал для выбранного в
		// ComboBox интервала
		void DoGetMaxInterval(CInterval* pMaxInterval);

		// Снимает подсветку с выбранного интервала
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

		// Если ClientName Edit теряет фокус. Нужна, чтобы пересчитать
		// Total.
		afx_msg void ClientNameKillFocus();
		// Если LengthMoney Edit теряет фокус
		afx_msg void LengthMoneyKillFocus();

		// На DateTimeNotify
		afx_msg void OnDTNotify(NMHDR* pNotifyStruct, LRESULT* result);

		// Пересчитывает Total. Если передается bNormalizationRequired,
		// то к интервалу еще применяется MaxInterval.
		void DoRecalcTotal(bool bNormalizationRequired = 0);
		// Возвращает результирующий интервал. Не вычисляет его
		// цену, т.к. обычно еще нужна нормальзация, чтобы
		// не выйти за пределы тарифного плана.
		void DoGetEnteredInterval(CBusyInterval* pInterval);

		// Чтобы увеличить число элементов в выпадающем меню
		void DoIncreaseHeight(CComboBox* pBox);

		virtual void OnOK();
		virtual void OnCancel();

		DECLARE_MESSAGE_MAP()
	public:
		// Конструктор
		CNewIntervalDialog(CDialogState* pDialogState, CMasterRegistryStorer* pStorer,
					CClubState* pState);
		// Деструктор
		virtual ~CNewIntervalDialog();

		// Вызывается из CInterfaceDoc
		void OnTimer();

		// Возвращает время уже с учетом текущей даты
		CTimeContainer GetFromTime();

		virtual int DoModal();

		void DoCancel() {OnCancel();};
};


#endif // __NEWINTERVALDIALOG_H__