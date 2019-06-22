#include "stdafx.h"

#include "TCP_IP_Listener.h"
#include "Exceptions.h"
#include "Messages.h"


// Свободные функции
DWORD WINAPI AcceptProc(void* pParam)
{
	CTCP_IP_ListenerParameters* pParameters = (CTCP_IP_ListenerParameters*)pParam;

	CMultiThreadManager* pManager = 0;
		if (pParameters)
			pParameters->GetParentManager()->OnThreadBegan(&pManager);

		try
		{
			SOCKET AcceptedSocket = INVALID_SOCKET;
			SOCKADDR_IN accept_sin;
			int accept_sin_len = sizeof(accept_sin);

				while(true)
				{
						if (pManager)
							AcceptedSocket = accept(pParameters->GetListener()->GetSocketToListen(),
										(struct sockaddr*) &accept_sin, (int*) &accept_sin_len);
						else
							break;

						if ( (AcceptedSocket != INVALID_SOCKET) )
						{
								/*if (pParameters->GetParentManager()->GetCallbackThreadId())
								{
									PostThreadMessage(pParameters->GetParentManager()->GetCallbackThreadId(), WM_CONNECTIONACCEPTED, (DWORD)AcceptedSocket, 0);
								}*/
								if (pManager)
									pParameters->GetListener()->DoPostAcceptNotification(
												pManager->GetCallbackThreadId(),
												AcceptedSocket);
						}
				}
		}
		catch(...)
		{

		}

		if (pManager)
			pManager->OnThreadEnded();

	return 0;
}
// End of AcceptProc
// Конец свободных функций


CTCP_IP_Listener::CTCP_IP_Listener(CNetworkParametersDataReader* pNetworkDataReader)
{
	m_SocketToListen = INVALID_SOCKET;
	m_pAcceptProcManager = 0;

		try
		{
			//m_pParameters = new CTCP_IP_ListenerParameters;

				if (pNetworkDataReader)
					pNetworkDataReader->ReadTCP_IP_ListenerData(this);

			m_SocketToListen = socket(AF_INET, SOCK_STREAM, 0);
				if (m_SocketToListen == INVALID_SOCKET)
				{
					throw CAnyLogableException("allocating socket failed 8-/", bDoNotWriteDuplicates);
				}

			SOCKADDR_IN local_sin;
			local_sin.sin_family = AF_INET;
			local_sin.sin_port = htons(m_usPortToListen);
			local_sin.sin_addr.s_addr = htonl(INADDR_ANY);

			int iResult = bind(m_SocketToListen, (struct sockaddr*)&local_sin, sizeof(local_sin));
				if (iResult == SOCKET_ERROR)
				{
					throw CAnyLogableException("can't bind socket", bDoNotWriteDuplicates);
				}

			iResult = listen (m_SocketToListen, SOMAXCONN);
				if (iResult == SOCKET_ERROR)
				{
					throw CAnyLogableException("can't place the socket to the listening state", bDoNotWriteDuplicates);
				}

			m_pAcceptProcManager = new CMultiThreadManager;
			m_pAcceptProcManager->SetNeedToTerminateThread(false);
			m_pAcceptProcManager->GetTimeOutManager()->SetEnabled(false);

			m_Parameters.SetListener(this);
			m_Parameters.SetParentManager(m_pAcceptProcManager);

			m_pAcceptProcManager->StartAnotherThread(NULL, 0, AcceptProc,
						&m_Parameters, 0);
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();

			std::string ErrorString = "An error occured in CTCP_IP_Listener::CTCP_IP_Listener: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();

			throw CAnyLogableException("An unknown error occured in CTCP_IP_Listener::CTCP_IP_Listener", bDoNotWriteDuplicates);
		}
}
// End of CTCP_IP_Listener()


CTCP_IP_Listener::~CTCP_IP_Listener()
{
	DoDeleteEverything();
}
// End of ~CTCP_IP_Listener()


void CTCP_IP_Listener::DoDeleteEverything()
{
		if (m_pAcceptProcManager)
		{
			delete m_pAcceptProcManager;
			m_pAcceptProcManager = 0;
		}
		if (m_SocketToListen != INVALID_SOCKET)
		{
			closesocket(m_SocketToListen);
			m_SocketToListen = INVALID_SOCKET;
		}
}
// End of DoDeleteEverything()


void CTCP_IP_Listener::DoPostAcceptNotification(DWORD dwCallbackThreadID, SOCKET AcceptedSocket)
{
	DoPostThreadMessage(dwCallbackThreadID, WM_CONNECTIONACCEPTED, (DWORD)AcceptedSocket, 0);
}
// End of DoPostAcceptNotification
