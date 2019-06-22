#include "stdafx.h"

#include "ErrorsLogger.h"


CErrorsLogger::~CErrorsLogger()
{

}
// End of ~CErrorsLogger()


void CErrorsLogger::AddLogEntry(CAnyLogableException* pException)
{
		if (!pException)
			return;

		// ����� - ��������, ���� ��� �� ����������� �� ������� ��� m_pLogFileName
		/*if ( !(m_pLogFileName->size()) )
			return;

	bool bCheckHistory = CheckLogHistoryEntry(pException->what());
	bool bNotProhibited = CheckProhibition(pException->what());
		if ( (bCheckHistory || pException->GetWriteDuplicatesToLog()) && (bNotProhibited) )
		{
			DoAddLogEntry(pException->what());
		}*/
	CLogger::AddLogEntry(pException->what(), pException->GetWriteDuplicatesToLog());
}
// End of AddLogEntry


void CErrorsLogger::AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates)
{
	CLogger::AddLogEntry(pCharArray, bIsWriteDuplicates);
}
// End of AddLogEntry


void CErrorsLogger::WriteString(FILE* pFile, const char* pCharArray)
{
	DoWriteTimeStamp(pFile, CurrentTime().GetTime());

	// ���������� ��������� �� ������
	DoWriteString(pFile, pCharArray);

	// ������� ������
	std::string StringToWrite = "\n";
	DoWriteString(pFile, StringToWrite.c_str());
}
// End of WriteString()
