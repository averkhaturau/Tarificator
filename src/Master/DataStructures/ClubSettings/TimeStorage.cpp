#include "stdafx.h"

#include "TimeStorage.h"
#include "TimeException.h"
#include <string>

CTimeStorage::CTimeStorage()
{
}

CTimeStorage::CTimeStorage(LPSYSTEMTIME lpSysTime)
{
	SetTime(lpSysTime);
}

CTimeStorage::CTimeStorage(CTimeContainer i64Time)
{
	SetTime(i64Time);
}

CTimeStorage::CTimeStorage(LPFILETIME lpFileTime)
{
	m_TimeData = FileTimeToQuadWord(lpFileTime);
}

CTimeStorage::~CTimeStorage()
{
}

CTimeContainer CTimeStorage::GetTime() const
{
	return m_TimeData;
}

void CTimeStorage::GetTime(const LPFILETIME& lpFileTime) const
{
	QuadWordToFileTime(m_TimeData, lpFileTime);
}

void CTimeStorage::GetTime(const LPSYSTEMTIME& lpSysTime) const
{
	CTimeContainer_2_LPSYSTEMTIME(m_TimeData, lpSysTime);
}

void CTimeStorage::SetTime(const LPSYSTEMTIME& lpSysTime)
{
	// превратим LPSYSTEMTIME в CTimeContainer
	m_TimeData = LPSYSTEMTIME_2CTimeContainer(lpSysTime);
}

void CTimeStorage::SetTime(const CTimeContainer& i64Time)
{
	m_TimeData = i64Time;
}

void CTimeStorage::SetTime(const LPFILETIME& lpFileTime)
{
	m_TimeData = FileTimeToQuadWord(lpFileTime);
}

unsigned short int CTimeStorage::Minutes() const
{
	return (GetTime() / A_Minute.GetTime()) % 60;
}

unsigned short int CTimeStorage::Hours() const
{
	return (GetTime() / An_Hour.GetTime()) % 24;
}

unsigned int CTimeStorage::Days() const
{
	return (GetTime() / A_Day.GetTime());
}

CTimeStorage CTimeStorage::DaysInCTimeStorage() const
{
	// не оптимальная временная затычка
	return CTimeStorage(Days() * A_Day.GetTime());
}

CTimeStorage CTimeStorage::TransposeToToday() const
{
	return CTimeStorage(CurrentTime().DaysInCTimeStorage().GetTime()
		+ this->TruncateToDay().GetTime());
}

CTimeStorage CTimeStorage::TruncateToDay() const
{
	return CTimeStorage(GetTime() % A_Day.GetTime());
}

CTimeContainer CTimeStorage::LPSYSTEMTIME_2CTimeContainer(
		const LPSYSTEMTIME& lpSysTime) const
{
	FILETIME _FileTime = {0, 0};
	if (!SystemTimeToFileTime(lpSysTime, &_FileTime)) 
		throw CTimeException("CTimeStorage: Can't process ""SystemTimeToFileTime""", bDoNotWriteDuplicates);
	return FileTimeToQuadWord(&_FileTime);
}

void CTimeStorage::CTimeContainer_2_LPSYSTEMTIME(
		CTimeContainer i64Time, const LPSYSTEMTIME& lpSysTime) const
{
	char buf[] = "// FileTimeToSystemTime имеет ограничения \n	i64Time &= 0x7fffffffffffff00; // limitation";

	FILETIME _FileTime;
	QuadWordToFileTime(i64Time, &_FileTime);

	if (!FileTimeToSystemTime(&_FileTime, lpSysTime))
		throw CTimeException(std::string(
		"CTimeStorage: Can't process ""FileTimeToSystemTime"": error ")
		+ std::string(_itoa(GetLastError(), buf, 10)), bDoNotWriteDuplicates);
}

CTimeContainer CTimeStorage::FileTimeToQuadWord(const LPFILETIME& lpFileTime) const
{
	CTimeContainer qw;
	qw = lpFileTime->dwHighDateTime;
	qw <<= 32;
	qw |= lpFileTime->dwLowDateTime;
	return (qw);
}

void CTimeStorage::QuadWordToFileTime(CTimeContainer i64Time, const LPFILETIME& lpFileTime) const
{
	lpFileTime->dwLowDateTime  = (DWORD)i64Time;
	// i64Time копируется в стек, и это необходимо
	i64Time >>= 32;
	lpFileTime->dwHighDateTime = (DWORD)i64Time;
}


// operators
CTimeStorage& CTimeStorage::operator=(const CTimeStorage& NewTime)
{
	SetTime(NewTime.GetTime());
	return *this;
}

CTimeStorage& CTimeStorage::operator+=(const CTimeStorage& AddTime)
{
	m_TimeData += AddTime.GetTime();
	return *this;
}

CTimeStorage& CTimeStorage::operator-=(const CTimeStorage& SubTime)
{
	m_TimeData -= SubTime.GetTime();
	return *this;
}

CTimeStorage operator+(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	CTimeStorage _tmp(Time1.GetTime()+Time2.GetTime());
	return _tmp;
}

CTimeStorage operator-(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	CTimeStorage _tmp(Time1.GetTime()-Time2.GetTime());
	return _tmp;
}

bool  operator>(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	return Time1.GetTime()>Time2.GetTime();
}

bool  operator<(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	return Time1.GetTime()<Time2.GetTime();
}

bool  operator>=(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	return !(Time1 < Time2);
}

bool  operator<=(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	return !(Time1 > Time2);
}

bool  operator==(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	return Time1.GetTime() == Time2.GetTime();
}

bool  operator!=(const CTimeStorage& Time1, const CTimeStorage& Time2)
{
	return Time1.GetTime() != Time2.GetTime();
}


CTimeStorage CurrentTime()
{
	SYSTEMTIME _SysTime;
	GetLocalTime(&_SysTime);
	//GetSystemTime(&_SysTime);
	return CTimeStorage(&_SysTime);
}
