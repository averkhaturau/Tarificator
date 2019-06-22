#ifndef __WTSAPPLICATIONWAITER_H__
#define __WTSAPPLICATIONWAITER_H__

#include "..\Desktop\ApplicationWaiter.h"


class CWTSApplicationWaiter : public CApplicationWaiter
{
	private:
	protected:
		DWORD m_dwSessionId;
	public:
		CWTSApplicationWaiter();
		virtual ~CWTSApplicationWaiter();

		// Обертки
		void SetSessionId(DWORD a_dwNew) {m_dwSessionId = a_dwNew;};
		DWORD GetSessionId() {return m_dwSessionId;};
};


#endif / __WTSAPPLICATIONWAITER_H__