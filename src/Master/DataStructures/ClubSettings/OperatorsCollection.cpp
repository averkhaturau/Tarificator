#include "stdafx.h"

#include "OperatorsCollection.h"
#include "..\Saving\MasterBoundStorer.h"


COperatorsCollection::COperatorsCollection(CMasterBoundStorer* pStorer)
{
	pStorer->ReadOperatorsCollection(this);
}
// End of COperatorsCollection()


void COperatorsCollection::AddOperator(COperator& NewOperator)
{
	AddResident(NewOperator);
}
// End of AddOperator


void COperatorsCollection::DeleteOperator(const std::string& OperatorName)
{
	DeleteResident(COperator(OperatorName));
}
// End of DeleteOperator
