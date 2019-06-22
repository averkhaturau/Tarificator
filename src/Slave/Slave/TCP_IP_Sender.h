#ifndef __TCP_IP_SENDER_H__
#define __TCP_IP_SENDER_H__

#include "Winsock2.h"

#include "Sender.h"
#include "MultiThreadManager.h"
#include "ManagersCollection.h"
#include "NetworkParametersDataReader.h"
#include "TCP_IP_Class.h"


class CTCP_IP_Sender : public CSender, virtual public CTCP_IP_Class
{
	// ���������� ����� ��� ������� ������ ������ �� TCP/IP

	private:
		void DoDeleteEverything();
		// ��������������� - �������. �� ����� ������ ��� ����������
		// ������������. ����� ����� ������� ��� �������������
		// INVAlID_SOCKET.
		SOCKET m_SocketToSendTo;
	protected:
	public:
		// �����������
		CTCP_IP_Sender(CNetworkParametersDataReader* pNetworkDataReader);
		// ����������
		virtual ~CTCP_IP_Sender();

		// ������� �������� ������
		virtual void DoSendData(char* pData, DWORD dwSize);

		// �������
		void SetSocketToSendTo(SOCKET NewSocket) {m_SocketToSendTo = NewSocket;};
		SOCKET GetSocketToSendTo() {return m_SocketToSendTo;};
};


#endif // __TCP_IP_SENDER_H__