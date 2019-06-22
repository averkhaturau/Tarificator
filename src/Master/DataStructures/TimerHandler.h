#ifndef __TIMERHANDLER_H__
#define __TIMERHANDLER_H__


void CALLBACK TimerFunction(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	// Чтобы убить коммуникационные потоки с истекшим сроком
	//pCommunicator->OnTimerEvent();

	// Чтобы залочить комп, если давно на было ответа от мастера
	pMasterManager->OnTimerEvent();

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