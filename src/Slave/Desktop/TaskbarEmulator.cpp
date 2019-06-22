#include "stdafx.h"

#include "TaskbarEmulator.h"
#include "..\Slave\Exceptions.h"
#include "TaskButtonsCollection.h"

#include <math.h>





BOOL CALLBACK FindAppWindowProc(HWND hwnd, LPARAM lParam)
{
	CTaskbarEmulator* pEmulator = (CTaskbarEmulator*)lParam;

	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	DWORD dwExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

	HWND hOwner = 0;

		if (dwStyle & WS_VISIBLE)
		{
				if (!(dwExStyle & WS_EX_TOOLWINDOW))
				{
					hOwner = GetWindow(hwnd, GW_OWNER);
						if ( (dwExStyle & WS_EX_APPWINDOW) || (hOwner == 0) )
						{
								if (pEmulator)
									pEmulator->OnAppWindowFound(hwnd);
						}
				}
		}

	return true;
}
// End of FindAppWindowProc


LRESULT CALLBACK TaskbarWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//WNDCLASS wc;
	//GetClassInfo(0, /*"SysListView32"*/"Static", &wc);
	CTaskbarEmulator* pEmulator = (CTaskbarEmulator*)GetWindowLong(hWnd, GWL_USERDATA);

	WNDPROC pfProc = DefWindowProc;

		switch (uMsg)
		{
			case WM_CLOSE:

			break;

			case WM_ERASEBKGND:
				HDC hDC;
				hDC = (HDC)wParam;

				RECT WindowRect;
				GetClientRect(hWnd, &WindowRect);

					if (pEmulator)
						FillRect(hDC, &WindowRect, pEmulator->GetBackgroundBrush());
			break;

			default:
				return pfProc(hWnd, uMsg, wParam, lParam);
		 }

  return 0;
}
// End of TaskbarWindowProcedure







const char cClassName[50] = "Taskbar Window's Class";

CTaskbarEmulator::CTaskbarEmulator(HINSTANCE a_hInst)
{
	m_hWnd = 0;
	m_bWasNotFound = 0;
	m_pButtonsCollection = 0;
	m_bEnumerating = false;

	m_hInst = a_hInst;

		try
		{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbHatch = 0;
			lb.lbColor = GetSysColor(COLOR_WINDOW);

			m_hBackground = CreateBrushIndirect(&lb);

			WNDCLASS WndClass;
				if (!GetClassInfo(a_hInst, &(cClassName[0]), &WndClass))
				{
					GetClassInfo(0, /*"SysListView32"*/"Static", &WndClass);

					WndClass.lpfnWndProc = TaskbarWindowProcedure;
					WndClass.lpszClassName = &(cClassName[0]);

					ATOM _ClassAtom;
					_ClassAtom = RegisterClass(&WndClass);

						if (!_ClassAtom)
							throw CAnyLogableException("An error occured in CTaskbarEmulator::CTaskbarEmulator: can't register window class 8-/", bDoNotWriteDuplicates);
				}

			m_pButtonsCollection = new CTaskButtonsCollection();
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknow error occured in CTaskbarEmulator::CTaskbarEmulator()", bDoNotWriteDuplicates);
		}
}
// ENd of CTaskbarEmulator()


CTaskbarEmulator::~CTaskbarEmulator()
{
	DoDeleteEverything();
}
// End of ~CTaskbarEmulator()


void CTaskbarEmulator::DoDeleteEverything()
{
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = 0;
		}
		if (m_pButtonsCollection)
		{
			delete m_pButtonsCollection;
			m_pButtonsCollection = 0;
		}
		if (m_hBackground)
		{
			DeleteObject(m_hBackground);
			m_hBackground = 0;
		}
}
// End of DoDeleteEverything()


void CTaskbarEmulator::CreateWnd(HINSTANCE a_hInst)
{
		try
		{
				if (!m_hWnd)
				{
					HWND hTaskbarWindow = FindWindow("Shell_traywnd", "");
					RECT BarRect = {0, 0, 0, 0};
						if (hTaskbarWindow)
							GetWindowRect(hTaskbarWindow, &BarRect);

					m_hWnd = CreateWindowEx(
								WS_EX_TOOLWINDOW,
								&(cClassName[0]),
								"Taskbar Emulation",
								WS_VISIBLE | WS_POPUP | WS_DLGFRAME | SS_WHITERECT,
								BarRect.left, BarRect.top, BarRect.right - BarRect.left, BarRect.bottom - BarRect.top,
								GetDesktopWindow(),
								0, 0, 0);
					SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
				}
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CTaskbarEmulator::CreateWnd()", bDoNotWriteDuplicates);
		}
}
// End of CreateWnd()


