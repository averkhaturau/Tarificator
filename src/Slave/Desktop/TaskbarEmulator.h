#ifndef __TASKBAREMULATOR_H__
#define __TASKBAREMULATOR_H__

#include "TaskButtonsCollection.h"


class CTaskbarEmulator
{
	private:
		void DoDeleteEverything();
	protected:
		HWND m_hWnd;
		HINSTANCE m_hInst;
		HBRUSH m_hBackground;

		bool m_bWasNotFound;
		bool m_bEnumerating;

		CTaskButtonsCollection* m_pButtonsCollection;

		void OnAppWindowFound(HWND a_hWnd);
		void ReCreateButtons();
		void RePosButtons();

		void GetPos(DWORD a_dwXNumber, RECT* a_pRect);

		friend BOOL CALLBACK FindAppWindowProc(HWND hwnd, LPARAM lParam);
	public:
		CTaskbarEmulator(HINSTANCE a_hInst);
		~CTaskbarEmulator();

		void CreateWnd(HINSTANCE a_hInst);

		void OnTimer();

		// Обертки
		HWND GetWnd() {return m_hWnd;};
		HBRUSH GetBackgroundBrush() {return m_hBackground;};
};

#endif // __TASKBAREMULATOR_H__