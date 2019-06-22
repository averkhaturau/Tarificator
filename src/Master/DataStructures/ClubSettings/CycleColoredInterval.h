#ifndef _LX_CYCLECOLOREDINTERVAL_H_INCLUDED
#define _LX_CYCLECOLOREDINTERVAL_H_INCLUDED

#include "CycleInterval.h"
#include "ColoredTimeClass.h"

class CCycleColoredInterval 
	: public CCycleInterval, public CColoredClass
{
public:
	CCycleColoredInterval() {};
	CCycleColoredInterval(CCycleInterval& Interval)
	{
		CCycleInterval::operator = (Interval);
		SetColor(RGB(0xff, 0, 0));
	};

	virtual ~CCycleColoredInterval() {};

	CCycleColoredInterval& operator =(CCycleColoredInterval& ColoredInterval)
	{
		CCycleInterval::operator =(ColoredInterval);
		SetColor(ColoredInterval.GetColor());
		return *this;
	}; 

};

#endif // _LX_CYCLECOLOREDINTERVAL_H_INCLUDED