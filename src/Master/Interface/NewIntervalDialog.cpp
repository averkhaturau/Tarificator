#include "stdafx.h"

#include "NewIntervalDialog.h"
#include "AdditionalResource.h"
#include "..\..\Slave\Slave\Exceptions.h"
#include "..\DataStructures\ClubSettings\IntervalAddition.h"
#include "Interface.h"
#include "BusyView.h"
#include "..\DataStructures\ClubSettings\IntervalAddition.h"
#include "..\DataStructures\FinantialHistoryLogger.h"

#include <string>


BEGIN_MESSAGE_MAP(CNewIntervalDialog, CDialog)
	//{{AFX_MSG_MAP(CNewIntervalDialog)
	ON_BN_CLICKED(IDC_FROM_TIME_CURRENT_RADIO, OnFromTimeCurrentClick)
	ON_BN_CLICKED(IDC_FROM_TIME_AS_SOON_AS_RADIO, OnFromTimeAsSoonAsClick)
	ON_BN_CLICKED(IDC_FROM_TIME_TIME_RADIO, OnFromTimeTimeClick)
	ON_BN_CLICKED(IDC_LENGTH_MONEY_RADIO, OnLengthMoneyClick)
	ON_BN_CLICKED(IDC_LENGTH_TIME_RADIO, OnLengthTimeClick)
	ON_BN_CLICKED(IDC_STOP_RIGHT_NOW_CHECK, OnStopRightNowClick)

	ON_CBN_SELCHANGE(IDC_ACTION_COMBO, OnActionComboSelectionChange)
	ON_CBN_SELCHANGE(IDC_INTERVAL_CHOICE_COMBO, OnIntervalChoiceComboSelectionChange)
	ON_CBN_SELCHANGE(IDC_MASHINE_COMBO, OnMashineComboSelectionChange)
	ON_CBN_SELCHANGE(IDC_TARIF_COMBO, OnTarifComboSelectionChange)

	ON_EN_KILLFOCUS(IDC_LENGTH_MONEY, LengthMoneyKillFocus)
	ON_EN_KILLFOCUS(IDC_CLINETNAME_EDIT, ClientNameKillFocus)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_FROM_TIME, OnDTNotify)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_LENGTH_TIME, OnDTNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CNewIntervalDialog::CNewIntervalDialog(CDialogState* pDialogState,
			CMasterRegistryStorer* pStorer, CClubState* pState) : CDialog(IDD)
{
		if (!pState)
			throw CAnyLogableException("NULL pState in CNewIntervalDialog::CNewIntervalDialog!", bDoNotWriteDuplicates);

	m_pState = pState;

	m_pFreeIntervals = 0;

	m_pPaybackDialog = 0;

	m_pFinantialLogger = 0;

	m_pActionCombo = 0;
	m_pIntervalChoiceCombo = 0;
	m_pMashineCombo = 0;
	m_pTarifCombo = 0;

	m_pFromTimeCurrentRadio = 0;
	m_pFromTimeAsSoonAsRadio = 0;
	m_pFromTimeTimeRadio = 0;
	m_pLengthTimeRadio = 0;
	m_pLengthMoneyRadio = 0;
	m_pClientNameEdit = 0;
	m_pStopRightNow = 0;
	m_pTotalStatic = 0;
	m_pAdditionalTotalStatic = 0;
	m_pMashinesSelection = 0;

	m_pFromTime = 0;
	m_pLengthTime = 0;
	m_pLengthMoney = 0;

	m_pPreviouslySelected = 0;
	m_pHighlightedColoredCollection = 0;

	m_pView = 0;

	m_pDialogState = pDialogState;

	try{
		try{
			m_pFreeIntervals = new CIntervalsStorage<CInterval>;

			m_pFromTime = new CDateTimeCtrl;
			m_pLengthTime = new CDateTimeCtrl;
			m_pLengthMoney = new CIntEdit;
			m_pMashinesSelection = new CMashinesSelectionControl;

			m_pFont = new CFont;
			NONCLIENTMETRICS ncm;
			ncm.cbSize = sizeof(NONCLIENTMETRICS);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
			m_pFont->CreateFontIndirect(&ncm.lfMessageFont);

				if (pStorer)
				{
					m_pFinantialLogger = new CFinantialHistoryLogger(pStorer, m_pState);
				}
		}catch(...){
			DoDeleteEverything();
			throw;
		}
	}catch(CAnyLogableException &e){
		throw CAnyLogableException(
			std::string((std::string)"CNewIntervalDialog() failed: "
			+ (std::string)e.what()).c_str(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("CNewIntervalDialog() failed", bDoNotWriteDuplicates);
	}
}
// End of CNewIntervalDialog()


CNewIntervalDialog::~CNewIntervalDialog()
{
	DoDeleteEverything();
}
// End of ~CNewIntervalDialog()


void CNewIntervalDialog::DoDeleteEverything()
{
		if (m_pFinantialLogger)
		{
			delete m_pFinantialLogger;
			m_pFinantialLogger = 0;
		}
		if (m_pFreeIntervals)
		{
			delete m_pFreeIntervals;
			m_pFreeIntervals = 0;
		}
		if (m_pFromTime)
		{
			delete m_pFromTime;
			m_pFromTime = 0;
		}
		if (m_pLengthTime)
		{
			delete m_pLengthTime;
			m_pLengthTime = 0;
		}
		if (m_pLengthMoney)
		{
			delete m_pLengthMoney;
			m_pLengthMoney = 0;
		}
		if (m_pPaybackDialog)
		{
			delete m_pPaybackDialog;
			m_pPaybackDialog = 0;
		}
		if (m_pMashinesSelection)
		{
			delete m_pMashinesSelection;
			m_pMashinesSelection = 0;
		}
		if (m_pFont)
		{
			m_pFont->DeleteObject();
			delete m_pFont;
			m_pFont = 0;
		}
}
// End of DoDeleteEverything()


int CNewIntervalDialog::DoModal()
{
	int retcode = CDialog::DoModal();

	return retcode;
}
// End of DoModal


BOOL CNewIntervalDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pActionCombo = (CComboBox*)GetDlgItem(IDC_ACTION_COMBO);
	m_pIntervalChoiceCombo = (CComboBox*)GetDlgItem(IDC_INTERVAL_CHOICE_COMBO);
	m_pMashineCombo = (CComboBox*)GetDlgItem(IDC_MASHINE_COMBO);
	m_pTarifCombo = (CComboBox*)GetDlgItem(IDC_TARIF_COMBO);

	m_pFromTimeCurrentRadio = (CButton*)GetDlgItem(IDC_FROM_TIME_CURRENT_RADIO);
	m_pFromTimeAsSoonAsRadio = (CButton*)GetDlgItem(IDC_FROM_TIME_AS_SOON_AS_RADIO);
	m_pFromTimeTimeRadio = (CButton*)GetDlgItem(IDC_FROM_TIME_TIME_RADIO);
	m_pLengthTimeRadio = (CButton*)GetDlgItem(IDC_LENGTH_TIME_RADIO);
	m_pLengthMoneyRadio = (CButton*)GetDlgItem(IDC_LENGTH_MONEY_RADIO);
	m_pClientNameEdit = (CEdit*)GetDlgItem(IDC_CLINETNAME_EDIT);

	m_pStopRightNow = (CButton*)GetDlgItem(IDC_STOP_RIGHT_NOW_CHECK);

	m_pTotalStatic = (CStatic*)GetDlgItem(IDC_TOTAL_STATIC);
	m_pAdditionalTotalStatic = (CStatic*)GetDlgItem(IDC_ADDITIONAL_TOTAL_STATIC);
	m_pOldOperatorStatic = (CStatic*)GetDlgItem(IDC_OLD_OPERATOR_STATIC);

		if (!(m_pActionCombo && m_pIntervalChoiceCombo &&
					m_pMashineCombo && m_pTarifCombo &&
					m_pFromTimeCurrentRadio && m_pFromTimeAsSoonAsRadio &&
					m_pFromTimeTimeRadio && m_pLengthTimeRadio &&
					m_pLengthMoneyRadio && m_pClientNameEdit &&
					m_pStopRightNow && m_pTotalStatic && m_pOldOperatorStatic))
		{
			// Тут нельзя делать throw, т.к. исключения в OnInitDialog
			// не ловятся и получается хрен знает что
			//throw CAnyLogableException("Can't get a control in CNewIntervalDialog::OnInitDialog()", bDoNotWriteDuplicates);
		}

	CInterfaceDoc* pDoc = ((CInterfaceApp*)AfxGetApp())->GetActiveDoc();

	m_pView = pDoc->GetBusyView();

	m_pClientNameEdit->SetWindowText("");

	CRect ComboRect;
	m_pActionCombo->GetWindowRect(&ComboRect);
	ScreenToClient(&ComboRect);

	CRect RadioRect;
	m_pFromTimeTimeRadio->GetWindowRect(&RadioRect);
	ScreenToClient(&RadioRect);

	CRect Rect;
	m_pStopRightNow->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	Rect.right = Rect.left + dwMoneyEditWidth;
	Rect.bottom = RadioRect.bottom;
	Rect.top = Rect.bottom - ComboRect.Height();

	m_pFromTime->Create(
				WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT | WS_TABSTOP, // Styles
				Rect, // Rect
				this, // Parent
				IDC_FROM_TIME
	);

	m_pLengthTimeRadio->GetWindowRect(&RadioRect);
	ScreenToClient(&RadioRect);

	Rect.bottom = RadioRect.bottom;
	Rect.top = Rect.bottom - ComboRect.Height();

	m_pLengthTime->Create(
				WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT | WS_TABSTOP, // Styles
				Rect, // Rect
				this, // Parent
				IDC_LENGTH_TIME
	);

	m_pLengthMoneyRadio->GetWindowRect(&RadioRect);
	ScreenToClient(&RadioRect);
	Rect.bottom = RadioRect.bottom;
	Rect.top = Rect.bottom - ComboRect.Height();

	m_pLengthMoney->CreateEx(
				WS_EX_CLIENTEDGE, // Styles
				"EDIT", // Control class name
				"0", // Window name
				ES_RIGHT | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER, //Styles
				Rect, // Rect
				this, // Parent
				IDC_LENGTH_MONEY
	);

	m_pMashinesSelection->Create("Caption", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, 0);
	m_pMashineCombo->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	CRect ClientRect;
	GetClientRect(&ClientRect);
	m_pMashinesSelection->SetWindowPos(0,
				Rect.right + 5,
				ClientRect.top + 2,
				ClientRect.right - Rect.right - 10,
				100,
				SWP_NOZORDER);
	m_pMashinesSelection->SetMashinesCollection(m_pState->GetMashinesCollection());
	m_pMashinesSelection->SetFont(m_pFont);

	// Обнуление длины интервала
	{
		SYSTEMTIME Length;
		m_pLengthTime->GetTime(&Length);
		CTimeStorage LengthTime(&Length);
		LengthTime -= LengthTime.TruncateToDay();
		LengthTime.GetTime(&Length);
		m_pLengthTime->SetTime(&Length);
	}

		if ( (!m_pFromTime) || (!m_pLengthTime) )
		{
			//throw CAnyLogableException("Can't create DateTime control in CNewIntervalDialog::OnInitDialog (Internet Explorer 3+ needed)", bDoNotWriteDuplicates);
		}

	DoSetTabOrders();

	DoCheckFromTimeCurrent();
	OnFromTimeCurrentClick();

	DoCheckLengthMoney();
	OnLengthMoneyClick();

		// Заполнение ComboBox'ов
		{
			DoFillActionCombo();

			// Машины:
			DoFillMashineCombo();

			DoFillTarifCombo(/*csFrom_m_DialogState*/);

			DoIncreaseHeight(m_pActionCombo);
			DoIncreaseHeight(m_pMashineCombo);
			DoIncreaseHeight(m_pIntervalChoiceCombo);
			DoIncreaseHeight(m_pTarifCombo);
		}

	DoDisableControls();

	return TRUE;
}
// End of OnInitDialog()


void CNewIntervalDialog::DoFillActionCombo()
{

}
// End of DoFillActionCombo()


void CNewIntervalDialog::DoFillIntervalCombo(DWORD dwRememberState)
{
	int iRememberedState;
		if (dwRememberState == csDefault)
			iRememberedState = -1;
		if (dwRememberState == csDontChange)
			iRememberedState = m_pIntervalChoiceCombo->GetItemData(m_pIntervalChoiceCombo->GetCurSel());

	m_pIntervalChoiceCombo->ResetContent();

	int iMashineIndex = m_pMashineCombo->GetCurSel();
		if ( (iMashineIndex == CB_ERR) )
			return;

	iMashineIndex = m_pMashineCombo->GetItemData(iMashineIndex);

	CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[iMashineIndex]);

		if (m_pActionCombo->GetCurSel() == iNewInterval)
		{
			// Если выбрано создание нового интервала
			int iTarifIndex = m_pTarifCombo->GetCurSel();
				if ( (iTarifIndex != CB_ERR) )
				{
					iTarifIndex = m_pTarifCombo->GetItemData(iTarifIndex);
					CTarifPlan* pPlan = &(*m_pState->GetTarifPlansCollection())[iTarifIndex];

					DoFillFreeIntervals(pPlan, pSelectedMashine);
				}
		}
		if (m_pActionCombo->GetCurSel() == iEditInterval)
		{
			// Если выбрано редактирование интервала
			DWORD i = 0;
			CBusyIntervalsCollection* pCollection = pSelectedMashine->GetBusyIntervalsCollection();
			CBusyIntervalsCollection::iterator EndIter = pCollection->GetData()->end();
				for (CBusyIntervalsCollection::iterator Iter = pCollection->GetData()->begin();
							Iter != EndIter; ++Iter, ++i)
				{
					CBusyInterval* pBusyInterval = (*Iter)->GetCurrentInterval();
						// Чтобы не писались прошедшие интервалы
						if ((*Iter)->GetCurrentInterval()->GetFinishTime() > CurrentTime())
						{
							DoAddBusyIntervalToCombo((*Iter)->GetCurrentInterval(), i);
						}
				}
		}

		if (dwRememberState == csDontChange)
		{
				for (int i = 0; i < m_pIntervalChoiceCombo->GetCount(); ++i)
				{
						if (m_pIntervalChoiceCombo->GetItemData(i) == iRememberedState)
						{
							m_pIntervalChoiceCombo->SetCurSel(i);
							OnIntervalChoiceComboSelectionChange();
							break;
						}
				}
		}
		else
			m_pIntervalChoiceCombo->SetCurSel(iRememberedState);

		if (m_pIntervalChoiceCombo->GetCurSel() == CB_ERR)
			DoUnHighlightInterval();
}
// End of DoFillIntervalCombo()


