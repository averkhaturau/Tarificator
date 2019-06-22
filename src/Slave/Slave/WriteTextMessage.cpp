#include "stdafx.h"

#include "WriteTextMessage.h"

#include <string>


void WriteTextMessage(LPCTSTR a_psText, DWORD a_dwNumber)
{
	std::string* psText = new std::string;
	*psText = a_psText;
	PostThreadMessage(GetCurrentThreadId(), WM_WRITE_TEXT_MESSAGE, (WPARAM)psText, a_dwNumber);
}
