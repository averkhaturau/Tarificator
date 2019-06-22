#ifndef __REMAININGTIMESLAVEDESCRIPTION_H__
#define __REMAININGTIMESLAVEDESCRIPTION_H__

#include "..\..\Master\DataStructures\ClubSettings\RemainingTimeDescription.h"
#include "..\Slave\TimeOutManager.h"
#include "..\Slave\InvertedTimeOutManager.h"


struct CRemainingTimeSlaveDescription : public CRemainingTimeDescription
{
	CTimeContainer SlaveCurrent;

	void FillInvertedTimeOutManager(CInvertedTimeOutManager* a_pManager)
	{
			if ( !a_pManager )
				return;

			if (SlaveCurrent > MasterCurrent)
			{
				CTimeContainer Temp = SlaveCurrent - MasterCurrent;
				Temp += Finish; // Теперь в Temp Finish в Slave-времени
				a_pManager->SetEdgeTime(Temp);
			}
			else
			{
				CTimeContainer Temp = Finish;
				Temp -= MasterCurrent - SlaveCurrent;	// Теперь в Temp Finish в Slave-времени
				a_pManager->SetEdgeTime(Temp);
			}
	}

	/*void FillFinishTimeOutManager(CTimeOutManager* a_pManager)
	{
			if (a_pManager)
			{
					if (Finish > MasterCurrent)
						a_pManager->SetTimeOut(Finish - MasterCurrent);
					else
						a_pManager->SetTimeOut((CTimeContainer)0);

				a_pManager->OnBegin();

					if (SlaveCurrent > MasterCurrent)
					{
						CTimeContainer Temp = SlaveCurrent - MasterCurrent;
						Temp += Finish; // Теперь в Temp Finish в Slave-времени
							// Если интервал еще не закончился
							if (SlaveCurrent < Finish)
							{
								a_pManager->SetTimeOut(Finish - SlaveCurrent);
								a_pManager->OnBegin();
							}
					}
					else
					{
						CTimeContainer Temp = Finish;
						Temp -= MasterCurrent - SlaveCurrent;	// Теперь в Temp Finish в Slave-времени
							if (SlaveCurrent < Finish)
							{
								a_pManager->SetTimeOut(Finish - SlaveCurrent);
								a_pManager->OnBegin();
							}
					}
			}
	}*/

	void FillWithZeros()
	{
		Start = (CTimeContainer)0;
		Finish = (CTimeContainer)0;
		MasterCurrent = (CTimeContainer)0;
		SlaveCurrent = (CTimeContainer)0;
		cUserNames[0] = 0;
	}
};


#endif // __REMAININGTIMESLAVEDESCRIPTION_H__