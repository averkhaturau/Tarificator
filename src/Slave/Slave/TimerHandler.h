#ifndef __TIMERHANDLER_H__
#define __TIMERHANDLER_H__


#include "GlobalVariables.h"
#include "SlaveManager.h"
#include "SlaveTPC_IP_Communicator.h"


void CALLBACK TimerFunction(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	// Чтобы залочить комп, если давно на было ответа от мастера
	pSlaveManager->OnTimerEvent();

	// Чтобы убить коммуникационные потоки с истекшим сроком
	pCommunicator->OnTimerEvent();

		/*if ( !(pSlaveManager->GetGlobalLocker()->GetLocked()) )
		{
			pSlaveManager->GetGlobalLocker()->LockEverything();
		}
		else
		{
			pSlaveManager->GetGlobalLocker()->UnLockEverything();
		}*/
};


#endif // __TIMERHANDLER_H__