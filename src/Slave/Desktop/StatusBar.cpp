#include "stdafx.h"

#include "StatusBar.h"
#include "..\Slave\Exceptions.h"
#include <math.h>



const char cClassName[50] = "Desktop Emulator Status Bar Window's Class";

LRESULT CALLBACK StatusWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CSlaveStatusBar* pStatusBar = (CSlaveStatusBar*)GetWindowLong(hWnd, GWL_USERDATA);

	WNDPROC pfProc = DefWindowProc;
	//WNDCLASS wc;
	//GetClassInfo(0, "Static"/*"SysListView32"*/, &wc);

	switch (uMsg)
	{
		case WM_CLOSE:

		break;
		case WM_SIZE:
			pfProc(hWnd, uMsg, wParam, lParam);
				if (pStatusBar)
					pStatusBar->OnResize();
		break;
		case WM_ERASEBKGND:
			HDC hDC;
			hDC = (HDC)wParam;

			RECT WindowRect;
			GetClientRect(hWnd, &WindowRect);

				if (pStatusBar)
					FillRect(hDC, &WindowRect, pStatusBar->GetBackgroundBrush());
		break;

		default:
			return pfProc(hWnd, uMsg, wParam, lParam);
   }

  return 0;
}
// End of StatusWindowProcedure




