// Logon.cpp : Defines the entry point for the console application.
//

#define SECURITY_WIN32

#include <windows.h>
#include <sspi.h>

#include "security.h"
#include <winsock.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "security.h"
#include "comm.h"


/*++

Module Name:

   SSPLogon.c

Abstract:

  This module implements the network logon type by
  interfacing with the Windows NT Lan Man Security Support
  Provider (NTLMSSP) for the purpose of validating
  the provided users credentials.


Author:

  David Mowers (DaveMo) January 14, 1998

The following modules from the SockAuth sample are required:

  security.c (modify according to comment below)
  collect.c

The following import libraries are required:

  none

Revision History:

--*/ 


// 
// Slight change to GenClientContext so that you can
// pass user credentials.
// 
/*BOOL GenClientContext (
  DWORD dwKey,
  SEC_WINNT_AUTH_IDENTITY *pAuthIdentity,
  BYTE *pIn,
  DWORD cbIn,
  BYTE *pOut,
  DWORD *pcbOut,
  BOOL *pfDone);
*/
/*

  In security.c, for the GenClientContext function,
  make the following modification:

  ss = g_pFuncs->AcquireCredentialsHandle (
     NULL,   // principal
     PACKAGE_NAME,
     SECPKG_CRED_OUTBOUND,
     NULL,   // LOGON id
     pAuthIdentity,   // auth data
     NULL,   // get key fn
     NULL,   // get key arg
     &pAS->_hcred,
     &Lifetime
     );
*/ 


static PBYTE g_pClientBuf = NULL;
static PBYTE g_pServerBuf = NULL;
static DWORD g_cbMaxMessage = 0;

BOOL
SSPLogonUser(
  LPTSTR DomainName,
  LPTSTR UserName,
  LPTSTR Password )
{
  BOOL done = FALSE;
  DWORD cbOut, cbIn;
  //char szUser[80];
  DWORD cbUser = 80;
  SEC_WINNT_AUTH_IDENTITY AuthIdentity;

  if(!InitSession(0))
  {
     return(FALSE);
  }

  if(!InitSession(1))
  {
     return(FALSE);
  }

  if (!InitPackage (&g_cbMaxMessage))
  {
     return(FALSE);
  }

  g_pClientBuf = (PBYTE) malloc(g_cbMaxMessage);
  g_pServerBuf = (PBYTE) malloc(g_cbMaxMessage);

  ZeroMemory( &AuthIdentity, sizeof(AuthIdentity) );

  if ( DomainName != NULL )
  {
     AuthIdentity.Domain = (unsigned char *)DomainName;
     AuthIdentity.DomainLength = lstrlen(DomainName);
  }

  if ( UserName != NULL )
  {
     AuthIdentity.User = (unsigned char *)UserName;
     AuthIdentity.UserLength = lstrlen(UserName);
  }

  if ( Password != NULL )
  {
     AuthIdentity.Password = (unsigned char *)Password;
     AuthIdentity.PasswordLength = lstrlen(Password);
  }

#ifdef UNICODE
   AuthIdentity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
#else
  AuthIdentity.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
#endif

  // 
  // Prepare client message (negotiate).
  // 
  cbOut = g_cbMaxMessage;
  if (!GenClientContext (
	  0,
     &AuthIdentity,
     NULL,
     0,
     g_pClientBuf,
     &cbOut,
     &done))
  {
     return(FALSE);
  }

  cbIn = cbOut;
  // 
  // Prepare server message (challenge).
  // 
  cbOut = g_cbMaxMessage;
  if (!GenServerContext (
     1,
     g_pClientBuf,
     cbIn,
     g_pServerBuf,
     &cbOut,
     &done))
  {
     // 
     // Most likely failure: AcceptServerContext fails with
     // SEC_E_LOGON_DENIED in the case of bad username or password
     // 
     // Unexpected Result: Logon will succeed if you pass in a bad
     // username and the guest account is enabled in the specified
     // domain.
     // 
     return(FALSE);
  }

  cbIn = cbOut;
  // 
  // Prepare client message (authenticate).
  // 
  cbOut = g_cbMaxMessage;
  if (!GenClientContext (
	  0,
     &AuthIdentity,
     g_pServerBuf,
     cbIn,
     g_pClientBuf,
     &cbOut,
     &done))
  {
     return(FALSE);
  }

  cbIn = cbOut;
  // 
  // Prepare server message (authentication).
  // 
  cbOut = g_cbMaxMessage;
  if (!GenServerContext (
     1,
     g_pClientBuf,
     cbIn,
     g_pServerBuf,
     &cbOut,
     &done))
  {
     return(FALSE);
  }

		if ( !ImpersonateContext(1) )
			return FALSE;

  TermSession(0);
  TermSession(1);

  TermPackage();

  free(g_pClientBuf);
  free(g_pServerBuf);

  return(TRUE);
}


/*
int main( int argc, char *argv[] )
{

	if(SSPLogonUser("LX", "NetLogonTest", "pocemon"))
	{
		MessageBox(0, "SSP Logon Succeeded!",  "!", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(0, "SSP Logon Failed!",  "!", MB_ICONINFORMATION);
		exit(1);
	}

	getch();


	return EXIT_SUCCESS;
}
*/