#include "stdafx.h"

#include "InvertedTimeOutManager.h"


CInvertedTimeOutManager::CInvertedTimeOutManager()
{
	m_TimeOut = (CTimeContainer)0;
	m_EdgeTime = (CTimeContainer)0;
	m_bEnabled = false;
}
// End of CInvertedTimeOutManager()


CInvertedTimeOutManager::~CInvertedTimeOutManager()
{

}
// End of ~CInvertedTimeOutManager()


bool CInvertedTimeOutManager::IsTimeExpired()
{
	return ( CheckForExpiration() && (m_bEnabled) );
}
// End of IsTimeExpired()


bool CInvertedTimeOutManager::CheckForExpiration()
{
	return (CurrentTime() > m_EdgeTime - m_TimeOut);
}
// End of CheckForExpiration()
