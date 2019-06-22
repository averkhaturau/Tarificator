#ifndef _LX_APPINTERVALSCOLLECTION_H_INCLUDED__
#define _LX_APPINTERVALSCOLLECTION_H_INCLUDED__

#include "IntervalsCollection.h"
#include "AppHistoryInterval.h"

// explicit specialization for CAppInterval
template<> class CIntervalsCollection<CAppInterval*> 
	: public CIntervalsCollection<CAppInterval>
{
	public:
		// Функция разная для специализаций. 
		// Проверяет чтобы интервалы были корректными
		virtual bool IsValidIntervalsCollection() const
		{
			bool _not_result = 0; // чтобы было логически, а не побитно
			CTimeStorage _BarrierStart, _BarrierFinish((__int64)0);
			try{
				for (CList::const_iterator _ListIterator = m_ListIntervals.begin();
					_ListIterator != m_ListIntervals.end(); _ListIterator++)
				{
					_not_result |= !(*_ListIterator)->IsValidTimeInterval(); // все интервалы корректны
				};

			}catch(std::exception &e){
				throw CTimeException((std::string)"Error in CIntervalsCollection<CTarifInterval*>::IsValidIntervalCollection(): "
					+std::string(e.what()), bDoNotWriteDuplicates);
			}catch(...){
				throw CTimeException("Error in CIntervalsCollection<CTarifInterval*>::IsValidIntervalCollection(): unhandled exception",
					bDoNotWriteDuplicates);
			};
			return !_not_result; // чтобы было логически, а не побитно
		};
};

typedef CIntervalsCollection<CAppInterval*> CAppIntervalsCollection;

#endif // _LX_APPINTERVALSCOLLECTION_H_INCLUDED__