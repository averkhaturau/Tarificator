#ifndef __LOCKER_H__
#define __LOCKER_H__


#include "Exceptions.h"


class CLocker
{
	// Абстрактный класс запрещальщика чего-либо. От него наследуются
	// CKeyboardLocker и CMouseLocker.

	private:
	protected:
		// Закрыт ли
		bool m_bLocked;
	public:
		// Конструктор по умолчанию
		CLocker() {m_bLocked = false;};
		// Деструктор
		virtual ~CLocker() {};

		// Запрещение
		virtual void Lock() = 0;
		// Разрешение
		virtual void UnLock() = 0;

		// Обертки
		bool GetLocked() {return m_bLocked;};
		//void SetLocked(bool bNew) {m_bLocked = bNew;};
};


#endif // __LOCKER_H__