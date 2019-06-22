#ifndef __MANAGERSCOLLECTION_H__
#define __MANAGERSCOLLECTION_H__

#include "MultiThreadManager.h"

#include <vector>


typedef unsigned long int SizeType;

// Пачка MultiThreadManager's с ограничением размера. Сделана на базе
// вектора.
// Этот класс, как оказалось, не юзается ни в мастере, ни в Slave.
class CManagersCollection
{
	public:
		typedef std::vector<CMultiThreadManager*> CVector;
		typedef void __stdcall EnumFunction(CMultiThreadManager* pManager, LPARAM lParam);

	private:
		void DoDeleteEverything();
	protected:
		// Пачка данных
		CVector* m_pData;
	public:
		// Конструктор по умолчанию
		CManagersCollection();
		// Конструктор с указанием начального размера
		CManagersCollection(SizeType uiInitialSize);
		// Деструктор
		~CManagersCollection();

		SizeType size();
		void resize(SizeType uiNewSize);
		// Выдает Manager, который можно заюзать, или 0, если все
		// манагеры уже заюзаны
		CMultiThreadManager* GetFreeManager();
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


#endif // __MANAGERSCOLLECTION_H__