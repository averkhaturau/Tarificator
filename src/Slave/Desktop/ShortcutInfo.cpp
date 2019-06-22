#include "stdafx.h"

#include "ShortcutInfo.h"
#include "..\Slave\Exceptions.h"
#include "..\Slave\Messages.h"


#include "shlobj.h"
#include "Shellapi.h"



CShortcutInfo::CShortcutInfo()
{
	m_sLinkFileName = "";
	m_sShortLinkFileName = "";
	m_czArguments[0] = '\0';
	m_iShowCmd = 0;
	m_czWorkingDirectory[0] = '\0';
	m_czTargetPath[0] = '\0';
	m_czIconPath[0] = '\0';
	m_iIcon = 0;
	m_hUserToken = 0;
}
// End of CShortcutInfo()


CShortcutInfo::~CShortcutInfo()
{

}
// End of ~CShortcutInfo()


void CShortcutInfo::SetLinkFileName(std::string* a_pNew)
{
	m_sLinkFileName = *a_pNew;

	DetermineShortFileName();
}
// End of SetLinkFileName


void CShortcutInfo::DetermineShortFileName()
{
	UINT uiDotPosition = 0, uiSlashPosition = 0;
		for (signed long int i = strlen(m_sLinkFileName.c_str());
					((i >= 0) && ((uiSlashPosition == 0) || (uiDotPosition == 0))); --i)
		{
				if (m_sLinkFileName[i] == '.')
						if (!uiDotPosition)
							uiDotPosition = i;
				if (m_sLinkFileName[i] == '\\')
						if (!uiSlashPosition)
							uiSlashPosition = i;
		}

		if (uiSlashPosition < uiDotPosition)
		{
			m_sShortLinkFileName.resize(uiDotPosition - uiSlashPosition);
				for (i = uiSlashPosition + 1; i < uiDotPosition; ++i)
				{
					m_sShortLinkFileName[i - uiSlashPosition - 1] = m_sLinkFileName[i];
				}
			m_sShortLinkFileName[uiDotPosition - uiSlashPosition - 1] = '\0';
		}
}
// End of DetermineShortFileName()


void CShortcutInfo::DoResolve(IShellLink* a_psl, IPersistFile* a_ppf, HWND a_hWnd)
{
	(GetTargetPath())[0] = 0; // assume failure

	WCHAR wsz[MAX_PATH];

	// Ensure that the string is Unicode.
	MultiByteToWideChar(CP_ACP, 0, GetLinkFileName().c_str(), -1, wsz,
				MAX_PATH);

	HRESULT hres;
	// Load the shortcut.
	hres = a_ppf->Load(wsz, STGM_READ);

		if (SUCCEEDED(hres))
		{
			// Resolve the link.
			hres = a_psl->Resolve(a_hWnd, SLR_NO_UI);

				if (SUCCEEDED(hres))
				{
					char szGotPath[MAX_PATH];
					WIN32_FIND_DATA wfd;
					// Get the path to the link target.
					hres = a_psl->GetPath(szGotPath,
								MAX_PATH, (WIN32_FIND_DATA *)&wfd,
								SLGP_SHORTPATH);

						if (FAILED(hres))
						{
							std::string ErrorMessage = "An error occured in CDesktopEmulator::ResolveShortcut: can't get link target's path for shortcut ";
							ErrorMessage += GetLinkFileName();
							throw CAnyLogableException(ErrorMessage, bDoNotWriteDuplicates);
						}

					lstrcpy(GetTargetPath(), szGotPath);

					int iIcon;
					hres = a_psl->GetIconLocation(&(GetIconPath()[0]), MAX_PATH, &iIcon);
					SetIcon(iIcon);
						if (FAILED(hres))
						{
							std::string ErrorMessage = "An error occured in CDesktopEmulator::ResolveShortcut: can't get icon for shortcut ";
							ErrorMessage += GetLinkFileName();
							throw CAnyLogableException(ErrorMessage, bDoNotWriteDuplicates);
						}

					hres = a_psl->GetArguments(&(GetArguments()[0]), MAX_PATH);
						if (FAILED(hres))
						{
							std::string ErrorMessage = "An error occured in CDesktopEmulator::ResolveShortcut: can't get arguments for shortcut ";
							ErrorMessage += GetLinkFileName();
							throw CAnyLogableException(ErrorMessage, bDoNotWriteDuplicates);
						}

					hres = a_psl->GetWorkingDirectory(&(GetWorkingDirectory()[0]), MAX_PATH);
						if (FAILED(hres))
						{
							std::string ErrorMessage = "An error occured in CDesktopEmulator::ResolveShortcut: can't get working directory for shortcut ";
							ErrorMessage += GetLinkFileName();
							throw CAnyLogableException(ErrorMessage, bDoNotWriteDuplicates);
						}

					hres = a_psl->GetShowCmd(GetShowCmd());
						if (FAILED(hres))
						{
							std::string ErrorMessage = "An error occured in CDesktopEmulator::ResolveShortcut: can't get show command for shortcut ";
							ErrorMessage += GetLinkFileName();
							throw CAnyLogableException(ErrorMessage, bDoNotWriteDuplicates);
						}
				}
		}
}
// End of DoResolve


HRESULT CShortcutInfo::ResolveShortcut(HWND a_hWnd)
{
	HRESULT hres;
	IShellLink* psl;
 
	// Get a pointer to the IShellLink interface.
	hres = CoCreateInstance(CLSID_ShellLink, NULL,
				CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl);

		if (SUCCEEDED(hres))
		{
			IPersistFile* ppf;

			// Get a pointer to the IPersistFile interface.
			hres = psl->QueryInterface(IID_IPersistFile,
						(void**)&ppf);
				if (SUCCEEDED(hres))
				{
					DoResolve(psl, ppf, a_hWnd);

					// Release the pointer to the IPersistFile interface.
					ppf->Release();
				}
			// Release the pointer to the IShellLink interface.
			psl->Release();
		}
		else
			throw CAnyLogableException("An error occured in CDesktopEmulator::ResolveShortcut: possible reason is COM library is not initialized", bDoNotWriteDuplicates);

	return hres;
}
// End of ResolveShortcut

