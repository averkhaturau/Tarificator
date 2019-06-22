#ifndef __TCP_IP_CLASS_H__
#define __TCP_IP_CLASS_H__

#include "TCP_IP_SocketHolder.h"


// ������������ ������������� TCP/IP. �� ���� ����������� ���
// ���������� ������, ���������� � TCP/IP.
class CTCP_IP_Class
{
	private:
		void DoDeleteEverything();
	protected:
	public:
		// �����������. ��� ���������������� WinSockets ��� ����������
		CTCP_IP_Class(CNetworkParametersDataReader* pReader);
		// ����������. ��� ��������� WinSockets ��� ������� ����������
		virtual ~CTCP_IP_Class();
};


#endif // __TCP_IP_CLASS_H__