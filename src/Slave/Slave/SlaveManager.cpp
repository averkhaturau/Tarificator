#include "stdafx.h"

#include "SlaveManager.h"
#include "Exceptions.h"
#include "Messages.h"
#include "SlaveRegistryDataReader.h"
#include "WTSSessionsIdsCollection.h"
#include "WriteTextMessage.h"

#include "Wtsapi32.h"
#include "Mmsystem.h"



CSlaveManager::CSlaveManager(HINSTANCE hInstance, CSlaveDataReader* pSlaveDataReader, CErrorsLogger* pErrorsLogger)
{
	m_hMutex = 0;
	m_pPermissionManager = 0;
	m_pCheckStateManager = 0;
	m_uiSlaveTimerIdentifier = 0;
	m_bMustBeLocked = true;
	m_hInstance = hInstance;
	m_pAssumedFinishManager = 0;
	m_pNewUserDefiner = 0;
	m_pSoundManager = 0;

	m_EarlyWarnManager.SetEnabled(false);
	m_LateWarnManager.SetEnabled(false);

	m_Remaining.Finish = (CTimeContainer)0;
	m_Remaining.Start = (CTimeContainer)0;
	m_Remaining.SlaveCurrent = (CTimeContainer)0;
	m_Remaining.MasterCurrent = (CTimeContainer)0;

	m_bDesktopCreatedSuccessfully = true;

	m_pSuperUsersNamesCollection = 0;

	m_pTimeOutCollection = 0;

	m_bWasLocked = true;

		try
		{
			// Чтобы нельзя было запустить сразу 2 экземпляра проги.
			// Если один экземпляр запущен - в лог ничего не будет писАться,
			// хотя это легко сделать. В повторный запуск - нормальная
			// ситуация при каждой загрузке винды.
			CheckMutex(sSlaveMutexName.c_str());

			// Регистрирует процесс как Service
			//RegisterService();

			m_pPermissionManager = new CTimeOutManager;
			m_pCheckStateManager = new CTimeOutManager;
			m_pAssumedFinishManager = new CInvertedTimeOutManager;
			m_pAssumedFinishManager->SetEnabled(true);

			m_pNewUserDefiner = new CNewUserDefiner();

			m_pSuperUsersNamesCollection = new CNamesCollection;

			m_pSoundManager = new CSlaveSoundManager;

			m_pDesktopInfosCollection = new CApplicationInfosCollection;

			m_pTimeOutCollection = new CSessionTimeOutCollection;

			pSlaveDataReader->ReadSlaveManagerData(this);
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CSlaveManager::CSlaveManager()", bWriteDuplicates);
		}
}
// End of CSlaveManager()


CSlaveManager::~CSlaveManager()
{
	DoDeleteEverything();
}
// End of ~CSlaveManager()


void CSlaveManager::DoDeleteEverything()
{
	CApplicationInfosCollection::iterator Iter = m_pDesktopInfosCollection->GetData()->begin(),
				EndIter = m_pDesktopInfosCollection->GetData()->end();
		for (; Iter != EndIter; ++Iter)
		{
				if ((*Iter)->GetProcessHandle())
				{
					TerminateProcess((*Iter)->GetProcessHandle(), 0);
					CloseHandle((*Iter)->GetProcessHandle());
					(*Iter)->SetProcessHandle(0);
				}
				if ((*Iter)->GetThreadHandle())
				{
					CloseHandle((*Iter)->GetThreadHandle());
					(*Iter)->SetThreadHandle(0);
				}
		}
	m_pDesktopInfosCollection->Clear();
	UpdateExchangeData();

		if (m_pSoundManager)
		{
			delete m_pSoundManager;
			m_pSoundManager = 0;
		}
		if (m_uiSlaveTimerIdentifier)
		{
			KillTimer(NULL, m_uiSlaveTimerIdentifier);
			m_uiSlaveTimerIdentifier = 0;
		}
		if (m_hMutex)
		{
			ReleaseMutex(m_hMutex);
			CloseHandle(m_hMutex);
			m_hMutex = 0;
		}
		if (m_pPermissionManager)
		{
			delete m_pPermissionManager;
			m_pPermissionManager = 0;
		}
		if (m_pCheckStateManager)
		{
			delete m_pCheckStateManager;
			m_pCheckStateManager = 0;
		}
		if (m_pAssumedFinishManager)
		{
			delete m_pAssumedFinishManager;
			m_pAssumedFinishManager = 0;
		}
		if (m_pNewUserDefiner)
		{
			delete m_pNewUserDefiner;
			m_pNewUserDefiner = 0;
		}
		if (m_pDesktopInfosCollection)
		{
			delete m_pDesktopInfosCollection;
			m_pDesktopInfosCollection = 0;
		}
		if (m_pSuperUsersNamesCollection)
		{
			delete m_pSuperUsersNamesCollection;
			m_pSuperUsersNamesCollection = 0;
		}
		if (m_pTimeOutCollection)
		{
			delete m_pTimeOutCollection;
			m_pTimeOutCollection = 0;
		}
}
// End of DoDeleteEverything() 


