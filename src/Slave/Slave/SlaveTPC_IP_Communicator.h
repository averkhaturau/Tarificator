#ifndef __SLAVETCP_IP_COMMUNICATOR_H__
#define __SLAVETCP_IP_COMMUNICATOR_H__

#include "TCP_IP_Sender.h"
#include "TCP_IP_Listener.h"
#include "TCP_IP_Receiver.h"
#include "TCP_IP_Class.h"
#include "SlaveCommunicator.h"
#include "Exceptions.h"


class CSlaveTCP_IP_Communicator : public CSlaveCommunicator,
			public CTCP_IP_Sender, public CTCP_IP_Listener,
			public CTCP_IP_Receiver, virtual public CTCP_IP_Class
{
	// Конкретный класс, умеющий посылать конкректные данные конкретным
	// образом

	private:
		void DoDeleteEverything();
	protected:
		CTCP_IP_SocketHolder* m_pAcceptedSocketHolder;
		CTCP_IP_SocketHolder* m_pConnectedSocketHolder;

		void DoSendToMaster(DWORD dwSlaveToMasterMessage);
	public:
		// Конструктор
		CSlaveTCP_IP_Communicator(CNetworkParametersDataReader* pDataReader) :
					CTCP_IP_Class(pDataReader), CTCP_IP_Sender(pDataReader),
					CTCP_IP_Listener(pDataReader), CTCP_IP_Receiver(pDataReader)
		{
			m_pAcceptedSocketHolder = 0;
			m_pConnectedSocketHolder = 0;

				try
				{
					// Тут недостаточно прочитать Common параметры - надо еще и
					// специфичные для connect
					m_pConnectedSocketHolder = new CTCP_IP_SocketHolder;
					pDataReader->ReadSlaveConnectedSocketHolder(m_pConnectedSocketHolder);

					// Тут достаточно прочитать Common параметры
					m_pAcceptedSocketHolder = new CTCP_IP_SocketHolder(pDataReader);

					m_pReceiveManagersCollection->resize(5);
					m_pReceiverParamsCollection->resize(5);
				}
				catch(CAnyLogableException)
				{
					DoDeleteEverything();
					throw;
				}
				catch(...)
				{
					DoDeleteEverything();
					throw CAnyLogableException("An unknown error occured in CSlaveTCP_IP_Communicator::CSlaveTCP_IP_Communicator", bDoNotWriteDuplicates);
				}
		};

		// Деструктор
		virtual ~CSlaveTCP_IP_Communicator();

		// Посылает подтверждение о залочке машины
		virtual void SendLockSuccess();
		// Посылает подтверждение об отлочке машины
		virtual void SendUnLockSuccess();
		// Посылает уведомление о неуспехе залочки машины
		virtual void SendLockFail();
		// Посылает уведомление о неуспехе отлочки машины
		virtual void SendUnLockFail();
		// Посылает запрос на повторную посылку состояния машины
		virtual void SendReCheckState();

		void CloseSocket(SOCKET& SocketToClose);

		void OnTimerEvent();

		// Обертки
		CTCP_IP_SocketHolder* GetAcceptedSocketHolder() {return m_pAcceptedSocketHolder;};
		CTCP_IP_SocketHolder* GetConnectedSocketHolder() {return m_pConnectedSocketHolder;};
};


#endif // __SLAVETCP_IP_COMMUNICATOR_H__