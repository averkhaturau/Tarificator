#ifndef __ASYNCEXCHANGER_H__
#define __ASYNCEXCHANGER_H__

#include "stdafx.h"


// ����� �������� ��� ����������� ������������ ������ �������
class CAsyncExchanger
{
	private:
	protected:
		// ���������� ������� ������� ������
		void DoPostThreadMessage(DWORD dwCallbackThreadID, UINT Msg, WPARAM wParam, LPARAM lParam);
	public:
		CAsyncExchanger();
		virtual ~CAsyncExchanger();
};


#endif // __ASYNCEXCHANGER_H__