#include "stdafx.h"

#include "..\Source\Slave\Slave\SlaveRegistryDataReader.h"
#include "..\Source\Slave\Slave\ErrorsLogger.h"

#include "lmcons.h"
#include "Wtsapi32.h"




struct CEnumWindowsStruct
{
	HWND TaskBarWnd;
};

struct CEnumDesktopsStruct
{
	HDESK Desktop;
	HWINSTA Station;
	CErrorsLogger* pLogger;
};



BOOL CALLBACK EnumWindowsForLogProc(HWND hwnd, LPARAM lParam)
{
	CErrorsLogger* pLogger = (CErrorsLogger*)lParam;

	char cBuffer[UNLEN + 1];
	GetWindowText(hwnd, &(cBuffer[0]), UNLEN);

		if (pLogger)
			pLogger->AddLogEntry( ((std::string)"\t\tWindow name: " + cBuffer).c_str(), bWriteDuplicates );

	return true;
}
// End of EnumWindowsForLogProc


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	CEnumWindowsStruct* pEnumStruct = (CEnumWindowsStruct*)lParam;

	char cBuffer[1024];
	RealGetWindowClass(hwnd, &(cBuffer[0]), 1023);
		if ( !strcmp(&(cBuffer[0]), "Shell_TrayWnd") )
		{
			GetWindowText(hwnd, &(cBuffer[0]), 1023);
				if ( !strcmp(&(cBuffer[0]), "") )
				{
					pEnumStruct->TaskBarWnd = hwnd;
					return false;
				}
		}

	return true;
}
// End of EnumWindowsProc


std::string GetUserNameOfDesktop(HDESK a_hDesktop)
{
		if (!a_hDesktop)
			return "";

	/*SECURITY_INFORMATION si = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION;
	SECURITY_DESCRIPTOR* psd = 0;
	DWORD dwNeeded = 0;
	GetUserObjectSecurity(a_hDesktop, &si, 0, 0, &dwNeeded);
	psd = (SECURITY_DESCRIPTOR*)new char[dwNeeded];
		if (!GetUserObjectSecurity(a_hDesktop, &si, psd, dwNeeded, &dwNeeded))
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);
		}

	PSID psidOwner;
	BOOL bOwnerDefaulted = FALSE;
		if ( !GetSecurityDescriptorGroup(psd,
					(PSID*)&psidOwner, (LPBOOL)&bOwnerDefaulted) )
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);
		}


		if ( !IsValidSid(psidOwner) )
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);
		}

	DWORD dwUserNameLen = UNLEN;
	char cUserName_[UNLEN + 5], cDomainName_[UNLEN + 5];
	SID_NAME_USE Use_;

		if ( !LookupAccountSid(0, psidOwner, &(cUserName_[0]), &dwUserNameLen, &(cDomainName_[0]), &dwUserNameLen, &Use_) )
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);
		}

	delete psd;


	{
		PSID pSid = 0;
		DWORD dwNeeded = 0;
		GetUserObjectInformation(a_hDesktop, UOI_USER_SID, 0, 0, &dwNeeded);
		pSid = (PSID)new char[dwNeeded];
			if (!GetUserObjectInformation(a_hDesktop, UOI_USER_SID, pSid, dwNeeded, &dwNeeded))
			{
				std::string Buffer;
				Buffer.resize(0xff);
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
							NULL, Buffer.begin(), 0xfe, NULL);
			}

		DWORD dwUserNameLen = UNLEN;
		char cUserName[UNLEN + 5], cDomainName[UNLEN + 5];
		SID_NAME_USE Use;

			if ( !LookupAccountSid(0, pSid, &(cUserName[0]), &dwUserNameLen, &(cDomainName[0]), &dwUserNameLen, &Use) )
			{
				std::string Buffer;
				Buffer.resize(0xff);
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
							NULL, Buffer.begin(), 0xfe, NULL);
			}
	}


	return cUserName_;*/






	CEnumWindowsStruct EnumStruct;
	EnumStruct.TaskBarWnd = 0;

	EnumDesktopWindows(a_hDesktop, EnumWindowsProc, (long)&EnumStruct);

		if (!EnumStruct.TaskBarWnd)
			return "";

	DWORD dwProcessID = 0;
	GetWindowThreadProcessId(EnumStruct.TaskBarWnd, &dwProcessID);
		if (!dwProcessID)
			return "";

	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
		if (!hProcess)
			return "";

	HANDLE hToken = 0;
	OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);
		if ( !hToken )
			return "";

	TOKEN_USER* ptUser = 0;
	DWORD dwReturnedLength = 0;
	GetTokenInformation(hToken, TokenUser, ptUser, 0, &dwReturnedLength);

	ptUser = (TOKEN_USER*)new char[dwReturnedLength];
		if (!GetTokenInformation(hToken, TokenUser, ptUser, dwReturnedLength, &dwReturnedLength))
			return "";

	DWORD dwUNLen = UNLEN;
	char cUserName[UNLEN + 5], cDomainName[UNLEN + 5];
	SID_NAME_USE Use;
		if ( !LookupAccountSid(0, (ptUser->User.Sid), &(cUserName[0]), &dwUNLen, &(cDomainName[0]), &dwUNLen, &Use) )
			return "";

		if (hProcess)
		{
			CloseHandle(hProcess);
			hProcess = 0;
		}
		if (hToken)
		{
			CloseHandle(hToken);
			hToken = 0;
		}
		if (ptUser)
		{
			delete ptUser;
			ptUser = 0;
		}

	return cUserName;
}
// End of GetUserNameOfDesktop()


