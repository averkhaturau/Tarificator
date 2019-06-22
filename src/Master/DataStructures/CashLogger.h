#ifndef _LX_CASHLOGGER_H_INCLUDED_
#define _LX_CASHLOGGER_H_INCLUDED_

#include "..\..\Slave\Slave\LoggerWithFullFileName.h"
#include "CashStorer.h"

/*
	������ ��� ��������� ��������.
*/
class CCashLogger : public CLoggerWithFullFileName
{
	protected:
		virtual void WriteString(FILE* pFile, const char* pCharArray);
		virtual CFileName DoGetFileName() {return *m_pLogFileName;};

		// TimeStamp �������� �������. ���������, �.�. ��� ������ �������
		// �������� ��� � ������� WriteString.
		CTimeStorage m_TimeStamp;
	public:
		CCashLogger(){};
		virtual ~CCashLogger(){};

		// �������
		CTimeStorage* GetTimeStamp() {return &m_TimeStamp;};
		void SetTimeStamp(CTimeStorage& a_New) {m_TimeStamp = a_New;};
};

#endif //_LX_CASHLOGGER_H_INCLUDED_
