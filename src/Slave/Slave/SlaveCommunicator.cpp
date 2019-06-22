#include "stdafx.h"

#include "SlaveCommunicator.h"
#include "Exceptions.h"
#include "Messages.h"
#include "NetworkConstants.h"


CSlaveCommunicator::CSlaveCommunicator()
{
	m_pIncoming = 0;
	m_pOutcoming = 0;
		try
		{
			m_pIncoming = new CIncoming(sMasterToSlavePrefix,
						&(MasterToSlaveMessages[0]), dwMasterToSlaveMsgLength);

			m_pOutcoming = new COutcoming(sSlaveToMasterPrefix,
						&(SlaveToMasterMessages[0]), dwSlaveToMasterMsgLength);
		}
		catch(CAnyLogableException)
		{
			DoDeleteEverything();
			throw;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CSlaveCommunicator::CSlaveCommunicator", bDoNotWriteDuplicates);
		}
}
// End of CSlaveCommunicator()


CSlaveCommunicator::~CSlaveCommunicator()
{
	DoDeleteEverything();
}
// End of ~CSlaveCommunicator()


void CSlaveCommunicator::DoDeleteEverything()
{
		if (m_pIncoming)
		{
			delete m_pIncoming;
			m_pIncoming = 0;
		}
		if (m_pOutcoming)
		{
			delete m_pOutcoming;
			m_pOutcoming = 0;
		}
}
// End of DoDeleteEverything()


void CSlaveCommunicator::OnDataReceived(char* pBuffer, DWORD dwSize, WPARAM wParam, LPARAM lParam)
{
	m_pIncoming->OnDataReceived(pBuffer, dwSize, wParam, lParam);
}
// End of OnDataReceived
