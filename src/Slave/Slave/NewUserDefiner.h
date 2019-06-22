#ifndef __NEWUSERDEFINER_H__
#define __NEWUSERDEFINER_H__

#include "SlaveDataReader.h"
#include "WTSSessionsIdsCollection.h"

#include <string>


class CNewUserDefiner
{
	private:
	protected:
		std::string m_sLastUserName;

		std::string GetUserNameByProcessId(DWORD a_dwProcessId);
	public:
		CNewUserDefiner();
		~CNewUserDefiner();

		void OnTimer();

		HANDLE GetUserTokenBySessionId(DWORD a_dwSessionId);
		HANDLE GetUserPrimaryTokenBySessionId(DWORD a_dwSessionId);
		HANDLE GetUserImpersonatingTokenBySessionId(DWORD a_dwSessionId);

		HANDLE GetCurrentUserImpersonatingToken();
		HANDLE GetCurrentUserPrimaryToken();
		HANDLE GetCurrentUserToken();

		HANDLE GetExplorerSessionToken(DWORD a_dwSessionId);

		// Возвращает номер первой активной сессии. Если таких нет -
		// генерит исключение.
		DWORD GetCurrentUserSessionId();

		void DoFillSessionsIdsCollection(CWTSSessionsIdsCollection* a_pCollection);

		//void GetUserDesktopAndStation(HDESK* a_pDesktop, HWINSTA* a_pStation);

		std::string GetUserNameBySessionId(DWORD a_dwSessionId);

		std::string GetCurrentUserName();
};


#endif // __NEWUSERDEFINER_H__