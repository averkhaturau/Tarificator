#include "stdafx.h"

#include "TimeOutManager.h"
#include "Exceptions.h"


CTimeOutManager::CTimeOutManager()
{
	m_bEnabled = false;
	m_TimeOut = (CTimeContainer)0;
	m_Begin = (CTimeContainer)0;//CurrentTime();
}
// End of CTimeOutManager()


CTimeOutManager::CTimeOutManager(CTimeOutManager* pManager)
{
		try
		{
			m_bEnabled = pManager->GetEnabled();
			m_TimeOut = pManager->GetTimeOut();
			m_Begin = (CTimeContainer)0;//pManager->m_Begin;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CTimeOutManager::CTimeOutManager", bDoNotWriteDuplicates);
		}
}
// End of CTimeOutManager


CTimeOutManager::~CTimeOutManager()
{

}
// End of ~CTimeOutManager()


void CTimeOutManager::OnBegin()
{
		try
		{
			m_Begin = CurrentTime();
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CTimeOutManager::OnBegin: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CTimeOutManager::OnBegin", bDoNotWriteDuplicates);
		}
}
// End of OnBegin()


bool CTimeOutManager::IsTimeExpired()
{
		if (!m_bEnabled)
			return false;

	bool bResult = false;
		try
		{
			CTimeStorage Curr = CurrentTime();
				if (m_Begin <= Curr)
					bResult = (Curr - m_Begin) >= m_TimeOut;
				else
					//throw CAnyLogableException("Illegal start time in CTimeOutManager::IsTimeExpired()", bDoNotWriteDuplicates);
					bResult = true;
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CTimeOutManager::IsTimeExpired: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CTimeOutManager::IsTimeExpired", bDoNotWriteDuplicates);
		}

	return bResult;
}
// End of IsTimeExpired()


void CTimeOutManager::SetArtificialTimeOutState()
{
	m_Begin = CurrentTime() - m_TimeOut - A_Minute;
}
// End of SetArtificailTimeOutState()


bool CTimeOutManager::operator==(CTimeOutManager& a_Other)
{
	return ( (m_TimeOut == a_Other.m_TimeOut) &&
				(m_Begin == a_Other.m_Begin) && (m_bEnabled == a_Other.m_bEnabled) );
}
// End of operator==
