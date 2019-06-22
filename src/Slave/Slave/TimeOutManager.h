#ifndef __TIMEOUTMANAGER_H__
#define __TIMEOUTMANAGER_H__

#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"


class CTimeOutManager
{
	private:
	protected:
		// Включен ли
		bool m_bEnabled;
		// Таймаут в стонаносекундных интервалах
		CTimeStorage m_TimeOut;
		// Начало
		CTimeStorage m_Begin;
	public:
		// Конструктор по умолчанию
		CTimeOutManager();
		// Копирует все, кроме begin
		CTimeOutManager(CTimeOutManager* pManager);
		// Деструктор
		virtual ~CTimeOutManager();

		// Устанавливает значение начала отсчета
		void OnBegin();
		// true, если время вышло. Если !m_bEnabled - возвращает false.
		bool IsTimeExpired();

		// Искусственно устанавливает состояние прошедшего времени
		void SetArtificialTimeOutState();

		bool operator==(CTimeOutManager& a_Other);

		// Обертки
		bool GetEnabled() {return m_bEnabled;};
		void SetEnabled(bool bNew) {m_bEnabled = bNew;};
		CTimeStorage GetTimeOut() {return m_TimeOut;};
		void SetTimeOut(CTimeStorage New) {m_TimeOut = New;};
};


#endif // __TIMEOUTMANAGER_H__