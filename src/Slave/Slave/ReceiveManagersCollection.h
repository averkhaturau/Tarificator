#ifndef __RECEIVEMANAGERSCOLLECTION_H__
#define __RECEIVEMANAGERSCOLLECTION_H__

#include "ReceiveMulthiThreadManager.h"

#include <vector>


typedef unsigned long int SizeType;

// ����� MultiThreadManager's � ������������ �������. ������� �� ����
// �������.
class CReceiveManagersCollection
{
	public:
		typedef std::vector<CReceiveMultiThreadManager*> CVector;
		typedef void __stdcall EnumFunction(CReceiveMultiThreadManager* pManager, LPARAM lParam);

	private:
		void DoDeleteEverything();
	protected:
		// ����� ������
		CVector* m_pData;
	public:
		// ����������� �� ���������
		CReceiveManagersCollection();
		// ����������� � ��������� ���������� �������
		CReceiveManagersCollection(SizeType uiInitialSize);
		// ����������
		~CReceiveManagersCollection();

		SizeType size();
		void resize(SizeType uiNewSize);
		// ������ Manager, ������� ����� �������, ��� 0, ���� ���
		// �������� ��� �������
		CReceiveMultiThreadManager* GetFreeManager();
		// ���������� ��� �������� � �������� ��� ��� ������� pFunction.
		// lParam - application-defined value. �����, ��������, ��� ��������
		// ���������.
		void EnumManagers(EnumFunction* pFunction, LPARAM lParam);
		// ���������, �� ������� �� ����� ���������
		void OnTimerEvent();

		// �������
		// �� ������������� �����
		CVector* GetData() {return m_pData;};
};


#endif // __RECEIVEMANAGERSCOLLECTION_H__