/*
	Содержит данные операторов
*/
#ifndef _LX_OPERATORSCOLLECTION_H_INCLUDED_
#define _LX_OPERATORSCOLLECTION_H_INCLUDED_

#include "Operator.h"
#include <vector>
#include "..\ActiveContainerResizable.h"


// Predefinition
class CMasterBoundStorer;

class COperatorsCollection : public CActiveContainerResizable<COperator>
{
public:
	COperatorsCollection(CMasterBoundStorer* pStorer);

	void AddOperator(COperator& NewOperator);

	void DeleteOperator(const std::string& OperatorName);
};

#endif //_LX_OPERATORSCOLLECTION_H_INCLUDED_