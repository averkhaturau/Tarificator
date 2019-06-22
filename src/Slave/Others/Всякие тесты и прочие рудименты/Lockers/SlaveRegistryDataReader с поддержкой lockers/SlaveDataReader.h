#ifndef __SLAVEDATAREADER_H__
#define __SLAVEDATAREADER_H__

#include "NetworkParametersDataReader.h"
#include "LoggerParametersReader.h"
#include "DataReader.h"

#include <string>


// Predefinitions
class CLogger;
class CInputLocker;
class CSlaveManager;
class CDesktopEmulator;
class CKeyboardLocker;
class CNewUserDefiner;
class CRemainingTimeSlaveDescription;


class CSlaveDataReader : public CNetworkParametersDataReader,
			public CLoggerParametersReader, public CDataReader
{
	// ����������� �����-������ ��� CRegistryDataReader. �����, �����
	// ����� ���� �����, �� ����� ���������, ����������� ������
	// ���������� �� �����, �� ���� � �.�..

	private:
	protected:
	public:
		// �����������
		CSlaveDataReader() {};
		// ����������
		virtual ~CSlaveDataReader() {};

		// ������ ������ ��� �������
		virtual void ReadErrorLoggerData(CErrorsLogger* pLogger) = 0;

		// ������ ������ ��� InputLocker'�
		virtual void ReadInputLockerData(CInputLocker* pInputLocker) = 0;

		// ������ ������ ��� SlaveManager'a
		virtual void ReadSlaveManagerData(CSlaveManager* pSlaveManager) = 0;

		virtual void ReadDesktopEmulatorData(CDesktopEmulator* pEmulator, std::string* sUserName) = 0;

		virtual void ReadKeyboardLockerData(CKeyboardLocker* pLocker) = 0;

		virtual void ReadExchangeDesktopData(CDesktopEmulator* a_pEmulator) = 0;

		virtual void WriteExchangeDesktopData(CSlaveManager* a_pManager) = 0;
};


#endif // __SLAVEDATAREADER_H__