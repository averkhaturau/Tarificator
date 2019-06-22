#include "stdafx.h"

#include "GlobalLocker.h"
#include "Constants.h"
#include "Messages.h"



// Свободные функции
void Lock(CLocker* pLocker)
{
		if (pLocker)
			pLocker->Lock();
}
// End of Lock


void UnLock(CLocker* pLocker)
{
		if (pLocker)
			pLocker->UnLock();
}
// End of UnLock


BOOL CALLBACK MinimizeAll(HWND hwnd, LPARAM lParam)
{
	LONG lStyles = GetWindowLong(hwnd, GWL_STYLE);
		if ( (lStyles & WS_CAPTION) && (lStyles & WS_SYSMENU) &&
					(lStyles & WS_THICKFRAME) && (lStyles & WS_MINIMIZEBOX)
					&& (lStyles & WS_VISIBLE) )
		{
			PostMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
	return true;
}
// End of MinimizeAll




// CGlobalLocker


CGlobalLocker::CGlobalLocker(CSlaveDataReader* pDataReader)
{
	m_bLocked = false;

	m_pKeyboardLocker = 0;
	m_pMouseLocker = 0;

	m_bEnabled = true;
	m_bSavedState = false;

		try
		{
			m_pKeyboardLocker = new CKeyboardLocker(pDataReader);
				if (!m_pKeyboardLocker)
				{
					throw CAnyLogableException("Can't create keyboard locker 8-/", bWriteDuplicates);
				}

			m_pMouseLocker = new CMouseLocker(pDataReader);
				if (!m_pMouseLocker)
				{
					throw CAnyLogableException("Can't create mouse locker 8-/", bWriteDuplicates);
				}
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CGlobalLocker::CGlobalLocker", bWriteDuplicates);
		}
}
// End of CGlobalLocker


CGlobalLocker::~CGlobalLocker()
{
	DoDeleteEverything();
}
// End of ~CGlobalLocker()


void CGlobalLocker::DoDeleteEverything()
{
		if (m_pKeyboardLocker)
		{
			m_pKeyboardLocker->UnLock();
			m_pKeyboardLocker->RemoveHookProcedure();
		}
		if (m_pMouseLocker)
		{
			m_pMouseLocker->UnLock();
			m_pMouseLocker->RemoveHookProcedure();
		}

		if (m_pKeyboardLocker)
		{
			delete m_pKeyboardLocker;
			m_pKeyboardLocker = 0;
		}
		if (m_pMouseLocker)
		{
			delete m_pMouseLocker;
			m_pMouseLocker = 0;
		}
}
// End of DoDeleteEverything()


void CGlobalLocker::LockEverything()
{
		if (!m_bEnabled)
		{
			m_bSavedState = true;
			return;
		}

		if (!m_bLocked)
		{
			//ExecuteFunctions(Lock);

			DoExitToDesktop();

			PostThreadMessage(GetCurrentThreadId(), WM_NEED_TO_ACTIVATE, 0, 1);

			m_bLocked = true;
		}
}
// End of LockEverything()


void CGlobalLocker::UnLockEverything()
{
		if (!m_bEnabled)
		{
			m_bSavedState = false;
			return;
		}

		if (m_bLocked)
		{
			ExecuteFunctions(UnLock);

			m_bLocked = false;

		}
}
// End of UnLockEverything()


void CGlobalLocker::ExecuteFunctions(CLockUnlockFunction* Function)
{
		// Можно так просто, потому что при правильно написанной программе
		// этого происходить не будет
		if (!Function)
		{
			return;
		}

	CAnyLogableException* pKeyboardError = 0;
	CAnyLogableException* pMouseError = 0;

		// Обработка клавы
		try
		{
			Function(m_pKeyboardLocker);
		}
		catch(CAnyLogableException& Error)
		{
			pKeyboardError = new CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			pKeyboardError = new CAnyLogableException("An unknown error occured in CGlobalLocker", bWriteDuplicates);
		}

		// Обработка мыши
		try
		{
			Function(m_pMouseLocker);
		}
		catch(CAnyLogableException& Error)
		{
			pMouseError = new CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			pMouseError = new CAnyLogableException("An unknown error occured in CGlobalLocker", bWriteDuplicates);
		}

		if ((pKeyboardError) || (pMouseError))
		{
			std::string ExceptionString = "";
			bool bWriteToLog = true;

				if (pKeyboardError)
				{
					ExceptionString += (std::string)pKeyboardError->what();
					bWriteToLog &= pKeyboardError->GetWriteDuplicatesToLog();
				}
				if (pMouseError)
				{
						if (ExceptionString.size() > 1)
							ExceptionString += "; ";

					ExceptionString += (std::string)pMouseError->what();
					bWriteToLog &= pMouseError->GetWriteDuplicatesToLog();
				}

			throw CAnyLogableException(ExceptionString, bWriteToLog);
		}
}
// End of ExecuteFunctions


void CGlobalLocker::DoExitToDesktop()
{
		try
		{
			HWND hDesktopWindow = 0;
			hDesktopWindow = GetDesktopWindow();
				if (!hDesktopWindow)
					throw CAnyLogableException("Can't get desktop window 8-/", bDoNotWriteDuplicates);

			PostMessage(hDesktopWindow, WM_SYSCOMMAND, SC_TASKLIST, 0);

			//EnumWindows(MinimizeAll, 0);
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CGlobalLocker::DoExitToDesktop", bDoNotWriteDuplicates);
		}
}
// End of DoExitToDesktop()


void CGlobalLocker::SetEnabled(bool bNewEnabled)
{
		try
		{
				if (bNewEnabled)
				{
						if (m_bSavedState)
						{
							m_bLocked = false;
							LockEverything();
						}
						else
						{
							m_bLocked = true;
							UnLockEverything();
						}
				}
				else
				{
					m_bSavedState = m_bLocked;

					UnLockEverything();
				}
			m_bEnabled = bNewEnabled;
		}
		catch(CAnyLogableException)
		{
			throw;
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CGlobalLocker::SetEnabled", bDoNotWriteDuplicates);
		}
}
// End of SetEnabled
