#include "stdafx.h"

#include "TimeException.h"
#include "BusyIntervalsCollection.h"

bool CBusyIntervalsCollection::IsValidIntervalsCollection()
{
	bool _not_result = 0; // чтобы было логически, а не побитно
	 try{
		CTimeStorage _BarrierFinish((__int64)0);

		for (iterator _Iter = GetNextInterval(_BarrierFinish); // первый по времени
				_Iter != m_BaseContainer.end(); _Iter = GetNextInterval((**_Iter).GetFinishTime()))
		{
			_not_result |= (_BarrierFinish >= (*_Iter)->GetCurrentInterval()->GetStartTime()); // интервалы не наезжают друг на друга
			_BarrierFinish = (*_Iter)->GetCurrentInterval()->GetFinishTime(); // FinishTime i-го интервала для i+1 шага
			_not_result |= !(*_Iter)->GetCurrentInterval()->IsValidTimeInterval(); // все интервалы корректны
		}

	 }catch(std::exception &e){
		 throw CTimeException((std::string)"IsValidIntervalCollection() failed: "
			 + std::string(e.what()), bDoNotWriteDuplicates);
	 }catch(...){
		 throw CTimeException("IsValidIntervalCollection() failed: unhandled exception", bDoNotWriteDuplicates);
	 }
	return !_not_result; // чтобы было логически, а не побитно
}

void CBusyIntervalsCollection::AddInterval(CBusyInterval& Interval, const int i)
{
	// надо бы AddResident(CBusyIntervalHist(Interval));
	CBusyIntervalHist _Temp(Interval);
	_Temp.m_Number = i; // самый маздай, из-за которого вся беда
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

	_Temp.m_Number = i; // самый маздай, из-за которого вся беда

	AddResident(_Temp);
}


