#include "stdafx.h"

#include "InputLocker.h"


CInputLocker::CInputLocker(CSlaveDataReader* pDataReader)
{
		try
		{
			DoInitPointers();

			pDataReader->ReadInputLockerData(this);

				#ifdef _DEBUG
					HMODULE hTemp = GetDLLModule();
					bool bTest = true;
				#endif // _DEBUG
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CInputLocker::CInputLocker", bWriteDuplicates);
		}
}
// End of CInputLocker


CInputLocker::~CInputLocker()
{
	DoDeleteEverything();
}
// End of ~CInputLocker()


void CInputLocker::DoInitPointers()
{
	m_pHookProc = 0;
	m_pGetHook = 0;
	m_pSetHook = 0;
	m_pHookProceduresDLLNames = 0;
	m_pExceptionStringAddition = 0;
	m_pGetLocked = 0;
	m_pSetLocked = 0;
	m_pSetTaskbarWnd = 0;
	m_pGetTaskbarWnd = 0;

	m_pHookProceduresDLLNames = new CNamesCollection;

	m_pExceptionStringAddition = new std::string;
}
// End of InitPointers()


void CInputLocker::DoDeleteEverything()
{
		if (GetDLLModule())
		{
			FreeLibrary(GetDLLModule());
			GetDLLModule() = 0;
		}
		if (m_pExceptionStringAddition)
		{
			delete m_pExceptionStringAddition;
			m_pExceptionStringAddition = 0;
		}
		if (m_pHookProceduresDLLNames)
		{
			delete m_pHookProceduresDLLNames;
			m_pHookProceduresDLLNames = 0;
		}
}
// End of DoDeleteEverything()


void CInputLocker::DoInitDLL()
{
		try
		{
			bool bModule = true;
				if (GetDLLModule())
					// Если не надо грузить dll
					bModule = false;

				for (SizeType i = 0; ( bModule && (i < m_pHookProceduresDLLNames->size()) ); i++)
				{
					GetDLLModule() = LoadLibrary( (*m_pHookProceduresDLLNames)[i].c_str() );
						if (GetDLLModule())
							bModule = false;
				}
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CInputLocker::DoInitDLL", bDoNotWriteDuplicates);
		}

		if ( !(GetDLLModule()) )
		{
			throw CAnyLogableException("Can't load DLL", bWriteDuplicates);
		}

	DoInitExceptionStringAddition();

	std::string ErrorString;

		// Чтобы проинились указатели на функции в DLL
		try
		{
			DoLoadDLLProcedures();
		}
		catch(CAnyLogableException& Error)
		{
			ErrorString = Error.what();
		}
		catch(...)
		{
			ErrorString = "An unknown error occured in DoLoadDLLProcedures";
		};

	std::string ExceptionString = "";
		if (!m_pHookProc)
		{
			ExceptionString += "Can't get ";
			// Добавляется слово keyboard или mouse
			ExceptionString += *m_pExceptionStringAddition;
			ExceptionString += " procedure address from dll";
		}
		if (!m_pGetHook)
		{
				if (ExceptionString.size() > 1)
					ExceptionString += "; ";
			ExceptionString += "Can't get ";
			ExceptionString += *m_pExceptionStringAddition;
			ExceptionString += " \"Get\" procedure address from dll";
		}
		if (!m_pSetHook)
		{
				if (ExceptionString.size() > 1)
					ExceptionString += "; ";
			ExceptionString += "Can't get ";
			ExceptionString += *m_pExceptionStringAddition;
			ExceptionString += " \"Set\" procedure address from dll";
		}
		if (ErrorString.size() > 1)
		{
				if (ExceptionString.size() > 1)
					ExceptionString += "; ";
			ExceptionString += ErrorString;
		}
		if (!m_pSetTaskbarWnd)
		{
				if (ExceptionString.size() > 1)
					ExceptionString += "; ";
			ExceptionString += "Can't get ";
			ExceptionString += *m_pExceptionStringAddition;
			ExceptionString += " \"SetTaskbarWnd\" procedure address from dll";
		}
		if (!m_pGetTaskbarWnd)
		{
				if (ExceptionString.size() > 1)
					ExceptionString += "; ";
			ExceptionString += "Can't get ";
			ExceptionString += *m_pExceptionStringAddition;
			ExceptionString += " \"GetTaskbarWnd\" procedure address from dll";
		}

		if ( ExceptionString.size() > 1 )
			throw CAnyLogableException(ExceptionString, bWriteDuplicates);
}
// End of DoInitDLL()


void CInputLocker::SetHookProcedure()
{
		try
		{
			HHOOK hHook = SetWindowsHookEx(GetHookType(), m_pHookProc, GetDLLModule(), 0);
				if (!hHook)
				{
					std::string ErrorString = "Can't lock ";
					ErrorString += *m_pExceptionStringAddition;
					throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
				}

			m_pSetHook(hHook);
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			std::string ErrorString = "An unknown error occured while locking ";
			ErrorString += *m_pExceptionStringAddition;
			ErrorString += " (may be invalid procedures in DLL)";
			throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
		}
}
// End of SetHookProcedure()


void CInputLocker::RemoveHookProcedure()
{
		try
		{
				if (GetDLLModule())
						if (m_pGetHook())
						{
							BOOL bResult = UnhookWindowsHookEx(m_pGetHook());
								if (!bResult)
								{
									std::string ErrorString = "Can't unlock ";
									ErrorString += *m_pExceptionStringAddition;
									throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
								}
							m_pSetHook(0);
						}
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			std::string ErrorString = "An unknown error occured while unlocking ";
			ErrorString += *m_pExceptionStringAddition;
			ErrorString += " (may be invalid procedures in DLL)";
			throw CAnyLogableException(ErrorString, bDoNotWriteDuplicates);
		}
}
// End of RemoveHookProcedure()


void CInputLocker::DoSetGurrentThreadID()
{
		try
		{
			CSetCallbackThreadID* pSetCallbackThreadID = (CSetCallbackThreadID*)GetProcAddress(GetDLLModule(), "SetCallbackThreadID");
				if (!pSetCallbackThreadID)
					throw CAnyLogableException("can't get \"SetCallbackThreadID\" procedure address from DLL", bDoNotWriteDuplicates);
			pSetCallbackThreadID(GetCurrentThreadId());
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CInputLocker::DoSetGurrentThreadID(): ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch (...)
		{
			throw CAnyLogableException("An unknown error occured in CInputLocker::DoSetGurrentThreadID() (may be can't execute \"SetCallbackThreadID\" procedure from DLL)", bDoNotWriteDuplicates);
		}
}
// End of DoSetGurrentThreadID()


HMODULE& CInputLocker::GetDLLModule()
{
	return m_StaticClass.GetModule();
}
// End of GetDLLModule()


void CInputLocker::SetTaskbarWnd(HWND a_hNew)
{
		if ( (m_pSetTaskbarWnd) && (m_pGetTaskbarWnd) )
		{
			m_pSetTaskbarWnd(a_hNew);
				if ( a_hNew != m_pGetTaskbarWnd() )
					throw CAnyLogableException("Can't set taskbar window to dll in CInputLocker::SetTaskbarWnd", bDoNotWriteDuplicates);
		}
}
// End of SetTaskbarWnd
