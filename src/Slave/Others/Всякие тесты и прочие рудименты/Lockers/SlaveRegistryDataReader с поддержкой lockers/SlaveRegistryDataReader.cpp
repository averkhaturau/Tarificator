#include "stdafx.h"

#include "SlaveRegistryDataReader.h"
#include "Logger.h"
#include "ErrorsLogger.h"
#include "KeyboardLogger.h"
#include "InputLocker.h"
#include "TCP_IP_Sender.h"
#include "TCP_IP_Listener.h"
#include "TCP_IP_SocketHolder.h"
#include "TCP_IP_Receiver.h"
#include "SlaveManager.h"
#include "..\Desktop\DesktopEmulator.h"
#include "Constants.h"
#include "KeyboardLocker.h"


CSlaveRegistryDataReader::CSlaveRegistryDataReader()
{

}
// End of CSlaveRegistryDataReader


CSlaveRegistryDataReader::~CSlaveRegistryDataReader()
{

}
// End of ~CSlaveRegistryDataReader()


void CSlaveRegistryDataReader::ReadErrorLoggerData(CErrorsLogger* pLogger)
{
		if (!pLogger)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadErrorLoggerRegistryData(pLogger, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadLoggerData", bDoNotWriteDuplicates);
		}
}
// End of ReadErrorLoggerData


void CSlaveRegistryDataReader::DoReadErrorLoggerRegistryData(CErrorsLogger* pLogger, PHKEY phkKey)
{
	std::string LogFileNameString = "LogFileName";
		if (pLogger->GetLogFileName())
			DoReadOneRegistryName( phkKey, LogFileNameString, *(pLogger->GetLogFileName()) );
}
// End of DoReadErrorLoggerRegistryData


void CSlaveRegistryDataReader::DoReadInputLockerData(CInputLocker* pInputLocker, PHKEY phkKey)
{
		if (pInputLocker->GetHookProceduresDLLNames())
		{
			DWORD dwProceduresDLLFilesNumber;
			DoReadRegistryNumber(phkKey, (std::string)"ProceduresDLLNumber", dwProceduresDLLFilesNumber);

				if (dwProceduresDLLFilesNumber >= 10)
					throw CAnyLogableException("Too many DLL Files Number (see registry)", bDoNotWriteDuplicates);

			pInputLocker->GetHookProceduresDLLNames()->resize(dwProceduresDLLFilesNumber);

			std::string NamesString = "ProceduresDLLFileName ";
				for (SizeType i = 0; i < dwProceduresDLLFilesNumber; i++)
				{
					NamesString[21] = (i + 48);
					DoReadOneRegistryName(phkKey, NamesString, (*pInputLocker->GetHookProceduresDLLNames())[i]);
				}
		}
}
// End of DoReadInputLockerData


void CSlaveRegistryDataReader::ReadInputLockerData(CInputLocker* pInputLocker)
{
		if (!pInputLocker)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadInputLockerData(pInputLocker, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadLoggerData", bDoNotWriteDuplicates);
		}
}
// End of ReadInputLockerData


void CSlaveRegistryDataReader::ReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender)
{
		if (!pTCP_IP_Sender)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadTCP_IP_SenderData(pTCP_IP_Sender, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadTCP_IP_SenderData", bDoNotWriteDuplicates);
		}
}
// End of ReadTCP_IP_SenderData


void CSlaveRegistryDataReader::DoReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender, PHKEY phkKey)
{
	std::string sPortToSendTo = "PortToSendTo";
	DWORD dwPort;
	DoReadRegistryNumber(phkKey, sPortToSendTo, dwPort);

	u_short usPort = dwPort & 0xffff;
	//pTCP_IP_Sender->SetPortToConnectTo(usPort);
}
// End of DoReadTCP_IP_SenderData


void CSlaveRegistryDataReader::ReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder)
{
		if (!pHolder)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadCommonTCP_IP_SocketHolderData(pHolder, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadCommonTCP_IP_SocketHolderData", bDoNotWriteDuplicates);
		}
}
// End of ReadTCP_IP_SocketHolderData


