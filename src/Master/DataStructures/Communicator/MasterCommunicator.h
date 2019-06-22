#ifndef __MASTERCOMMUNICATOR_H__
#define __MASTERCOMMUNICATOR_H__

#include "..\..\..\Slave\Slave\Incoming.h"
#include "..\..\..\Slave\Slave\Outcoming.h"
#include "..\ClubSettings\TimeInterval.h"


// Predefinition
class CTarifPlan;

// ����������� �����, �������������� ��������� ��� �������
// ��������������� ������
class CMasterCommunicator
{
	private:
		void DoDeleteEverything();
	protected:
		CIncoming* m_pIncoming;
		COutcoming* m_pOutcoming;
	public:
		CMasterCommunicator();
		virtual ~CMasterCommunicator();

		// �������� ������ � �������� ������
		virtual void SendLockOrder(CInterval* pInterval) = 0;
		// �������� ������ �� �������� ������
		virtual void SendUnLockOrder(CInterval* pInterval, CTarifPlan* pPlan) = 0;
		virtual void SendTurnoffOrder() = 0;
		virtual void SendRestartOrder() = 0;

		void OnDataReceived(char* pBuffer, DWORD dwSize, WPARAM wParam, LPARAM lParam);
};


#endif // __MASTERCOMMUNICATOR_H__