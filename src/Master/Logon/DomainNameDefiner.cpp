#include "stdafx.h"

#include "DomainNameDefiner.h"


BOOL GetUserAndDomainName(LPTSTR UserName,
			LPDWORD cchUserName, LPTSTR DomainName,
			LPDWORD cchDomainName)
{
	HANDLE hToken;

	#define MY_BUFSIZE 512  // highly unlikely to exceed 512 bytes
	UCHAR InfoBuffer[ MY_BUFSIZE ];
	DWORD cbInfoBuffer = MY_BUFSIZE;
	SID_NAME_USE snu;

	BOOL bSuccess;

		if (!OpenThreadToken(GetCurrentThread(),
					TOKEN_QUERY, TRUE, &hToken))
		{
				if(GetLastError() == ERROR_NO_TOKEN)
				{
					// 
					// attempt to open the process token, since no thread token
					// exists
					// 

					if(!OpenProcessToken(GetCurrentProcess(),
								TOKEN_QUERY, &hToken))
						return FALSE;

				}
				else
				{
					// 
					// error trying to get thread token
					// 

					return FALSE;
				}
		}

	bSuccess = GetTokenInformation(hToken, TokenUser,
				InfoBuffer, cbInfoBuffer, &cbInfoBuffer);

		if (!bSuccess)
		{
				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					// 
					// alloc buffer and try GetTokenInformation() again
					// 

					CloseHandle(hToken);
					return FALSE;
				}
				else
				{
					// 
					// error getting token info
					// 

					CloseHandle(hToken);
					return FALSE;
				}
		}

	CloseHandle(hToken);

	return LookupAccountSid(NULL,
				((PTOKEN_USER)InfoBuffer)->User.Sid,
				UserName, cchUserName, DomainName,
				cchDomainName, &snu);
}
// End of GetUserAndDomainName