void CNewIntervalDialog::DoAddBusyIntervalToCombo(CBusyInterval* pInterval, DWORD dwNumber)
{
	CString Text = "Занятый ";
	Text += IntervalAddition::DescribeInterval_In_Russian(pInterval).c_str();
	Text += ", клиент ";
	Text += pInterval->GetClientName().c_str();

	int ItemIndex = m_pIntervalChoiceCombo->AddString( Text );
	m_pIntervalChoiceCombo->SetItemData(ItemIndex, dwNumber);
}
// End of DoAddBusyIntervalToCombo


void CNewIntervalDialog::DoAddFreeIntervalToCombo(CInterval* pInterval, DWORD dwNumber)
{
	CString Text = "Свободный ";
	Text += IntervalAddition::DescribeInterval_In_Russian(pInterval).c_str();

	int ItemIndex = m_pIntervalChoiceCombo->AddString( Text );
	m_pIntervalChoiceCombo->SetItemData(ItemIndex, dwNumber);
}
// End of DoAddFreeIntervalToCombo


void CNewIntervalDialog::DoFillMashineCombo()
{
	m_pMashineCombo->ResetContent();

	int ItemIndex = 0;
	int i = 0;
	CMashinesCollection::iterator End = m_pState->GetMashinesCollection()->GetData()->end();
		for (CMashinesCollection::iterator Iter = m_pState->GetMashinesCollection()->GetData()->begin();
					Iter < End; ++Iter, ++i)
		{
			ItemIndex = m_pMashineCombo->AddString( (*Iter)->GetMashineName().c_str() );
			m_pMashineCombo->SetItemData(ItemIndex, i);
		}

		if ( m_pMashineCombo->GetCount() > m_pDialogState->GetMashineIndex() )
			m_pMashineCombo->SetCurSel(m_pDialogState->GetMashineIndex());
}
// End of DoFillMashineCombo()


