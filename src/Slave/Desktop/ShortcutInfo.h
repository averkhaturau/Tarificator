#ifndef __SHORTCUTINFO_H__
#define __SHORTCUTINFO_H__

#include <string>
#include "shlobj.h"


class CIconButtonsCollection;


// Структура для описания .lnk-файла
class CShortcutInfo
{
	private:
	protected:
		// Token, под которым следует запустить shortcut
		HANDLE m_hUserToken;

		void DetermineShortFileName();

		// In
		std::string m_sLinkFileName;

		// Out
		// На самом деле не совсем short, а просто без полного пути и
		// расширения
		std::string m_sShortLinkFileName;

		// Out
		char m_czArguments[MAX_PATH];

		// Out
		int m_iShowCmd;

		// Out
		char m_czWorkingDirectory[MAX_PATH];

		// Out
		char m_czTargetPath[MAX_PATH];

		// Out
		char m_czIconPath[MAX_PATH];

		// Out
		int m_iIcon;
	public:
		CShortcutInfo();
		~CShortcutInfo();

		void SetLinkFileName(std::string* a_pNew);

		// Для ускорения ResolveAll в IconButtonsCollection - чтобы
		// каждый раз не создавать instance объектов.
		void DoResolve(IShellLink* a_psl, IPersistFile* a_ppf, HWND a_hWnd);

		HRESULT ResolveShortcut(HWND a_hwnd);

		// Обертки
		int GetIcon() {return m_iIcon;};
		void SetIcon(int a_iNew) {m_iIcon = a_iNew;};
		char* GetIconPath() {return &(m_czIconPath[0]);};
		char* GetTargetPath() {return &(m_czTargetPath[0]);};
		std::string GetLinkFileName() {return m_sLinkFileName;};
		std::string GetShortLinkFileName() {return m_sShortLinkFileName;};
		char* GetArguments() {return &(m_czArguments[0]);};
		char* GetWorkingDirectory() {return &(m_czWorkingDirectory[0]);};
		int* GetShowCmd() {return &m_iShowCmd;};
		void SetUserToken(HANDLE a_hNew) {m_hUserToken = a_hNew;};
		HANDLE GetUserToken() {return m_hUserToken;};
};

#endif // __SHORTCUTINFO_H__