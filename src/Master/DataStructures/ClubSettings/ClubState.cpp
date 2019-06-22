#include "stdafx.h"
#include "ClubState.h"

#include <math.h>


CClubState::CClubState(CMasterBoundStorer* pMasterStorer)
{
	m_pMashinesCollection = 0;
	m_pOperatorsCollection = 0;
	m_pTarifPlansCollection = 0;

	try{
		m_pMashinesCollection = new CMashinesCollection(pMasterStorer);
		m_pOperatorsCollection = new COperatorsCollection(pMasterStorer);
		m_pTarifPlansCollection = new CTarifPlansCollection(pMasterStorer);

		pMasterStorer->ReadClubState(this);

	}catch(CAnyLogableException &e){
		DoDeleteEverything();

		throw CAnyLogableException((std::string)"An error occured in CClubState::CClubState: "
			+ (std::string)e.what(), e.GetWriteDuplicatesToLog());
	}catch(...){
		DoDeleteEverything();
		throw CAnyLogableException("An unknown error occured in CClubState::CClubState", bDoNotWriteDuplicates);
	}
}
// End of CClubState()


CClubState::~CClubState()
{
	DoDeleteEverything();
}
// End of ~CClubState()


void CClubState::DoDeleteEverything()
{
	if (m_pMashinesCollection)
	{
		delete m_pMashinesCollection;
		m_pMashinesCollection = 0;
	}
	if (m_pOperatorsCollection)
	{
		delete m_pOperatorsCollection;
		m_pOperatorsCollection = 0;
	}
	if (m_pTarifPlansCollection)
	{
		delete m_pTarifPlansCollection;
		m_pTarifPlansCollection = 0;
	}
}
//End of DoDeleteEverything()


CCurrency CClubState::CalcIntervalPrice(CBusyInterval* pInterval)
{
		if (!pInterval)
			return 0;

	CCurrency Result = 0;

		try
		{
				if (pInterval->GetStartTime() > pInterval->GetFinishTime())
					throw CAnyLogableException("incorrect interval delivered to CalcIntervalPrice (interval's start time is greater than finish time)", bDoNotWriteDuplicates);

			CTarifPlan* pTarifPlan = &((*m_pTarifPlansCollection)[pInterval->GetTarifPlanNumber()]);

			CIntervalsStorage<CInterval> IntervalsCollection;

			// Весь временнОй промежуток, который надо оценить
			CInterval TotalInterval;
			TotalInterval.SetStartTime(pInterval->GetStartTime().TruncateToDay() + A_Day);
			TotalInterval.SetFinishTime(TotalInterval.GetStartTime() + pInterval->GetLength());

			IntervalsCollection.AddResident(TotalInterval);

			// Интервал для оценки
			CInterval IntervalToAddToPrice;
			// Для содержания временного нового резидента
			CInterval TempInterval;
			// Времена начала и окончания выбранного тарифного интервала
			CTimeStorage IterStart, IterFinish;
			CTimeStorage NormalizedIterStart, NormalizedIterFinish;
			// Результат поиска по pFreeIntervals
			CIntervalsStorage<CInterval>::iterator SearchResult;
			// Для организации цикла
			CTarifPlan::iterator EndIter = pTarifPlan->GetData()->end(),
						Iter = pTarifPlan->GetData()->begin();
				for (; Iter < EndIter; ++Iter)
				{
					IterStart = (**Iter).GetShortStartTime();
					IterFinish = (**Iter).GetShortFinishTime();

						do
						{
							NormalizedIterStart = IterStart;
							NormalizedIterFinish = IterFinish;

							PutTimeToInterval(&NormalizedIterStart, &TotalInterval);
							PutTimeToInterval(&NormalizedIterFinish, &TotalInterval);

								if (SearchResult != IntervalsCollection.GetData()->end())
								{
									SearchResult = IntervalsCollection.GetIntervalAtTime(NormalizedIterStart);
										if (NormalizedIterStart != NormalizedIterFinish)
										{
											TempInterval.SetStartTime(NormalizedIterFinish);
											TempInterval.SetFinishTime((*SearchResult)->GetFinishTime());
											(*SearchResult)->SetFinishTime(NormalizedIterStart);
											IntervalsCollection.AddResident(TempInterval);

											IntervalToAddToPrice.SetStartTime(NormalizedIterStart);
											IntervalToAddToPrice.SetFinishTime(NormalizedIterFinish);
											Result += DoGetPrice(pTarifPlan, *Iter, &IntervalToAddToPrice);
										}
								}
							IterStart += A_Day;
							IterFinish += A_Day;
						}
						while (IterStart < TotalInterval.GetFinishTime());
				}

			// Проход для определения, остались ли неоцененные отрезки
			CIntervalsStorage<CInterval>::iterator CollectionIter = IntervalsCollection.GetData()->begin(),
						CollectionEndIter = IntervalsCollection.GetData()->end();
				for (; CollectionIter < CollectionEndIter; ++CollectionIter)
				{
						if ( (*CollectionIter)->GetLength().GetTime() != 0 )
							throw CAnyLogableException((std::string)
										"incorrect tarif plan named " + (std::string)pTarifPlan->GetName(),
										bDoNotWriteDuplicates);
				}
		}
		catch(CAnyLogableException &e)
		{
			throw CAnyLogableException(std::string((std::string)
				"CClubState::CalcIntervalPrice failed: " + (std::string)e.what()), bDoNotWriteDuplicates);
		}
		catch(...)
		{
			throw CAnyLogableException("CClubState::CalcIntervalPrice failed", bDoNotWriteDuplicates);
		}

	return Result;
}
// End of CalcIntervalPrice


