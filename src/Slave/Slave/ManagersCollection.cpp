#include "stdafx.h"

#include "ManagersCollection.h"


// ��������� �������
void __stdcall CheckForExpiration(CMultiThreadManager* pManager, LPARAM lParam)
{
		if (pManager->GetAnotherThread())
		{
			pManager->OnTimerEvent();
		}
};
// ����� ��������� �������


CManagersCollection::CManagersCollection()
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
// End of CManagersCollection()


CManagersCollection::CManagersCollection(SizeType uiInitialSize)
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
// End of CManagersCollection


CManagersCollection::~CManagersCollection()
{
	DoDeleteEverything();
}
// End of ~CManagersCollection()


void CManagersCollection::DoDeleteEverything()
{
	resize(0);
		if (m_pData)
		{
			delete m_pData;
			m_pData = 0;
		}
}
// End of DoDeleteEverything()


SizeType CManagersCollection::size()
{
	return m_pData->size();
}
// End of size()


void CManagersCollection::resize(SizeType uiNewSize)
{
	SizeType uiOldSize = m_pData->size();

		if (uiNewSize > uiOldSize)
		{
			// ������ ����� ������
			m_pData->resize(uiNewSize);
				for (CVector::iterator iter = m_pData->begin() + uiOldSize;
						iter < m_pData->end();
						++iter)
				{
					*iter = new CMultiThreadManager;
				}
		}
		else
		{
				/* ������ ������. ���� uiNewSize == uiOldSize, ����
				�� ����������� �� ����. */
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


CMultiThreadManager* CManagersCollection::GetFreeManager()
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


void CManagersCollection::EnumManagers(EnumFunction* pFunction, LPARAM lParam)
{
	CVector::iterator EndIter = m_pData->end();
		for (CVector::iterator Iter = m_pData->begin(); Iter < EndIter; Iter++)
		{
			pFunction(*Iter, lParam);
		}
}
// End of EnumManagers


void CManagersCollection::OnTimerEvent()
{
	EnumManagers(CheckForExpiration, 0);
}
// End of OnTimerEvent()
