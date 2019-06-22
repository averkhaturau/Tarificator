#ifndef __ASYNCEXCHANGER_H__
#define __ASYNCEXCHANGER_H__

#include "stdafx.h"


// Имеет средства для организации асинхронного обмена данными
class CAsyncExchanger
{
	private:
	protected:
		// Безопасная функция посылки мессаг
		void DoPostThreadMessage(DWORD dwCallbackThreadID, UINT Msg, WPARAM wParam, LPARAM lParam);
	public:
		CAsyncExchanger();
		virtual ~CAsyncExchanger();
};


#endif // __ASYNCEXCHANGER_H__