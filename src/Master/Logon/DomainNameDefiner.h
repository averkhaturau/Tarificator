#ifndef __DOMAINNAMEDEFINER_H__
#define __DOMAINNAMEDEFINER_H__


// ������������ ����� user name'�
const DWORD dwUNLength = 1024;
// ������������ ����� domain name'�
const DWORD dwDNLength = 1024;


// true, ���� ��� ��
BOOL GetUserAndDomainName(LPTSTR UserName,
			LPDWORD cchUserName, LPTSTR DomainName,
			LPDWORD cchDomainName);

#endif // __DOMAINNAMEDEFINER_H__
