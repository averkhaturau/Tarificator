#ifndef __KEYBOARDLOCKER_H__
#define __KEYBOARDLOCKER_H__

#include "InputLocker.h"


class CKeyboardLocker : public CInputLocker
{
	// Закрывальщик клавиатуры

	private:
	protected:
		typedef void CSetuiState(DWORD uiNewState);
		typedef DWORD CGetuiState();

		CSetuiState* m_pSetuiState;
		CGetuiState* m_pGetuiState;

		bool m_bIsSpecialKeysAlwaysLocked;
		// true, если юзер с короткими руками (т.е. у которого прописан
		// IconsFolder)
		bool m_bIsUserRestricted;

		//void LockUsualKeys();
		//void UnLockUsualKeys();

		virtual void DoLoadDLLProcedures();
		virtual void DoInitExceptionStringAddition() {*m_pExceptionStringAddition = "keyboard";};
		virtual int GetHookType();
	public:
		// Конструктор
		CKeyboardLocker(CSlaveDataReader* pDataReader) : CInputLocker(pDataReader)
		{
			m_pSetuiState = 0;
			m_pGetuiState = 0;
			m_bIsSpecialKeysAlwaysLocked = false;
			m_bIsUserRestricted = false;

			m_bIsSpecialKeysAlwaysLocked = false;
				try
				{
					pDataReader->ReadKeyboardLockerData(this);

					DoInitDLL();

						if (m_bIsSpecialKeysAlwaysLocked)
							LockSpecialKeys();

					DoSetGurrentThreadID();

					// Чтобы снять залочку
					m_pSetLocked(false);
						if (m_pGetLocked())
							throw CAnyLogableException("Can't set bKeyboardLocked in DLL", bDoNotWriteDuplicates);

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
					throw CAnyLogableException("An unknown error occured in CKeyboardLocker::CKeyboardLocker", bWriteDuplicates);
				}
		};
		// Деструктор
		virtual ~CKeyboardLocker();

		// Запрещение
		virtual void Lock();
		// Разрешение
		virtual void UnLock();

		void OnReCheckSpecialKeys();

		void LockSpecialKeys();
		void UnLockSpecialKeys();

		// Обертки
		void SetIsSpecialKeysAlwaysLocked(bool a_bNew) {m_bIsSpecialKeysAlwaysLocked = a_bNew;};
		bool GetIsSpecialKeysAlwaysLocked() {return m_bIsSpecialKeysAlwaysLocked;};
		void SetIsUserRestricted(bool a_bNew) {m_bIsUserRestricted = a_bNew;};
		bool GetIsUserRestricted() {return m_bIsUserRestricted;};
};


#endif // __KEYBOARDLOCKER_H__