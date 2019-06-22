#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__


#include <stdexcept>


// ���������, ����� �� ���������� ������ ���
const bool bWriteDuplicates = true;
const bool bDoNotWriteDuplicates = false;


class CAnyLogableException : public std::exception
{
	// ����������, ����� �������� �������� ��������� � ���

	protected:
		virtual void _Doraise() const {_RAISE(*this);}

		// true, ���� ���� ������ ������������� �������. �� ��������� false.
		bool m_bWriteDuplicatesToLog;
	public:
		// �����������. ���� ��������� ����� ����������.
		//explicit CAnyLogableException(const std::string& _S):
				//std::exception(_S.c_str()) {m_bWriteDuplicatesToLog = false;}

		// ����������� � ��������� m_bWriteDuplicatesToLog
		explicit CAnyLogableException(const std::string& _S, bool bIsWriteDuplicates):
				std::exception(_S.c_str()) {m_bWriteDuplicatesToLog = bIsWriteDuplicates;}
		// ����������
		virtual ~CAnyLogableException() {}

		// �������
		void SetWriteDuplicatesToLog(bool bNewValue) {m_bWriteDuplicatesToLog = bNewValue;};
		bool GetWriteDuplicatesToLog() {return m_bWriteDuplicatesToLog;};
};


#endif // __EXCEPTIONS_H__