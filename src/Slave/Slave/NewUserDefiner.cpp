#include "stdafx.h"


#include "NewUserDefiner.h"
#include "Messages.h"
#include "SlaveRegistryDataReader.h"
#include "Exceptions.h"
#include "ErrorsLogger.h"
#include "WriteTextMessage.h"

#include "Lmcons.h"
#include "Wtsapi32.h"



DWORD dwMaxRepetitionsNumber = 20;

/*struct CEnumWindowsStruct
{
	HWND TaskBarWnd;
};

struct CEnumDesktopsStruct
{
	HDESK Desktop;
	HWINSTA Station;
	char cUserName[UNLEN + 1];
};


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

//	/*SECURITY_INFORMATION si = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION;
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


//	return cUserName_; // Тут заканчивался комментарий






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
				true,
				DESKTOP_CREATEMENU |
				DESKTOP_CREATEWINDOW |
				DESKTOP_ENUMERATE    |
				DESKTOP_HOOKCONTROL  |
				DESKTOP_JOURNALPLAYBACK |
				DESKTOP_JOURNALRECORD |
				DESKTOP_READOBJECTS |
				DESKTOP_SWITCHDESKTOP |
				DESKTOP_WRITEOBJECTS);

		if (!hDesktop)
			return true;

	char cBuffer[1024];

	char cUserName[UNLEN + 5];
	strcpy(&(cUserName[0]), GetUserNameOfDesktop(hDesktop).c_str());

		if ( !strcmp(&(cUserName[0]), &(pEnumStruct->cUserName[0])) )
		{
				//if ( !_stricmp(lpszDesktop, "default") )
				{
					pEnumStruct->Desktop = hDesktop;
					return false;
				}
		}

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
				true,
				WINSTA_ACCESSCLIPBOARD   |
				WINSTA_ACCESSGLOBALATOMS |
				WINSTA_CREATEDESKTOP     |
				WINSTA_ENUMDESKTOPS      |
				WINSTA_ENUMERATE         |
				WINSTA_EXITWINDOWS       |
				WINSTA_READATTRIBUTES    |
				WINSTA_READSCREEN        |
				WINSTA_WRITEATTRIBUTES);

		if (!hStation)
			return true;

	HWINSTA hSavedStation = GetProcessWindowStation();
	SetProcessWindowStation(hStation);

	EnumDesktops(hStation, EnumDesktopsProc, lParam);

		if (pEnumStruct->Desktop)
		{
				//if ( !_stricmp(lpszWindowStation, "winsta0") )
				{
					pEnumStruct->Station = hStation;
					SetProcessWindowStation(hSavedStation);
					return false;
				}
		}

	CloseWindowStation(hStation);

	SetProcessWindowStation(hSavedStation);
	return true;
}*/
// End of EnumWindowStationsProc





CNewUserDefiner::CNewUserDefiner()
{
	m_sLastUserName = "";
}
// End of CNewUserDefiner()


CNewUserDefiner::~CNewUserDefiner()
{

}
// End of ~CNewUserDefiner()


void CNewUserDefiner::OnTimer()
{
	std::string sUserName = GetCurrentUserName();

		if ( strcmp(m_sLastUserName.c_str(), sUserName.c_str()) )
		{
			m_sLastUserName = sUserName;

			PostThreadMessage(GetCurrentThreadId(), WM_NEW_USER_LOGGED, 0, 0);
		}
}
// End of OnTimer()


std::string CNewUserDefiner::GetCurrentUserName()
{
	DWORD dwCurrentSessionId = 0;
		try
		{
			dwCurrentSessionId = GetCurrentUserSessionId();
		}
		catch(CAnyLogableException)
		{
			return "";
		}

	return GetUserNameBySessionId(dwCurrentSessionId);

		/*try
		{
			std::string sName;
			CSlaveRegistryDataReader Reader;
			Reader.ReadUserName(&sName);

			return sName;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CNewUserDefiner::GetInteractivelyLoggedUserName()", bDoNotWriteDuplicates);
		}*/


	/*HDESK hDesktop = OpenInputDesktop(0, 0, DESKTOP_ENUMERATE);

	CEnumWindowsStruct EnumStruct;
	EnumStruct.TaskBarWnd = 0;

	EnumDesktopWindows(hDesktop, EnumWindowsProc, (long)&EnumStruct);

		if (hDesktop)
		{
			CloseDesktop(hDesktop);
			hDesktop = 0;
		}

		if (!EnumStruct.TaskBarWnd)
			return "";

	//HWND hTaskbarWindow = FindWindow("Shell_traywnd", "");
		//if (!hTaskbarWindow)
			//return ""

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

	return cUserName;*/
}
// End of GetCurrentUserName()


