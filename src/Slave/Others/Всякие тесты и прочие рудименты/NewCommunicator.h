#ifndef __NEWCOMMUNICATOR_H__
#define __NEWCOMMUNICATOR_H__

#include "MultiThreadManager.h"


class CAsyncCommunicator
{
	private:
		void DoDeleteEverything();
	protected:
		CMultiThreadManager* m_pAcceptManager;
		//SOCKET m_AcceptingSocket;
	public:
		CAsyncCommunicator(HINSTANCE a_hInst);
		~CAsyncCommunicator();
};


#endif // __NEWCOMMUNICATOR_H__