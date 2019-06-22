#include "stdafx.h"

#include "ReceiveManagersCollection.h"


// Свободные функции
void __stdcall CheckForExpiration(CReceiveMultiThreadManager* pManager, LPARAM lParam)
{
		if (pManager->GetAnotherThread())
		{
			pManager->OnTimerEvent();
		}
};
// Конец свободных функций


CReceiveManagersCollection::CReceiveManagersCollection()
{
	m_pData = 0;

		try
		{
			m_pData = new CVector;
			resize(0);
		}
		catch(...)
		{
			DoDeleteEverything();
		}
}
// End of CReceiveManagersCollection()


CReceiveManagersCollection::CReceiveManagersCollection(SizeType uiInitialSize)
{
	m_pData = 0;

		try
		{
			m_pData = new CVector;
			resize(uiInitialSize);
		}
		catch(...)
		{
			DoDeleteEverything();
		}
}
// End of CReceiveManagersCollection


CReceiveManagersCollection::~CReceiveManagersCollection()
{
	DoDeleteEverything();
}
// End of ~CReceiveManagersCollection()


void CReceiveManagersCollection::DoDeleteEverything()
{
	resize(0);
		if (m_pData)
		{
			delete m_pData;
			m_pData = 0;
		}
}
// End of DoDeleteEverything()


SizeType CReceiveManagersCollection::size()
{
	return m_pData->size();
}
// End of size()


void CReceiveManagersCollection::resize(SizeType uiNewSize)
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
					*iter = new CReceiveMultiThreadManager;
					(*iter)->SetNeedToTerminateThread(false);
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


CReceiveMultiThreadManager* CReceiveManagersCollection::GetFreeManager()
{
	CVector::iterator EndIter = m_pData->end();
	for (CVector::iterator Iter = m_pData->begin(); Iter < EndIter; ++Iter)
	{
			if ( !((*Iter)->GetAnotherThread()) )
				return *Iter;
	}

	return 0;
}
// End of GetFreeManager()


void CReceiveManagersCollection::EnumManagers(EnumFunction* pFunction, LPARAM lParam)
{
	CVector::iterator EndIter = m_pData->end();
		for (CVector::iterator Iter = m_pData->begin(); Iter < EndIter; Iter++)
		{
			pFunction(*Iter, lParam);
		}
}
// End of EnumManagers


void CReceiveManagersCollection::OnTimerEvent()
{
	EnumManagers(CheckForExpiration, 0);
}
// End of OnTimerEvent()
