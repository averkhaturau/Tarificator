/*
	Коллекция тарифных планов
*/
#ifndef _LX_TARIFPLANSCOLLECTION_INCLUDED_
#define _LX_TARIFPLANSCOLLECTION_INCLUDED_

#include "TarifPlan.h"
#include "..\ActiveContainerResizable.h"
#include "..\Saving\MasterBoundStorer.h"
#include <vector>

// никакой ответственности, просто оболочка
class CTarifPlansCollection : public CActiveContainerResizable<CTarifPlan>
{
public:

	CTarifPlansCollection(CMasterBoundStorer* pStorer)
		{ pStorer->ReadTarifPlansCollection(this); };

	//virtual ~CTarifPlansCollection(){ DoDeleteEverything(); };

	void AddTarifPlan(CTarifPlan& NewPlan) // просто такой интерфейс
		{ AddResident(NewPlan); };

};

#endif //_LX_TARIFPLANSCOLLECTION_INCLUDED_