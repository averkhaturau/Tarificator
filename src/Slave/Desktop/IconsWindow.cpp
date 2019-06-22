#include "stdafx.h"

#include "IconsWindow.h"
#include "..\Slave\Messages.h"



LRESULT CALLBACK IconWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CIconsWindow* pIconsWindow = (CIconsWindow*)GetWindowLong(hWnd, GWL_USERDATA);

	WNDPROC pfProc = DefWindowProc;
	//WNDCLASS wc;
	//GetClassInfo(0, "Static"/*"SysListView32"*/, &wc);

		switch (uMsg)
		{
			case WM_CLOSE:

			break;
			case WM_SIZE:
				pfProc(hWnd, uMsg, wParam, lParam);
					if (pIconsWindow)
						pIconsWindow->OnResize();
			break;
			case WM_ACTIVATE:
				pfProc(hWnd, uMsg, wParam, lParam);
					/*if (pIconsWindow)
					{
						pIconsWindow->m_bIsActivatingNow = true;
					}*/
					if ( (LOWORD(wParam) == WA_ACTIVE) )
					{
						PostThreadMessage(GetCurrentThreadId(), WM_ACTIVATED, (WPARAM)hWnd, 0);
					}

					/*if ( wParam )
					{
						PostThreadMessage(GetCurrentThreadId(), WM_ACTIVATED, (WPARAM)hWnd, 0);
					}*/

					/*if ( (LOWORD(wParam) == WA_ACTIVE) || (LOWORD(wParam) == WA_CLICKACTIVE) )
					{
						PostThreadMessage(GetCurrentThreadId(), WM_ACTIVATED, (WPARAM)hWnd, 0);
					}*/
			break;
			case WM_STATUSBAR_TEXT_CHANGE:
				/*GetWindowText(hWnd, &(cBuffer[0]), MAX_PATH);
					if (strcmp(&(cBuffer[0]), (LPCTSTR)lParam))
						InvalidateRect(hWnd, 0, true);*/

					if (pIconsWindow)
						SetWindowText(pIconsWindow->m_hNameWindow, (LPCSTR)lParam);

				return pfProc(hWnd, uMsg, wParam, lParam);
			break;
			case WM_ERASEBKGND:
				HDC hDC;
				hDC = (HDC)wParam;

				RECT WindowRect;
				GetClientRect(hWnd, &WindowRect);

					if (pIconsWindow)
						FillRect(hDC, &WindowRect, pIconsWindow->GetBackgroundBrush());
			break;

			default:
				return pfProc(hWnd, uMsg, wParam, lParam);
		 }

  return 0;
}
// End of IconWindowProcedure



CIconsWindow::CIconsWindow(HINSTANCE a_hInst)
{
	m_dwXIcons = 0;
	m_dwYIcons = 0;

	m_hNameWindow = 0;
	m_hIconsWindow = 0;

	m_sIconsFolderPath = "";
	//m_bIsActivatingNow = 0;

	m_hBackground = 0;

		try
		{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbHatch = 0;
			lb.lbColor = GetSysColor(COLOR_WINDOW);

			m_hBackground = CreateBrushIndirect(&lb);

			WNDCLASS WndClass;
				if (!GetClassInfo(a_hInst, &(cIconsWindowClassName[0]), &WndClass))
				{
					GetClassInfo(0, "Static"/*"SysListView32"*/, &WndClass);

					WndClass.lpfnWndProc = IconWindowProcedure;
					/*WndClass.style = 0;
					WndClass.cbClsExtra = 0;
					WndClass.cbWndExtra = 0;
					WndClass.hInstance = 0;
					WndClass.hIcon = NULL;
					WndClass.hCursor = NULL;
					WndClass.hbrBackground = NULL;
					WndClass.lpszMenuName = NULL;*/
					WndClass.lpszClassName = &(cIconsWindowClassName[0]);

					ATOM _ClassAtom;
					_ClassAtom = RegisterClass(&WndClass);

						if (!_ClassAtom)
							throw CAnyLogableException("An error occured in CIconsWindow::CIconsWindow: can't register window class 8-/", bDoNotWriteDuplicates);
				}
		}
		catch(CAnyLogableException)
		{
			throw;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CSlaveStatusBar::CSlaveStatusBar", bDoNotWriteDuplicates);
		}
}
// End of CIconsWindow()


CIconsWindow::~CIconsWindow()
{
	DoDeleteEverything();
}
// End of ~CIconsWindow()


