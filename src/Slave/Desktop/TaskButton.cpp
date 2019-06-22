#include "stdafx.h"

#include "TaskButton.h"
#include "..\Slave\Exceptions.h"

#include "Windowsx.h"





LRESULT CALLBACK TaskButtonWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CTaskButton* pButton = (CTaskButton*)GetWindowLong(hWnd, GWL_USERDATA);

	WNDCLASS wc;
	GetClassInfo(0, /*"Static"*/"Button", &wc);

		switch (uMsg)
		{
			case WM_CLOSE:

			break;

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

			case WM_ERASEBKGND:
					if (pButton)
					{
						pButton->OnPaint((HDC)wParam);
					}
			break;

			default:
				return wc.lpfnWndProc(hWnd, uMsg, wParam, lParam);
		 }

  return 0;
}
// End of TaskButtonWindowProcedure






const char cClassName[50] = "Task Button Window's Class";


CTaskButton::CTaskButton()
{
	m_hWnd = 0;
	m_hAppWnd = 0;
	m_bWasFound = 0;
	m_AppName = "";
	m_dwWindowTextSetForWidth = 0;
	m_dwProcessId = 0;
}
// End of CTaskButton()


CTaskButton::~CTaskButton()
{
	DoDeleteEverything();
}
// End of ~CTaskButton()


void CTaskButton::DoDeleteEverything()
{
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = 0;
		}
}
// End of DoDeleteEverything()


void CTaskButton::CreateWnd(HWND a_hParent, HINSTANCE a_hInst)
{
		try
		{
			WNDCLASS WndClass;
				if (!GetClassInfo(a_hInst, &(cClassName[0]), &WndClass))
				{
					GetClassInfo(0, "Button"/*"Static"*/, &WndClass);

					WndClass.lpfnWndProc = TaskButtonWindowProcedure;
					WndClass.lpszClassName = &(cClassName[0]);

					ATOM _ClassAtom;
					_ClassAtom = RegisterClass(&WndClass);

						if (!_ClassAtom)
							throw CAnyLogableException("An error occured in CTaskButton::CreateWnd: can't register window class 8-/", bDoNotWriteDuplicates);
				}

				if (!m_hWnd)
				{
					m_hWnd = CreateWindowEx(
								0,
								&(cClassName[0]),
								"",
								WS_VISIBLE | WS_CHILD,
								0, 0, 0, 0,
								a_hParent,
								0, 0, 0);
					SetWindowLong(m_hWnd, GWL_USERDATA, (long)this);
				}
		}
		catch(CAnyLogableException)
		{
			throw;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CTaskButton::CreateWnd()", bDoNotWriteDuplicates);
		}
}
// End of CreateWnd()


void CTaskButton::OnPaint(HDC a_hDC)
{
		if ( (a_hDC) && (m_hWnd) )
		{
			RECT Rect;
			GetWindowRect(m_hWnd, &Rect);
				if ( Rect.right - Rect.left != m_dwWindowTextSetForWidth )
				{
					RECT TextRect = {0, 0, 0, 0};
					TextRect.bottom = Rect.bottom - Rect.top;
					TextRect.right = Rect.right - Rect.left;
					char cBuffer[1024];
					memcpy(&(cBuffer[0]), m_AppName.c_str(), strlen(m_AppName.c_str()) + 1);

					DrawText(a_hDC, cBuffer, strlen(cBuffer), &TextRect, DT_CALCRECT | DT_SINGLELINE);

					DWORD dwTextLength = strlen(m_AppName.c_str());
					signed long int i = dwTextLength - 3;
						for (;(i >= 0) && (TextRect.right - TextRect.left >
									Rect.right - Rect.left - 2 * GetSystemMetrics(SM_CXEDGE)); --i)
						{
							cBuffer[i] = '.';
							cBuffer[i + 1] = '.';
							cBuffer[i + 2] = '.';
							cBuffer[i + 3] = '\0';

							DrawText(a_hDC, cBuffer, strlen(cBuffer), &TextRect, DT_CALCRECT | DT_SINGLELINE);
						}

					SetWindowText(m_hWnd, cBuffer);
					m_dwWindowTextSetForWidth = Rect.right - Rect.left;
				}
		}
}
// End of OnPaint()


void CTaskButton::OnLButtonUp(WPARAM wParam, LPARAM lParam)
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
						if (m_hAppWnd)
						{
							HWND hWasActive = SetActiveWindow(m_hAppWnd);
								if (hWasActive)
								{
									SendMessage(hWasActive, WM_ACTIVATEAPP, FALSE, 0);
									//PostMessage(hWasActive, WM_ACTIVATE, WA_INACTIVE, (long)m_hAppWnd);
								}

							WINDOWPLACEMENT wp;
							wp.length = sizeof(WINDOWPLACEMENT);
							GetWindowPlacement(m_hAppWnd, &wp);
								if ( (!(wp.showCmd == SW_SHOWMAXIMIZED)) &&
											(!(wp.showCmd == SW_RESTORE)) )
								{
									SendMessage(m_hAppWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
								}

							SetWindowPos(m_hAppWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						}
				}
		}
}
// End of OnLButtonUp
