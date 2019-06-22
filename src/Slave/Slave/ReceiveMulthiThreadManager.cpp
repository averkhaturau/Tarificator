#include "stdafx.h"

#include "ReceiveMulthiThreadManager.h"


CReceiveMultiThreadManager::CReceiveMultiThreadManager()
{
	m_pReceiveParameters = 0;
}
// End of CReceiveMultiThreadManager()


CReceiveMultiThreadManager::~CReceiveMultiThreadManager()
{
		if (m_pReceiveParameters)
		{
			m_pReceiveParameters->SetUsed(false);
			m_pReceiveParameters = 0;
		}
}
// End of ~CReceiveMultiThreadManager()


bool CReceiveMultiThreadManager::OnTimerEvent()
{
	bool bReturn = false;
		if ( bReturn = CMultiThreadManager::OnTimerEvent())
		{
				if (m_pReceiveParameters)
				{
					m_pReceiveParameters->SetUsed(false);
					m_pReceiveParameters = 0;
				}
		}

	return bReturn;
}
// End of OnTimerEvent()
