#include "StdAfx.h"
#include "BusyIntervalHist.h"

bool CBusyIntervalHist::operator ==(CBusyIntervalHist& _2)
{
	bool _result = true;

	iterator _IterMe, _Iter2;
	for (_IterMe = GetData()->begin(),
			_Iter2 = _2.GetData()->begin();
		_IterMe != GetData()->end() &&
			_Iter2 != _2.GetData()->end(); ++_IterMe, ++_Iter2)
	{
		if (**_Iter2 != **_IterMe)
		{
			_result = false;
			break;
		}
	}
	return _result;

	// оптимизированно: return (*GetCurrentInterval()) == (*_2.GetCurrentInterval());
}