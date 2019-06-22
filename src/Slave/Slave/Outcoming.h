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

		// ��������� ���������� ����� ������ ��� ������ ������� ���
		// ����������� ������� �... ����� ������������ �������� ���������
		// �� dwSlaveToMasterMessage ��������� �������
		// SlaveToMasterMessages.
		void DoFillPacketContent(DWORD dwOutcomingMessage,
					char* pcBuffer, DWORD& dwBufferSize);
};


#endif // __OUTCOMING_H__