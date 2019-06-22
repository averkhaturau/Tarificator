#ifndef __LOGGER_H__
#define __LOGGER_H__


#include "NamesCollection.h"
#include "Exceptions.h"
#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"

class CDataReader;


class CLogger
{
	// Пишет в файл LogName. Не держит его открытым, поэтому можно
	// писАть в один файл несколькими экземплярами логгера, если
	// они работают в одном потоке.
	private:
		// Освобождает память из-под всего. Вызывается из конструктора
		// при возникновении исключения или из деструктора.
		void DoDeleteEverything();
	protected:
		typedef std::string CFileName;
		// Пачка мессаг, записывавшихся в лог
		CNamesCollection* m_pLogHistory;
		// Пачка мессаг, запись которых в лог запрещена
		CNamesCollection* m_pProhibited;
		bool m_bGenerateExceptionInAddLogEntry;

		// Записывают дату и время в строки
		void GetDate(std::string* pDateString);
		void GetTime(std::string* pTimeString);
		void DoWriteTimeStamp(FILE* pFile, CTimeContainer Time);
		// Записывает строку в файл
		void DoWriteString(FILE* pFile, const char* pCharArray);
		// Вызывается из AddLogEntry
		virtual void DoAddLogEntry(const char* pCharArray);
		// Вызывается из AddLogEntry. Возвращает true, если надо
		// писАть в лог.
		bool CheckLogHistoryEntry(const char* pCharArray);
		// Вызывается из AddLogEntry. Возвращает true, если можно
		// писАть в лог.
		bool CheckProhibition(const char* pCharArray);
		virtual void WriteString(FILE* pFile, const char* pCharArray) = 0;
		virtual CFileName DoGetFileName() = 0;
	public:
		// Конструктор
		CLogger();
		// Деструктор по умолчанию
		virtual ~CLogger();

		// Дописывает строку в лог. Делает после нее перевод строки.
		void AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates);

		// Обертки
		CNamesCollection* GetProhibitionsTable() {return m_pProhibited;};
};


#endif // __LOGGER_H__