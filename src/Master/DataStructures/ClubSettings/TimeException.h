/*
	Описывает исключения в объектах, 
	работающих со временем.
*/

#ifndef _LX_TIMEEXCEPTIONS_H__
#define _LX_TIMEEXCEPTIONS_H__

#include "..\..\..\Slave\Slave\Exceptions.h"

class CTimeException : public CAnyLogableException
{
	protected:
		virtual void _Doraise() const {_RAISE(*this);};
	public:
		// Конструктор с указанием m_bWriteDuplicatesToLog
		explicit CTimeException(const std::string& _S, bool bIsWriteDuplicates)
			: CAnyLogableException(_S, bIsWriteDuplicates){};
		// Деструктор
		virtual ~CTimeException() {};
};


#endif // _LX_TIMEEXCEPTIONS_H__