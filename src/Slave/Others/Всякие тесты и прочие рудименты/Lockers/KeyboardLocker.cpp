#include "stdafx.h"

#include "KeyboardLocker.h"
#include "Exceptions.h"




CKeyboardLocker::~CKeyboardLocker()
{
	UnLock();
	RemoveHookProcedure();
	UnLockSpecialKeys();
}
// End of ~CKeyboardLocker()


void CKeyboardLocker::Lock()
{
		if (!m_bLocked)
		{
			// Чтобы прошла залочка
			m_pSetLocked(true);
				if (!m_pGetLocked())
					throw CAnyLogableException("Can't set bKeyboardLocked in DLL", bDoNotWriteDuplicates);

				try
				{
					LockSpecialKeys();
				}
				catch(CAnyLogableException)
				{
					throw CAnyLogableException("Can't lock usual keys", bDoNotWriteDuplicates);
				}
				catch(...)
				{
					throw CAnyLogableException("An unknown error occured in CKeyboardLocker:: Lock(): can't lock usual keys", bDoNotWriteDuplicates);
				}

			// Это не глюк. Если возникло исключение при закрытии - значит,
			// клавиатура открыта.
			m_bLocked = true;
		}
}
// End of Lock()


void CKeyboardLocker::UnLock()
{
		if (m_bLocked)
		{
			// Чтобы снять залочку
			m_pSetLocked(false);
				if (m_pGetLocked())
					throw CAnyLogableException("Can't set bKeyboardLocked in DLL", bDoNotWriteDuplicates);

				try
				{
						if (!m_bIsSpecialKeysAlwaysLocked)
							UnLockSpecialKeys();
				}
				catch(CAnyLogableException)
				{
					throw CAnyLogableException("Can't unlock usual keys", bDoNotWriteDuplicates);
				}
				catch(...)
				{
					throw CAnyLogableException("An unknown error occured in CKeyboardLocker::UnLock(): can't unlock usual keys", bDoNotWriteDuplicates);
				}

			// Это не глюк. Если возникло исключение при открытии - значит,
			// клавиатура закрыта.
			m_bLocked = false;
		}
}
// End of UnLock()


void CKeyboardLocker::LockSpecialKeys()
{
		/*try
		{
			DWORD uiState;
				if (!SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, TRUE, &uiState, 0))
				{
					throw CAnyLogableException("Can't lock special keys", bDoNotWriteDuplicates);
				}
			m_pSetuiState(uiState);
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CKeyboardLocker::LockSpecialKeys (may be invalid function address in dll)", bDoNotWriteDuplicates);
		}*/
}
// End of LockSpecialKeys


void CKeyboardLocker::UnLockSpecialKeys()
{
		/*try
		{
			DWORD uiState = m_pGetuiState();
				if (!SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, FALSE, &uiState, 0))
				{
					throw CAnyLogableException("!", bDoNotWriteDuplicates);
				}
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CKeyboardLocker::UnLockSpecialKeys (may be invalid function address in dll)", bDoNotWriteDuplicates);
		}*/
}
// End of UnLockSpecialKeys


void CKeyboardLocker::DoLoadDLLProcedures()
{
	// Exceptions проверяются в CInputLocker::DoInitDLL()
	m_pHookProc = (CHookProc*)GetProcAddress(GetDLLModule(), "KeyboardProc");
	m_pGetHook = (CGetHook*)GetProcAddress(GetDLLModule(), "GetKeyboardHook");
	m_pSetHook = (CSetHook*)GetProcAddress(GetDLLModule(), "SetKeyboardHook");

	m_pSetuiState = (CSetuiState*)GetProcAddress(GetDLLModule(), "SetuiState");
		if (!m_pSetuiState)
			throw CAnyLogableException("Can't get \"SetuiState\" procedure address from dll", bDoNotWriteDuplicates);

	m_pGetuiState = (CGetuiState*)GetProcAddress(GetDLLModule(), "GetuiState");
		if (!m_pGetuiState)
			throw CAnyLogableException("Can't get \"GetuiState\" procedure address from dll", bDoNotWriteDuplicates);

	m_pGetLocked = (CGetLocked*)GetProcAddress(GetDLLModule(), "GetKeyboardLocked");
		if (!m_pGetLocked)
			throw CAnyLogableException("Can't get \"GetKeyboardLocked\" procedure address from dll", bDoNotWriteDuplicates);

	m_pSetLocked = (CSetLocked*)GetProcAddress(GetDLLModule(), "SetKeyboardLocked");
		if (!m_pSetLocked)
			throw CAnyLogableException("Can't get \"SetKeyboardLocked\" procedure address from dll", bDoNotWriteDuplicates);

	m_pSetTaskbarWnd = (CSetWnd*)GetProcAddress(GetDLLModule(), "SetTaskbarWnd");
		if (!m_pSetTaskbarWnd)
			throw CAnyLogableException("Can't get \"SetTaskbarWnd\" procedure address from dll", bDoNotWriteDuplicates);
	m_pGetTaskbarWnd = (CGetWnd*)GetProcAddress(GetDLLModule(), "GetTaskbarWnd");
		if (!m_pSetTaskbarWnd)
			throw CAnyLogableException("Can't get \"GetTaskbarWnd\" procedure address from dll", bDoNotWriteDuplicates);
}
// End of DoLoadDLLProcedures()


void CKeyboardLocker::OnReCheckSpecialKeys()
{
		if (m_bLocked)
		{
			LockSpecialKeys();
		}
		else
		{
				if ( m_bIsSpecialKeysAlwaysLocked && m_bIsUserRestricted )
					LockSpecialKeys();
				else
					UnLockSpecialKeys();
		}
}
// End of OnReCheckSpecialKeys()


int CKeyboardLocker::GetHookType()
{
	return WH_KEYBOARD_LL;
}
// End of GetHookType()
