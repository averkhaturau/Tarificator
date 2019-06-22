#include "stdafx.h"

#include "Outcoming.h"
#include "Exceptions.h"


void COutcoming::DoFillPacketContent(DWORD dwOutcomingMessage,
			char* pcBuffer, DWORD& dwBufferSize)
{
		try
		{
			const char* pcCommandPrefix = &((*m_psPrefix)[0]);
				for (; *pcBuffer = *pcCommandPrefix; ++pcBuffer, ++pcCommandPrefix) {}

			char dwCommandNumber = 0;
				for (char i = 0; i < m_pMessagesTable->size(); ++i)
				{
						if ((*m_pMessagesTable)[i] == dwOutcomingMessage)
						{
							dwCommandNumber = i;
							break;
						}
				}
			*pcBuffer = dwCommandNumber;

				if (dwCommandNumber)
					dwBufferSize = strlen(m_psPrefix->c_str()) + 1;
				else
					throw CAnyLogableException("can't find message number to send to master", bDoNotWriteDuplicates);
		}
		catch(CAnyLogableException)
		{
			throw;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CSlaveCommunicator::DoFillPacketContent", bDoNotWriteDuplicates);
		}
}
// End of DoFillPacketContent
