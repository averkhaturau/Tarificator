#include "stdafx.h"

#include "TCP_IP_SocketHolder.h"
#include "Exceptions.h"
#include "Messages.h"


// Свободные функции
DWORD WINAPI ConnectProc(void* pParam)
{
	CConnectParameters* pParameters = (CConnectParameters*)pParam;

	CMultiThreadManager* pManager = 0;
		if (pParameters)
			pParameters->GetParentManager()->OnThreadBegan(&pManager);

	int iResult;
		try
		{
			// Для отладки
			/*bool bFlag = false;
				if (pParameters->GetSocketHolder()->GetAddressToConnectTo() == 0xc0a80001)
				{
					bFlag = true;
				}*/

			SOCKADDR_IN Connect_sin;
			Connect_sin.sin_family = AF_INET;
			Connect_sin.sin_port = htons(pParameters->GetSocketHolder()->GetPortToConnectTo());
			DWORD dwAddress = htonl(pParameters->GetSocketHolder()->GetAddressToConnectTo());
			memcpy((char FAR *)&(Connect_sin.sin_addr), &dwAddress, sizeof(DWORD));

			iResult = connect(pParameters->GetSocketHolder()->GetSocket(),
						(PSOCKADDR) &Connect_sin, sizeof(Connect_sin));
		}
		catch(...)
		{
			iResult = SOCKET_ERROR;
		}

		try
		{
				if (iResult == SOCKET_ERROR)
				{
						if (pManager)
						{
							pParameters->GetSocketHolder()->DoPostConnectNotification(
										pManager->GetCallbackThreadId(), 0, iResult);
						}
				}
				else
				{
						if (pManager)
						{
							pParameters->GetSocketHolder()->GetOpenConnectionManager()->OnBegin();
							pParameters->GetSocketHolder()->DoPostConnectNotification(
										pManager->GetCallbackThreadId(),
										pParameters->GetSocketHolder()->GetSocket(), iResult);
						}
				}

				if (pManager)
					pManager->OnThreadEnded();
		}
		catch(...)
		{

		}

	return 0;
}
// End of ConnectProc
// Конец свободных функций


CTCP_IP_SocketHolder::CTCP_IP_SocketHolder(CNetworkParametersDataReader* pNetworkDataReader)
{
	m_Socket = INVALID_SOCKET;
	m_pConnectManager = 0;
	m_dwAddressToConnectTo = 0;
	m_usPortToConnectTo = 0;
	m_pConnectionRetriesManager = 0;
	m_pOpenConnectionManager = 0;

		try
		{
			m_pConnectManager = new CMultiThreadManager;
			m_pConnectManager->SetNeedToTerminateThread(false);

			m_pConnectionRetriesManager = new CTimeOutManager;
			//m_pConnectionRetriesManager->OnBegin();

			m_pOpenConnectionManager = new CTimeOutManager;
			m_pOpenConnectionManager->OnBegin();
			
				if (pNetworkDataReader)
					pNetworkDataReader->ReadCommonTCP_IP_SocketHolderData(this);
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();
			std::string ErrorString = "An error occured in CTCP_IP_SocketHolder::CTCP_IP_SocketHolder: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CTCP_IP_SocketHolder::CTCP_IP_SocketHolder", bDoNotWriteDuplicates);
		}
}
// End of CTCP_IP_SocketHolder


CTCP_IP_SocketHolder::CTCP_IP_SocketHolder()
{
	m_Socket = INVALID_SOCKET;
	m_pConnectManager = 0;
	m_dwAddressToConnectTo = 0;
	m_usPortToConnectTo = 0;
	m_pConnectionRetriesManager = 0;
	m_pOpenConnectionManager = 0;

		try
		{
			m_pConnectManager = new CMultiThreadManager;
			m_pConnectManager->SetNeedToTerminateThread(false);

			m_pConnectionRetriesManager = new CTimeOutManager;
			//m_pConnectionRetriesManager->OnBegin();

			m_pOpenConnectionManager = new CTimeOutManager;
			m_pOpenConnectionManager->OnBegin();
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();
			std::string ErrorString = "An error occured in CTCP_IP_SocketHolder::CTCP_IP_SocketHolder: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CTCP_IP_SocketHolder::CTCP_IP_SocketHolder", bDoNotWriteDuplicates);
		}
}
// End of CTCP_IP_SocketHolder()


