#ifndef __MOUSELOCKER_H__
#define __MOUSELOCKER_H__

#include "InputLocker.h"


#define _WIN32_WINNT 0x0500

class CMouseLocker : public CInputLocker
{
	// ������������ ����

	private:
	protected:
		typedef void CSetLockingCursor(DWORD bNewValue);
		typedef DWORD CGetLockingCursor();

		virtual void DoLoadDLLProcedures();
		virtual void DoInitExceptionStringAddition() {*m_pExceptionStringAddition = "mouse";};
		virtual int GetHookType() {return WH_MOUSE;};

		CSetLockingCursor* m_pSetLockingCursor;
		CGetLockingCursor* m_pGetLockingCursor;
	public:
		// ����������� �� ����������
		CMouseLocker(CSlaveDataReader* pDataReader) : CInputLocker(pDataReader)
		{
			m_pSetLockingCursor = 0;
			m_pGetLockingCursor = 0;
				try
				{
					DoInitDLL();

					DoSetGurrentThreadID();

					// ����� ����� �������
					m_pSetLocked(false);
						if (m_pGetLocked())
							throw CAnyLogableException("Can't set bMouseLocked in DLL", bDoNotWriteDuplicates);

					SetHookProcedure();
				}
				catch(CAnyLogableException& Error)
				{
					DoDeleteEverything();
					throw CAnyLogableException(Error.what(), Error.GetWriteDuplicatesToLog());
				}
				catch(...)
				{
					DoDeleteEverything();
					throw CAnyLogableException("An unknown error occured in CMouseLocker::CMouseLocker", bWriteDuplicates);
				}
		};
		// ����������
		virtual ~CMouseLocker();

		// ����������
		virtual void Lock();
		// ����������
		virtual void UnLock();
};


#endif // __MOUSELOCKER_H__