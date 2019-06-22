#ifndef __REGISTRYFILEMANAGER_H__
#define __REGISTRYFILEMANAGER_H__


#include "RegistryClass.h"

#include <string>

// Класс для сохранения из реестра в .reg-файл и наоборот. Под
// Win95 будет работать хреново. Под 98 вроде все ОК
// (см. в MSDN RegSaveKey).
class CRegistryFileManager : public virtual CRegistryClass
{
	public:
		typedef std::string CFileName;
	private:
	protected:
		HKEY m_Hist_key;
		HKEY m_Curr_key;
	public:
		CRegistryFileManager();
		virtual ~CRegistryFileManager();

		// Сохраняет ключ Key в файл с именем pName
		void SaveKeyToFile(HKEY Key, CFileName* pName);
		void SaveCurrToFile(CFileName* pName);
		void SaveHistToFile(CFileName* pName);

		void RestoreFromFile(CFileName* pName);
};


#endif // __REGISTRYFILEMANAGER_H__