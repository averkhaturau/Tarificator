#include "stdafx.h"
#include "Interface.h"
#include "MashineLineControl.h"


BEGIN_MESSAGE_MAP(CMashineLineControl, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


CMashineLineControl::CMashineLineControl()
{
	m_pMashineData = 0;

	m_pIntervalsLineControl = 0;
	m_pMashineNameControl = 0;
	m_pMashineStatusControl = 0;

	m_dwIntervalsLength = 200;
	m_dwNameLength = 100;
	m_dwStatusLength = 100;
	m_dwTarifLength = 100;

	try{
		m_pIntervalsLineControl = new CIntervalsLineControl;
		m_pMashineNameControl = new CMashineNameControl;
		m_pMashineStatusControl = new CMashineStatusControl;

	}catch(...){
		DoDeleteEverything();
		throw CAnyLogableException("An unknown error occured in CMashineLineControl::CMashineLineControl", bDoNotWriteDuplicates);
	}
}
// End of CMashineLineControl()


CMashineLineControl::~CMashineLineControl()
{
	DoDeleteEverything();
}
// End of ~CMashineLineControl()


void CMashineLineControl::DoDeleteEverything()
{
	if (m_pIntervalsLineControl)
	{
		delete m_pIntervalsLineControl;
		m_pIntervalsLineControl = 0;
	}

	if (m_pMashineNameControl)
	{
		delete m_pMashineNameControl;
		m_pMashineNameControl = 0;
	}

	if (m_pMashineStatusControl)
	{
		delete m_pMashineStatusControl;
		m_pMashineStatusControl =0 ;
	}
}
// End of DoDeleteEverything()


int CMashineLineControl::OnCreate(LPCREATESTRUCT pCreateStruct)
{
	bool bError = false;

	try{

		if (!m_pMashineData)
			return -1;

		if ( DoCreateLine(m_pIntervalsLineControl) != 0 )// Ошибка
			bError = true;
		SetIntervalsLength(m_dwIntervalsLength);
		m_pIntervalsLineControl->SetMashineLineControl(this);

		if ( DoCreateLine(m_pMashineNameControl) != 0 )	// Ошибка
			bError = true;
		SetNameLength(m_dwNameLength);

		if ( DoCreateLine(m_pMashineStatusControl) != 0 )// Ошибка
			bError = true;
		SetStatusLength(m_dwStatusLength);
		m_pMashineStatusControl->SetMashineLineControl(this);

		//if ( DoCreateLine(m_pMashinePlanControl) != 0 )
		//	bError = true;
		//SetPlanLength(m_dwTarifLength);

		RefreshLineData();

	}catch(CAnyLogableException &e){
		((CInterfaceApp*)AfxGetApp())->GetErrorsLogger()->AddLogEntry(&e);
	}catch(...){
		((CInterfaceApp*)AfxGetApp())->GetErrorsLogger()->AddLogEntry("Error in creating MashinelineControl", bDoNotWriteDuplicates);
	}

	if (bError)
		return -1;
	else
		return 0;
}
// End of OnCreate


int CMashineLineControl::DoCreateLine(CLineControl* pLine)
{
	// Создаю новый Line
	int iResult = pLine->CreateEx(
		0, // Window Style
		"LineControl", // Имя зарегистрированного класса контрола
		"", // Window Name
		WS_CHILD | WS_VISIBLE, //Styles
		CRect(0, 0, 0, 0),
		this, // Parent
		0 // ID
	);

	if (iResult)
		// Все ОК
		return 0;
	else
		// Что-то не так
		return -1;
}
// End of DoCreateLine


void CMashineLineControl::SetIntervalsLength(DWORD dwNew)
{
	m_dwIntervalsLength = dwNew;

	try{
		if (! m_pIntervalsLineControl->m_hWnd)
			return;

		CRect ClientRect;
		GetClientRect(&ClientRect);
		m_pIntervalsLineControl->SetWindowPos(NULL, m_dwNameLength - 1, 0,
					m_dwIntervalsLength + 1, ClientRect.bottom, 0);

		ChoseWidthAccodingToAttributes();

	}catch(CAnyLogableException){
		throw;
	}catch(...){
		throw CAnyLogableException("SetIntervalsLength(DWORD dwNew)", bDoNotWriteDuplicates);
	}
}
// End of SetIntervalsLength


void CMashineLineControl::SetNameLength(DWORD dwNew)
{
	m_dwNameLength = dwNew;

	try{
		if (!m_pMashineNameControl->m_hWnd)
			return;

		CRect ClientRect;
		GetClientRect(&ClientRect);
		m_pMashineNameControl->SetWindowPos(NULL, 0, 0,
				m_dwNameLength, ClientRect.bottom, 0);

		ChoseWidthAccodingToAttributes();

	}catch(CAnyLogableException){
		throw;
	}catch(...){
		throw CAnyLogableException("SetNameLength(DWORD dwNew)", bDoNotWriteDuplicates);
	}
}
// End of SetNameLength


void CMashineLineControl::SetStatusLength(DWORD dwNew)
{
	m_dwStatusLength = dwNew;

	try{
		if (!m_pMashineStatusControl->m_hWnd)
			return;

		CRect ClientRect;
		GetClientRect(&ClientRect);
		m_pMashineStatusControl->SetWindowPos(NULL,
			m_dwNameLength + m_dwIntervalsLength - 1, 0,
			m_dwStatusLength + 1, ClientRect.bottom, 0);

		ChoseWidthAccodingToAttributes();

	}catch(CAnyLogableException){
		throw;
	}catch(...){
		throw CAnyLogableException("SetStatusLength(DWORD dwNew)", bDoNotWriteDuplicates);
	}
}
// End of SetStatusLength

void CMashineLineControl::ChoseWidthAccodingToAttributes()
{
	try{
		if (m_hWnd)
		{
			CRect WindowRect;
			GetWindowRect(&WindowRect);

			ScreenToClient(&WindowRect);
			MapWindowPoints(GetParent(), &WindowRect);

			WindowRect.right = WindowRect.left + m_dwIntervalsLength +
						m_dwStatusLength + m_dwNameLength;

			SetWindowPos(NULL, WindowRect.left, WindowRect.top,
						WindowRect.Width(), WindowRect.Height(), 0);
		}
	}catch(...){
		throw CAnyLogableException("Error in CMashineLineControl::ChoseWidthAccodingToAttributes()", bDoNotWriteDuplicates);
	};
}

void CMashineLineControl::SetMashineData(CMashineData* pNew)
{
	try{
		m_pMashineData = pNew;
		RefreshLineData();

	}catch(CAnyLogableException &e){
		((CInterfaceApp*)AfxGetApp())->GetErrorsLogger()->AddLogEntry(&e);
	}catch(...){
		((CInterfaceApp*)AfxGetApp())->GetErrorsLogger()->AddLogEntry("Error in SetMashineData", bDoNotWriteDuplicates);
	}
}

void CMashineLineControl::RefreshLineData()
{
	try{
		if (m_pMashineData && GetIntervalsLineControl()->m_hWnd)
		{
			(*m_pMashineNameControl->GetMashineName()) =
				(m_pMashineData->GetMashineName());

			*GetIntervalsLineControl()->GetIntervalsCollection() = 
				*m_pMashineData->GetBusyIntervalsCollection();

		}// if (m_pMashineData)

	}catch(CAnyLogableException &e){
 		throw CAnyLogableException(CString((CString)"RefreshLineData failed: "
			+ (CString)e.what()).operator LPCTSTR(), e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("RefreshLineData failed", bDoNotWriteDuplicates);
	}
}