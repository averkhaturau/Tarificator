#include "stdafx.h"

#include "IntervalAddition.h"

#include <xstring>


std::string& IntervalAddition::DoAddLeadingZeros(std::string& String, int iRequiredLength)
{
	int iLength = strlen(String.c_str());
		if ( iLength < iRequiredLength )
		{
			String.insert(0, &"0", iRequiredLength - iLength);
		}

	return String;
}


std::string IntervalAddition::DescribeInterval_In_Russian(CIntervalsAncestor* pInterval)
{
	char cBuffer[100];

	DWORD dwHours = pInterval->GetLength().Days() * 24 + pInterval->GetLength().Hours();
	DWORD dwMinutes = pInterval->GetLength().Minutes();

	return (std::string)"c "
		+ DescribeTime(&pInterval->GetStartTime()) + " до "
		+ DescribeTime(&pInterval->GetFinishTime()) + " (всего "
		+ DoAddLeadingZeros((std::string)_itoa(dwHours, cBuffer, 10), 2) + ":"
		+ DoAddLeadingZeros((std::string)_itoa(dwMinutes, cBuffer, 10), 2) + ")";
}


std::string IntervalAddition::DescribeTime(CTimeStorage* a_pTime)
{
	char cBuffer[100];

	SYSTEMTIME SysTime;
	a_pTime->GetTime(&SysTime);

	return DoAddLeadingZeros((std::string)_itoa(SysTime.wHour, cBuffer, 10), 2) + ":"
		+ DoAddLeadingZeros((std::string)_itoa(SysTime.wMinute, cBuffer, 10), 2) + ":"
		+ DoAddLeadingZeros((std::string)_itoa(SysTime.wSecond, cBuffer, 10), 2);
}
