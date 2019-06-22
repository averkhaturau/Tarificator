/*
	CTimeStorageInterval ��������� ��������� ��������, 
	�������� ������� ������� ��� CPriceInterval
	� CBusyInterval.
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

	// �������
	virtual void SetStartTime(const CTimeStorage& Start) = 0;
	virtual CTimeStorage GetStartTime() = 0;

	virtual CTimeStorage GetFinishTime() = 0;

	virtual CTimeStorage GetLength() = 0;

	// ��������� ��������� �� ���������
	bool operator==(CIntervalsAncestor& Interval2);
	bool operator!=(CIntervalsAncestor& Interval2);


	virtual void SetInterval(const CTimeStorage& Start, const CTimeStorage& Finish) = 0;
	virtual void GetInterval(CTimeStorage& Start, CTimeStorage& Finish) = 0;

	virtual void SetLengthFromStart(const CTimeStorage& Length) = 0;

protected:
	// ����� ������ ���������. � ������ ����������� ����� �����
	// ������ ����� (� ������ ��� ���). ������ �����������
	// ��������� �������������� ����������� �������� GetStartTime().
	CTimeStorage m_StartTime;
};

class CInterval : public CIntervalsAncestor
{
public:
	CInterval();
	CInterval(const CTimeStorage& Start, const CTimeStorage& Finish);
	virtual ~CInterval();

	// ��������� ��������
	virtual void SetStartTime(const CTimeStorage& Start);
	virtual void SetInterval(const CTimeStorage& Start, const CTimeStorage& Finish);
	void SetFinishTime(const CTimeStorage& Finish);

	// ������ ��������
	virtual CTimeStorage GetStartTime();
	virtual void GetInterval(CTimeStorage& Start, CTimeStorage& Finish);
	virtual CTimeStorage GetFinishTime();

	// ����� ��������� � CTimeStorage
	virtual CTimeStorage GetLength();
	virtual void SetLengthFromStart(const CTimeStorage& Length);

	// �������� ����������
	virtual bool IsValidTimeInterval();

	// operators

	// ���������� ������������
	CInterval& operator=(CInterval& NewInterval);

protected:
	// ������ � ����� ���������
	CTimeStorage m_FinishTime;
};


/*
// ��� ����������, ����� �������� ������, ���� ��� �����
// �������� ���� �� �����? ������ ������ ���������� ���������
// ������� ������� ��� ��������, ������� ������ �������
bool operator>(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
bool operator<(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
bool operator>=(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
bool operator<=(const CIntervalsAncestor& Interval1, const CIntervalsAncestor& Interval2);
*/

#endif // _LX_TIMEINTERVAL_INCLUDED_