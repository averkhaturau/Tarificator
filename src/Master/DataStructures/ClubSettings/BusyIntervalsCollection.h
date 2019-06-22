#ifndef _LX_BUSYINTERVALSCOLLECTION_INCLIDED_
#define _LX_BUSYINTERVALSCOLLECTION_INCLIDED_

#include "BusyIntervalHist.h"
#include "IntervalsStorage.h"
#include "..\..\..\Slave\Slave\Exceptions.h"


class CBusyIntervalsCollection
	: public CIntervalsStorage<CBusyIntervalHist>
{
	typedef CBusyIntervalsCollection _tMe;
public:
	CBusyIntervalsCollection(){};
	virtual ~CBusyIntervalsCollection(){};

	CBusyIntervalHist& operator[](const size_type Index)
	{
		if (Index > m_BaseContainer.size())
			throw CAnyLogableException("CBusyIntervalsCollection::operator[] failed", bDoNotWriteDuplicates);
		return *m_BaseContainer[Index]; 
	};

	// Проверяет чтобы интервалы были корректными
	virtual bool IsValidIntervalsCollection();

	void AddInterval(CBusyInterval& Interval, const int i);
	void AddInterval(CBusyInterval& Interval);

	//void SplitHistory(const CTimeStorage& SplitTime, _tMe *pHBIC);

};

#endif // _LX_BUSYINTERVALSCOLLECTION_INCLIDED_
