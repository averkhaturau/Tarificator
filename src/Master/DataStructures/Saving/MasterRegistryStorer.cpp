/* Implementation of CMasterRegistryStorer */
#include "stdafx.h"

#include <string>
#include "..\ClubSettings\MashineData.h"
#include "..\..\..\Slave\Slave\Exceptions.h"
#include "MasterRegistryStorer.h"
#include "..\ClubSettings\BusyIntervalsCollection.h"
#include "..\ClubSettings\MashinesCollection.h"
#include "..\ClubSettings\OperatorsCollection.h"
#include "..\ClubSettings\BusyIntervalsCollection.h"
#include "..\ClubSettings\TarifPlansCollection.h"
#include "..\MasterManager\MasterManager.h"
#include "..\..\..\Slave\Slave\TCP_IP_Listener.h"
#include "..\..\..\Slave\Slave\TCP_IP_Receiver.h"
#include "..\..\..\Slave\Slave\ErrorsLogger.h"
#include "..\FileUpdateManager.h"
#include "..\ClubSettings\ClubState.h"
#include "..\FinantialHistoryLogger.h"

#include "..\Constants.h"


CMasterRegistryStorer::CMasterRegistryStorer()
{
	m_pHistFileUpdateManager = 0;
	m_pCurrFileUpdateManager = 0;
	m_pYestFileUpdateManager = 0;
	HKEY _hKey = 0;
	m_IsStorageChanged = 0;
	try{

		try{
			m_pHistFileUpdateManager = new CFileUpdateManager(this);
			m_pCurrFileUpdateManager = new CFileUpdateManager(this);
			m_pYestFileUpdateManager = new CFileUpdateManager(this);
			m_pHistFileUpdateManager->SetBaseFileName(&TodayInFileName());
			m_pCurrFileUpdateManager->SetBaseFileName(&std::string("Current.dat"));
			m_pYestFileUpdateManager->SetBaseFileName(&DateInFileName(CurrentTime()-A_Day));

			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath;
			DoOpenRegistryKey(&_hKey);

			DoCreateRegistryKey(&_hKey, sCurrDataSubkey,
				NULL, REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS, NULL, &m_Curr_key, NULL);

			DoCreateRegistryKey(&_hKey, sHistorySubkey +'\\'+
				TodayInStr(), NULL, REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS, NULL, &m_Hist_key, NULL);

			DoCloseRegistryKey(&_hKey);

		}catch(...){// не знаю, надо ли это
			if (m_pHistFileUpdateManager !=0)
			{
				delete m_pHistFileUpdateManager;
				m_pHistFileUpdateManager = 0;
			}
			if (m_pCurrFileUpdateManager != 0)
			{
				delete m_pCurrFileUpdateManager;
				m_pCurrFileUpdateManager = 0;
			}
			if (m_pYestFileUpdateManager != 0)
			{
				delete m_pYestFileUpdateManager;
				m_pYestFileUpdateManager = 0;
			}

			DoCloseRegistryKey(&m_Curr_key);
			DoCloseRegistryKey(&m_Hist_key);
			DoCloseRegistryKey(&_hKey);
			throw;
		}

		RestoreRegFromFile();

	}catch(std::exception &e){
		throw CAnyLogableException(std::string(
			(std::string)"CMasterRegistryStorer constructor failed: " +
			(std::string)e.what()).c_str(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			"CMasterRegistryStorer constructor failed",
			bDoNotWriteDuplicates);
	}
}

CMasterRegistryStorer::~CMasterRegistryStorer()
{
	if (m_pHistFileUpdateManager != 0)
	{
		delete m_pHistFileUpdateManager;
	}
	if (m_pCurrFileUpdateManager != 0)
	{
		delete m_pCurrFileUpdateManager;
	}
	if (m_pYestFileUpdateManager != 0)
	{
		delete m_pYestFileUpdateManager;
	}
	DoCloseRegistryKey(&m_Curr_key);
	DoCloseRegistryKey(&m_Hist_key);
}

void CMasterRegistryStorer::ReadFileUpdateManager(CFileUpdateManager* pFileUpdateManager)
{
	try{
		static unsigned int _count = 1;
		char buff[0xff];
		// попытаемся прочитать внутренние настройки CMasterRegistryStorer
		HKEY hkKey =0;
		CFileUpdateManager::CFileName sStr;

		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath +'\\'+ sOthersSubkey;

			DoOpenRegistryKey(&hkKey);
			DoReadOneRegistryName(&hkKey, sSaveToPath, sStr);
			pFileUpdateManager->SetDirectoryPath(&sStr);

			pFileUpdateManager->SetBaseFileName(
				&std::string((std::string)_itoa(_count, buff, 16)
				+ (std::string)".dat"));
			// pFileUpdateManager->SetBaseFileName(&TodayInFileName());
			// pFileUpdateManager->SetBaseFileName(&std::string("Current.dat"));

			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(std::string(
			(std::string)"CMasterRegistryStorer ReadFileUpdateManager failed: " +
			(std::string)e.what()).c_str(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			"CMasterRegistryStorer ReadFileUpdateManager failed",
			bDoNotWriteDuplicates);
	}
}
// end of CMasterRegistryStorer::ReadFileUpdateManager

void CMasterRegistryStorer::ReadErrorLoggerData(CErrorsLogger* pLogger)
{
	HKEY hkKey =0;
	try{
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath +'\\'+ sOthersSubkey;

			DoOpenRegistryKey(&hkKey);
			DoReadOneRegistryName(&hkKey,sLogFileNameValue,
				*(pLogger->GetLogFileName()) );
			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException& Error){
		throw CAnyLogableException((std::string)"CMasterRegistryStorer::ReadLoggerData failed: "
			+(std::string)Error.what(), Error.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An unknown error occured in CMasterRegistryStorer::ReadLoggerData", bDoNotWriteDuplicates);
	}
}
// End of ReadErrorLoggerData


void CMasterRegistryStorer::SaveHourMinuteTime(const std::string& sSubKeyName, const CTimeStorage& Time)
{
	try{
		HKEY hKey=0, hkOpenedKey = GetKey();
		try{
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = "";
			DoCreateRegistryKey(&hkOpenedKey, sSubKeyName, NULL,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

			DoWriteRegistryNumber(&hKey, "Hour", Time.Hours());
			DoWriteRegistryNumber(&hKey, "Minute", Time.Minutes());

			DoCloseRegistryKey(&hKey);
		}catch(...){
			DoCloseRegistryKey(&hKey);
			SetKey(hkOpenedKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("SaveHourMinuteTime can't write ") + sSubKeyName +
			std::string(": ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("SaveHourMinuteTime can't write ") + sSubKeyName,
			bDoNotWriteDuplicates);
	}
}
// end of CTimeStorage SaveHourMinuteTime(const std::string& sSubKeyName)

CTimeStorage CMasterRegistryStorer::ReadHourMinuteTime(const std::string& sSubKeyName)
{
	try{
		HKEY _hKey =0, hkOpenedKey =0;
		DWORD dwValue;
		try{
			hkOpenedKey = GetKey();
			(*GetSubKeyName()) = sSubKeyName;
			DoOpenRegistryKey(&_hKey);
			SetKey(_hKey);

			DoReadRegistryNumber(&_hKey, "Hour", dwValue);
			CTimeStorage _Result(An_Hour.GetTime() * dwValue);
			DoReadRegistryNumber(&_hKey, "Minute", dwValue);
			_Result += CTimeStorage(A_Minute.GetTime() * dwValue);

			DoCloseRegistryKey(&_hKey);
			SetKey(hkOpenedKey);
			return _Result;

		}catch(...){
			DoCloseRegistryKey(&_hKey);
			SetKey(hkOpenedKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("ReadHourMinuteTime can't read ") + sSubKeyName +
			std::string(": ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
			throw CAnyLogableException(
			std::string("ReadHourMinuteTime can't read ") + sSubKeyName,
			bDoNotWriteDuplicates);
	}
}
// end of ReadHourMinuteTime(const std::string& sSubKeyName)

void CMasterRegistryStorer::ReadWorkingInterval(
	CIntervalsAncestor* pTimeInterval)
{
	try{
		HKEY _hKey = 0;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath +'\\'+ sOthersSubkey
				+ "\\WorkingInterval";
			DoOpenRegistryKey(&_hKey);
			SetKey(_hKey);

			CTimeStorage Start = ReadHourMinuteTime("Start");
			CTimeStorage Finish = ReadHourMinuteTime("Finish");
			CTimeStorage Length = Finish - Start;

			DoCloseRegistryKey(&_hKey);

			pTimeInterval->SetStartTime(Start);
			pTimeInterval->SetLengthFromStart(
				Finish<=Start ? Length + A_Day : Length );

		}catch(...){
			DoCloseRegistryKey(&_hKey);
			throw;
		}

	}catch(CAnyLogableException &e){
		throw CAnyLogableException(
			std::string("ReadWorkingInterval failed: ")+
			(std::string)e.what(), e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("ReadWorkingInterval failed",
			bDoNotWriteDuplicates);
	}
}
// end of ReadWorkingInterval(CInterval* TimeInterval)

void CMasterRegistryStorer::ReadMashinesCollection(
	CMashinesCollection* pMashinesCollection)
{
	try{
		const std::string sTodayKey = sMasterRegistryPath
			+'\\'+ sCurrDataSubkey +'\\'+ sMashinesSubkey;
		HKEY hKey = 0, _hKey = 0;
		DWORD dwValue = 0, IPAddr = 0;
		try{
			ReadMashinesCollectionFundamental(
				sMasterRegistryPath, pMashinesCollection);

			// проверим, есть ли данные по сегодняшнему числу в реестре
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sTodayKey;

			// Определяем, были ли записи по сегодняшнему числу
			bool bIsAnyInRegToday = true;
			try{
				DoOpenRegistryKey(&hKey);
			}catch(CAnyLogableException){
				bIsAnyInRegToday = false;
			}

			if (bIsAnyInRegToday)
			{// читаем ключи
				DoReadRegistryNumber(&hKey, "NumberOfMashines",
					dwValue);
				for (signed int si = 0; si < dwValue; ++si)
				{
					CMashineData* _pMashine;
					std::string sBusySubKey;
					sBusySubKey = sTodayKey +'\\'+ ((*GetSubKeyName())=
						GenerateName("Mashine", si, 2));

					SetKey(hKey);
					DoOpenRegistryKey(&_hKey);
					DoReadRegistryNumber(&_hKey, "IPAddress", IPAddr);

					if (_pMashine = // разумеется присвоение а не сравнение
							pMashinesCollection->FindMashine(IPAddr))
					{
						ReadBusyIntervalsFromKey(sBusySubKey,
							_pMashine->GetBusyIntervalsCollection());
					}
					else throw CAnyLogableException("ReadMashinesCollection: Registry is corrupted: can't find mashine", bDoNotWriteDuplicates);

					DoCloseRegistryKey(&_hKey);
				}
			}
			DoCloseRegistryKey(&hKey);
		}catch(...){
			DoCloseRegistryKey(&_hKey);
			DoCloseRegistryKey(&hKey);
			throw;
		}
	}catch(CAnyLogableException &e){
		throw CAnyLogableException(std::string(
			"ReadMashinesCollection failed: ")+e.what(),
			e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("ReadMashinesCollection failed", bDoNotWriteDuplicates);
	}
}
// end of void CMasterRegistryStorer::ReadMashinesCollection


void CMasterRegistryStorer::ReadMashinesCollectionHistory(
		CMashinesCollection* pMashinesCollection,
		CInterval& ReadInterval)
{
	try{
		HKEY hKey = 0, _hKey = 0;
		DWORD dwValue = 0, IPAddr = 0;
		try{
			ReadMashinesCollectionFundamental(
					sMasterRegistryPath, pMashinesCollection);

			for (CTimeStorage _iDay = ReadInterval.GetStartTime();
					_iDay <= ReadInterval.GetFinishTime(); _iDay += A_Day)
			{
				try{
					// проверим, есть ли данные по числу в реестре
					SetKey(HKEY_LOCAL_MACHINE);
					SetSecurityAccessMask(KEY_ALL_ACCESS);
					(*GetSubKeyName()) = sMasterRegistryPath
						+'\\'+ sHistorySubkey + DateInStr(_iDay) +'\\'+ sMashinesSubkey;

					// Определяем, были ли записи по сегодняшнему числу
					bool bIsAnyInRegToday = true;
					try{
						DoOpenRegistryKey(&hKey);
					}catch(CAnyLogableException){
						bIsAnyInRegToday = false;
					}

					if (bIsAnyInRegToday)
					{// читаем ключи
						DoReadRegistryNumber(&hKey, "NumberOfMashines",
							dwValue);
						for (signed int si = 0; si < dwValue; ++si)
						{
							CMashineData* _pMashine;
							std::string sBusySubKey;
							sBusySubKey = sMasterRegistryPath
								+'\\'+ sHistorySubkey + DateInStr(_iDay) +'\\'+
								sMashinesSubkey +'\\'+
									((*GetSubKeyName())= GenerateName("Mashine", si, 2));

							SetKey(hKey);
							DoOpenRegistryKey(&_hKey);
							DoReadRegistryNumber(&_hKey, "IPAddress", IPAddr);

							if (_pMashine = // разумеется присвоение а не сравнение
									pMashinesCollection->FindMashine(IPAddr))
							{
								ReadBusyIntervalsFromKey(sBusySubKey,
									_pMashine->GetBusyIntervalsCollection());
							}
							else
								throw CAnyLogableException("Registry is corrupted or machines have been changed: can't find machine", bDoNotWriteDuplicates);

							DoCloseRegistryKey(&_hKey);
						}
					}//if (bIsAnyInRegToday)

				}catch(CAnyLogableException &e){
						// не знаю, что здесь сделать, и стоит ли передать exception дальше
				}

				DoCloseRegistryKey(&hKey);
			}
		}catch(...){
			DoCloseRegistryKey(&_hKey);
			DoCloseRegistryKey(&hKey);
			throw;
		}
	}catch(CAnyLogableException &e){
		throw CAnyLogableException(std::string(
			"ReadMashinesCollectionHistory failed: ")+e.what(),
			e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("ReadMashinesCollectionHistory failed", bDoNotWriteDuplicates);
	}
}


void CMasterRegistryStorer::ReadMashinesCollectionFundamental(
	const std::string &RegistryPath,
	CMashinesCollection* pMashinesCollection)
{
	try{
		HKEY hMashinesCollectionKey =0, hMashineKey =0;
		DWORD dwValue;
		std::string sMashineName;
		DWORD _IPAddress;
		CTimeStorage _TimeOut;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			// чтение общего для всех машин CheckStatePeriod
			(*GetSubKeyName()) = RegistryPath + '\\' + sCommunicationSubkey;
			DoOpenRegistryKey(&hMashinesCollectionKey);
			DoReadRegistryNumber(&hMashinesCollectionKey, "NoAnswerPeriod", dwValue);
			_TimeOut.SetTime((__int64)dwValue*A_Second.GetTime()/1000);

			DoCloseRegistryKey(&hMashinesCollectionKey);

			// чтение для каждой машины
			(*GetSubKeyName()) = RegistryPath + '\\' + sMashinesSubkey;
			DoOpenRegistryKey(&hMashinesCollectionKey);

			// читаем количество машин
			DoReadRegistryNumber(&hMashinesCollectionKey, "NumberOfMashines", dwValue);

			// это не абстрагирует от реализации контейнера, но что поделать
			pMashinesCollection->resize(dwValue);

			for (signed int si = dwValue-1; si >= 0; --si)
			{
				SetKey(hMashinesCollectionKey);
				*(GetSubKeyName()) = GenerateName("Mashine", si, 2);
				DoOpenRegistryKey(&hMashineKey);
				DoReadOneRegistryName(&hMashineKey, "Name", sMashineName);
				DoReadRegistryNumber(&hMashineKey, "IPAddress", _IPAddress);
				DoCloseRegistryKey(&hMashineKey);

				(*pMashinesCollection)[si].GetMashineName() = sMashineName;
				(*pMashinesCollection)[si].SetIPAddress(_IPAddress);
				(*pMashinesCollection)[si].GetLastSuccessCommunication()->SetTimeOut(_TimeOut);
				(*pMashinesCollection)[si].GetLastSuccessCommunication()->SetEnabled(_TimeOut.GetTime() != 0); // не правда ли красиво!
				
				*(GetSubKeyName()) += std::string("\\AllowedTarifPlans");
				DoOpenRegistryKey(&hMashineKey);
				DoReadRegistryNumber(&hMashineKey, "AllowedPlansNumber", dwValue);

				for (signed int sj = 0; sj < dwValue; ++sj)
				{
					DWORD dwVal;
					DoReadRegistryNumber(&hMashineKey, GenerateName("PlanNumber",
						sj, 2), dwVal);
					(*pMashinesCollection)[si].GetTarifPlansNumbers()->insert(dwVal);
				}

				ReadMasterConnectedSocketHolder((*pMashinesCollection)[si].GetConnectingSocket());
				ReadCommonTCP_IP_SocketHolderData((*pMashinesCollection)[si].GetAcceptingSocket());
			}
			DoCloseRegistryKey(&hMashinesCollectionKey);

		}catch(...){
			DoCloseRegistryKey(&hMashinesCollectionKey);
			DoCloseRegistryKey(&hMashineKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(std::string("ReadMashinesCollection failed: ")+
			std::string(e.what()), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("ReadMashinesCollection failed: unknown exception",
			bDoNotWriteDuplicates);
	}

}
// end of void FillMashinesCollection(CMashinesCollection* pMashinesCollection)

void CMasterRegistryStorer::ReadTarifPlansCollection(CTarifPlansCollection* pTarifPlansColl)
{
	ReadTarifPlansCollFromKey(sMasterRegistryPath, pTarifPlansColl);
}

void CMasterRegistryStorer::ReadTarifPlansCollFromKey(
	const std::string &RegistryPath, CTarifPlansCollection* pTarifPlansColl)
{
	try{
		HKEY hKey =0, _hKey1 =0, _hKey2 =0;
		DWORD dwValue;
		std::string sPlanName;
		CPermission _Permission;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = RegistryPath +'\\'+ sTarifPlansSubkey;
			DoOpenRegistryKey(&hKey);

			// читаем количество тарифных планов
			DWORD dwTarifPlansNum;
			DoReadRegistryNumber(&hKey, "NumberOfTarifs", dwTarifPlansNum);
			
			// почистим пёрышки
			pTarifPlansColl->resize(dwTarifPlansNum);

			// читаем тарифные планы
			for (signed int si = dwTarifPlansNum-1; si >= 0; --si)
			{
				SetKey(hKey);
				*(GetSubKeyName()) = GenerateName("TarifPlan", si, 2);
				DoOpenRegistryKey(&_hKey1);
				SetKey(_hKey1);
				// Чтение разрешнных ЮзерНэймов
				{
					DWORD dwNum;
					DoReadRegistryNumber(&_hKey1, "NumberUserNames", dwNum);
					(*pTarifPlansColl)[si].GetUserNames()->resize(dwNum);
					for (int i = 0; i < dwNum; ++i)
					{
						DoReadOneRegistryName( &_hKey1, GenerateName("UserName", i, 2),
							(*pTarifPlansColl)[si].GetUserNames()->operator[](i) );
					}
				}
				DoReadOneRegistryName(&_hKey1, "Name", sPlanName);
				DoReadRegistryNumber(&_hKey1, "Permission", _Permission);
				(*pTarifPlansColl)[si].SetPermission(_Permission);
				(*pTarifPlansColl)[si].SetName(sPlanName);
				(*pTarifPlansColl)[si].SetStandardization(
						ReadHourMinuteTime("Standardization") );
				(*pTarifPlansColl)[si].SetTimeQuant(
						ReadHourMinuteTime((std::string)"TimeQuant") );

				DoReadRegistryNumber(&_hKey1, "NumberOfIntervals", dwValue);
				for (signed int sj = dwValue-1; sj >= 0; --sj)
				{
					SetKey(_hKey1);
					*(GetSubKeyName()) = GenerateName("Interval", sj, 2);
					DoOpenRegistryKey(&_hKey2);
					SetKey(_hKey2);

					DoReadRegistryNumber(&_hKey2, "Currency", dwValue);

					CTimeStorage _Start = ReadHourMinuteTime(
							(std::string)"Start");
					CTimeStorage _Finish = ReadHourMinuteTime(
							(std::string)"Finish");
					CTimeStorage _Length = _Finish - _Start;
					CTarifInterval _TarifInterval;

					DoCloseRegistryKey(&_hKey2);

					_TarifInterval.SetStartTime(_Start);
					_TarifInterval.SetLengthFromStart(
							_Finish<=_Start ? _Length + A_Day : _Length );
					_TarifInterval.SetTarif((CCurrency)dwValue);

					(*pTarifPlansColl)[si].AddResident(_TarifInterval);
				}
				DoCloseRegistryKey(&_hKey1);
			}
			DoCloseRegistryKey(&hKey);
		}catch(...){
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey1);
			DoCloseRegistryKey(&_hKey2);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(std::string("ReadTarifPlan failed: ")+
			std::string(e.what()), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("ReadTarifPlan failed: unknown exception",
			bDoNotWriteDuplicates);
	}
}
// end of void ReadTarifPlan(CTarifPlan* pTarifPlan)

void CMasterRegistryStorer::ReadOperatorsCollection(
		COperatorsCollection* pOperatorsCollection)
{
	ReadOperatorsFromKey(sMasterRegistryPath, pOperatorsCollection);
}
// end of void ReadOperatorsCollection(COperatorsCollection* pOperatorsCollection)

void CMasterRegistryStorer::ReadOperatorsFromKey(
	const std::string &RegistryPath,
	COperatorsCollection* pOperatorsCollection)
{
	try{
		HKEY hKey =0, _hKey =0;
		DWORD dwValue;
		std::string sOperatorName;
		CPasswordHash PswrdHash;
		CPermission Permisson;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = RegistryPath + '\\' + sOperatorsSubkey;
			DoOpenRegistryKey(&hKey);
			SetKey(hKey);

			// читаем количество oператоров
			DoReadRegistryNumber(&hKey, "NumberOfOperators", dwValue);

			pOperatorsCollection->Clear();

			// читаем операторов
			for (signed int si = dwValue-1; si >= 0; --si)
			{
				*(GetSubKeyName()) = GenerateName("Operator", si, 2);
				DoOpenRegistryKey(&_hKey);
				DoReadOneRegistryName(&_hKey, "Name", sOperatorName);
				DoReadRegistryInt64(&_hKey, "PasswordHash", PswrdHash);
				DoReadRegistryNumber(&_hKey, "Permission", Permisson);

				// добавляем оператора - корректно только так
				pOperatorsCollection->AddOperator(COperator(sOperatorName, PswrdHash, Permisson));

				DoCloseRegistryKey(&_hKey);
			}

			DoCloseRegistryKey(&hKey);
		}catch(...){
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(std::string("ReadTarifPlan failed: ")+
			std::string(e.what()), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("ReadTarifPlan failed: unknown exception",
			bDoNotWriteDuplicates);
	}
}
// end of void CMasterRegistryStorer::ReadOperators

void CMasterRegistryStorer::ReadBusyIntervalsFromKey(
	const std::string &RegistryPath, CBusyIntervalsCollection* pBusyIntervalsCollection)
{
	try{
		HKEY hKey=0, _hKey=0;
		DWORD dwValue1, dwValue2, _OperatorNumber, _TarifPlanNumber, _dwPrice;
		CTimeContainer _Start, _Finish, _CreationTime;
		std::string sName;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = RegistryPath +'\\'+ sBusyIntervalsSubkey;
			DoOpenRegistryKey(&hKey);

			DoReadRegistryNumber(&hKey, "NumberOfIntervals", dwValue2);

			pBusyIntervalsCollection->Clear();

			SetKey(hKey);
			for (signed int sj = dwValue2-1; sj >= 0; --sj)
			{
				*(GetSubKeyName()) = GenerateName("Interval", sj, 2);
				DoOpenRegistryKey(&_hKey);
				DoReadRegistryNumber(&_hKey, "EventsNumber", dwValue1);
				DoCloseRegistryKey(&_hKey);

				CBusyIntervalHist _curBIH;
				_curBIH.Clear();
				for (signed int si = 0; si < dwValue1; ++si)
				{
					*(GetSubKeyName()) = GenerateName("Interval", sj, 2) 
						+ '\\' + GenerateName("Event", si, 2);
					DoOpenRegistryKey(&_hKey);
					DoReadRegistryInt64(&_hKey, "Start", _Start);
					DoReadRegistryInt64(&_hKey, "Finish", _Finish);
					DoReadRegistryInt64(&_hKey, "CreationTime", _CreationTime);

					DoReadRegistryNumber(&_hKey, "OperatorNumber", _OperatorNumber);
					DoReadRegistryNumber(&_hKey, "TarifPlanNumber", _TarifPlanNumber);
					DoReadOneRegistryName(&_hKey, "ClientName", sName);
					DoReadRegistryNumber(&_hKey, sIntervalPrice, _dwPrice);

					/*	pBusyIntervalsCollection->AddInterval(CBusyInterval(
							CTimeStorage(_Start), CTimeStorage(_Finish),
							CBusyInterval::CTarifPlanNumber(_TarifPlanNumber),
							COperatorNumber(_OperatorNumber), sName,
							_CreationTime, (CCurrency)_dwPrice
						)
							, si//маздай
						);
					*/
					_curBIH.AddResident(CBusyInterval(
							CTimeStorage(_Start), CTimeStorage(_Finish),
							CBusyInterval::CTarifPlanNumber(_TarifPlanNumber),
							COperatorNumber(_OperatorNumber), sName,
							_CreationTime, (CCurrency)_dwPrice
					));
					DoCloseRegistryKey(&_hKey);
				}// for (signed int si = 0; si < dwValue1; ++si)
				_curBIH.m_Number = sj;
				pBusyIntervalsCollection->AddResident(_curBIH);
			}// for (signed int sj = dwValue2-1; sj >= 0; --sj)

			DoCloseRegistryKey(&hKey);
		}catch(...){ // закрываем то, что пооткрывали в реестре
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			throw;
		}
	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("ReadBusyIntervalsFromKey ") + RegistryPath +
			std::string(" failed: ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("ReadBusyIntervalsFromKey ") + RegistryPath +
			std::string(" failed: unknown exception"), bDoNotWriteDuplicates);
	}
}
// end of void ReadBusyIntervalsFromKey

void CMasterRegistryStorer::SaveBusyIntervalsToKey(const std::string &RegistryPath,
		CBusyIntervalsCollection* pBusyIntervalsCollection)
{
	try{
		HKEY hKey=0, _hKey=0;
		DWORD _dwCollectionSize = pBusyIntervalsCollection->size();
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = "";
			DoOpenRegistryKey(&_hKey);
			DoCreateRegistryKey(&_hKey, RegistryPath +'\\'+
				sBusyIntervalsSubkey, NULL, REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS, NULL, &hKey, NULL);
			DoCloseRegistryKey(&_hKey); // больше не нужен

			// сохраняем количество для контроля и удобства чтения
			DoWriteRegistryNumber(&hKey, "NumberOfIntervals",
				_dwCollectionSize);

			SetKey(hKey);

			for (CBusyIntervalsCollection::iterator _Element =
					pBusyIntervalsCollection->GetData()->begin();
				_Element != pBusyIntervalsCollection->GetData()->end();
					++_Element)
			{

				DWORD _dwHistSize = (*_Element)->size();

				DoCreateRegistryKey(&hKey,
					GenerateName("Interval", (*_Element)->m_Number, 2)
					, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
					NULL, &_hKey, NULL);

				DoWriteRegistryNumber(&_hKey, "EventsNumber",
					_dwHistSize );

				DoCloseRegistryKey(&_hKey);

				for (signed int si = 0; si < _dwHistSize; ++si)
				{

					DoCreateRegistryKey(&hKey,
						GenerateName("Interval",
							(*_Element)->m_Number, 2)
							+ '\\' + GenerateName("Event", si, 2)

						, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_hKey, NULL);

					DoWriteRegistryInt64(&_hKey, "Start",
						(**_Element)[si].GetStartTime().GetTime() );
					DoWriteRegistryInt64(&_hKey, "Finish",
						(**_Element)[si].GetFinishTime().GetTime() );
					DoWriteRegistryInt64(&_hKey, "CreationTime",
						(**_Element)[si].GetCreationTime().GetTime() );
					DoWriteRegistryNumber(&_hKey, "OperatorNumber",
						(**_Element)[si].GetOperatorNumber());
					DoWriteRegistryNumber(&_hKey, "TarifPlanNumber",
						(**_Element)[si].GetTarifPlanNumber());
					DoWriteRegistryString(&_hKey, "ClientName",
						(**_Element)[si].GetClientName());
					DoWriteRegistryNumber(&_hKey, sIntervalPrice,
						(**_Element)[si].GetPrice());

					DoCloseRegistryKey(&_hKey);
				}
			}

			DoCloseRegistryKey(&hKey);
		}catch(...){ // закрываем то, что пооткрывали в реестре
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("SaveBusyIntervalToKey ") + RegistryPath +
			std::string(" failed: ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("SaveBusyIntervalsToKey ") + RegistryPath +
			std::string(" failed: unknown exception"), bDoNotWriteDuplicates);
	}
}
// end of void SaveBusyIntervalsToKey

void CMasterRegistryStorer::SaveBusyIntervalHistToHKEY(CBusyIntervalHist* pBIH, HKEY& OpenedKey)
{
	try{
		DWORD _dwHistSize = pBIH->size();
		DWORD dwValue;
		HKEY _hKey = 0;

		try{
			try{
				DoReadRegistryNumber(&OpenedKey, "NumberOfIntervals", dwValue);
			}catch(CAnyLogableException){
				dwValue = 0;
			}

			DoCreateRegistryKey(&OpenedKey,
				GenerateName("Interval", dwValue, 2),
				"", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
				NULL, &_hKey, NULL);

			DoWriteRegistryNumber(&_hKey, "EventsNumber", _dwHistSize);

			DoCloseRegistryKey(&_hKey);

			for (signed int si = 0; si < _dwHistSize; ++si)
			{

				DoCreateRegistryKey(&OpenedKey,
					GenerateName("Interval", dwValue, 2)
						+ '\\' + GenerateName("Event", si, 2),
					"", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
					&_hKey, NULL);

				DoWriteRegistryInt64(&_hKey, "Start",
					(*pBIH)[si].GetStartTime().GetTime() );
				DoWriteRegistryInt64(&_hKey, "Finish",
					(*pBIH)[si].GetFinishTime().GetTime() );
				DoWriteRegistryInt64(&_hKey, "CreationTime",
					(*pBIH)[si].GetCreationTime().GetTime() );
				DoWriteRegistryNumber(&_hKey, "OperatorNumber",
					(*pBIH)[si].GetOperatorNumber());
				DoWriteRegistryNumber(&_hKey, "TarifPlanNumber",
					(*pBIH)[si].GetTarifPlanNumber());
				DoWriteRegistryString(&_hKey, "ClientName",
					(*pBIH)[si].GetClientName());
				DoWriteRegistryNumber(&_hKey, sIntervalPrice,
					(*pBIH)[si].GetPrice());

				DoCloseRegistryKey(&_hKey);
			}

			DoWriteRegistryNumber(&OpenedKey, "NumberOfIntervals", ++dwValue);

		}catch(...){
			DoCloseRegistryKey(&_hKey);
			throw;
		}

	}catch(CAnyLogableException &e){
		throw CAnyLogableException(
			std::string("SaveBusyIntervalHistToHKEY failed: ")
			+ (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("SaveBusyIntervalHistToHKEY failed", bDoNotWriteDuplicates);
	}
}


void CMasterRegistryStorer::SaveBusyIntervalsToHistory(int iMachine, CBusyIntervalsCollection* pBusyIntervalsCollection)
{
	try{
		HKEY hKey=0, _hKey=0;
		DWORD _dwCollectionSize = pBusyIntervalsCollection->size();
		if (!_dwCollectionSize) return;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = "";
			DoOpenRegistryKey(&_hKey);
			DoCreateRegistryKey(&_hKey, sMasterRegistryPath+'\\'+
					sHistorySubkey, NULL, REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS, NULL, &hKey, NULL);
			DoCloseRegistryKey(&_hKey); // больше не нужен
			SetKey(hKey);

			for (CBusyIntervalsCollection::iterator _Element =
					pBusyIntervalsCollection->GetData()->begin();
				_Element != pBusyIntervalsCollection->GetData()->end();
					++_Element)
			{
				std::string _sKeyName =
					DateInStr((**_Element).GetStartTime());

				_sKeyName+='\\'+ sMashinesSubkey +'\\'+
					GenerateName("Mashine", iMachine, 2) +'\\'+
					sBusyIntervalsSubkey;

				DoCreateRegistryKey(&hKey, _sKeyName,
					NULL, REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS, NULL, &_hKey, NULL);
				
				SaveBusyIntervalHistToHKEY(*_Element, _hKey);
				DoCloseRegistryKey(&_hKey);
			}

			DoCloseRegistryKey(&hKey);

		}catch(...){ // закрываем то, что пооткрывали в реестре
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("SaveBusyIntervalsToHistory failed: ") +
			(std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("SaveBusyIntervalsToHistory failed."),
			bDoNotWriteDuplicates);
	}
}

void CMasterRegistryStorer::SaveMashinesCollection(CMashinesCollection* pMashinesCollection)
{
	try{ // пересраXYЙемся
		// Грохнем всё, что было и сохраним заново
		HKEY _hKey = 0;
		try{
				SetKey(HKEY_LOCAL_MACHINE);
				SetSecurityAccessMask(KEY_ALL_ACCESS);
				(*GetSubKeyName()) = "";
				DoOpenRegistryKey(&_hKey);

			try{

				DoDeleteRegistryKeyWithSubkeys(&_hKey, sMasterRegistryPath +'\\'+
					sCurrDataSubkey +'\\'+ sMashinesSubkey);
			}catch(...){
			}

			SaveMashinesCollectionToKey(sMasterRegistryPath +'\\'+
				sCurrDataSubkey +'\\'+ sMashinesSubkey, pMashinesCollection);

			m_IsStorageChanged = true;
			DoCloseRegistryKey(&_hKey);

		}catch(...){
			DoCloseRegistryKey(&_hKey);
			throw;
		}

		//FlushCurrToFile();
	}catch(CAnyLogableException &e){
		throw CAnyLogableException(
			(std::string)"SaveMashinesCollection failed" +
			(std::string)e.what(), e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("SaveMashinesCollection failed", bDoNotWriteDuplicates);
	}
}
// end of void SaveMashinesCollection(CMashinesCollection* pMashinesCollection)

void CMasterRegistryStorer::SaveMashinesCollectionToHistory(
		CMashinesCollection* pMashinesCollection)
{
	SaveMashinesCollectionToKey(sMasterRegistryPath +'\\'+
			sHistorySubkey +'\\'+ TodayInStr() +'\\'+ sMashinesSubkey,
		pMashinesCollection, false);
}
// end of void CMasterRegistryStorer::SaveMashinesCollectionToHistory

void CMasterRegistryStorer::SaveMashinesCollectionToKey(
		const std::string &RegistryPath,
		CMashinesCollection* pMashinesCollection, bool bWriteBIC)
{
	try{
		HKEY hKey =0, _hKey =0;
		DWORD dwValue = pMashinesCollection->size();
		if (!dwValue)return;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = "";
			DoOpenRegistryKey(&_hKey);
			DoCreateRegistryKey(&_hKey, RegistryPath, NULL,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
			DoCloseRegistryKey(&_hKey); // больше не нужен

			// пишем количество машин
			DoWriteRegistryNumber(&hKey, "NumberOfMashines", dwValue);

			SetKey(hKey);
			for (signed int si = dwValue-1; si >= 0; --si)
			{
				std::string sMashineSubKey = GenerateName("Mashine", si, 2);
				DoCreateRegistryKey(&hKey, sMashineSubKey, "",
					REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_hKey, NULL);

				DoWriteRegistryString(&_hKey, "Name",
					(*pMashinesCollection)[si].GetMashineName() );
				DoWriteRegistryNumber(&_hKey, "IPAddress",
					(*pMashinesCollection)[si].GetIPAddress() );

				DoCloseRegistryKey(&_hKey);

				// сэйваем бизю
				if (bWriteBIC) // ...если надо
					SaveBusyIntervalsToKey(RegistryPath+'\\'+sMashineSubKey,
						(*pMashinesCollection)[si].GetBusyIntervalsCollection());

				// а теперь пишем разрешённые планы
				DoCreateRegistryKey(&hKey, sMashineSubKey +"\\AllowedTarifPlans", "",
					REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_hKey, NULL);

				dwValue = (*pMashinesCollection)[si].GetTarifPlansNumbers()->size();
				DoWriteRegistryNumber(&_hKey, "AllowedPlansNumber", dwValue);

				CMashineData::CTarifPlansNumbers::iterator _Element =
					(*pMashinesCollection)[si].GetTarifPlansNumbers()->begin();
				for (signed int sj = 0;
					_Element != (*pMashinesCollection)[si].GetTarifPlansNumbers()->end();
						++sj, ++_Element)
					DoWriteRegistryNumber(&_hKey, GenerateName("PlanNumber",
						sj, 2), (*_Element));

				DoCloseRegistryKey(&_hKey);
			}
			DoCloseRegistryKey(&hKey);
		}catch(...){ // закрываем то, что пооткрывали в реестре
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			throw;
		}
		
	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("SaveMashinesCollectionToKey ") + RegistryPath +
			std::string(" failed: ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("SaveMashinesCollectionToKey ") + RegistryPath +
			std::string(" failed: unknown exception"), bDoNotWriteDuplicates);
	}
}
// end of void CMasterRegistryStorer::SaveMashinesCollectionToKey


void CMasterRegistryStorer::ChangeInterval(
	const unsigned long MashineNumber,
	const unsigned long IntervalNumber,
	CBusyInterval* pInterval)
{
	throw CAnyLogableException("CMasterRegistryStorer::ChangeInterval не реализована", bDoNotWriteDuplicates);
	std::string sIntervalSubKey;
	try{
		sIntervalSubKey = MashinesCollectionSaveToStr()+
			'\\'+ GenerateName("Mashine", MashineNumber, 2)+
			'\\'+ sBusyIntervalsSubkey +'\\'+
			GenerateName("Interval", IntervalNumber, 2);

		HKEY hKey =0, _hKey =0;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = "";
			DoOpenRegistryKey(&_hKey);

			DoCreateRegistryKey(&_hKey, sIntervalSubKey, "",
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
			DoCloseRegistryKey(&_hKey);

			{
				DoWriteRegistryInt64(&hKey, "Start",
					__int64(pInterval->GetStartTime().GetTime()) );
				DoWriteRegistryInt64(&hKey, "Finish",
					__int64(pInterval->GetFinishTime().GetTime()) );
				DoWriteRegistryNumber(&hKey, "OperatorNumber",
					pInterval->GetOperatorNumber());
				DoWriteRegistryNumber(&hKey, "TarifPlanNumber",
					pInterval->GetTarifPlanNumber());
			}

			DoCloseRegistryKey(&hKey);

		}catch(...){ // закрываем то, что пооткрывали в реестре
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			throw;
		}
		
	}catch(CAnyLogableException &e){
		throw CAnyLogableException(
			std::string("ChangeInterval ") + sIntervalSubKey +
			std::string(" failed: ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("ChangeInterval ") + sIntervalSubKey +
			std::string(" failed: unknown exception"), bDoNotWriteDuplicates);
	}

 }
 // end of void ChangeInterval

void CMasterRegistryStorer::SaveOperatorsToHistrory(
	COperatorsCollection* pOperatorColl)
{
	SaveOperatorsToKey(TodayHistoryKey(), pOperatorColl);
}
// end of void SaveOperatorsToHistriry

void CMasterRegistryStorer::SaveOperatorsChanged(COperatorsCollection* pOperatorColl)
{
	SaveOperatorsToKey(sMasterRegistryPath, pOperatorColl);
}
// end of SaveOperatorsChanged(COperatorsCollection* pOperatorColl)

void CMasterRegistryStorer::SaveOperatorsToKey(const std::string
		&RegistryPath, COperatorsCollection* pOperatorColl)
{
	try{
		HKEY hKey=0, _hKey=0;
		DWORD _dwCollectionSize = pOperatorColl->size();
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = "";
			DoOpenRegistryKey(&_hKey);
			DoCreateRegistryKey(&_hKey, RegistryPath+'\\'+sOperatorsSubkey, NULL,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
			DoCloseRegistryKey(&_hKey); // больше не нужен

			// сохраняем количество для контроля и удобства чтения
			DoWriteRegistryNumber(&hKey, "NumberOfOperators",
				_dwCollectionSize);

			SetKey(hKey);

			COperatorsCollection::iterator _Element = pOperatorColl->GetData()->begin();
			signed int si = _dwCollectionSize-1;
			for (; si >= 0; --si , ++_Element)
			{
				DoCreateRegistryKey(&hKey, GenerateName("Operator", si, 2), "",
					REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_hKey, NULL);
				DoWriteRegistryString(&_hKey, "Name",(*_Element)->GetName());
				DoWriteRegistryInt64(&_hKey, "PasswordHash",
					__int64((*_Element)->GetPasswordHash()) );
				DoWriteRegistryNumber(&_hKey, "Permission",
					(*_Element)->GetPermission());

				DoCloseRegistryKey(&_hKey);
			}

			DoCloseRegistryKey(&hKey);
		}catch(...){ // закрываем то, что пооткрывали в реестре
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("SaveOperatorsToKey ") + RegistryPath +
			std::string(" failed: ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("SaveOperatorsToKey ") + RegistryPath +
			std::string(" failed: unknown exception"), bDoNotWriteDuplicates);
	}
}
// end of SaveOperatorsToKey



void CMasterRegistryStorer::SaveTarifPlansToHistrory(
	CTarifPlansCollection* pTarifPlansColl)
{
	SaveTarifPlansToKey(TodayHistoryKey(), pTarifPlansColl);
}
// end of void SaveTarifPlansToHistrory

void CMasterRegistryStorer::SaveTarifPlansToKey(const std::string
		&RegistryPath,	CTarifPlansCollection* pTarifPlansColl)
{
	try{
		HKEY hKey=0, _hKey=0, __hKey=0;
		DWORD _dwCollectionSize = pTarifPlansColl->size();
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = "";
			DoOpenRegistryKey(&_hKey);
			DoCreateRegistryKey(&_hKey, RegistryPath+'\\'+sTarifPlansSubkey, NULL,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
			DoCloseRegistryKey(&_hKey); // больше не нужен

			// сохраняем количество для контроля и удобства чтения
			DoWriteRegistryNumber(&hKey, "NumberOfTarifs",_dwCollectionSize);
			SetKey(hKey);
			//CTarifPlansCollection::CVector::iterator _Element = pTarifPlansColl->GetData()->begin();
			for (signed int si = _dwCollectionSize-1; si >= 0; --si)
			{
				DoCreateRegistryKey(&hKey, GenerateName("TarifPlan", si, 2), "",
					REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_hKey, NULL);

				SetKey(_hKey);

				// Сохранение разрешнных ЮзерНэймов
				{
					DWORD dwNum = (*pTarifPlansColl)[si].GetUserNames()->size();
					DoWriteRegistryNumber(&_hKey, "NumberUserNames", dwNum);
					for (int i = 0; i < dwNum; ++i)
					{
						DoWriteRegistryString( &_hKey, GenerateName("UserName", i, 2),
							(*pTarifPlansColl)[si].GetUserNames()->operator[](i) );
					}
				}

				DoWriteRegistryString(&_hKey, "Name",
						(*pTarifPlansColl)[si].GetName());
				DoWriteRegistryNumber(&_hKey, "Permission",
						(*pTarifPlansColl)[si].GetPermission());
				SaveHourMinuteTime("Standardization",
						(*pTarifPlansColl)[si].GetStandardization());
				SaveHourMinuteTime("TimeQuant",
						(*pTarifPlansColl)[si].GetTimeQuant());

				DWORD dwValue = (*pTarifPlansColl)[si].size();
				DoWriteRegistryNumber(&_hKey, "NumberOfIntervals", dwValue);

				CTarifPlan::iterator _ElementInterval =
						(*pTarifPlansColl)[si].GetData()->begin();
				for (signed int sj = dwValue-1; sj >= 0; --sj, ++_ElementInterval)
				{
					DoCreateRegistryKey(&_hKey, GenerateName("Interval", sj, 2), "",
						REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &__hKey, NULL);

					SetKey(__hKey);

					DoWriteRegistryNumber(&__hKey, "Currency",
						(*_ElementInterval)->GetTarif());
					SaveHourMinuteTime("Start",
						(*_ElementInterval)->GetStartTime());
					SaveHourMinuteTime("Finish",
						(*_ElementInterval)->GetFinishTime());

					DoCloseRegistryKey(&__hKey);
				}

				DoCloseRegistryKey(&_hKey);
			}

			DoCloseRegistryKey(&hKey);

		}catch(...){ // закрываем то, что пооткрывали в реестре
			DoCloseRegistryKey(&hKey);
			DoCloseRegistryKey(&_hKey);
			DoCloseRegistryKey(&__hKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(
			std::string("SaveTarifPlansToKey ") + RegistryPath +
			std::string(" failed: ") + (std::string)e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			std::string("SaveTarifPlansToKey ") + RegistryPath +
			std::string(" failed: unknown exception"), bDoNotWriteDuplicates);
	}
}
// end of void SaveTarifPlansToKey


std::string CMasterRegistryStorer::MashinesCollectionSaveToStr()
{	return TodayHistoryKey() +'\\'+sMashinesSubkey; }

std::string CMasterRegistryStorer::TodayHistoryKey()
{
	return sMasterRegistryPath +'\\'+
		sHistorySubkey +'\\'+ TodayInStr();
}


// Наследки CNetworkParametersDataReader
void CMasterRegistryStorer::ReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder *pHolder)
{
	try{
		SetKey(HKEY_LOCAL_MACHINE);
		SetSecurityAccessMask(KEY_ALL_ACCESS);
		*(GetSubKeyName()) = sMasterRegistryPath +'\\'+ sCommunicationSubkey;

		HKEY hkKey =0;
		try{
			DoOpenRegistryKey(&hkKey);
			DoReadCommonTCP_IP_SocketHolderData(&hkKey, pHolder);
			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException& Error){
		throw CAnyLogableException(std::string("ReadCommonTCP_IP_SocketHolderData: ")+Error.what(), Error.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An unknown error occured in ReadCommonTCP_IP_SocketHolderData", bDoNotWriteDuplicates);
	}
}
// end of ReadCommonTCP_IP_SocketHolderData

void CMasterRegistryStorer::DoReadCommonTCP_IP_SocketHolderData(PHKEY phkKey, CTCP_IP_SocketHolder* pHolder)
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

// Читает из реестра данные для TCP_IP_Sender'а
void CMasterRegistryStorer::ReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender)
{
	// не читает из реестра данные для TCP_IP_Sender'а
}

	// Читает из реестра данные для TCP_IP_Listener'а
void CMasterRegistryStorer::ReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener)
{
	try{
		HKEY _hKey =0;
		DWORD dwValue;

		SetKey(HKEY_LOCAL_MACHINE);
		SetSecurityAccessMask(KEY_ALL_ACCESS);
		*(GetSubKeyName()) = sMasterRegistryPath +'\\'+ sCommunicationSubkey;

		try{
			DoOpenRegistryKey(&_hKey);
			DoReadRegistryNumber(&_hKey, "PortToListen", dwValue);
			pTCP_IP_Listener->SetPortToListen((u_short)dwValue & 0xffff);
			DoCloseRegistryKey(&_hKey);

		}catch(...){
			DoCloseRegistryKey(&_hKey);
			throw;
		}

	}catch(CAnyLogableException &e){
		throw CAnyLogableException((std::string)"ReadTCP_IP_ListenerData failed: "
			+(std::string)e.what(), e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("ReadTCP_IP_ListenerData failed",
			bDoNotWriteDuplicates);
	}
}


void CMasterRegistryStorer::ReadMasterConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder)
{
	try{
		SetKey(HKEY_LOCAL_MACHINE);
		SetSecurityAccessMask(KEY_ALL_ACCESS);
		*(GetSubKeyName()) = sMasterRegistryPath +'\\'+ sCommunicationSubkey;

		HKEY hkKey =0;
		try{
			DoOpenRegistryKey(&hkKey);
			DoReadMasterConnectedSocketHolder(&hkKey, pHolder);
			DoReadCommonTCP_IP_SocketHolderData(&hkKey, pHolder);
			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException& Error){
		throw CAnyLogableException(std::string("An error occured in CMasterRegistryStorer::ReadMasterConnectedSocketHolder: ") + Error.what(), Error.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An unknown error occured in CMasterRegistryStorer::ReadMasterConnectedSocketHolder", bDoNotWriteDuplicates);
	}
}
// End of ReadMasterConnectedSocketHolder


void CMasterRegistryStorer::DoReadMasterConnectedSocketHolder(PHKEY phkKey, CTCP_IP_SocketHolder* pHolder)
{
	DWORD dwReadData;

	std::string sSlavePort = "SlavePort";
	DoReadRegistryNumber(phkKey, sSlavePort, dwReadData);
	pHolder->SetPortToConnectTo(0xffff & dwReadData);
}
// End of DoReadMasterConnectedSocketHolder


void CMasterRegistryStorer::ReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pReceiver)
{
	try{
		SetKey(HKEY_LOCAL_MACHINE);
		SetSecurityAccessMask(KEY_ALL_ACCESS);
		*(GetSubKeyName()) = sMasterRegistryPath +'\\'+ sCommunicationSubkey;

		HKEY hkKey =0;
		try{
			DoOpenRegistryKey(&hkKey);
			DoReadTCP_IP_ReceiverData(&hkKey, pReceiver);
			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException& Error){
		throw CAnyLogableException(std::string("An error occured in CMasterRegistryStorer::ReadTCP_IP_ReceiverData: ") + Error.what(), Error.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An unknown error occured in CMasterRegistryStorer::ReadTCP_IP_ReceiverData", bDoNotWriteDuplicates);
	}
}
// End of ReadTCP_IP_ReceiverData


void CMasterRegistryStorer::DoReadTCP_IP_ReceiverData(PHKEY phkKey, CTCP_IP_Receiver* pReceiver)
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


void CMasterRegistryStorer::ReadMasterManager(CMasterManager* pManager)
{
	try{
		SetKey(HKEY_LOCAL_MACHINE);
		SetSecurityAccessMask(KEY_ALL_ACCESS);
		*(GetSubKeyName()) = sMasterRegistryPath +'\\'+ sOthersSubkey;

		HKEY hkKey =0;
		try{
			DoOpenRegistryKey(&hkKey);
			DoReadMasterManagerFuflo(&hkKey, pManager);
			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException& Error){
		throw CAnyLogableException(std::string("An error occured in CMasterRegistryStorer::ReadMasterManager: ") + Error.what(), Error.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An unknown error occured in CMasterRegistryStorer::ReadMasterManager", bDoNotWriteDuplicates);
	}
}
// End of ReadMasterManager

void CMasterRegistryStorer::DoReadMasterManagerFuflo(PHKEY phkKey, CMasterManager* pManager)
{
	DWORD dwReadData;
	std::string sReadData;

	DoReadRegistryNumber(phkKey, "TimerPeriod", dwReadData);
	pManager->SetTimerPeriod(dwReadData);


	DoReadOneRegistryName(phkKey, "ClubName", sReadData);
	pManager->GetClubState()->SetClubName(sReadData);

	DoReadRegistryNumber(phkKey, sHoldHistoryTime, dwReadData);
	pManager->SetTimeSplitHist(CTimeStorage(dwReadData * A_Minute.GetTime()));
}
// End of DoReadMasterManagerFuflo


void CMasterRegistryStorer::ReadFinantialHistLoggerData(CFinantialHistoryLogger* pFinantialLogger)
{
	try{
		static unsigned int _count = 1;
		char buff[0xff];
		// попытаемся прочитать внутренние настройки CMasterRegistryStorer
		HKEY hkKey =0;
		CFileUpdateManager::CFileName sStr;

		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath +'\\'+ sOthersSubkey;

			DoOpenRegistryKey(&hkKey);
			DoReadOneRegistryName(&hkKey, sSaveToPath, sStr);

			(*pFinantialLogger->GetDirectoryName()) = sStr;

			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(std::exception &e){
		throw CAnyLogableException(std::string(
			(std::string)"CMasterRegistryStorer ReadFinantialHistLoggerData failed: " +
			(std::string)e.what()).c_str(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(
			"CMasterRegistryStorer ReadFinantialHistLoggerData failed",
			bDoNotWriteDuplicates);
	}
}
//end of ReadFinantialHistLoggerData(CFinantialHistoryLogger* pFinantialLogger)

void CMasterRegistryStorer::ReadClubState(CClubState* pClubState)
{
	try{
		{
			CCycleInterval WorkingInterval;
			ReadWorkingInterval(&WorkingInterval);
			pClubState->SetWorkingInterval(&WorkingInterval);
		}

		HKEY hkKey =0;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			*(GetSubKeyName()) = sMasterRegistryPath
				+'\\'+ sOthersSubkey;
			DoOpenRegistryKey(&hkKey);
			SetKey(hkKey);

			pClubState->SetMaxIntervLength(
				ReadHourMinuteTime("MaxIntervalLength"));

			DoCloseRegistryKey(&hkKey);
		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException &e){
		throw CAnyLogableException((std::string)
			"ReadClubState failed: " + (std::string)e.what(),
				bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("ReadClubState failed",
				bDoNotWriteDuplicates);
	}
}

void CMasterRegistryStorer::FlushCurrToFile()
{
	if (m_IsStorageChanged)
	{
		CVersions Ver = m_Definer.GetVersion();
		if ( Ver == WinNT )
			if (m_pCurrFileUpdateManager != 0) // скидываем в файл
			{
				SaveCurrToFile(&m_pCurrFileUpdateManager->DoPrepareBeforeUpdate());
				m_pCurrFileUpdateManager->DoFinalizeUpdate();
			}
	}// if (m_IsStorageChanged)
}

void CMasterRegistryStorer::FlushHistToFile()
{
	try{
		if (m_IsStorageChanged)
		{
			HKEY _hKey = 0, _hYest = 0;
			DWORD _dwIsHistoryYesturday;
			CVersions Ver = m_Definer.GetVersion();

			CTimeStorage CurrTime = CurrentTime();

			if ( Ver == WinNT )
			{
				try{
					{
						SetKey(HKEY_LOCAL_MACHINE);
						SetSecurityAccessMask(KEY_ALL_ACCESS);
						(*GetSubKeyName()) = sMasterRegistryPath;
						DoOpenRegistryKey(&_hKey);

						DoCreateRegistryKey(&_hKey, sHistorySubkey +'\\'+
							DateInStr(CurrTime-A_Day), NULL,
							REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
							&_hYest, &_dwIsHistoryYesturday);
						if (_dwIsHistoryYesturday == REG_CREATED_NEW_KEY)
						{
							DoDeleteRegistryKeyWithSubkeys(&_hYest, "");
						}

						DoCloseRegistryKey(&m_Hist_key);
						DoCreateRegistryKey(&_hKey, sHistorySubkey +'\\'+
							TodayInStr(), NULL, REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS, NULL, &m_Hist_key, NULL);
					}
					if (m_pHistFileUpdateManager != 0) // скидываем в файл
					{
						m_pHistFileUpdateManager->SetBaseFileName(&TodayInFileName());

						SaveHistToFile(&m_pHistFileUpdateManager->DoPrepareBeforeUpdate());
						m_pHistFileUpdateManager->DoFinalizeUpdate();
					}

					if (m_pYestFileUpdateManager != 0 && _dwIsHistoryYesturday == REG_OPENED_EXISTING_KEY)
					{
						m_pYestFileUpdateManager->SetBaseFileName(&DateInFileName(CurrTime-A_Day));

						SaveKeyToFile(_hYest, &m_pYestFileUpdateManager->DoPrepareBeforeUpdate());
						m_pYestFileUpdateManager->DoFinalizeUpdate();
					}

					DoCloseRegistryKey(&_hKey);
					DoCloseRegistryKey(&_hYest);

				}catch(...){
					DoCloseRegistryKey(&_hKey);
					DoCloseRegistryKey(&_hYest);
					throw;
				}
			}

			m_IsStorageChanged = false;
		}// if (m_IsStorageChanged)
	}catch(CAnyLogableException &e){
		throw CAnyLogableException((std::string)
			"FlushHistToFile failed: " + (std::string)e.what(),
				e.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("FlushHistToFile failed",
				bDoNotWriteDuplicates);
	}
}
// end of void CMasterRegistryStorer::FlushRegToFile()

void CMasterRegistryStorer::RestoreRegFromFile()
{
	CVersions Ver = m_Definer.GetVersion();
	if ( Ver == WinNT )
		if (m_pCurrFileUpdateManager != 0) // скидываем в файл
		{
			std::string sStr = m_pCurrFileUpdateManager->GetValidFileName();
			if (sStr != "")
				RestoreFromFile(&sStr);
		}
}
// end of RestoreRegFromFile()


bool CMasterRegistryStorer::SaveClubStateToHistory(CClubState* pClubState,
		const CTimeStorage& TimeToSplitHistory)
{
	SaveOperatorsToHistrory(pClubState->GetOperatorsCollection());
	SaveTarifPlansToHistrory(pClubState->GetTarifPlansCollection());
	SaveMashinesCollectionToHistory(pClubState->GetMashinesCollection());

	bool bResult = false;
	for (int i =0; i < pClubState->GetMashinesCollection()->size(); ++i)
	{
		CBusyIntervalsCollection _BIC;

		(*pClubState->GetMashinesCollection())[i].
			GetBusyIntervalsCollection()->SplitHistory(
				TimeToSplitHistory, &_BIC);

		if (_BIC.size() > 0)
		{
			bResult = true;
			SaveBusyIntervalsToHistory(i, &_BIC);
		}
	}

	m_IsStorageChanged = bResult;

	FlushHistToFile();

	return bResult;
}
//end of SaveClubState


// for CashStorer
void CMasterRegistryStorer::ReadCash(CCashdesk *Cash)
{
	HKEY hkKey =0;
	try{
		DWORD dwValue =0;
		std::string sStr;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath +'\\'+ sOthersSubkey;

			DoOpenRegistryKey(&hkKey);

			DoReadOneRegistryName(&hkKey, sCashLogName, sStr);

			*(Cash->GetLogger()->GetLogFileName()) = sStr;

			//DoReadRegistryNumber(&hkKey, sCashSum, dwValue);
			//Cash->SetInitialSum((CCurrency)dwValue, "Initialization from registry");

			DoReadRegistryNumber(&hkKey, sPermTakeOff, dwValue);
			Cash->SetPermission((CPermission)dwValue);

			DoCloseRegistryKey(&hkKey);

			// а теперь ещё кое-что посмотрим
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath +'\\'+ sCurrDataSubkey;

			DoOpenRegistryKey(&hkKey);
			try{
				DoReadRegistryNumber(&hkKey, sCashSum, dwValue);
				Cash->SetInitialSum((CCurrency)dwValue, "Initialization from registry");
			}catch(...){Cash->SetInitialSum(0, "Initialization from registry failed");}
				DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException& Error){
		throw CAnyLogableException((std::string)"CMasterRegistryStorer::ReadCash failed: "
			+(std::string)Error.what(), Error.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An unknown error occured in CMasterRegistryStorer::ReadCash", bDoNotWriteDuplicates);
	}
}

void CMasterRegistryStorer::SaveCash(CCashdesk *Cash)
{
	HKEY hkKey =0;
	try{
		DWORD dwValue =0;
		try{
			SetKey(HKEY_LOCAL_MACHINE);
			SetSecurityAccessMask(KEY_ALL_ACCESS);
			(*GetSubKeyName()) = sMasterRegistryPath +'\\'+ sCurrDataSubkey;

			DoOpenRegistryKey(&hkKey);

			dwValue = Cash->GetSum();
			DoWriteRegistryNumber(&hkKey, sCashSum, dwValue);

			DoCloseRegistryKey(&hkKey);

		}catch(...){
			DoCloseRegistryKey(&hkKey);
			throw;
		}

	}catch(CAnyLogableException& Error){
		throw CAnyLogableException((std::string)"CMasterRegistryStorer::SaveCash failed: "
			+(std::string)Error.what(), Error.GetWriteDuplicatesToLog());
	}catch(...){
		throw CAnyLogableException("An unknown error occured in CMasterRegistryStorer::SaveCash", bDoNotWriteDuplicates);
	}
	m_IsStorageChanged = true;
}