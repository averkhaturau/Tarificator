#ifndef __LOGGERPARAMETERSREADER_H__
#define __LOGGERPARAMETERSREADER_H__


class CErrorsLogger;
class CKeyboardLogger;

// ��������� �������� ���������� Logger'�
class CLoggerParametersReader
{
	private:
	protected:
	public:
		// �����������
		CLoggerParametersReader() {};
		// ����������
		virtual ~CLoggerParametersReader() {};

		// ������ ������ ��� Logger'a
		virtual void ReadErrorLoggerData(CErrorsLogger* pLogger) = 0;
		virtual void ReadKeyboardLoggerData(CKeyboardLogger* pLogger) = 0;
};


#endif // __LOGGERPARAMETERSREADER_H__