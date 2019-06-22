#include "stdafx.h"

#include "WindowsVersionDefiner.h"
#include "..\..\Slave\Slave\Exceptions.h"


CWindowsVersionDefiner::CWindowsVersionDefiner()
{
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure,
	// which is supported on Windows 2000.
	//
	// If that fails, try using the OSVERSIONINFO structure.

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

		if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
		{
			// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

			osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
				if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) )
					throw CAnyLogableException("Can't define Windows version 8-/", bDoNotWriteDuplicates);
   }

		switch (osvi.dwPlatformId)
		{
			case VER_PLATFORM_WIN32_NT:
				m_Version = WinNT;
			break;

			case VER_PLATFORM_WIN32_WINDOWS:
				m_Version = Win9x;
			break;
   }
}
// End of CWindowsVersionDefiner()


CWindowsVersionDefiner::~CWindowsVersionDefiner()
{

}
// End of ~CWindowsVersionDefiner()
