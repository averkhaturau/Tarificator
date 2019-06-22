#ifndef __REMAININGTIMEDESCRIPTION_H__
#define __REMAININGTIMEDESCRIPTION_H__


#include "TimeInterval.h"
#include "TarifPlan.h"

#include "lmcons.h"


struct CRemainingTimeDescription
{
	CTimeContainer Start;
	CTimeContainer Finish;
	CTimeContainer MasterCurrent;

	char cUserNames[10 * UNLEN];

	void Fill(CInterval* a_pInterval, CTarifPlan* a_pPlan)
	{
			if (a_pInterval)
			{
				Start = a_pInterval->GetStartTime().GetTime();
				Finish = a_pInterval->GetFinishTime().GetTime();
				MasterCurrent = CurrentTime().GetTime();
			}
			else
			{
				Start = (CTimeContainer)0;
				Finish = (CTimeContainer)0;
				MasterCurrent = (CTimeContainer)0;
			}
			if (a_pPlan)
			{
				cUserNames[0] = a_pPlan->GetUserNames()->size();
				DWORD dwPosition = 1;
					for (char i = 0; i < cUserNames[0]; ++i)
					{
						strcpy(&(cUserNames[dwPosition]), (*a_pPlan->GetUserNames())[i].c_str());
						dwPosition += strlen(&(cUserNames[dwPosition]));
						++dwPosition;
					}
			}
			else
			{
				cUserNames[0] = '\0';
			}
	};

	bool LookForUserName(LPCTSTR a_pcName)
	{
		DWORD dwPosition = 1;
			for (char i = 0; i < cUserNames[0]; ++i)
			{
					if ( !stricmp(&(cUserNames[dwPosition]), a_pcName) )
						return true;
				dwPosition += strlen(&(cUserNames[dwPosition]));
				++dwPosition;
			}

		return false;
	};
};

#endif // __REMAININGTIMEDESCRIPTION_H__