void CNewIntervalDialog::DoFillTarifCombo(DWORD dwRememberState)
{
	int iRememberedState;
		if (dwRememberState == csDefault)
			iRememberedState = -1;
		if (dwRememberState == csFrom_m_DialogState)
			iRememberedState = m_pDialogState->GetTarifPlanIndex();
		if (dwRememberState == csDontChange)
			iRememberedState = m_pTarifCombo->GetItemData(m_pTarifCombo->GetCurSel());

	m_pTarifCombo->ResetContent();

	int iMashineIndex = m_pMashineCombo->GetCurSel();
		if ( iMashineIndex == CB_ERR )
			return;

	iMashineIndex = m_pMashineCombo->GetItemData(iMashineIndex);

	COperator* pSelectedOperator = &((*m_pState->GetOperatorsCollection())[m_pDialogState->GetOperatorIndex()]);
	CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[iMashineIndex]);

	int iItemNumber;
	CMashineData::CTarifPlansNumbers::iterator End = pSelectedMashine->GetTarifPlansNumbers()->end();
	for (CMashineData::CTarifPlansNumbers::iterator Iter =
			pSelectedMashine->GetTarifPlansNumbers()->begin();
				Iter != End; ++Iter)
	{
		//CTarifPlan* pPlan = &((*m_pState->GetTarifPlansCollection())[*Iter]);
			if ( (*m_pState->GetTarifPlansCollection())[*Iter].GetPermission() <=
						pSelectedOperator->GetPermission() )
			{
				iItemNumber = m_pTarifCombo->AddString( (*m_pState->GetTarifPlansCollection())[*Iter].GetName().c_str() );
				m_pTarifCombo->SetItemData(iItemNumber, *Iter);
			}
	}

		if (dwRememberState == csDontChange)
		{
				for (int i = 0; i < m_pTarifCombo->GetCount(); ++i)
				{
						if (m_pTarifCombo->GetItemData(i) == iRememberedState)
						{
							m_pTarifCombo->SetCurSel(i);
							break;
						}
				}
		}
		else
			m_pTarifCombo->SetCurSel(iRememberedState);
}
// End of DoFillTarifCombo()


void CNewIntervalDialog::DoIncreaseHeight(CComboBox* pBox)
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


void CNewIntervalDialog::OnFromTimeCurrentClick()
{
	SYSTEMTIME Time;
	CurrentTime().GetTime(&Time);
	m_pFromTime->SetTime(&Time);

	m_pFromTime->EnableWindow(0);
}
// End of OnFromTimeCurrentClick()


void CNewIntervalDialog::OnFromTimeAsSoonAsClick()
{
	int iIntervalIndex = m_pIntervalChoiceCombo->GetCurSel();
		if ( (iIntervalIndex == CB_ERR) )
			return;

	iIntervalIndex = m_pIntervalChoiceCombo->GetItemData(iIntervalIndex);

	int iMashineIndex = m_pMashineCombo->GetCurSel();
	iMashineIndex = m_pMashineCombo->GetItemData(iMashineIndex);

		if ( (iMashineIndex == CB_ERR) )
			return;

		if (m_pActionCombo->GetCurSel() == iEditInterval)
		{
			CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[iMashineIndex]);
			CBusyInterval* pSelectedInterval = ((*pSelectedMashine->GetBusyIntervalsCollection())[iIntervalIndex]).GetCurrentInterval();

				if (!pSelectedInterval)
					throw CAnyLogableException("An error occured in CNewIntervalDialog: can't get pointed interval 8-/", bDoNotWriteDuplicates);

			// Предыдущий по времени интервал
			CBusyIntervalHist** ppPrevIntervalHist = pSelectedMashine->GetBusyIntervalsCollection()->GetPreviousInterval(pSelectedInterval->GetStartTime());
			CBusyInterval* pPrevInterval = 0;
				if (ppPrevIntervalHist != pSelectedMashine->GetBusyIntervalsCollection()->GetData()->end())
					pPrevInterval = (*ppPrevIntervalHist)->GetCurrentInterval();

			SYSTEMTIME Time;
				if (pPrevInterval != 0)
				{
					pPrevInterval->GetFinishTime().TransposeToToday().GetTime(&Time);
					m_pFromTime->SetTime(&Time);
				}
		}

	m_pFromTime->EnableWindow(0);
}
// End of OnFromTimeAsSoonAsClick()


void CNewIntervalDialog::OnFromTimeTimeClick()
{
	m_pFromTime->EnableWindow(1);
}
// End of OnFromTimeTimeClick()


void CNewIntervalDialog::OnLengthMoneyClick()
{
	m_pLengthTime->EnableWindow(0);
	m_pLengthMoney->EnableWindow(1);
	m_pStopRightNow->EnableWindow(0);
}
// End of OnLengthMoneyClick()


void CNewIntervalDialog::OnLengthTimeClick()
{
		if (m_pActionCombo->GetCurSel() == iEditInterval)
		{
			m_pStopRightNow->EnableWindow(1);
		}
		if (m_pActionCombo->GetCurSel() == iNewInterval)
		{
			m_pStopRightNow->EnableWindow(0);
		}

	m_pLengthTime->EnableWindow(1);
	m_pLengthMoney->EnableWindow(0);

	OnStopRightNowClick();
}
// End of OnLengthTimeClick()


CTimeContainer CNewIntervalDialog::GetFromTime()
{
	SYSTEMTIME FromTime;
	m_pFromTime->GetTime(&FromTime);

	CTimeStorage From(&FromTime);

	CTimeStorage Time = From.TruncateToDay();

	return (Time.TransposeToToday()).GetTime();
}
// End of GetFromTime()


