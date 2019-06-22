/* Implementation of CDayHistory */
#include "stdafx.h"

#include "DayHistory.h"
#include "..\..\..\Slave\Slave\Exceptions.h"

std::string CDayHistory::TodayInStr()
{
	try{
		const int buflen = 16;
		char _DateBuffer[buflen];
		int iSize;
		
		if (0 == (iSize = GetDateFormat(NULL, 0, 0,
					"dd.MM.yyyy", _DateBuffer, buflen)) ) 
			throw CAnyLogableException("TodayInStr failed", bDoNotWriteDuplicates);

		return std::string(_DateBuffer);
	}catch(std::exception &e){
		throw CAnyLogableException(std::string("TodayInStr failed: ")
			+ e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(std::string("TodayInStr failed"),
			bDoNotWriteDuplicates);
	}
}

std::string CDayHistory::DateInStr(const CTimeStorage& Date)
{
	try{
		const int buflen = 16;
		char _DateBuffer[buflen];
		int iSize=0;
		SYSTEMTIME _SysTime;
		Date.GetTime(&_SysTime);

		if (0 == (iSize = GetDateFormat(NULL, 0, &_SysTime,
				"dd.MM.yyyy", _DateBuffer, buflen)) ) 
			throw CAnyLogableException("GetDateFormat failed", bDoNotWriteDuplicates);
		
		return std::string(_DateBuffer);

	}catch(std::exception &e){
		throw CAnyLogableException(std::string("DateInStr faild because ")+e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("DateInStr faild: unknown exception", bDoNotWriteDuplicates);
	}
}

std::string CDayHistory::TodayInFileName()
{
	try{
		const int buflen = 16;
		char _DateBuffer[buflen];
		int iSize;
		
		if (0 == (iSize = GetDateFormat(NULL, 0, 0,
					"yy_MM_dd", _DateBuffer, buflen)) ) 
			throw CAnyLogableException("TodayInFileName failed", bDoNotWriteDuplicates);

		return std::string(_DateBuffer)+(std::string)".dat";

	}catch(std::exception &e){
		throw CAnyLogableException(std::string("TodayInFileName failed: ")
			+ e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(std::string("TodayInFileName failed"),
			bDoNotWriteDuplicates);
	}
}


std::string CDayHistory::DateInFileName(const CTimeStorage& Date)
{
	try{
		const int buflen = 16;
		char _DateBuffer[buflen];
		int iSize=0;
		SYSTEMTIME _SysTime;
		Date.GetTime(&_SysTime);

		if (0 == (iSize = GetDateFormat(NULL, 0, &_SysTime,
				"yy_MM_dd", _DateBuffer, buflen)) ) 
			throw CAnyLogableException("GetDateFormat failed", bDoNotWriteDuplicates);

		return std::string(_DateBuffer)+(std::string)".dat";

	}catch(std::exception &e){
		throw CAnyLogableException(std::string("DateInFileName failed: ")
			+ e.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException(std::string("DateInFileName failed"),
			bDoNotWriteDuplicates);
	}
}
