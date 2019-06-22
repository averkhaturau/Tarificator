#ifndef _LX_BUSYINTERVALEVENT_H_INCLUDED__
#define _LX_BUSYINTERVALEVENT_H_INCLUDED__

/*		BusyIntervalEvent.h - предок CBusyInterval,
 *		описывает событие изменения интервалов
 */

#include <string>
#include "TimeStorage.h"

typedef unsigned int COperatorNumber;

class CBusyIntervalEvent
{
public:
	inline COperatorNumber GetOperatorNumber() const
		{ return m_OperatorNumber; };

	inline void SetOperatorNumber(const COperatorNumber& OperatorNumber)
		{ m_OperatorNumber = OperatorNumber; };


	inline CTimeStorage GetCreationTime() const
		{ return m_CreationTime; };

	inline void SetCreationTime(const CTimeStorage& Time)
		{ m_CreationTime = Time; };


protected:
	// Номер оператора, создавшего интервал
	COperatorNumber m_OperatorNumber;

	// время создания
	CTimeStorage m_CreationTime;
};

#endif // _LX_BUSYINTERVALEVENT_H_INCLUDED__