std::string CNewUserDefiner::GetUserNameByProcessId(DWORD a_dwProcessId)
{
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, a_dwProcessId);
		if (!hProcess)
			return "";

	HANDLE hToken = 0;
	OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);
		if ( !hToken )
		{
				if (hProcess)
				{
					CloseHandle(hProcess);
					hProcess = 0;
				}
			return "";
		}
		if (hProcess)
		{
			CloseHandle(hProcess);
			hProcess = 0;
		}

	TOKEN_USER* ptUser = 0;
	DWORD dwReturnedLength = 0;
	GetTokenInformation(hToken, TokenUser, ptUser, 0, &dwReturnedLength);

	ptUser = (TOKEN_USER*)new char[dwReturnedLength];
		if (!GetTokenInformation(hToken, TokenUser, ptUser, dwReturnedLength, &dwReturnedLength))
		{
				if (hToken)
				{
					CloseHandle(hToken);
					hToken = 0;
				}
			return "";
		}
		if (hToken)
		{
			CloseHandle(hToken);
			hToken = 0;
		}

	DWORD dwUNLen = UNLEN;
	char cUserName[UNLEN + 5], cDomainName[UNLEN + 5];
	SID_NAME_USE Use;
		if ( !LookupAccountSid(0, (ptUser->User.Sid), &(cUserName[0]), &dwUNLen, &(cDomainName[0]), &dwUNLen, &Use) )
		{
				if (ptUser)
				{
					delete ptUser;
					ptUser = 0;
				}
			return "";
		}

		if (ptUser)
		{
			delete ptUser;
			ptUser = 0;
		}

	return cUserName;
}
// End of GetUserNameByProcessId


DWORD CNewUserDefiner::GetCurrentUserSessionId()
{
	PWTS_SESSION_INFO pInfo;
	DWORD dwSessionsNumber = 0;
		if (!WTSEnumerateSessions(
					WTS_CURRENT_SERVER_HANDLE,
					0,
					1,
					&pInfo,
					&dwSessionsNumber))
			throw CAnyLogableException("There's no one session found", bDoNotWriteDuplicates);

	DWORD dwResult = 0;
	bool bFlag = false;
	int i = 0;
		for (i = 0; i < dwSessionsNumber; ++i)
		{
				if( (pInfo[i].State == WTSActive) && (strcmp(GetUserNameBySessionId(pInfo[i].SessionId).c_str(), "")) )
				{
					dwResult = pInfo[i].SessionId;
					bFlag = true;
					break;
				}
		}

		if (pInfo)
		{
			WTSFreeMemory(pInfo);
			pInfo = 0;
		}

		if (!bFlag)
			throw CAnyLogableException("There's no one active session found", bDoNotWriteDuplicates);

	return dwResult;
}
// End of GetCurrentUserSessionId()


HANDLE CNewUserDefiner::GetCurrentUserToken()
{
	DWORD dwCurrentUserSessionId = 0;
		try
		{
			dwCurrentUserSessionId = GetCurrentUserSessionId();
		}
		catch(CAnyLogableException)
		{
			return 0;
		}

	return GetUserTokenBySessionId(dwCurrentUserSessionId);
}
// End of GetCurrentUserToken()


HANDLE CNewUserDefiner::GetCurrentUserImpersonatingToken()
{
	DWORD dwCurrentUserSessionId = 0;
		try
		{
			dwCurrentUserSessionId = GetCurrentUserSessionId();
		}
		catch(CAnyLogableException)
		{
			return 0;
		}

	return GetUserImpersonatingTokenBySessionId(dwCurrentUserSessionId);
}
// End of GetCurrentUserImpersonatingToken()


HANDLE CNewUserDefiner::GetCurrentUserPrimaryToken()
{
		DWORD dwCurrentUserSessionId = 0;
		try
		{
			dwCurrentUserSessionId = GetCurrentUserSessionId();
		}
		catch(CAnyLogableException)
		{
			return 0;
		}

	return GetUserPrimaryTokenBySessionId(dwCurrentUserSessionId);
}
// End of GetCurrentUserPrimaryToken()


