#include "stdafx.h"

#include "TCP_IP_Receiver.h"
#include "Exceptions.h"


// Свободные функции
DWORD WINAPI ReceiveProc(void* pParam)
{
	CReceiveParameters* pParameters = (CReceiveParameters*)pParam;

	CMultiThreadManager* pManager = 0;
		if (pParameters)
			pParameters->GetParentManager()->OnThreadBegan(&pManager);

	SOCKET SocketToReceiveFrom = pParameters->GetSocket();
	char* pBuffer = pParameters->GetBuffer();
	DWORD dwSize = pParameters->GetSize();
	int iReturn = 0;

	CTCP_IP_SocketHolder TempSocketHolder;
	TempSocketHolder.SetSocket(SocketToReceiveFrom);
	DWORD dwIP = TempSocketHolder.ObtainIP();
	TempSocketHolder.SetSocket(INVALID_SOCKET);

		try
		{
			iReturn = recv(SocketToReceiveFrom, pBuffer, dwSize, 0);
		}
		catch(...)
		{
		}

		if (iReturn != SOCKET_ERROR)
		{
			CTCP_IP_SocketHolder TempSocketHolder;
			TempSocketHolder.SetSocket(SocketToReceiveFrom);
			DWORD dwIP = TempSocketHolder.ObtainIP();
			TempSocketHolder.SetSocket(INVALID_SOCKET);

				if (pManager)
				{
					pParameters->GetReceiver()->DoPostReceiveNotification(
								pManager->GetCallbackThreadId(),
								pParameters, iReturn);
				}
		}
		else
		{
		}

		if (pManager)
			pManager->OnThreadEnded();

	return 0;
}
// End of ReceiveProc
// Конец свободных функций


CTCP_IP_Receiver::CTCP_IP_Receiver(CNetworkParametersDataReader* pNetworkDataReader) :
			CTCP_IP_Class(pNetworkDataReader)
{
	m_pReceiveManagersCollection = 0;
	m_SocketToReceiveFrom = INVALID_SOCKET;

		try
		{
			m_pReceiveManagersCollection = new CReceiveManagersCollection;

			m_pReceiverParamsCollection = new CReceiverParamsCollection;

				if (pNetworkDataReader)
					pNetworkDataReader->ReadTCP_IP_ReceiverData(this);
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CTCP_IP_Receiver::CTCP_IP_Receiver: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CTCP_IP_Receiver::CTCP_IP_Receiver (may be not enough memory)", bDoNotWriteDuplicates);
		}
}
// End of CTCP_IP_Receiver


CTCP_IP_Receiver::~CTCP_IP_Receiver()
{
	DoDeleteEverything();
}
// End of ~CTCP_IP_Receiver()


void CTCP_IP_Receiver::DoDeleteEverything()
{
		if (m_pReceiveManagersCollection)
		{
			delete m_pReceiveManagersCollection;
			m_pReceiveManagersCollection = 0;
		}
		if (m_pReceiverParamsCollection)
		{
			delete m_pReceiverParamsCollection;
			m_pReceiverParamsCollection = 0;
		}
}
// End of DoDeleteEverything()


void CTCP_IP_Receiver::DoReceive(DWORD dwSize)
{
		if (m_SocketToReceiveFrom == INVALID_SOCKET)
			throw CAnyLogableException("Invalid Socket to receive from in CTCP_IP_Receiver::DoReceive", bDoNotWriteDuplicates);

		try
		{
			CReceiveMultiThreadManager* pManager = m_pReceiveManagersCollection->GetFreeManager();
			CReceiveParameters* pParameters = m_pReceiverParamsCollection->GetFreeParams();
				if ( (pManager) && (pParameters) )
				{
					pParameters->SetParentManager(pManager);
					pParameters->SetReceiver(this);
					pParameters->SetUsed(true);
					pParameters->SetSocket(m_SocketToReceiveFrom);
					pParameters->GetVectorBuffer()->resize(dwSize);

					pManager->GetTimeOutManager()->SetEnabled(m_bHasReceiveTimeOut);
					pManager->GetTimeOutManager()->SetTimeOut(A_Second.GetTime() * (m_uiReceiveTimeOut / 1000));
					pManager->SetReceiveParameters(pParameters);
					pManager->StartAnotherThread(NULL, 0, ReceiveProc,
						pParameters, 0);
					m_SocketToReceiveFrom = INVALID_SOCKET;
				}
		}
		catch(...)
		{
			throw;
		}
}
// End of DoReceive
