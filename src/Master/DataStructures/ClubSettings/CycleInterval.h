#ifndef _LX_CYCLEINTERVAL_H_INCLUDED_
#define _LX_CYCLEINTERVAL_H_INCLUDED_

#include "TimeInterval.h"
#include "TimeException.h"

class CCycleInterval : public CIntervalsAncestor
{
	private:
	protected:
		// Ќачальное врем€ интервала задаетс€ в "маленьком" времени
		// (без лет, дней и т.п.).
		// ƒлина интервала
		CTimeStorage m_Length;
	public:
		CCycleInterval() {};
		virtual ~CCycleInterval() {};

		CCycleInterval& operator=(CCycleInterval& New)
		{
			m_StartTime = New.m_StartTime;
			m_Length = New.GetLength();
			return (*this);
		};

		virtual bool IsValidTimeInterval() {return true;};

		// ќбертки
		virtual CTimeStorage GetStartTime()
		{
			return m_StartTime.TransposeToToday();
		};

		// Start может быть как длинным, так и коротким - все равно
		// он обрежетс€
		virtual void SetInterval(const CTimeStorage& Start, const CTimeStorage& Finish)
		{
			m_StartTime = Start.TruncateToDay();
			m_Length = Finish.TruncateToDay() - m_StartTime;
				if (Finish.TruncateToDay() < m_StartTime)
				{
					m_Length = A_Day - m_Length;
				}
		};

		virtual void GetInterval(CTimeStorage& Start, CTimeStorage& Finish)
		{
			Start = GetStartTime();
			Finish = GetFinishTime();
		};

		virtual CTimeStorage GetFinishTime()
		{
			return m_StartTime.TransposeToToday() + m_Length;
		};

		virtual void SetStartTime(const CTimeStorage& Start)
		{
			m_StartTime = Start.TruncateToDay();
		};

		virtual CTimeStorage GetLength()
		{
			return m_Length;
		};

		virtual void SetLengthFromStart(const CTimeStorage& Length)
		{
			m_Length = Length;
		};

		// ѕереопеделен дл€ работы с короткими временами
		virtual bool IsTimeInInterval(const CTimeStorage& TimeAsked)
		{
			/*CTimeStorage Asked = TimeAsked.TruncateToDay();
			CTimeStorage Start = GetShortStartTime(), Finish = GetShortFinishTime();
			bool bFirst = TimeAsked.TruncateToDay() >= GetShortStartTime();
			bool bSocond = TimeAsked.TruncateToDay() <= GetShortFinishTime();
			bool bResult = (TimeAsked.TruncateToDay() >= GetShortStartTime()) && (TimeAsked.TruncateToDay() <= GetShortFinishTime());*/
			return ( (TimeAsked.TruncateToDay() >= GetShortStartTime()) && (TimeAsked.TruncateToDay() <= GetShortFinishTime()) ) ||
				((TimeAsked.TruncateToDay() + A_Day >= GetShortStartTime()) && (TimeAsked.TruncateToDay() + A_Day <= GetShortFinishTime()));
		};

		// ”никальные обертки (ни от кого не унаследованы)
		CTimeStorage GetShortStartTime()
		{
			return m_StartTime;
		};

		CTimeStorage GetShortFinishTime()
		{
			return m_StartTime + m_Length;
		};
};

#endif // _LX_CYCLEINTERVAL_H_INCLUDED_