void CSlaveRegistryDataReader::DoReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder, PHKEY phkKey)
{
	DWORD dwReadData;

	std::string sConnectTimeOut = "ConnectTimeOut";
	DoReadRegistryNumber(phkKey, sConnectTimeOut, dwReadData);
	pHolder->GetConnectManager()->GetTimeOutManager()->SetTimeOut((A_Second.GetTime() * dwReadData) / 1000);
		if (dwReadData)
			pHolder->GetConnectManager()->GetTimeOutManager()->SetEnabled(true);
		else
			pHolder->GetConnectManager()->GetTimeOutManager()->SetEnabled(false);

	std::string sConnectRetriesPeriod = "ConnectRetriesPeriod";
	DoReadRegistryNumber(phkKey, sConnectRetriesPeriod, dwReadData);

	pHolder->GetConnectionRetriesManager()->SetTimeOut((A_Second.GetTime() * dwReadData) / 1000);
		if (dwReadData)
			pHolder->GetConnectionRetriesManager()->SetEnabled(true);
		else
			pHolder->GetConnectionRetriesManager()->SetEnabled(false);

	std::string sOpenConnectionTimeOut = "OpenConnectionTimeOut";
	DoReadRegistryNumber(phkKey, sOpenConnectionTimeOut, dwReadData);

	pHolder->GetOpenConnectionManager()->SetTimeOut((A_Second.GetTime() * dwReadData) / 1000);
		if (dwReadData)
			pHolder->GetOpenConnectionManager()->SetEnabled(true);
		else
			pHolder->GetOpenConnectionManager()->SetEnabled(false);
}
// End of DoReadTCP_IP_SocketHolderData


void CSlaveRegistryDataReader::ReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder)
{
		if (!pHolder)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadSlaveConnectedSocketHolder(pHolder, &hkKey);
			DoReadCommonTCP_IP_SocketHolderData(pHolder, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadCommonTCP_IP_SocketHolderData", bDoNotWriteDuplicates);
		}
}
// End of ReadSlaveConnectedSocketHolder


void CSlaveRegistryDataReader::DoReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder, PHKEY phkKey)
{
	std::string sMasterPort = "MasterPort";
	DWORD dwReadData;
	DoReadRegistryNumber(phkKey, sMasterPort, dwReadData);

	u_short usPort = dwReadData & 0xffff;
	pHolder->SetPortToConnectTo(usPort);

	std::string sMasterAddress = "MasterAddress";
	DoReadRegistryNumber(phkKey, sMasterAddress, dwReadData);
	pHolder->SetAddressToConnectTo(dwReadData);
}
// End of ReadSlaveConnectedSocketHolder


void CSlaveRegistryDataReader::ReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener)
{
		if (!pTCP_IP_Listener)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadTCP_IP_ListenerData(pTCP_IP_Listener, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadTCP_IP_ListenerData", bDoNotWriteDuplicates);
		}
}
// End of ReadTCP_IP_ListenerData


void CSlaveRegistryDataReader::DoReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener, PHKEY phkKey)
{
	std::string sPortToListen = "PortToListen";
	DWORD dwPort;
	DoReadRegistryNumber(phkKey, sPortToListen, dwPort);

	u_short usPort = dwPort & 0xffff;
	pTCP_IP_Listener->SetPortToListen(usPort);
}
// End of DoReadTCP_IP_ListenerData


void CSlaveRegistryDataReader::ReadSlaveManagerData(CSlaveManager* pSlaveManager)
{
		if (!pSlaveManager)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadSlaveManagerData(pSlaveManager, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadSlaveManagerData", bDoNotWriteDuplicates);
		}
}
// End of ReadSlaveManagerData


