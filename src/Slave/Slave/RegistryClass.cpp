#include "stdafx.h"

#include "RegistryClass.h"
#include "Exceptions.h"


CRegistryClass::CRegistryClass()
{
		try
		{
			m_sSubKeyName = 0;
			m_sSubKeyName = new std::string;
			m_SAM = KEY_READ;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CRegistryDataReader::CRegistryDataReader() (may be not enough memory)", bDoNotWriteDuplicates);
		}
}
// End of CRegistryClass()


CRegistryClass::~CRegistryClass()
{
	DoDeleteEverything();
}
// End of ~CRegistryClass()


void CRegistryClass::DoDeleteEverything()
{
		if (m_sSubKeyName)
		{
			delete m_sSubKeyName;
			m_sSubKeyName = 0;
		}
}
// End of DoDeleteEverything()
