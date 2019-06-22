/* Implementation of CAppHistoryInterval */

#include "StdAfx.h"
#include "AppHistoryInterval.h"

CAppInterval::CAppInterval()
{
	m_AppName = "";
}

CAppInterval::~CAppInterval()
{
}

void CAppInterval::SetAppName(std::string AppName)
{
	m_AppName = AppName;
}

std::string CAppInterval::GetAppName()
{
	return m_AppName;
}

bool CAppInterval::IsValidTimeInterval()
{
	return CInterval::IsValidTimeInterval() && (m_AppName != "");
}

bool operator==(CAppInterval& Interval1, CAppInterval& Interval2)
{
	return ((CInterval)Interval1==(CInterval)Interval2) &&
			Interval1.GetAppName()==Interval2.GetAppName();
}

bool operator!=(CAppInterval& Interval1, CAppInterval& Interval2)
{
	return !(Interval1==Interval2);
}