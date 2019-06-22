#ifndef __INVERTEDTIMEOUTMANAGER_H__
#define __INVERTEDTIMEOUTMANAGER_H__

#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"


// Time out manager, который срабатывает за заданный промежуток
// времени до события, а не через заданный промежуток после, в
// отличие от CTimeOutManager
class CInvertedTimeOutManager
{
	private:
	protected:
		// Тайм-аут
		CTimeStorage m_TimeOut;
		// Время, перед которым должна произойти сработка
		CTimeStorage m_EdgeTime;
		bool m_bEnabled;
	public:
		CInvertedTimeOutManager();
		~CInvertedTimeOutManager();

		// Учитывает m_bEnabled
		bool IsTimeExpired();
		// Не учитывает m_bEnabled
		bool CheckForExpiration();

		// Обертки
		void SetTimeOut(CTimeStorage a_New) {m_TimeOut = a_New;};
		CTimeStorage GetTimeOut() {return m_TimeOut;};
		void SetEdgeTime(CTimeStorage a_New) {m_EdgeTime = a_New;};
		CTimeStorage GetEdgeTime() {return m_EdgeTime;};
		void SetEnabled(bool a_bNew) {m_bEnabled = a_bNew;};
		bool GetEnabled() {return m_bEnabled;};
};


#endif // __INVERTEDTIMEOUTMANAGER_H__