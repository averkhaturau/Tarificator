#ifndef __SENDER_H__
#define __SENDER_H__

#include "Messages.h"
#include "ManagersCollection.h"
#include "AsyncExchanger.h"


class CSender : virtual public CAsyncExchanger
{
	// Абстрактный класс для обмена пакетами данных

	public:
	private:
	protected:
	public:
		// Конструктор
		CSender();
		// Деструктор
		virtual ~CSender();

		// Абстрактная функция передачи данных
		virtual void DoSendData(char* pData, DWORD dwSize) = 0;
};


#endif // __SENDER_H__