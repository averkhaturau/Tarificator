#ifndef __UPDATEMANAGER_H__
#define __UPDATEMANAGER_H__


// Абстрактный класс обновителя.
// Будет юзаться как класс-примесь для CMasterRegistryStorer.
class CUpdateManager
{
	private:
	protected:
	public:
		CUpdateManager();
		virtual ~CUpdateManager();
};

#endif // __UPDATEMANAGER_H__