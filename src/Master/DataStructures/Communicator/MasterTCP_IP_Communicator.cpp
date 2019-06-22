#include "stdafx.h"

#include "MasterTCP_IP_Communicator.h"
#include "..\..\..\Slave\Slave\Exceptions.h"
#include "..\..\..\Slave\Slave\NetworkConstants.h"
#include "..\ClubSettings\RemainingTimeDescription.h"


CMasterTCP_IP_Communicator::~CMasterTCP_IP_Communicator()
{
	DoDeleteEverything();
}
// End of ~CMasterTCP_IP_Communicator()


void CMasterTCP_IP_Communicator::DoDeleteEverything()
{

}
// End of DoDeleteEverything()


void CMasterTCP_IP_Communicator::SendLockOrder(CInterval* pInterval)
{
		if (pInterval)
		{
			CRemainingTimeDescription Description;
			Description.Fill(pInterval, 0);
			DoSendToSlave(WM_LOCK_REQUIRED, (void*)&Description, sizeof(CRemainingTimeDescription));
		}
		else
		{
			DoSendToSlave(WM_LOCK_REQUIRED, 0, 0);
		}
}
// End of SendLockOrder()


void CMasterTCP_IP_Communicator::SendUnLockOrder(CInterval* pInterval, CTarifPlan* pPlan)
{
		if (pInterval)
		{
			CRemainingTimeDescription Description;
			Description.Fill(pInterval, pPlan);
			DoSendToSlave(WM_UNLOCK_REQUIRED, (void*)&Description, sizeof(CRemainingTimeDescription));
		}
		else
		{
			DoSendToSlave(WM_UNLOCK_REQUIRED, 0, 0);
		}
}
// End of SendUnLockOrder()


void CMasterTCP_IP_Communicator::DoSendToSlave(DWORD dwMasterToSlaveMessage, void* pAdditionalData, DWORD dwAdditionalLength)
{
		try
		{
			char cBuffer[dwBufferLength];
			DWORD dwSize = dwBufferLength;

			m_pOutcoming->DoFillPacketContent(dwMasterToSlaveMessage, &(cBuffer[0]), dwSize);

			memcpy(&(cBuffer[dwSize]), pAdditionalData, dwAdditionalLength);
			dwSize += dwAdditionalLength;
				if (dwSize)
					DoSendData(&(cBuffer[0]), dwSize);
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CMasterTCP_IP_Communicator::DoSendToSlave: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CMasterTCP_IP_Communicator::DoSendToSlave", bDoNotWriteDuplicates);
		}
}
// End of DoSendToSlave


void CMasterTCP_IP_Communicator::OnTimerEvent()
{
	m_pAcceptProcManager->OnTimerEvent();
	m_pReceiveManagersCollection->OnTimerEvent();
}
// End of OnTimerEvent()


void CMasterTCP_IP_Communicator::SendTurnoffOrder()
{
	DoSendToSlave(WM_TURNOFF_REQUIRED, 0, 0);
}
// End of SendTurnoffOrder()


void CMasterTCP_IP_Communicator::SendRestartOrder()
{
	DoSendToSlave(WM_RESTART_REQUIRED, 0, 0);
}
// End of SendRestartOrder()
