/*
	Implementation of CMasterManagerAttribute
*/
#include "stdafx.h"
#include "MasterManagerAttribute.h"

// the default constructor
CMasterManagerAttribute::CMasterManagerAttribute()
{
	m_pMasterManager = 0;
}
// the end of the default constructor

// explicit constructor
CMasterManagerAttribute::CMasterManagerAttribute(CMasterManager* pMasterManager)
{
	m_pMasterManager = pMasterManager;
}
// the end of the explicit constructor

// the destructor
CMasterManagerAttribute::~CMasterManagerAttribute()
{
}
// the end of the destructor

/* Copyrights: Alex Verkhoturov */