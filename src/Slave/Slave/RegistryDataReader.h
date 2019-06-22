#ifndef __REGISTRYDATAREADER_H__
#define __REGISTRYDATAREADER_H__

#include "NamesCollection.h"
#include "RegistryClass.h"


class CRegistryDataReader : public virtual CRegistryClass
{
	// Класс, инкапсулирующий все, что надо для работы с реестром.
	private:
		// Читает строку и если надо - генерит exception. Используется в
		// ReadOneName.
		void DoReadRegistryString(PHKEY phkRegistryKey,
					const std::string& ValueName, unsigned char* pValueData, DWORD& nSize);
	protected:
		// Открывает ключ реестра. Может генерять исключения.
		void DoOpenRegistryKey(PHKEY phkKey);
		// Если надо - закрывает ключ реестра
		void DoCloseRegistryKey(PHKEY phkKey);
		// Эту функцию надо использовать, чтобы прочитать строку из реестра
		void DoReadOneRegistryName(PHKEY phkRegistryKey, const std::string& ValueName, FileName& ValueData);
		// Читает DWORD и умеет генерить исключение
		void DoReadRegistryNumber(PHKEY phkRegistryKey,
					const std::string& ValueName, DWORD& ValueData);
		// Читает путь каталога или файла, разворачивает переменные
		// окружения. Если bSlashEnded - следит, чтобы последним символом
		// был '\\'.
		void DoReadRegistryPath(PHKEY phkRegistryKey,
					const std::string& ValueName, std::string* pValueData, bool bSlashEnded);
		void DoReadRegistryInt64(PHKEY phkRegistryKey,
					const std::string& ValueName, __int64& ValueData);
	public:
		// Конструктор по умолчанию
		CRegistryDataReader();
		// Деструктор
		virtual ~CRegistryDataReader();
};


#endif // __REGISTRYDATAREADER_H__