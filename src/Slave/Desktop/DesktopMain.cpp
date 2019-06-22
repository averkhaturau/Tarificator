#include "stdafx.h"


#include "..\Slave\Exceptions.h"
#include "..\Slave\Messages.h"
#include "..\Slave\SlaveRegistryDataReader.h"
#include "..\Slave\Constants.h"
#include "..\Slave\ErrorsLogger.h"
#include "DesktopEmulator.h"





void CALLBACK TimerFunction(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	PostThreadMessage(GetCurrentThreadId(), WM_SLAVE_TIMER, 0, 0);
}


int APIENTRY WinMain(HINSTANCE hInstance,
			HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CDesktopEmulator* pEmulator = 0;

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
			HWINSTA hStation = OpenWindowStation("winsta0", true,
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

				if (hStation == NULL)
					throw CAnyLogableException("Can't open window station", bDoNotWriteDuplicates);

				if (!SetProcessWindowStation(hStation))
				{
						if (hStation)
						{
							CloseWindowStation(hStation);
							hStation = 0;
						}

					throw CAnyLogableException("Can't set process window station", bDoNotWriteDuplicates);
				}
				if (hStation)
				{
					CloseWindowStation(hStation);
					hStation = 0;
				}

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

				if (!SetThreadDesktop(hDesktop))
				{
						if (hDesktop)
						{
							CloseDesktop(hDesktop);
							hDesktop = 0;
						}

					throw CAnyLogableException("Can't set thread desktop", bDoNotWriteDuplicates);
				}
				if (hDesktop)
				{
					CloseDesktop(hDesktop);
					hDesktop = 0;
				}

			CSlaveRegistryDataReader Reader;

			CNewUserDefiner Definer;

			pEmulator = new CDesktopEmulator(hInstance, true, &Definer.GetCurrentUserName(), 0, &Reader, Definer.GetCurrentUserPrimaryToken(), Definer.GetCurrentUserImpersonatingToken(), Definer.GetCurrentUserSessionId());

			pErrorsLogger->GetProhibitionsTable()->AddName("User is not restricted!");
				if ( !pEmulator->IsUserRestricted() )
					throw CAnyLogableException("User is not restricted!", bDoNotWriteDuplicates);

			pEmulator->StartTimer(TimerFunction);

			// Чтобы прога висела и ловила мессаги
			MSG theMessage;
				while ( GetMessage(&theMessage, NULL, 0, 0) )
				{
						if ( (theMessage.message == WM_SLAVE_CLOSE) /*||
									(theMessage.message == WM_CLOSE)*/ )
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
										pEmulator->OnIconButtonClicked((CIconButton*)theMessage.wParam);
									break;

									case WM_WAITED_APPLICATION_ENDED:
										pEmulator->OnWaitedApplicationEnded((CMultiThreadManager*)theMessage.wParam);
									break;

									case WM_ACTIVATED:
										pEmulator->OnActivated((HWND)theMessage.wParam);
									break;

									case WM_NEED_TO_ACTIVATE:
										pEmulator->NeedToActivate();
									break;

									case WM_WRITE_DEBUG_MESSAGE:
										char cFirstBuffer[20], cSecondBuffer[20];
										_itoa(theMessage.wParam, &(cFirstBuffer[0]), 10);
										_itoa(theMessage.lParam, &(cSecondBuffer[0]), 10);
											if (pErrorsLogger)
											{
												pErrorsLogger->AddLogEntry( ((std::string)"Debug Message: " + cFirstBuffer + ", " + cSecondBuffer).c_str(), bWriteDuplicates );
											}
									break;

									case WM_WRITE_TEXT_MESSAGE:
										char cBuffer[20];
										_itoa(theMessage.lParam, &(cBuffer[0]), 10);
											if (pErrorsLogger)
											{
												pErrorsLogger->AddLogEntry( (*((std::string*)theMessage.wParam) + cBuffer).c_str(), bWriteDuplicates );
											}
										delete (std::string*)theMessage.wParam;
									break;

									/*case WM_SET_IS_USER_RESTRICTED:
										PostThreadMessage(pParameters->GetParentManager()->GetCallbackThreadId(), WM_SET_IS_USER_RESTRICTED, theMessage.wParam, theMessage.lParam);
									break;

									case WM_CHECK_SPECIAL_KEYS:
										PostThreadMessage(pParameters->GetParentManager()->GetCallbackThreadId(), WM_CHECK_SPECIAL_KEYS, theMessage.wParam, theMessage.lParam);
									break;*/

									case WM_SLAVE_TIMER:
										pEmulator->OnTimer();
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

		if (pEmulator)
		{
			delete pEmulator;
			pEmulator = 0;
		}
		if (pErrorsLogger)
		{
			delete pErrorsLogger;
			pErrorsLogger = 0;
		}

	return 0;
}