#include "stdafx.h"

#include "MouseLocker.h"
#include "Constants.h"
#include "Exceptions.h"

//#include "..\ProceduresDLL\ProceduresDLL.h"


CMouseLocker::~CMouseLocker()
{
	UnLock();
	RemoveHookProcedure();
}
// End of ~CMouseLocker()


void CMouseLocker::Lock()
{
		if (!m_bLocked)
		{
				try
				{
					// Чтобы курсор замер ровно там, где он находится сейчас
					m_pSetLockingCursor(1);

					// Чтобы прошла залочка
					m_pSetLocked(true);
						if (!m_pGetLocked())
							throw CAnyLogableException("Can't set bMouseLocked in DLL", bDoNotWriteDuplicates);
				}
				catch(...)
				{
					throw CAnyLogableException("An unknown error occured in CMouseLocker::Lock (may be can't execute SetLockingMouseCursorMovingNow from DLL)", bDoNotWriteDuplicates);
				}

			m_bLocked = true;
		}
}
// End of Lock()


void CMouseLocker::UnLock()
{
		if (m_bLocked)
		{
			// Чтобы снять залочку
			m_pSetLocked(false);
				if (m_pGetLocked())
					throw CAnyLogableException("Can't set bMouseLocked in DLL", bDoNotWriteDuplicates);

				// Чтобы курсор ходил везде
				if (!ClipCursor(NULL))
				{
					throw CAnyLogableException("Can't release mouse cursor moving", bDoNotWriteDuplicates);
				}

			m_bLocked = false;
		}
}
// End of UnLock()


void CMouseLocker::DoLoadDLLProcedures()
{
	// Exceptions проверяются в CInputLocker::DoInitDLL()
	m_pHookProc = (CHookProc*)GetProcAddress(GetDLLModule(), "MouseProc");
	m_pGetHook = (CGetHook*)GetProcAddress(GetDLLModule(), "GetMouseHook");
	m_pSetHook = (CSetHook*)GetProcAddress(GetDLLModule(), "SetMouseHook");

	// Тут надо самому обработать исключение
	m_pSetLockingCursor = (CSetLockingCursor*)GetProcAddress(GetDLLModule(), "SetLockingCursor");
		if (!m_pSetLockingCursor)
			throw CAnyLogableException("Can't get \"SetLockingCursor\" procedure address from dll", bDoNotWriteDuplicates);

	m_pGetLockingCursor = (CGetLockingCursor*)GetProcAddress(GetDLLModule(), "GetLockingCursor");
		if (!m_pGetLockingCursor)
			throw CAnyLogableException("Can't get \"GetLockingCursor\" procedure address from dll", bDoNotWriteDuplicates);

	m_pGetLocked = (CGetLocked*)GetProcAddress(GetDLLModule(), "GetMouseLocked");
		if (!m_pGetLocked)
			throw CAnyLogableException("Can't get \"GetMouseLocked\" procedure address from dll", bDoNotWriteDuplicates);

	m_pSetLocked = (CSetLocked*)GetProcAddress(GetDLLModule(), "SetMouseLocked");
		if (!m_pGetLocked)
			throw CAnyLogableException("Can't get \"SetMouseLocked\" procedure address from dll", bDoNotWriteDuplicates);

	m_pSetTaskbarWnd = (CSetWnd*)GetProcAddress(GetDLLModule(), "SetTaskbarWnd");
		if (!m_pSetTaskbarWnd)
			throw CAnyLogableException("Can't get \"SetTaskbarWnd\" procedure address from dll", bDoNotWriteDuplicates);
	m_pGetTaskbarWnd = (CGetWnd*)GetProcAddress(GetDLLModule(), "GetTaskbarWnd");
		if (!m_pSetTaskbarWnd)
			throw CAnyLogableException("Can't get \"GetTaskbarWnd\" procedure address from dll", bDoNotWriteDuplicates);
}
// End of DoLoadDLLProcedures()
