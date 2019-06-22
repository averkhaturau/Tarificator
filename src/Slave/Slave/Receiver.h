#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "AsyncExchanger.h"


// ����������� ����������� ������
class CReceiver : virtual public CAsyncExchanger
{
	friend DWORD WINAPI ReceiveProc(void* pParam);

	private:
	protected:
		// �������� Notification, ��� ������ ������, � �������� ������
		// � ����� ������� ��� �������� � ������ �����
		void DoPostReceiveNotification(DWORD dwCallbackThreadID, void* pData, DWORD uiSize);
	public:
		// ����������� �� ���������
		CReceiver();
		// ����������
		virtual ~CReceiver();
};


#endif // __RECEIVER_H__