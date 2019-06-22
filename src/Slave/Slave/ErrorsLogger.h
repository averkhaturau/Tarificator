#ifndef __ERRORSLOGGER_H__
#define __ERRORSLOGGER_H__

#include "LoggerWithFullFileName.h"


class CErrorsLogger : public CLoggerWithFullFileName
{
	private:
	protected:
		virtual void WriteString(FILE* pFile, const char* pCharArray);
	public:
		// �����������
		CErrorsLogger(CLoggerParametersReader* pReader)
		{
			m_bGenerateExceptionInAddLogEntry = 0;
				if (pReader)
					pReader->ReadErrorLoggerData(this);
		};
		// ����������
		virtual ~CErrorsLogger();

		// ����� �������� ��������
		void AddLogEntry(CAnyLogableException* pException);
		// ���������� ������ � ���. ������ ����� ��� ������� ������.
		void AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates);
};


#endif // __ERRORSLOGGER_H__