void CSlaveRegistryDataReader::DoReadSlaveManagerData(CSlaveManager* pManager, PHKEY phkKey)
{
	std::string sTimerPeriod = "TimerPeriod";
	DWORD dwValue;
	DoReadRegistryNumber(phkKey, sTimerPeriod, dwValue);

	pManager->SetTimerPeriod(dwValue);

	std::string sNoMasterAnswerPeriod = "NoMasterAnswerPeriod";
	DoReadRegistryNumber(phkKey, sNoMasterAnswerPeriod, dwValue);

	pManager->GetPermissionManager()->SetTimeOut((A_Second.GetTime() * dwValue) / 1000);
		if (dwValue)
			pManager->GetPermissionManager()->SetEnabled(true);
		else
			pManager->GetPermissionManager()->SetEnabled(false);

	std::string sCheckStatePeriod = "CheckStatePeriod";
	DoReadRegistryNumber(phkKey, sCheckStatePeriod, dwValue);

	pManager->GetCheckStateManager()->SetTimeOut((A_Second.GetTime() * dwValue) / 1000);
		if (dwValue)
			pManager->GetCheckStateManager()->SetEnabled(true);
		else
			pManager->GetCheckStateManager()->SetEnabled(false);

	std::string sLateWarn = "LateWarn";
	DoReadRegistryNumber(phkKey, sLateWarn, dwValue);
	pManager->GetLateWarnManager()->SetTimeOut((A_Second.GetTime() * dwValue) / 1000);

	std::string sEarlyWarn = "EarlyWarn";
	DoReadRegistryNumber(phkKey, sEarlyWarn, dwValue);
	pManager->GetEarlyWarnManager()->SetTimeOut((A_Second.GetTime() * dwValue) / 1000);

		if (pManager->GetSoundManager())
		{
			std::string sEarlyWarnName = "EarlyWarnName";
			DoReadOneRegistryName( phkKey, sEarlyWarnName, pManager->GetSoundManager()->GetEarlyWarnName() );

			std::string sLateWarnName = "LateWarnName";
			DoReadOneRegistryName( phkKey, sLateWarnName, pManager->GetSoundManager()->GetLateWarnName() );

			std::string sFinishedName = "FinishedName";
			DoReadOneRegistryName( phkKey, sFinishedName, pManager->GetSoundManager()->GetFinishedName() );
		}

	std::string DesktopExecutablePath = "DesktopExecutablePath";
		if (pManager->GetDesktopExecutablePath())
			DoReadOneRegistryName( phkKey, DesktopExecutablePath, *(pManager->GetDesktopExecutablePath()) );

	std::string sSuperUsersNamesNumberName = "SuperUserNamesNumber";
	DWORD dwNumber = 0;
	DoReadRegistryNumber(phkKey, sSuperUsersNamesNumberName, dwNumber);
	pManager->GetSuperUsersNamesCollection()->resize(dwNumber);
		for (int i = 0; i < dwNumber; ++i)
		{
			DoReadOneRegistryName(phkKey, GenerateName("SuperUserName", i, 2), (*pManager->GetSuperUsersNamesCollection())[i]);
		}

	/*std::string sRestrictedUsersNamesNumberName = "RestrictedUserNamesNumber";
	dwNumber = 0;
	DoReadRegistryNumber(phkKey, sRestrictedUsersNamesNumberName, dwNumber);
	pManager->GetRestrictedUsersNamesCollection()->resize(dwNumber);
		for (i = 0; i < dwNumber; ++i)
		{
			DoReadOneRegistryName(phkKey, GenerateName("RestrictedUserName", i, 2), (*pManager->GetRestrictedUsersNamesCollection())[i]);
		}*/
}
// End of DoReadSlaveManagerData


void CSlaveRegistryDataReader::ReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pTCP_IP_Receiver)
{
		if (!pTCP_IP_Receiver)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadTCP_IP_ReceiverData(pTCP_IP_Receiver, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadTCP_IP_ReceiverData", bDoNotWriteDuplicates);
		}
}
// End of ReadTCP_IP_ReceiverData


void CSlaveRegistryDataReader::DoReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pReceiver, PHKEY phkKey)
{
	std::string sReceiveTimeOut = "ReceiveTimeOut";
	DWORD dwValue;
	DoReadRegistryNumber(phkKey, sReceiveTimeOut, dwValue);

	pReceiver->SetReceiveTimeOut((A_Second.GetTime() * dwValue) / 1000);

		if (dwValue)
			pReceiver->SetHasReceiveTimeOut(true);
		else
			pReceiver->SetHasReceiveTimeOut(false);
}
// End of DoReadTCP_IP_ReceiverData


void CSlaveRegistryDataReader::ReadKeyboardLoggerData(CKeyboardLogger* pLogger)
{
		if (!pLogger)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadKeyboardLoggerRegistryData(pLogger, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadLoggerData", bDoNotWriteDuplicates);
		}
}
// End of ReadKeyboardLoggerData


