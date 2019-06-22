#include "stdafx.h"

#include "..\Slave\SlaveRegistryDataReader.h"
#include "..\Slave\Messages.h"
/*#include "GlobalVariables.h"
#include "SlaveManager.h"*/

#include "DesktopEmulator.h"
#include "..\Slave\Exceptions.h"
#include "..\..\Master\DataStructures\ClubSettings\IntervalAddition.h"
#include "..\Slave\WriteTextMessage.h"

#include <math.h>
#include "shlobj.h"
#include "Lmcons.h"
#include "Winuser.h"
#include "Windows.h"


// Свободные функции
BOOL CALLBACK FindStartButton(HWND hwnd, LPARAM lParam)
{
	char cBuffer[100];

	GetClassName(hwnd, &(cBuffer[0]), 90);

		if (!strcmp(cBuffer, "Button"))
		{
			*((HWND*)lParam) = hwnd;
			return FALSE;
		}

	return TRUE;
}


BOOL CALLBACK FindSystemTray(HWND hwnd, LPARAM lParam)
{
	char cBuffer[100];

	GetClassName(hwnd, &(cBuffer[0]), 90);

		if (!strcmp(cBuffer, "TrayNotifyWnd"))
		{
			*((HWND*)lParam) = hwnd;
			return FALSE;
		}

	return TRUE;
}


BOOL CALLBACK FindProgman(HWND hwnd, LPARAM lParam)
{
	char cBuffer[100];

	GetClassName(hwnd, &(cBuffer[0]), 90);

		if (!strcmp(cBuffer, "Progman"))
		{
			GetWindowText(hwnd, &(cBuffer[0]), 90);
				if (!strcmp(cBuffer, "Program Manager"))
				{
					*((HWND*)lParam) = hwnd;
					return FALSE;
				}
		}

	return TRUE;
}


BOOL CALLBACK FindSysList(HWND hwnd, LPARAM lParam)
{
	char cBuffer[100];

	GetClassName(hwnd, &(cBuffer[0]), 90);

		if (!strcmp(cBuffer, "SysListView32"))
		{
			//GetWindowText(hwnd, &(cBuffer[0]), 90);
				//if (!strcmp(cBuffer, ""))
				//{
					*((HWND*)lParam) = hwnd;
					return FALSE;
				//}
		}

	return TRUE;
}

// Конец свободных функций





CDesktopEmulator::CDesktopEmulator(HINSTANCE a_hInst, bool a_bEnabled, std::string* a_pUserName, CRemainingTimeSlaveDescription* a_pRemaining, CSlaveDataReader* a_pReader, HANDLE a_hPrimaryToken, HANDLE a_hImpersonatingToken, DWORD a_dwSessionId)
{
	m_bEnabled = a_bEnabled;
	m_hDesktopEmulation = 0;
	m_bIconsFilledForThisUser = 0;
	m_bFillingIcons = 0;
	m_pStatusBar = 0;

	m_bIsTaskbarArtificial = 0;

	m_hInst = a_hInst;

	m_pIconsWindow = 0;
	m_pSpecialIconsWindow = 0;

	m_sPreliminaryIconsFolderPath = "";

		if (a_pRemaining)
			m_Remaining = *a_pRemaining;
		else
			m_Remaining.FillWithZeros();

	m_bTaskbarHidden = false;
	m_bOnlyOneApplication = 0;

	m_pApplicationWaiter = 0;
	m_pPreliminaryAppWaiter = 0;

	m_hPrimaryToken = a_hPrimaryToken;
	m_hImpersonatingToken = a_hImpersonatingToken;

	m_sFullName = "";

	m_uiTimerIdentifier = 0;

	m_bNeedToCloseSysTray = true;

	m_bLockNeeded = 0;

	m_pAllowedSessionsCollection = 0;

	m_dwSessionId = a_dwSessionId;

	m_pTaskbarEmulator = 0;

		try
		{
			m_pIconsWindow = new CIconsWindow(a_hInst);
			m_pSpecialIconsWindow = new CIconsWindow(a_hInst);
			m_pStatusBar = new CSlaveStatusBar(a_hInst);
			m_pTaskbarEmulator = new CTaskbarEmulator(a_hInst);

			m_pApplicationWaiter = new CApplicationWaiter;
			m_pPreliminaryAppWaiter = new CApplicationWaiter;

			m_pAllowedSessionsCollection = new CApplicationInfosCollection;

			// Нужно вызвать перед разбором ярлыков
			CoInitialize(NULL);

				if (a_bEnabled)
				{
						try
						{
							a_pReader->ReadDesktopEmulatorData(this, a_pUserName);
						}
						catch(CAnyLogableException)
						{
						}
				}

				/*if (!SetThreadToken(0, a_hImpersonatingToken))
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					throw CAnyLogableException(((std::string)"Can't set thread token. System message: " + Buffer).c_str(), bDoNotWriteDuplicates);
				}*/
		}
		catch(CAnyLogableException)
		{
			DoDeleteEverything();
			throw;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CDesktopEmulator::CDesktopEmulator", bDoNotWriteDuplicates);
		}
}
// End of CDesktopEmulator()


