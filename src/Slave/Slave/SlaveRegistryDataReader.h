#ifndef __SLAVEREGISTRYDATAREADER_H__
#define __SLAVEREGISTRYDATAREADER_H__


#include "SlaveDataReader.h"
#include "RegistryDataReader.h"
#include "RegistryDataWriter.h"
#include "NewUserDefiner.h"


class CSlaveRegistryDataReader : public CRegistryDataReader,
			public CSlaveDataReader,
			public CRegistryDataWriter
{
	// Класс для заполнения начльных значений полей экземпляров классов,
	// используемых в дальнейшем для работы

	private:
	protected:
		// Читает из реестра данные для логгера
		void DoReadErrorLoggerRegistryData(CErrorsLogger* pLogger, PHKEY phkKey);

		void DoReadKeyboardLoggerRegistryData(CKeyboardLogger* pLogger, PHKEY phkKey);

		// Читает из реестра данные для TCP_IP_Sender'а
		void DoReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender, PHKEY phkKey);

		// Читает из реестра данные для TCP_IP_Listener'а
		void DoReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener, PHKEY phkKey);

		// Читает параметры стандартные для всех SocketHolder'ов данные
		void DoReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder, PHKEY phkKey);

		// Читает из реестра данные для TCP_IP_Receiver'а
		void DoReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pReceiver, PHKEY phkKey);

		void DoReadSlaveManagerData(CSlaveManager* pManager, PHKEY phkKey);

		void DoReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder, PHKEY phkKey);

		void DoReadDesktopEmulatorData(CDesktopEmulator* pEmulator, PHKEY phkKey, std::string* pUserName);

		void DoReadDesktopErrorLoggerData(CErrorsLogger* pLogger, PHKEY phkKey);

		//void DoWriteUserName(LPCTSTR a_psName, PHKEY phkKey);

		//void DoReadUserName(std::string* a_psName, PHKEY phkKey);

		void DoReadExchangeDesktopData(CDesktopEmulator* a_pEmulator, PHKEY a_phkKey);

		void DoWriteExchangeDesktopData(CSlaveManager* a_pManager, PHKEY a_phkKey);
	public:
		// Конструктор по умолчанию
		CSlaveRegistryDataReader();
		// Деструктор
		virtual ~CSlaveRegistryDataReader();

		// Читает из реестра данные для логгера ошибок
		virtual void ReadErrorLoggerData(CErrorsLogger* pLogger);

		// Читает из реестра данные для логгера клавиатуры
		virtual void ReadKeyboardLoggerData(CKeyboardLogger* pLogger);

		// Читает из реестра данные для TCP_IP_Sender'а
		virtual void ReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender);

		// Читает из реестра данные для TCP_IP_Listener'а
		virtual void ReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener);

		// Читает параметры SocketHolder'a
		virtual void ReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder);

		// Читает из реестра данные для SlaveManager'a
		virtual void ReadSlaveManagerData(CSlaveManager* pSlaveManager);

		// Читает из реестра данные для TCP_IP_Receiver'а
		virtual void ReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pTCP_IP_Receiver);

		// Читает из реестра данные для SocketHolder'а, по которому надо будет
		// коннектиться, т.е. стандартные для всех SocketHolder'ов данные
		// и еще MasterPort и MasterAddress
		virtual void ReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder);

		// Читает из реестра данные для SocketHolder'а, по которому мастер
		// будет коннектиться к slave. Тут это просто затычка.
		virtual void ReadMasterConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder) {};

		// После него прочитанный путь обязательно заканчивается слэшем
		virtual void ReadDesktopEmulatorData(CDesktopEmulator* pEmulator, std::string* pUserName);

		// Читает из реестра данные для десктопного логгера ошибок 
		void ReadDesktopErrorLoggerData(CErrorsLogger* pLogger);

		virtual void ReadExchangeDesktopData(CDesktopEmulator* a_pEmulator);

		virtual void WriteExchangeDesktopData(CSlaveManager* a_pManager);

		//void WriteUserName(LPCTSTR a_psName);

		//void ReadUserName(std::string* a_psName);
};


#endif // __SLAVEREGISTRYDATAREADER_H__