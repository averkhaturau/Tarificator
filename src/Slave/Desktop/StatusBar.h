#ifndef __STATUSBAR_H__
#define __STATUSBAR_H__

#include "AboutButton.h"
#include "SmallPictureDescription.h"



// Класс статусной строки. Юзается в CDesktopEmulator.
class CSlaveStatusBar
{
	private:
		void DoDeleteEverything();
	protected:
		void OnResize();

		void DoCreateWnd(HWND& a_hWnd, LPCTSTR a_pName);

		HWND m_hWindow;
		HWND m_hServerTimeCaption;
		HWND m_hIntervalCaption;
		HWND m_hRemainingCaption;
		HWND m_hServerTimeText;
		HWND m_hIntervalText;
		HWND m_hRemainingText;

		HWND m_hGroupWindow;

		HBRUSH m_hBackground;

		CAboutButton* m_pAboutButton;

		HINSTANCE m_hInst;

		friend LRESULT CALLBACK StatusWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	public:
		CSlaveStatusBar(HINSTANCE a_hInst);
		~CSlaveStatusBar();

		void CreateWnd(DWORD a_dwExStyle, LPCTSTR a_lpWindowName,
					DWORD a_dwStyle, HWND a_hWndParent);

		// Обертки
		HWND GetWindow() {return m_hWindow;};
		HWND GetServerTimeTextWnd() {return m_hServerTimeText;};
		HWND GetIntervalTextWnd() {return m_hIntervalText;};
		HWND GetRemainingTextWnd() {return m_hRemainingText;};
		HBRUSH GetBackgroundBrush() {return m_hBackground;};
};

#endif // __STATUSBAR_H__