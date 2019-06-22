#define _WIN32_WINNT 0x0500

#include "stdafx.h"

#include "IconButton.h"
#include "..\Slave\Exceptions.h"
#include "..\Slave\Messages.h"


#include "shlobj.h"
#include "Shellapi.h"
#include <string>
#include "Windowsx.h"
#include "Windows.h"
#include "Winuser.h"



const char cClassName[50] = "Icon Button Class";


LRESULT CALLBACK IconButtonWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CIconButton* pIconButton = (CIconButton*)GetWindowLong(hWnd, GWL_USERDATA);;
	WNDCLASS wc;
	GetClassInfo(0, "BUTTON", &wc);

		switch (uMsg)
		{
			case WM_MOUSEMOVE:
					if (pIconButton)
					{
						wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
						pIconButton->OnMouseMove(wParam, lParam);
						return true;
					}
					else
						return wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
			break;

			case WM_MOUSELEAVE:
					if (pIconButton)
					{
						wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
						pIconButton->OnMouseLeave();
						return true;
					}
					else
						return wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
			break;

			case WM_LBUTTONUP:
					if (pIconButton)
					{
						wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
						pIconButton->OnLButtonUp(wParam, lParam);
						return true;
					}
					else
						return wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
			break;

			default:
				return wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
		 }

  return 0;
}
// End of WindowProcedure







CIconButton::CIconButton()
{
	m_hWnd = 0;
	m_hIcon = 0;
	m_bPushed = 0;
	m_pPreliminaryInfo = 0;;
}
// End of CIconButton()


CIconButton::~CIconButton()
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_CANCEL | TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	TrackMouseEvent(&tme);

	DoDeleteEverything();
}
// End of ~CIconButton()


void CIconButton::DoDeleteEverything()
{
		if (m_hIcon)
		{
			DestroyIcon(m_hIcon);
			m_hIcon = 0;
		}
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = 0;
		}
		if (m_pPreliminaryInfo)
		{
			delete m_pPreliminaryInfo;
			m_pPreliminaryInfo = 0;
		}
}
// End of DoDeleteEverything()


void CIconButton::CreateIconButton(HWND a_hParent, UINT a_uiX, UINT a_uiY, HINSTANCE a_hInst)
{
	WNDCLASS wc;
		if (!GetClassInfo(a_hInst, &(cClassName[0]), &wc))
			DoInitialization();

		if (m_hIcon)
		{
			DestroyIcon(m_hIcon);
			m_hIcon = 0;
		}
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = 0;
		}

	//m_ShortcutInfo.ResolveShortcut(0);

	UINT uiIconsNumber = 0;
	UINT uiResult = 0;

		if (m_ShortcutInfo.GetIconPath()[0])
		{
			m_hIcon = ExtractIcon(0, &(m_ShortcutInfo.GetIconPath()[0]), m_ShortcutInfo.GetIcon());
		}
		else
		{
			m_hIcon = ExtractIcon(0, &(m_ShortcutInfo.GetTargetPath()[0]), 0);
		}


	UINT uiButtonHeight = 0, uiButtonWidth = 0;
	uiButtonWidth = GetSystemMetrics(SM_CXICON) + (GetSystemMetrics(SM_CXEDGE)) * 2;
	uiButtonHeight = GetSystemMetrics(SM_CYICON) + (GetSystemMetrics(SM_CYEDGE)) * 2;


	m_hWnd = CreateWindowEx(
				0,
				&(cClassName[0]),//"Button",
				"",
				WS_VISIBLE | WS_CHILD | BS_ICON,
				a_uiX, a_uiY, uiButtonWidth, uiButtonHeight,
				a_hParent,
				0,
				0,
				0);

	SetWindowLong(m_hWnd, GWL_USERDATA, (long)this);
	SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)m_hIcon);
}
// End of CreateIconButton


void CIconButton::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	// В Client coordinates
	signed short int siXPos = GET_X_LPARAM(lParam);
	signed short int siYPos = GET_Y_LPARAM(lParam);

	RECT Rect;
	// В Screen coonrdinates
	GetWindowRect(m_hWnd, &Rect);
	POINT LeftTop = {Rect.left, Rect.top};
	POINT RightBottom = {Rect.right, Rect.bottom};
	ScreenToClient(m_hWnd, &LeftTop);
	ScreenToClient(m_hWnd, &RightBottom);
	// Теперь тоже в Client coordinates
	Rect.left = LeftTop.x;
	Rect.top = LeftTop.y;
	Rect.right = RightBottom.x;
	Rect.bottom = RightBottom.y; 

		if ( (siXPos >= Rect.left) && (siXPos <= Rect.right) &&
					(siYPos >= Rect.top) && (siYPos <= Rect.bottom) )
		{
				if (SendMessage(m_hWnd, BM_GETSTATE, 0, 0) & BST_FOCUS)
					// Если LButtonUp - внутри окна кнопки и если кнопка нажата
					OnLButtonClicked();
		}
}
// End of OnLButtonUp


void CIconButton::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
		/*if (SendMessage(m_hWnd, BM_GETSTATE, 0, 0) & BST_PUSHED)
			// Если LButtonUp - внутри окна кнопки и если кнопка нажата
			OnLButtonClicked();*/
}
// End of OnLButtonUp


void CIconButton::OnLButtonClicked()
{
	PostThreadMessage(GetCurrentThreadId(), WM_ICON_BUTTON_CLICKED, (WPARAM)this, 0);
}
// End of OnLButtonClicked


void CIconButton::DoInitialization()
{
	WNDCLASS WndClass;
	GetClassInfo(0, "Button", &WndClass);

	WndClass.lpfnWndProc = IconButtonWindowProcedure;
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
			throw CAnyLogableException("An error occured in CIconButton::CreateIconButton: can't register window class 8-/", bDoNotWriteDuplicates);
}
// End of DoInitialization()


void CIconButton::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	/*TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hWnd;

	TrackMouseEvent(&tme);*/

	//SetWindowText(GetParent(m_hWnd), m_ShortcutInfo.GetShortLinkFileName().c_str());

	SendMessage(GetParent(m_hWnd), WM_STATUSBAR_TEXT_CHANGE, 0, (WPARAM)m_ShortcutInfo.GetShortLinkFileName().c_str());
	UpdateWindow(GetParent(m_hWnd));

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	tme.dwHoverTime = 0;
	TrackMouseEvent(&tme);
}
// End of OnMouseMove


void CIconButton::OnMouseLeave()
{
	SendMessage(GetParent(m_hWnd), WM_STATUSBAR_TEXT_CHANGE, 0, 0);
	UpdateWindow(GetParent(m_hWnd));
}
// End of OnMouseLeave()


void CIconButton::CreatePreliminaryShortcutInfo(CShortcutInfo* a_pFrom)
{
		try
		{
				if (!m_pPreliminaryInfo)
					m_pPreliminaryInfo = new CShortcutInfo;

			*m_pPreliminaryInfo = *a_pFrom;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CIconButton::CreatePreliminaryShortcutInfo", bDoNotWriteDuplicates);
		}
}
// End of CreatePreliminaryShortcutInfo
