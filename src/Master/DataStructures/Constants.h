#ifndef __MASTER_CONSTANTS_H__
#define __MASTER_CONSTANTS_H__


// Тарифная ставка измеряется в деньгах
typedef signed long int CCurrency;


// Registry Keys
const std::string sBusyIntervalsSubkey = "BusyIntervals" ;
const std::string sMasterRegistryPath = "Software\\_LX";
const std::string sTarifPlansSubkey  = "TarifPlans" ;
const std::string sOperatorsSubkey  = "Operators" ;
const std::string sMashinesSubkey  = "Mashines" ;
const std::string sHistorySubkey = "BusyIntervalsHistory\\History";
const std::string sCurrDataSubkey = "BusyIntervalsHistory\\CurrentData";
const std::string sCommunicationSubkey = "Communication";
const std::string sOthersSubkey = "Others";
const std::string sSpecDaysSubKey = "Holidays";

const std::string sLogFileNameValue = "LogFileName";
const std::string sSaveToPath = "SaveToPath";
const std::string sCashSum = "CashSum";
const std::string sCashLogName = "CashLogName";
const std::string sPermTakeOff = "PermissionTakeOff";

// Registry Values
const std::string sIntervalPrice = "Price";
const std::string sHoldHistoryTime = "TimeHoldHistoryInMinutes";


// Mutex name
const std::string sMainMutexName = "Tarification_Program__Master__Mutex___BE9807490B";

// Interface strings
#define NUM_HEADERS_IN_GRID 4
const std::string _cHeaders[NUM_HEADERS_IN_GRID] = {"Имя", "Статус", "Занятые интервалы", "Тарифный план"};
#define NUM_MASHINE_STATES 4
const std::string _cMashineStates[NUM_MASHINE_STATES] = {"Занято", "Cвободно", "Ожидание клиента", "Не определяется"};

// Messages to users
const std::string sMesNegativeCash = "Сумма в кассе не может стать отрицательной!";

#endif // __MASTER_CONSTANTS_H__
