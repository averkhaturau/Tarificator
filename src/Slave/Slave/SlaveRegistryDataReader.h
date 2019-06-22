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
	// ����� ��� ���������� �������� �������� ����� ����������� �������,
	// ������������ � ���������� ��� ������

	private:
	protected:
		// ������ �� ������� ������ ��� �������
		void DoReadErrorLoggerRegistryData(CErrorsLogger* pLogger, PHKEY phkKey);

		void DoReadKeyboardLoggerRegistryData(CKeyboardLogger* pLogger, PHKEY phkKey);

		// ������ �� ������� ������ ��� TCP_IP_Sender'�
		void DoReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender, PHKEY phkKey);

		// ������ �� ������� ������ ��� TCP_IP_Listener'�
		void DoReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener, PHKEY phkKey);

		// ������ ��������� ����������� ��� ���� SocketHolder'�� ������
		void DoReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder, PHKEY phkKey);

		// ������ �� ������� ������ ��� TCP_IP_Receiver'�
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
		// ����������� �� ���������
		CSlaveRegistryDataReader();
		// ����������
		virtual ~CSlaveRegistryDataReader();

		// ������ �� ������� ������ ��� ������� ������
		virtual void ReadErrorLoggerData(CErrorsLogger* pLogger);

		// ������ �� ������� ������ ��� ������� ����������
		virtual void ReadKeyboardLoggerData(CKeyboardLogger* pLogger);

		// ������ �� ������� ������ ��� TCP_IP_Sender'�
		virtual void ReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender);

		// ������ �� ������� ������ ��� TCP_IP_Listener'�
		virtual void ReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener);

		// ������ ��������� SocketHolder'a
		virtual void ReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder);

		// ������ �� ������� ������ ��� SlaveManager'a
		virtual void ReadSlaveManagerData(CSlaveManager* pSlaveManager);

		// ������ �� ������� ������ ��� TCP_IP_Receiver'�
		virtual void ReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pTCP_IP_Receiver);

		// ������ �� ������� ������ ��� SocketHolder'�, �� �������� ���� �����
		// ������������, �.�. ����������� ��� ���� SocketHolder'�� ������
		// � ��� MasterPort � MasterAddress
		virtual void ReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder);

		// ������ �� ������� ������ ��� SocketHolder'�, �� �������� ������
		// ����� ������������ � slave. ��� ��� ������ �������.
		virtual void ReadMasterConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder) {};

		// ����� ���� ����������� ���� ����������� ������������� ������
		virtual void ReadDesktopEmulatorData(CDesktopEmulator* pEmulator, std::string* pUserName);

		// ������ �� ������� ������ ��� ����������� ������� ������ 
		void ReadDesktopErrorLoggerData(CErrorsLogger* pLogger);

		virtual void ReadExchangeDesktopData(CDesktopEmulator* a_pEmulator);

		virtual void WriteExchangeDesktopData(CSlaveManager* a_pManager);

		//void WriteUserName(LPCTSTR a_psName);

		//void ReadUserName(std::string* a_psName);
};


#endif // __SLAVEREGISTRYDATAREADER_H__