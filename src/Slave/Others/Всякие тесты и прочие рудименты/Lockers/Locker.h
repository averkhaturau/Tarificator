#ifndef __LOCKER_H__
#define __LOCKER_H__


#include "Exceptions.h"


class CLocker
{
	// ����������� ����� ������������� ����-����. �� ���� �����������
	// CKeyboardLocker � CMouseLocker.

	private:
	protected:
		// ������ ��
		bool m_bLocked;
	public:
		// ����������� �� ���������
		CLocker() {m_bLocked = false;};
		// ����������
		virtual ~CLocker() {};

		// ����������
		virtual void Lock() = 0;
		// ����������
		virtual void UnLock() = 0;

		// �������
		bool GetLocked() {return m_bLocked;};
		//void SetLocked(bool bNew) {m_bLocked = bNew;};
};


#endif // __LOCKER_H__