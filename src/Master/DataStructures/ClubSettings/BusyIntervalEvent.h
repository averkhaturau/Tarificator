#ifndef _LX_BUSYINTERVALEVENT_H_INCLUDED__
#define _LX_BUSYINTERVALEVENT_H_INCLUDED__

/*		BusyIntervalEvent.h - ������ CBusyInterval,
 *		��������� ������� ��������� ����������
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
	// ����� ���������, ���������� ��������
	COperatorNumber m_OperatorNumber;

	// ����� ��������
	CTimeStorage m_CreationTime;
};

#endif // _LX_BUSYINTERVALEVENT_H_INCLUDED__