#ifndef __TASKBUTTON_H__
#define __TASKBUTTON_H__

#include <string>


class CTaskButton
{
	private:
		void DoDeleteEverything();
	protected:
		HWND m_hWnd;
		HWND m_hAppWnd;
		std::string m_AppName;
		DWORD m_dwProcessId;
		bool m_bWasFound;
		bool m_dwWindowTextSetForWidth;

		void OnPaint(HDC a_hDC);

		void OnLButtonUp(WPARAM wParam, LPARAM lParam);

		friend LRESULT CALLBACK TaskButtonWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	public:
		CTaskButton();
		~CTaskButton();

		void CreateWnd(HWND a_hParent, HINSTANCE a_hInst);

		// Обертки
		HWND GetWnd() {return m_hWnd;};
		bool GetWasFound() {return m_bWasFound;};
		void SetWasFound(bool a_bNew) {m_bWasFound = a_bNew;};
		HWND GetAppWnd() {return m_hAppWnd;};
		void SetAppWnd(HWND a_hAppWnd) {m_hAppWnd = a_hAppWnd;};
		std::string* GetAppName() {return &m_AppName;};
		DWORD GetProcessId() {return m_dwProcessId;};
		void SetProcessId(DWORD a_dwNew) {m_dwProcessId = a_dwNew;};
};


#endif // __TASKBUTTON_H__