BOOL CALLBACK EnumDesktopsProc(LPTSTR lpszDesktop, LPARAM lParam)
{
	CEnumDesktopsStruct* pEnumStruct = (CEnumDesktopsStruct*)lParam;

	HDESK hDesktop = OpenDesktop(
				lpszDesktop,
				0,
				0,
				/*DESKTOP_CREATEMENU |
				DESKTOP_CREATEWINDOW |
				DESKTOP_ENUMERATE    |
				DESKTOP_HOOKCONTROL  |
				DESKTOP_JOURNALPLAYBACK |
				DESKTOP_JOURNALRECORD |
				DESKTOP_READOBJECTS |
				DESKTOP_SWITCHDESKTOP |
				DESKTOP_WRITEOBJECTS |
				READ_CONTROL*/
				DESKTOP_ENUMERATE    |
				DESKTOP_READOBJECTS |
				DESKTOP_SWITCHDESKTOP |
				READ_CONTROL);

		if (!hDesktop)
			return true;

	char cUserName[UNLEN + 5];
	strcpy(&(cUserName[0]), GetUserNameOfDesktop(hDesktop).c_str());

	pEnumStruct->pLogger->AddLogEntry( ((std::string)"\tDesktop: " + lpszDesktop + ", user: " + cUserName).c_str(), bWriteDuplicates);

	//HDESK hSavedDesktop = GetThreadDesktop(GetCurrentThreadId());
	//SetThreadDesktop(hDesktop);

	EnumDesktopWindows(hDesktop, EnumWindowsForLogProc, (long)pEnumStruct->pLogger);

	//SetThreadDesktop(hSavedDesktop);

		if (hDesktop)
		{
			CloseDesktop(hDesktop);
			hDesktop = 0;
		}

	return true;
}
// End of EnumDesktopsProc


BOOL CALLBACK EnumWindowStationsProc(LPTSTR lpszWindowStation, LPARAM lParam)
{
	CEnumDesktopsStruct* pEnumStruct = (CEnumDesktopsStruct*)lParam;

	HWINSTA hStation = OpenWindowStation(
				lpszWindowStation,
				0,
				/*WINSTA_ACCESSCLIPBOARD   |
				WINSTA_ACCESSGLOBALATOMS |
				WINSTA_CREATEDESKTOP     |
				WINSTA_ENUMDESKTOPS      |
				WINSTA_ENUMERATE         |
				WINSTA_EXITWINDOWS       |
				WINSTA_READATTRIBUTES    |
				WINSTA_READSCREEN        |
				WINSTA_WRITEATTRIBUTES*/
				WINSTA_ENUMDESKTOPS      |
				WINSTA_ENUMERATE         |
				WINSTA_READATTRIBUTES    |
				WINSTA_READSCREEN        |
				WINSTA_WRITEATTRIBUTES   |
				WINSTA_ACCESSGLOBALATOMS);

		if (!hStation)
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);

			pEnumStruct->pLogger->AddLogEntry(((std::string)"Can't load window station " + lpszWindowStation + ", system message: " + Buffer).c_str(), bWriteDuplicates);
			return true;
		}

	HWINSTA hSavedStation = GetProcessWindowStation();
	SetProcessWindowStation(hStation);

	pEnumStruct->pLogger->AddLogEntry( ((std::string)"Station: " + lpszWindowStation).c_str(), bWriteDuplicates);

	EnumDesktops(hStation, EnumDesktopsProc, lParam);

	CloseWindowStation(hStation);

	SetProcessWindowStation(hSavedStation);
	return true;
}
// End of EnumWindowStationsProc