CDesktopEmulator::~CDesktopEmulator()
{
		if (m_bEnabled)
		{
				if ( (*m_pIconsWindow->GetIconsFolderPath() != "") && (*m_pSpecialIconsWindow->GetIconsFolderPath() != "") )
				{
					DoHideTaskbar(cdeUnHideTaskbar);
				}
		}

	DoDeleteEverything();
}
// End of ~CDesktopEmulator()


void CDesktopEmulator::DoDeleteEverything()
{
		if (m_pIconsWindow)
		{
			delete m_pIconsWindow;
			m_pIconsWindow = 0;
		}
		if (m_pSpecialIconsWindow)
		{
			delete m_pSpecialIconsWindow;
			m_pSpecialIconsWindow = 0;
		}
		if (m_pStatusBar)
		{
			delete m_pStatusBar;
			m_pStatusBar = 0;
		}
		if (m_hDesktopEmulation)
		{
			DestroyWindow(m_hDesktopEmulation);
			m_hDesktopEmulation = 0;
		}
		if (m_pApplicationWaiter)
		{
			delete m_pApplicationWaiter;
			m_pApplicationWaiter = 0;
		}
		if (m_pPreliminaryAppWaiter)
		{
			delete m_pPreliminaryAppWaiter;
			m_pPreliminaryAppWaiter = 0;
		}
		if (m_pTaskbarEmulator)
		{
			delete m_pTaskbarEmulator;
			m_pTaskbarEmulator = 0;
		}
		if (m_hPrimaryToken)
		{
			CloseHandle(m_hPrimaryToken);
			m_hPrimaryToken = 0;
		}
		if (m_hImpersonatingToken)
		{
			CloseHandle(m_hImpersonatingToken);
			m_hImpersonatingToken = 0;
		}
		if (m_uiTimerIdentifier)
		{
			KillTimer(NULL, m_uiTimerIdentifier);
			m_uiTimerIdentifier = 0;
		}
		if (m_pAllowedSessionsCollection)
		{
			delete m_pAllowedSessionsCollection;
			m_pAllowedSessionsCollection = 0;
		}
}
// End of DoDeleteEverything()


void CDesktopEmulator::StartTimer(CTimerProcedure* Procedure)
{
	// Чтобы вызывать по таймеру функцию TimerFunction
	m_uiTimerIdentifier = SetTimer(NULL, 0, 1000, Procedure);
		if (!m_uiTimerIdentifier)
			throw CAnyLogableException("Can't create timer", bDoNotWriteDuplicates);
}
// End of StartTimer


bool CDesktopEmulator::IsUserRestricted()
{
	return ( (*GetIconsWindow()->GetIconsFolderPath())[0] ) ||
				( (*GetSpecialIconsWindow()->GetIconsFolderPath())[0] );
}
// End of IsUserRestricted()


void CDesktopEmulator::DoHideTaskbar(bool a_bHide)
{
	bool bSuccess = true;

	HWND hTaskbarWindow = FindWindow("Shell_traywnd", "");

		if (hTaskbarWindow)
		{
				if (m_bIsTaskbarArtificial)
					ShowWindow(hTaskbarWindow, (a_bHide == cdeHideTaskbar) ? SW_HIDE : SW_SHOW);

			//PostThreadMessage(GetCurrentThreadId(), WM_NEED_TO_SET_TASKBAR, (WPARAM)hTaskbarWindow, 0);

			HWND hStartMenuButton = 0;
			EnumChildWindows(hTaskbarWindow, FindStartButton, (LONG)&hStartMenuButton);
				if (hStartMenuButton)
						if (a_bHide == cdeHideTaskbar)
							PostMessage(hStartMenuButton, WM_CLOSE, 0, 0);

			HWND hSystemTray = 0;
			EnumChildWindows(hTaskbarWindow, FindSystemTray, (LONG)&hSystemTray);
				if (hSystemTray)
						if (a_bHide == cdeHideTaskbar)
							EnableWindow(hSystemTray, false);
						else
							EnableWindow(hSystemTray, true);
		}
		else // hTaskbarWnd
			bSuccess = false;

		if (!m_bIsTaskbarArtificial)
		{
			m_bTaskbarHidden = bSuccess;
			return;
		}

	HWND hProgmanWindow = 0;
	EnumChildWindows(GetDesktopWindow(), FindProgman, (LONG)&hProgmanWindow);

	HWND hSysListWindow = 0;
	EnumChildWindows(hProgmanWindow, FindSysList, (LONG)&hSysListWindow);
		if (hSysListWindow)
				if (a_bHide == cdeHideTaskbar)
					EnableWindow(hSysListWindow, false);
				else
					EnableWindow(hSysListWindow, true);
		else
			bSuccess = false;

	m_bTaskbarHidden = bSuccess;
}
// End of DoHideTaskbar()