//void CNewUserDefiner::GetUserDesktopAndStation(HDESK* a_pDesktop, HWINSTA* a_pStation)
//{
	/*HWINSTA hSavedStation = GetProcessWindowStation();

	// Obtain a handle to WinSta0 - service must be running
	// in the LocalSystem account
	// 
	*a_pStation = OpenWindowStation("winsta0", true,
				WINSTA_ACCESSCLIPBOARD   |
				WINSTA_ACCESSGLOBALATOMS |
				WINSTA_CREATEDESKTOP     |
				WINSTA_ENUMDESKTOPS      |
				WINSTA_ENUMERATE         |
				WINSTA_EXITWINDOWS       |
				WINSTA_READATTRIBUTES    |
				WINSTA_READSCREEN        |
				WINSTA_WRITEATTRIBUTES   |
				MAXIMUM_ALLOWED);

		if (*a_pStation == NULL)
			return;

		if (!SetProcessWindowStation(*a_pStation))
			 return;

	*a_pDesktop = OpenDesktop("default", 0, true,
				DESKTOP_CREATEMENU |
				DESKTOP_CREATEWINDOW |
				DESKTOP_ENUMERATE    |
				DESKTOP_HOOKCONTROL  |
				DESKTOP_JOURNALPLAYBACK |
				DESKTOP_JOURNALRECORD |
				DESKTOP_READOBJECTS |
				DESKTOP_SWITCHDESKTOP |
				DESKTOP_WRITEOBJECTS |
				MAXIMUM_ALLOWED);
		if ((*a_pDesktop) == NULL)
		{
			SetProcessWindowStation(hSavedStation);
			return;
		}

	SetProcessWindowStation(hSavedStation);

	return;*/


		
		/*try
		{
			*a_pDesktop = 0;
			*a_pStation = 0;

			CEnumDesktopsStruct Struct;
				do
				{
					strcpy(&(Struct.cUserName[0]), GetInteractivelyLoggedUserName().c_str());
					Struct.Desktop = 0;

					EnumWindowStations(EnumWindowStationsProc, (LPARAM)&Struct);

					Sleep(1000);
				}
				while ( !(Struct.Desktop && Struct.Station) );

			*a_pDesktop = Struct.Desktop;
			*a_pStation = Struct.Station;






		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CNewUserDefiner::GetUserDesktop()", bDoNotWriteDuplicates);
		}
}*/
// End of GetUserDesktop()


void CNewUserDefiner::DoFillSessionsIdsCollection(CWTSSessionsIdsCollection* a_pCollection)
{
		try
		{
				if (!a_pCollection)
					return;

			PWTS_SESSION_INFO pInfo;
			DWORD dwSessionsNumber = 0;
			WTSEnumerateSessions(
						WTS_CURRENT_SERVER_HANDLE,
						0,
						1,
						&pInfo,
						&dwSessionsNumber);

			a_pCollection->resize(dwSessionsNumber);

			DWORD dwReallyAddedSessions = 0;
			int i = 0;
				for (i = 0; i < dwSessionsNumber; ++i)
				{
						try
						{
								if ( (strcmp(GetUserNameBySessionId(pInfo[i].SessionId).c_str(), "")) )
								{
									(*a_pCollection)[dwReallyAddedSessions] = pInfo[i].SessionId;
									++dwReallyAddedSessions;
								}
						}
						catch(CAnyLogableException& Error)
						{
							//WriteTextMessage(Error.what(), 0);
						}
						catch(...)
						{
						}
				}
			a_pCollection->resize(dwReallyAddedSessions);
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(((std::string)"An error occured in CNewUserDefiner::DoFillSessionsIdsCollection: " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CNewUserDefiner::DoFillSessionsIdsCollection", bDoNotWriteDuplicates);
		}
}
// End of DoFillSessionsIdsCollection


HANDLE CNewUserDefiner::GetUserTokenBySessionId(DWORD a_dwSessionId)
{
	PWTS_PROCESS_INFO pProcessInfo;
	DWORD dwProcessesCount;
			if (!WTSEnumerateProcesses(
						WTS_CURRENT_SERVER_HANDLE,
						0,
						1,
						&pProcessInfo,
						&dwProcessesCount))
			{
				std::string Buffer;
				Buffer.resize(0xff);
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
							NULL, Buffer.begin(), 0xfe, NULL);

				throw CAnyLogableException((std::string("Can't enumerate processes. System message: ") + Buffer).c_str(), bWriteDuplicates);
			}

		try
		{
			std::string sSessionUserName = GetUserNameBySessionId(a_dwSessionId);
			std::string sProcessUserName = "";
			int i = 0;
				for(i = 0; i < dwProcessesCount; ++i)
				{
						if ( pProcessInfo[i].SessionId == a_dwSessionId )
						{
							sProcessUserName = GetUserNameByProcessId(pProcessInfo[i].ProcessId);
								//if (!_stricmp(pProcessInfo[i].pProcessName, "explorer.exe"))
								if (!_stricmp(sProcessUserName.c_str(), sSessionUserName.c_str()))
								{
									HANDLE hProcess = 0;
									hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pProcessInfo[i].ProcessId);
										if (!hProcess)
										{
											std::string Buffer;
											Buffer.resize(0xff);
											FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
														NULL, Buffer.begin(), 0xfe, NULL);

											throw CAnyLogableException((std::string("OpenProcess failed with message: ") + Buffer).c_str(), bWriteDuplicates);
										}

									HANDLE hProcessToken = 0;
									OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_IMPERSONATE, &hProcessToken);

										if (!hProcessToken)
										{
											std::string Buffer;
											Buffer.resize(0xff);
											FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
														NULL, Buffer.begin(), 0xfe, NULL);

												if (hProcess)
												{
													CloseHandle(hProcess);
													hProcess = 0;
												}

											throw CAnyLogableException((std::string("OpenProcessToken failed with message: ") + Buffer).c_str(), bWriteDuplicates);
										}
										if (hProcess)
										{
											CloseHandle(hProcess);
											hProcess = 0;
										}

										if (pProcessInfo)
										{
											WTSFreeMemory(pProcessInfo);
											pProcessInfo = 0;
										}

									return hProcessToken;
								}
						}
				}
		}
		catch(CAnyLogableException& Error)
		{
				if (pProcessInfo)
				{
					WTSFreeMemory(pProcessInfo);
					pProcessInfo = 0;
				}
			throw CAnyLogableException(((std::string)"An error occured in CNewUserDefiner::GetUserTokenBySessionId: " + Error.what()), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
				if (pProcessInfo)
				{
					WTSFreeMemory(pProcessInfo);
					pProcessInfo = 0;
				}
			throw CAnyLogableException("An unknown error occured in CNewUserDefiner::GetUserTokenBySessionId", bDoNotWriteDuplicates);
		}

	return 0;
}
// End of GetUserTokenBySessionId


