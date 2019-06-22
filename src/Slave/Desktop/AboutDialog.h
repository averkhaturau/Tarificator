#ifndef __ABOUTDIALOG_H__
#define __ABOUTDIALOG_H__


class CAboutDialog
{
	private:
		void DoDeleteEverything();
	protected:
		HINSTANCE m_hInst;
		HWND m_hDialog;
		HWND m_hOrionSmallPicture;
		HWND m_hClubBigPicture;

		HWND m_hCommonInfoStatic;
		HWND m_hCommonInfoGroup;

		HWND m_hClubInfoStatic;
		HWND m_hClubInfoGroup;

		HBITMAP m_hOrionSmall;
		HBITMAP m_hClubBig;

		void DoEndDialog();

		friend BOOL FAR PASCAL AboutBoxProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	public:
		CAboutDialog(HINSTANCE a_hInst);
		~CAboutDialog();

		void CreateWnd(HWND a_hParent);

		// Обертки
		HWND GetWnd() {return m_hDialog;};
};


#endif // __ABOUTDIALOG_H__