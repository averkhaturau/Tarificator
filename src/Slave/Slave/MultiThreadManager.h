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

		// �������
		void SetParentManager(CMultiThreadManager* pNewManager) {m_pParentManager = pNewManager;};
		CMultiThreadManager* GetParentManager() {return m_pParentManager;};
};


class CMultiThreadManager
{
	private:
		void DoDeleteEverything();
	protected:
		CTimeOutManager* m_pTimeOutManager;
		// ���������� �����
		HANDLE m_hThread;
		DWORD m_dwAnotherThreadId;
		// ���� ����� �������� �������
		DWORD m_dwCallbackThreadId;
		HWND m_hCallbackWnd;
		// ��������� �� ��������� ���������� � ������� ������� ������
		CMultiThreadManager** m_ppManager;

		// ���������� ����� OnThreadEnded. ����� ��� derived
		// class-specific ���������.
		virtual void OnThreadEndedEvent() {};

		bool m_bNeedToTerminateThread;
	public:
		CMultiThreadManager();
		// ���������� �����������
		CMultiThreadManager(CMultiThreadManager* pManager);
		virtual ~CMultiThreadManager();

		bool IsTimeExpired();
		void StartAnotherThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
					DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
					void* pParameters, DWORD dwCreationFlags);
		void TerminateAnotherThread();
		void OnThreadEnded();
		// ����������� �� ������� ������� ������. � �������� ���������
		// ���������� ����� ��������� ����������.
		void OnThreadBegan(CMultiThreadManager** a_ppManager);
		// ��������� Expired � ���� ���� - ���������. ���������� true,
		// ���� �������� ����� �����. ���� a_bNeedToTerminate, ��
		// �������� TerminateThread. ����� ������ ������ CloseHandle
		// � �����. ����� ��� �����������. �����, ��������, ��� ConnectProc
		// �� CTCP_IP_SocketHolder.
		bool OnTimerEvent();

		// �������
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