void CDesktopEmulator::CreateDesktopEmulationWindow()
{
		if (m_hDesktopEmulation)
			return;

	HWND hProgmanWindow = 0;
	EnumChildWindows(GetDesktopWindow(), FindProgman, (LONG)&hProgmanWindow);

		if (hProgmanWindow)
		{
			RECT Rect;
			GetClientRect(GetDesktopWindow(), &Rect);

			SystemParametersInfo(SPI_GETWORKAREA, 0, &Rect, SPIF_UPDATEINIFILE);
				if (!m_hDesktopEmulation)
				{
					m_hDesktopEmulation = CreateWindowEx(
								WS_EX_TOOLWINDOW,
								/*&(cClassName[0])*/"SysListView32"/*"Static"*/,
								"",
								WS_CHILD | WS_DISABLED,
								Rect.left,
								Rect.top,
								Rect.right - Rect.left,
								Rect.bottom - Rect.top,
								/*100, 100, 600, 400,*/
								GetDesktopWindow(),
								0,
								0,
								0);
				}

			SetWindowPos(m_hDesktopEmulation, GetDesktopWindow(), 0, 0, 0, 0,
						SWP_NOMOVE | SWP_NOSIZE);

				if (!m_pIconsWindow->GetIconsWindow())
				{
					m_pIconsWindow->CreateWnd(
								WS_EX_APPWINDOW,
								"Desktop",
								WS_VISIBLE | WS_POPUP | WS_DLGFRAME,
								m_hDesktopEmulation);
				}

				if (!m_pSpecialIconsWindow->GetIconsWindow())
				{
					m_pSpecialIconsWindow->CreateWnd(
								WS_EX_TOOLWINDOW,
								"Special Desktop",
								WS_VISIBLE | WS_POPUP | WS_DLGFRAME,
								m_hDesktopEmulation);
				}

				if (!m_pStatusBar->GetWindow())
				{
					m_pStatusBar->CreateWnd(
								WS_EX_TOOLWINDOW,
								"",
								WS_VISIBLE | WS_POPUP | WS_DLGFRAME,
								m_hDesktopEmulation);
				}

				if ( (!m_pTaskbarEmulator->GetWnd()) && (m_bIsTaskbarArtificial) )
				{
					m_pTaskbarEmulator->CreateWnd(m_hInst);
				}
		}
}
// End of CreateDesktopEmulationWindow()


void CDesktopEmulator::DoFillIcons(HINSTANCE a_hInst)
{
//		if ( (*m_pIconsWindow->GetIconsFolderPath() == "") || (*m_pSpecialIconsWindow->GetIconsFolderPath() == "") )
//			return;

		if (!m_bTaskbarHidden)
			return;

		if (m_bIconsFilledForThisUser)
			return;

		if (m_bFillingIcons)
			return;

	m_bFillingIcons = true;

		try
		{
			CreateDesktopEmulationWindow();

			m_pIconsWindow->GetButonsCollection()->resize(0);
			DWORD dwAddedLNKs = 0, dwAddedPIFs = 0;
			DoFillIconButtonsCollection(m_pIconsWindow->GetButonsCollection(), *m_pIconsWindow->GetIconsFolderPath(), &dwAddedLNKs, (FileName)"*.lnk");
			DoFillIconButtonsCollection(m_pIconsWindow->GetButonsCollection(), *m_pIconsWindow->GetIconsFolderPath(), &dwAddedPIFs, (FileName)"*.pif");

			m_pSpecialIconsWindow->GetButonsCollection()->resize(0);
			DWORD dwAddedSpecialLNKs = 0, dwAddedSpecialPIFs = 0;
			DoFillIconButtonsCollection(m_pSpecialIconsWindow->GetButonsCollection(), *m_pSpecialIconsWindow->GetIconsFolderPath(), &dwAddedSpecialLNKs, (FileName)"*.lnk");
			DoFillIconButtonsCollection(m_pSpecialIconsWindow->GetButonsCollection(), *m_pSpecialIconsWindow->GetIconsFolderPath(), &dwAddedSpecialPIFs, (FileName)"*.pif");

			CIconButtonsCollection PreliminaryCollection;
			DWORD dwAddedPreliminaryLNKs = 0, dwAddedPreliminaryPIFs = 0;
			DoFillIconButtonsCollection(&PreliminaryCollection, *GetPreliminaryIconsFolderPath(), &dwAddedPreliminaryLNKs, (FileName)"*.lnk");
			DoFillIconButtonsCollection(&PreliminaryCollection, *GetPreliminaryIconsFolderPath(), &dwAddedPreliminaryPIFs, (FileName)"*.pif");

			m_pIconsWindow->GetButonsCollection()->ResolveAll(0);
			m_pSpecialIconsWindow->GetButonsCollection()->ResolveAll(0);
			PreliminaryCollection.ResolveAll(0);

			CIconButtonsCollection::iterator SourceIter = PreliminaryCollection.GetData()->begin(),
						SourceEndIter = PreliminaryCollection.GetData()->end();
				for (; SourceIter < SourceEndIter; ++SourceIter)
				{
					CIconButtonsCollection::iterator TargetIter = m_pIconsWindow->GetButonsCollection()->GetData()->begin(),
								TargetEndIter = m_pIconsWindow->GetButonsCollection()->GetData()->end();
						for (; TargetIter < TargetEndIter; ++TargetIter)
						{
								if (!strcmp( (*SourceIter)->GetShortcutInfo()->GetShortLinkFileName().c_str(), (*TargetIter)->GetShortcutInfo()->GetShortLinkFileName().c_str() ))
								{
									(*TargetIter)->CreatePreliminaryShortcutInfo((*SourceIter)->GetShortcutInfo());
									break;
								}
						}
				}

			DoCalcSpecialWindowExtends(dwAddedSpecialLNKs + dwAddedSpecialPIFs);

			// Для вычисления пропорции, т.е. чтобы при большом кол-ве икон
			// IconWindow занимал все место

			// Стиль таскбара
			DWORD dwStyle = GetWindowLong(FindWindow("Shell_traywnd", ""), GWL_STYLE);

			RECT MaxWorkRect;
				//if (dwStyle & WS_VISIBLE)
				{
					SystemParametersInfo(SPI_GETWORKAREA, 0, &MaxWorkRect, SPIF_UPDATEINIFILE);
				}
				/*else
				{
					GetWindowRect(GetDesktopWindow(), &MaxWorkRect);
				}*/

			UINT uiXResolution = MaxWorkRect.right - MaxWorkRect.left;
			UINT uiYResolution = MaxWorkRect.bottom - MaxWorkRect.top -
						(m_pSpecialIconsWindow->GetIconButtonYCoord(m_pSpecialIconsWindow->GetYIcons() + 1)
						+ 7 * GetSystemMetrics(SM_CYEDGE)
						+ uiSmallPictureHeight);

			m_pIconsWindow->SetXIcons(ceil( sqrt( (float)(uiXResolution * (dwAddedLNKs + dwAddedPIFs)) / uiYResolution) ) );
			m_pIconsWindow->SetYIcons(ceil( sqrt( (float)(uiYResolution * (dwAddedLNKs + dwAddedPIFs)) / uiXResolution) ) );

			bool bPosResult = DoRePosWindows();

			m_pIconsWindow->CreateAllButtons(a_hInst);

			m_pSpecialIconsWindow->CreateAllButtons(a_hInst);

				if ( bPosResult )
					m_bIconsFilledForThisUser = true;
		}
		catch(...)
		{
			m_bFillingIcons = false;
			throw;
		}
	m_bFillingIcons = false;
}
// End of DoFillIcons()


