#ifndef __TIMEOUTMANAGER_H__
#define __TIMEOUTMANAGER_H__

#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"


class CTimeOutManager
{
	private:
	protected:
		// ������� ��
		bool m_bEnabled;
		// ������� � ���������������� ����������
		CTimeStorage m_TimeOut;
		// ������
		CTimeStorage m_Begin;
	public:
		// ����������� �� ���������
		CTimeOutManager();
		// �������� ���, ����� begin
		CTimeOutManager(CTimeOutManager* pManager);
		// ����������
		virtual ~CTimeOutManager();

		// ������������� �������� ������ �������
		void OnBegin();
		// true, ���� ����� �����. ���� !m_bEnabled - ���������� false.
		bool IsTimeExpired();

		// ������������ ������������� ��������� ���������� �������
		void SetArtificialTimeOutState();

		bool operator==(CTimeOutManager& a_Other);

		// �������
		bool GetEnabled() {return m_bEnabled;};
		void SetEnabled(bool bNew) {m_bEnabled = bNew;};
		CTimeStorage GetTimeOut() {return m_TimeOut;};
		void SetTimeOut(CTimeStorage New) {m_TimeOut = New;};
};


#endif // __TIMEOUTMANAGER_H__