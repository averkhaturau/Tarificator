#ifndef __MANAGERSCOLLECTION_H__
#define __MANAGERSCOLLECTION_H__

#include "MultiThreadManager.h"

#include <vector>


typedef unsigned long int SizeType;

// ����� MultiThreadManager's � ������������ �������. ������� �� ����
// �������.
// ���� �����, ��� ���������, �� ������� �� � �������, �� � Slave.
class CManagersCollection
{
	public:
		typedef std::vector<CMultiThreadManager*> CVector;
		typedef void __stdcall EnumFunction(CMultiThreadManager* pManager, LPARAM lParam);

	private:
		void DoDeleteEverything();
	protected:
		// ����� ������
		CVector* m_pData;
	public:
		// ����������� �� ���������
		CManagersCollection();
		// ����������� � ��������� ���������� �������
		CManagersCollection(SizeType uiInitialSize);
		// ����������
		~CManagersCollection();

		SizeType size();
		void resize(SizeType uiNewSize);
		// ������ Manager, ������� ����� �������, ��� 0, ���� ���
		// �������� ��� �������
		CMultiThreadManager* GetFreeManager();
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


#endif // __MANAGERSCOLLECTION_H__