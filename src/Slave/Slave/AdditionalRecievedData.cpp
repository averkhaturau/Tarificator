#include "stdafx.h"

#include "AdditionalRecievedData.h"
#include "Exceptions.h"


CAdditionalRecievedData::CAdditionalRecievedData()
{
	m_pData = 0;
	m_pTimeOutManager = 0;
	m_bIsUsed = 0;

		try
		{
			m_pData = new CData;

			m_pTimeOutManager = new CTimeOutManager;
			m_pTimeOutManager->SetTimeOut(A_Minute.GetTime());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CAdditionalRecievedData::CAdditionalRecievedData()", bDoNotWriteDuplicates);
		}
}
// End of CAdditionalRecievedData()


CAdditionalRecievedData::~CAdditionalRecievedData()
{
	DoDeleteEverything();
}
// End of ~CAdditionalRecievedData()


void CAdditionalRecievedData::DoDeleteEverything()
{
		if (m_pData)
		{
			delete m_pData;
			m_pData = 0;
		}
		if (m_pTimeOutManager)
		{
			delete m_pTimeOutManager;
			m_pTimeOutManager = 0;
		}
}
// End of DoDeleteEverything()


void CAdditionalRecievedData::CheckForExpiration()
{
		if (m_pTimeOutManager->IsTimeExpired())
		{
			m_bIsUsed = false;
			m_pData->resize(0);
		}
}
// End of CheckForExpiration()


void CAdditionalRecievedData::SetIsUsed(bool a_bNew)
{
	m_bIsUsed = a_bNew;

	m_pTimeOutManager->OnBegin();
}
// End of SetIsUsed
