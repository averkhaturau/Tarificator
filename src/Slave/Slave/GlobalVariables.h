#ifndef __GLOBALVARIABLES_H__
#define __GLOBALVARIABLES_H__


class CSlaveManager;
class CErrorsLogger;
class CRegistryDataReader;
class CSlaveTCP_IP_Communicator;


static CSlaveManager* pSlaveManager = 0;
static CErrorsLogger* pErrorsLogger = 0;
static CSlaveRegistryDataReader* pSlaveRegistryDataReader = 0;
// Коммуникатор
static CSlaveTCP_IP_Communicator* pCommunicator = 0;


#endif // __GLOBALVARIABLES_H__