void CSlaveRegistryDataReader::DoReadKeyboardLoggerRegistryData(CKeyboardLogger* pLogger, PHKEY phkKey)
{
	std::string LogFileNameString = "KeyLogFileName";
		if (pLogger->GetLogFileName())
			DoReadOneRegistryName( phkKey, LogFileNameString, *(pLogger->GetLogFileName()) );
}
// End of DoReadKeyboardLoggerRegistryData


void CSlaveRegistryDataReader::ReadDesktopEmulatorData(CDesktopEmulator* pEmulator, std::string* pUserName)
{
		if (!pEmulator)
			return;

	HKEY hkKey;
		try
		{
			std::string sSavedKeyName = *GetSubKeyName();
			HKEY hSavedKey = GetKey();

			/**GetSubKeyName() = sShellFoldersRegistryPath;
			SetKey(HKEY_CURRENT_USER);*/

			SetKey(HKEY_LOCAL_MACHINE);
			*GetSubKeyName() = sSlaveRegistryPath;
			//*GetSubKeyName() = "Security";
			SetSecurityAccessMask(KEY_READ);

			DoOpenRegistryKey(&hkKey);

			SetKey(hSavedKey);
			*GetSubKeyName() = sSavedKeyName;

			DoReadDesktopEmulatorData(pEmulator, &hkKey, pUserName);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadDesktopEmulatorData", bDoNotWriteDuplicates);
		}
}
// End of ReadDesktopEmulatorData


void CSlaveRegistryDataReader::DoReadDesktopEmulatorData(CDesktopEmulator* pEmulator, PHKEY phkKey, std::string* pUserName)
{
	std::string sIconsValueName = "Icons_";
	std::string sSpecialIconsValueName = "SpecialIcons_";
	std::string sPreliminaryIconsValueName = "PreliminaryIcons_";
	std::string sOnlyOneApplication = "OnlyOneApplication_";

	sIconsValueName += *pUserName;
	sSpecialIconsValueName += *pUserName;
	sPreliminaryIconsValueName += *pUserName;
	sOnlyOneApplication += *pUserName;

		if (pEmulator->GetIconsWindow()->GetIconsFolderPath())
		{
			DoReadRegistryPath(phkKey, sIconsValueName, pEmulator->GetIconsWindow()->GetIconsFolderPath(), true);
		}

		if (pEmulator->GetSpecialIconsWindow()->GetIconsFolderPath())
		{
			DoReadRegistryPath(phkKey, sSpecialIconsValueName, pEmulator->GetSpecialIconsWindow()->GetIconsFolderPath(), true);
		}

		if (pEmulator->GetPreliminaryIconsFolderPath())
			DoReadRegistryPath(phkKey, sPreliminaryIconsValueName, pEmulator->GetPreliminaryIconsFolderPath(), true);

		if (pEmulator->GetRunnerName())
			DoReadOneRegistryName(phkKey, "RunnerName", *pEmulator->GetRunnerName());

	DWORD dwOnlyOneApplication = 0;
	DoReadRegistryNumber(phkKey, sOnlyOneApplication, dwOnlyOneApplication);
	pEmulator->SetOnlyOneApplication(dwOnlyOneApplication);
}
// End of DoReadDesktopEmulatorData


void CSlaveRegistryDataReader::ReadKeyboardLockerData(CKeyboardLocker* pLocker)
{
		if (!pLocker)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadKeyboardLockerData(pLocker, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadKeyboardLockerData", bDoNotWriteDuplicates);
		}
}
// End of ReadKeyboardLockerData


void CSlaveRegistryDataReader::DoReadKeyboardLockerData(CKeyboardLocker* pLocker, PHKEY phkKey)
{
	DWORD dwIsSpecialKeysAlwaysLocked;
	DoReadRegistryNumber(phkKey, "IsSpecialKeysAlwaysLocked", dwIsSpecialKeysAlwaysLocked);

	pLocker->SetIsSpecialKeysAlwaysLocked(dwIsSpecialKeysAlwaysLocked);
}
// End of DoReadKeyboardLockerData


