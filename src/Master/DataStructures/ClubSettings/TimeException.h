/*
	��������� ���������� � ��������, 
	���������� �� ��������.
*/

#ifndef _LX_TIMEEXCEPTIONS_H__
#define _LX_TIMEEXCEPTIONS_H__

#include "..\..\..\Slave\Slave\Exceptions.h"

class CTimeException : public CAnyLogableException
{
	protected:
		virtual void _Doraise() const {_RAISE(*this);};
	public:
		// ����������� � ��������� m_bWriteDuplicatesToLog
		explicit CTimeException(const std::string& _S, bool bIsWriteDuplicates)
			: CAnyLogableException(_S, bIsWriteDuplicates){};
		// ����������
		virtual ~CTimeException() {};
};


#endif // _LX_TIMEEXCEPTIONS_H__