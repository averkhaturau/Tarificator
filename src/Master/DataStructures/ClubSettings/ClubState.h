#ifndef __CLUBSTATE_H__
#define __CLUBSTATE_H__

#include <string>
#include "OperatorsCollection.h"
#include "MashinesCollection.h"
#include "TarifPlansCollection.h"
#include "..\Saving\MasterBoundStorer.h"

/*
	��������� ��������� ���� ����� �����, ����� �� ���������, ��� �����...
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
		// ����������� � ��������� ������ ��������� ������
		CClubState(CMasterBoundStorer* pMasterStorer);
		// ����������
		virtual ~CClubState();

		// ��������� ���� ���������. ��������� � ���� ������, �.�. ���
		// ���������� ���� ����� ����� TarifInterval.
		CCurrency CalcIntervalPrice(CBusyInterval* pInterval);

		// ��������� Finish �� Start, ��������� ����� � ����.
		// ������������� ���� ����� ��������� ������� �������, ��� ���
		// � Price ������������ �������� ����. pInterval ������
		// ��� ��������� ������������ Finish.
		void CalcIntervalFinishByPrice(CBusyInterval* pInterval, CCurrency& Price);

		// �������
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
