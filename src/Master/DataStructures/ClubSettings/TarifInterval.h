/*
	CTarifInterval - Описывает интервал тарифа для
	случая, когда в одно время устанавливается один
	тариф, а ночью дешевле, утром бесплатно,
	днём  дороже, вечером ещё дороже, или наоборот...
*/

#ifndef _LX_TARIFINTERVAL_H_INCLUDED_
#define _LX_TARIFINTERVAL_H_INCLUDED_

#include "CycleInterval.h"
#include "..\Constants.h"

class CTarifInterval : public CCycleInterval
{
	public:
		CTarifInterval();
		CTarifInterval(const CTimeStorage& Start, const CTimeStorage& Finish,
			const CCurrency Tarif)
		{
			SetInterval(Start, Finish);
			SetTarif(Tarif);
		};

		virtual ~CTarifInterval();

		// Доступ к m_Tarif
		void SetTarif(CCurrency Tarif);
		CCurrency GetTarif() const;

		virtual bool IsValidTimeInterval() const;

	protected:
		// Оплата за интервал времени (напр за час)
		CCurrency m_Tarif;
};

#endif // _LX_TARIFINTERVAL_H_INCLUDED_