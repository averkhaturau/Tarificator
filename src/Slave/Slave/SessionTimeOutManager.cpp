#include "stdafx.h"

#include "SessionTimeOutManager.h"


CSessionTimeOutManager::CSessionTimeOutManager()
{
	m_dwSessionId = 0;
}
// End of CSessionTimeOutManager()


CSessionTimeOutManager::~CSessionTimeOutManager()
{

}
// End of ~CSessionTimeOutManager()


CSessionTimeOutManager::CSessionTimeOutManager(DWORD a_dwSessionId, CTimeContainer a_TimeOut)
{
	m_dwSessionId = a_dwSessionId;
	SetTimeOut(a_TimeOut);
	SetEnabled(true);
	OnBegin();
}
// End of CSessionTimeOutManager


bool CSessionTimeOutManager::operator==(CSessionTimeOutManager& a_Other)
{
	return ( (m_dwSessionId == a_Other.m_dwSessionId) &&
				/*(CTimeOutManager::operator==(a_Other))*/
				(m_TimeOut == a_Other.m_TimeOut) );
}
// End of operator==
