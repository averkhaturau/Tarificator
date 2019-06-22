#include "stdafx.h"

#include "Operator.h"

operator == (COperator _1, COperator _2)
{
	return _1.GetName() == _2.GetName();
}

operator != (COperator _1, COperator _2)
{
	return !(_1 == _2);
}