#ifndef __NETWORKCONSTANTS_H__
#define __NETWORKCONSTANTS_H__

#include <string>
#include <vector>

#include "Messages.h"
#include "MasterMessages.h"


// Длина буфера, достаточная для приема мессаг
const DWORD dwBufferLength = 10000;

const DWORD dwMasterToSlaveMsgLength = 5;
const DWORD MasterToSlaveMessages[dwMasterToSlaveMsgLength] =
			{0, WM_UNLOCK_REQUIRED, WM_LOCK_REQUIRED, WM_RESTART_REQUIRED,
			WM_TURNOFF_REQUIRED};
const std::string sMasterToSlavePrefix = "Master to slave command: ";

const DWORD dwSlaveToMasterMsgLength = 6;
const DWORD SlaveToMasterMessages[dwSlaveToMasterMsgLength] =
			{0, WM_LOCK_SUCCESS_ACKNOWLEDGE, WM_UNLOCK_SUCCESS_ACKNOWLEDGE,
			WM_LOCK_FAIL_ACKNOWLEDGE, WM_UNLOCK_FAIL_ACKNOWLEDGE,
			WM_RE_CHECK_STATE_REQUEST};
const std::string sSlaveToMasterPrefix = "Slave to master command: ";


#endif // __NETWORKCONSTANTS_H__