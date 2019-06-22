#include "stdafx.h"

#include "SlaveTPC_IP_Communicator.h"
#include "Exceptions.h"
#include "MasterMessages.h"
#include "NetworkConstants.h"


CSlaveTCP_IP_Communicator::~CSlaveTCP_IP_Communicator()
{
	DoDeleteEverything();
}
// End of ~CSlaveTCP_IP_Communicator()


void CSlaveTCP_IP_Communicator::DoDeleteEverything()
{
		if (m_pAcceptedSocketHolder)
		{
			delete m_pAcceptedSocketHolder;
			m_pAcceptedSocketHolder = 0;
		}
		if (m_pConnectedSocketHolder)
		{
			delete m_pConnectedSocketHolder;
			m_pConnectedSocketHolder = 0;
		}
}
// End of DoDeleteEverything()


void CSlaveTCP_IP_Communicator::SendLockSuccess()
{
	DoSendToMaster(WM_LOCK_SUCCESS_ACKNOWLEDGE);
}
// End of SendLockAcknowledgement()


void CSlaveTCP_IP_Communicator::SendUnLockSuccess()
{
	DoSendToMaster(WM_UNLOCK_SUCCESS_ACKNOWLEDGE);
}
// End of SendUnLockAcknowledgement()


void CSlaveTCP_IP_Communicator::SendLockFail()
{
	DoSendToMaster(WM_LOCK_FAIL_ACKNOWLEDGE);
}
// End of SendLockFail()


void CSlaveTCP_IP_Communicator::SendUnLockFail()
{
	DoSendToMaster(WM_UNLOCK_FAIL_ACKNOWLEDGE);
}
// End of SendUnLockFail()


void CSlaveTCP_IP_Communicator::SendReCheckState()
{
	DoSendToMaster(WM_RE_CHECK_STATE_REQUEST);
}
// End of SendReCheckState()


void CSlaveTCP_IP_Communicator::OnTimerEvent()
{
	m_pAcceptProcManager->OnTimerEvent();
	m_pReceiveManagersCollection->OnTimerEvent();
	m_pAcceptedSocketHolder->OnTimerEvent();
	m_pConnectedSocketHolder->OnTimerEvent();
}
// End of OnTimerEvent()


void CSlaveTCP_IP_Communicator::DoSendToMaster(DWORD dwSlaveToMasterMessage)
{
		try
		{
			char cBuffer[dwBufferLength];
			DWORD dwSize = dwBufferLength;

			m_pOutcoming->DoFillPacketContent(dwSlaveToMasterMessage, &(cBuffer[0]), dwSize);

				if (dwSize)
				{
					DoSendData(&(cBuffer[0]), dwSize);
				}
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CSlaveTCP_IP_Communicator::DoSendToMaster: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CSlaveTCP_IP_Communicator::DoSendToMaster", bDoNotWriteDuplicates);
		}
}
// End of DoSendToMaster


void CSlaveTCP_IP_Communicator::CloseSocket(SOCKET& SocketToClose)
{
		if (SocketToClose != INVALID_SOCKET)
		{
			closesocket(SocketToClose);
			SocketToClose = INVALID_SOCKET;
		}
}
// End of CloseSocket
