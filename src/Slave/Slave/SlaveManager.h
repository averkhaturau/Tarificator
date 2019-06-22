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
		// Чтобы можно было вызвать функцию в RegisterService с
		// нужными параметрами
		typedef DWORD CALLBACK RegisterProcess(DWORD, DWORD);

		HANDLE m_hMutex;
		UINT m_uiSlaveTimerPeriod;
		// Таймер
		UINT_PTR m_uiSlaveTimerIdentifier;
		// Отвечает за отсчет времени с последнего подтверждения от
		// мастера, что комп должен работать
		CTimeOutManager* m_pPermissionManager;
		// Отвечает за периодичность запроса состояния slave у мастера
		CTimeOutManager* m_pCheckStateManager;
		// Отвечает за отсчет времени до предполагаемогоокончания времени.
		// Обновляется при каждом коннекте с мастером.
		CInvertedTimeOutManager* m_pAssumedFinishManager;
		CInvertedTimeOutManager m_EarlyWarnManager, m_LateWarnManager;
		// Эмулятор стандартного десктопа Windows
		//CDesktopEmulator* m_pDesktopEmulator;
		//CMultiThreadedDesktopEmulator* m_pMultiThreadedDesktopEmulator;
		CNewUserDefiner* m_pNewUserDefiner;
		CRemainingTimeSlaveDescription m_Remaining;
		CSlaveSoundManager* m_pSoundManager;
		bool m_bMustBeLocked;
		bool m_bWasLocked;
		bool m_bDesktopCreatedSuccessfully;
		// Instance приложения
		HINSTANCE m_hInstance;
		std::string m_sDesktopExecutablePath;
		CApplicationInfosCollection* m_pDesktopInfosCollection;
		CNamesCollection* m_pSuperUsersNamesCollection;
		CSessionTimeOutCollection* m_pTimeOutCollection;

		// Возвращает true, если a_dwSession была завершена
		bool DoTerminateInproperSessions(DWORD a_dwSessionId = 0);
		void DoAllowLogon(LPTSTR a_pName, bool a_bAllow);
		void CheckForAllowOrDisallow(LPTSTR a_pName);
	public:
		// Конструктор. hInstance нужен для передачи в конструктор
		// CMultiThreadMessageBox
		CSlaveManager(HINSTANCE hInstance, CSlaveDataReader* pSlaveDataReader, CErrorsLogger* pErrorsLogger);
		// Деструктор
		~CSlaveManager();

		// Реситрирует процесс как service, чтобы под Win9x его не было
		// в TaskList по ctrl-alt-del
		void RegisterService();
		// Если программа должна выполняться - просто создает mutex и
		// хранит его handle в m_hMutex. Если надо выходить, т.е. один
		// экземпляр уже работает - генерит exception.
		void CheckMutex(const char* cMutexName);
		void StartTimer(CTimerProcedure* Procedure);
		void OnTimerEvent();
		void OnNewUserLogged();
		void UpdateExchangeData();
		void RestartWindows();
		void TurnOffComputer();

		// Обертки
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