void CNewIntervalDialog::OnMashineComboSelectionChange()
{
	m_pOldOperatorStatic->SetWindowText("");

	m_pDialogState->SetMashineIndex(m_pMashineCombo->GetCurSel());

	DoFillTarifCombo();

	DoFillIntervalCombo();

		/*if ( (m_pActionCombo->GetCurSel() == iEditInterval) &&
					(m_pIntervalChoiceCombo->GetCurSel() == CB_ERR) )
		{*/
			m_pClientNameEdit->SetWindowText("");

			DoDisableFromTimeLengthControls();
		//}

	DoRecalcTotal();
}
// End of OnMashineComboSelectionChange()


void CNewIntervalDialog::OnTarifComboSelectionChange()
{
	m_pDialogState->SetTarifPlanIndex(m_pTarifCombo->GetCurSel());

	int iState = csDefault;

		if (m_pIntervalChoiceCombo->GetCurSel() != CB_ERR)
		{
			iState = csDontChange;
		}

	DoFillIntervalCombo(iState);

	DoRecalcTotal();
}
// End of OnTarifComboSelectionChange()


void CNewIntervalDialog::OnActionComboSelectionChange()
{
	m_pOldOperatorStatic->SetWindowText("");
		if (m_pActionCombo->GetCurSel() == iNewInterval)
		{
			// Если выбрано создание нового интервала
			DoDisableControls();

			m_pMashineCombo->EnableWindow(true);
			m_pTarifCombo->EnableWindow(true);
			m_pIntervalChoiceCombo->EnableWindow(true);

			DoFillIntervalCombo();

			m_pClientNameEdit->SetWindowText("");

			//m_pActionCombo->EnableWindow(false);
		}

		if (m_pActionCombo->GetCurSel() == iEditInterval)
		{
			// Если выбрано редактирование интервала
			DoDisableControls();

			m_pMashineCombo->EnableWindow(true);
			m_pTarifCombo->EnableWindow(false);
			m_pIntervalChoiceCombo->EnableWindow(true);

			DoFillIntervalCombo();

			//m_pActionCombo->EnableWindow(false);
		}

	DoRecalcTotal();
}
// End of OnActionComboSelectionChange()


void CNewIntervalDialog::OnIntervalChoiceComboSelectionChange()
{
	int iIntervalIndex = m_pIntervalChoiceCombo->GetCurSel();
		if ( (iIntervalIndex == CB_ERR) )
			return;

	iIntervalIndex = m_pIntervalChoiceCombo->GetItemData(iIntervalIndex);

	int iMashineIndex = m_pMashineCombo->GetCurSel();
	iMashineIndex = m_pMashineCombo->GetItemData(iMashineIndex);

		if ( (iMashineIndex == CB_ERR) )
			return;

	m_pOldOperatorStatic->SetWindowText("");

		if (m_pActionCombo->GetCurSel() == iNewInterval)
		{
			// Создание нового интервала
			CInterval* pFreeInterval = &((*m_pFreeIntervals)[iIntervalIndex]);

			// Разборки с начальным временем
			DoCheckFromTimeTime();
			SYSTEMTIME StartTime;
			pFreeInterval->GetStartTime().GetTime(&StartTime);
			m_pFromTime->SetTime(&StartTime);
			m_pFromTimeAsSoonAsRadio->EnableWindow(false);
			m_pFromTimeCurrentRadio->EnableWindow(false);
			m_pFromTimeTimeRadio->EnableWindow(true);
				if ( m_pFromTimeTimeRadio->GetCheck() )
					// Если checked:
					OnFromTimeTimeClick();

			// Разборки с длиной интервала
			SYSTEMTIME Length;
			pFreeInterval->GetLength().TransposeToToday().GetTime(&Length);
			m_pLengthTime->SetTime(&Length);
			m_pLengthMoneyRadio->EnableWindow(true);
			m_pLengthTimeRadio->EnableWindow(true);
				if ( m_pLengthMoneyRadio->GetCheck() )
					// Если checked:
					OnLengthMoneyClick();
				if ( m_pLengthTimeRadio->GetCheck() )
					// Если checked:
					OnLengthTimeClick();

			m_pClientNameEdit->EnableWindow(true);

			// Разборки с подсветкой FreeInterval
			/*{
				DoUnHighlightInterval();

				CMashineLineControl* pLineControl = &((*m_pView->GetLineControlsCollection())[iMashineIndex]);
				CColoredIntervalsCollection* pCollection = pLineControl->GetIntervalsLineControl()->GetIntervalsCollection();

				CColoredInterval ColoredFreeInterval(*pFreeInterval);
				ColoredFreeInterval.SetColor(ciSelectedFreeColor);

				m_pPreviouslySelected = pCollection->AddResident(ColoredFreeInterval);

				m_pHighlightedColoredCollection = pCollection;

				m_pView->Invalidate();
			}*/

			// Разборки со стоимостью интервала
			{
				int iTarifIndex = m_pTarifCombo->GetCurSel();
					if ( (iTarifIndex == CB_ERR) )
						return;
				iTarifIndex = m_pTarifCombo->GetItemData(iTarifIndex);
				//CTarifPlan pPlan = (*m_pState->GetTarifPlansCollection())[iTarifIndex];

				CBusyInterval TempBusyInterval;
				TempBusyInterval.SetStartTime(pFreeInterval->GetStartTime());
				TempBusyInterval.SetFinishTime(pFreeInterval->GetFinishTime());
				TempBusyInterval.SetTarifPlanNumber(iTarifIndex);
				TempBusyInterval.SetPrice( m_pState->CalcIntervalPrice(&TempBusyInterval) );

				m_pLengthMoney->FillEdit(TempBusyInterval.GetPrice());
			}
		}
		if (m_pActionCombo->GetCurSel() == iEditInterval)
		{
			// Редактирование интервала
			m_pStopRightNow->SetCheck(false);

			CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[iMashineIndex]);
			CBusyInterval* pSelectedInterval = ((*pSelectedMashine->GetBusyIntervalsCollection())[iIntervalIndex]).GetCurrentInterval();

				if (!pSelectedInterval)
					throw CAnyLogableException("An error occured in CNewIntervalDialog: can't get pointed interval 8-/", bDoNotWriteDuplicates);

			// Подсветка выбранного интервала другим цветом
			/*{
				CMashineLineControl* pLineControl = &((*m_pView->GetLineControlsCollection())[iMashineIndex]);
				CColoredIntervalsCollection* pCollection = pLineControl->GetIntervalsLineControl()->GetIntervalsCollection();
				CColoredInterval ColoredInterval(*pSelectedInterval);
				CColoredInterval* pSelectedColoredInterval = *(pCollection->FindResident(ColoredInterval));
					if (&pSelectedColoredInterval == pCollection->GetData()->end())
						throw CAnyLogableException("An error occured in CNewIntervalDialog::OnIntervalChoiceComboSelectionChange: can't get selected colored interval (programmer's mistake)", bDoNotWriteDuplicates);

				DoUnHighlightInterval();

				pSelectedColoredInterval->SetColor(ciSelectedBusyColor);

				m_pPreviouslySelected = pSelectedColoredInterval;

				m_pView->Invalidate();
			}*/

			m_pClientNameEdit->EnableWindow(true);
			m_pClientNameEdit->SetWindowText(pSelectedInterval->GetClientName().c_str());

			// Разборки с начальным временем
			DoCheckFromTimeTime();
			SYSTEMTIME StartTime;
			pSelectedInterval->GetStartTime().GetTime(&StartTime);
			m_pFromTime->SetTime(&StartTime);
				if (pSelectedInterval->GetStartTime() < CurrentTime())
				{
					m_pFromTimeAsSoonAsRadio->EnableWindow(false);
					m_pFromTimeCurrentRadio->EnableWindow(false);
					m_pFromTimeTimeRadio->EnableWindow(false);
					m_pFromTime->EnableWindow(false);
				}
				else
				{
					// Предыдущий по времени интервал
					CBusyIntervalHist** ppPrevIntervalHist = pSelectedMashine->GetBusyIntervalsCollection()->GetPreviousInterval(pSelectedInterval->GetStartTime());
					CBusyInterval* pPrevInterval = 0;
						if (ppPrevIntervalHist != pSelectedMashine->GetBusyIntervalsCollection()->GetData()->end())
							pPrevInterval = (*ppPrevIntervalHist)->GetCurrentInterval();

					m_pFromTimeAsSoonAsRadio->EnableWindow(false);
					m_pFromTimeCurrentRadio->EnableWindow(true);
						if (pPrevInterval != 0)
								if (pPrevInterval->GetFinishTime() >= CurrentTime())
								{
									m_pFromTimeAsSoonAsRadio->EnableWindow(true);
									m_pFromTimeCurrentRadio->EnableWindow(false);
								}
					m_pFromTimeTimeRadio->EnableWindow(true);
						if ( m_pFromTimeTimeRadio->GetCheck() )
							// Если checked:
							OnFromTimeTimeClick();
				}

			// Разборки с длиной интервала
			SYSTEMTIME Length;
			pSelectedInterval->GetLength().TransposeToToday().GetTime(&Length);
			m_pLengthTime->SetTime(&Length);
			m_pLengthMoneyRadio->EnableWindow(true);
			m_pLengthTimeRadio->EnableWindow(true);
				if ( m_pLengthMoneyRadio->GetCheck() )
					// Если checked:
					OnLengthMoneyClick();
				if ( m_pLengthTimeRadio->GetCheck() )
					// Если checked:
					OnLengthTimeClick();

			DoFillTarifCombo();

				// Разборки с подсветкой тарифного плана
				{
					/*COperator* pOperator = &((*m_pState->GetOperatorsCollection())[pSelectedInterval->GetOperatorNumber()]);
					CPermission Permission = pOperator->GetPermission();*/
					bool bFlag = false;
						for (DWORD i = 0; i < m_pTarifCombo->GetCount(); ++i)
						{
								if (m_pTarifCombo->GetItemData(i) ==
									pSelectedInterval->GetTarifPlanNumber())
								{
									m_pTarifCombo->SetCurSel(i);
									bFlag = true;
									break;
								}
						}
						if (!bFlag)
							m_pTarifCombo->SetCurSel(-1);
				}

			std::string StaticText = "Старый оператор: ";
			StaticText += ((*m_pState->GetOperatorsCollection())[pSelectedInterval->GetOperatorNumber()]).GetName();
			m_pOldOperatorStatic->SetWindowText(StaticText.c_str());
		}

	DoRecalcTotal();
}
// End of OnIntervalChoiceComboSelectionChange()


