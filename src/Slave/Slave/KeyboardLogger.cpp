#include "stdafx.h"

#include "KeyboardLogger.h"


CKeyboardLogger::~CKeyboardLogger()
{

}
// End of ~CKeyboardLogger()


void CKeyboardLogger::WriteString(FILE* pFile, const char* pCharArray)
{
	// Собственно сообщение об ошибке
	DoWriteString(pFile, pCharArray);

	// Перевод строки
	/*std::string StringToWrite = "\n";
	DoWriteString(pFile, StringToWrite.c_str());*/
}
// End of WriteString
