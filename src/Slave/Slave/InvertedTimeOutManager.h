#ifndef __INVERTEDTIMEOUTMANAGER_H__
#define __INVERTEDTIMEOUTMANAGER_H__

#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"


// Time out manager, ������� ����������� �� �������� ����������
// ������� �� �������, � �� ����� �������� ���������� �����, �
// ������� �� CTimeOutManager
class CInvertedTimeOutManager
{
	private:
	protected:
		// ����-���
		CTimeStorage m_TimeOut;
		// �����, ����� ������� ������ ��������� ��������
		CTimeStorage m_EdgeTime;
		bool m_bEnabled;
	public:
		CInvertedTimeOutManager();
		~CInvertedTimeOutManager();

		// ��������� m_bEnabled
		bool IsTimeExpired();
		// �� ��������� m_bEnabled
		bool CheckForExpiration();

		// �������
		void SetTimeOut(CTimeStorage a_New) {m_TimeOut = a_New;};
		CTimeStorage GetTimeOut() {return m_TimeOut;};
		void SetEdgeTime(CTimeStorage a_New) {m_EdgeTime = a_New;};
		CTimeStorage GetEdgeTime() {return m_EdgeTime;};
		void SetEnabled(bool a_bNew) {m_bEnabled = a_bNew;};
		bool GetEnabled() {return m_bEnabled;};
};


#endif // __INVERTEDTIMEOUTMANAGER_H__