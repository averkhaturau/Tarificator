#include "stdafx.h"
#include "ColoredInterval.h"

bool operator ==(CColoredInterval CI_1, CColoredInterval CI_2)
{
	return CI_1.GetStartTime() == CI_2.GetStartTime()
		&& CI_1.GetFinishTime() == CI_2.GetFinishTime()
		//&& CI1.GetColor() == CI2.GetColor()
		;
}
