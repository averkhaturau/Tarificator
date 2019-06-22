#ifndef __LOGGERWITHFULLFILENAME_H__
#define __LOGGERWITHFULLFILENAME_H__

#include "Logger.h"
#include "LoggerParametersReader.h"


// �� ���� ����������� CErrorsLogger, CKeyboardLogger � �����
// ����� ���� ������ ������� � ������ ������ ����� (�.�. ��
// �������� ����� � ��� �����, � ����)
class CLoggerWithFullFileName : public CLogger
{
	private:
		void DoDeleteEverything();
	protected:
		// ��� ���-�����
		FileName* m_pLogFileName;
		virtual CFileName DoGetFileName() {return *m_pLogFileName;};
	public:
		CLoggerWithFullFileName();
		virtual ~CLoggerWithFullFileName();

		// �������
		FileName* GetLogFileName() {return m_pLogFileName;};
};

#endif // __LOGGERWITHFULLFILENAME_H__