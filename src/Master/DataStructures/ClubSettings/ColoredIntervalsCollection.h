#ifndef _LX_COLOREDINTERVALSCOLLECTION_INCLUDED_
#define _LX_COLOREDINTERVALSCOLLECTION_INCLUDED_

#include "IntervalsStorage.h"
#include "BusyIntervalsCollection.h"
#include "ColoredInterval.h"
#include "..\ActiveContainerResizable.h"

class CColoredIntervalsCollection : public CIntervalsStorage<CColoredInterval>
{
public:
	CColoredIntervalsCollection(){};
	virtual ~CColoredIntervalsCollection(){};

	CColoredIntervalsCollection& operator =(CBusyIntervalsCollection& BIC)
	{
		// надо выделить память для всех элементов
		// и скопировать все элементы
		Clear();

		for (CBusyIntervalsCollection::const_iterator
				_Iter = BIC.GetData()->begin();
				_Iter != BIC.GetData()->end(); ++_Iter)
		{
			AddResident((CColoredInterval((**_Iter).operator CBusyInterval())));
		}

		return *this;
	};
};

#endif // _LX_COLOREDINTERVALSCOLLECTION_INCLUDED_