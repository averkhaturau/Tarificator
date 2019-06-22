#include "stdafx.h"

#include "Logger.h"
#include "SlaveRegistryDataReader.h"


CLogger::CLogger()
{
	// Чтобы не произошло ложного убивания, если произойдет исключение
	m_pLogHistory = 0;
	m_pProhibited = 0;

	m_bGenerateExceptionInAddLogEntry = 0;

		try
		{
			m_pLogHistory = new CNamesCollection;
			m_pProhibited = new CNamesCollection;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("Can't create logger", bWriteDuplicates);
		}
}
// End of CLogger()


CLogger::~CLogger()
{
	DoDeleteEverything();
}
// End of ~CLogger()


void CLogger::DoDeleteEverything()
{
		if (m_pLogHistory)
		{
			delete m_pLogHistory;
			m_pLogHistory = 0;
		}
		if (m_pProhibited)
		{
			delete m_pProhibited;
			m_pProhibited = 0;
		}
}
// End of DoDeleteEverything()


bool CLogger::CheckLogHistoryEntry(const char* pCharArray)
{
	bool bIsStringInHistory = false;

		// На всякий случай
		try
		{
				for (int i = 0; i < m_pLogHistory->size(); i++)
				{
						if ( !strcmp( ((*m_pLogHistory)[i]).c_str(), pCharArray ) )
						{
							bIsStringInHistory = true;
						}
				}

				if ( !bIsStringInHistory )
				{
					m_pLogHistory->AddName(pCharArray);
				}
		}
		catch(...)
		{

		}

		if ( bIsStringInHistory )
		{
			return false;
		}
		else
		{
			return true;
		}
}
// End of CheckLogHistoryEntry


void CLogger::AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates)
{
		// Иначе - вылетает, если еще не прочиталось из реестра имя файла
		if ( !(DoGetFileName().size()) )
			return;

	bool bCheckHistory = CheckLogHistoryEntry(pCharArray);
	bool bProhibited = CheckProhibition(pCharArray);
		if ( (bCheckHistory || bIsWriteDuplicates) && (bProhibited) )
		{
			DoAddLogEntry(pCharArray);
		}
}
// End of AddLogEntry


void CLogger::GetDate(std::string* pDateString)
{
	// Получаю размер iDateStringSize
	int iDateStringSize = GetDateFormat(LOCALE_SYSTEM_DEFAULT,
				LOCALE_NOUSEROVERRIDE, NULL, NULL, pDateString->begin(), NULL);

	pDateString->resize(iDateStringSize);

	GetDateFormat(LOCALE_SYSTEM_DEFAULT,
				LOCALE_NOUSEROVERRIDE, NULL, NULL, pDateString->begin(), iDateStringSize);

	pDateString->resize(pDateString->size() + 1);
	(*pDateString)[pDateString->size() - 2] = ' ';
	(*pDateString)[pDateString->size() - 1] = '\0';
}
// End of GetDate


void CLogger::GetTime(std::string* pTimeString)
{
	// Получаю размер iTimeStringSize
	int iTimeStringSize = GetTimeFormat(LOCALE_SYSTEM_DEFAULT,
				TIME_FORCE24HOURFORMAT, NULL, NULL, pTimeString->begin(), NULL);

	pTimeString->resize(iTimeStringSize);

	GetTimeFormat(LOCALE_SYSTEM_DEFAULT,
				TIME_FORCE24HOURFORMAT, NULL, NULL, pTimeString->begin(), iTimeStringSize);

	pTimeString->resize(pTimeString->size() + 1);
	(*pTimeString)[pTimeString->size() - 2] = ' ';
	(*pTimeString)[pTimeString->size() - 1] = '\0';
}
// End of GetTime


void CLogger::DoWriteString(FILE* pFile, const char* pCharArray)
{
		if (!pFile)
			return;

	fwrite(pCharArray, 1, strlen(pCharArray), pFile);
}
// End of WriteString


bool CLogger::CheckProhibition(const char* pCharArray)
{
	bool bIsStringProhibited = false;

		// На всякий случай
		try
		{
				for (int i = 0; i < m_pProhibited->size(); i++)
				{
						if ( !strcmp( ((*m_pProhibited)[i]).c_str(), pCharArray ) )
						{
							bIsStringProhibited = true;
						}
				}
		}
		catch(...)
		{

		}

	return !bIsStringProhibited;
}
// End of CheckProhibition


void CLogger::DoAddLogEntry(const char* pCharArray)
{
		// На всякий случай, чтобы из-за какой-нить фигни прога не вылетела
		try
		{
			FILE* pLogFile;
			// Открываю файл для дополнения
			std::string Name = DoGetFileName();

				if (Name == "")
					return;

			pLogFile = fopen( (char*)(Name.c_str()), "a" );

				if (!pLogFile)
					throw CAnyLogableException((std::string)"can't open log file name (" + Name + ")", bDoNotWriteDuplicates);

			WriteString(pLogFile, pCharArray);

			// Чтобы очистить буфер. Если линкеру дать команду прилинковать
			// COMMODE.OBJ, то будет опустошать даже файл-кэш винды
			_flushall();

			fclose(pLogFile);
		}
		catch(CAnyLogableException& Error)
		{
				if (m_bGenerateExceptionInAddLogEntry)
				{
					std::string Str = "An error occured in CLogger::DoAddLogEntry: ";
					Str += Error.what();
					throw CAnyLogableException(Str, bDoNotWriteDuplicates);
				}
		}
		catch(...)
		{
			// Тут часто даже делать ничего не надо - нЕкому будет записывать
			// сообщения об ошибках
				if (m_bGenerateExceptionInAddLogEntry)
					throw CAnyLogableException("An unknown error occured in CLogger::DoAddLogEntry", bDoNotWriteDuplicates);
		}
}
// End of DoAddLogEntry


void CLogger::DoWriteTimeStamp(FILE* pFile, CTimeContainer Time)
{
	// Дата
	std::string DateString;
	GetDate(&DateString);
	DoWriteString(pFile, DateString.c_str());

	// Время
	std::string TimeString;
	GetTime(&TimeString);
	DoWriteString(pFile, TimeString.c_str());
}
