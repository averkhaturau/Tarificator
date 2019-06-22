#ifndef __TIMERHANDLER_H__
#define __TIMERHANDLER_H__


#include "GlobalVariables.h"
#include "SlaveManager.h"
#include "SlaveTPC_IP_Communicator.h"


void CALLBACK TimerFunction(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	// ����� �������� ����, ���� ����� �� ���� ������ �� �������
	pSlaveManager->OnTimerEvent();

	// ����� ����� ���������������� ������ � �������� ������
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