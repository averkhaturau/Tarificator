#ifndef __ABOUTBUTTON_H__
#define __ABOUTBUTTON_H__


#include "AboutDialog.h"

class CAboutButton
{
	private:
		void DoDeleteEverything();
	protected:
		HWND m_hWnd;
		HINSTANCE m_hInst;
		HBITMAP m_hBitmap;

		CAboutDialog* m_pAboutDialog;

		void OnLButtonUp(WPARAM wParam, LPARAM lParam);

		friend LRESULT CALLBACK AboutButtonWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	public:
		CAboutButton(HINSTANCE a_hInst);
		~CAboutButton();

		// Создает окно и грузат икону
		void CreateWnd(HWND a_hParent);

		// Обертки
		HWND GetWnd() {return m_hWnd;};
};


#endif // __ABOUTBUTTON_H__