void DoWriteSessionAttributes(WTS_CONNECTSTATE_CLASS a_State, CErrorsLogger* a_pLogger)
{
		if (a_State == WTSActive)
			a_pLogger->AddLogEntry("\t\tSession's state: Active", bWriteDuplicates);
		if (a_State == WTSConnected)
			a_pLogger->AddLogEntry("\t\tSession's state: Connected", bWriteDuplicates);
		if (a_State == WTSConnectQuery)
			a_pLogger->AddLogEntry("\t\tSession's state: ConnectQuery", bWriteDuplicates);
		if (a_State == WTSShadow)
			a_pLogger->AddLogEntry("\t\tSession's state: Shadow", bWriteDuplicates);
		if (a_State == WTSDisconnected)
			a_pLogger->AddLogEntry("\t\tSession's state: Disconnected", bWriteDuplicates);
		if (a_State == WTSIdle)
			a_pLogger->AddLogEntry("\t\tSession's state: Idle", bWriteDuplicates);
		if (a_State == WTSListen)
			a_pLogger->AddLogEntry("\t\tSession's state: Listen", bWriteDuplicates);
		if (a_State == WTSReset)
			a_pLogger->AddLogEntry("\t\tSession's state: Reset", bWriteDuplicates);
		if (a_State == WTSDown)
			a_pLogger->AddLogEntry("\t\tSession's state: Down", bWriteDuplicates);
		if (a_State == WTSInit)
			a_pLogger->AddLogEntry("\t\tSession's state: Init", bWriteDuplicates);
}
// End of DoWriteSessionAttributes