void CTaskbarEmulator::OnTimer()
{
	CTaskButtonsCollection::iterator Iter = m_pButtonsCollection->GetData()->begin(),
				EndIter = m_pButtonsCollection->GetData()->end();
		for (; Iter < EndIter; ++Iter)
		{
			(*Iter)->SetWasFound(false);
		}

	m_bWasNotFound = 0;
	m_bEnumerating = true;
	EnumWindows(FindAppWindowProc, (LPARAM)this);
	m_bEnumerating = false;

	bool bTooManyButtons = 0;

	Iter = m_pButtonsCollection->GetData()->begin();
	EndIter = m_pButtonsCollection->GetData()->end();
		for (; Iter < EndIter; ++Iter)
		{
			bTooManyButtons |= !((*Iter)->GetWasFound());
		}

		if ( bTooManyButtons || m_bWasNotFound )
		{
			ReCreateButtons();
		}
}
// End of OnTimer()


void CTaskbarEmulator::OnAppWindowFound(HWND a_hWnd)
{
	char cFirstBuffer[1024];

		if (m_bEnumerating)
		{
			bool bWasNotFound = true;

			CTaskButtonsCollection::iterator Iter = m_pButtonsCollection->GetData()->begin(),
						EndIter = m_pButtonsCollection->GetData()->end();
				for (; Iter < EndIter; ++Iter)
				{
						if ((*Iter)->GetWnd())
						{
							//GetWindowText((*Iter)->GetWnd(), &(cSecondBuffer[0]), 1020);
							GetWindowText(a_hWnd, &(cFirstBuffer[0]), 1020);
								if ( !strcmp(cFirstBuffer, (*Iter)->GetAppName()->c_str()) )
								{
									DWORD dwProcessId;
									GetWindowThreadProcessId(a_hWnd, &dwProcessId);
										if (dwProcessId == (*Iter)->GetProcessId())
										{
											(*Iter)->SetWasFound(true);
											bWasNotFound = false;
										}
								}
						}
				}

			m_bWasNotFound |= bWasNotFound;
		}
		else
		{
			m_pButtonsCollection->resize(m_pButtonsCollection->size() + 1);

			(*m_pButtonsCollection)[m_pButtonsCollection->size() - 1].CreateWnd(m_hWnd, m_hInst);

			DWORD dwProcessId;
			GetWindowThreadProcessId(a_hWnd, &dwProcessId);

			GetWindowText(a_hWnd, &(cFirstBuffer[0]), 1020);
			(*m_pButtonsCollection)[m_pButtonsCollection->size() - 1].SetAppWnd(a_hWnd);
			(*(*m_pButtonsCollection)[m_pButtonsCollection->size() - 1].GetAppName()) = cFirstBuffer;
			(*m_pButtonsCollection)[m_pButtonsCollection->size() - 1].SetProcessId(dwProcessId);
			//SetWindowText((*m_pButtonsCollection)[m_pButtonsCollection->size() - 1].GetWnd(), &(cFirstBuffer[0]));
		}
}
// End of OnAppWindowFound


void CTaskbarEmulator::ReCreateButtons()
{
	m_bEnumerating = false;

	m_pButtonsCollection->resize(0);

	EnumWindows(FindAppWindowProc, (LPARAM)this);

	RePosButtons();
}
// End of ReCreateButtons()


void CTaskbarEmulator::RePosButtons()
{
	RECT Rect;
	DWORD dwXNumber = 0;
	CTaskButtonsCollection::iterator Iter = m_pButtonsCollection->GetData()->begin(),
				EndIter = m_pButtonsCollection->GetData()->end();
		for (; Iter < EndIter; ++Iter, ++dwXNumber)
		{
			GetPos(dwXNumber, &Rect);
			SetWindowPos(
						(*Iter)->GetWnd(),
						0,
						Rect.left,
						Rect.top,
						Rect.right - Rect.left,
						Rect.bottom - Rect.top,
						SWP_NOZORDER);
		}
}
// End of RePosButtons()


void CTaskbarEmulator::GetPos(DWORD a_dwXNumber, RECT* a_pRect)
{
	RECT Rect;
	GetWindowRect(m_hWnd, &Rect);

	a_pRect->left = GetSystemMetrics(SM_CXDLGFRAME) + ceil( (float)(a_dwXNumber * (Rect.right - Rect.left - 4 * GetSystemMetrics(SM_CXEDGE))) / (float)m_pButtonsCollection->size() );
	a_pRect->top = GetSystemMetrics(SM_CYEDGE);
	a_pRect->right = ceil( (float)((a_dwXNumber + 1) * (Rect.right - Rect.left - 4 * GetSystemMetrics(SM_CXEDGE))) / (float)m_pButtonsCollection->size() );
	a_pRect->bottom = a_pRect->top + Rect.bottom - Rect.top - 1 * GetSystemMetrics(SM_CYDLGFRAME) - 3 * GetSystemMetrics(SM_CYEDGE);
}
// End of GetPos()
