#ifndef __LOGGER_H__
#define __LOGGER_H__


#include "NamesCollection.h"
#include "Exceptions.h"
#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"

class CDataReader;


class CLogger
{
	// ����� � ���� LogName. �� ������ ��� ��������, ������� �����
	// ������ � ���� ���� ����������� ������������ �������, ����
	// ��� �������� � ����� ������.
	private:
		// ����������� ������ ��-��� �����. ���������� �� ������������
		// ��� ������������� ���������� ��� �� �����������.
		void DoDeleteEverything();
	protected:
		typedef std::string CFileName;
		// ����� ������, �������������� � ���
		CNamesCollection* m_pLogHistory;
		// ����� ������, ������ ������� � ��� ���������
		CNamesCollection* m_pProhibited;
		bool m_bGenerateExceptionInAddLogEntry;

		// ���������� ���� � ����� � ������
		void GetDate(std::string* pDateString);
		void GetTime(std::string* pTimeString);
		void DoWriteTimeStamp(FILE* pFile, CTimeContainer Time);
		// ���������� ������ � ����
		void DoWriteString(FILE* pFile, const char* pCharArray);
		// ���������� �� AddLogEntry
		virtual void DoAddLogEntry(const char* pCharArray);
		// ���������� �� AddLogEntry. ���������� true, ���� ����
		// ������ � ���.
		bool CheckLogHistoryEntry(const char* pCharArray);
		// ���������� �� AddLogEntry. ���������� true, ���� �����
		// ������ � ���.
		bool CheckProhibition(const char* pCharArray);
		virtual void WriteString(FILE* pFile, const char* pCharArray) = 0;
		virtual CFileName DoGetFileName() = 0;
	public:
		// �����������
		CLogger();
		// ���������� �� ���������
		virtual ~CLogger();

		// ���������� ������ � ���. ������ ����� ��� ������� ������.
		void AddLogEntry(const char* pCharArray, bool bIsWriteDuplicates);

		// �������
		CNamesCollection* GetProhibitionsTable() {return m_pProhibited;};
};


#endif // __LOGGER_H__