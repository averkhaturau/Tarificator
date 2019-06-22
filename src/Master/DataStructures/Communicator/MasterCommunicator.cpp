#include "stdafx.h"

#include "MasterCommunicator.h"
#include "..\..\..\Slave\Slave\NetworkConstants.h"
#include "..\..\..\Slave\Slave\Exceptions.h"


CMasterCommunicator::CMasterCommunicator()
{
	m_pIncoming = 0;
	m_pOutcoming = 0;

		try
		{
			m_pIncoming = new CIncoming(sSlaveToMasterPrefix,
						&(SlaveToMasterMessages[0]), dwSlaveToMasterMsgLength);
			m_pOutcoming = new COutcoming(sMasterToSlavePrefix,
						&(MasterToSlaveMessages[0]), dwMasterToSlaveMsgLength);
		}
		catch(CAnyLogableException)
		{
			DoDeleteEverything();
			throw;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CMasterCommunicator::CMasterCommunicator", bDoNotWriteDuplicates);
		}
}
// End of CMasterCommunicator()


CMasterCommunicator::~CMasterCommunicator()
{
	DoDeleteEverything();
}
// End of ~CMasterCommunicator()


void CMasterCommunicator::DoDeleteEverything()
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


void CMasterCommunicator::OnDataReceived(char* pBuffer, DWORD dwSize,
			WPARAM wParam, LPARAM lParam)
{
	m_pIncoming->OnDataReceived(pBuffer, dwSize, wParam, lParam);
}
// End of OnDataReceived
