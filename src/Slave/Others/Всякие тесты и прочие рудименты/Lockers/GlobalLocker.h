#ifndef __GLOBALLOCKER_H__
#define __GLOBALLOCKER_H__


#include "KeyboardLocker.h"
#include "MouseLocker.h"


class CGlobalLocker
{
	private:
	protected:
		// Так выглядят свободные функции Lock и UnLock
		typedef void CLockUnlockFunction(CLocker*);

		CKeyboardLocker* m_pKeyboardLocker;
		CMouseLocker* m_pMouseLocker;
		// Закрыт ли
		bool m_bLocked;
		// Включен ли
		bool m_bEnabled;
		// Сюда сохраняется статус при выключенном локере
		bool m_bSavedState;

		// Нужна, т.к. применяется навороченная обработка исключений, т.е.
		// для борьбы с дублированием больших кусков кода
		void ExecuteFunctions(CLockUnlockFunction* Function);
		void DoDeleteEverything();
		void DoExitToDesktop();
	public:
		// Конструктор
		CGlobalLocker(CSlaveDataReader* pDataReader);
		// Деструктор
		~CGlobalLocker();

		// Может возникнуть исключение
		void LockEverything();
		// Может возникнуть исключение
		void UnLockEverything();

		// Обертки
		CKeyboardLocker* GetKeyboardLocker() {return m_pKeyboardLocker;};
		CMouseLocker* GetMouseLocker() {return m_pMouseLocker;};
		bool GetLocked() {return m_bLocked;};
		bool GetEnabled() {return m_bEnabled;};
		void SetEnabled(bool bNewEnabled);
};


#endif // __GLOBALLOCKER_H__