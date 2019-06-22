#ifndef __APPLICATIONWAITER_H__
#define __APPLICATIONWAITER_H__


#include "..\Slave\MultiThreadManager.h"


// Predefinition
class CWaitParameters;

class CApplicationWaiter
{
	private:
		void DoDeleteEverything();
	protected:
		CMultiThreadManager* m_pWaitManager;
		CWaitParameters* m_pWaitParameters;

		// Handle запущенного процесса
		HANDLE m_hProcess;
		// Id главного потока - чтобы ему можно было слать мессаги
		DWORD m_dwThreadId;
	public:
		CApplicationWaiter();
		virtual ~CApplicationWaiter();

		//void OnApplicationEnded();
		void StartWaiting(HANDLE a_hProcess);

		bool operator==(CApplicationWaiter& a_Waiter);

		// Обертки
		HANDLE GetProcess() {return m_hProcess;};
		void SetProcess(HANDLE a_hNew) {m_hProcess = a_hNew;};
		CMultiThreadManager* GetWaitManager() {return m_pWaitManager;};
		void SetThreadId(DWORD a_dwNew) {m_dwThreadId = a_dwNew;};
		DWORD GetThreadId() {return m_dwThreadId;};
};


#endif // __APPLICATIONWAITER_H__