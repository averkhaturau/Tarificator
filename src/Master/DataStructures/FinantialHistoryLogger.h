#ifndef __FINANTIALHISTORYLOGGER_H__
#define __FINANTIALHISTORYLOGGER_H__

#include "FinantialLoggerParametersReader.h"
#include "..\..\Slave\Slave\Logger.h"
//#include "ClubSettings\BusyIntervalHist.h"
#include "Saving\DayHistory.h"
#include "ClubSettings\ClubState.h"


// ����� ������� ���������� �������. ��� ���� �������������������
// ������ ���������. ��� ����� �� ��� �������� �� ���� ��������
// ������������� CBysuIntervalHist. ����, ����� � ����� DirectoryName
// ����������� ����� '\'.
class CFinantialHistoryLogger : public CLogger, public CDayHistory
{
	private:
	protected:
		CClubState* m_pState;

		// �����, ������������ ��� ����������� ���� � �������������
		// ����� �����, � ������� ��������� �������
		CTimeContainer m_TimeToDefineDate;
		// �������� �������� ��������� �� ������, ����� ���������� ���
		// ���-�����
		CMashineData* m_pMashineToDefineFileName;

		void DoDescribeInterval(CBusyInterval* pInterval, std::string* Str);

		virtual void WriteString(FILE* pFile, const char* pCharArray);

		// ��� �������� ��� �������
		CFileName m_DirectoryName;
		virtual CFileName DoGetFileName();
	public:
		// �����������
		CFinantialHistoryLogger(CFinantialLoggerParametersReader* pReader,
					CClubState* pState);
		// ����������
		virtual ~CFinantialHistoryLogger();

		// ����� �������� ��������
		//void AddLogEntry(CAnyLogableException* pException);
		// ���������� ������ � ���. ������ ����� ��� ������� ������.
		//void AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates);

		// �������
		CFileName* GetDirectoryName() {return &m_DirectoryName;};

		void WriteBusyIntervalHist(CBusyIntervalHist* pHist, CMashineData* pMashine);
		void WriteBusyIntervals(CBusyInterval* pNewInterval,
					CBusyInterval* pOldInterval, CMashineData* pMashine);
};

#endif // __FINANTIALHISTORYLOGGER_H__