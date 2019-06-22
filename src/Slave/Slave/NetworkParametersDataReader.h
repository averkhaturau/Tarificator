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

		// ������ ��������� ����������� ��� ���� SocketHolder'�� ������
		virtual void ReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder) = 0;

		// ������ ������ ��� TCP_IP_Sender'�
		virtual void ReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender) = 0;

		// ������ ������ ��� TCP_IP_Listener'�
		virtual void ReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener) = 0;

		// ������ ������ ��� TCP_IP_Receiver'�
		virtual void ReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pTCP_IP_Receiver) = 0;

		// ������ ������ ��� SocketHolder'�, �� �������� ���� �����
		// ������������, �.�. ����������� ��� ���� SocketHolder'�� ������
		// � ��� MasterPort � MasterAddress
		virtual void ReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder) = 0;

		// ������ ������ ��� SocketHolder'�, �� �������� ������ �����
		// ������������ � slave
		virtual void ReadMasterConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder) = 0;
};


#endif // __NETWORKPARAMETERSDATAREADER_H__