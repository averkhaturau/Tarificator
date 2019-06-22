#include "stdafx.h"

#include "TimeException.h"
#include "BusyIntervalsCollection.h"

bool CBusyIntervalsCollection::IsValidIntervalsCollection()
{
	bool _not_result = 0; // ����� ���� ���������, � �� �������
	 try{
		CTimeStorage _BarrierFinish((__int64)0);

		for (iterator _Iter = GetNextInterval(_BarrierFinish); // ������ �� �������
				_Iter != m_BaseContainer.end(); _Iter = GetNextInterval((**_Iter).GetFinishTime()))
		{
			_not_result |= (_BarrierFinish >= (*_Iter)->GetCurrentInterval()->GetStartTime()); // ��������� �� �������� ���� �� �����
			_BarrierFinish = (*_Iter)->GetCurrentInterval()->GetFinishTime(); // FinishTime i-�� ��������� ��� i+1 ����
			_not_result |= !(*_Iter)->GetCurrentInterval()->IsValidTimeInterval(); // ��� ��������� ���������
		}

	 }catch(std::exception &e){
		 throw CTimeException((std::string)"IsValidIntervalCollection() failed: "
			 + std::string(e.what()), bDoNotWriteDuplicates);
	 }catch(...){
		 throw CTimeException("IsValidIntervalCollection() failed: unhandled exception", bDoNotWriteDuplicates);
	 }
	return !_not_result; // ����� ���� ���������, � �� �������
}

void CBusyIntervalsCollection::AddInterval(CBusyInterval& Interval, const int i)
{
	// ���� �� AddResident(CBusyIntervalHist(Interval));
	CBusyIntervalHist _Temp(Interval);
	_Temp.m_Number = i; // ����� ������, ��-�� �������� ��� ����
	AddResident(_Temp);
}

void CBusyIntervalsCollection::AddInterval(CBusyInterval& Interval)
{
	CBusyIntervalHist _Temp(Interval);
	for (int i = 0;; ++i)
	{
		bool done = true;
		for (iterator _Iter = m_BaseContainer.begin();
				_Iter != m_BaseContainer.end(); ++_Iter)
			done &= ((**_Iter).m_Number != i);
		if (done) break;
	}

	_Temp.m_Number = i; // ����� ������, ��-�� �������� ��� ����

	AddResident(_Temp);
}


