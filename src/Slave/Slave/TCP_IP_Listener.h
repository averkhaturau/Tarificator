#ifndef __TCP_IP_LISTENER_H__
#define __TCP_IP_LISTENER_H__

#include "Winsock2.h"

#include "ManagersCollection.h"
#include "NetworkParametersDataReader.h"
#include "Listener.h"


// Predefinition
class CTCP_IP_Listener;

class CTCP_IP_ListenerParameters : public CThreadParameters
{
	private:
	protected:
		// ����� ����� ������ ����� � �.�.
		CTCP_IP_Listener* m_pListener;
	public:
		CTCP_IP_ListenerParameters() {m_pListener = 0;};
		virtual ~CTCP_IP_ListenerParameters() {};

		// �������
		void SetListener(CTCP_IP_Listener* pNew) {m_pListener = pNew;};
		CTCP_IP_Listener* GetListener() {return m_pListener;};
};


// �� ���� ������ ���� �������� ��������� ����� �������������
class CTCP_IP_Listener : public CListener
{
	friend DWORD WINAPI AcceptProc(void* pParam);

	private:
		void DoDeleteEverything();
	protected:
		SOCKET m_SocketToListen;
		// ���� ��� ������������� � host byte order
		u_short m_usPortToListen;
		CMultiThreadManager* m_pAcceptProcManager;
		CTCP_IP_ListenerParameters m_Parameters;

		// �������� ����������� �� �������� Accept
		void DoPostAcceptNotification(DWORD dwCallbackThreadID, SOCKET AcceptedSocket);
	public:
		// ����������� �� ���������
		// ��� ��������� ���, ��� ���� ��� ��������� �����
		CTCP_IP_Listener(CNetworkParametersDataReader* pNetworkDataReader);
		// ����������
		virtual ~CTCP_IP_Listener();

		// �������
		void SetPortToListen(u_short usNew) {m_usPortToListen = usNew;};
		u_short GetPortToListen() {return m_usPortToListen;};
		SOCKET GetSocketToListen() {return m_SocketToListen;};
};


#endif // __TCP_IP_LISTENER_H__