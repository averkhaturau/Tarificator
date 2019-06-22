#include "stdafx.h"

#include "RegistryDataReader.h"
#include "Exceptions.h"


CRegistryDataReader::CRegistryDataReader()
{

}
// End of CRegistryDataReader()


CRegistryDataReader::~CRegistryDataReader()
{

}
// End of ~CRegistryDataReader()


void CRegistryDataReader::DoOpenRegistryKey(PHKEY phkKey)
{
	*phkKey = 0;
	LONG lResult = RegOpenKeyEx(m_hKey, m_sSubKeyName->c_str(), 0, m_SAM, phkKey);
		if ( !(lResult == ERROR_SUCCESS) )
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, lResult,
						NULL, Buffer.begin(), 0xfe, NULL);

			throw CAnyLogableException((std::string)"can't open registry key " + *m_sSubKeyName + ": " + Buffer, bDoNotWriteDuplicates);
		}
}
// End of DoOpenRegistryKey()


void CRegistryDataReader::DoReadRegistryString(PHKEY phkKey,
			const std::string& ValueName, unsigned char* pValueData, DWORD& nSize)
{
	DWORD dwType = REG_SZ;
	LONG lResult = RegQueryValueEx(*phkKey, ValueName.c_str(), 0, &dwType, pValueData, &nSize);
		// Если какая-то ошибка - вызываю исключение
		if ( !(lResult == ERROR_SUCCESS) )
		{
			throw CAnyLogableException("Can't read string registry value " + ValueName, bDoNotWriteDuplicates);
		}
}
// End of DoReadRegistryString


void CRegistryDataReader::DoReadRegistryNumber(PHKEY phkKey,
					const std::string& ValueName, DWORD& ValueData)
{
	DWORD dwType = REG_DWORD;
	DWORD nSize = sizeof(DWORD);
	LONG lResult = RegQueryValueEx(*phkKey, ValueName.c_str(), 0, &dwType, (unsigned char*)&ValueData, &nSize);
		if ( !(lResult == ERROR_SUCCESS) )
		{
			throw CAnyLogableException("Can't read registry value " + ValueName, bDoNotWriteDuplicates);
		}
}
// End of DoReadRegistryNumber


void CRegistryDataReader::DoReadOneRegistryName(PHKEY phkKey,
			const std::string& ValueName, FileName& ValueData)
{
	DWORD nSize;
	DoReadRegistryString(phkKey, ValueName, NULL, nSize);
	ValueData.resize(nSize);
		if (!nSize)
			return;
	DoReadRegistryString(phkKey, ValueName, (unsigned char*)ValueData.begin(), nSize);
	ValueData.resize(ValueData.size() - 1);
}
// End of DoReadOneRegistryName


void CRegistryDataReader::DoCloseRegistryKey(PHKEY phkKey)
{
		if (*phkKey)
		{
			RegCloseKey(*phkKey);
			*phkKey = 0;
		}
}
// End of CloseRegistryKey


void CRegistryDataReader::DoReadRegistryInt64(PHKEY phkRegistryKey,
					const std::string& ValueName, __int64& ValueData)
{
	//DWORD dwType = /*REG_BINARY*/REG_DWORD_LITTLE_ENDIAN;
	DWORD dwType;
	DWORD nSize = sizeof(__int64);
	DWORD nRealSize = 0;
	LONG lResult = RegQueryValueEx(*phkRegistryKey, ValueName.c_str(), 0, &dwType, NULL, &nRealSize);
		if ( !(lResult == ERROR_SUCCESS) )
		{
			throw CAnyLogableException("Can't read registry value " + ValueName, bDoNotWriteDuplicates);
		}
		if (nRealSize != nSize)
		{
			throw CAnyLogableException("Can't read registry value (must be 8 bytes long) " + ValueName, bDoNotWriteDuplicates);
		}
	lResult = RegQueryValueEx(*phkRegistryKey, ValueName.c_str(), 0, &dwType, (unsigned char*)&ValueData, &nSize);
		if ( !(lResult == ERROR_SUCCESS) )
		{
			throw CAnyLogableException("Can't read registry value " + ValueName, bDoNotWriteDuplicates);
		}
}
// End of DoReadRegistryInt64


void CRegistryDataReader::DoReadRegistryPath(PHKEY phkRegistryKey,
					const std::string& ValueName, std::string* pValueData, bool bSlashEnded)
{
	char cBuffer[1024];

	bool bError = false;
		try
		{
			DoReadOneRegistryName( phkRegistryKey, ValueName, *pValueData );
		}
		catch(CAnyLogableException)
		{
			bError = true;
		}

		if (!bError)
		{
				if (bSlashEnded)
				{
					ExpandEnvironmentStrings(pValueData->c_str(), &(cBuffer[0]), 1020);
					*pValueData = cBuffer;

						if ( (*pValueData)[0] )
						{
							char cLast = (pValueData->c_str())[strlen(pValueData->c_str()) - 1];
								if ( (cLast != '\\') )
									*pValueData += "\\";
						}
				}
		}
		else
			*pValueData = "";
}
// End of DoReadRegistryPath
