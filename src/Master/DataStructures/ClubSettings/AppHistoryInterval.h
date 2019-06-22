/*
	CAppHistoryInterval - потомок интервала, хранящий интевал
	времени от момента, когда было замечено что приложение
	запущено, до момента, когда было замечено, что оно закрыто.
*/

#ifndef _LX_APPHISTORYINTERVAL_INCLUDED_
#define _LX_APPHISTORYINTERVAL_INCLUDED_

#include "TimeInterval.h"
#include <string>

class CAppInterval : public CInterval
{
	public:
		CAppInterval();
		CAppInterval(const CTimeStorage Start, const CTimeStorage Finish, const std::string AppName)
			: CInterval(Start, Finish) {SetAppName(AppName);};
		virtual ~CAppInterval();

		// Доступ к m_AppName
		void SetAppName(std::string AppName);
		std::string GetAppName();

		// проверка валидности
		virtual bool IsValidTimeInterval();

	protected:
		// Хранит название приложения (или его окна...)
		std::string m_AppName;
};

// сравнивет интервалы на равенство
bool operator==(CAppInterval& Interval1, CAppInterval& Interval2);
bool operator!=(CAppInterval& Interval1, CAppInterval& Interval2);


#endif // _LX_APPHISTORYINTERVAL_INCLUDED_