void CClubState::CalcIntervalFinishByPrice(CBusyInterval* pInterval, CCurrency& Price)
{
	// Реализован методом деления отрезка пополам для ускорения
	// разработки. По идее страшно нерационально, зато корректно.

	CBusyInterval SmallInterval = *pInterval, BigInterval = *pInterval, TestInterval = *pInterval;
	CCurrency SmallPrice = 0, BigPrice = 0, TestPrice = 0;

	SYSTEMTIME StartTime, FinishTime;
	pInterval->GetStartTime().GetTime(&StartTime);
	pInterval->GetFinishTime().GetTime(&FinishTime);

	SmallInterval.SetLengthFromStart((CTimeContainer)0);

	bool bBigPriceFailed, bTestPriceFailed;

		try
		{
			CTarifPlan* pTarifPlan = &((*m_pTarifPlansCollection)[pInterval->GetTarifPlanNumber()]);

				do
				{
					TestInterval.SetLengthFromStart( (SmallInterval.GetLength().GetTime() + BigInterval.GetLength().GetTime())/2 );

					SmallPrice = CalcIntervalPrice(&SmallInterval);

					bBigPriceFailed = false;
						try
						{
							BigPrice = CalcIntervalPrice(&BigInterval);
						}
						catch(CAnyLogableException)
						{
							bBigPriceFailed = true;
						}

					bTestPriceFailed = false;
						try
						{
							TestPrice = CalcIntervalPrice(&TestInterval);
						}
						catch(CAnyLogableException)
						{
							bTestPriceFailed = true;
						}

						if ( (TestPrice >= Price) || (bBigPriceFailed))
						{
							BigInterval = TestInterval;
								if (bTestPriceFailed)
									BigPrice = SmallPrice + 1;
								else
									BigPrice = TestPrice;
						}
						else
						{
							SmallInterval = TestInterval;
							SmallPrice = SmallPrice;
						}
				}
				while( !((SmallPrice == Price) || (BigPrice == Price) ||
							(SmallPrice == BigPrice)) );

				if (SmallPrice == Price)
				{
					*pInterval = SmallInterval;
				}
				else
				{
					Price = BigPrice;
					*pInterval = BigInterval;
				}
		}
		catch(CAnyLogableException &e)
		{
			throw CAnyLogableException(std::string((std::string)
				"CClubState::CalcIntervalPrice failed: " + (std::string)e.what()), bDoNotWriteDuplicates);
		}
		catch(...)
		{
			throw CAnyLogableException("CClubState::CalcIntervalPrice failed", bDoNotWriteDuplicates);
		}
}
// End of CalcIntervalFinishByPrice


void CClubState::PutTimeToInterval(CTimeStorage* pTime, CInterval* pInterval)
{
		if ((*pTime) < pInterval->GetStartTime())
			(*pTime) = pInterval->GetStartTime();
		if ((*pTime) > pInterval->GetFinishTime())
			(*pTime) = pInterval->GetFinishTime();
}
// End of PutTimeToInterval


CCurrency CClubState::DoGetPrice(CTarifPlan* pTarifPlan, CTarifInterval* pTarifInterval, CInterval* pInterval)
{
	return ceil( double(pInterval->GetLength().GetTime() *
				pTarifInterval->GetTarif())
				/ double((*pTarifPlan).GetStandardization().GetTime()) );
}
// End of DoGetPrice
