#include "stdafx.h"

#include "ApplicationWaiter.h"
#include "..\Slave\Exceptions.h"
#include "..\Slave\Messages.h"



class CWaitParameters : public CThreadParameters
{
	private:
	protected:
		// Чтобы туда сообщать. Ответственность снаружи.
		CApplicationWaiter* m_pApplicationWaiter;
	public:
		CWaitParameters() {m_pApplicationWaiter = 0;};
		virtual ~CWaitParameters() {};

		// Обертки
		void SetApplicationWaiter(CApplicationWaiter* a_pNew) {m_pApplicationWaiter = a_pNew;};
		CApplicationWaiter* GetApplicationWaiter() {return m_pApplicationWaiter;};
};





// Свободные функции
DWORD WINAPI WaitProc(void* pParam)
{
	CWaitParameters* pParameters = (CWaitParameters*)pParam;

	CMultiThreadManager* pManager = 0;
		if (pParameters)
				if (pParameters->GetApplicationWaiter())
						if (pParameters->GetApplicationWaiter()->GetWaitManager())
							pParameters->GetApplicationWaiter()->GetWaitManager()->OnThreadBegan(&pManager);

	HANDLE hInst = pParameters->GetApplicationWaiter()->GetProcess();

		try
		{
				if (pManager)
						if (hInst)
						{
								if ( WaitForSingleObject(hInst, INFINITE)
											== WAIT_OBJECT_0 )
								{
										if (pManager)
										{
											//pParameters->GetApplicationWaiter()->OnApplicationEnded();
											LPARAM lp = (LPARAM)pParameters->GetApplicationWaiter();
												if (pManager->GetCallbackThreadId())
												{
													PostThreadMessage(pManager->GetCallbackThreadId(),
																WM_WAITED_APPLICATION_ENDED, (WPARAM)pManager, lp);
												}
										}
								}
							CloseHandle(hInst);
							hInst = 0;
						}
		}
		catch(...)
		{

		}

		if (pManager)
			pManager->OnThreadEnded();

	return 0;
}
// End of WaitProc
// Конец свободных функций






CApplicationWaiter::CApplicationWaiter()
{
	m_pWaitManager = 0;
	m_pWaitParameters = 0;
	m_hProcess = 0;
	m_dwThreadId = 0;

		try
		{
			m_pWaitManager = new CMultiThreadManager();
			m_pWaitManager->SetNeedToTerminateThread(false);

			m_pWaitParameters = new CWaitParameters();
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CApplicationWaiter::CApplicationWaiter()", bDoNotWriteDuplicates);
		}
}
// End of CApplicationWaiter()


CApplicationWaiter::~CApplicationWaiter()
{
	DoDeleteEverything();
}
// End of ~CApplicationWaiter()


void CApplicationWaiter::DoDeleteEverything()
{
		if (m_pWaitManager)
		{
			delete m_pWaitManager;
			m_pWaitManager = 0;
		}
		if (m_pWaitParameters)
		{
			delete m_pWaitParameters;
			m_pWaitParameters = 0;
		}
}
// End of DoDeleteEverything()


void CApplicationWaiter::StartWaiting(HANDLE a_hProcess)
{
		if (!a_hProcess)
		{
			PostThreadMessage(GetCurrentThreadId(),
						WM_WAITED_APPLICATION_ENDED, (WPARAM)m_pWaitManager, 0);
			return;
		}

	SetProcess(a_hProcess);

	m_pWaitParameters->SetApplicationWaiter(this);
	m_pWaitParameters->SetParentManager(m_pWaitManager);

	m_pWaitManager->SetCallbackThreadId(GetCurrentThreadId());
	m_pWaitManager->StartAnotherThread(NULL, 0, WaitProc,
						m_pWaitParameters, 0);
}
// End of StartWaiting


bool CApplicationWaiter::operator==(CApplicationWaiter& a_Waiter)
{
	return ( (m_hProcess == a_Waiter.m_hProcess) &&
				(m_dwThreadId == a_Waiter.m_dwThreadId) );
}
// End of operator==
