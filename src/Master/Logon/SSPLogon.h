#ifndef _LX_SSPLOGON_H_INCLUDED_1234
#define _LX_SSPLOGON_H_INCLUDED_1234


#define SECURITY_WIN32

#include <windows.h>
#include <sspi.h>


namespace SSP
{
	extern "C"{
		//#include "comm.h"
		//#include "security.h"

		BOOL SSPLogonUser(
			LPTSTR DomainName,
			LPTSTR UserName,
			LPTSTR Password );
	}// extern "C"
};

#endif //_LX_SSPLOGON_H_INCLUDED_1234
