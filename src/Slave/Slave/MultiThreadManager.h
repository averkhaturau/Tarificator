#ifndef __MULTITHREADMANAGER_H__
#define __MULTITHREADMANAGER_H__

#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"
#include "TimeOutManager.h"


// Predefinition
class CMultiThreadManager;

class CThreadParameters
{
	private:
	protected:
		CMultiThreadManager* m_pParentManager;
	public:
		CThreadParameters()
		{
			m_pParentManager = 0;
		};
		virtual ~CThreadParameters() {};

		// Обертки
		void SetParentManager(CMultiThreadManager* pNewManager) {m_pParentManager = pNewManager;};
		CMultiThreadManager* GetParentManager() {return m_pParentManager;};
};


class CMultiThreadManager
{
	private:
		void DoDeleteEverything();
	protected:
		CTimeOutManager* m_pTimeOutManager;
		// Запущенный поток
		HANDLE m_hThread;
		DWORD m_dwAnotherThreadId;
		// Сюда будет кидаться мессага
		DWORD m_dwCallbackThreadId;
		HWND m_hCallbackWnd;
		// Указатель на локальную переменную в функции второго потока
		CMultiThreadManager** m_ppManager;

		// Вызывается после OnThreadEnded. Нужен для derived
		// class-specific обработки.
		virtual void OnThreadEndedEvent() {};

		bool m_bNeedToTerminateThread;
	public:
		CMultiThreadManager();
		// Копирующий конструктор
		CMultiThreadManager(CMultiThreadManager* pManager);
		virtual ~CMultiThreadManager();

		bool IsTimeExpired();
		void StartAnotherThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
					DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
					void* pParameters, DWORD dwCreationFlags);
		void TerminateAnotherThread();
		void OnThreadEnded();
		// Вызываеатся из функции другого потока. В качестве параметра
		// передается адрес локальной переменной.
		void OnThreadBegan(CMultiThreadManager** a_ppManager);
		// Проверяет Expired и если надо - грохается. Возвращает true,
		// если пришлось убить поток. Если a_bNeedToTerminate, то
		// вызывает TerminateThread. Иначе просто делает CloseHandle
		// и соотв. поток сам завершается. Катит, например, для ConnectProc
		// из CTCP_IP_SocketHolder.
		bool OnTimerEvent();

		// Обертки
		HANDLE GetAnotherThread() {return m_hThread;};
		void SetCallbackThreadId(DWORD dwNew) {m_dwCallbackThreadId = dwNew;};
		DWORD GetCallbackThreadId() {return m_dwCallbackThreadId;};
		CTimeOutManager* GetTimeOutManager() {return m_pTimeOutManager;};
		void SetCallbackWnd(HWND hNew) {m_hCallbackWnd = hNew;};
		HWND GetCallbackWnd() {return m_hCallbackWnd;};
		bool GetNeedToTerminateThread() {return m_bNeedToTerminateThread;};
		void SetNeedToTerminateThread(bool a_bNeedToTerminateThread) {m_bNeedToTerminateThread = a_bNeedToTerminateThread;};
		DWORD GetAnotherThreadId() {return m_dwAnotherThreadId;};
		void SetAnotherThreadId(DWORD a_dwNew) {m_dwAnotherThreadId = a_dwNew;};
};

#endif // __MULTITHREADMANAGER_H__