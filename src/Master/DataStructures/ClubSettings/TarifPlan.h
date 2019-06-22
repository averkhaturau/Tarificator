/*
	Обписывает тарифный план
*/
#ifndef _LX_TARIFPLAN_H_INCLUDED_
#define _LX_TARIFPLAN_H_INCLUDED_

#include "IntervalsStorage.h"
#include "TarifInterval.h"
#include "Operator.h"


class CTarifPlan : public CIntervalsStorage<CTarifInterval>
{
public:
	typedef std::vector<std::string> CUserNames;


	CTarifPlan(){ m_Permission = 0; m_Standardization = An_Hour; };
	virtual ~CTarifPlan(){};

	void SetStandardization(const CTimeStorage NewStandardization)
		{ m_Standardization = NewStandardization;};
	CTimeStorage GetStandardization() const { return m_Standardization;};

	// доступ к permission
	void SetPermission(CPermission Resolution)
		{ m_Permission = Resolution; };
	CPermission GetPermission() const { return m_Permission; };

	void SetName(const std::string& Name) { m_Name = Name; };
	std::string GetName() const { return m_Name; };

		// Проверяет чтобы интервалы были корректными
	virtual bool IsValidIntervalsCollection()
	{
		bool _not_result = 0; // чтобы было логически, а не побитно
		CTimeStorage _BarrierFinish;
		try{

			iterator _Iterator = GetData()->begin();
			_BarrierFinish = (*_Iterator)->GetStartTime();
			for (; _Iterator != GetData()->end(); ++_Iterator)
			{
				_not_result |= (_BarrierFinish != (*_Iterator)->GetStartTime()); // конец одного интервала совпадает с началом другого
				_BarrierFinish = (**_Iterator).GetFinishTime(); // FinishTime i-го интервала для i+1 шага
				_not_result |= !(**_Iterator).IsValidTimeInterval(); // все интервалы корректны
			}

		}catch(std::exception &e){
			 throw CTimeException((std::string)"Error in CIntervalsCollection<CTarifInterval*>::IsValidIntervalCollection(): "
				 +std::string(e.what()), bDoNotWriteDuplicates);
		}catch(...){
			 throw CTimeException("Error in CIntervalsCollection<CTarifInterval*>::IsValidIntervalCollection(): unhandled exception",
				 bDoNotWriteDuplicates);
		}
		return !_not_result; // чтобы было логически, а не побитно
	};

	// Для пустой коллекци возвращает FromTime
	void CalcTarifPlanStartFinish(CTimeStorage& FromTime, CInterval& Interval)
	{
		// Интервал, из которого потом будут вырезаться куски с помощью
		// функции GetFreeIntervals
		CInterval ReqInterval;
		// Начало суток, на которые указывает FromTime
		CTimeStorage FromTimeDay = FromTime - FromTime.TruncateToDay();

		ReqInterval.SetStartTime(FromTimeDay - A_Day);
		// Длина - сутки
		ReqInterval.SetLengthFromStart(3 * A_Day.GetTime());

		CIntervalsStorage<CInterval> FreeIntervals;

		// Пачка интервалов, образованных из данного плана
		CIntervalsStorage<CInterval> UnCycledIntervals;
		CInterval TempInterval;
			for (iterator Iter = GetData()->begin();
						Iter < GetData()->end(); ++Iter)
			{
				TempInterval.SetStartTime( (*Iter)->GetShortStartTime() + FromTimeDay );
				TempInterval.SetFinishTime( (*Iter)->GetShortFinishTime() + FromTimeDay );
				UnCycledIntervals.AddResident(TempInterval);

				TempInterval.SetStartTime(TempInterval.GetStartTime() - A_Day);
				TempInterval.SetFinishTime(TempInterval.GetFinishTime() - A_Day);
				UnCycledIntervals.AddResident(TempInterval);

				TempInterval.SetStartTime(TempInterval.GetStartTime() + A_Day + A_Day);
				TempInterval.SetFinishTime(TempInterval.GetFinishTime() + A_Day + A_Day);
				UnCycledIntervals.AddResident(TempInterval);
			}

		UnCycledIntervals.GetFreeIntervals(&FreeIntervals, ReqInterval, (CTimeContainer)0);

		CInterval** CurrentFree = FreeIntervals.GetIntervalAtTime(FromTime);
			if (CurrentFree != FreeIntervals.GetData()->end())
			{
				Interval.SetStartTime( (**CurrentFree).GetFinishTime() );

				CInterval** Next = FreeIntervals.GetNextInterval(Interval.GetStartTime());
					if (Next != FreeIntervals.GetData()->end())
						Interval.SetFinishTime( (**Next).GetStartTime() );
					else
						Interval.SetFinishTime(ReqInterval.GetFinishTime());
			}
			else
			{
				Interval.SetStartTime(FromTime);

				CInterval** Next = FreeIntervals.GetNextInterval(FromTime);
					if (Next != FreeIntervals.GetData()->end())
						Interval.SetFinishTime( (**Next).GetStartTime() );
					else
						Interval.SetFinishTime(ReqInterval.GetFinishTime());
			}
	};

