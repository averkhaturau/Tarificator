#include "stdafx.h"

#include "CashLogger.h"
//#include "SlaveRegistryDataReader.h"


void CCashLogger::WriteString(FILE* pFile, const char* pCharArray)
{
	DoWriteTimeStamp(pFile, m_TimeStamp.GetTime());

	DoWriteString(pFile, pCharArray);

	// ������� ������
	std::string StringToWrite = "\n";
	DoWriteString(pFile, StringToWrite.c_str());
}
// End of WriteString

