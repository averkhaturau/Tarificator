/*
	Абстрактный класс для сохранения мастера и восстановления
*/
#ifndef _LX_MASTERBOUNDSTORER_H_INCLUDED_
#define _LX_MASTERBOUNDSTORER_H_INCLUDED_

#include <string>

#include "Windows.h"
#include "..\..\..\Slave\Slave\Exceptions.h"
#include "..\..\..\Slave\Slave\NetworkParametersDataReader.h"
#include "..\ClubSettings\TimeStorage.h"
#include "..\ClubSettings\TimeInterval.h"
#include "..\CashStorer.h"
#include "..\..\..\Slave\Slave\DataReader.h"

class CMashinesCollection;
class COperatorsCollection;
class CBusyIntervalsCollection;
class CTarifPlansCollection;
class CTarifPlan;
class CMasterManager;
class CIntervalsAncestor;
class CClubState;
class CFileUpdateManager;

class CMasterBoundStorer :
		public CNetworkParametersDataReader,
		public CCashStorer, public CDataReader
{
public:
	CMasterBoundStorer(){};
	virtual ~CMasterBoundStorer(){};

	virtual void ReadFileUpdateManager(CFileUpdateManager* pFileUpdateManager) =0;

	virtual void ReadWorkingInterval(CIntervalsAncestor* TimeInterval) =0;
	
	// заполняет данными MashinesCollection
	virtual void ReadMashinesCollection(CMashinesCollection* pMashinesCollection) =0;

	virtual void ReadMashinesCollectionHistory(CMashinesCollection* pMashinesCollection, CInterval& ReadInterval) =0;

	// читает тарифный план
	virtual void ReadTarifPlansCollection(CTarifPlansCollection* pTarifPlan) =0;

	// читает операторов
	virtual void ReadOperatorsCollection(COperatorsCollection* pOperatorsCollection) =0;

	virtual void ReadMasterManager(CMasterManager* pManager) = 0;

	// сэйвает MashinesCollection
	virtual void SaveMashinesCollection(CMashinesCollection* pMashinesCollection) =0;

	virtual void SaveMashinesCollectionToHistory(CMashinesCollection* pMashinesCollection) =0;

	virtual void SaveBusyIntervalsToHistory(int iMachine, CBusyIntervalsCollection* pBusyIntervalsCollection) =0;

	virtual void SaveOperatorsToHistrory(COperatorsCollection* pOperatorColl) =0;

	virtual void SaveOperatorsChanged(COperatorsCollection* pOperatorColl) =0;

	virtual void SaveTarifPlansToHistrory(CTarifPlansCollection* pTarifPlansColl) =0;

	virtual void ReadClubState(CClubState* pClubState) =0;

	virtual bool SaveClubStateToHistory(CClubState* pClubState, const CTimeStorage& TimeToSplitHistory) =0;

protected:
	// генеряет имена для нумерующихся объектов (Mashine001, Interval002...)
	//std::string GenerateName(const std::string sObjName, DWORD Number,
	//	const unsigned short int _NumDigits = 3) const
	// - Унаследована от CDataReader
};

#endif // _LX_MASTERBOUNDSTORER_H_INCLUDED_