#include "stdafx.h"

#include "fcntl.h"

#include "Winreg.h"

#include "SlaveRegistryDataReader.h"
#include "ErrorsLogger.h"
//#include "TimerHandler.h"
#include "SlaveManager.h"
#include "Messages.h"
#include "SlaveTPC_IP_Communicator.h"
#include "TCP_IP_SocketHolder.h"
#include "NetworkConstants.h"
#include "SlaveService.h"

#include "Lmcons.h"


#include "NewUserDefiner.h"









BOOL EnablePrivilege(HANDLE hToken, LPCTSTR szPrivName,
			BOOL fEnable)
{
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	LookupPrivilegeValue(NULL, szPrivName, &tp.Privileges[0].Luid);
	tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
	return((GetLastError() == ERROR_SUCCESS));
}

void EnableDebugPrivForCurrentThread()
{
	HANDLE hCurrentToken;
		if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,
					&hCurrentToken))
		{
				if (EnablePrivilege(hCurrentToken, SE_DEBUG_NAME, TRUE))
				{
					// OK
				}
			CloseHandle(hCurrentToken);
		}
}















int APIENTRY WinMain(HINSTANCE hInstance,
			HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//int main(int argc, char* argv[])
{
	/*EnableDebugPrivForCurrentThread();

	CNewUserDefiner NewUserDefiner;
	std::string Name = NewUserDefiner.GetInteractivelyLoggedUserName();*/












	/*HMODULE hDllModule = LoadLibrary( "c:\\Program Files\\Slave\\logon.dll" );
	typedef void CGetLoggedUserName(LPTSTR a_pName, DWORD a_dwMaxLength);
	CGetLoggedUserName* pGetUserNameFunction = (CGetLoggedUserName*)GetProcAddress(hDllModule, "GetLoggedUserName");

	char cBuffer[UNLEN + 1];
	pGetUserNameFunction(&(cBuffer[0]), UNLEN);*/




	// Create the service object
	CSlaveService SlaveService(hInstance);
    
		// Parse for standard arguments (install, uninstall, version etc.)
		if (!SlaveService.ParseStandardArgs(1, lpCmdLine))
		{
			// Didn't find any standard args so start the service
			// Uncomment the DebugBreak line below to enter the debugger
			// when the service is started.
			//DebugBreak();
			SlaveService.StartService();
		}

	// When we get here, the service has been stopped
	return SlaveService.m_Status.dwWin32ExitCode;

	//return 0;
}
