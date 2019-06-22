#include "stdafx.h"

#include "RegistryFileManager.h"
#include "Exceptions.h"

//#include "MSI.H"

// Эта функция выдрана из MSDN, так что не пугайся.
BOOL EnablePrivilege(LPCTSTR szPrivName, BOOL fEnable)
{
	HANDLE hToken;
	bool bResult = true;
	bResult = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
		if (!bResult)
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);
			throw CAnyLogableException("Can't execute OpenProcessToken API function: " + Buffer, bDoNotWriteDuplicates);
		}
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	LookupPrivilegeValue(NULL, szPrivName, &tp.Privileges[0].Luid);
	tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

	return((GetLastError() == ERROR_SUCCESS));
}








// Собственно определение класса

// Конструктор
CRegistryFileManager::CRegistryFileManager()
{
	m_Hist_key = 0;
	m_Curr_key = 0;
		try
		{
			EnablePrivilege(SE_RESTORE_NAME, TRUE);
			EnablePrivilege(SE_BACKUP_NAME, TRUE);
		}
		catch(...)
		{
			// Тут ничего не надо делать, т.к. exception
			// при выполнении EnablePrivilege - реальная
			// некритическая ошибка (при запуске под
			// админским аккаутом будет все OK, а под
			// тарификатором - нет).
		}
}
// End of CRegistryFileManager()


CRegistryFileManager::~CRegistryFileManager()
{
		try
		{
			EnablePrivilege(SE_RESTORE_NAME, FALSE);
			EnablePrivilege(SE_BACKUP_NAME, FALSE);
		}
		catch(...)
		{
			// Тут ничего не надо делать, т.к. exception
			// при выполнении EnablePrivilege - реальная
			// некритическая ошибка (при запуске под
			// админским аккаутом будет все OK, а под
			// тарификатором - нет).
		}
}
// End of ~CRegistryFileManager()

void CRegistryFileManager::SaveHistToFile(CFileName* pName)
{
	SaveKeyToFile(m_Hist_key, pName);
}

void CRegistryFileManager::SaveCurrToFile(CFileName* pName)
{
	SaveKeyToFile(m_Curr_key, pName);
}

void CRegistryFileManager::SaveKeyToFile(HKEY Key, CFileName* pName)
{
	LONG lResult = RegSaveKey(Key, pName->c_str(), NULL);
	if ( !(lResult == ERROR_SUCCESS) )
	{
		char cStr[0xff];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | (FORMAT_MESSAGE_MAX_WIDTH_MASK & 0xff),
					0, lResult, 0, cStr, 0xfe, 0);
		throw CAnyLogableException(
				(std::string)"can't save registry key. Possible reason is SE_BACKUP_NAME privilege not enabled. Please enable \"Back up files and directories\" privilege for tarificator's user account. System message: " +
				(std::string)cStr, bDoNotWriteDuplicates);
	}
}
// End of SaveToFile


void CRegistryFileManager::RestoreFromFile(CFileName* pName)
{
	LONG lResult = RegRestoreKey(m_Curr_key, pName->c_str(), REG_NO_LAZY_FLUSH);
	if ( !(lResult == ERROR_SUCCESS) )
	{
		char cStr[0xff];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | (FORMAT_MESSAGE_MAX_WIDTH_MASK & 0xff),
					0, lResult, 0, cStr, 0xfe, 0);
		throw CAnyLogableException(
					(std::string)"can't restore registry key. Possible reason is SE_RESTORE_NAME privilege not enabled. Please enable \"Restore files and directories\" privilege for tarificator's user account. System message: " +
					(std::string)cStr, bDoNotWriteDuplicates);
	}
}
// End of RestoreFromFile
