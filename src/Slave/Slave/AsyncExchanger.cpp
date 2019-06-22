#include "stdafx.h"

#include "AsyncExchanger.h"


CAsyncExchanger::CAsyncExchanger()
{

}
// End of CAsyncExchanger()


CAsyncExchanger::~CAsyncExchanger()
{

}
// End of ~CAsyncExchanger()


void CAsyncExchanger::DoPostThreadMessage(DWORD dwCallbackThreadID, UINT Msg, WPARAM wParam, LPARAM lParam)
{
		if (dwCallbackThreadID)
		{
			PostThreadMessage(dwCallbackThreadID, Msg, wParam, lParam);
		}
}
// End of DoPostThreadMessage
