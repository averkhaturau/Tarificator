#ifndef _LX_INTERVALADDITION_H_INCLUDED_
#define _LX_INTERVALADDITION_H_INCLUDED_

#include "TimeInterval.h"
#include <string>

namespace IntervalAddition
{
	// ƒобавл€ет ведущие нули к числам, если надо
	std::string& DoAddLeadingZeros(std::string& String, int iRequiredLength);

	std::string DescribeInterval_In_Russian(
		CIntervalsAncestor* pInterval);

	std::string DescribeTime(CTimeStorage* a_pTime);
};

#endif //_LX_INTERVALADDITION_H_INCLUDED_
