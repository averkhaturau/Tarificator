#ifndef __LISTENER_H__
#define __LISTENER_H__

#include "AsyncExchanger.h"

#include "Winsock2.h"


// Абстрактный класс асинхронного принимателя данных
class CListener : virtual public CAsyncExchanger
{
	private:
	protected:
	public:
		// Конструктор по умолчанию
		CListener();
		// Деструктор
		virtual ~CListener();
};


#endif // __LISTENER_H__