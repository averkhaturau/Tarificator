#ifndef __ADDITIONALRECEIVEDDATUMCOLLECTION_H__
#define __ADDITIONALRECEIVEDDATUMCOLLECTION_H__

#include "..\..\Master\DataStructures\ActiveContainerResizable.h"
#include "AdditionalRecievedData.h"


class CAdditionalRecievedDatumCollection :
			public CActiveContainerResizable<CAdditionalRecievedData>
{
	private:
	protected:
	public:
		CAdditionalRecievedDatumCollection();
		~CAdditionalRecievedDatumCollection();

		// ���������� ������ ���������� ��������� ���������
		// CAdditionalRecievedData, ��� 0, ���� ����� ���
		CAdditionalRecievedData* GetFreeData();
};


#endif // __ADDITIONALRECEIVEDDATUMCOLLECTION_H__