#ifndef _LX_SPECDAYSCOLLECTION_H_INCLUDED_
#define _LX_SPECDAYSCOLLECTION_H_INCLUDED_

#include "SpecialDay.h"
#include "ActiveContainerResizable.h"

class CSpecDaysCollection
	: public CActiveContainerResizable<CSpecialTimeInterval>
{
public:
	CSpecDaysCollection(){};
	virtual ~CSpecDaysCollection(){};

	CSpecialDayType GetTypeOfDay(LPSYSTEMTIME & a_pDate)
	{
		CSpecialDayType DayType = sdWeekDay;

		for (iterator _Iter = GetData()->begin();
					_Iter != GetData()->end(); ++_Iter)
		{
			if ((**_Iter).IsSpecialDay(a_pDate) != sdWeekDay)
			{
				DayType = (**_Iter).IsSpecialDay(a_pDate);
				break;
			}
		}

		return DayType;
	};

};

#endif //_LX_SPECDAYSCOLLECTION_H_INCLUDED_
