#include "stdafx.h"

#include "Commander.h"
#include "Exceptions.h"


CCommander::CCommander(std::string sPrefix, const DWORD* pdwMessagesTable, DWORD dwTableLength)
{
	m_pMessagesTable = 0;
	m_psPrefix = 0;

		try
		{
			m_psPrefix = new std::string;
			*m_psPrefix = sPrefix;

			m_pMessagesTable = new CVector;
			m_pMessagesTable->resize(dwTableLength);
				for (CVector::iterator iter = m_pMessagesTable->begin();
							iter < m_pMessagesTable->end(); ++iter, ++pdwMessagesTable)
				{
					*iter = *pdwMessagesTable;
				}
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CCommander::CCommander", bDoNotWriteDuplicates);
		}
}
// End of CCommander()


CCommander::~CCommander()
{
	DoDeleteEverything();
}
// End of ~CCommander()


void CCommander::DoDeleteEverything()
{
		if (m_psPrefix)
		{
			delete m_psPrefix;
			m_psPrefix = 0;
		}
		if (m_pMessagesTable)
		{
			delete m_pMessagesTable;
			m_pMessagesTable = 0;
		}
}
// End of DoDeleteEverything()
