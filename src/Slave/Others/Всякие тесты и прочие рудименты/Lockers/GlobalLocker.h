#ifndef __GLOBALLOCKER_H__
#define __GLOBALLOCKER_H__


#include "KeyboardLocker.h"
#include "MouseLocker.h"


class CGlobalLocker
{
	private:
	protected:
		// ��� �������� ��������� ������� Lock � UnLock
		typedef void CLockUnlockFunction(CLocker*);

		CKeyboardLocker* m_pKeyboardLocker;
		CMouseLocker* m_pMouseLocker;
		// ������ ��
		bool m_bLocked;
		// ������� ��
		bool m_bEnabled;
		// ���� ����������� ������ ��� ����������� ������
		bool m_bSavedState;

		// �����, �.�. ����������� ������������ ��������� ����������, �.�.
		// ��� ������ � ������������� ������� ������ ����
		void ExecuteFunctions(CLockUnlockFunction* Function);
		void DoDeleteEverything();
		void DoExitToDesktop();
	public:
		// �����������
		CGlobalLocker(CSlaveDataReader* pDataReader);
		// ����������
		~CGlobalLocker();

		// ����� ���������� ����������
		void LockEverything();
		// ����� ���������� ����������
		void UnLockEverything();

		// �������
		CKeyboardLocker* GetKeyboardLocker() {return m_pKeyboardLocker;};
		CMouseLocker* GetMouseLocker() {return m_pMouseLocker;};
		bool GetLocked() {return m_bLocked;};
		bool GetEnabled() {return m_bEnabled;};
		void SetEnabled(bool bNewEnabled);
};


#endif // __GLOBALLOCKER_H__