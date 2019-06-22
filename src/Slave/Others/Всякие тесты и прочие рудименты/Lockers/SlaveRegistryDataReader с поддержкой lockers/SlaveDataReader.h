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
	// Абстрактный класс-предок для CRegistryDataReader. Нужен, чтобы
	// можно было потом, не меняя структуру, реализовать чтение
	// параметров из файла, по сети и т.п..

	private:
	protected:
	public:
		// Конструктор
		CSlaveDataReader() {};
		// Деструктор
		virtual ~CSlaveDataReader() {};

		// Читает данные для логгера
		virtual void ReadErrorLoggerData(CErrorsLogger* pLogger) = 0;

		// Читает данные для InputLocker'а
		virtual void ReadInputLockerData(CInputLocker* pInputLocker) = 0;

		// Читает данные для SlaveManager'a
		virtual void ReadSlaveManagerData(CSlaveManager* pSlaveManager) = 0;

		virtual void ReadDesktopEmulatorData(CDesktopEmulator* pEmulator, std::string* sUserName) = 0;

		virtual void ReadKeyboardLockerData(CKeyboardLocker* pLocker) = 0;

		virtual void ReadExchangeDesktopData(CDesktopEmulator* a_pEmulator) = 0;

		virtual void WriteExchangeDesktopData(CSlaveManager* a_pManager) = 0;
};


#endif // __SLAVEDATAREADER_H__