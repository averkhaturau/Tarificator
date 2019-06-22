#ifndef __SLAVECOMMUNICATOR_H__
#define __SLAVECOMMUNICATOR_H__

#include "Incoming.h"
#include "Outcoming.h"


class CSlaveCommunicator
{
	// Абстрактный класс, предоставляющий интерфейс для посылки и
	// средства для формирования/разбора готовых команд
	private:
		void DoDeleteEverything();
	protected:
		CIncoming* m_pIncoming;
		COutcoming* m_pOutcoming;
	public:
		// Конструктор
		CSlaveCommunicator();
		// Деструктор
		virtual ~CSlaveCommunicator();

		// Посылает подтверждение о залочке машины
		virtual void SendLockSuccess() = 0;
		// Посылает подтверждение об отлочке машины
		virtual void SendUnLockSuccess() = 0;
		// Посылает уведомление о неуспехе залочки машины
		virtual void SendLockFail() = 0;
		// Посылает уведомление о неуспехе отлочки машины
		virtual void SendUnLockFail() = 0;
		// Посылает запрос на повторную посылку состояния машины
		virtual void SendReCheckState() = 0;

		void OnDataReceived(char* pBuffer, DWORD dwSize, WPARAM wParam, LPARAM lParam);
};


#endif // __SLAVECOMMUNICATOR_H__