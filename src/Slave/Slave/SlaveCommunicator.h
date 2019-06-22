#ifndef __SLAVECOMMUNICATOR_H__
#define __SLAVECOMMUNICATOR_H__

#include "Incoming.h"
#include "Outcoming.h"


class CSlaveCommunicator
{
	// ����������� �����, ��������������� ��������� ��� ������� �
	// �������� ��� ������������/������� ������� ������
	private:
		void DoDeleteEverything();
	protected:
		CIncoming* m_pIncoming;
		COutcoming* m_pOutcoming;
	public:
		// �����������
		CSlaveCommunicator();
		// ����������
		virtual ~CSlaveCommunicator();

		// �������� ������������� � ������� ������
		virtual void SendLockSuccess() = 0;
		// �������� ������������� �� ������� ������
		virtual void SendUnLockSuccess() = 0;
		// �������� ����������� � �������� ������� ������
		virtual void SendLockFail() = 0;
		// �������� ����������� � �������� ������� ������
		virtual void SendUnLockFail() = 0;
		// �������� ������ �� ��������� ������� ��������� ������
		virtual void SendReCheckState() = 0;

		void OnDataReceived(char* pBuffer, DWORD dwSize, WPARAM wParam, LPARAM lParam);
};


#endif // __SLAVECOMMUNICATOR_H__