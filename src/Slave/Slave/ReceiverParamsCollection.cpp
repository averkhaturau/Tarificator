#include "stdafx.h"

#include "ReceiverParamsCollection.h"
#include "Exceptions.h"


CReceiverParamsCollection::CReceiverParamsCollection()
{
	m_pData = 0;
		try
		{
			m_pData = new CVector;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CReceiverParamsCollection::CReceiverParamsCollection", bDoNotWriteDuplicates);
		}
}
// End of CReceiverParamsCollection()


CReceiverParamsCollection::~CReceiverParamsCollection()
{
	DoDeleteEverything();
}
// End of ~CReceiverParamsCollection()


void CReceiverParamsCollection::DoDeleteEverything()
{
	resize(0);

		if (m_pData)
		{
			delete m_pData;
			m_pData = 0;
		}
}
// End of DoDeleteEverything()


SizeType CReceiverParamsCollection::size()
{
	return m_pData->size();
}
// End of size()


void CReceiverParamsCollection::resize(SizeType uiNewSize)
{
	SizeType uiOldSize = m_pData->size();

		if (uiNewSize > uiOldSize)
		{
			// Создаю новые строки
			m_pData->resize(uiNewSize);
				for (CVector::iterator iter = m_pData->begin() + uiOldSize;
						iter < m_pData->end();
						++iter)
				{
					*iter = new CReceiveParameters;
				}
		}
		else
		{
				/* Убиваю строки. Если uiNewSize == uiOldSize, цикл
				не выполняется ни разу. */
				for (CVector::iterator iter = m_pData->begin() + uiNewSize;
						iter < m_pData->end();
						++iter)
				{
					delete *iter;
				}
			m_pData->resize(uiNewSize);
		}
}
// End of resize


CReceiveParameters* CReceiverParamsCollection::GetFreeParams()
{
	CVector::iterator EndIter = m_pData->end();
		for (CVector::iterator Iter = m_pData->begin(); Iter < EndIter; ++Iter)
		{
			(*Iter)->OnTimer();
				if ( !((*Iter)->GetUsed()) )
					return (*Iter);
		}

	return 0;
}
// End of GetFreeParams()
