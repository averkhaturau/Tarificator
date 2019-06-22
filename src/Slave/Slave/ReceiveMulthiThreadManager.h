#ifndef __RECEIVEMULTITHREADMANAGER_H__
#define __RECEIVEMULTITHREADMANAGER_H__

#include "MultiThreadManager.h"
#include "ReceiverParamsCollection.h"


// ���������� �� CMultiThreadManager'� ������ ���, ��� �����
// ��������� �� ��������������� CReceiveParameters, ����� ��� TimeOut
// ������� ��� Used = false
class CReceiveMultiThreadManager : public CMultiThreadManager
{
	private:
	protected:
		// ��������������� �������
		CReceiveParameters* m_pReceiveParameters;
	public:
		// ����������� �� ���������
		CReceiveMultiThreadManager();
		~CReceiveMultiThreadManager();

		// ��������� Expired � ���� ���� - ���������. ���������� true,
		// ���� �������� ����� �����.
		bool OnTimerEvent();

		// �������
		CReceiveParameters* GetReceiveParameters() {return m_pReceiveParameters;};
		void SetReceiveParameters(CReceiveParameters* pNew) {m_pReceiveParameters = pNew;};
};


#endif // __RECEIVEMULTITHREADMANAGER_H__