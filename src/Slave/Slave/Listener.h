#ifndef __LISTENER_H__
#define __LISTENER_H__

#include "AsyncExchanger.h"

#include "Winsock2.h"


// ����������� ����� ������������ ����������� ������
class CListener : virtual public CAsyncExchanger
{
	private:
	protected:
	public:
		// ����������� �� ���������
		CListener();
		// ����������
		virtual ~CListener();
};


#endif // __LISTENER_H__