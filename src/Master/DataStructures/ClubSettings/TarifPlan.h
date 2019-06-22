/*
	���������� �������� ����
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

	// ������ � permission
	void SetPermission(CPermission Resolution)
		{ m_Permission = Resolution; };
	CPermission GetPermission() const { return m_Permission; };

	void SetName(const std::string& Name) { m_Name = Name; };
	std::string GetName() const { return m_Name; };

		// ��������� ����� ��������� ���� �����������
	virtual bool IsValidIntervalsCollection()
	{
		bool _not_result = 0; // ����� ���� ���������, � �� �������
		CTimeStorage _BarrierFinish;
		try{

			iterator _Iterator = GetData()->begin();
			_BarrierFinish = (*_Iterator)->GetStartTime();
			for (; _Iterator != GetData()->end(); ++_Iterator)
			{
				_not_result |= (_BarrierFinish != (*_Iterator)->GetStartTime()); // ����� ������ ��������� ��������� � ������� �������
				_BarrierFinish = (**_Iterator).GetFinishTime(); // FinishTime i-�� ��������� ��� i+1 ����
				_not_result |= !(**_Iterator).IsValidTimeInterval(); // ��� ��������� ���������
			}

		}catch(std::exception &e){
			 throw CTimeException((std::string)"Error in CIntervalsCollection<CTarifInterval*>::IsValidIntervalCollection(): "
				 +std::string(e.what()), bDoNotWriteDuplicates);
		}catch(...){
			 throw CTimeException("Error in CIntervalsCollection<CTarifInterval*>::IsValidIntervalCollection(): unhandled exception",
				 bDoNotWriteDuplicates);
		}
		return !_not_result; // ����� ���� ���������, � �� �������
	};

	// ��� ������ �������� ���������� FromTime
	void CalcTarifPlanStartFinish(CTimeStorage& FromTime, CInterval& Interval)
	{
		// ��������, �� �������� ����� ����� ���������� ����� � �������
		// ������� GetFreeIntervals
		CInterval ReqInterval;
		// ������ �����, �� ������� ��������� FromTime
		CTimeStorage FromTimeDay = FromTime - FromTime.TruncateToDay();

		ReqInterval.SetStartTime(FromTimeDay - A_Day);
		// ����� - �����
		ReqInterval.SetLengthFromStart(3 * A_Day.GetTime());

		CIntervalsStorage<CInterval> FreeIntervals;

		// ����� ����������, ������������ �� ������� �����
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

	// ���������� ��������� �� ������� �������� �� �������,
	// (����� ���������� ������� �����) ����� - iterator end()
	// �������������� ���������� ��������� ������������ ���������
	/*virtual iterator GetNextInterval(const CTimeStorage& Infimum)
	{
		try{
			iterator _Supremum = GetData()->end();
			iterator _Iter; // ����� ���������� ��������� ��������������� Borland � MS ������������

			// ������� ������ ���������� ����������� �������� ��������
			for (_Iter = GetData()->begin();
					_Iter != GetData()->end(); ++_Iter)
				if (((**_Iter)).GetStartTime() >= Infimum
					&& (**_Iter).GetLength() >= CTimeStorage((__int64)1) )
				{
					_Supremum = _Iter;
					break;
				}

			// ����� ���������� �� ����������� �������� ��������
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

	// ���������� ���������� �� ������� �������� ����� �������,
	// (����� ���������� ������� �����) ����� - iterator end()
	// �������������� ���������� ��������� ������������ ���������
	virtual iterator GetPreviousInterval(const CTimeStorage& Supremum)
	{
		try{
			iterator _Infimum
				= GetData()->end();
			iterator _Iter; // ����� ���������� ��������� ��������������� Borland � MS ������������

			// ������� ������ ���������� ����������� �������� ��������
			for (_Iter = GetData()->begin();
					_Iter != GetData()->end(); ++_Iter)
				if (((**_Iter)).GetFinishTime() <= Supremum
					&& (**_Iter).GetLength() >= CTimeStorage((__int64)1) )
				{
					_Infimum = _Iter;
					break;
				}

			// ����� ���������� �� ����������� �������� ��������
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
	// ��� ����������� ���� ����� �� ��������� (�����) ��������� �����
	CPermission m_Permission;
	// ��������� ����� �������, �� ������� ����� ������
	CTimeStorage m_Standardization;
	// ��� ��������� �����
	std::string m_Name;
	// ���������� ����������� ����� ���������
	CTimeStorage m_TimeQuant;

	// ������ ������, ��� �������� ����� ��������� �������
	CUserNames m_svUserNames;
};
// end of class CTarifPlan

#endif // _LX_TARIFPLAN_H_INCLUDED_
