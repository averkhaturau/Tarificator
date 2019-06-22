#include "stdafx.h"

#include "Receiver.h"
#include "Messages.h"
#include "Exceptions.h"


CReceiver::CReceiver()
{

}
// End of CReceiver()


CReceiver::~CReceiver()
{

}
// ~CReceiver()


void CReceiver::DoPostReceiveNotification(DWORD dwCallbackThreadID, void* pData, DWORD uiSize)
{
	DoPostThreadMessage(dwCallbackThreadID, WM_DATARECEIVED, (DWORD)pData, uiSize);
}
// End of DoSendReceiveNotification
