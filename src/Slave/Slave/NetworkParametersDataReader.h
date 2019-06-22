#ifndef __NETWORKPARAMETERSDATAREADER_H__
#define __NETWORKPARAMETERSDATAREADER_H__


// Predefinitions
class CTCP_IP_SocketHolder;
class CTCP_IP_Sender;
class CTCP_IP_Listener;
class CTCP_IP_Receiver;
class CSlaveTCP_IP_Communicator;

class CNetworkParametersDataReader
{
	private:
	protected:
	public:
		CNetworkParametersDataReader() {};
		virtual ~CNetworkParametersDataReader() {};

		// Читает параметры стандартные для всех SocketHolder'ов данные
		virtual void ReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder) = 0;

		// Читает данные для TCP_IP_Sender'а
		virtual void ReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender) = 0;

		// Читает данные для TCP_IP_Listener'а
		virtual void ReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener) = 0;

		// Читает данные для TCP_IP_Receiver'а
		virtual void ReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pTCP_IP_Receiver) = 0;

		// Читает данные для SocketHolder'а, по которому надо будет
		// коннектиться, т.е. стандартные для всех SocketHolder'ов данные
		// и еще MasterPort и MasterAddress
		virtual void ReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder) = 0;

		// Читает данные для SocketHolder'а, по которому мастер будет
		// коннектиться к slave
		virtual void ReadMasterConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder) = 0;
};


#endif // __NETWORKPARAMETERSDATAREADER_H__