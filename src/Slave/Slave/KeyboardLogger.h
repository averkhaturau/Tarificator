#ifndef __KEYBOARDLOGGER_H__
#define __KEYBOARDLOGGER_H__

#include "LoggerWithFullFileName.h"


class CKeyboardLogger : public CLoggerWithFullFileName
{
	private:
	protected:
		virtual void WriteString(FILE* pFile, const char* pCharArray);
	public:
		// �����������
		CKeyboardLogger(CLoggerParametersReader* pReader)
		{
			m_bGenerateExceptionInAddLogEntry = 0;
				if (pReader)
					pReader->ReadKeyboardLoggerData(this);
		};
		// ����������
		virtual ~CKeyboardLogger();
};


#endif // __KEYBOARDLOGGER_H__