	// Возвращает следующий по времени интервал за укзаным,
	// (кроме интервалов нулевой длины) иначе - iterator end()
	// Предварительно необходимо проверить корректность коллекции
	/*virtual iterator GetNextInterval(const CTimeStorage& Infimum)
	{
		try{
			iterator _Supremum = GetData()->end();
			iterator _Iter; // такое объявление разрешает несовместимость Borland и MS компиляторов

			// схватим первый попавшийся превышающий заданный интервал
			for (_Iter = GetData()->begin();
					_Iter != GetData()->end(); ++_Iter)
				if (((**_Iter)).GetStartTime() >= Infimum
					&& (**_Iter).GetLength() >= CTimeStorage((__int64)1) )
				{
					_Supremum = _Iter;
					break;
				}

			// найдём наименьший из превышающих заданный интервал
			for (_Iter = _Supremum;
					_Iter != GetData()->end(); ++_Iter)
				if ( ((**_Iter)).GetStartTime() >= Infimum
					&& ((**_Iter)).GetFinishTime()
						<= ((**_Supremum)).GetStartTime()
					&& (**_Iter).GetLength() >= CTimeStorage((__int64)1) )
				{
					_Supremum = _Iter;
				}

				if ( (_Supremum == GetData()->end()) && (Infimum.GetTime() != 0))
					return GetNextInterval(CTimeStorage((CTimeContainer)0));
				else
					return _Supremum;

		}catch(CAnyLogableException &e){
			throw CAnyLogableException(std::string((std::string)
				"GetNextInterval failed: " + (std::string)e.what()
				).c_str(), e.GetWriteDuplicatesToLog());
		}catch(...){
			throw CAnyLogableException("GetNextInterval failed",
				bDoNotWriteDuplicates);
		}
	}// end of iterator GetNextInterval(const CTimeStorage& Infimum)

	// Возвращает предыдущий по времени интервал перед укзаным,
	// (кроме интервалов нулевой длины) иначе - iterator end()
	// Предварительно необходимо проверить корректность коллекции
	virtual iterator GetPreviousInterval(const CTimeStorage& Supremum)
	{
		try{
			iterator _Infimum
				= GetData()->end();
			iterator _Iter; // такое объявление разрешает несовместимость Borland и MS компиляторов

			// схватим первый попавшийся превышающий заданный интервал
			for (_Iter = GetData()->begin();
					_Iter != GetData()->end(); ++_Iter)
				if (((**_Iter)).GetFinishTime() <= Supremum
					&& (**_Iter).GetLength() >= CTimeStorage((__int64)1) )
				{
					_Infimum = _Iter;
					break;
				}

			// найдём наименьший из превышающих заданный интервал
			for (_Iter = _Infimum;
					_Iter != GetData()->end(); ++_Iter)
				if (((**_Iter)).GetFinishTime() <= Supremum
					&& ((**_Iter)).GetFinishTime()
						>= ((**_Infimum)).GetStartTime()
					&& (**_Iter).GetLength() >= CTimeStorage((__int64)1) )
				{
					_Infimum = _Iter;
				}

				if ( (_Infimum == GetData()->end()) && (Supremum.GetTime() != A_Day))
					return GetPreviousInterval(A_Day);
				else
					return _Infimum;

		}catch(CAnyLogableException &e){
			throw CAnyLogableException(std::string((std::string)
				"GetPreviousInterval failed: "
				+ (std::string)e.what()).c_str(),
				e.GetWriteDuplicatesToLog());
		}catch(...){
			throw CAnyLogableException(
				"GetPreviousInterval failed",
				bDoNotWriteDuplicates);
		}
	}*/
	// end of iterator GetPreviousInterval(const CTimeStorage& Supremum)

	void SetTimeQuant(const CTimeStorage& Quant) { m_TimeQuant = Quant; };
	CTimeStorage GetTimeQuant() const { return  m_TimeQuant; };

	CUserNames *GetUserNames() {return &m_svUserNames;};

protected:
	// для определения прав юзера на установку (выбор) тарифного плана
	CPermission m_Permission;
	// определим квант времени, за который плата берётся
	CTimeStorage m_Standardization;
	// имя тарифного плана
	std::string m_Name;
	// определяет минимальную длину интервала
	CTimeStorage m_TimeQuant;

	// Список Юзеров, под которыми можно загружать клиента
	CUserNames m_svUserNames;
};
// end of class CTarifPlan

#endif // _LX_TARIFPLAN_H_INCLUDED_