/*void CSlaveRegistryDataReader::WriteUserName(LPCTSTR a_psName)
{
		if (!a_psName)
			return;

	HKEY hkKey;
		try
		{
			std::string sSavedKeyName = *GetSubKeyName();
			HKEY hSavedKey = GetKey();
			REGSAM SavedSam = GetSecurityAccessMask();

			SetKey(HKEY_LOCAL_MACHINE);
			*GetSubKeyName() = sUserNamePath;
			SetSecurityAccessMask(KEY_READ | KEY_WRITE);

			DoOpenRegistryKey(&hkKey);

			SetKey(hSavedKey);
			*GetSubKeyName() = sSavedKeyName;
			SetSecurityAccessMask(SavedSam);

			DoWriteUserName(a_psName, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadDesktopEmulatorData", bDoNotWriteDuplicates);
		}
}
// End of WriteUserName


void CSlaveRegistryDataReader::DoWriteUserName(LPCTSTR a_psName, PHKEY phkKey)
{
	DoWriteRegistryString(phkKey, "UserName", (std::string)a_psName);
}
// End of DoWriteUserName


void CSlaveRegistryDataReader::ReadUserName(std::string* a_psName)
{
		if (!a_psName)
			return;

	HKEY hkKey;
		try
		{
			std::string sSavedKeyName = *GetSubKeyName();
			HKEY hSavedKey = GetKey();
			REGSAM SavedSam = GetSecurityAccessMask();

			SetKey(HKEY_LOCAL_MACHINE);
			*GetSubKeyName() = sUserNamePath;
			SetSecurityAccessMask(KEY_READ);

			DoOpenRegistryKey(&hkKey);

			SetKey(hSavedKey);
			*GetSubKeyName() = sSavedKeyName;
			SetSecurityAccessMask(SavedSam);

			DoReadUserName(a_psName, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadDesktopEmulatorData", bDoNotWriteDuplicates);
		}
}
// End of ReadUserName


void CSlaveRegistryDataReader::DoReadUserName(std::string* a_psName, PHKEY phkKey)
{
	DoReadOneRegistryName(phkKey, "UserName", *a_psName);
}*/
// End of DoReadUserName


