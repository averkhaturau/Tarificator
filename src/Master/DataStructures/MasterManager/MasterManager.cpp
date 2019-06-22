// MasterManager.cpp: implementation of the CMasterManager class.
//

#include "stdafx.h"
#include "MasterManager.h"
//#include "..\..\Logon\SSPLogon.h"


CMasterManager::CMasterManager(CMasterBoundStorer* pStorer)
{
	m_pClubState = 0;
	m_pCommunicator = 0;
	m_uiMasterTimerPeriod = 0;
	m_uiMasterTimerIdentifier = 0;
	m_pCashdesk = 0;

	//	проинициализируем всё
	try{
		m_pClubState = new CClubState(pStorer);
		m_pCommunicator = new CMasterTCP_IP_Communicator(pStorer);
		m_pCashdesk = new CCashdesk(pStorer);

		DWORD dwSize = m_pClubState->GetMashinesCollection()->size();
		m_pCommunicator->GetReceiveManagersCollection()->resize(5 * dwSize);
		m_pCommunicator->GetReceiverParamsCollection()->resize(5 * dwSize);

		pStorer->ReadMasterManager(this);

	}catch(CAnyLogableException){
		DoDeleteEverything();
		throw;
	}catch(...){
		DoDeleteEverything();
		throw CAnyLogableException("An unknown error occured in CMasterManager::CMasterManager", bDoNotWriteDuplicates);
	}
}
// End of CMasterManager()


CMasterManager::~CMasterManager()
{
	DoDeleteEverything();
}
// End of ~CMasterManager()


void CMasterManager::DoDeleteEverything()
{
	if (m_pCashdesk)
	{
		delete m_pCashdesk;
		m_pCashdesk = 0;
	}
	if (m_pClubState)
	{
		delete m_pClubState;
		m_pClubState = 0;
	}
	if (m_pCommunicator)
	{
		delete m_pCommunicator;
		m_pCommunicator = 0;
	}
}
// End of DoDeleteEverything()


void CMasterManager::StartTimer(CTimerProcedure* Procedure)
{
	// Чтобы вызывать по таймеру функцию TimerFunction
	m_uiMasterTimerIdentifier = SetTimer(NULL, 0, m_uiMasterTimerPeriod, Procedure);
		if (!m_uiMasterTimerIdentifier)
			throw CAnyLogableException("Can't create timer", bDoNotWriteDuplicates);
}
// End of StartTimer


void CMasterManager::OnTimerEvent()
{
	m_pCommunicator->OnTimerEvent();
	m_pClubState->GetMashinesCollection()->OnTimerEvent();
}
// End of OnTimerEvent()