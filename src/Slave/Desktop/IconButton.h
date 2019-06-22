#ifndef __ICONBUTTON_H__
#define __ICONBUTTON_H__

#include "ShortcutInfo.h"


#define WM_STATUSBAR_TEXT_CHANGE WM_USER+1


class CIconButton
{
	private:
		void DoDeleteEverything();
	protected:
		// Должен вызываться только 1 раз!
		void DoInitialization();
		void OnLButtonUp(WPARAM wParam, LPARAM lParam);
		void OnLButtonDown(WPARAM wParam, LPARAM lParam);
		// Вызывается только если клик был НА кнопке
		void OnLButtonClicked();
		void OnMouseMove(WPARAM wParam, LPARAM lParam);
		void OnMouseLeave();

		bool m_bPushed;

		CShortcutInfo m_ShortcutInfo;
		CShortcutInfo* m_pPreliminaryInfo;

		HICON m_hIcon;
		HWND m_hWnd;

		friend LRESULT CALLBACK IconButtonWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	public:
		CIconButton();
		~CIconButton();

		// a_hInst - HANDLE of current instance of the application
		void CreateIconButton(HWND a_hParent, UINT a_uiX, UINT a_uiY, HINSTANCE a_hInst);
		void CreatePreliminaryShortcutInfo(CShortcutInfo* a_pFrom);

		// Обертки
		CShortcutInfo* GetShortcutInfo() {return &m_ShortcutInfo;};
		CShortcutInfo* GetPreliminaryShortcutInfo() {return m_pPreliminaryInfo;};
		HWND GetWindow() {return m_hWnd;};
};


#endif // __ICONBUTTON_H__