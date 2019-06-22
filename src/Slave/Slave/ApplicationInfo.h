#ifndef __APPLICATIONINFO_H__
#define __APPLICATIONINFO_H__


#include <string>

class CApplicationInfo
{
	private:
	protected:
		DWORD m_dwSessionId;
		DWORD m_dwMainThreadId;
		HANDLE m_hProcess;
		HANDLE m_hThread;
		// Имя юзера сессии m_dwSessionId
		std::string m_sUserName;
	public:
		CApplicationInfo();
		virtual ~CApplicationInfo();

		bool operator==(CApplicationInfo& a_Info);

		// Обертки
		DWORD GetSessionId() {return m_dwSessionId;};
		void SetSessionID(DWORD a_dwNew) {m_dwSessionId = a_dwNew;};
		DWORD GetMainThreadId() {return m_dwMainThreadId;};
		void SetMainThreadId(DWORD a_dwNew) {m_dwMainThreadId = a_dwNew;};
		std::string* GetUserName() {return &m_sUserName;};
		HANDLE GetThreadHandle() {return m_hThread;};
		void SetThreadHandle(HANDLE a_hNew) {m_hThread = a_hNew;};
		HANDLE GetProcessHandle() {return m_hProcess;};
		void SetProcessHandle(HANDLE a_hNew) {m_hProcess = a_hNew;};
};


#endif // __APPLICATIONINFO_H__