#ifndef __ERRORSLOGGER_H__
#define __ERRORSLOGGER_H__

#include "LoggerWithFullFileName.h"


class CErrorsLogger : public CLoggerWithFullFileName
{
	private:
	protected:
		virtual void WriteString(FILE* pFile, const char* pCharArray);
	public:
		// Конструктор
		CErrorsLogger(CLoggerParametersReader* pReader)
		{
			m_bGenerateExceptionInAddLogEntry = 0;
				if (pReader)
					pReader->ReadErrorLoggerData(this);
		};
		// Деструктор
		virtual ~CErrorsLogger();

		// Чтобы вызывать напрямую
		void AddLogEntry(CAnyLogableException* pException);
		// Дописывает строку в лог. Делает после нее перевод строки.
		void AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates);
};


#endif // __ERRORSLOGGER_H__