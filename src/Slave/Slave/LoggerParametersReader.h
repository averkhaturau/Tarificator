#ifndef __LOGGERPARAMETERSREADER_H__
#define __LOGGERPARAMETERSREADER_H__


class CErrorsLogger;
class CKeyboardLogger;

// Интерфейс читателя параметров Logger'а
class CLoggerParametersReader
{
	private:
	protected:
	public:
		// Конструктор
		CLoggerParametersReader() {};
		// Деструктор
		virtual ~CLoggerParametersReader() {};

		// Читает данные для Logger'a
		virtual void ReadErrorLoggerData(CErrorsLogger* pLogger) = 0;
		virtual void ReadKeyboardLoggerData(CKeyboardLogger* pLogger) = 0;
};


#endif // __LOGGERPARAMETERSREADER_H__