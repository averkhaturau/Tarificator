#include "stdafx.h"


//#include "..\Desktop\ShortcutInfo.h"

#include <string>
#include "shellapi.h"




void GetTextBetweenQuotas(std::string* a_psIn, std::string* a_psOut)
{
		if ( (!a_psIn) || (!a_psOut) )
			return;

	DWORD dwLength = strlen(a_psIn->c_str());
	signed long int dwFirstQuota = -1, dwLastQuota = dwLength;

	signed long int i = 0;
		for (i = 0; i < dwLength; ++i)
		{
				if ( (*a_psIn)[i] == '\"' )
				{
					dwFirstQuota = i;
					break;
				}
		}
		for (i = dwLength - 1; i >= 0; --i)
		{
				if ( (*a_psIn)[i] == '\"' )
				{
					dwLastQuota = i;
					break;
				}
		}

	a_psOut->resize(dwLastQuota - dwFirstQuota - 1);
		for (i = 0; i < dwLastQuota - dwFirstQuota - 1; ++i)
		{
			(*a_psOut)[i] = (*a_psIn)[i + dwFirstQuota + 1];
		}
};




// Разделяет полный путь на имя каталога и имя файла 
void SeparateTextForDirAndFile(std::string* a_psIn, std::string* a_psOutDir, std::string* a_psOutFile)
{
		if ( (!a_psIn) || (!a_psOutDir) || (!a_psOutFile) )
			return;

	DWORD dwLength = strlen(a_psIn->c_str());
	signed long int dwLastSlashPosition = -1;

	signed long int i = 0;
		for (i = dwLength; i >= 0; --i)
		{
				if ( (*a_psIn)[i] == '\\' )
				{
					dwLastSlashPosition = i;
					break;
				}
		}

		if (dwLastSlashPosition >= 0)
			a_psOutDir->resize(dwLastSlashPosition);
	a_psOutFile->resize(dwLength - dwLastSlashPosition - 1);
		for (i = 0; i < dwLastSlashPosition; ++i)
		{
			(*a_psOutDir)[i] = (*a_psIn)[i];
		}
		for (i = 0; i < dwLength - dwLastSlashPosition - 1; ++i)
		{
			(*a_psOutFile)[i] = (*a_psIn)[i + dwLastSlashPosition + 1];
		}
};




//int main( int argc, char *argv[ ], char *envp[ ] )
int APIENTRY WinMain(HINSTANCE hInstance,
			HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{
		if (!strcmp(lpCmdLine, ""))
			return 0;

	HANDLE hApp = 0;

		try
		{
			//CoInitialize(0);

			std::string sFullName = "";
			GetTextBetweenQuotas( &((std::string)lpCmdLine), &sFullName );

			/*CShortcutInfo Shortcut;
			Shortcut.SetLinkFileName( &sName );
			Shortcut.ResolveShortcut(0);

			SHELLEXECUTEINFO seInfo = {
						sizeof(SHELLEXECUTEINFO),
						SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI, //| SEE_MASK_DOENVSUBST | SEE_MASK_CONNECTNETDRV,
						0,
						"open",
						&(Shortcut.GetTargetPath()[0]),
						&(Shortcut.GetArguments()[0]),
						&(Shortcut.GetWorkingDirectory()[0]),
						*Shortcut.GetShowCmd(),
						0,
						0, 0, 0, 0, 0,
						0};*/

			std::string sDirectory, sShortFileName;
			SeparateTextForDirAndFile(&sFullName, &sDirectory, &sShortFileName);

			SetCurrentDirectory(sDirectory.c_str());

			SHELLEXECUTEINFO seInfo = {
						sizeof(SHELLEXECUTEINFO),
						SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI, //| SEE_MASK_DOENVSUBST | SEE_MASK_CONNECTNETDRV,
						0,
						0, // Verb
						//lpCmdLine,
						//sName.c_str(),
						sShortFileName.c_str(),
						0, // Arguments
						0, // Working directory
						nCmdShow,
						0,
						0, 0, 0, 0, 0,
						0};

				if ( ShellExecuteEx(&seInfo) )
				{
						if ((int)seInfo.hInstApp > 32)
						{
							hApp = seInfo.hProcess;
							WaitForSingleObject(hApp, INFINITE);
						}
				}
		}
		catch(...)
		{
		}

		if (hApp)
		{
			CloseHandle(hApp);
			hApp = 0;
		}

	//CoUninitialize();

	return 0;
}
