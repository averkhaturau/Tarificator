#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


#include <string>


const std::string sSlaveRegistryPath = "SYSTEM\\CurrentControlSet\\Services\\Slave Service\\Parameters";
const std::string sExchangeRegistryPath = "SYSTEM\\CurrentControlSet\\Services\\Slave Service\\Exchange";
const std::string sUserNamePath = "SYSTEM\\CurrentControlSet\\Services\\Slave Service\\Parameters\\UserName";
const std::string sShellFoldersRegistryPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders";
const std::string sSlaveMutexName = "__Slave__Mutex__98274903840979328563248563248__";
const std::string sSlaveServiceName = "Slave Service";


#endif // __CONSTANTS_H__