/*
	CMashinesCollection описывает состояние всех машин клуба
*/
#ifndef _LX_MASHINESCOLLECTION_H_INCLUDED_
#define _LX_MASHINESCOLLECTION_H_INCLUDED_

#include "MashineData.h"
#include "..\Saving\MasterBoundStorer.h"
#include "..\Saving\MasterRegistryStorer.h"
#include "..\ActiveContainerResizable.h"

class CMashinesCollection : public CActiveContainerResizable<CMashineData>
{
private:
	void DoDeleteEverything();
protected:
	typedef std::vector<bool> CBoolVector;

public:
	typedef void __stdcall CEnumMashinesFunction(CMashineData* pMashine, void* pParam);

	CMashinesCollection(CMasterBoundStorer* pStorer);
	CMashinesCollection(const bool a_bResponsable)
		: CActiveContainerResizable<CMashineData>(a_bResponsable){};

	virtual ~CMashinesCollection();

	// Занесение данных о машине
	void InsertMashine(CMashineData& MashineData);

	CMashineData* FindMashine(const DWORD& Aipishnick);
	// Вызывает pFunction для каждой машины. pParam -
	// application-defined parameter
	void EnumMashines(CEnumMashinesFunction* pFunction, void* pParam);

	void OnTimerEvent();
};

#endif //_LX_MASHINESCOLLECTION_H_INCLUDED_
