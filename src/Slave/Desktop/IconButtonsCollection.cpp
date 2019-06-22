#include "stdafx.h"

#include "IconButtonsCollection.h"
#include "..\Slave\Exceptions.h"
#include "..\Slave\Messages.h"

#include "shlobj.h"


void CIconButtonsCollection::ResolveAll(HWND a_hwnd)
{
	CoInitialize(NULL);

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
					iterator Iter = GetData()->begin(), EndIter = GetData()->end();
						for (; Iter < EndIter; ++Iter)
						{
							(*Iter)->GetShortcutInfo()->DoResolve(psl, ppf, a_hwnd);
						}
					// Release the pointer to the IPersistFile interface.
					ppf->Release();
				}
			// Release the pointer to the IShellLink interface.
			psl->Release();
		}
		else
			throw CAnyLogableException("An error occured in CDesktopEmulator::ResolveShortcut: possible reason is COM library is not initialized", bDoNotWriteDuplicates);

	//return hres;
}
// End of ResolveAll()
