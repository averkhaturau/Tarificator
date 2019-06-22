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
		// Чтобы взять оттуда сокет и т.п.
		CTCP_IP_Listener* m_pListener;
	public:
		CTCP_IP_ListenerParameters() {m_pListener = 0;};
		virtual ~CTCP_IP_ListenerParameters() {};

		// Обертки
		void SetListener(CTCP_IP_Listener* pNew) {m_pListener = pNew;};
		CTCP_IP_Listener* GetListener() {return m_pListener;};
};


// На этом классе надо замешать серверный класс коммуникатора
class CTCP_IP_Listener : public CListener
{
	friend DWORD WINAPI AcceptProc(void* pParam);

	private:
		void DoDeleteEverything();
	protected:
		SOCKET m_SocketToListen;
		// Порт для прослушивания в host byte order
		u_short m_usPortToListen;
		CMultiThreadManager* m_pAcceptProcManager;
		CTCP_IP_ListenerParameters m_Parameters;

		// Посылает уведомление об успешном Accept
		void DoPostAcceptNotification(DWORD dwCallbackThreadID, SOCKET AcceptedSocket);
	public:
		// Конструктор по умолчанию
		// Тут создается все, что надо для прослушки порта
		CTCP_IP_Listener(CNetworkParametersDataReader* pNetworkDataReader);
		// Деструктор
		virtual ~CTCP_IP_Listener();

		// Обертки
		void SetPortToListen(u_short usNew) {m_usPortToListen = usNew;};
		u_short GetPortToListen() {return m_usPortToListen;};
		SOCKET GetSocketToListen() {return m_SocketToListen;};
};


#endif // __TCP_IP_LISTENER_H__