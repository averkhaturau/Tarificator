#include "stdafx.h"

#include "AboutButton.h"
#include "ClubDefiner.h"
#include "..\Slave\Exceptions.h"
#include "..\Slave\Messages.h"

#include "Windowsx.h"




const char cClassName[50] = "AboutButton Class";


LRESULT CALLBACK AboutButtonWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CAboutButton* pButton = (CAboutButton*)GetWindowLong(hWnd, GWL_USERDATA);;
	WNDCLASS wc;
	GetClassInfo(0, "BUTTON", &wc);

	switch (uMsg)
	{
		case WM_LBUTTONUP:
				if (pButton)
				{
					wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
					pButton->OnLButtonUp(wParam, lParam);
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
// End of AboutButtonWindowProcedure






CAboutButton::CAboutButton(HINSTANCE a_hInst)
{
	m_hWnd = 0;
	m_hInst = a_hInst;
	m_hBitmap = 0;
	m_pAboutDialog = 0;

		try
		{
			m_pAboutDialog = new CAboutDialog(m_hInst);

			WNDCLASS wc;
				if (!GetClassInfo(a_hInst, &(cClassName[0]), &wc))
				{
					WNDCLASS WndClass;
					GetClassInfo(0, "Button", &WndClass);

					WndClass.lpfnWndProc = AboutButtonWindowProcedure;
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
		}
		catch(CAnyLogableException& Error)
		{
			std::string Str = "An error occured in CAboutButton::CAboutButton: ";
			Str += Error.what();
			throw CAnyLogableException(Str.c_str(), bDoNotWriteDuplicates);
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CAboutButton::CAboutButton", bDoNotWriteDuplicates);
		}
}
// End of CAboutButton()


CAboutButton::~CAboutButton()
{
	DoDeleteEverything();
}
// ENd of ~CAboutButton()


void CAboutButton::DoDeleteEverything()
{
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = 0;
		}
		if (m_hBitmap)
		{
			DeleteObject(m_hBitmap);
			m_hBitmap = 0;
		}
		if (m_pAboutDialog)
		{
			delete m_pAboutDialog;
			m_pAboutDialog = 0;
		}
}
// End of DoDeleteEverything()


void CAboutButton::CreateWnd(HWND a_hParent)
{
		if (!m_hWnd)
		{
			m_hWnd = CreateWindowEx(
						0,
						&(cClassName[0]),
						"",
						WS_VISIBLE | WS_CHILD | BS_BITMAP,
						0, 0, 0, 0,
						a_hParent,
						0, 0, 0);
		}
	SetWindowLong(m_hWnd, GWL_USERDATA, (long)this);

		if (!m_hBitmap)
			m_hBitmap = LoadBitmap(m_hInst, SMALL_BITMAP);
		if (m_hBitmap)
			SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (long)m_hBitmap);
}
// End of CreateWnd


void CAboutButton::OnLButtonUp(WPARAM wParam, LPARAM lParam)
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
				{
					// Если LButtonUp - внутри окна кнопки и если кнопка нажата
						if (m_pAboutDialog)
						{
								if (!m_pAboutDialog->GetWnd())
								{
									m_pAboutDialog->CreateWnd(m_hWnd);
								}
						}
				}
		}
}
// End of OnLButtonUp
