#include "stdafx.h"

#include "Incoming.h"
#include "Exceptions.h"


CIncoming::CIncoming(std::string sPrefix, const DWORD* pdwMessagesTable, DWORD dwTableLength) :
			CCommander(sPrefix, pdwMessagesTable, dwTableLength)
{
	m_dwTopLevelCommandsCallbackThreadId = GetCurrentThreadId();
	m_pReceivedCollection = 0;

		try
		{
			m_pReceivedCollection = new CAdditionalRecievedDatumCollection;
			m_pReceivedCollection->resize(50);
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CIncoming::CIncoming", bDoNotWriteDuplicates);
		}
}
// End of CIncoming


CIncoming::~CIncoming()
{
	DoDeleteEverything();
}
// End of ~CIncoming()


void CIncoming::OnDataReceived(char* pBuffer, DWORD dwSize, WPARAM wParam, LPARAM lParam)
{
		try
		{
				if ( (dwSize < strlen(m_psPrefix->c_str())) )
					return;

			bool bComparisonResult = true;
			char* pBufferPointer = pBuffer;
			const char* pcExample = &((m_psPrefix->begin())[0]);
				for (; (*pcExample) && (bComparisonResult); ++pBufferPointer, ++pcExample)
				{
					bComparisonResult = ( (*pcExample) == (*pBufferPointer) );
				}

				if (!bComparisonResult)
					return;

			char cIndex = *pBufferPointer;

				if (cIndex < m_pMessagesTable->size())
				{
						if (cIndex)
						{
							CAdditionalRecievedData* pAdditionalData = 0;
								if ( dwSize > (strlen(m_psPrefix->c_str()) + 1) )
								{
									++pBufferPointer;
									pAdditionalData = m_pReceivedCollection->GetFreeData();
										if(pAdditionalData)
										{
											pAdditionalData->SetIsUsed(true);
											pAdditionalData->GetData()->resize(dwSize - strlen(m_psPrefix->c_str()) - 1);
												for (int i = 0;
															i < pAdditionalData->GetData()->size(); ++i, ++pBufferPointer)
													(*pAdditionalData->GetData())[i] = *pBufferPointer;
										}
								}
							DWORD dwMessage = (*m_pMessagesTable)[cIndex];
							PostThreadMessage(m_dwTopLevelCommandsCallbackThreadId,
										dwMessage, wParam, (WPARAM)pAdditionalData);
						}
				}
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CSlaveCommunicator::OnDataReceived", bDoNotWriteDuplicates);
		}
}
// End of OnDataReceived


void CIncoming::DoDeleteEverything()
{
		if (m_pReceivedCollection)
		{
			delete m_pReceivedCollection;
			m_pReceivedCollection = 0;
		}
}
// End of DoDeleteEverything()
