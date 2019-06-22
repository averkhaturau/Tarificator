#ifndef _LX_SPECIALDAY_H_INCLUDED_
#define _LX_SPECIALDAY_H_INCLUDED_

#include "ClubSettings\TimeStorage.h"
#include "ClubSettings\TimeInterval.h"
#include "windows.h"

/* перечислим возможные типы временных интервалов */
enum CSpecialDayType
{
	sdAnyDay = 0, /*default*/
	sdWeekDay,
	//sdWeekDayNigth,
	sdHoliday,
	//sdHolidayNight,
	sdOpenDoors/*or something else*/
	/*// may be:
	sdWeekdayMorning,
	sdWeekdayEvening,
	sdWeekdayAfternung,
	sdHolidayMorning
	//...
	*/
};

/*	Класс описывает по маске день,
	который следует считать специальным (праздником и т.п.),
	а также тип этого дня (из присутствующих в CSpecialDayType).
 */
class CSpecialTimeInterval
{
public:
	CSpecialTimeInterval()
	{
		m_TimeMask.wYear = -1;
		m_TimeMask.wMonth = -1;
		m_TimeMask.wDayOfWeek = -1;
		m_TimeMask.wDay = -1;
		m_TimeMask.wHour = -1;
		m_TimeMask.wMinute = -1;
		m_TimeMask.wSecond = -1;
		m_TimeMask.wMilliseconds = -1;

		m_Length = A_Day;

		m_stType = sdWeekDay;
	};

	/* Возвращает тип, если переданая дата подходит, иначе - sdWeekDay */
	CSpecialDayType IsSpecialDay(LPSYSTEMTIME &a_pDate)
	{
		// Условие несовпадания дат запишется так:
		if ( 
			(m_TimeMask.wYear==-1?0:m_TimeMask.wYear^a_pDate->wYear) ||
			(m_TimeMask.wMonth==-1?0:m_TimeMask.wMonth^a_pDate->wMonth) ||
			(m_TimeMask.wDayOfWeek==-1?0:m_TimeMask.wDayOfWeek^a_pDate->wDayOfWeek) ||
			(m_TimeMask.wDay==-1?0:m_TimeMask.wDay^a_pDate->wDay)
			 )
		{// даты не совпадают
			return sdWeekDay;
		}
		// else
		return GetType();
	};

	LPSYSTEMTIME GetTimeMask(){return &m_TimeMask;};

	void SetIntervalMask(LPSYSTEMTIME & a_pMask)
	{
		m_TimeMask.wYear      = a_pMask->wYear;
		m_TimeMask.wMonth     = a_pMask->wMonth;
		m_TimeMask.wDayOfWeek = a_pMask->wDayOfWeek;
		m_TimeMask.wDay       = a_pMask->wDay;
		// остальное игнорируется
 	};

	// Обращение к длине интервала
	CTimeStorage GetLength(){return m_Length;};
	void SetLenght(CTimeStorage &a_Length){m_Length=a_Length;};

	// Обращения к типу
	CSpecialDayType GetType()const{return m_stType;};
	void SetType(const CSpecialDayType &a_stType){m_stType=a_stType;};

protected:
	// Type of time
	CSpecialDayType m_stType;
	// Length of the interval
	CTimeStorage m_Length;

	// Маска начала циклического специального интервала
	// Не играющие значения переменные равны WORD(-1)
	// недостаток - период цикличности кратен одному из
	// полей SYSTEMTIME: или дням, или часам, или неделям.
	// ещё: нельзя описать такие праздники, как первый четверг месяца...
	SYSTEMTIME m_TimeMask;

};

#endif //_LX_SPECIALDAY_H_INCLUDED_
