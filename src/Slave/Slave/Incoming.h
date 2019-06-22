#ifndef __INCOMING_H__
#define __INCOMING_H__

#include "Commander.h"
#include "AdditionalRecievedDatumCollection.h"


class CIncoming : public CCommander
{
	private:
		void DoDeleteEverything();
	protected:
		DWORD m_dwTopLevelCommandsCallbackThreadId;
		CAdditionalRecievedDatumCollection* m_pReceivedCollection;
	public:
		CIncoming(std::string sPrefix, const DWORD* pdwMessagesTable, DWORD dwTableLength);
		virtual ~CIncoming();

		// wParam и lParam передаются дальше с результирующей мессагой,
		// чтобы мастер мог распознать, от какого именно slave пришла мессага
		void OnDataReceived(char* pBuffer, DWORD dwSize, WPARAM wParam, LPARAM lParam);

		// Обертки
		DWORD GetTopLevelCommandsCallbackThreadId() {return m_dwTopLevelCommandsCallbackThreadId;};
		void SetTopLevelCommandsCallbackThreadId(DWORD dwNew) {m_dwTopLevelCommandsCallbackThreadId = dwNew;};
		CAdditionalRecievedDatumCollection* GetAdditionalReceivedDatumCollection() {return m_pReceivedCollection;};
};


#endif // __INCOMING_H__