#ifndef __FINANTIALLOGGERPARAMETERSREADER_H__
#define __FINANTIALLOGGERPARAMETERSREADER_H__


class CFinantialHistoryLogger;

class CFinantialLoggerParametersReader
{
	private:
	protected:
	public:
		// �����������
		CFinantialLoggerParametersReader() {};
		// ����������
		virtual ~CFinantialLoggerParametersReader() {};

		// ������ ������ ��� Logger'a
		virtual void ReadFinantialHistLoggerData(CFinantialHistoryLogger* pFinantialLogger) = 0;
};

#endif //__FINANTIALLOGGERPARAMETERSREADER_H__