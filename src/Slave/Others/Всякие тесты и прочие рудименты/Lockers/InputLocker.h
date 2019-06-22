#ifndef __INPUTLOCKER_H__
#define __INPUTLOCKER_H__


#include "Locker.h"
#include "SlaveDataReader.h"
#include "NamesCollection.h"
#include "StaticClass.h"


class CInputLocker : public CLocker
{
	// ����������� �����. �� ���� ����������� CKeyboardLocker
	// � CMouseLocker.
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

		// ������ dll-��
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

		// ���������� �� ������������
		void DoInitPointers();
		// ����� ���, ��� ����, � DLL
		void DoInitDLL();
		// ���� ��������� �� ������� � DLL
		virtual void DoLoadDLLProcedures() = 0;
		virtual void DoInitExceptionStringAddition() = 0;
		virtual int GetHookType() = 0;
		void DoDeleteEverything();
		void SetHookProcedure();
		// ���������� CurrentThreadID � DLL
		void DoSetGurrentThreadID();
		CStaticClass m_StaticClass;
	public:
		// ����������� �� ��������� - ���� ����� �����
		//CInputLocker();
		// �����������
		CInputLocker(CSlaveDataReader* pDataReader);
		// ����������
		~CInputLocker();

		// �� ����� � protected, �� ����� �� ������ ������� �� CGlobalLocker
		void RemoveHookProcedure();

		void SetTaskbarWnd(HWND a_hNew);

		// �������
		CNamesCollection* GetHookProceduresDLLNames() {return m_pHookProceduresDLLNames;};
		HMODULE& GetDLLModule();
};


#endif // __INPUTLOCKER_H__