#ifndef __DOMAINNAMEDEFINER_H__
#define __DOMAINNAMEDEFINER_H__


// Максимальная длина user name'а
const DWORD dwUNLength = 1024;
// Максимальная длина domain name'а
const DWORD dwDNLength = 1024;


// true, если все ОК
BOOL GetUserAndDomainName(LPTSTR UserName,
			LPDWORD cchUserName, LPTSTR DomainName,
			LPDWORD cchDomainName);

#endif // __DOMAINNAMEDEFINER_H__
