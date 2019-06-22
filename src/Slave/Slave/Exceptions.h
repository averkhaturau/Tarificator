#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__


#include <stdexcept>


// Константы, чтобы не вспоминать каждый раз
const bool bWriteDuplicates = true;
const bool bDoNotWriteDuplicates = false;


class CAnyLogableException : public std::exception
{
	// Исключение, текст которого подлежит занесению в лог

	protected:
		virtual void _Doraise() const {_RAISE(*this);}

		// true, если надо писАть повторяющиеся мессаги. По умолчанию false.
		bool m_bWriteDuplicatesToLog;
	public:
		// Конструктор. Надо указывать текст исключения.
		//explicit CAnyLogableException(const std::string& _S):
				//std::exception(_S.c_str()) {m_bWriteDuplicatesToLog = false;}

		// Конструктор с указанием m_bWriteDuplicatesToLog
		explicit CAnyLogableException(const std::string& _S, bool bIsWriteDuplicates):
				std::exception(_S.c_str()) {m_bWriteDuplicatesToLog = bIsWriteDuplicates;}
		// Деструктор
		virtual ~CAnyLogableException() {}

		// Обертки
		void SetWriteDuplicatesToLog(bool bNewValue) {m_bWriteDuplicatesToLog = bNewValue;};
		bool GetWriteDuplicatesToLog() {return m_bWriteDuplicatesToLog;};
};


#endif // __EXCEPTIONS_H__