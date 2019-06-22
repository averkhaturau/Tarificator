#ifndef __MANAGER_H__
#define __MANAGER_H__


#include <string>

#include "ErrorsLogger.h"
#include "Constants.h"
#include "TimeOutManager.h"
//#include "MultiThreadedDesktopEmulator.h"
#include "NewUserDefiner.h"
#include "InvertedTimeOutManager.h"
#include "SlaveSoundManager.h"
#include "..\Desktop\RemainingTimeSlaveDescription.h"
#include "ApplicationInfosCollection.h"
#include "SessionTimeOutCollection.h"

//#include "Windows.h"



class CSlaveManager
{
	public:
		typedef void CALLBACK CTimerProcedure(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);

	private:
		void DoDeleteEverything();
	protected:
		// ����� ����� ���� ������� ������� � RegisterService �
		// ������� �����������
		typedef DWORD CALLBACK RegisterProcess(DWORD, DWORD);

		HANDLE m_hMutex;
		UINT m_uiSlaveTimerPeriod;
		// ������
		UINT_PTR m_uiSlaveTimerIdentifier;
		// �������� �� ������ ������� � ���������� ������������� ��
		// �������, ��� ���� ������ ��������
		CTimeOutManager* m_pPermissionManager;
		// �������� �� ������������� ������� ��������� slave � �������
		CTimeOutManager* m_pCheckStateManager;
		// �������� �� ������ ������� �� ������������������������ �������.
		// ����������� ��� ������ �������� � ��������.
		CInvertedTimeOutManager* m_pAssumedFinishManager;
		CInvertedTimeOutManager m_EarlyWarnManager, m_LateWarnManager;
		// �������� ������������ �������� Windows
		//CDesktopEmulator* m_pDesktopEmulator;
		//CMultiThreadedDesktopEmulator* m_pMultiThreadedDesktopEmulator;
		CNewUserDefiner* m_pNewUserDefiner;
		CRemainingTimeSlaveDescription m_Remaining;
		CSlaveSoundManager* m_pSoundManager;
		bool m_bMustBeLocked;
		bool m_bWasLocked;
		bool m_bDesktopCreatedSuccessfully;
		// Instance ����������
		HINSTANCE m_hInstance;
		std::string m_sDesktopExecutablePath;
		CApplicationInfosCollection* m_pDesktopInfosCollection;
		CNamesCollection* m_pSuperUsersNamesCollection;
		CSessionTimeOutCollection* m_pTimeOutCollection;

		// ���������� true, ���� a_dwSession ���� ���������
		bool DoTerminateInproperSessions(DWORD a_dwSessionId = 0);
		void DoAllowLogon(LPTSTR a_pName, bool a_bAllow);
		void CheckForAllowOrDisallow(LPTSTR a_pName);
	public:
		// �����������. hInstance ����� ��� �������� � �����������
		// CMultiThreadMessageBox
		CSlaveManager(HINSTANCE hInstance, CSlaveDataReader* pSlaveDataReader, CErrorsLogger* pErrorsLogger);
		// ����������
		~CSlaveManager();

		// ����������� ������� ��� service, ����� ��� Win9x ��� �� ����
		// � TaskList �� ctrl-alt-del
		void RegisterService();
		// ���� ��������� ������ ����������� - ������ ������� mutex �
		// ������ ��� handle � m_hMutex. ���� ���� ��������, �.�. ����
		// ��������� ��� �������� - ������� exception.
		void CheckMutex(const char* cMutexName);
		void StartTimer(CTimerProcedure* Procedure);
		void OnTimerEvent();
		void OnNewUserLogged();
		void UpdateExchangeData();
		void RestartWindows();
		void TurnOffComputer();

		// �������
		void SetTimerPeriod(UINT uiNew) {m_uiSlaveTimerPeriod = uiNew;};
		UINT GetTimerPeriod() {return m_uiSlaveTimerPeriod;};
		CTimeOutManager* GetPermissionManager() {return m_pPermissionManager;};
		CTimeOutManager* GetCheckStateManager() {return m_pCheckStateManager;};
		CInvertedTimeOutManager* GetAssumedFinishManager() {return m_pAssumedFinishManager;};
		CInvertedTimeOutManager* GetEarlyWarnManager() {return &m_EarlyWarnManager;};
		CInvertedTimeOutManager* GetLateWarnManager() {return &m_LateWarnManager;};
		void SetMustBeLocked(bool bNew) {m_bMustBeLocked = bNew;};
		bool GetMustBeLocked() {return m_bMustBeLocked;};
		//CMultiThreadedDesktopEmulator* GetMultiThreadedDesktopEmulator() {return m_pMultiThreadedDesktopEmulator;};
		HINSTANCE GetInstance() {return m_hInstance;};
		CRemainingTimeSlaveDescription* GetRemainingTime() {return &m_Remaining;};
		CSlaveSoundManager* GetSoundManager() {return m_pSoundManager;};
		std::string* GetDesktopExecutablePath() {return &m_sDesktopExecutablePath;};
		CApplicationInfosCollection* GetDesktopInfosCollection() {return m_pDesktopInfosCollection;};
		CNamesCollection* GetSuperUsersNamesCollection() {return m_pSuperUsersNamesCollection;};
};


#endif // __MANAGER_H__