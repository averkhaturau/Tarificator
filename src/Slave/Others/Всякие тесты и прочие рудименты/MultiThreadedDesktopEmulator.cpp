#include "stdafx.h"

#include "MultiThreadedDesktopEmulator.h"
#include "..\Slave\Exceptions.h"
#include "..\Slave\Messages.h"
#include "..\Slave\SlaveRegistryDataReader.h"
#include "..\Slave\Constants.h"
#include "..\Slave\ErrorsLogger.h"




// Свободные функции
DWORD WINAPI DesktopProc(void* pParam)
{
	CMultiThreadedDesktopEmulatorParameters* pParameters = (CMultiThreadedDesktopEmulatorParameters*)pParam;

	CDesktopEmulator* pEmulator = 0;

	CMultiThreadManager* pManager = 0;
		if (pParameters)
				if (pParameters->GetMultiThreadedDesktopEmulator())
						if (pParameters->GetMultiThreadedDesktopEmulator()->GetMultiThreadManager())
						{
							pParameters->GetMultiThreadedDesktopEmulator()->GetMultiThreadManager()->OnThreadBegan(&pManager);
							pParameters->GetMultiThreadedDesktopEmulator()->GetMultiThreadManager()->SetAnotherThreadId(GetCurrentThreadId());
						}

	CErrorsLogger* pErrorsLogger = 0;
		// Персональный try для создания логгера ошибок
		try
		{
			CSlaveRegistryDataReader Reader;

			Reader.SetKey(HKEY_LOCAL_MACHINE);
			Reader.SetSecurityAccessMask(KEY_READ);
			*(Reader.GetSubKeyName()) = sSlaveRegistryPath;

			// Теперь pLogger инициализирован
			pErrorsLogger = new CErrorsLogger(0);
			Reader.ReadDesktopErrorLoggerData(pErrorsLogger);
			pErrorsLogger->GetProhibitionsTable()->resize(1);
			(*pErrorsLogger->GetProhibitionsTable())[0] = "Exit!";
		}
		catch(...)
		{
		}

		try
		{
			PROCESS_INFORMATION pi;
			STARTUPINFO         si;

			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb        = sizeof(STARTUPINFO);
			//si.lpDesktop = "winsta0\\default";
				if (!CreateProcessAsUser(
							pParameters->GetPrimaryToken(),
							NULL,
							"e:\mb.exe",
							NULL,
							NULL,
							FALSE,
							NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
							NULL,
							NULL,
							&si,
							&pi
							))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);
					throw CAnyLogableException(((std::string)"Can't create process! System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
				}

				if (pParameters->GetPrimaryToken())
				{
					CloseHandle(pParameters->GetPrimaryToken());
					pParameters->SetPrimaryToken(0);
				}







			CSlaveRegistryDataReader Reader;

				if (!SetThreadToken(NULL, pParameters->GetImpersonatingToken()))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);
					throw CAnyLogableException(((std::string)"Can't set thread's token! System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
				}

				if (pParameters->GetImpersonatingToken())
				{
					CloseHandle(pParameters->GetImpersonatingToken());
					pParameters->SetImpersonatingToken(0);
				}

			HWINSTA hStation = OpenWindowStation("WinSta0", true,
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

			SetProcessWindowStation(hStation);

			HDESK hDesktop = OpenDesktop("default", 0, true,
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
			SetThreadDesktop(hDesktop);

				if (hStation)
				{
					CloseWindowStation(hStation);
					hStation = 0;
				}
				if (hDesktop)
				{
					CloseDesktop(hDesktop);
					hDesktop = 0;
				}

			MessageBox(0, "Fuck!", "", MB_OK);

			//pEmulator = new CDesktopEmulator(pParameters->GetInstance(), true, pParameters->GetUserName(), pParameters->GetRemaining(), &Reader, pParameters->GetPrimaryToken(), 0, 0);
			pParameters->GetMultiThreadedDesktopEmulator()->SetDesktopEmulator(pEmulator);

			// Чтобы прога висела и ловила мессаги
			MSG theMessage;
				while ( GetMessage(&theMessage, NULL, 0, 0) )
				{
					if (theMessage.message == WM_CLOSE)
					{
						throw CAnyLogableException("Exit!", bDoNotWriteDuplicates);
					}
						// Чтобы исключения в процессе работы не приводили к выходу
						// из программы, и чтобы их можно было записАть в лог
						try
						{
							TranslateMessage(&theMessage);
							DispatchMessage(&theMessage);
								switch (theMessage.message)
								{
									case WM_ICON_BUTTON_CLICKED:
										pParameters->GetMultiThreadedDesktopEmulator()->GetDesktopEmulator()->OnIconButtonClicked((CIconButton*)theMessage.wParam);
									break;

									case WM_WAITED_APPLICATION_ENDED:
										pParameters->GetMultiThreadedDesktopEmulator()->GetDesktopEmulator()->OnWaitedApplicationEnded((CMultiThreadManager*)theMessage.wParam);
									break;

									case WM_ACTIVATED:
										pParameters->GetMultiThreadedDesktopEmulator()->GetDesktopEmulator()->OnActivated((HWND)theMessage.wParam);
									break;

									case WM_NEED_TO_ACTIVATE:
										pParameters->GetMultiThreadedDesktopEmulator()->GetDesktopEmulator()->NeedToActivate();
									break;

									case WM_WRITE_DEBUG_MESSAGE:
										//PostThreadMessage(pParameters->GetParentManager()->GetCallbackThreadId(), WM_WRITE_DEBUG_MESSAGE, 0, 0);
										PostThreadMessage(pParameters->GetParentManager()->GetCallbackThreadId(), WM_WRITE_DEBUG_MESSAGE, theMessage.wParam, theMessage.lParam);
									break;

									case WM_SET_IS_USER_RESTRICTED:
										PostThreadMessage(pParameters->GetParentManager()->GetCallbackThreadId(), WM_SET_IS_USER_RESTRICTED, theMessage.wParam, theMessage.lParam);
									break;

									case WM_CHECK_SPECIAL_KEYS:
										PostThreadMessage(pParameters->GetParentManager()->GetCallbackThreadId(), WM_CHECK_SPECIAL_KEYS, theMessage.wParam, theMessage.lParam);
									break;

									case WM_SLAVE_TIMER:
										pParameters->GetMultiThreadedDesktopEmulator()->GetDesktopEmulator()->OnTimer();
									break;
								}
						}
						catch(CAnyLogableException& Error)
						{
								if (pErrorsLogger)
								{
									pErrorsLogger->AddLogEntry(&Error);
								}
						}
						catch(...)
						{
								if (pErrorsLogger)
								{
									pErrorsLogger->AddLogEntry("An unknown error occured in desktop's message loop", bDoNotWriteDuplicates);
								}
						}
				}
		}
		catch(CAnyLogableException& Error)
		{
				if (pErrorsLogger)
				{
					pErrorsLogger->AddLogEntry(&Error);
				}
		}
		catch(...)
		{
				if (pErrorsLogger)
				{
					pErrorsLogger->AddLogEntry("An unknown error occured in DesktopProc", bWriteDuplicates);
				}
		}

		if (pManager)
		{
			pParameters->GetMultiThreadedDesktopEmulator()->SetDesktopEmulator(0);
			pManager->OnThreadEnded();
		}

		if (pEmulator)
		{
			delete pEmulator;
			pEmulator = 0;
		}

	return 0;
}
// End of DesktopProc
// Конец свободных функций





CMultiThreadedDesktopEmulator::CMultiThreadedDesktopEmulator()
{
	m_pDesktopEmulator = 0;
	m_pMultiThreadManager = 0;
		try
		{
			m_pMultiThreadManager = new CMultiThreadManager;
		}
		catch(CAnyLogableException)
		{
			DoDeleteEverything();
			throw;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CMultiThreadedDesktopEmulator::CMultiThreadedDesktopEmulator()", bDoNotWriteDuplicates);
		}
}
// End of CMultiThreadedDesktopEmulator()


CMultiThreadedDesktopEmulator::~CMultiThreadedDesktopEmulator()
{
	PostThreadMessage(m_pMultiThreadManager->GetAnotherThreadId(), WM_CLOSE, 0, 0);
	DoDeleteEverything();
}
// End of ~CMultiThreadedDesktopEmulator()


void CMultiThreadedDesktopEmulator::DoDeleteEverything()
{
		if (m_pMultiThreadManager)
		{
			delete m_pMultiThreadManager;
			m_pMultiThreadManager = 0;
		}
}
// End of DoDeleteEverything()


void CMultiThreadedDesktopEmulator::Create(HINSTANCE a_hInst, std::string* a_pUserName, CRemainingTimeSlaveDescription* a_pRemaining, HANDLE a_hImpersonatingToken, HANDLE a_hPrimaryToken)
{
	m_Parameters.SetInstance(a_hInst);
	*m_Parameters.GetUserName() = *a_pUserName;
	m_Parameters.SetRemaining(a_pRemaining);
	m_Parameters.SetImpersonatingToken(a_hImpersonatingToken);
	m_Parameters.SetPrimaryToken(a_hPrimaryToken);

	m_Parameters.SetMultiThreadedDesktopEmulator(this);
	m_Parameters.SetParentManager(m_pMultiThreadManager);
	m_pMultiThreadManager->SetCallbackThreadId(GetCurrentThreadId());
	m_pMultiThreadManager->SetNeedToTerminateThread(false);

	m_pMultiThreadManager->StartAnotherThread(NULL, 0, DesktopProc,
						&m_Parameters, 0);
}
// End of Create
