#ifndef __RECEIVEMANAGERSCOLLECTION_H__
#define __RECEIVEMANAGERSCOLLECTION_H__

#include "ReceiveMulthiThreadManager.h"

#include <vector>


typedef unsigned long int SizeType;

// Пачка MultiThreadManager's с ограничением размера. Сделана на базе
// вектора.
class CReceiveManagersCollection
{
	public:
		typedef std::vector<CReceiveMultiThreadManager*> CVector;
		typedef void __stdcall EnumFunction(CReceiveMultiThreadManager* pManager, LPARAM lParam);

	private:
		void DoDeleteEverything();
	protected:
		// Пачка данных
		CVector* m_pData;
	public:
		// Конструктор по умолчанию
		CReceiveManagersCollection();
		// Конструктор с указанием начального размера
		CReceiveManagersCollection(SizeType uiInitialSize);
		// Деструктор
		~CReceiveManagersCollection();

		SizeType size();
		void resize(SizeType uiNewSize);
		// Выдает Manager, который можно заюзать, или 0, если все
		// манагеры уже заюзаны
		CReceiveMultiThreadManager* GetFreeManager();
		// Перебирает все манагеры и вызывает для них функцию pFunction.
		// lParam - application-defined value. Нужно, например, для проверки
		// таймаутов.
		void EnumManagers(EnumFunction* pFunction, LPARAM lParam);
		// Проверяет, не истекло ли время манагеров
		void OnTimerEvent();

		// Обертки
		// Не рекомендуется юзать
		CVector* GetData() {return m_pData;};
};


#endif // __RECEIVEMANAGERSCOLLECTION_H__