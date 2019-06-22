/*
	Interval that has COLORREF for graphical imaging
*/

#ifndef _LX_COLOREDINTERVAL_INCLUDED_
#define _LX_COLOREDINTERVAL_INCLUDED_

#include "TimeInterval.h"
#include "ColoredTimeClass.h"


class CColoredInterval : public CInterval, public CColoredClass  
{
public:
	CColoredInterval() {};
	CColoredInterval(CInterval& Interval)
	{
		CInterval::operator = (Interval);
		SetColor(ciDefaultBusyColor);
	};

	virtual ~CColoredInterval() {};

	CColoredInterval& operator =(CColoredInterval& ColoredInterval)
	{
		CInterval::operator =(ColoredInterval);
		SetColor(ColoredInterval.GetColor());
		return *this;
	}; 
};

bool operator ==(CColoredInterval CI_1, CColoredInterval CI_2);

#endif // _LX_COLOREDINTERVAL_INCLUDED_