/*
	‘ункции, позвол€ющие сохранить текущие данные за день
*/

#ifndef _LX_DAYHISTORY_H_INCLUDED
#define _LX_DAYHISTORY_H_INCLUDED

#include <windows.h>
#include <string>
#include "..\ClubSettings\TimeStorage.h"

class CDayHistory
{
protected:
	std::string TodayInStr();
	std::string DateInStr(const CTimeStorage& Date);

	std::string TodayInFileName();
	std::string DateInFileName(const CTimeStorage& Date);
};

#endif // _LX_DAYHISTORY_H_INCLUDED