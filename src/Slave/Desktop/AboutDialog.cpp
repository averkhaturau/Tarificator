#include "stdafx.h"

#include "AboutDialog.h"
#include "SmallPictureDescription.h"
#include "BigPictureDescription.h"
#include "ClubDefiner.h"
#include "..\Slave\Messages.h"

#include "resource.h"



BOOL FAR PASCAL AboutBoxProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	CAboutDialog* pDialog = (CAboutDialog*)GetWindowLong(hWnd, GWL_USERDATA);

		switch (uiMsg)
		{
			case WM_COMMAND:
					if (LOWORD(wParam) == IDOK)
							if (pDialog)
								pDialog->DoEndDialog();
			break;

			case WM_CLOSE:
					if (pDialog)
						pDialog->DoEndDialog();
			break;

			case WM_INITDIALOG:
				return TRUE;
		}

	return FALSE;
}
// End of AboutBoxProc 





CAboutDialog::CAboutDialog(HINSTANCE a_hInst)
{
	m_hInst = a_hInst;
	m_hDialog = 0;
	m_hOrionSmallPicture = 0;
	m_hClubBigPicture = 0;

	m_hCommonInfoGroup = 0;
	m_hCommonInfoStatic = 0;

	m_hClubBig = 0;

	m_hOrionSmall = 0;
}
// End of CAboutDialog()


CAboutDialog::~CAboutDialog()
{
	DoDeleteEverything();
}
// End of ~CAboutDialog()


void CAboutDialog::DoDeleteEverything()
{
	DoEndDialog();

		if (m_hOrionSmall)
		{
			DeleteObject(m_hOrionSmall);
			m_hOrionSmall = 0;
		}
		if (m_hClubBig)
		{
			DeleteObject(m_hClubBig);
			m_hClubBig = 0;
		}
}
// End of DoDeleteEverything()


void CAboutDialog::DoEndDialog()
{
		if (m_hOrionSmallPicture)
		{
			DestroyWindow(m_hOrionSmallPicture);
			m_hOrionSmallPicture = 0;
		}
		if (m_hClubBigPicture)
		{
			DestroyWindow(m_hClubBigPicture);
			m_hClubBigPicture = 0;
		}
		if (m_hDialog)
		{
			EndDialog(m_hDialog, 0);
			m_hDialog = 0;
		}

	m_hCommonInfoGroup = 0;
	m_hCommonInfoStatic = 0;
	m_hClubInfoGroup = 0;
	m_hClubInfoStatic = 0;
}
// End of DoEndDialog()


