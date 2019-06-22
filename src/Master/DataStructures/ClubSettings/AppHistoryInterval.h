/*
	CAppHistoryInterval - ������� ���������, �������� �������
	������� �� �������, ����� ���� �������� ��� ����������
	��������, �� �������, ����� ���� ��������, ��� ��� �������.
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

		// ������ � m_AppName
		void SetAppName(std::string AppName);
		std::string GetAppName();

		// �������� ����������
		virtual bool IsValidTimeInterval();

	protected:
		// ������ �������� ���������� (��� ��� ����...)
		std::string m_AppName;
};

// ��������� ��������� �� ���������
bool operator==(CAppInterval& Interval1, CAppInterval& Interval2);
bool operator!=(CAppInterval& Interval1, CAppInterval& Interval2);


#endif // _LX_APPHISTORYINTERVAL_INCLUDED_