void CDesktopEmulator::DoCalcSpecialWindowExtends(DWORD a_dwSppecialLinks)
{
	DWORD dwButtonWidth = 0;
	//dwButtonWidth = GetSystemMetrics(SM_CXICON) + 2 * GetSystemMetrics(SM_CXEDGE);
	dwButtonWidth = m_pSpecialIconsWindow->GetIconButtonXCoord(1) - m_pSpecialIconsWindow->GetIconButtonXCoord(0);

	// Стиль таскбара
	DWORD dwStyle = GetWindowLong(FindWindow("Shell_traywnd", ""), GWL_STYLE);

	DWORD dwMaxWidth = 0;
		if (dwStyle & WS_VISIBLE)
		{
			dwMaxWidth = GetSystemMetrics(SM_CXFULLSCREEN);
		}
		else
		{
			RECT Rect;
			GetWindowRect(GetDesktopWindow(), &Rect);
			dwMaxWidth = Rect.right - Rect.left;
		}

	DWORD dwMaxButtonsInOneString = floor((float)(dwMaxWidth - 2 * GetSystemMetrics(SM_CXEDGE)) / (float)dwButtonWidth);
		if (a_dwSppecialLinks < dwMaxButtonsInOneString)
			m_pSpecialIconsWindow->SetXIcons(a_dwSppecialLinks);
		else
			m_pSpecialIconsWindow->SetXIcons(dwMaxButtonsInOneString);
	m_pSpecialIconsWindow->SetYIcons(ceil((float)a_dwSppecialLinks / (float)dwMaxButtonsInOneString));
}
// End of DoCalcSpecialWindowExtends