void DoWriteSessionsInfo(CErrorsLogger* a_pLogger)
{
	PWTS_SESSION_INFO pInfo;
	DWORD dwSessionsNumber = 0;
		if (!WTSEnumerateSessions(
					WTS_CURRENT_SERVER_HANDLE,
					0,
					1,
					&pInfo,
					&dwSessionsNumber))
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);
			a_pLogger->AddLogEntry((std::string("WTSEnumerateSessions failed with message: ") + Buffer).c_str(), bWriteDuplicates);
		}

	char cBuffer[20];
	_itoa(dwSessionsNumber, &(cBuffer[0]), 10);
	a_pLogger->AddLogEntry( ((std::string)"Sessions number: " + cBuffer).c_str(), bWriteDuplicates );

	DWORD dwReturned = 0;
	LPTSTR pName = 0;
	LPTSTR pWinStationName = 0;
	int i = 0;
		for (i = 0; i < dwSessionsNumber; ++i)
		{
				if(!WTSQuerySessionInformation(
							WTS_CURRENT_SERVER_HANDLE,
							pInfo[i].SessionId,
							WTSUserName,
							&pName,
							&dwReturned))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					a_pLogger->AddLogEntry((std::string("WTSQuerySessionInformation failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

				if(!WTSQuerySessionInformation(
							WTS_CURRENT_SERVER_HANDLE,
							pInfo[i].SessionId,
							WTSWinStationName,
							&pWinStationName,
							&dwReturned))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					a_pLogger->AddLogEntry((std::string("WTSQuerySessionInformation failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

			a_pLogger->AddLogEntry(((std::string)"Session user name: " + pName + ", window station name: " + pWinStationName).c_str(), bWriteDuplicates);
			DoWriteSessionAttributes(pInfo[i].State, a_pLogger);

				if (pName)
				{
					WTSFreeMemory(pName);
					pName = 0;
				}
				if (pWinStationName)
				{
					WTSFreeMemory(pWinStationName);
					pWinStationName = 0;
				}
		}

	PWTS_PROCESS_INFO pProcessInfo;
	DWORD dwProcessesCount;
	WTSEnumerateProcesses(
				WTS_CURRENT_SERVER_HANDLE,
				0,
				1,
				&pProcessInfo,
				&dwProcessesCount);
		for(i = 0; i < dwProcessesCount; ++i)
		{
				if(!WTSQuerySessionInformation(
							WTS_CURRENT_SERVER_HANDLE,
							pProcessInfo[i].SessionId,
							WTSUserName,
							&pName,
							&dwReturned))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					a_pLogger->AddLogEntry((std::string("WTSQuerySessionInformation failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

			a_pLogger->AddLogEntry(((std::string)"\t\tProcess Name: " + pProcessInfo[i].pProcessName + ", process's user name: " + pName).c_str(), bWriteDuplicates);

			HANDLE hProcess = 0;
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pProcessInfo[i].ProcessId);
				if (!hProcess)
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					a_pLogger->AddLogEntry((std::string("OpenProcess failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

			HANDLE hProcessToken = 0;
			OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE, &hProcessToken);

				if (!hProcessToken)
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					a_pLogger->AddLogEntry((std::string("OpenProcessToken failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

				if (hProcess)
				{
					CloseHandle(hProcess);
					hProcess = 0;
				}

			HANDLE hPrimaryToken = 0;
			DuplicateTokenEx(
						hProcessToken,
						TOKEN_IMPERSONATE | TOKEN_READ | TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE,
						0,
						SecurityImpersonation,
						TokenPrimary,
						&hPrimaryToken);

			if (!hPrimaryToken)
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					a_pLogger->AddLogEntry((std::string("DuplicateTokenEx failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

				if (hProcessToken)
				{
					CloseHandle(hProcessToken);
					hProcessToken = 0;
				}

				if (hPrimaryToken)
					a_pLogger->AddLogEntry("\t\t\tProcess primary token successfully queried", bWriteDuplicates);

			WTSFreeMemory(pName);
		}

	WTSFreeMemory(pInfo);
	WTSFreeMemory(pProcessInfo);
}
// End of DoWriteSessionsInfo















int APIENTRY WinMain(HINSTANCE hInstance,
			HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
		try
		{
			CSlaveRegistryDataReader Reader;

			Reader.SetKey(HKEY_LOCAL_MACHINE);
			Reader.SetSecurityAccessMask(KEY_READ);
			*(Reader.GetSubKeyName()) = "SYSTEM\\CurrentControlSet\\Services\\Slave Service\\Parameters";
			CErrorsLogger* pLogger = new CErrorsLogger(&Reader);

				if (pLogger)
					*pLogger->GetLogFileName() = "e:\\TestLog.txt";

			CEnumDesktopsStruct Struct;
			Struct.Desktop = 0;
			Struct.pLogger = pLogger;

			//EnumWindowStations(EnumWindowStationsProc, (LPARAM)&Struct);

			HDESK hDesktop = GetThreadDesktop(GetCurrentThreadId());
			HWINSTA hStation = GetProcessWindowStation();
			char cBuffer[UNLEN + 1];
			DWORD dwLength = 0;
			GetUserObjectInformation(hDesktop, UOI_NAME, &(cBuffer[0]), UNLEN, &dwLength);
				if (pLogger)
					pLogger->AddLogEntry( ((std::string)"Current desktop name: " + &(cBuffer[0])).c_str(), bWriteDuplicates );
			GetUserObjectInformation(hStation, UOI_NAME, &(cBuffer[0]), UNLEN, &dwLength);
				if (pLogger)
					pLogger->AddLogEntry( ((std::string)"Current station name: " + &(cBuffer[0])).c_str(), bWriteDuplicates );

			DoWriteSessionsInfo(pLogger);




				if (pLogger)
				{
					delete pLogger;
					pLogger = 0;
				}
		}
		catch(...)
		{

		}

	return 0;
}
