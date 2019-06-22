#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "AsyncExchanger.h"


// Асинхронный приниматель данных
class CReceiver : virtual public CAsyncExchanger
{
	friend DWORD WINAPI ReceiveProc(void* pParam);

	private:
	protected:
		// Посылает Notification, что пришли данные, и передает вектор
		// с этими данными для поюзания в родной поток
		void DoPostReceiveNotification(DWORD dwCallbackThreadID, void* pData, DWORD uiSize);
	public:
		// Конструктор по умолчанию
		CReceiver();
		// Деструктор
		virtual ~CReceiver();
};


#endif // __RECEIVER_H__