void CSlaveRegistryDataReader::ReadDesktopErrorLoggerData(CErrorsLogger* pLogger)
{
		if (!pLogger)
			return;

	HKEY hkKey;
		try
		{
			DoOpenRegistryKey(&hkKey);

			DoReadDesktopErrorLoggerData(pLogger, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadLoggerData", bDoNotWriteDuplicates);
		}
}
// End of ReadDesktopErrorLoggerData


void CSlaveRegistryDataReader::DoReadDesktopErrorLoggerData(CErrorsLogger* pLogger, PHKEY phkKey)
{
	std::string DesktopLogFileNameString = "DesktopLogFileName";
		if (pLogger->GetLogFileName())
			DoReadOneRegistryName( phkKey, DesktopLogFileNameString, *(pLogger->GetLogFileName()) );
}
// End of DoReadDesktopErrorLoggerData


void CSlaveRegistryDataReader::ReadExchangeDesktopData(CDesktopEmulator* a_pEmulator)
{
		if (!a_pEmulator)
			return;

	HKEY hkKey;
		try
		{
			std::string sSavedKeyName = *GetSubKeyName();
			HKEY hSavedKey = GetKey();
			REGSAM SavedSam = GetSecurityAccessMask();

			SetKey(HKEY_LOCAL_MACHINE);
			*GetSubKeyName() = sExchangeRegistryPath;
			SetSecurityAccessMask(KEY_READ);

			DoOpenRegistryKey(&hkKey);

			SetKey(hSavedKey);
			*GetSubKeyName() = sSavedKeyName;
			SetSecurityAccessMask(SavedSam);

			DoReadExchangeDesktopData(a_pEmulator, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadDesktopEmulatorData", bDoNotWriteDuplicates);
		}
}
// End of ReadExchangeDesktopData


void CSlaveRegistryDataReader::WriteExchangeDesktopData(CSlaveManager* a_pManager)
{
		if ( (!a_pManager) )
			return;

	HKEY hkKey;
		try
		{
			std::string sSavedKeyName = *GetSubKeyName();
			HKEY hSavedKey = GetKey();
			REGSAM SavedSam = GetSecurityAccessMask();

			SetKey(HKEY_LOCAL_MACHINE);
			*GetSubKeyName() = sExchangeRegistryPath;
			SetSecurityAccessMask(KEY_READ | KEY_WRITE);

			DoOpenRegistryKey(&hkKey);

			SetKey(hSavedKey);
			*GetSubKeyName() = sSavedKeyName;
			SetSecurityAccessMask(SavedSam);

			DoWriteExchangeDesktopData(a_pManager, &hkKey);

			DoCloseRegistryKey(&hkKey);
		}
		catch(CAnyLogableException& Error)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoCloseRegistryKey(&hkKey);
			throw CAnyLogableException("An unknown error occured in CSlaveRegistryDataReader::ReadDesktopEmulatorData", bDoNotWriteDuplicates);
		}
}
// End of WriteExchangeDesktopData


void CSlaveRegistryDataReader::DoReadExchangeDesktopData(CDesktopEmulator* a_pEmulator, PHKEY a_phkKey)
{
	std::string sRemainingSlaveCurrentName = "RemainingSlaveCurrent";
	DoReadRegistryInt64(a_phkKey, sRemainingSlaveCurrentName, a_pEmulator->GetRemainingDescription()->SlaveCurrent);
	std::string sRemainingMasterCurrentName = "RemainingMasterCurrent";
	DoReadRegistryInt64(a_phkKey, sRemainingMasterCurrentName, a_pEmulator->GetRemainingDescription()->MasterCurrent);
	std::string sRemainingStartName = "RemainingStart";
	DoReadRegistryInt64(a_phkKey, sRemainingStartName, a_pEmulator->GetRemainingDescription()->Start);
	std::string sRemainingFinishName = "RemainingFinish";
	DoReadRegistryInt64(a_phkKey, sRemainingFinishName, a_pEmulator->GetRemainingDescription()->Finish);

	std::string sLockNeededName = "LockNeeded";
	DWORD bResult = 0;
	DoReadRegistryNumber(a_phkKey, sLockNeededName, bResult);
	a_pEmulator->SetLockNeeded(bResult);


	DWORD dwNumber = 0;
	std::string sAllowedSessionsNumberName = "AllowedSessionsNumber";
	DoReadRegistryNumber(a_phkKey, sAllowedSessionsNumberName, dwNumber);

	a_pEmulator->GetAllowedSessionsCollection()->Clear();

	int i = 0;
	DWORD dwSessionId;
		for (; i < dwNumber; ++i)
		{
			DoReadRegistryNumber(a_phkKey, GenerateName("AllowedSession", i, 2), dwSessionId);
			a_pEmulator->GetAllowedSessionsCollection()->AddApplication(dwSessionId, 0);
		}
}
// End of DoReadExchangeDesktopData


void CSlaveRegistryDataReader::DoWriteExchangeDesktopData(CSlaveManager* a_pManager, PHKEY a_phkKey)
{
	std::string sRemainingSlaveCurrentName = "RemainingSlaveCurrent";
	DoWriteRegistryInt64(a_phkKey, sRemainingSlaveCurrentName, a_pManager->GetRemainingTime()->SlaveCurrent);
	std::string sRemainingMasterCurrentName = "RemainingMasterCurrent";
	DoWriteRegistryInt64(a_phkKey, sRemainingMasterCurrentName, a_pManager->GetRemainingTime()->MasterCurrent);
	std::string sRemainingStartName = "RemainingStart";
	DoWriteRegistryInt64(a_phkKey, sRemainingStartName, a_pManager->GetRemainingTime()->Start);
	std::string sRemainingFinishName = "RemainingFinish";
	DoWriteRegistryInt64(a_phkKey, sRemainingFinishName, a_pManager->GetRemainingTime()->Finish);

	std::string sLockNeededName = "LockNeeded";
	DoWriteRegistryNumber(a_phkKey, sLockNeededName, a_pManager->GetLockNeeded());

	DWORD dwNumber = 0;
	CApplicationInfosCollection::iterator Iter = a_pManager->GetDesktopInfosCollection()->GetData()->begin(),
				EndIter = a_pManager->GetDesktopInfosCollection()->GetData()->end();
		for (; Iter != EndIter; ++Iter, ++dwNumber)
		{
			DoWriteRegistryNumber(a_phkKey, GenerateName("AllowedSession", dwNumber, 2), (*Iter)->GetSessionId());
		}

	std::string sAllowedSessionsNumberName = "AllowedSessionsNumber";
	DoWriteRegistryNumber(a_phkKey, sAllowedSessionsNumberName, dwNumber);
}
// End of DoWriteExchangeDesktopData
