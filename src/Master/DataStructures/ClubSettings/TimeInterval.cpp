/* Implementation of TimeInterval */
#include "stdafx.h"

#include "TimeInterval.h"
#include "TimeException.h"


CInterval::CInterval()
{
}

CInterval::CInterval(const CTimeStorage& Start, const CTimeStorage& Finish)
{
	SetInterval(Start, Finish);
}

CInterval::~CInterval()
{
}

void CInterval::SetInterval(const CTimeStorage& Start, const CTimeStorage& Finish)
{
	//if (!IsValidTimeInterval())
	//	throw CTimeException("CInterval: Incorrect interval. Detected in CInterval::SetInterval(CTimeStorage Start, CTimeStorage Finish)\n", bDoNotWriteDuplicates);
	SetStartTime(Start);
	SetFinishTime(Finish);
}

void CInterval::SetStartTime(const CTimeStorage& Start)
{
	m_StartTime = Start;
}

void CInterval::SetFinishTime(const CTimeStorage& Finish)
{
	m_FinishTime = Finish;
}

void CInterval::GetInterval(CTimeStorage& Start, CTimeStorage& Finish)
{
	//if (!IsValidTimeInterval())
	//	throw CTimeException();
	Start = GetStartTime();
	Finish = GetFinishTime();
}

CTimeStorage CInterval::GetStartTime()
{
	return m_StartTime;
}

CTimeStorage CInterval::GetFinishTime()
{
	return m_FinishTime;
}

CTimeStorage CInterval::GetLength()
{
	return m_FinishTime - m_StartTime;
}

void CInterval::SetLengthFromStart(const CTimeStorage& Lenth)
{
	m_FinishTime = m_StartTime + Lenth;
}

bool CInterval::IsValidTimeInterval()
{
	return (m_FinishTime > m_StartTime) && (m_StartTime.GetTime()!=0); 
}

CInterval& CInterval::operator=(CInterval& NewInterval)
{
	m_StartTime = NewInterval.GetStartTime();
	m_FinishTime = NewInterval.GetFinishTime();
	return (*this);
}

bool CIntervalsAncestor::operator==(CIntervalsAncestor& Interval2)
{
	/*bool bStart = GetStartTime()==Interval2.GetStartTime(),
				bFinish = GetFinishTime() == Interval2.GetFinishTime();*/

	return (GetStartTime() == Interval2.GetStartTime()) &&
		(GetFinishTime() == Interval2.GetFinishTime());
}

bool CIntervalsAncestor::operator!=(CIntervalsAncestor& Interval2)
{
	return !(operator==(Interval2));
}
/*
bool operator>(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2)
{
	return Interval1.GetStartTime() > Interval2.GetStartTime();
}

bool operator<(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2)
{
		return Interval1.GetStartTime() < Interval2.GetStartTime();
}

bool operator>=(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2)
{
	return !(Interval1.GetStartTime() < Interval2.GetStartTime());
}

bool operator<=(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2)
{
	return !(Interval1.GetStartTime() > Interval2.GetStartTime());
}
*/

bool CIntervalsAncestor::IsTimeInInterval(const CTimeStorage& TimeAsked)
{
	return ((TimeAsked >= GetStartTime()) && (TimeAsked <= GetFinishTime()));
}