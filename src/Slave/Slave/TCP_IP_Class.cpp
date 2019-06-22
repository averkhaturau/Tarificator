#include "stdafx.h"

#include "TCP_IP_Class.h"
#include "Exceptions.h"

#include "Winsock2.h"
#include <string>


CTCP_IP_Class::CTCP_IP_Class(CNetworkParametersDataReader* pReader)
{
	WSADATA WSAData;
	int iResult = WSAStartup(MAKEWORD(2,0), &WSAData);
		if (iResult)
		{
			std::string ErrorString = "an error occured while initializing WinSocket: ";

				switch (iResult)
				{
					case WSASYSNOTREADY:
						ErrorString += "underlying network subsystem is not ready for network communication (may be TCP/IP protocol is not installed)";
					break;

					case WSAVERNOTSUPPORTED:
						ErrorString += "the version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation (version 2.0 required)";
					break;

					case WSAEINPROGRESS:
						ErrorString += "a blocking Windows Sockets 1.1 operation is in progress";
					break;

					case WSAEPROCLIM:
						ErrorString += "limit on the number of tasks supported by the Windows Sockets implementation has been reached";
					break;

					case WSAEFAULT:
						ErrorString += "the lpWSAData is not a valid pointer 8-/";
					break;
				}

			throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
		}
}
// End of CTCP_IP_Class()


CTCP_IP_Class::~CTCP_IP_Class()
{
	DoDeleteEverything();

	WSACleanup();

		//if (WSACleanup())
			//throw CAnyLogableException("An error occured in CTCP_IP_Class::~CTCP_IP_Class: can't terminate using WinSockets 8-/", bDoNotWriteDuplicates);
}
// End of ~CTCP_IP_Class()


void CTCP_IP_Class::DoDeleteEverything()
{

}
// End of DoDeleteEverything()
