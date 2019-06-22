/*
	CBusyInterval описывает интервал, 
	в который машина может быть занята пользователем
*/
#ifndef _LX_BUSYINTERVAL_H_INCLUDED_
#define _LX_BUSYINTERVAL_H_INCLUDED_

#include "TimeInterval.h"
#include "BusyIntervalEvent.h"
#include "..\Constants.h"
#include <string>


class CBusyInterval
	: public CInterval, public CBusyIntervalEvent
{
public:
	typedef unsigned short int CTarifPlanNumber; // if ==0 then not setted

	CBusyInterval(){SetTarifPlanNumber(0);};

	CBusyInterval(const CTimeStorage& Start, const CTimeStorage& Finish,
		const CTarifPlanNumber& TarifPlan, const COperatorNumber& OperatorNumber,
		const std::string& sClientName, const CTimeStorage& Creation, const CCurrency& Price)
	:	CInterval(Start, Finish)
	{	SetTarifPlanNumber(TarifPlan);
		SetOperatorNumber(OperatorNumber);
		SetClientName(sClientName);
		SetCreationTime(Creation);
		SetPrice(Price);
	};

	//virtual ~CBusyInterval(){};

	inline CTarifPlanNumber GetTarifPlanNumber() const
		{ return m_TarifPlanNumber; };

	inline void SetTarifPlanNumber(const CTarifPlanNumber& TarifPlanNumber)
		{	m_TarifPlanNumber = TarifPlanNumber; };

	inline void SetClientName(const std::string& Name)
		{ m_ClientName = Name; };

	inline std::string& GetClientName()
		{ return m_ClientName; };

	// проверка валидности
	virtual bool IsValidTimeInterval()
		{ return CInterval::IsValidTimeInterval() && (m_TarifPlanNumber!=0); };

	void operator=(CBusyInterval& FromInterval)
	{
		CInterval::operator=(FromInterval);
		m_OperatorNumber = FromInterval.GetOperatorNumber();
		m_CreationTime = FromInterval.GetCreationTime();
		m_TarifPlanNumber = FromInterval.GetTarifPlanNumber();
		m_ClientName = FromInterval.GetClientName();
		m_Price = FromInterval.GetPrice();
	};

	bool operator ==(CBusyInterval& IntervalToCompare)
	{
		return CIntervalsAncestor::operator ==(IntervalToCompare)
			&& IntervalToCompare.GetPrice() == this->GetPrice()
			&& IntervalToCompare.GetClientName() == this->GetClientName()
			&& IntervalToCompare.GetTarifPlanNumber() ==
				this->GetTarifPlanNumber();
	};

	CCurrency GetPrice() const { return m_Price; };

	void SetPrice(const CCurrency& Price) { m_Price = Price; };

protected:
	// тарифный план. Если 0, то не установлен
	CTarifPlanNumber m_TarifPlanNumber;

	// стоимость интервала
	CCurrency m_Price;

	// имя заказавшего
	std::string m_ClientName;

};

#endif //_LX_BUSYINTERVAL_H_INCLUDED_