CSlaveStatusBar::CSlaveStatusBar(HINSTANCE a_hInst)
{
	m_hWindow = 0;

	m_hServerTimeCaption = 0;
	m_hIntervalCaption = 0;
	m_hRemainingCaption = 0;
	m_hServerTimeText = 0;
	m_hIntervalText = 0;
	m_hRemainingText = 0;

	m_hGroupWindow = 0;

	m_hInst = a_hInst;

	m_pAboutButton = 0;

	m_hBackground = 0;

		try
		{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbHatch = 0;
			lb.lbColor = GetSysColor(COLOR_WINDOW);

			m_hBackground = CreateBrushIndirect(&lb);

			m_pAboutButton = new CAboutButton(m_hInst);

			WNDCLASS WndClass;
				if (!GetClassInfo(a_hInst, &(cClassName[0]), &WndClass))
				{
					GetClassInfo(0, /*"SysListView32"*/"Static", &WndClass);

					WndClass.lpfnWndProc = StatusWindowProcedure;
					/*WndClass.style = 0;
					WndClass.cbClsExtra = 0;
					WndClass.cbWndExtra = 0;
					WndClass.hInstance = 0;
					WndClass.hIcon = NULL;
					WndClass.hCursor = NULL;
					WndClass.hbrBackground = NULL;
					WndClass.lpszMenuName = NULL;*/
					WndClass.lpszClassName = &(cClassName[0]);

					ATOM _ClassAtom;
					_ClassAtom = RegisterClass(&WndClass);

						if (!_ClassAtom)
							throw CAnyLogableException("An error occured in CSlaveStatusBar::CSlaveStatusBar: can't register window class 8-/", bDoNotWriteDuplicates);
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
// End of CSlaveStatusBar()


CSlaveStatusBar::~CSlaveStatusBar()
{
	DoDeleteEverything();
}
// End of ~CSlaveStatusBar()


void CSlaveStatusBar::DoDeleteEverything()
{
		if (m_pAboutButton)
		{
			delete m_pAboutButton;
			m_pAboutButton = 0;
		}

		if (m_hServerTimeCaption)
		{
			DestroyWindow(m_hServerTimeCaption);
			m_hServerTimeCaption = 0;
		}
		if (m_hIntervalCaption)
		{
			DestroyWindow(m_hIntervalCaption);
			m_hIntervalCaption = 0;
		}
		if (m_hRemainingCaption)
		{
			DestroyWindow(m_hRemainingCaption);
			m_hRemainingCaption = 0;
		}

		if (m_hServerTimeText)
		{
			DestroyWindow(m_hServerTimeText);
			m_hServerTimeText = 0;
		}
		if (m_hIntervalText)
		{
			DestroyWindow(m_hIntervalText);
			m_hIntervalText = 0;
		}
		if (m_hRemainingText)
		{
			DestroyWindow(m_hRemainingText);
			m_hRemainingText = 0;
		}

		if (m_hGroupWindow)
		{
			DestroyWindow(m_hGroupWindow);
			m_hGroupWindow = 0;
		}

		if (m_hWindow)
		{
			DestroyWindow(m_hWindow);
			m_hWindow = 0;
		}

		if (m_hBackground)
		{
			DeleteObject(m_hBackground);
			m_hBackground = 0;
		}
}
// End of DoDeleteEverything()


void CSlaveStatusBar::CreateWnd(DWORD a_dwExStyle, LPCTSTR a_lpWindowName,
			DWORD a_dwStyle, HWND a_hWndParent)
{
		try
		{
				if (!m_hWindow)
				{
					m_hWindow = CreateWindowEx(
								a_dwExStyle,
								&(cClassName[0]),
								a_lpWindowName,
								a_dwStyle | SS_WHITERECT,
								0, 0, 0, 0,
								a_hWndParent,
								0, 0, 0);
				}
			SetWindowLong(m_hWindow, GWL_USERDATA, (long)this);

				if (!m_hGroupWindow)
				{
					m_hGroupWindow = CreateWindowEx(
								WS_EX_CLIENTEDGE,
								"Static",
								"",
								WS_VISIBLE | WS_CHILD,
								0, 0, 0, 0,
								m_hWindow,
								0, 0, 0);
				}

			DoCreateWnd(m_hServerTimeCaption, "Время на сервере: ");
			DoCreateWnd(m_hIntervalCaption, "Интервал: ");
			DoCreateWnd(m_hRemainingCaption, "Осталось: ");

			DoCreateWnd(m_hServerTimeText, "");
			DoCreateWnd(m_hIntervalText, "");
			DoCreateWnd(m_hRemainingText, "");

			m_pAboutButton->CreateWnd(m_hWindow);
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CSlaveStatusBar::CreateWnd", bDoNotWriteDuplicates);
		}
}
// End of CreateWnd


void CSlaveStatusBar::OnResize()
{
	RECT ClientRect;
	GetClientRect(m_hWindow, &ClientRect);

	UINT uiGWX = 0, uiGWY = 0, 
				uiGWWidth = 350 + 2 * GetSystemMetrics(SM_CXEDGE),
				uiGWHeight = ClientRect.bottom - ClientRect.top;

	//UINT uiHeight = ceil( float(ClientRect.bottom - ClientRect.top) / 3 );
	UINT uiHeight = ceil( float(uiGWHeight - 2 * GetSystemMetrics(SM_CYEDGE)) / 3 );

	UINT uiSTCX = 10, uiSTCY = 0, uiSTCHeight = uiHeight, uiSTCWidth = 150;
	UINT uiICX = 10, uiICY = uiHeight, uiICHeight = uiHeight, uiICWidth = 150;
	UINT uiRTCX = 10, uiRTCY = 2 * uiHeight, uiRTCHeight = uiHeight, uiRTCWidth = 150;

	UINT uiSTTX = uiSTCX + uiSTCWidth, uiSTTY = 0, uiSTTHeight = uiHeight, uiSTTWidth = 200;
	UINT uiITX = uiICX + uiICWidth, uiITY = uiHeight, uiITHeight = uiHeight, uiITWidth = 200;
	UINT uiRTTX = uiRTCX + uiRTCWidth, uiRTTY = 2 * uiHeight, uiRTTHeight = uiHeight, uiRTTWidth = 200;

	UINT uiABHeight = uiSmallPictureHeight + 2 * GetSystemMetrics(SM_CYEDGE),
				uiABWidth = uiSmallPictureWidth + 2 * GetSystemMetrics(SM_CXEDGE),
				uiABX = ClientRect.right - ClientRect.left - uiABWidth - GetSystemMetrics(SM_CXEDGE),
				uiABY = GetSystemMetrics(SM_CYEDGE);

	SetWindowPos(m_hGroupWindow, m_hWindow, uiGWX, uiGWY, uiGWWidth, uiGWHeight, SWP_NOZORDER);

	SetWindowPos(m_hServerTimeCaption, m_hGroupWindow, uiSTCX, uiSTCY, uiSTCWidth, uiSTCHeight, SWP_NOZORDER);
	SetWindowPos(m_hIntervalCaption, m_hGroupWindow, uiICX, uiICY, uiICWidth, uiICHeight, SWP_NOZORDER);
	SetWindowPos(m_hRemainingCaption, m_hGroupWindow, uiRTCX, uiRTCY, uiRTCWidth, uiRTCHeight, SWP_NOZORDER);

	SetWindowPos(m_hServerTimeText, m_hGroupWindow, uiSTTX, uiSTTY, uiSTTWidth, uiSTTHeight, SWP_NOZORDER);
	SetWindowPos(m_hIntervalText, m_hGroupWindow, uiITX, uiITY, uiITWidth, uiITHeight, SWP_NOZORDER);
	SetWindowPos(m_hRemainingText, m_hGroupWindow, uiRTTX, uiRTTY, uiRTTWidth, uiRTTHeight, SWP_NOZORDER);

	SetWindowPos(m_pAboutButton->GetWnd(), m_hWindow, uiABX, uiABY, uiABWidth, uiABHeight, SWP_NOZORDER);
}
// End of OnResize()


void CSlaveStatusBar::DoCreateWnd(HWND& a_hWnd, LPCTSTR a_pName)
{
		if (!a_hWnd)
		{
			a_hWnd = CreateWindowEx(
				0,
				"Static",
				a_pName,
				WS_VISIBLE | WS_CHILD,
				0, 0, 0, 0,
				m_hGroupWindow,
				0, 0, 0);
		}
}
// End of DoCreateWnd
