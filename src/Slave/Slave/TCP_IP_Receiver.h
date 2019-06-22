#ifndef __TCP_IP_RECEIVER_H__
#define __TCP_IP_RECEIVER_H__

#include "Receiver.h"
#include "NetworkParametersDataReader.h"
#include "ReceiveManagersCollection.h"
#include "ReceiverParamsCollection.h"
#include "TCP_IP_Class.h"

#include "Winsock2.h"


// ����������� ������ ������ �� TCP/IP
class CTCP_IP_Receiver : public CReceiver, virtual public CTCP_IP_Class
{
	private:
		void DoDeleteEverything();
	protected:
		CReceiveManagersCollection* m_pReceiveManagersCollection;
		CReceiverParamsCollection* m_pReceiverParamsCollection;
		// ���� �� TimeOut � ����������
		bool m_bHasReceiveTimeOut;
		// �������� TimeOut'a
		UINT m_uiReceiveTimeOut;
		// ��������������� - �������. �� ����� ������ ��� ����������
		// ������������. ����� ����� ������� ������ ��� �������������
		// INVAlID_SOCKET.
		SOCKET m_SocketToReceiveFrom;
	public:
		// ����������� � ��������� �������� ������
		CTCP_IP_Receiver(CNetworkParametersDataReader* pNetworkDataReader);
		// ����������
		virtual ~CTCP_IP_Receiver();

		void DoReceive(DWORD dwSize);

		// �������
		CReceiveManagersCollection* GetReceiveManagersCollection() {return m_pReceiveManagersCollection;};
		CReceiverParamsCollection* GetReceiverParamsCollection() {return m_pReceiverParamsCollection;};
		bool GetHasReceiveTimeOut() {return m_bHasReceiveTimeOut;};
		void SetHasReceiveTimeOut(bool bNew) {m_bHasReceiveTimeOut = bNew;};
		UINT GetReceiveTimeOut() {return m_uiReceiveTimeOut;};
		void SetReceiveTimeOut(UINT uiNew) {m_uiReceiveTimeOut = uiNew;};
		void SetSocketToReceiveFrom(SOCKET NewSocket) {m_SocketToReceiveFrom = NewSocket;};
		SOCKET GetSocketToReceiveFrom() {return m_SocketToReceiveFrom;};
};


#endif // __TCP_IP_RECEIVER_H__