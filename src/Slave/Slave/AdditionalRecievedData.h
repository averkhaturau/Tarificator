#ifndef __ADDITIONALRECEIVEDDATA_H__
#define __ADDITIONALRECEIVEDDATA_H__

#include <vector>
#include "TimeOutManager.h"


//typedef std::vector<char> CAdditionalRecievedData;
class CAdditionalRecievedData
{
	private:
		void DoDeleteEverything();
	protected:
		typedef std::vector<char> CData;

		CData* m_pData;
		bool m_bIsUsed;
		CTimeOutManager* m_pTimeOutManager;
	public:
		CAdditionalRecievedData();
		~CAdditionalRecievedData();

		// ���� ����� ������� - ������ m_bIsUsed = false
		void CheckForExpiration();

		void SetIsUsed(bool a_bNew);

		// �������
		bool GetIsUsed() {return m_bIsUsed;};
		CData* GetData() {return m_pData;};
};


#endif // __ADDITIONALRECEIVEDDATA_H__