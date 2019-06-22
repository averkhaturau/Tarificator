#include "stdafx.h"

#include "TCP_IP_Sender.h"
#include "Exceptions.h"
#include "Messages.h"


CTCP_IP_Sender::CTCP_IP_Sender(CNetworkParametersDataReader* pNetworkDataReader) :
			CTCP_IP_Class(pNetworkDataReader)
{
	m_SocketToSendTo = INVALID_SOCKET;
}
// End of CTCP_IP_Sender()


CTCP_IP_Sender::~CTCP_IP_Sender()
{
	DoDeleteEverything();
}
// End of ~CTCP_IP_Sender()


void CTCP_IP_Sender::DoDeleteEverything()
{

}
// End of DoDeleteEverything()


void CTCP_IP_Sender::DoSendData(char* pData, DWORD dwSize)
{
		try
		{
			send(m_SocketToSendTo, pData, dwSize, 0);
			m_SocketToSendTo = INVALID_SOCKET;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CTCP_IP_Sender::DoSendData", bDoNotWriteDuplicates);
		}
}
// End of DoSendData
