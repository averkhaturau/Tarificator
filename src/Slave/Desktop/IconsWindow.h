#ifndef __ICONSWINDOW_H__
#define __ICONSWINDOW_H__

#include "IconButtonsCollection.h"
#include "..\Slave\Logger.h"


#define cIconsWindowClassName "Desktop Emulator Icon Window's Class"

class CIconsWindow
{
	private:
			void DoDeleteEverything();
	protected:
		// Тут производится resize окна с именами
		void OnResize();

		HWND m_hIconsWindow;
		HWND m_hNameWindow;
		HBRUSH m_hBackground;
		FileName m_sIconsFolderPath;
		CIconButtonsCollection m_ButtonsCollection;
		// Кол-во ярлыков по X и Y
		DWORD m_dwXIcons, m_dwYIcons;
		//bool m_bIsActivatingNow;

		friend LRESULT CALLBACK IconWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	public:
		CIconsWindow(HINSTANCE a_hInst);
		~CIconsWindow();

		void CreateAllButtons(HINSTANCE a_hInst);
		void CreateWnd(DWORD a_dwExStyle, LPCTSTR a_lpWindowName,
					DWORD a_dwStyle, HWND a_hWndParent);

		// Возвращает координату левого края в пикселах для кнопки с
		// иконой номер dwXPos. Нумерация с 0.
		DWORD GetIconButtonXCoord(DWORD dwXPos);
		// Возвращает координату верхнего края в пикселах для кнопки с
		// иконой номер dwYPos. Нумерация с 0.
		DWORD GetIconButtonYCoord(DWORD dwYPos);

		// Обертки
		void SetXIcons(DWORD a_dwNew) {m_dwXIcons = a_dwNew;};
		void SetYIcons(DWORD a_dwNew) {m_dwYIcons = a_dwNew;};
		DWORD GetXIcons() {return m_dwXIcons;};
		DWORD GetYIcons() {return m_dwYIcons;};
		FileName* GetIconsFolderPath() {return &m_sIconsFolderPath;};
		HWND GetIconsWindow() {return m_hIconsWindow;};
		HWND GetNameWindow() {return m_hIconsWindow;};
		HBRUSH GetBackgroundBrush() {return m_hBackground;};
		CIconButtonsCollection* GetButonsCollection() {return &m_ButtonsCollection;};
		/*bool GetIsActivatingNow() {return m_bIsActivatingNow;};
		void SetIsActivatingNow(bool a_bNew) {m_bIsActivatingNow = a_bNew;};*/
};

#endif // __ICONSWINDOW_H__