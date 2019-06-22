#include "stdafx.h"

#include "FinantialHistoryLogger.h"
#include "ClubSettings\IntervalAddition.h"


void CFinantialHistoryLogger::WriteString(FILE* pFile, const char* pCharArray)
{
	DoWriteTimeStamp(pFile, m_TimeToDefineDate);

	DoWriteString(pFile, pCharArray);

	// Перевод строки
	std::string StringToWrite = "\n";
	DoWriteString(pFile, StringToWrite.c_str());
}
// End of WriteString


CFinantialHistoryLogger::CFinantialHistoryLogger(CFinantialLoggerParametersReader* pReader,
			CClubState* pState)
{
		if (!pState)
			throw CAnyLogableException("NULL pState in CFinantialHistoryLogger::CFinantialHistoryLogger!", bDoNotWriteDuplicates);

	m_pState = pState;

	m_DirectoryName = "";

	m_TimeToDefineDate = 0;

	m_pMashineToDefineFileName = 0;

		if (pReader)
			pReader->ReadFinantialHistLoggerData(this);
}
// End of CFinantialHistoryLogger


CFinantialHistoryLogger::~CFinantialHistoryLogger()
{

}
// End of ~CFinantialHistoryLogger()


void CFinantialHistoryLogger::WriteBusyIntervalHist(CBusyIntervalHist* pHist,
			CMashineData* pMashine)
{
	CBusyInterval* pNewInterval = pHist->GetCurrentInterval(),
				*pOldInterval = pHist->GetLastButOne();

	WriteBusyIntervals(pNewInterval, pOldInterval, pMashine);
}
// End of WriteBusyIntervalHist


CFinantialHistoryLogger::CFileName CFinantialHistoryLogger::DoGetFileName()
{
		if ( (m_TimeToDefineDate == 0) || (m_pMashineToDefineFileName == 0) )
			throw CAnyLogableException("An error occured in CFinantialHistoryLogger::DoGetFileName() (programmer's mistake)", bDoNotWriteDuplicates);

	#ifdef _DEBUG
	std::string Str1 = m_DirectoryName;
	std::string Str2 = DateInStr(m_TimeToDefineDate);
	std::string Str3 = m_pMashineToDefineFileName->GetMashineName();
	#endif // _DEBUG

	return m_DirectoryName + DateInStr(m_TimeToDefineDate) + " - " + m_pMashineToDefineFileName->GetMashineName() + ".txt";
}
// End of DoGetFileName()


void CFinantialHistoryLogger::WriteBusyIntervals(CBusyInterval* pNewInterval,
			CBusyInterval* pOldInterval, CMashineData* pMashine)
{
		if (!pNewInterval)
			return;

	char cBuffer[50];
	std::string Str = "";

	Str += "\n\t";
	Str += pMashine->GetMashineName();
	Str += ":";
		if (pOldInterval)
		{
			Str += "\n\t\tстарый интервал: ";
			DoDescribeInterval(pOldInterval, &Str);
		}

	Str += "\n\t\tновый интервал: ";
	DoDescribeInterval(pNewInterval, &Str);

	Str += "\n\tДобавлено в кассу: ";
	CCurrency Result = pNewInterval->GetPrice();
		if (pOldInterval)
			Result -= pOldInterval->GetPrice();
	Str += _itoa(Result, &(cBuffer[0]), 10);
	Str += " рублей.\n";

	m_TimeToDefineDate = pNewInterval->GetCreationTime().GetTime();
	m_pMashineToDefineFileName = pMashine;

	// Собственно запись
	DoAddLogEntry(Str.c_str());

	m_TimeToDefineDate = 0;
	m_pMashineToDefineFileName = 0;
}
// End of WriteBusyIntervals


void CFinantialHistoryLogger::DoDescribeInterval(CBusyInterval* pInterval, std::string* pStr)
{
	char cBuffer[50];

	*pStr += IntervalAddition::DescribeInterval_In_Russian(pInterval);

	*pStr += ",\n\t\t\tтарифный план ";
	*pStr += ((*m_pState->GetTarifPlansCollection())[pInterval->GetTarifPlanNumber()]).GetName();

	*pStr += ",\n\t\t\tоператор ";
	*pStr += ((*m_pState->GetOperatorsCollection())[pInterval->GetOperatorNumber()]).GetName();

	*pStr += ",\n\t\t\tклиент ";
	*pStr += pInterval->GetClientName();

	*pStr += ",\n\t\t\tстоимость ";
	*pStr += _itoa(pInterval->GetPrice(), &(cBuffer[0]), 10);
	*pStr += " рублей.";
}
// End of DoDescribeInterval
