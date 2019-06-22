#ifndef _LX_INTERVALSSTORAGE_H_INCLUDED__
#define _LX_INTERVALSSTORAGE_H_INCLUDED__

#include "..\ActiveContainerResizable.h"
#include "TimeStorage.h"
#include "TimeInterval.h"

template<class CIntervalClass>
	class CIntervalsStorage
		: public CActiveContainerResizable<CIntervalClass>
{
	typedef CIntervalsStorage<CIntervalClass> _tMe;
public:
	CIntervalsStorage(){};
	virtual ~CIntervalsStorage(){};

	// Проверяет чтобы интервалы были корректными
	//virtual bool IsValidIntervalsCollection() {};

	// Входит ли время в один из интервалов
	bool IsTimeInIntervals(const CTimeStorage& TimeAsked)
	{
		return GetIntervalAtTime(TimeAsked) != m_BaseContainer.end();
	};

	// Возвращает следующий по времени интервал за укзаным,
	// (кроме интервалов нулевой длины) иначе - iterator end()
	// Предварительно необходимо проверить корректность коллекции
	iterator GetNextInterval(const CTimeStorage& Infimum)
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
	iterator GetPreviousInterval(const CTimeStorage& Supremum)
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
	}// end of iterator GetPreviousInterval(const CTimeStorage& Supremum)

	// работает некорректно на перекрывающейся коллекции,
	// возвращает end() если нет такого интервала
	iterator GetIntervalAtTime(const CTimeStorage& PointedTime)
	{
		for (iterator _Iter = GetData()->begin();
					_Iter != GetData()->end(); ++_Iter)
			if ( (**_Iter).IsTimeInInterval(PointedTime) )
				break;

		return _Iter;
	};


	void PutTimeToInterval(CTimeStorage* pTime, CInterval* pInterval)
	{
			if ((*pTime) < pInterval->GetStartTime())
				(*pTime) = pInterval->GetStartTime();
			if ((*pTime) > pInterval->GetFinishTime())
				(*pTime) = pInterval->GetFinishTime();
	}


	// принимает созданную Collection,
	// целиком переписывает, возвращает дополнение к себе
	void GetFreeIntervals(
		CIntervalsStorage<CInterval>* pFreeIntervals,
		CInterval& ReqInterval,
		CTimeStorage MinimumIntervalLength
	)
	{
			// Затычка, чтобы можно было ни о чем не волноваться и
			// передавать в функцию 0
			if (MinimumIntervalLength.GetTime() == 0)
				MinimumIntervalLength.SetTime((CTimeContainer)1);

		// некорректно работает с перекрывающимися интервалами
		try{
			CIntervalsStorage<CInterval> TempFreeIntervals;
			// Формирование TempFreeIntervals
			{
				TempFreeIntervals.AddResident(ReqInterval);

				CTimeStorage IterStart, IterFinish;
				// Для содержания временного нового резидента
				CInterval TempInterval;
				// Результат поиска по pFreeIntervals
				CIntervalsStorage<CInterval>::iterator SearchResult;
				// Для организации цикла
				CIntervalsStorage<CIntervalClass>::iterator EndIter = GetData()->end(),
							Iter = GetData()->begin();
				for (; Iter < EndIter; ++Iter)
				{
					IterStart = (*Iter)->GetStartTime();
					PutTimeToInterval(&IterStart, &ReqInterval);

					IterFinish = (*Iter)->GetFinishTime();
					PutTimeToInterval(&IterFinish, &ReqInterval);

					SearchResult = TempFreeIntervals.
								GetIntervalAtTime(IterStart);
					if (SearchResult != TempFreeIntervals.GetData()->end())
					{
						if (IterStart != IterFinish)
						{
							TempInterval.SetStartTime(IterFinish);
							TempInterval.SetFinishTime(
								(*SearchResult)->GetFinishTime());
							(*SearchResult)->SetFinishTime(IterStart);
							TempFreeIntervals.AddResident(TempInterval);
						}
					}
				}
			}

			// Убивание слишком мелких интервалов (фильтрующее копирование)
			{
				CIntervalsStorage<CInterval>::iterator Iter
					= TempFreeIntervals.GetData()->begin(),
						EndIter = TempFreeIntervals.GetData()->end();
					for (; Iter != EndIter; ++Iter)
						if ((*Iter)->GetLength() >= MinimumIntervalLength)
							pFreeIntervals->AddResident((**Iter));
			}
		}
		catch(CAnyLogableException &e){
			throw CAnyLogableException(std::string((std::string)
				"GetFreeIntervals failed: " + (std::string)e.what()
				).c_str(), e.GetWriteDuplicatesToLog());
		}catch(...){
			throw CAnyLogableException("GetFreeIntervals failed",
				bDoNotWriteDuplicates);
		}
	};

	// Отщепляет интервалы, которые закончились ранее, чем SplitTime
	// возвращает их, удаляя из коллекции.
	void SplitHistory(const CTimeStorage& SplitTime, _tMe *pHBIC)
	{
  		int _i;
		try{

			for (iterator _Iter = GetData()->begin();
					_Iter != GetData()->end(); ++_Iter)
			{
				if ((**_Iter).GetFinishTime() < SplitTime)
				{
					pHBIC->AddResident(**_Iter);
				}
			}

			for (_Iter = pHBIC->GetData()->begin();
					_Iter != pHBIC->GetData()->end(); ++_Iter)
			{
				CBusyIntervalHist *_tempBIC = *_Iter;
				this->DeleteResident(*_tempBIC);
			}

			for (_Iter = GetData()->begin(), _i = 0;
					_Iter != GetData()->end(); ++_Iter)
				(**_Iter).m_Number = _i++;

		}
		catch(CAnyLogableException &e){
			throw CAnyLogableException(std::string((std::string)
				"SplitHistory failed: " + (std::string)e.what()
				).c_str(), e.GetWriteDuplicatesToLog());
		}catch(...){
			throw CAnyLogableException("SplitHistory failed",
				bDoNotWriteDuplicates);
		}
	};

	// Возвращает время дозавершения текущего интервала
	CTimeStorage GetTimeRemaining(const CTimeStorage &a_TimeNow)
	{
		iterator TempIter = GetIntervalAtTime(a_TimeNow);
		if (TempIter != GetData()->end())
			return (*TempIter)->GetFinishTime()-a_TimeNow;

		return CTimeStorage((CTimeContainer)0);
	};
};

#endif // _LX_INTERVALSSTORAGE_H_INCLUDED__