HANDLE CNewUserDefiner::GetUserPrimaryTokenBySessionId(DWORD a_dwSessionId)
{
	DWORD dwRepetitionsNumber = 0;

	HANDLE hResultToken = 0;

		do
		{
				try
				{
					HANDLE hToken = GetUserTokenBySessionId(a_dwSessionId);

					hResultToken = 0;
					DuplicateTokenEx(
								hToken,
								TOKEN_IMPERSONATE | TOKEN_READ | TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE,
								0,
								SecurityImpersonation,
								TokenPrimary,
								&hResultToken);

						if (!hResultToken)
						{
							std::string Buffer;
							Buffer.resize(0xff);
							FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
										NULL, Buffer.begin(), 0xfe, NULL);

								if (hToken)
								{
									CloseHandle(hToken);
									hToken = 0;
								}

							throw CAnyLogableException((std::string("DuplicateTokenEx failed with message: ") + Buffer).c_str(), bWriteDuplicates);
						}

						if (hToken)
						{
							CloseHandle(hToken);
							hToken = 0;
						}

					return hResultToken;
				}
				catch(...)
				{
					Sleep(500);
					++dwRepetitionsNumber;
						if (dwRepetitionsNumber >= dwMaxRepetitionsNumber)
							throw;
				}
		}
		while (true);

	return hResultToken;
}
// End of GetUserPrimaryTokenBySessionId


HANDLE CNewUserDefiner::GetUserImpersonatingTokenBySessionId(DWORD a_dwSessionId)
{
	DWORD dwRepetitionsNumber = 0;

	HANDLE hResultToken = 0;

		do
		{
				try
				{
					HANDLE hToken = GetUserTokenBySessionId(a_dwSessionId);

					hResultToken = 0;
					DuplicateTokenEx(
								hToken,
								TOKEN_IMPERSONATE | TOKEN_READ | TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE,
								0,
								SecurityImpersonation,
								TokenImpersonation,
								&hResultToken);

						if (!hResultToken)
						{
							std::string Buffer;
							Buffer.resize(0xff);
							FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
										NULL, Buffer.begin(), 0xfe, NULL);

								if (hToken)
								{
									CloseHandle(hToken);
									hToken = 0;
								}

							throw CAnyLogableException((std::string("DuplicateTokenEx failed with message: ") + Buffer).c_str(), bWriteDuplicates);
						}

						if (hToken)
						{
							CloseHandle(hToken);
							hToken = 0;
						}

					return hResultToken;
				}
				catch(...)
				{
					++dwRepetitionsNumber;
					Sleep(500);
						if (dwRepetitionsNumber >= dwMaxRepetitionsNumber)
							throw;
				}
		}
		while (true);

	return hResultToken;
}
// End of GetUserImpersonatingTokenBySessionId


