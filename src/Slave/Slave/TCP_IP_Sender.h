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
	// Конкретный класс для посылки данных именно по TCP/IP

	private:
		void DoDeleteEverything();
		// Ответственность - снаружи. Он нужен только для сохранения
		// полиморфизма. Сразу после посылки ему присваивается
		// INVAlID_SOCKET.
		SOCKET m_SocketToSendTo;
	protected:
	public:
		// Конструктор
		CTCP_IP_Sender(CNetworkParametersDataReader* pNetworkDataReader);
		// Деструктор
		virtual ~CTCP_IP_Sender();

		// Функция передачи данных
		virtual void DoSendData(char* pData, DWORD dwSize);

		// Обертки
		void SetSocketToSendTo(SOCKET NewSocket) {m_SocketToSendTo = NewSocket;};
		SOCKET GetSocketToSendTo() {return m_SocketToSendTo;};
};


#endif // __TCP_IP_SENDER_H__