void CNewIntervalDialog::DoDisableControls()
{
	m_pIntervalChoiceCombo->EnableWindow(false);
	m_pMashineCombo->EnableWindow(false);
	m_pTarifCombo->EnableWindow(false);
	m_pClientNameEdit->EnableWindow(false);

	DoDisableFromTimeLengthControls();
}
// End of DoDisableControls()


void CNewIntervalDialog::DoDisableFromTimeLengthControls()
{
	m_pFromTimeCurrentRadio->EnableWindow(false);
	m_pFromTimeAsSoonAsRadio->EnableWindow(false);
	m_pFromTimeTimeRadio->EnableWindow(false);
	m_pFromTime->EnableWindow(false);

	m_pLengthTimeRadio->EnableWindow(false);
	m_pLengthMoneyRadio->EnableWindow(false);
	m_pLengthMoney->EnableWindow(false);
	m_pLengthTime->EnableWindow(false);

	m_pStopRightNow->EnableWindow(false);
}
// End of DoDisableFromTimeLengthControls()


void CNewIntervalDialog::DoSetTabOrders()
{
	// Этот кошмар - для установки Tab Order'ов

	CRect WindowRect;

	m_pActionCombo->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pActionCombo->SetWindowPos(&wndTop, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pMashineCombo->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pMashineCombo->SetWindowPos(m_pActionCombo, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pTarifCombo->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pTarifCombo->SetWindowPos(m_pMashineCombo, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pIntervalChoiceCombo->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pIntervalChoiceCombo->SetWindowPos(m_pTarifCombo, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pClientNameEdit->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pClientNameEdit->SetWindowPos(m_pIntervalChoiceCombo, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pFromTimeCurrentRadio->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pFromTimeCurrentRadio->SetWindowPos(m_pClientNameEdit, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pFromTimeAsSoonAsRadio->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pFromTimeAsSoonAsRadio->SetWindowPos(m_pFromTimeCurrentRadio, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pFromTimeTimeRadio->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pFromTimeTimeRadio->SetWindowPos(m_pFromTimeAsSoonAsRadio, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pFromTime->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pFromTime->SetWindowPos(m_pFromTimeTimeRadio, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pLengthMoneyRadio->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pLengthMoneyRadio->SetWindowPos(m_pFromTime, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pLengthTimeRadio->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pLengthTimeRadio->SetWindowPos(m_pLengthMoneyRadio, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pLengthMoney->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pLengthMoney->SetWindowPos(m_pLengthTimeRadio, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);

	m_pLengthTime->GetWindowRect(&WindowRect);
	ScreenToClient(&WindowRect);
	m_pLengthTime->SetWindowPos(m_pLengthMoney, WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height(), 0);
}
// End of DoSetTabOrders()


void CNewIntervalDialog::DoCheckFromTimeCurrent()
{
	m_pFromTimeCurrentRadio->SetCheck(true);
	m_pFromTimeAsSoonAsRadio->SetCheck(false);
	m_pFromTimeTimeRadio->SetCheck(false);
}
// End of DoCheckFromTimeCurrent()


void CNewIntervalDialog::DoCheckFromTimeAsSoonAs()
{
	m_pFromTimeCurrentRadio->SetCheck(false);
	m_pFromTimeAsSoonAsRadio->SetCheck(true);
	m_pFromTimeTimeRadio->SetCheck(false);
}
// End of DoCheckFromTimeAsSoonAs()


void CNewIntervalDialog::DoCheckFromTimeTime()
{
	m_pFromTimeCurrentRadio->SetCheck(false);
	m_pFromTimeAsSoonAsRadio->SetCheck(false);
	m_pFromTimeTimeRadio->SetCheck(true);
}
// End of DoCheckFromTimeTime()


void CNewIntervalDialog::DoCheckLengthMoney()
{
	m_pLengthMoneyRadio->SetCheck(true);
	m_pLengthTimeRadio->SetCheck(false);
}
// End of DoCheckLengthMoney()


void CNewIntervalDialog::DoCheckLengthTime()
{
	m_pLengthMoneyRadio->SetCheck(false);
	m_pLengthTimeRadio->SetCheck(true);
}
// End of DoCheckLengthTime()


void CNewIntervalDialog::OnStopRightNowClick()
{
		if (m_pStopRightNow->GetCheck())
		{
			m_pLengthTime->EnableWindow(0);
			m_pLengthMoneyRadio->EnableWindow(0);

			int iIntervalIndex = m_pIntervalChoiceCombo->GetCurSel();
				if ( (iIntervalIndex == CB_ERR) )
					return;

			iIntervalIndex = m_pIntervalChoiceCombo->GetItemData(iIntervalIndex);

			int iMashineIndex = m_pMashineCombo->GetCurSel();
			iMashineIndex = m_pMashineCombo->GetItemData(iMashineIndex);
				if ( (iMashineIndex == CB_ERR) )
					return;

			CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[iMashineIndex]);
			CBusyInterval* pSelectedInterval = ((*pSelectedMashine->GetBusyIntervalsCollection())[iIntervalIndex]).GetCurrentInterval();

			CBusyInterval IntervalToEdit = *pSelectedInterval;
				if (IntervalToEdit.GetStartTime() < CurrentTime())
					IntervalToEdit.SetFinishTime(CurrentTime());
				else
					IntervalToEdit.SetLengthFromStart(CTimeStorage((CTimeContainer)0));

			SYSTEMTIME Time;
			IntervalToEdit.GetLength().TransposeToToday().GetTime(&Time);
			m_pLengthTime->SetTime(&Time);

			DoRecalcTotal(true);
		}
		else
		{
			m_pLengthTime->EnableWindow(1);
			m_pLengthMoneyRadio->EnableWindow(1);
		}
}
//End of OnStopRightNowClick()


void CNewIntervalDialog::OnOK()
{
	m_pPaybackDialog = 0;

		try
		{
			DoUnHighlightInterval();

				if (m_pLengthMoneyRadio->GetCheck())
				{
					DoRecalcLengthByPrice();
				}
				if (m_pLengthTimeRadio->GetCheck())
				{
					DoRecalcTotal(true);
				}

			int iDialogResult = IDOK;

				if (m_pIntervalChoiceCombo->GetCurSel() != CB_ERR)
				{
					CTimeContainer CurrTime = CurrentTime().GetTime();
					CBusyInterval BusyIntervalToAdd;

					DoGetEnteredInterval(&BusyIntervalToAdd);

					// Максимальный интервал, доступный для задания с помощью
					// DateTimeControls
					/*CInterval MaxInterval;
					DoGetMaxInterval(&MaxInterval);

					CTimeContainer Length = BusyIntervalToAdd.GetLength().GetTime();
						if (m_pActionCombo->GetCurSel() == iEditInterval)
								if (BusyIntervalToAdd.GetFinishTime() < CurrTime)
									BusyIntervalToAdd.SetFinishTime(CurrTime);
						if (m_pActionCombo->GetCurSel() == iNewInterval)
								if (BusyIntervalToAdd.GetStartTime() < CurrTime)
								{
									BusyIntervalToAdd.SetStartTime(CurrTime);
									BusyIntervalToAdd.SetLengthFromStart(Length);

										if (BusyIntervalToAdd.GetFinishTime() > MaxInterval.GetFinishTime())
											BusyIntervalToAdd.SetFinishTime(MaxInterval.GetFinishTime());
								}*/

					BusyIntervalToAdd.SetPrice( m_pState->CalcIntervalPrice(&BusyIntervalToAdd) );
					BusyIntervalToAdd.SetCreationTime(CurrTime);

					int iMashineIndex = m_pMashineCombo->GetCurSel();
					iMashineIndex = m_pMashineCombo->GetItemData(iMashineIndex);

						if ( (iMashineIndex == CB_ERR) )
							return;

					CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[iMashineIndex]);

					CBusyIntervalsCollection* pCollection = pSelectedMashine->GetBusyIntervalsCollection();



					m_pPaybackDialog = new CClientPaybackDialog;
						if (m_pActionCombo->GetCurSel() == iNewInterval)
						{
							m_pPaybackDialog->SetOldBusyInterval(0);
							m_pPaybackDialog->SetNewBusyInterval(&BusyIntervalToAdd);

							// Вызов диалога для расчета с клиентом
							iDialogResult = m_pPaybackDialog->DoModal();
								if (iDialogResult == IDOK)
								{
									pCollection->AddInterval(BusyIntervalToAdd);
									m_pFinantialLogger->WriteBusyIntervals(&BusyIntervalToAdd, 0, pSelectedMashine);
									((CInterfaceApp*)AfxGetApp())->GetActiveDoc()->DoFileSave();
								}
						}
						if (m_pActionCombo->GetCurSel() == iEditInterval)
						{
							int iIntervalIndex = m_pIntervalChoiceCombo->GetCurSel();
								if ( (iIntervalIndex == CB_ERR) )
									return;

							iIntervalIndex = m_pIntervalChoiceCombo->GetItemData(iIntervalIndex);

							CBusyIntervalHist* pHist = &( (*pCollection)[iIntervalIndex] );

							m_pPaybackDialog->SetOldBusyInterval(pHist->GetCurrentInterval());
							m_pPaybackDialog->SetNewBusyInterval(&BusyIntervalToAdd);

							// Вызов диалога для расчета с клиентом
							iDialogResult = m_pPaybackDialog->DoModal();
								if (iDialogResult == IDOK)
								{
									pHist->AddResident(BusyIntervalToAdd);
									m_pFinantialLogger->WriteBusyIntervalHist(pHist, pSelectedMashine);
									((CInterfaceApp*)AfxGetApp())->GetActiveDoc()->DoFileSave();
								}
						}
					m_pView->Invalidate();
				}

				if (iDialogResult == IDOK)
				{
					CDialog::OnOK();
				}
		}
		catch(CAnyLogableException& Error)
		{
				if (m_pPaybackDialog)
				{
					delete m_pPaybackDialog;
					m_pPaybackDialog = 0;
				}

			throw CAnyLogableException((std::string)"An error occured in CNewIntervalDialog::OnOK: " + Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
				if (m_pPaybackDialog)
				{
					delete m_pPaybackDialog;
					m_pPaybackDialog = 0;
				}

			throw CAnyLogableException("An unknown error occured in CNewIntervalDialog::OnOK", bDoNotWriteDuplicates);
		}

		if (m_pPaybackDialog)
		{
			delete m_pPaybackDialog;
			m_pPaybackDialog = 0;
		}
}
// End of OnOK()


void CNewIntervalDialog::OnCancel()
{
	DoUnHighlightInterval();

	CDialog::OnCancel();
}
// End of OnCancel()


void CNewIntervalDialog::DoCalcMaxInterval(CInterval* pReqInterval, CTarifPlan* pPlan)
{
	CTimeStorage CurrTime = CurrentTime();

	pPlan->CalcTarifPlanStartFinish(CurrTime, *pReqInterval);

		if ( (m_pState->GetWorkingInterval()->GetLength() !=
					A_Day.GetTime()) &&
					(m_pState->GetWorkingInterval()->GetFinishTime() <
					pReqInterval->GetFinishTime()) )
		{
			pReqInterval->SetFinishTime(m_pState->GetWorkingInterval()->GetFinishTime());
		}

	// Максимальная длина интервала
	CTimeStorage MaxMaxIntervalLength = A_Day - A_Second;
		if (pReqInterval->GetLength() > MaxMaxIntervalLength)
			pReqInterval->SetLengthFromStart(MaxMaxIntervalLength);
}
// End of DoCalcMaxInterval


void CNewIntervalDialog::DoFillFreeIntervals(CTarifPlan* pPlan, CMashineData* pMashine)
{
	// Интервал, в котором будет происходить поиск свободных интервалов
	CInterval RequiredInterval;
	DoCalcMaxInterval(&RequiredInterval, pPlan);

	// Вместо CTimeStorage((__int64)0) пошли TimeQuant (если знаешь какой)
	m_pFreeIntervals->Clear();
	pMashine->GetBusyIntervalsCollection()->GetFreeIntervals(m_pFreeIntervals, RequiredInterval, CTimeStorage(CTimeContainer(1)));
	// А теперь проверь, чтобы длина интервала не была меньше TimeQuant

	int i = 0;
	CIntervalsStorage<CInterval>::iterator EndIter = m_pFreeIntervals->GetData()->end();
		for (CIntervalsStorage<CInterval>::iterator Iter = m_pFreeIntervals->GetData()->begin();
					Iter != EndIter; ++Iter, ++i)
		{
			DoAddFreeIntervalToCombo(*Iter, i);
		}
}
// End of DoFillFreeIntervals


void CNewIntervalDialog::ClientNameKillFocus()
{
	DoRecalcTotal();
}
// End of ClientNameKillFocus()


void CNewIntervalDialog::LengthMoneyKillFocus()
{
		if (m_pLengthMoneyRadio->GetCheck())
		{
			DoRecalcLengthByPrice();
		}
}
// End of LengthMoneyKillFocus()


void CNewIntervalDialog::DoRecalcLengthByPrice()
{
	// Заданный с помощью DateTimeControls интервал
	CBusyInterval EnteredInterval;
	DoGetEnteredInterval(&EnteredInterval);

	CInterval MaxInterval;
	DoGetMaxInterval(&MaxInterval);

	// Для возвращения интервала на место при редактировании начального
	// времени

	#ifdef _DEBUG
		bool bTest1 = (m_pActionCombo->GetCurSel() == iNewInterval);
		bool bTest2 = (m_pActionCombo->GetCurSel() == iEditInterval);
		//bool bTest3 = pSelectedInterval->GetStartTime().GetTime() > CurrentTime();

		SYSTEMTIME MaxStart, MaxFinish;
		MaxInterval.GetStartTime().GetTime(&MaxStart);
		MaxInterval.GetFinishTime().GetTime(&MaxFinish);
	#endif // _DEBUG

	SYSTEMTIME Time;
		if ( (m_pActionCombo->GetCurSel() == iNewInterval) )
		{
			CTimeStorage Length = EnteredInterval.GetLength();
				if ( (EnteredInterval.GetStartTime() < MaxInterval.GetStartTime()) ||
							(EnteredInterval.GetStartTime() > MaxInterval.GetFinishTime()))
				{
					EnteredInterval.SetStartTime(MaxInterval.GetStartTime());
					EnteredInterval.GetStartTime().GetTime(&Time);
					m_pFromTime->SetTime(&Time);
				}
				if (m_pLengthTimeRadio->GetCheck())
					EnteredInterval.SetLengthFromStart(Length);
		}
		if ( m_pActionCombo->GetCurSel() == iEditInterval )
		{
			CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[m_pMashineCombo->GetItemData(m_pMashineCombo->GetCurSel())]);
			CBusyInterval* pSelectedInterval = ((*pSelectedMashine->GetBusyIntervalsCollection())[m_pIntervalChoiceCombo->GetItemData(m_pIntervalChoiceCombo->GetCurSel())]).GetCurrentInterval();

				#ifdef _DEBUG
					CTimeStorage CurrTime = CurrentTime();
					CTimeStorage Start = pSelectedInterval->GetStartTime().GetTime();
				#endif // _DEBUG

				if (pSelectedInterval->GetStartTime().GetTime() > CurrentTime())
				{
						if ( (EnteredInterval.GetStartTime() < MaxInterval.GetStartTime()) ||
									(EnteredInterval.GetStartTime() > MaxInterval.GetFinishTime()))
						{
							EnteredInterval.SetStartTime(MaxInterval.GetStartTime());
							EnteredInterval.GetStartTime().GetTime(&Time);
							m_pFromTime->SetTime(&Time);
						}
				}
		}

	EnteredInterval.SetFinishTime(MaxInterval.GetFinishTime());

	CCurrency Price = m_pLengthMoney->Convert();

	SYSTEMTIME Start, Finish;
	EnteredInterval.GetStartTime().GetTime(&Start);
	EnteredInterval.GetFinishTime().GetTime(&Finish);

	m_pState->CalcIntervalFinishByPrice(&EnteredInterval, Price);

	SYSTEMTIME Systemtime;
	EnteredInterval.GetLength().GetTime(&Systemtime);
	EnteredInterval.GetLength().TransposeToToday().GetTime(&Systemtime);
	m_pLengthTime->SetTime(&Systemtime);

	DoRecalcTotal(true);
}
// End of DoRecalcLengthByPrice()


void CNewIntervalDialog::OnDTNotify(NMHDR* pNotifyStruct, LRESULT* result)
{
		if (m_pLengthMoneyRadio->GetCheck())
		{
			DoRecalcLengthByPrice();
		}
		if (m_pLengthTimeRadio->GetCheck())
		{
			DoRecalcTotal(true);
		}
}
// End of OnDTNotify


void CNewIntervalDialog::DoRecalcTotal(bool bNormalizationRequired)
{
		if ( (m_pIntervalChoiceCombo->GetCurSel() == CB_ERR) ||
					(m_pTarifCombo->GetCurSel() == CB_ERR) ||
					(m_pMashineCombo->GetCurSel() == CB_ERR) )
		{
			m_pTotalStatic->SetWindowText("");
			m_pAdditionalTotalStatic->SetWindowText("");
			return;
		}

	// Заданный с помощью DateTimeControls интервал
	CBusyInterval EnteredInterval;
	DoGetEnteredInterval(&EnteredInterval);

		if (bNormalizationRequired)
		{
			// Максимальный интервал, доступный для задания с помощью
			// DateTimeControls
			CInterval MaxInterval;
			DoGetMaxInterval(&MaxInterval);

			SYSTEMTIME Time;
				if ( (EnteredInterval.GetStartTime() < MaxInterval.GetStartTime()) ||
							(EnteredInterval.GetStartTime() > MaxInterval.GetFinishTime()))
				{
						if ( (m_pActionCombo->GetCurSel() == iNewInterval) )
						{
							CTimeStorage Length = EnteredInterval.GetLength();
								if ( (EnteredInterval.GetStartTime() < MaxInterval.GetStartTime()) ||
											(EnteredInterval.GetStartTime() > MaxInterval.GetFinishTime()))
								{
									EnteredInterval.SetStartTime(MaxInterval.GetStartTime());
									EnteredInterval.GetStartTime().GetTime(&Time);
									m_pFromTime->SetTime(&Time);
								}
								if (m_pLengthTimeRadio->GetCheck())
									EnteredInterval.SetLengthFromStart(Length);
						}
						if ( m_pActionCombo->GetCurSel() == iEditInterval )
						{
							CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[m_pMashineCombo->GetItemData(m_pMashineCombo->GetCurSel())]);
							CBusyInterval* pSelectedInterval = ((*pSelectedMashine->GetBusyIntervalsCollection())[m_pIntervalChoiceCombo->GetItemData(m_pIntervalChoiceCombo->GetCurSel())]).GetCurrentInterval();

								if (pSelectedInterval->GetStartTime().GetTime() > CurrentTime())
								{
									CTimeStorage Length = EnteredInterval.GetLength();
										if ( (EnteredInterval.GetStartTime() < MaxInterval.GetStartTime()) ||
													(EnteredInterval.GetStartTime() > MaxInterval.GetFinishTime()))
										{
											EnteredInterval.SetStartTime(MaxInterval.GetStartTime());
											EnteredInterval.GetStartTime().GetTime(&Time);
											m_pFromTime->SetTime(&Time);
										}
										if (m_pLengthTimeRadio->GetCheck())
											EnteredInterval.SetLengthFromStart(Length);
								}
						}

					EnteredInterval.GetStartTime().GetTime(&Time);
					m_pFromTime->SetTime(&Time);
				}
				if (EnteredInterval.GetFinishTime() > MaxInterval.GetFinishTime())
				{
					EnteredInterval.SetFinishTime(MaxInterval.GetFinishTime());
					EnteredInterval.GetLength().TransposeToToday().GetTime(&Time);
					m_pLengthTime->SetTime(&Time);
				}
				if (EnteredInterval.GetFinishTime() < CurrentTime())
				{
					EnteredInterval.SetFinishTime(CurrentTime());
					EnteredInterval.GetLength().TransposeToToday().GetTime(&Time);
					m_pLengthTime->SetTime(&Time);
				}
				/*if (EnteredInterval.GetStartTime() < MaxInterval.GetStartTime())
				{
					EnteredInterval.SetStartTime(MaxInterval.GetStartTime());
					EnteredInterval.GetStartTime().TransposeToToday().GetTime(&Time);
					m_pFromTime->SetTime(&Time);
				}*/
		}

	EnteredInterval.SetPrice( m_pState->CalcIntervalPrice(&EnteredInterval) );

	// Заполнение m_pTotalStatic
	CString TempText = "", PriceText = "";

	CString TotalText = "";
	TotalText += IntervalAddition::DescribeInterval_In_Russian(&EnteredInterval).c_str();

	m_pClientNameEdit->GetWindowText(TempText);
	TotalText += ", клиент - ";
	TotalText += TempText;
	TotalText += ",";

	m_pTotalStatic->SetWindowText(TotalText);

	// Заполнение m_pAdditionalTotalStatic
	TotalText = "оператор ";
	TotalText += (*m_pState->GetOperatorsCollection())[EnteredInterval.GetOperatorNumber()].GetName().c_str();

	char cBuffer[100];
	TotalText += ". Цена интервала - ";
	PriceText = _itoa(EnteredInterval.GetPrice(), &(cBuffer[0]), 10);
		if (m_pLengthTimeRadio->GetCheck())
			m_pLengthMoney->SetWindowText(PriceText);
	TotalText += PriceText;
	TotalText += " рублей";

	m_pAdditionalTotalStatic->SetWindowText(TotalText);

	m_pLengthMoney->SetWindowText(PriceText);
}
// End of DoRecalcTotal()


void CNewIntervalDialog::DoGetMaxInterval(CInterval* pMaxInterval)
{
		if (!pMaxInterval)
			return;

	CTimeContainer CurrTime = CurrentTime().GetTime();
		if (m_pActionCombo->GetCurSel() == iNewInterval)
		{
			(*pMaxInterval) = (*m_pFreeIntervals)[m_pIntervalChoiceCombo->GetItemData(m_pIntervalChoiceCombo->GetCurSel())];

			/*CTimeStorage CurrTime = CurrentTime();
			CBusyIntervalsCollection* pCollection = ((*m_pState->GetMashinesCollection())[m_pMashineCombo->GetItemData(m_pMashineCombo->GetCurSel())]).GetBusyIntervalsCollection();
			CBusyInterval* pInterval = *pCollection->GetPreviousInterval();

			CTimeStorage PrevIntervalFinish = ()->GetFinishTime();
				if (CurrTime > PrevIntervalFinish)
					pMaxInterval->SetStartTime(PrevIntervalFinish);
				else
					pMaxInterval->SetStartTime(CurrTime);*/
		}
		if (m_pActionCombo->GetCurSel() == iEditInterval)
		{
			CMashineData* pSelectedMashine = &((*m_pState->GetMashinesCollection())[m_pMashineCombo->GetItemData(m_pMashineCombo->GetCurSel())]);
			CBusyInterval* pSelectedInterval = (*pSelectedMashine->GetBusyIntervalsCollection())[m_pIntervalChoiceCombo->GetItemData(m_pIntervalChoiceCombo->GetCurSel())].GetCurrentInterval();
			CTarifPlan* pSelectedPlan = &((*m_pState->GetTarifPlansCollection())[m_pTarifCombo->GetItemData(m_pTarifCombo->GetCurSel())]);

			DoCalcMaxInterval(pMaxInterval, pSelectedPlan);

			CBusyIntervalsCollection::iterator Iter;
			Iter = pSelectedMashine->GetBusyIntervalsCollection()->GetNextInterval(pSelectedInterval->GetFinishTime());
				if (Iter != pSelectedMashine->GetBusyIntervalsCollection()->GetData()->end())
					pMaxInterval->SetFinishTime((*Iter)->GetStartTime());
			Iter = pSelectedMashine->GetBusyIntervalsCollection()->GetPreviousInterval(pSelectedInterval->GetStartTime());
				if (Iter != pSelectedMashine->GetBusyIntervalsCollection()->GetData()->end())
					pMaxInterval->SetStartTime((*Iter)->GetFinishTime());
		}
}
// End of DoGetMaxInterval


void CNewIntervalDialog::DoGetEnteredInterval(CBusyInterval* pInterval)
{
		if (!pInterval)
			return;

	SYSTEMTIME Time;
	m_pFromTime->GetTime(&Time);
	pInterval->SetStartTime(&Time);

	m_pLengthTime->GetTime(&Time);
	pInterval->SetLengthFromStart(CTimeStorage(&Time).TruncateToDay());

	CString ClientName;
	m_pClientNameEdit->GetWindowText(ClientName);
		if (ClientName != "")
			pInterval->SetClientName(ClientName.operator LPCTSTR());
		else
			pInterval->SetClientName("неизвестный");

	pInterval->SetCreationTime(CurrentTime());

	pInterval->SetOperatorNumber(m_pDialogState->GetOperatorIndex());
	pInterval->SetTarifPlanNumber(m_pTarifCombo->GetItemData(m_pTarifCombo->GetCurSel()));

	// Закомментарено, т.к. неправильно вычислять цену, не выполнив
	// нормализацию
	//pInterval->SetPrice( m_pState->CalcIntervalPrice(pInterval) );
}
// End of DoGetEnteredInterval


void CNewIntervalDialog::DoUnHighlightInterval()
{
		if (m_pPreviouslySelected)
		{
				if (m_pHighlightedColoredCollection)
				{
					m_pHighlightedColoredCollection->DeleteResident(*m_pPreviouslySelected);
					m_pHighlightedColoredCollection = 0;
				}
				else
				{
					m_pPreviouslySelected->SetColor(ciDefaultBusyColor);
				}

			m_pPreviouslySelected = 0;

			m_pView->Invalidate();
		}
}
// End of DoUnHighlightInterval()


void CNewIntervalDialog::OnTimer()
{
		if (m_pPaybackDialog)
		{
			m_pPaybackDialog->OnTimer();
		}
}
// End of OnTimer()
