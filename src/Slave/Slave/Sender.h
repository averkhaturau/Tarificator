#ifndef __SENDER_H__
#define __SENDER_H__

#include "Messages.h"
#include "ManagersCollection.h"
#include "AsyncExchanger.h"


class CSender : virtual public CAsyncExchanger
{
	// ����������� ����� ��� ������ �������� ������

	public:
	private:
	protected:
	public:
		// �����������
		CSender();
		// ����������
		virtual ~CSender();

		// ����������� ������� �������� ������
		virtual void DoSendData(char* pData, DWORD dwSize) = 0;
};


#endif // __SENDER_H__