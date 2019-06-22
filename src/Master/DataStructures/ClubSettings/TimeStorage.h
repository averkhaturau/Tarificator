/*
	CTimeStorageStorageStorageStorageStorageStorage обеспечивает хранение времени
*/
#ifndef _LX_TIME_H_INCLUDED_
#define _LX_TIME_H_INCLUDED_

#include <windows.h>

typedef __int64 CTimeContainer;

class CTimeStorage
{
		typedef CTimeStorage _MyT;
	public:
		CTimeStorage();
		CTimeStorage(const LPSYSTEMTIME lpSysTime);
		CTimeStorage(const CTimeContainer i64Time);
		CTimeStorage(const LPFILETIME lpFileTime);

		virtual ~CTimeStorage();

		// устанавливает значение объекта
		void SetTime(const LPSYSTEMTIME& lpSysTime);
		void SetTime(const CTimeContainer& i64Time);
		void SetTime(const LPFILETIME& lpFileTime);

		// возвращают значение объекта
		void GetTime(const LPSYSTEMTIME& lpSysTime) const;
		void GetTime(const LPFILETIME& lpFileTime) const;
		CTimeContainer GetTime() const;

		unsigned short int Minutes() const;
		unsigned short int Hours() const;
		unsigned int Days() const; // количество дней с начала отсчёта
		CTimeStorage DaysInCTimeStorage() const;

		// Транспонирует(муз.) время в сегодняшное число
		// Работает только если *время меньше 1 дня*
		CTimeStorage TransposeToToday() const;
		// Обрезает дни, годы и т.п..
		CTimeStorage TruncateToDay() const;

		CTimeStorage& operator=(const CTimeStorage& NewTime);
		CTimeStorage& operator+=(const CTimeStorage& AddTime);
		CTimeStorage& operator-=(const CTimeStorage& SubTime);

	protected:
		inline CTimeContainer LPSYSTEMTIME_2CTimeContainer(const LPSYSTEMTIME& lpSysTime) const;
		inline void CTimeContainer_2_LPSYSTEMTIME(CTimeContainer i64Time, const LPSYSTEMTIME& lpSysTime) const;

		// Выражает время в 100-наносекундных интервалах
		CTimeContainer m_TimeData;

		inline CTimeContainer FileTimeToQuadWord(const LPFILETIME& lpFileTime) const;
		inline void QuadWordToFileTime(CTimeContainer i64Time, const PFILETIME& lpFileTime) const;
};
// end of class CTimeStorageStorageStorageStorageStorageStorage

CTimeStorage operator+(const CTimeStorage& Time1, const CTimeStorage& Time2); // returns Time1+Time2; avoid overflow
CTimeStorage operator-(const CTimeStorage& Time1, const CTimeStorage& Time2); // returns Time1-Time2
// Сравнение значение
bool operator>(const CTimeStorage& Time1, const CTimeStorage& Time2); // Time1 > Time2
bool operator<(const CTimeStorage& Time1, const CTimeStorage& Time2); // Time1 < Time2
bool operator>=(const CTimeStorage& Time1, const CTimeStorage& Time2); // Time1 >= Time2
bool operator<=(const CTimeStorage& Time1, const CTimeStorage& Time2); // Time1 <= Time2
bool operator==(const CTimeStorage& Time1, const CTimeStorage& Time2); // Time1 == Time2
bool operator!=(const CTimeStorage& Time1, const CTimeStorage& Time2); // Time1 != Time2

// константы времени
const CTimeStorage A_Second((CTimeContainer)1e7);
const CTimeStorage A_Minute(60*A_Second.GetTime());
const CTimeStorage An_Hour(60*A_Minute.GetTime());
const CTimeStorage A_Day(24*An_Hour.GetTime());

// Функция, выдающая текущее время
CTimeStorage CurrentTime();

#endif //_LX_TIME_H_INCLUDED_