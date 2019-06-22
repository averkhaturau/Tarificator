#include "stdafx.h"

#include "NewCommunicator.h"
#include "Exceptions.h"
#include "CommunicatorMessages.h"

#include <string>



CAsyncCommunicator::CAsyncCommunicator(HINSTANCE a_hInst)
{
		try
		{
			m_pAcceptManager = new CMultiThreadManager;
			m_pAcceptManager->SetNeedToTerminateThread(false);
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();
			throw CAnyLogableException(((std::string)"An error occured in CCommunicator::CCommunicator(): " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CCommunicator::CCommunicator()", bDoNotWriteDuplicates);
		}
}
// End of CAsyncCommunicator()


CAsyncCommunicator::~CAsyncCommunicator()
{
	DoDeleteEverything();
}
// End of ~CCommunicator()


void CAsyncCommunicator::DoDeleteEverything()
{
		if (m_pAcceptManager)
		{
			delete m_pAcceptManager;
			m_pAcceptManager = 0;
		}
}
// End of DoDeleteEverything()