void CSlaveManager::RegisterService()
{
	HINSTANCE hInst = 0;
	hInst = LoadLibrary("KERNEL32.DLL");
		if (!hInst)
			throw CAnyLogableException("Can't load KERNEL32.DLL", bWriteDuplicates);

	RegisterProcess* RegisterServiceProcess = (RegisterProcess*)GetProcAddress(hInst, "RegisterServiceProcess");
		if (!RegisterServiceProcess)
		{
				if (hInst)
				{
					FreeLibrary(hInst);
					hInst = 0;
				}
			throw CAnyLogableException("Can't take RegisterServiceProcess address", bWriteDuplicates);
		}

	// Собственно регистрация процесса как service
	(*RegisterServiceProcess)(0, 1);

		if (hInst)
		{
			FreeLibrary(hInst);
			hInst = 0;
		}
}
// End of RegisterService() 


void CSlaveManager::CheckMutex(const char* cMutexName)
{
	m_hMutex = CreateMutex(NULL, true, cMutexName);
		if ( (GetLastError() == ERROR_ALREADY_EXISTS) || (m_hMutex == 0))
		{
			// Если один экземпляр уже запущен
			throw CAnyLogableException("One program copy is already running", bWriteDuplicates);
		}
}
// End of CheckMutex();


void CSlaveManager::StartTimer(CTimerProcedure* Procedure)
{
	// Чтобы вызывать по таймеру функцию TimerFunction
	m_uiSlaveTimerIdentifier = SetTimer(NULL, 0, m_uiSlaveTimerPeriod, Procedure);
		if (!m_uiSlaveTimerIdentifier)
			throw CAnyLogableException("Can't create timer", bDoNotWriteDuplicates);
}
// End of StartTimer


void CSlaveManager::OnTimerEvent()
{
		if (m_pNewUserDefiner)
		{
			m_pNewUserDefiner->OnTimer();
		}

		if (m_pPermissionManager->IsTimeExpired())
		{
			m_bMustBeLocked = true;
		}

		if (m_pAssumedFinishManager->IsTimeExpired())
		{
			m_bMustBeLocked = true;
		}

		if (m_bMustBeLocked)
		{
			m_Remaining.cUserNames[0] = '\0';

				if ( !m_bWasLocked )
				{
					m_pSoundManager->PlayFinished();
				}
		}

		if (m_pCheckStateManager->IsTimeExpired())
			PostThreadMessage(GetCurrentThreadId(), WM_NEED_TO_CHECK_STATE, 0, 0);

		if ( (m_EarlyWarnManager.GetTimeOut().GetTime() != 0) && (m_EarlyWarnManager.IsTimeExpired()) )
		{
			m_EarlyWarnManager.SetEnabled(false);
			m_pSoundManager->PlayEarlyWarn();
		}

		if ( (m_LateWarnManager.GetTimeOut().GetTime() != 0) && (m_LateWarnManager.IsTimeExpired()) )
		{
			m_LateWarnManager.SetEnabled(false);
			m_pSoundManager->PlayLateWarn();
		}

	m_pSoundManager->OnTimer();

	UpdateExchangeData();

		if (!m_bDesktopCreatedSuccessfully)
		{
			OnNewUserLogged();
		}

	DoTerminateInproperSessions();

	m_bWasLocked = m_bMustBeLocked;
}
// End of OnTimerEvent()