CTCP_IP_SocketHolder::CTCP_IP_SocketHolder(CTCP_IP_SocketHolder* pHolder)
{
	m_Socket = INVALID_SOCKET;
	m_pConnectManager = 0;
	m_dwAddressToConnectTo = 0;
	m_usPortToConnectTo = 0;
	m_pConnectionRetriesManager = 0;
	m_pOpenConnectionManager = 0;

		try
		{
			m_dwAddressToConnectTo = pHolder->GetAddressToConnectTo();
			m_usPortToConnectTo = pHolder->GetPortToConnectTo();

			m_pConnectManager = new CMultiThreadManager(pHolder->GetConnectManager());
			m_pConnectManager->SetNeedToTerminateThread(false);

			m_pConnectionRetriesManager = new CTimeOutManager;
			//m_pConnectionRetriesManager->OnBegin();

			m_pOpenConnectionManager = new CTimeOutManager;
			m_pOpenConnectionManager->OnBegin();
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();
			std::string ErrorString = "An error occured in CTCP_IP_SocketHolder::CTCP_IP_SocketHolder: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CTCP_IP_SocketHolder::CTCP_IP_SocketHolder", bDoNotWriteDuplicates);
		}
}
// End of CTCP_IP_SocketHolder


CTCP_IP_SocketHolder::~CTCP_IP_SocketHolder()
{
	DoDeleteEverything();
}
// End of ~CTCP_IP_SocketHolder()


void CTCP_IP_SocketHolder::DoDeleteEverything()
{
		if (m_pConnectManager)
		{
			delete m_pConnectManager;
			m_pConnectManager = 0;
		}
		if (m_pConnectionRetriesManager)
		{
			delete m_pConnectionRetriesManager;
			m_pConnectionRetriesManager = 0;
		}
		if (m_pOpenConnectionManager)
		{
			delete m_pOpenConnectionManager;
			m_pOpenConnectionManager = 0;
		}

	CloseSocket();
}
// End of DoDeleteEverything()


void CTCP_IP_SocketHolder::CloseSocket()
{
		if (m_Socket != INVALID_SOCKET)
		{
			closesocket(m_Socket);
			m_Socket = INVALID_SOCKET;
		}
}
// End of DoCloseSocket()


void CTCP_IP_SocketHolder::DoConnectTo()
{
		//if ( !(m_pConnectManager->GetAnotherThread()) )
		//{
				if ( m_pConnectionRetriesManager->IsTimeExpired() )
				{
					m_pConnectManager->TerminateAnotherThread();
					CloseSocket();

					m_Socket = socket(AF_INET, SOCK_STREAM, 0);
						if (m_Socket == INVALID_SOCKET)
						{
							throw CAnyLogableException("allocating socket failed 8-/", bDoNotWriteDuplicates);
						}

					m_Parameters.SetSocketHolder(this);
					m_Parameters.SetParentManager(m_pConnectManager);

					m_pConnectionRetriesManager->OnBegin();
					m_pOpenConnectionManager->OnBegin();
					m_pConnectManager->StartAnotherThread(NULL, 0, &ConnectProc,
								&m_Parameters, 0);
				}
		//}
}
// End of DoConnectTo()


void CTCP_IP_SocketHolder::DoPostConnectNotification(DWORD dwCallbackThreadID, SOCKET Socket, int Result)
{
	DoPostThreadMessage(dwCallbackThreadID, WM_CONNECTED, (LPARAM)Socket, Result);
}
// End of DoPostConnectNotification


void CTCP_IP_SocketHolder::OnTimerEvent()
{
		if ( m_pConnectManager->OnTimerEvent() )
		{
			CloseSocket();
		}

		if ( m_pOpenConnectionManager->IsTimeExpired() )
		{
			CloseSocket();
		}
}
// End of OnTimerEvent()


DWORD CTCP_IP_SocketHolder::ObtainIP()
{
	SOCKADDR_IN TheAddress;
	int iLength = sizeof(sockaddr);
	getpeername(m_Socket, (PSOCKADDR)&TheAddress, &iLength);

	return ntohl(TheAddress.sin_addr.S_un.S_addr);
}
// End of ObtainIP()