void CAboutDialog::CreateWnd(HWND a_hParent)
{
	m_hDialog = CreateDialog(
				m_hInst,
				MAKEINTRESOURCE(IDD_ABOUT),
				a_hParent,
				AboutBoxProc);

	SetWindowLong(m_hDialog, GWL_USERDATA, (long)this);

	// Стиль таскбара
	//DWORD dwStyle = GetWindowLong(FindWindow("Shell_traywnd", ""), GWL_STYLE);

	RECT MaxWorkRect;
		//if (dwStyle & WS_VISIBLE)
		{
			SystemParametersInfo(SPI_GETWORKAREA, 0, &MaxWorkRect, SPIF_UPDATEINIFILE);
		}
		/*else
		{
			GetWindowRect(GetDesktopWindow(), &MaxWorkRect);
		}*/

	RECT DialogRect;
	GetWindowRect(m_hDialog, &DialogRect);
	UINT uiDWidth = DialogRect.right - DialogRect.left,
				uiDHeight = DialogRect.bottom - DialogRect.top,
				uiDX = (MaxWorkRect.right - MaxWorkRect.left - uiDWidth) / 2,
				uiDY = (MaxWorkRect.bottom - MaxWorkRect.top - uiDHeight) / 2;
	SetWindowPos(m_hDialog, 0, uiDX, uiDY, uiDWidth, uiDHeight, SWP_NOZORDER);

		if (!m_hOrionSmallPicture)
		{
			m_hOrionSmallPicture = CreateWindowEx(
						0,
						"Button",
						"",
						WS_VISIBLE | WS_CHILD | BS_BITMAP,
						0, 0, 0, 0,
						m_hDialog,
						0, 0, 0);
		}

	m_hCommonInfoGroup = GetDlgItem(m_hDialog, IDC_COMMON_INFO_GROUP);
	m_hCommonInfoStatic = GetDlgItem(m_hDialog, IDC_COMMON_INFO_STATIC);

	RECT GroupRect, StaticRect;
		if ( m_hCommonInfoGroup && m_hCommonInfoStatic && m_hOrionSmallPicture )
		{
			GetClientRect(m_hCommonInfoGroup, &GroupRect);
			GetClientRect(m_hCommonInfoStatic, &StaticRect);

			UINT uiOSWidth = uiSmallPictureWidth + 2 * GetSystemMetrics(SM_CXEDGE),
						uiOSHeight = uiSmallPictureHeight + 2 * GetSystemMetrics(SM_CYEDGE),
						uiOSX = (GroupRect.right + StaticRect.right - uiOSWidth) / 2,
						uiOSY = (GroupRect.bottom + GroupRect.top - uiOSHeight)/2;
			SetWindowPos(m_hOrionSmallPicture, 0, uiOSX, uiOSY, uiOSWidth, uiOSHeight, SWP_NOZORDER);

				if (!m_hOrionSmall)
					m_hOrionSmall = LoadBitmap(m_hInst, ORION_SMALL);
				if (m_hOrionSmall)
					SendMessage(m_hOrionSmallPicture, BM_SETIMAGE, IMAGE_BITMAP, (long)m_hOrionSmall);
		}

	m_hClubInfoGroup = GetDlgItem(m_hDialog, IDC_CLUB_INFO_GROUP);
	m_hClubInfoStatic = GetDlgItem(m_hDialog, IDC_CLUB_INFO_STATIC);
		if (!m_hClubBigPicture)
		{
			m_hClubBigPicture = CreateWindowEx(
						0,
						"Button",
						"",
						WS_VISIBLE | WS_CHILD | BS_BITMAP,
						0, 0, 0, 0,
						m_hDialog,
						0, 0, 0);
		}

		if (m_hClubInfoStatic)
		{
			char cBuffer[1024];
				if (LoadString(m_hInst, CLUB_INFO, &(cBuffer[0]), 1023))
				{
					SetWindowText(m_hClubInfoStatic, &(cBuffer[0]));
				}
		}

		if ( m_hClubInfoGroup && m_hClubInfoStatic && m_hClubBigPicture )
		{
			GetWindowRect(m_hClubInfoGroup, &GroupRect);
			GetWindowRect(m_hClubInfoStatic, &StaticRect);

			UINT uiCBWidth = uiBigPictureWidth + 2 * GetSystemMetrics(SM_CXEDGE),
						uiCBHeight = uiBigPictureHeight + 2 * GetSystemMetrics(SM_CYEDGE),
						uiCBX = (GroupRect.right + StaticRect.right - uiCBWidth) / 2,
						uiCBY = (GroupRect.bottom + GroupRect.top - uiCBHeight)/2;

			POINT Temp;
			Temp.x = uiCBX;
			Temp.y = uiCBY;
			ScreenToClient(m_hDialog, &Temp);
			uiCBX = Temp.x;
			uiCBY = Temp.y;

			SetWindowPos(m_hClubBigPicture, 0, uiCBX, uiCBY, uiCBWidth, uiCBHeight, SWP_NOZORDER);

				if (!m_hClubBig)
					m_hClubBig = LoadBitmap(m_hInst, BIG_BITMAP);
				if (m_hClubBig)
					SendMessage(m_hClubBigPicture, BM_SETIMAGE, IMAGE_BITMAP, (long)m_hClubBig);
		}
}
// ENd of CreateWnd
