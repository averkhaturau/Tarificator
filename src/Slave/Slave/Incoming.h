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

		// wParam � lParam ���������� ������ � �������������� ��������,
		// ����� ������ ��� ����������, �� ������ ������ slave ������ �������
		void OnDataReceived(char* pBuffer, DWORD dwSize, WPARAM wParam, LPARAM lParam);

		// �������
		DWORD GetTopLevelCommandsCallbackThreadId() {return m_dwTopLevelCommandsCallbackThreadId;};
		void SetTopLevelCommandsCallbackThreadId(DWORD dwNew) {m_dwTopLevelCommandsCallbackThreadId = dwNew;};
		CAdditionalRecievedDatumCollection* GetAdditionalReceivedDatumCollection() {return m_pReceivedCollection;};
};


#endif // __INCOMING_H__