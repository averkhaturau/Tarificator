#ifndef _LX_BUSYINTERVALHIST_H_INCLUDED___
#define _LX_BUSYINTERVALHIST_H_INCLUDED___

/*
 *		BusyIntervalHist.h - коллекци€ интервалов
 *		с изменени€ми реальных интервалов.
 *
 *		 ласс гарантирует, что интервалы в коллекции
 *		расположоны по-пор€дку их добавлени€.
 */


#include "..\ActiveContainerResizable.h"
#include "BusyInterval.h"
#include "..\..\..\Slave\Slave\Exceptions.h"

class CBusyIntervalHist
	: public CActiveContainerResizable<CBusyInterval>
{
public:
	// ќб€зательно должен быть первый интервал
	explicit CBusyIntervalHist(CBusyInterval& FirstInterval)
	{
		AddResident(FirstInterval);
	};

	CBusyIntervalHist(CBusyIntervalHist& BIH)
	{
		for (iterator _Iter = BIH.GetData()->begin();
			_Iter < BIH.GetData()->end(); ++_Iter)
		{
			AddResident(**_Iter);
		}
		m_Number = BIH.m_Number;
	};

	CBusyIntervalHist(){};

	inline operator CBusyInterval()
	{
		return *GetCurrentInterval();
	};

	virtual ~CBusyIntervalHist(){};

	// чтобы гарантировать, что добавл€емый интервал в конце, просто скопируем
	inline CBaseContainer::reference AddResident(CBusyInterval &BusyInterval)
	{
#pragma warning( push )
#pragma warning( disable : 4172 )

		try{
			CBusyInterval* pNewResident;
			if (IsResponsable())
			{
				pNewResident = new CBusyInterval;
				(*pNewResident) = BusyInterval;
				m_BaseContainer.push_back(pNewResident);
			}
			else
			{
				pNewResident = &BusyInterval;
				m_BaseContainer.push_back(pNewResident);
			}

			return pNewResident;
		}catch(std::exception &e){
			throw std::runtime_error((std::string)"AddResident failed "+std::string(e.what()));
		}catch(...){
			throw std::runtime_error((std::string)"AddResident failed: Unknown exception");
		}
#pragma warning( pop )
	};

	virtual bool IsTimeInInterval(const CTimeStorage& TimeAsked)
	{
		return GetCurrentInterval()->IsTimeInInterval(TimeAsked);
	};

	CBusyInterval* GetLastButOne()
	{
		if (size() >= 2)
		{
			// возвращаем предпоследний
			iterator _Iter = m_BaseContainer.end();
			return *(--(--_Iter));
		}

		return 0;
	};

	CBusyInterval* GetCurrentInterval()
	{
		if (size() == 0)
			throw CAnyLogableException("CBusyIntervalHist::GetCurrentInterval() failed", bDoNotWriteDuplicates);
		return m_BaseContainer.back();
	};

	virtual bool IsValidTimeInterval() {return true;};
	virtual void SetStartTime(const CTimeStorage& Start) {GetCurrentInterval()->SetStartTime(Start);};
	virtual CTimeStorage GetStartTime() {return GetCurrentInterval()->GetStartTime();};

	virtual CTimeStorage GetFinishTime() {return GetCurrentInterval()->GetFinishTime();};

	virtual CTimeStorage GetLength() {return GetCurrentInterval()->GetLength();};


	virtual void SetInterval(const CTimeStorage& Start, const CTimeStorage& Finish) {GetCurrentInterval()->SetInterval(Start, Finish);};
	virtual void GetInterval(CTimeStorage& Start, CTimeStorage& Finish) {GetCurrentInterval()->GetInterval(Start, Finish);};

	virtual void SetLengthFromStart(const CTimeStorage& Length) {GetCurrentInterval()->SetLengthFromStart(Length);};

	CBusyIntervalHist& operator=(CBusyIntervalHist& Hist)
	{
		Clear();

		for (iterator _Iter = Hist.GetData()->begin();
			_Iter < Hist.GetData()->end(); ++_Iter)
		{
			AddResident(**_Iter);
		}
		m_Number = Hist.m_Number;

		return *this;
	};

public:
	// маздай, которого не должно быть в следующей версии:
	unsigned int m_Number;

	bool operator ==(CBusyIntervalHist& _2);
};

#endif // _LX_BUSYINTERVALHIST_H_INCLUDED___
