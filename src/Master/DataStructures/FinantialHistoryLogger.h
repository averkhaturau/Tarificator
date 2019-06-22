#ifndef __FINANTIALHISTORYLOGGER_H__
#define __FINANTIALHISTORYLOGGER_H__

#include "FinantialLoggerParametersReader.h"
#include "..\..\Slave\Slave\Logger.h"
//#include "ClubSettings\BusyIntervalHist.h"
#include "Saving\DayHistory.h"
#include "ClubSettings\ClubState.h"


// Класс логгера финансовой истории. Его надо проинициализировать
// только каталогом. Имя файла он сам генеряет из даты создания
// записываемого CBysuIntervalHist. Надо, чтобы в конце DirectoryName
// обязательно стоял '\'.
class CFinantialHistoryLogger : public CLogger, public CDayHistory
{
	private:
	protected:
		CClubState* m_pState;

		// Время, используемое для определения даты и следовательно
		// имени файла, в который созранять историю
		CTimeContainer m_TimeToDefineDate;
		// Временно хранится указатель на машину, чтобы определять имя
		// лог-файла
		CMashineData* m_pMashineToDefineFileName;

		void DoDescribeInterval(CBusyInterval* pInterval, std::string* Str);

		virtual void WriteString(FILE* pFile, const char* pCharArray);

		// Имя каталога для истории
		CFileName m_DirectoryName;
		virtual CFileName DoGetFileName();
	public:
		// Конструктор
		CFinantialHistoryLogger(CFinantialLoggerParametersReader* pReader,
					CClubState* pState);
		// Деструктор
		virtual ~CFinantialHistoryLogger();

		// Чтобы вызывать напрямую
		//void AddLogEntry(CAnyLogableException* pException);
		// Дописывает строку в лог. Делает после нее перевод строки.
		//void AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates);

		// Обертки
		CFileName* GetDirectoryName() {return &m_DirectoryName;};

		void WriteBusyIntervalHist(CBusyIntervalHist* pHist, CMashineData* pMashine);
		void WriteBusyIntervals(CBusyInterval* pNewInterval,
					CBusyInterval* pOldInterval, CMashineData* pMashine);
};

#endif // __FINANTIALHISTORYLOGGER_H__