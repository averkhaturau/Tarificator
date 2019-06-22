#ifndef __MASTER_TCP_IP_COMMUNICATOR_H__
#define __MASTER_TCP_IP_COMMUNICATOR_H__

#include "MasterCommunicator.h"
#include "..\..\..\Slave\Slave\Exceptions.h"
#include "..\..\..\Slave\Slave\TCP_IP_Sender.h"
#include "..\..\..\Slave\Slave\TCP_IP_Receiver.h"
#include "..\..\..\Slave\Slave\TCP_IP_Listener.h"
#include "..\..\..\Slave\Slave\TCP_IP_SocketHolder.h"
#include "..\..\..\Slave\Slave\TCP_IP_Class.h"


class CMasterTCP_IP_Communicator : virtual public CTCP_IP_Class,
			public CMasterCommunicator, public CTCP_IP_Sender,
			public CTCP_IP_Receiver, public CTCP_IP_Listener
{
	private:
		void DoDeleteEverything();
	protected:
		// “акже передаютс€ доп. данные - чтобы можно было указать Slave,
		// сколько ему осталось
		void DoSendToSlave(DWORD dwMasterToSlaveMessage, void* pAdditionalData, DWORD dwAdditionalLength);
	public:
		CMasterTCP_IP_Communicator(CNetworkParametersDataReader* pStorer) :
					CTCP_IP_Class(pStorer), CTCP_IP_Sender(pStorer),
					CTCP_IP_Receiver(pStorer), CTCP_IP_Listener(pStorer)
		{
				try
				{
					// ѕотом они им еще сделаетс€ resize с учетом кол-ва машин
					m_pReceiveManagersCollection->resize(100);
					m_pReceiverParamsCollection->resize(100);
				}
				catch(CAnyLogableException& Error)
				{
					DoDeleteEverything();
					std::string ErrorString = "An error occured in CMasterTCP_IP_Communicator::CMasterTCP_IP_Communicator: ";
					ErrorString += Error.what();
					throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
				}
				catch(...)
				{
					DoDeleteEverything();
					throw CAnyLogableException("An unknown error occured in CMasterTCP_IP_Communicator::CMasterTCP_IP_Communicator", bDoNotWriteDuplicates);
				}
		};
		virtual ~CMasterTCP_IP_Communicator();

		// ѕосылает приказ о закрытии машины
		virtual void SendLockOrder(CInterval* pInterval);
		// ѕосылает приказ об открытии машины
		virtual void SendUnLockOrder(CInterval* pInterval, CTarifPlan* pPlan);
		virtual void SendTurnoffOrder();
		virtual void SendRestartOrder();

		void OnTimerEvent();
};


#endif // __MASTER_TCP_IP_COMMUNICATOR_H__