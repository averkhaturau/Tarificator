/*
	Описывает абстрактный атрибут класса CMasterManager,
	содержащий указатель на CMasterManager.
*/
#ifndef _LX_MasterMANAGERATTRIBUTE_H_INCLUDED
#define _LX_MasterMANAGERATTRIBUTE_H_INCLUDED

#include "MasterManager.h"

class CMasterManagerAttribute
{
	public:
		CMasterManagerAttribute();
		explicit CMasterManagerAttribute(CMasterManager* pMasterManager);
		virtual ~CMasterManagerAttribute();

	protected:
		CMasterManager* m_pMasterManager;

};

/* Copyrights: Alex Verkhoturov */
#endif //_LX_MasterMANAGERATTRIBUTE_H_INCLUDED