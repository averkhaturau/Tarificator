#ifndef __SESSIONTIMEOUTMANAGER_H__
#define __SESSIONTIMEOUTMANAGER_H__

#include "TimeOutManager.h"


class CSessionTimeOutManager : public CTimeOutManager
{
	private:
	protected:
		DWORD m_dwSessionId;
	public:
		CSessionTimeOutManager();
		CSessionTimeOutManager(DWORD a_dwSessionId, CTimeContainer a_TimeOut);
		~CSessionTimeOutManager();

		bool operator==(CSessionTimeOutManager& a_Other);

		// Обертки
		DWORD GetSessionId() {return m_dwSessionId;};
		void SetSessionId(DWORD a_dwNew) {m_dwSessionId = a_dwNew;};
};


#endif // __SESSIONTIMEOUTMANAGER_H__