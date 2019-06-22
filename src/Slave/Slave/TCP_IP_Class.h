#ifndef __TCP_IP_CLASS_H__
#define __TCP_IP_CLASS_H__

#include "TCP_IP_SocketHolder.h"


// Обеспечивает инициализацию TCP/IP. От него наследуются все
// конкретные классы, работающие с TCP/IP.
class CTCP_IP_Class
{
	private:
		void DoDeleteEverything();
	protected:
	public:
		// Конструктор. Тут инициализируются WinSockets для приложения
		CTCP_IP_Class(CNetworkParametersDataReader* pReader);
		// Деструктор. Тут убиваются WinSockets для данного приложения
		virtual ~CTCP_IP_Class();
};


#endif // __TCP_IP_CLASS_H__