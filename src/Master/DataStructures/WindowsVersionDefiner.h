#ifndef __WINDOWSVERSIONDEFINER_H__
#define __WINDOWSVERSIONDEFINER_H__


enum CVersions {Win9x, WinNT};

// Класс определителя версии Windows
class CWindowsVersionDefiner
{
	private:
	protected:
		// Версия маздая. Read-only, естественно.
		CVersions m_Version;
	public:
		// Тут собственно происходит определение версии и занесение
		// этой инфы в m_Version
		CWindowsVersionDefiner();
		~CWindowsVersionDefiner();

		// Обертки
		CVersions GetVersion() {return m_Version;};
};


#endif // __WINDOWSVERSIONDEFINER_H__