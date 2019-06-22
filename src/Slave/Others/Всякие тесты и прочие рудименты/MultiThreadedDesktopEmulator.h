#ifndef __MULTITHREADEDDESKTOPEMULATOR_H__
#define __MULTITHREADEDDESKTOPEMULATOR_H__


#include "DesktopEmulator.h"
#include "..\Slave\MultiThreadManager.h"


// Predefinition
class CMultiThreadedDesktopEmulator;

class CMultiThreadedDesktopEmulatorParameters : public CThreadParameters
{
	private:
	protected:
		// Чтобы взять оттуда сокет и т.п.
		CMultiThreadedDesktopEmulator* m_pMultiThreadedDesktopEmulator;
		HINSTANCE m_hInstance;
		std::string m_sUserName;
		CRemainingTimeSlaveDescription* m_pRemaining;
		HANDLE m_hImpersonatingToken;
		HANDLE m_hPrimaryToken;
	public:
		CMultiThreadedDesktopEmulatorParameters() {m_pMultiThreadedDesktopEmulator = 0;};
		virtual ~CMultiThreadedDesktopEmulatorParameters() {};

		// Обертки
		void SetMultiThreadedDesktopEmulator(CMultiThreadedDesktopEmulator* pNew) {m_pMultiThreadedDesktopEmulator = pNew;};
		CMultiThreadedDesktopEmulator* GetMultiThreadedDesktopEmulator() {return m_pMultiThreadedDesktopEmulator;};
		HINSTANCE GetInstance() {return m_hInstance;};
		void SetInstance(HINSTANCE a_hNew) {m_hInstance = a_hNew;};
		std::string* GetUserName() {return &m_sUserName;};
		CRemainingTimeSlaveDescription* GetRemaining() {return m_pRemaining;};
		void SetRemaining(CRemainingTimeSlaveDescription* a_pNew) {m_pRemaining = a_pNew;};
		HANDLE GetImpersonatingToken() {return m_hImpersonatingToken;};
		void SetImpersonatingToken(HANDLE a_hNew) {m_hImpersonatingToken = a_hNew;};
		HANDLE GetPrimaryToken() {return m_hPrimaryToken;};
		void SetPrimaryToken(HANDLE a_hNew) {m_hPrimaryToken = a_hNew;};
};


class CMultiThreadedDesktopEmulator
{
	private:
		void DoDeleteEverything();
	protected:
		CMultiThreadedDesktopEmulatorParameters m_Parameters;
		// Ответственность снаружи
		CDesktopEmulator* m_pDesktopEmulator;
		CMultiThreadManager* m_pMultiThreadManager;
	public:
		CMultiThreadedDesktopEmulator();
		virtual ~CMultiThreadedDesktopEmulator();

		void Create(HINSTANCE a_hInst, std::string* a_pUserName, CRemainingTimeSlaveDescription* a_pRemaining, HANDLE a_hImpersonatingToken, HANDLE a_hPrimaryToken);

		// Обертки
		CMultiThreadManager* GetMultiThreadManager() {return m_pMultiThreadManager;};
		CDesktopEmulator* GetDesktopEmulator() {return m_pDesktopEmulator;};
		void SetDesktopEmulator(CDesktopEmulator* a_pNew) {m_pDesktopEmulator = a_pNew;};
};


#endif // __MULTITHREADEDDESKTOPEMULATOR_H__