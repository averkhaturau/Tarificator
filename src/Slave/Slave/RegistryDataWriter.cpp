#include "stdafx.h"

#include "RegistryDataWriter.h"
#include "Exceptions.h"

#include "shlwapi.h"


CRegistryDataWriter::CRegistryDataWriter()
{

}
// End of CRegistryDataWriter()


CRegistryDataWriter::~CRegistryDataWriter()
{

}
// End of ~CRegistryDataWriter()


void CRegistryDataWriter::DoWriteRegistryNumber(PHKEY phkRegistryKey,
			const std::string& ValueName, const DWORD& ValueData)
{
	LONG lResult = RegSetValueEx(*phkRegistryKey, ValueName.c_str(),
				0, REG_DWORD, (unsigned char*)&ValueData, sizeof(DWORD));
		if (lResult != ERROR_SUCCESS)
			throw CAnyLogableException("Can't write registry value " + ValueName, bDoNotWriteDuplicates);
}
// End of DoWriteRegistryNumber


void CRegistryDataWriter::DoWriteRegistryInt64(PHKEY phkRegistryKey,
			const std::string& ValueName, const __int64& ValueData)
{
	LONG lResult = RegSetValueEx(*phkRegistryKey, ValueName.c_str(),
				0, REG_BINARY, (unsigned char*)&ValueData, sizeof(__int64));
		if (lResult != ERROR_SUCCESS)
			throw CAnyLogableException("Can't write registry value " + ValueName, bDoNotWriteDuplicates);
}
// End of DoWriteRegistryInt64


void CRegistryDataWriter::DoDeleteRegistryKeyWithSubkeys(PHKEY phkRegistryKey,
			const std::string& SubKeyName)
{
	LONG lResult = SHDeleteKey(*phkRegistryKey, SubKeyName.c_str());
		if (lResult != ERROR_SUCCESS)
			throw CAnyLogableException("Can't delete registry key " + SubKeyName, bDoNotWriteDuplicates);
}
// End of DoDeleteRegistryKeyWithSubkeys


void CRegistryDataWriter::DoCreateRegistryKey(PHKEY phkRegistryKey,
					const std::string& SubKeyName, LPTSTR lpClass, DWORD dwOptions,
					REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
					PHKEY phkResult, LPDWORD lpdwDisposition)
{
	LONG lResult = RegCreateKeyEx(*phkRegistryKey, SubKeyName.c_str(),
				0, lpClass, dwOptions, samDesired, lpSecurityAttributes,
				phkResult, lpdwDisposition);

		if (lResult != ERROR_SUCCESS)
			throw CAnyLogableException("Can't create registry key " + SubKeyName, bDoNotWriteDuplicates);
}
// End of DoCreateRegistryKey


void CRegistryDataWriter::DoWriteRegistryString(PHKEY phkRegistryKey,
			const std::string& ValueName, const std::string& ValueData)
{
	LONG lResult = RegSetValueEx(*phkRegistryKey, ValueName.c_str(),
				0, REG_SZ, (const unsigned char*)ValueData.c_str(), strlen(ValueData.c_str()));
		if (lResult != ERROR_SUCCESS)
			throw CAnyLogableException("Can't write registry value " + ValueName, bDoNotWriteDuplicates);
}
// End of DoWriteRegistryString
