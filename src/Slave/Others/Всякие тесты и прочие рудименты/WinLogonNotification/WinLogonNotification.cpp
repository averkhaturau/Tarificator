#include "stdafx.h"

#include "WinLogonNotification.h"

//#include "..\Slave\ErrorsLogger.h"
#include "..\Slave\SlaveRegistryDataReader.h"

#include "Lmcons.h"


#pragma data_seg(".SharedData")
char cLoggedUserName[UNLEN + 1] = "";
#pragma data_seg()


/*BOOL APIENTRY DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved )
{
		switch (dwReason)
		{
				case DLL_PROCESS_ATTACH:
					DisableThreadLibraryCalls (hInstance);
				break;

				case DLL_THREAD_ATTACH:
				case DLL_THREAD_DETACH:
				case DLL_PROCESS_DETACH:
				break;
		}

	return TRUE;
}*/



VOID WriteUserName(LPCTSTR a_psName)
{
	//CErrorsLogger* pLogger;
		try
		{
			CSlaveRegistryDataReader Reader;

			Reader.WriteUserName(a_psName);

			/*Reader.SetKey(HKEY_LOCAL_MACHINE);
			Reader.SetSecurityAccessMask(KEY_READ);
			*(Reader.GetSubKeyName()) = "SYSTEM\\CurrentControlSet\\Services\\Slave Service\\Parameters";
			pLogger = new CErrorsLogger(&Reader);

				if (pLogger)
					*pLogger->GetLogFileName() = "e:\Log.txt";

				if (pLogger)
				{
					pLogger->AddLogEntry( ((std::string)a_psName).c_str(), bWriteDuplicates );
				}

				if (pLogger)
				{
					delete pLogger;
					pLogger = 0;
				}*/
		}
		catch(...)
		{

		}
}
// End of WriteUserName



VOID LogonEventHandler(PWLX_NOTIFICATION_INFO pInfo)
{
	WideCharToMultiByte(
				CP_ACP,
				WC_NO_BEST_FIT_CHARS,
				pInfo->UserName,
				-1,
				&(cLoggedUserName[0]),
				UNLEN,
				0,
				0);

	WriteUserName( &(cLoggedUserName[0]) );
}
// End of LogonEventHandler


VOID LogoffEventHandler(PWLX_NOTIFICATION_INFO pInfo)
{
	cLoggedUserName[0] = '\0';

	WriteUserName( &(cLoggedUserName[0]) );
}
// End of LogoffEventHandler


VOID LockEventHandler(PWLX_NOTIFICATION_INFO pInfo)
{
	cLoggedUserName[0] = '\0';

	WriteUserName( &(cLoggedUserName[0]) );
}
// End of LockEventHandler


VOID UnLockEventHandler(PWLX_NOTIFICATION_INFO pInfo)
{
	WideCharToMultiByte(
				CP_ACP,
				WC_NO_BEST_FIT_CHARS,
				pInfo->UserName,
				-1,
				&(cLoggedUserName[0]),
				UNLEN,
				0,
				0);

	WriteUserName( &(cLoggedUserName[0]) );
}
// End of UnLockEventHandler


VOID DisconnectEventHandler(PWLX_NOTIFICATION_INFO pInfo)
{
	cLoggedUserName[0] = '\0';

	WriteUserName( &(cLoggedUserName[0]) );
}
// End of DisconnectEventHandler


VOID ReconnectEventHandler(PWLX_NOTIFICATION_INFO pInfo)
{
	WideCharToMultiByte(
				CP_ACP,
				WC_NO_BEST_FIT_CHARS,
				pInfo->UserName,
				-1,
				&(cLoggedUserName[0]),
				UNLEN,
				0,
				0);

	WriteUserName( &(cLoggedUserName[0]) );
}
// End of ReconnectEventHandler
