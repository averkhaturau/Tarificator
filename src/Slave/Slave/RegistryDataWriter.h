#ifndef __REGISTRYDATAWRITER_H__
#define __REGISTRYDATAWRITER_H__

#include "RegistryClass.h"


class CRegistryDataWriter : public virtual CRegistryClass
{
	private:
	protected:
		// Все они умеют райзить exception's
		void DoWriteRegistryNumber(PHKEY phkRegistryKey,
					const std::string& ValueName, const DWORD& ValueData);
		void DoWriteRegistryString(PHKEY phkRegistryKey,
					const std::string& ValueName, const std::string& ValueData);
		void DoWriteRegistryInt64(PHKEY phkRegistryKey,
					const std::string& ValueName, const __int64& ValueData);
		void DoDeleteRegistryKeyWithSubkeys(PHKEY phkRegistryKey,
					const std::string& SubKeyName);
		// Возвращает, был ли создан ключ до вызова функции
		void DoCreateRegistryKey(PHKEY phkRegistryKey,
					const std::string& SubKeyName, LPTSTR lpClass, DWORD dwOptions,
					REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
					PHKEY phkResult, LPDWORD lpdwDisposition);
	public:
		CRegistryDataWriter();
		virtual ~CRegistryDataWriter();
};


#endif // __REGISTRYDATAWRITER_H__