void CDesktopEmulator::DoFillIconButtonsCollection(CIconButtonsCollection* a_pButtons, FileName& a_Dir, DWORD* a_pdwAdded, FileName& a_Extention)
{
	WIN32_FIND_DATA fdFoundFile;
	HANDLE hFound = FindFirstFile((a_Dir + a_Extention).c_str(), &fdFoundFile);

	UINT uiTotalLinks = 0;
		if ( hFound != INVALID_HANDLE_VALUE )
		{
			BOOL bNextResult = 0;
				do
				{
					++uiTotalLinks;

					bNextResult = FindNextFile(hFound, &fdFoundFile);
				}
				while( bNextResult );
		}

	FindClose(hFound);

	DWORD dwOldSize = a_pButtons->size();

	a_pButtons->resize(dwOldSize + uiTotalLinks);

	UINT uiAddedLinks = 0;
	hFound = FindFirstFile((a_Dir + a_Extention).c_str(), &fdFoundFile);

		if ( hFound != INVALID_HANDLE_VALUE )
		{
			BOOL bNextResult = 0;
				do
				{
						if ( ((fdFoundFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) &&
									(uiAddedLinks < uiTotalLinks) )
						{
							(*a_pButtons)[uiAddedLinks + dwOldSize].GetShortcutInfo()->SetLinkFileName(&(a_Dir + fdFoundFile.cFileName));
							++uiAddedLinks;
						}

					bNextResult = FindNextFile(hFound, &fdFoundFile);
				}
				while( bNextResult );
		}

	FindClose(hFound);

	if ( uiTotalLinks != uiAddedLinks )
		{
			// Если вдруг между первым и вторым чтением изменилось кол-во
			// ярлыков на столе
			a_pButtons->resize(dwOldSize + uiAddedLinks);
			//DoFillIconButtonsCollection(a_pButtons, a_Dir, a_pdwAdded);
		}

	*a_pdwAdded = uiAddedLinks;
}
// End of DoFillIconButtonsCollection


void CDesktopEmulator::OnTimer()
{
		try
		{
			CSlaveRegistryDataReader Reader;
			Reader.ReadExchangeDesktopData(this);
		}
		catch(CAnyLogableException& Error)
		{
			//throw CAnyLogableException(((std::string)"An error occured in CDesktopEmulator::OnTimer() while reading exchange data: " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			//throw CAnyLogableException("An unknown error occured in CDesktopEmulator::OnTimer() while reading exchange data", bDoNotWriteDuplicates);
		}

		try
		{
				if ( !m_pAllowedSessionsCollection->LookForSessionId(m_dwSessionId) )
				{
					PostThreadMessage(GetCurrentThreadId(), WM_SLAVE_CLOSE, 0, 0);
				}
				if ( (*m_pIconsWindow->GetIconsFolderPath() != "") && (*m_pSpecialIconsWindow->GetIconsFolderPath() != "") )
				{
					DoHideTaskbar(cdeHideTaskbar);

					PostThreadMessage(GetCurrentThreadId(), WM_SET_IS_USER_RESTRICTED, 1, 0);

					DoFillIcons(m_hInst);

					DoRePosWindows();

					DoFillStatusBar();

						if (m_pTaskbarEmulator)
						{
							m_pTaskbarEmulator->OnTimer();
						}
				}
				else
				{
					PostThreadMessage(GetCurrentThreadId(), WM_SET_IS_USER_RESTRICTED, 0, 0);
				}

			PostThreadMessage(GetCurrentThreadId(), WM_CHECK_SPECIAL_KEYS, 0, 0);
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(((std::string)"An error occured in CDesktopEmulator::OnTimer(): " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CDesktopEmulator::OnTimer()", bDoNotWriteDuplicates);
		}
}
// End of OnTimer()


void CDesktopEmulator::InitializeForNewUser(std::string* a_pUserName)
{
		/*if (m_hDesktopEmulation)
		{
			DestroyWindow(m_hDesktopEmulation);
			m_hDesktopEmulation = 0;
		}*/
	m_pIconsWindow->GetButonsCollection()->resize(0);
	m_pSpecialIconsWindow->GetButonsCollection()->resize(0);

		if ( (*m_pIconsWindow->GetIconsFolderPath() != "") || (*m_pSpecialIconsWindow->GetIconsFolderPath() != "") )
		{
			DoHideTaskbar(cdeHideTaskbar);
		}

	DoFillIcons(m_hInst);
}
// End of InitializeForNewUser()


bool CDesktopEmulator::DoRePosWindows()
{
//		if ( (!m_hIconsWindow) || (!m_hNameWindow) )
//			return false;

	// Стиль таскбара
	DWORD dwStyle = GetWindowLong(FindWindow("Shell_traywnd", ""), GWL_STYLE);

	RECT MaxWorkRect;
		//if (dwStyle & WS_VISIBLE)
		{
			SystemParametersInfo(SPI_GETWORKAREA, 0, &MaxWorkRect, SPIF_UPDATEINIFILE);
		}
		/*else
		{
			GetWindowRect(GetDesktopWindow(), &MaxWorkRect);
		}*/


	UINT uiXResolution = MaxWorkRect.right - MaxWorkRect.left,
				uiYResolution = MaxWorkRect.bottom - MaxWorkRect.top;



	RECT IconsRect, SpecialRect, StatusRect;
	GetWindowRect(m_pIconsWindow->GetIconsWindow(), &IconsRect);
	GetWindowRect(m_pSpecialIconsWindow->GetIconsWindow(), &SpecialRect);
	GetWindowRect(m_pStatusBar->GetWindow(), &StatusRect);



	UINT uiSpecialWindowHeight = 0, uiSpecialWindowWidth = 0, uiSpecialWindowX = 0, uiSpecialWindowY = 0;
	uiSpecialWindowHeight = m_pSpecialIconsWindow->GetIconButtonYCoord(m_pSpecialIconsWindow->GetYIcons() + 1) + 2 * GetSystemMetrics(SM_CYDLGFRAME);
	uiSpecialWindowWidth = m_pSpecialIconsWindow->GetIconButtonXCoord(m_pSpecialIconsWindow->GetXIcons()) + 2 * GetSystemMetrics(SM_CXDLGFRAME);

	uiSpecialWindowX = (MaxWorkRect.right - MaxWorkRect.left - uiSpecialWindowWidth) / 2;
	uiSpecialWindowY = MaxWorkRect.top;
		if (m_pSpecialIconsWindow->GetXIcons() == 0)
			ShowWindow(m_pSpecialIconsWindow->GetIconsWindow(), SW_HIDE);
		else
			ShowWindow(m_pSpecialIconsWindow->GetIconsWindow(), SW_SHOW);

	DWORD dwSpecialPosResult = 0;
		if ( (SpecialRect.top != uiSpecialWindowY) ||
					(SpecialRect.bottom != uiSpecialWindowY + uiSpecialWindowHeight) ||
					(SpecialRect.left != uiSpecialWindowX) ||
					(SpecialRect.right != uiSpecialWindowX + uiSpecialWindowWidth) )
		{
			dwSpecialPosResult = SetWindowPos(
						m_pSpecialIconsWindow->GetIconsWindow(),
						0,
						uiSpecialWindowX,
						uiSpecialWindowY,
						uiSpecialWindowWidth,
						uiSpecialWindowHeight,
						SWP_NOZORDER);
		}
		else
			dwSpecialPosResult = 1;




	UINT uiStatusWindowHeight = 0, uiStatusWindowWidth = 0;
	uiStatusWindowHeight = uiSmallPictureHeight + 4 * GetSystemMetrics(SM_CYEDGE) + 2 * GetSystemMetrics(SM_CYDLGFRAME);
	uiStatusWindowWidth = uiXResolution;

	UINT uiStatusWindowX = 0, uiStatusWindowY = 0;
	uiStatusWindowX = MaxWorkRect.left;
	uiStatusWindowY = MaxWorkRect.bottom - uiStatusWindowHeight;

		if ( (m_pIconsWindow->GetXIcons() == 0) && (m_pSpecialIconsWindow->GetXIcons() == 0) )
			ShowWindow(m_pStatusBar->GetWindow(), SW_HIDE);
		else
			ShowWindow(m_pStatusBar->GetWindow(), SW_SHOW);

	DWORD dwStatusPosResult = 0;
		if ( (StatusRect.top != uiStatusWindowY) ||
					(StatusRect.bottom != uiStatusWindowY + uiStatusWindowHeight) ||
					(StatusRect.left != uiStatusWindowX) ||
					(StatusRect.right != uiStatusWindowX + uiStatusWindowWidth) )
		{
			dwStatusPosResult = SetWindowPos(
						m_pStatusBar->GetWindow(),
						0,
						uiStatusWindowX , uiStatusWindowY, uiStatusWindowWidth, uiStatusWindowHeight,
						SWP_NOZORDER);
		}
		else
			dwStatusPosResult = 1;




	UINT uiIconsWindowHeight = 0, uiIconsWindowWidth = 0;
	uiIconsWindowHeight = m_pIconsWindow->GetIconButtonYCoord(m_pIconsWindow->GetYIcons() + 1) + 2 * GetSystemMetrics(SM_CYDLGFRAME);
	uiIconsWindowWidth = m_pIconsWindow->GetIconButtonXCoord(m_pIconsWindow->GetXIcons()) + 2 * GetSystemMetrics(SM_CXDLGFRAME);

	UINT uiIconsWindowX = 0, uiIconsWindowY = 0;
	uiIconsWindowX = (uiXResolution - uiIconsWindowWidth) / 2;
	uiIconsWindowY = (uiYResolution - uiIconsWindowHeight - uiStatusWindowHeight - uiSpecialWindowHeight) / 2 + uiSpecialWindowHeight + uiSpecialWindowY;

		if (m_pIconsWindow->GetXIcons() == 0)
			ShowWindow(m_pIconsWindow->GetIconsWindow(), SW_HIDE);
		else
			ShowWindow(m_pIconsWindow->GetIconsWindow(), SW_SHOW);

	DWORD dwIconsPosResult = 0;
		if ( (IconsRect.top != uiIconsWindowY) ||
					(IconsRect.bottom != uiIconsWindowY + uiIconsWindowHeight) ||
					(IconsRect.left != uiIconsWindowX) ||
					(IconsRect.right != uiIconsWindowX + uiIconsWindowWidth) )
		{
			dwIconsPosResult = SetWindowPos(
						m_pIconsWindow->GetIconsWindow(),
						0,
						uiIconsWindowX , uiIconsWindowY, uiIconsWindowWidth, uiIconsWindowHeight,
						SWP_NOZORDER);
		}
		else
			dwIconsPosResult = 1;





		if ( (!dwIconsPosResult) || (!dwStatusPosResult) || (!dwSpecialPosResult) )
			return false;
		else
			return true;
}
// End of DoRePosWindows()


void CDesktopEmulator::OnActivated(HWND a_hActivatedWindow)
{
/*		if (a_hActivatedWindow != m_pIconsWindow->GetIconsWindow())
			SetWindowPos(m_pIconsWindow->GetIconsWindow(), HWND_TOP,
						0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);*/

		if (a_hActivatedWindow != m_pSpecialIconsWindow->GetIconsWindow())
		{
			/*SetWindowPos(m_pSpecialIconsWindow->GetIconsWindow(), HWND_TOPMOST,
						0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);*/
			SetWindowPos(m_pSpecialIconsWindow->GetIconsWindow(), HWND_TOP,
						0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

	/*SetWindowPos(m_pSpecialIconsWindow->GetIconsWindow(), HWND_TOP,
				0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowPos(m_pIconsWindow->GetIconsWindow(), HWND_TOP,
				0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_pSpecialIconsWindow->SetIsActivatingNow(false);
	m_pIconsWindow->SetIsActivatingNow(false);*/

	/*SetWindowPos(m_pStatusBar->GetWindow(), HWND_TOPMOST,
				0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);*/
	SetWindowPos(m_pStatusBar->GetWindow(), HWND_TOP,
				0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	/*SetWindowPos(m_pTaskbarEmulator->GetWnd(), HWND_TOPMOST,
				0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);*/
		if (m_bIsTaskbarArtificial)
			SetWindowPos(m_pTaskbarEmulator->GetWnd(), HWND_TOP,
						0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
// End of OnActivated()


void CDesktopEmulator::DoFillStatusBar()
{
	CTimeContainer PlusTime = (CTimeContainer)0,
				MinusTime = (CTimeContainer)0,
				CurrTime = CurrentTime().GetTime(),
				RemainingTime = (CTimeContainer)0;
		if (m_Remaining.MasterCurrent > m_Remaining.SlaveCurrent)
			PlusTime = m_Remaining.MasterCurrent - m_Remaining.SlaveCurrent;
		else
			MinusTime = m_Remaining.SlaveCurrent - m_Remaining.MasterCurrent;
	CurrTime += PlusTime;
	CurrTime -= MinusTime;
	// Теперь CurrTime получился в Master-времени

		if (CurrTime < m_Remaining.Finish)
			RemainingTime = m_Remaining.Finish - CurrTime;

	SetWindowText(m_pStatusBar->GetServerTimeTextWnd(), IntervalAddition::DescribeTime(&(CTimeStorage)CurrTime).c_str());
	SetWindowText( m_pStatusBar->GetIntervalTextWnd(), (std::string("с ") + IntervalAddition::DescribeTime(&(CTimeStorage)m_Remaining.Start) + " по " + IntervalAddition::DescribeTime(&(CTimeStorage)m_Remaining.Finish)).c_str() );
	SetWindowText(m_pStatusBar->GetRemainingTextWnd(), IntervalAddition::DescribeTime(&(CTimeStorage)RemainingTime).c_str());
}
// End of DoFillStatusBar()


void CDesktopEmulator::OnWaitedApplicationEnded(CMultiThreadManager* a_pManager)
{
		if (!a_pManager)
			return;

		if ( a_pManager == m_pPreliminaryAppWaiter->GetWaitManager() )
		{
			CIconButtonsCollection::iterator Iter = m_pIconsWindow->GetButonsCollection()->GetData()->begin(),
						EndIter = m_pIconsWindow->GetButonsCollection()->GetData()->end();
				for (; Iter < EndIter; ++Iter)
				{
						if ( !strcmp(m_sFullName.c_str(), (*Iter)->GetShortcutInfo()->GetLinkFileName().c_str()) )
						{
								if (m_bOnlyOneApplication)
								{
									EnableIconsWindow(false);
									(*Iter)->GetShortcutInfo()->SetUserToken((*Iter)->GetPreliminaryShortcutInfo()->GetUserToken());
									m_pApplicationWaiter->StartWaiting(RunShortcut((*Iter)->GetShortcutInfo()));
								}
								else
								{
									(*Iter)->GetShortcutInfo()->SetUserToken((*Iter)->GetPreliminaryShortcutInfo()->GetUserToken());
									RunShortcut((*Iter)->GetShortcutInfo());
								}
						}
				}
		}
		if (a_pManager == m_pApplicationWaiter->GetWaitManager())
		{
			EnableIconsWindow(true);
		}
}
// End of OnWaitedApplicationEnded()


void CDesktopEmulator::OnIconButtonClicked(CIconButton* a_pButton)
{
	bool bSpecial = true;
		if (a_pButton)
		{
			CIconButtonsCollection::iterator Iter = m_pIconsWindow->GetButonsCollection()->GetData()->begin(),
						EndIter = m_pIconsWindow->GetButonsCollection()->GetData()->end();
				for (; Iter < EndIter; ++Iter)
				{
					if ( *Iter == a_pButton )
					{
						bSpecial = false;
						break;
					}
				}

				if (!bSpecial)
				{
						if (a_pButton->GetPreliminaryShortcutInfo())
						{
							a_pButton->GetPreliminaryShortcutInfo()->SetUserToken(m_hPrimaryToken);
							m_pPreliminaryAppWaiter->StartWaiting(RunShortcut(a_pButton->GetPreliminaryShortcutInfo()));
							m_sFullName = a_pButton->GetShortcutInfo()->GetLinkFileName();
						}
						else
						{
								if (m_bOnlyOneApplication)
								{
									EnableIconsWindow(false);
									a_pButton->GetShortcutInfo()->SetUserToken(m_hPrimaryToken);
									m_pApplicationWaiter->StartWaiting(RunShortcut(a_pButton->GetShortcutInfo()));
								}
								else
								{
									a_pButton->GetShortcutInfo()->SetUserToken(m_hPrimaryToken);
									RunShortcut(a_pButton->GetShortcutInfo());
								}
						}
				}
				else
				{
					a_pButton->GetShortcutInfo()->SetUserToken(m_hPrimaryToken);
					RunShortcut(a_pButton->GetShortcutInfo());
				}
		}
}
// End of OnIconButtonClicked


void CDesktopEmulator::EnableIconsWindow(bool a_bEnabled)
{
	//EnableWindow(m_pIconsWindow->GetIconsWindow(), a_bEnabled);

	CIconButtonsCollection::iterator Iter = m_pIconsWindow->GetButonsCollection()->GetData()->begin(),
				EndIter = m_pIconsWindow->GetButonsCollection()->GetData()->end();
		for (; Iter < EndIter; ++Iter)
		{
			EnableWindow((*Iter)->GetWindow(), a_bEnabled);
		}
}
// End of EnableIconsWindow


void CDesktopEmulator::NeedToActivate()
{
	HWND hWasActive = SetActiveWindow(m_pIconsWindow->GetIconsWindow());

		if (hWasActive)
		{
			SendMessage(hWasActive, WM_ACTIVATEAPP, FALSE, 0);
			SendMessage(hWasActive, WM_ACTIVATE, FALSE, 0);
			SendMessage(hWasActive, WM_NCACTIVATE, FALSE, 0);
		}

	//SetWindowPos(m_pIconsWindow->GetIconsWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowPos(m_pIconsWindow->GetIconsWindow(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
// End of NeedToActivate()


/*HANDLE CDesktopEmulator::GetCurrentUserPrimaryToken()
{
	HWND hTaskbarWindow = FindWindow("Shell_traywnd", "");
		if (!hTaskbarWindow)
			return 0;

	DWORD dwProcessID = 0;
	GetWindowThreadProcessId(hTaskbarWindow, &dwProcessID);
		if (!dwProcessID)
			return 0;

	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
		if (!hProcess)
			return 0;

	HANDLE hProcessToken = 0;
	OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE, &hProcessToken);

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

		if (hProcessToken)
		{
			CloseHandle(hProcessToken);
			hProcessToken = 0;
		}

	return hPrimaryToken;
}*/
// End of GetCurrentUserPrimaryToken()


HANDLE CDesktopEmulator::RunShortcut(CShortcutInfo* a_pShortcut)
{
		if (!a_pShortcut)
			return 0;

	HANDLE hPrimaryToken = a_pShortcut->GetUserToken();

	/*SHELLEXECUTEINFO seInfo = {
				sizeof(SHELLEXECUTEINFO),
				SEE_MASK_NOCLOSEPROCESS, //| SEE_MASK_FLAG_NO_UI | SEE_MASK_DOENVSUBST | SEE_MASK_CONNECTNETDRV,
				0,
				"open",
				&(m_czTargetPath[0]),
				&(m_czArguments[0]),
				&(m_czWorkingDirectory[0]),
				m_iShowCmd,
				0,
				0, 0, 0, 0, 0,
				0};
		if (hUserToken)
		{
				if (ImpersonateLoggedOnUser(hUserToken))
				{
					ShellExecuteEx(&seInfo);
					RevertToSelf();
				}
		}*/

		if (hPrimaryToken)
		{
			PROCESS_INFORMATION pi;
			memset( &pi, 0, sizeof( pi ) );

			STARTUPINFO si;
			memset( &si, 0, sizeof( si ) );
			si.cb = sizeof( si );

			//RevertToSelf();

			BOOL bCreateResult = CreateProcessAsUser(
						hPrimaryToken,
						0, // Application name
						//(char*)m_sLinkFileName.c_str(), // CommandLine
						//"C:\\WINNT\\regedit.exe \"C:\\Documents and Settings\\Shurick\\Icons\\Test.reg\"",
						//"C:\\WINNT\\regedit.exe",
						(char*)(m_sRunnerName + " " + a_pShortcut->GetLinkFileName()).c_str(),
						NULL, // Process security attributes
						NULL, // thread security attributes
						false, // Are handles inherited
						0, // Creation flags
						NULL, // Environment block
						NULL, // Current directory
						&si, // Startup information
						&pi // Process information
			);

				/*if (!bCreateResult)
				{
					std::string Buffer;
					Buffer.resize(0xff);
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
								NULL, Buffer.begin(), 0xfe, NULL);

					WriteTextMessage(Buffer.c_str(), bCreateResult);
				}*/

				/*if (hPrimaryToken)
				{
					CloseHandle(hPrimaryToken);
					hPrimaryToken = 0;
				}*/

			//SetThreadToken(0, m_hImpersonatingToken);

			return pi.hProcess;
		}
		else
			return 0;

		/*if ((int)seInfo.hInstApp > 32)
			return seInfo.hProcess;
		else
			return 0;*/
}
// End of RunShortcut
