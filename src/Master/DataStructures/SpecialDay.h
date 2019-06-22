#ifndef _LX_SPECIALDAY_H_INCLUDED_
#define _LX_SPECIALDAY_H_INCLUDED_

#include "ClubSettings\TimeStorage.h"
#include "ClubSettings\TimeInterval.h"
#include "windows.h"

/* ���������� ��������� ���� ��������� ���������� */
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

/*	����� ��������� �� ����� ����,
	������� ������� ������� ����������� (���������� � �.�.),
	� ����� ��� ����� ��� (�� �������������� � CSpecialDayType).
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

	/* ���������� ���, ���� ��������� ���� ��������, ����� - sdWeekDay */
	CSpecialDayType IsSpecialDay(LPSYSTEMTIME &a_pDate)
	{
		// ������� ������������ ��� ��������� ���:
		if ( 
			(m_TimeMask.wYear==-1?0:m_TimeMask.wYear^a_pDate->wYear) ||
			(m_TimeMask.wMonth==-1?0:m_TimeMask.wMonth^a_pDate->wMonth) ||
			(m_TimeMask.wDayOfWeek==-1?0:m_TimeMask.wDayOfWeek^a_pDate->wDayOfWeek) ||
			(m_TimeMask.wDay==-1?0:m_TimeMask.wDay^a_pDate->wDay)
			 )
		{// ���� �� ���������
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
		// ��������� ������������
 	};

	// ��������� � ����� ���������
	CTimeStorage GetLength(){return m_Length;};
	void SetLenght(CTimeStorage &a_Length){m_Length=a_Length;};

	// ��������� � ����
	CSpecialDayType GetType()const{return m_stType;};
	void SetType(const CSpecialDayType &a_stType){m_stType=a_stType;};

protected:
	// Type of time
	CSpecialDayType m_stType;
	// Length of the interval
	CTimeStorage m_Length;

	// ����� ������ ������������ ������������ ���������
	// �� �������� �������� ���������� ����� WORD(-1)
	// ���������� - ������ ����������� ������ ������ ��
	// ����� SYSTEMTIME: ��� ����, ��� �����, ��� �������.
	// ���: ������ ������� ����� ���������, ��� ������ ������� ������...
	SYSTEMTIME m_TimeMask;

};

#endif //_LX_SPECIALDAY_H_INCLUDED_
