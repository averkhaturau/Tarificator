/*
	CTimeStorageInterval описывает временной интервал, 
	€вл€етс€ базовым классом дл€ CPriceInterval
	и CBusyInterval.
*/
#ifndef _LX_TIMEINTERVAL_INCLUDED_
#define _LX_TIMEINTERVAL_INCLUDED_

#include "TimeStorage.h"


class CIntervalsAncestor
{
public:
	CIntervalsAncestor() {};
	virtual ~CIntervalsAncestor() {};

	virtual bool IsTimeInInterval(const CTimeStorage& TimeAsked);

	virtual bool IsValidTimeInterval() = 0;

	// ќбертки
	virtual void SetStartTime(const CTimeStorage& Start) = 0;
	virtual CTimeStorage GetStartTime() = 0;

	virtual CTimeStorage GetFinishTime() = 0;

	virtual CTimeStorage GetLength() = 0;

	// сравнивет интервалы на равенство
	bool operator==(CIntervalsAncestor& Interval2);
	bool operator!=(CIntervalsAncestor& Interval2);


	virtual void SetInterval(const CTimeStorage& Start, const CTimeStorage& Finish) = 0;
	virtual void GetInterval(CTimeStorage& Start, CTimeStorage& Finish) = 0;

	virtual void SetLengthFromStart(const CTimeStorage& Length) = 0;

protected:
	// ¬рем€ начала интервала. ¬ разных наследниках может иметь
	// разный смысл (с годами или без). ≈диный полиморфный
	// интерфейс обеспечиваетс€ виртуальной функцией GetStartTime().
	CTimeStorage m_StartTime;
};

class CInterval : public CIntervalsAncestor
{
public:
	CInterval();
	CInterval(const CTimeStorage& Start, const CTimeStorage& Finish);
	virtual ~CInterval();

	// установка значений
	virtual void SetStartTime(const CTimeStorage& Start);
	virtual void SetInterval(const CTimeStorage& Start, const CTimeStorage& Finish);
	void SetFinishTime(const CTimeStorage& Finish);

	// чтение значений
	virtual CTimeStorage GetStartTime();
	virtual void GetInterval(CTimeStorage& Start, CTimeStorage& Finish);
	virtual CTimeStorage GetFinishTime();

	// длина интервала в CTimeStorage
	virtual CTimeStorage GetLength();
	virtual void SetLengthFromStart(const CTimeStorage& Length);

	// проверка валидности
	virtual bool IsValidTimeInterval();

	// operators

	// копирующее присваивание
	CInterval& operator=(CInterval& NewInterval);

protected:
	// начало и конец интервала
	CTimeStorage m_FinishTime;
};


/*
// как определить, какой интервал раньше, если они могут
// наезжать друг на друга? ƒанна€ верси€ операторов сравнени€
// считает раньшим тот интервал, который раньше началс€
bool operator>(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
bool operator<(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
bool operator>=(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
bool operator<=(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
*/

#endif // _LX_TIMEINTERVAL_INCLUDED_