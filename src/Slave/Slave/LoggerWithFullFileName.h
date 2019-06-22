#ifndef __LOGGERWITHFULLFILENAME_H__
#define __LOGGERWITHFULLFILENAME_H__

#include "Logger.h"
#include "LoggerParametersReader.h"


// От него наследуются CErrorsLogger, CKeyboardLogger и потом
// могут быть другие логгеры с полным именем файла (т.е. им
// задается сразу и имя файла, и путь)
class CLoggerWithFullFileName : public CLogger
{
	private:
		void DoDeleteEverything();
	protected:
		// Имя лог-файла
		FileName* m_pLogFileName;
		virtual CFileName DoGetFileName() {return *m_pLogFileName;};
	public:
		CLoggerWithFullFileName();
		virtual ~CLoggerWithFullFileName();

		// Обертки
		FileName* GetLogFileName() {return m_pLogFileName;};
};

#endif // __LOGGERWITHFULLFILENAME_H__