void CSlaveManager::UpdateExchangeData()
{
		try
		{
			CSlaveRegistryDataReader Reader;
			Reader.WriteExchangeDesktopData(this);
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(((std::string)"An error occured in CSlaveManager::UpdateExchangeData(): " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CSlaveManager::UpdateExchangeData()", bDoNotWriteDuplicates);
		}
}
// End of UpdateExchangeData()


void CSlaveManager::OnNewUserLogged()
{
	m_bDesktopCreatedSuccessfully = false;

		try
		{
			DWORD dwSessionId = 0;
				try
				{
					dwSessionId = m_pNewUserDefiner->GetCurrentUserSessionId();
				}
				catch(...)
				{
				}

				if ( DoTerminateInproperSessions(dwSessionId) )
				{
					m_bDesktopCreatedSuccessfully = true;
					return;
				}

			CWTSSessionsIdsCollection IdsCollection;
			m_pNewUserDefiner->DoFillSessionsIdsCollection(&IdsCollection);

			bool bDeleted = false;
				do
				{
					bDeleted = false;
					CApplicationInfosCollection::iterator Iter = m_pDesktopInfosCollection->GetData()->begin(),
								EndIter = m_pDesktopInfosCollection->GetData()->end();
						for (; Iter != EndIter; ++Iter)
						{
								if ( !IdsCollection.IsThereId((*Iter)->GetSessionId()) )
								{
										if ((*Iter)->GetProcessHandle())
										{
											TerminateProcess((*Iter)->GetProcessHandle(), 0);
											CloseHandle((*Iter)->GetProcessHandle());
											(*Iter)->SetProcessHandle(0);
										}
										if ((*Iter)->GetThreadHandle())
										{
											CloseHandle((*Iter)->GetThreadHandle());
											(*Iter)->SetThreadHandle(0);
										}
									m_pDesktopInfosCollection->DeleteResident(**Iter);

									bDeleted = true;
									break;
								}
						}
					}
					while(bDeleted);

			UpdateExchangeData();

				if (m_pDesktopInfosCollection->LookForSessionId(dwSessionId))
					return;

				if (!strcmp(m_pNewUserDefiner->GetCurrentUserName().c_str(), ""))
					return;

			HANDLE hToken = 0;
			OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
				if ( !hToken )
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					throw CAnyLogableException(((std::string)"Can't open process token. System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
				}


			DWORD dwOldSessionId = 0;
			DWORD dwReturned = 0;
				if (!GetTokenInformation(hToken, TokenSessionId, &dwOldSessionId, sizeof(DWORD), &dwReturned))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					throw CAnyLogableException(((std::string)"Can't get token's session id. System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
				}

				if (!SetTokenInformation(hToken, TokenSessionId, &dwSessionId, 4))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					throw CAnyLogableException(((std::string)"Can't set token's session id. System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
				}

			HANDLE hPrimaryToken = 0;
			DuplicateTokenEx(
						hToken,
						TOKEN_IMPERSONATE | TOKEN_READ | TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE,
						0,
						SecurityImpersonation,
						TokenPrimary,
						&hPrimaryToken);

			DWORD dwErrorCode = GetLastError();

				if (!hPrimaryToken)
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErrorCode,
								NULL, Buffer.begin(), 0xfe, NULL);

					throw CAnyLogableException((std::string("DuplicateTokenEx failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

			//HANDLE hPrimaryToken = m_pNewUserDefiner->GetCurrentUserPrimaryToken();

			PROCESS_INFORMATION pi;
			memset( &pi, 0, sizeof( pi ) );

			STARTUPINFO si;
			memset( &si, 0, sizeof( si ) );
			si.cb = sizeof( si );

			BOOL bCreateResult = true;
			bCreateResult = CreateProcessAsUser(
						hPrimaryToken,
						m_sDesktopExecutablePath.c_str(), // Application name
						0,//(char*)(m_sRunnerName + " " + a_pShortcut->GetLinkFileName()).c_str(),
						NULL, // Process security attributes
						NULL, // thread security attributes
						false, // Are handles inherited
						0, // Creation flags
						NULL, // Environment block
						NULL, // Current directory
						&si, // Startup information
						&pi // Process information
			);

			dwErrorCode = GetLastError();

				if (hPrimaryToken)
				{
					CloseHandle(hPrimaryToken);
					hPrimaryToken = 0;
				}

				if (!bCreateResult)
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErrorCode,
								NULL, Buffer.begin(), 0xfe, NULL);

					throw CAnyLogableException((std::string("CreateProcessAsUser failed with message: ") + Buffer).c_str(), bWriteDuplicates);
				}

			m_pDesktopInfosCollection->AddApplication(dwSessionId, pi.dwThreadId, pi.hProcess, pi.hThread);

			UpdateExchangeData();
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(((std::string)"An error occured in CSlaveManager::OnNewUserLogged(): " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CSlaveManager::OnNewUserLogged()", bDoNotWriteDuplicates);
		}

	m_bDesktopCreatedSuccessfully = true;
}
// End of OnNewUserLogged()


bool CSlaveManager::DoTerminateInproperSessions(DWORD a_dwSessionId)
{
	bool bResult = false;
		try
		{
			CWTSSessionsIdsCollection IdsCollection;
			m_pNewUserDefiner->DoFillSessionsIdsCollection(&IdsCollection);

			std::string sUserName;
				for (int i = 0; i < IdsCollection.size(); ++i)
						try
						{
							sUserName = m_pNewUserDefiner->GetUserNameBySessionId(IdsCollection[i]);

								if ( m_pSuperUsersNamesCollection->LookForName(sUserName.c_str()) )
									continue;

								if ( (!m_Remaining.LookForUserName(sUserName.c_str()))
											|| m_bMustBeLocked )
								{
									bResult |= (IdsCollection[i] == a_dwSessionId);

									LPTSTR pName;

									WTSDisconnectSession(
												WTS_CURRENT_SERVER_HANDLE,
												IdsCollection[i],
												false);

									CSessionTimeOutManager SessionTimeOut(IdsCollection[i], 5 * A_Second.GetTime());
										if ( m_pTimeOutCollection->FindResident(SessionTimeOut) == m_pTimeOutCollection->GetData()->end() )
										{
											m_pTimeOutCollection->AddResident(SessionTimeOut);
										}
								}
						}
						catch(CAnyLogableException& Error)
						{
							WriteTextMessage(Error.what(), 0);
						}
						catch(...)
						{
						}

				try
				{
					bool bDeleted = false;
						do
						{
							bDeleted = false;
							CSessionTimeOutCollection::iterator Iter = m_pTimeOutCollection->GetData()->begin(),
										EndIter = m_pTimeOutCollection->GetData()->end();
								for (; Iter != EndIter; ++Iter)
								{
										if ((*Iter)->IsTimeExpired())
										{
											WTSLogoffSession(
														WTS_CURRENT_SERVER_HANDLE,
														(*Iter)->GetSessionId(),
														false);

											m_pTimeOutCollection->DeleteResident(**Iter);
											bDeleted = true;
											break;
										}
								}
						}
						while(bDeleted);
				}
				catch(...)
				{
				}
		}
		catch(...)
		{
		}

	return bResult;
}
// End of DoTerminateInproperSessions()


void CSlaveManager::CheckForAllowOrDisallow(LPTSTR a_pName)
{
		try
		{
				if ( (!m_Remaining.LookForUserName(a_pName)) &&
							(!m_pSuperUsersNamesCollection->LookForName(a_pName)) )
					DoAllowLogon(a_pName, false);
				else
					DoAllowLogon(a_pName, true);
		}
		catch(CAnyLogableException& Error)
		{
			//WriteTextMessage(Error.what(), 0);
		}
		catch(...)
		{
		}
}
// End of CheckForAllowOrDisallow


void CSlaveManager::DoAllowLogon(LPTSTR a_pName, bool a_bAllow)
{
	LPTSTR pReturned = 0;
	DWORD dwReturned = 0;

		if (!WTSQueryUserConfig(
					WTS_CURRENT_SERVER_NAME,
					a_pName,
					WTSUserConfigfAllowLogonTerminalServer,
					&pReturned,
					&dwReturned))
		{
			std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);

				if (pReturned)
				{
					WTSFreeMemory(pReturned);
					pReturned = 0;
				}

			throw CAnyLogableException(((std::string)"Can't get AllowLogon for user " + a_pName + ". System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
		}
	bool bWasAllowed = pReturned[0];

		if (bWasAllowed != a_bAllow)
		{
			pReturned[0] = a_bAllow;
				if(!WTSSetUserConfig(
							WTS_CURRENT_SERVER_NAME,
							a_pName,
							WTSUserConfigfAllowLogonTerminalServer,
							pReturned,
							dwReturned))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

						if (pReturned)
						{
							WTSFreeMemory(pReturned);
							pReturned = 0;
						}

					throw CAnyLogableException(((std::string)"Can't set AllowLogon for user " + a_pName + ". System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
				}
		}

		if (pReturned)
		{
			WTSFreeMemory(pReturned);
			pReturned = 0;
		}
}
// End of DoAllowLogon


void CSlaveManager::RestartWindows()
{
		if (!m_bMustBeLocked)
			ExitWindowsEx(EWX_FORCE | EWX_REBOOT, 0);
}
// End of RestartWindows()


void CSlaveManager::TurnOffComputer()
{
		if (!m_bMustBeLocked)
			ExitWindowsEx(EWX_FORCE | EWX_POWEROFF, 0);
}
// End of TurnOffComputer()
