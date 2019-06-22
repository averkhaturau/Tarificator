#ifndef __TCP_IP_SOCKETHOLDER_H__
#define __TCP_IP_SOCKETHOLDER_H__

#include "AsyncExchanger.h"
#include "MultiThreadManager.h"
#include "NetworkParametersDataReader.h"
#include "TimeOutManager.h"

#include "Winsock2.h"


// Predefinition
class CTCP_IP_SocketHolder;

class CConnectParameters : public CThreadParameters
{
	private:
	protected:
		// Чтобы взять адрес и т.п.. Ответственность, конечно, снаружи.
		CTCP_IP_SocketHolder* m_pSocketHolder;
	public:
		CConnectParameters() {m_pSocketHolder = 0;};
		virtual ~CConnectParameters() {};

		// Обертки
		void SetSocketHolder(CTCP_IP_SocketHolder* pNewHolder) {m_pSocketHolder = pNewHolder;};
		CTCP_IP_SocketHolder* GetSocketHolder() {return m_pSocketHolder;};
};


class CTCP_IP_SocketHolder : virtual public CAsyncExchanger
{
	friend DWORD WINAPI ConnectProc(void* pParam);

	private:
		void DoDeleteEverything();
		void DoInitEverything();
	protected:
		// true, если сейчас идет коннект. Нужен, чтобы различать
		// тайм-аут m_pConnectManager и m_pOpenConnectionManager.
		//bool m_bConnecting;
		SOCKET m_Socket;
		// Адрес для коннекта
		DWORD m_dwAddressToConnectTo;
		// Адрес порта в host byte order
		u_short m_usPortToConnectTo;
		CMultiThreadManager* m_pConnectManager;
		CConnectParameters m_Parameters;
		// Учитывается внутри. Если не истекло время с последнего запуска
		// коннекта - просто ничего не делает при вызове DoConnectTo.
		CTimeOutManager* m_pConnectionRetriesManager;
		// Чтобы открытое соединение (возможно неработающее) не висело
		// слишком долго
		CTimeOutManager* m_pOpenConnectionManager;

		void DoPostConnectNotification(DWORD dwCallbackThreadID, SOCKET Socket, int Result);
	public:
		CTCP_IP_SocketHolder();
		CTCP_IP_SocketHolder(CTCP_IP_SocketHolder* pHolder);
		CTCP_IP_SocketHolder(CNetworkParametersDataReader* pNetworkDataReader);
		virtual ~CTCP_IP_SocketHolder();

		void DoConnectTo();
		void CloseSocket();

		void OnTimerEvent();
		// Возвращает IP сокета в host byte order
		DWORD ObtainIP();

		// Обертки
		SOCKET GetSocket() const {return m_Socket;};
		void SetSocket(SOCKET NewSocket) {m_Socket = NewSocket;};
		DWORD GetAddressToConnectTo() const {return m_dwAddressToConnectTo;};
		void SetAddressToConnectTo(DWORD dwNew) {m_dwAddressToConnectTo = dwNew;};
		u_short GetPortToConnectTo() const {return m_usPortToConnectTo;};
		void SetPortToConnectTo(u_short usNew) {m_usPortToConnectTo = usNew;};
		CMultiThreadManager* GetConnectManager() {return m_pConnectManager;};
		CTimeOutManager* GetConnectionRetriesManager() {return m_pConnectionRetriesManager;};
		CTimeOutManager* GetOpenConnectionManager() {return m_pOpenConnectionManager;};
};


#endif // __TCP_IP_SOCKETHOLDER_H__