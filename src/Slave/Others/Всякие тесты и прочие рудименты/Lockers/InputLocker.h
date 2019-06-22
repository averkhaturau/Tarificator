#ifndef __INPUTLOCKER_H__
#define __INPUTLOCKER_H__


#include "Locker.h"
#include "SlaveDataReader.h"
#include "NamesCollection.h"
#include "StaticClass.h"


class CInputLocker : public CLocker
{
	// Абстрактный класс. От него наследуются CKeyboardLocker
	// и CMouseLocker.
	private:
	protected:
		typedef LRESULT CALLBACK CHookProc(int code, WPARAM wParam, LPARAM lParam);
		typedef HHOOK CGetHook();
		typedef void CSetHook(HHOOK hNewHook);
		typedef void CSetLocked(bool bNew);
		typedef bool CGetLocked();
		typedef void CSetCallbackThreadID(DWORD dwNew);
		typedef void CSetWnd(HWND a_hNew);
		typedef HWND CGetWnd();

		// Модуль dll-ки
		//static HMODULE* m_phModule;
		CHookProc* m_pHookProc;
		CGetHook* m_pGetHook;
		CSetHook* m_pSetHook;
		CNamesCollection* m_pHookProceduresDLLNames;
		std::string* m_pExceptionStringAddition;
		CSetLocked* m_pSetLocked;
		CGetLocked* m_pGetLocked;
		CSetWnd* m_pSetTaskbarWnd;
		CGetWnd* m_pGetTaskbarWnd;

		// Вызывается из конструктора
		void DoInitPointers();
		// Берет все, что надо, в DLL
		void DoInitDLL();
		// Инит указатели на функции в DLL
		virtual void DoLoadDLLProcedures() = 0;
		virtual void DoInitExceptionStringAddition() = 0;
		virtual int GetHookType() = 0;
		void DoDeleteEverything();
		void SetHookProcedure();
		// Записывает CurrentThreadID в DLL
		void DoSetGurrentThreadID();
		CStaticClass m_StaticClass;
	public:
		// Конструктор по умолчанию - надо будет убить
		//CInputLocker();
		// Конструктор
		CInputLocker(CSlaveDataReader* pDataReader);
		// Деструктор
		~CInputLocker();

		// Ей место в protected, но тогда ее нельзя вызвать из CGlobalLocker
		void RemoveHookProcedure();

		void SetTaskbarWnd(HWND a_hNew);

		// Обертки
		CNamesCollection* GetHookProceduresDLLNames() {return m_pHookProceduresDLLNames;};
		HMODULE& GetDLLModule();
};


#endif // __INPUTLOCKER_H__