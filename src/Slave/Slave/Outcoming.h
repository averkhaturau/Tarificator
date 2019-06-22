#ifndef __OUTCOMING_H__
#define __OUTCOMING_H__

#include "Commander.h"


class COutcoming : public CCommander
{
	private:
	protected:
	public:
		COutcoming(std::string sPrefix, const DWORD* pdwMessagesTable, DWORD dwTableLength) :
					CCommander(sPrefix, pdwMessagesTable, dwTableLength) {};
		virtual ~COutcoming() {};

		// «аполн€ет содержимое пачки данных дл€ случа€ посылки дл€
		// уведомлени€ мастера о... Ќомер необходимого действи€ находитс€
		// из dwSlaveToMasterMessage перебором массива
		// SlaveToMasterMessages.
		void DoFillPacketContent(DWORD dwOutcomingMessage,
					char* pcBuffer, DWORD& dwBufferSize);
};


#endif // __OUTCOMING_H__