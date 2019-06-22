#include "stdafx.h"

#include "MultiThreadManager.h"
#include "Exceptions.h"


CMultiThreadManager::CMultiThreadManager()
{
	m_pTimeOutManager = 0;
	m_hCallbackWnd = 0;
	m_bNeedToTerminateThread = 1;
	m_ppManager = 0;
	m_dwAnotherThreadId = 0;

		try
		{
			m_pTimeOutManager = new CTimeOutManager;
			m_pTimeOutManager->OnBegin();
			m_pTimeOutManager->SetEnabled(true);
			// 30 секунд
			m_pTimeOutManager->SetTimeOut(30 * A_Second.GetTime());

			m_hThread = 0;
			m_dwCallbackThreadId = GetCurrentThreadId();
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CMultiThreadManager::CMultiThreadManager: ";
			ErrorString += Error.what();
			DoDeleteEverything();
			throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CMultiThreadManager::CMultiThreadManager", bDoNotWriteDuplicates);
		}
}
// End of CMultiThreadManager()


CMultiThreadManager::CMultiThreadManager(CMultiThreadManager* pManager)
{
	m_pTimeOutManager = 0;

		try
		{
			m_pTimeOutManager = new CTimeOutManager(pManager->GetTimeOutManager());
			//m_pTimeOutManager->SetEnabled(true);
			// 30 секунд
			//m_pTimeOutManager->SetTimeOut(30 * A_Second.GetTime());

			m_hThread = 0;
			m_dwCallbackThreadId = pManager->GetCallbackThreadId();
			m_hCallbackWnd = pManager->GetCallbackWnd();
			m_bNeedToTerminateThread = pManager->m_bNeedToTerminateThread;
			m_ppManager = pManager->m_ppManager;
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CMultiThreadManager::CMultiThreadManager: ";
			ErrorString += Error.what();
			DoDeleteEverything();
			throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CMultiThreadManager::CMultiThreadManager", bDoNotWriteDuplicates);
		}
}
// End of CMultiThreadManager


CMultiThreadManager::~CMultiThreadManager()
{
	TerminateAnotherThread();
	DoDeleteEverything();
}
// End of ~CMultiThreadManager()


void CMultiThreadManager::DoDeleteEverything()
{
		if (m_pTimeOutManager)
		{
			delete m_pTimeOutManager;
			m_pTimeOutManager = 0;
		}
}
// End of DoDeleteEverything()


void CMultiThreadManager::TerminateAnotherThread()
{
		try
		{
				if (m_ppManager)
				{
					*m_ppManager = 0;
					m_ppManager = 0;
				}
				if (m_hThread)
				{
						if (m_bNeedToTerminateThread)
							TerminateThread(m_hThread, 0);

					CloseHandle(m_hThread);
					m_hThread = 0;
				}
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CMultiThreadManager::TerminateAnotherThread", bDoNotWriteDuplicates);
		}
}
// End of TerminateAnotherThread()


void CMultiThreadManager::OnThreadEnded()
{
		if (m_hThread)
		{
			CloseHandle(m_hThread);
			m_hThread = 0;
			m_dwAnotherThreadId = 0;
		}
	m_ppManager = 0;

	OnThreadEndedEvent();
}
// End of OnThreadEnded()


bool CMultiThreadManager::OnTimerEvent()
{
	bool bResult = false;
		if (m_hThread)
		{
				if (bResult = m_pTimeOutManager->IsTimeExpired())
				{
					TerminateAnotherThread();
						/*if (m_bNeedToTerminateThread)
							TerminateThread(m_hThread, 0);*/

					//OnThreadEnded();
				}
		}

	return bResult;
}
// End of OnTimerEvent()


void CMultiThreadManager::StartAnotherThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
			DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
			void* pParameters, DWORD dwCreationFlags)
{
		try
		{
				if (m_hThread)
					return;

				if (m_ppManager)
				{
					*m_ppManager = 0;
					m_ppManager = 0;
				}

			m_pTimeOutManager->OnBegin();

				if (pParameters)
				{
					((CThreadParameters*)pParameters)->SetParentManager(this);
				}

			DWORD dwThreadID;
			HANDLE hThread = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress,
						pParameters, dwCreationFlags, &dwThreadID);
			// Так хитро надо для того, чтобы не было глюка, если второй
			// поток закончит выполнение и обнулит m_hAnotherThread раньше,
			// чем пройдет проверка
			m_hThread = hThread;

				if (!hThread)
							throw CAnyLogableException("can't create thread 8-/", bDoNotWriteDuplicates);
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CMultiThreadManager::StartAnotherThread: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CMultiThreadManager::StartAnotherThread", bDoNotWriteDuplicates);
		}
}
// End of StartAnotherThread


void CMultiThreadManager::OnThreadBegan(CMultiThreadManager** a_ppManager)
{
		if (a_ppManager)
		{
			*a_ppManager = this;
			m_ppManager = a_ppManager;
		}
}
// End of OnThreadBegan