std::string CNewUserDefiner::GetUserNameBySessionId(DWORD a_dwSessionId)
{
	DWORD dwReturned = 0;
	LPTSTR pName = 0;
		try
		{
				if(!WTSQuerySessionInformation(
							WTS_CURRENT_SERVER_HANDLE,
							a_dwSessionId,
							WTSUserName,
							&pName,
							&dwReturned))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);
					throw CAnyLogableException((std::string("Can't query session information. System message: ") + Buffer).c_str(), bWriteDuplicates);
				}
		}
		catch(CAnyLogableException& Error)
		{
				if (pName)
				{
					WTSFreeMemory(pName);
					pName = 0;
				}
			throw CAnyLogableException(((std::string)"An error occured in CNewUserDefiner::GetCurrentUserName(): " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
				if (pName)
				{
					WTSFreeMemory(pName);
					pName = 0;
				}
			throw CAnyLogableException("An unknown error occured in CNewUserDefiner::GetCurrentUserName()", bDoNotWriteDuplicates);
		}

	std::string sName = pName;

		if (pName)
		{
			WTSFreeMemory(pName);
			pName = 0;
		}

	return sName;
}
// End of GetUserNameBySessionId


HANDLE CNewUserDefiner::GetExplorerSessionToken(DWORD a_dwSessionId)
{
	PWTS_PROCESS_INFO pProcessInfo;
	DWORD dwProcessesCount;
			if (!WTSEnumerateProcesses(
						WTS_CURRENT_SERVER_HANDLE,
						0,
						1,
						&pProcessInfo,
						&dwProcessesCount))
			{
				std::string Buffer;
				Buffer.resize(0xff);
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
							NULL, Buffer.begin(), 0xfe, NULL);

				throw CAnyLogableException((std::string("Can't enumerate processes. System message: ") + Buffer).c_str(), bWriteDuplicates);
			}

		try
		{
			std::string sSessionUserName = GetUserNameBySessionId(a_dwSessionId);
			std::string sProcessUserName = "";
			int i = 0;
				for(i = 0; i < dwProcessesCount; ++i)
				{
						if ( pProcessInfo[i].SessionId == a_dwSessionId )
						{
							sProcessUserName = GetUserNameByProcessId(pProcessInfo[i].ProcessId);
								if (!_stricmp(pProcessInfo[i].pProcessName, "explorer.exe"))
								//if (!_stricmp(sProcessUserName.c_str(), sSessionUserName.c_str()))
								{
									HANDLE hProcess = 0;
									hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pProcessInfo[i].ProcessId);
										if (!hProcess)
										{
											std::string Buffer;
											Buffer.resize(0xff);
											FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
														NULL, Buffer.begin(), 0xfe, NULL);

											throw CAnyLogableException((std::string("OpenProcess failed with message: ") + Buffer).c_str(), bWriteDuplicates);
										}

									HANDLE hProcessToken = 0;
									OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_IMPERSONATE, &hProcessToken);

										if (!hProcessToken)
										{
											std::string Buffer;
											Buffer.resize(0xff);
											FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
														NULL, Buffer.begin(), 0xfe, NULL);

												if (hProcess)
												{
													CloseHandle(hProcess);
													hProcess = 0;
												}

											throw CAnyLogableException((std::string("OpenProcessToken failed with message: ") + Buffer).c_str(), bWriteDuplicates);
										}
										if (hProcess)
										{
											CloseHandle(hProcess);
											hProcess = 0;
										}

										if (pProcessInfo)
										{
											WTSFreeMemory(pProcessInfo);
											pProcessInfo = 0;
										}

									return hProcessToken;
								}
						}
				}
		}
		catch(CAnyLogableException& Error)
		{
				if (pProcessInfo)
				{
					WTSFreeMemory(pProcessInfo);
					pProcessInfo = 0;
				}
			throw CAnyLogableException(((std::string)"An error occured in CNewUserDefiner::GetUserTokenBySessionId: " + Error.what()), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
				if (pProcessInfo)
				{
					WTSFreeMemory(pProcessInfo);
					pProcessInfo = 0;
				}
			throw CAnyLogableException("An unknown error occured in CNewUserDefiner::GetUserTokenBySessionId", bDoNotWriteDuplicates);
		}

	return 0;
}
// End of GetExplorerSessionToken
