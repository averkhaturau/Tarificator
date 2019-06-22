#ifndef __CLUBSTATE_H__
#define __CLUBSTATE_H__

#include <string>
#include "OperatorsCollection.h"
#include "MashinesCollection.h"
#include "TarifPlansCollection.h"
#include "..\Saving\MasterBoundStorer.h"

/*
	Описывает состояние всех машин клуба, храня их состояния, имя клуба...
*/
class CClubState
{
	private:
		void DoDeleteEverything();
	protected:
		COperatorsCollection* m_pOperatorsCollection;
		CMashinesCollection* m_pMashinesCollection;
		CTarifPlansCollection* m_pTarifPlansCollection;
		std::string m_ClubName;
		CCycleInterval m_WorkingInterval;
		CTimeStorage m_MaxClIntervLength;

		void PutTimeToInterval(CTimeStorage* pTime, CInterval* pInterval);
		CCurrency DoGetPrice(CTarifPlan* pTarifPlan, CTarifInterval* pTarifInterval, CInterval* pInterval);
	public:
		// Конструктор с указанием ридера начальных данных
		CClubState(CMasterBoundStorer* pMasterStorer);
		// Деструктор
		virtual ~CClubState();

		// Вычисляет цену интервала. Находится в этом классе, т.к. для
		// вычисления цены нужно знать TarifInterval.
		CCurrency CalcIntervalPrice(CBusyInterval* pInterval);

		// Вечисляет Finish по Start, тарифному плану и цене.
		// Запрашиваемая цена может оказаться слишком большой, так что
		// в Price возвращается реальная цена. pInterval должен
		// уже содержать максимальный Finish.
		void CalcIntervalFinishByPrice(CBusyInterval* pInterval, CCurrency& Price);

		// Обертки
		COperatorsCollection* GetOperatorsCollection() {return m_pOperatorsCollection;};
		CMashinesCollection* GetMashinesCollection() {return m_pMashinesCollection;};
		CTarifPlansCollection* GetTarifPlansCollection() {return m_pTarifPlansCollection;};

		std::string GetClubName() const {return m_ClubName;};
		void SetClubName(const std::string& Name){m_ClubName = Name;};

		CCycleInterval* GetWorkingInterval() { return &m_WorkingInterval; };
		void SetWorkingInterval(CCycleInterval* pInterval)
			{ m_WorkingInterval = *pInterval; };

		void SetMaxIntervLength(const CTimeStorage& Length_)
			{ m_MaxClIntervLength = Length_; };
		CTimeStorage* GetMaxIntervLength()
			{ return &m_MaxClIntervLength; };

};


#endif // __CLUBSTATE_H__