void CIconsWindow::DoDeleteEverything()
{
	m_ButtonsCollection.resize(0);

		if (m_hNameWindow)
		{
			DestroyWindow(m_hNameWindow);
			m_hNameWindow = 0;
		}
		if (m_hIconsWindow)
		{
			DestroyWindow(m_hIconsWindow);
			m_hIconsWindow = 0;
		}
		if (m_hBackground)
		{
			DeleteObject(m_hBackground);
			m_hBackground = 0;
		}
}
// End of DoDeleteEverything()


DWORD CIconsWindow::GetIconButtonXCoord(DWORD dwXPos)
{
	return dwXPos * (2 * GetSystemMetrics(SM_CXEDGE) +
				GetSystemMetrics(SM_CXICON) + 5) + 5;
}
// End of GetIconButtonXCoord


DWORD CIconsWindow::GetIconButtonYCoord(DWORD dwYPos)
{
	return dwYPos * (2 * GetSystemMetrics(SM_CYEDGE) +
				GetSystemMetrics(SM_CYICON) + 5) + 5;
}
// End of GetIconButtonYCoord


void CIconsWindow::CreateAllButtons(HINSTANCE a_hInst)
{
	UINT uiXNumber = 0, uiYNumber = 0;
	CIconButtonsCollection::iterator Iter = m_ButtonsCollection.GetData()->begin(), EndIter = m_ButtonsCollection.GetData()->end();
		for (; Iter < EndIter; ++Iter)
		{
			(**Iter).CreateIconButton(m_hIconsWindow,
						GetIconButtonXCoord(uiXNumber),
						GetIconButtonYCoord(uiYNumber), a_hInst);

				if (uiXNumber < m_dwXIcons - 1)
					++uiXNumber;
				else
				{
					uiXNumber = 0;
					++uiYNumber;
				}
		}
}
// End of CreateAllButtons()


void CIconsWindow::CreateWnd(DWORD a_dwExStyle, LPCTSTR a_lpWindowName,
			DWORD a_dwStyle, HWND a_hWndParent)
{
		try
		{
			m_hIconsWindow = CreateWindowEx(
						a_dwExStyle,
						&(cIconsWindowClassName[0]),
						a_lpWindowName,
						a_dwStyle | SS_WHITERECT,
						0,
						0,
						0,
						0,
						a_hWndParent,
						0,
						0,
						0);
		}
		catch(...)
		{
			/*std::string Buffer;
			Buffer.resize(0xff);
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						NULL, Buffer.begin(), 0xfe, NULL);*/
		}

	SetWindowLong(m_hIconsWindow, GWL_USERDATA, (long)this);

		if (m_hIconsWindow)
		{
			m_hNameWindow = CreateWindowEx(
						WS_EX_CLIENTEDGE | WS_EX_TOOLWINDOW,
						"Static",
						"",
						WS_VISIBLE | WS_CHILD | SS_CENTER | SS_NOPREFIX,
						100, 100, 100, 100,
						m_hIconsWindow,
						0,
						0,
						0);
		}
}
// End of CreateWnd()


void CIconsWindow::OnResize()
{
	RECT NameRect, IconsRect;
	GetClientRect(m_hIconsWindow, &IconsRect);

	UINT uiIconsWindowHeight = 0, uiIconsWindowWidth = 0;
	uiIconsWindowHeight = IconsRect.bottom - IconsRect.top;
	uiIconsWindowWidth = IconsRect.right - IconsRect.left;

	UINT uiIconsWindowX = 0, uiIconsWindowY = 0;
	uiIconsWindowX = IconsRect.left;
	uiIconsWindowY = IconsRect.top;


	UINT uiNameWindowHeight = 0, uiNameWindowWidth = 0, uiNameWindowX = 0, uiNameWindowY = 0;
	uiNameWindowWidth = uiIconsWindowWidth;
	uiNameWindowHeight = GetIconButtonYCoord(GetYIcons() + 1) - GetIconButtonYCoord(GetYIcons());
	uiNameWindowX = 0;
	uiNameWindowY = GetIconButtonYCoord(GetYIcons());

		if ( (NameRect.top != uiNameWindowY) ||
					(NameRect.bottom != uiNameWindowY + uiNameWindowHeight) ||
					(NameRect.left != uiNameWindowX) ||
					(NameRect.right != uiNameWindowX + uiNameWindowWidth) )
		{
			SetWindowPos(
						m_hNameWindow,
						0,
						uiNameWindowX,
						uiNameWindowY,
						uiNameWindowWidth,
						uiNameWindowHeight,
						SWP_NOZORDER);
		}
}
// End of OnResize()
