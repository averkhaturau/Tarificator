/* Implementation of CClubState */
#include "stdafx.h"

#include "MashinesCollection.h"
#include "MashineData.h"
#include "..\Saving\MasterRegistryStorer.h"


// Свободные функции
void __stdcall TimerEventFunction(CMashineData* pMashine, void* pParam)
{
		if (pMashine->GetCurrentMashineState() != pMashine->GetLastMashineState())
		{
			pMashine->GetConnectingSocket()->GetConnectionRetriesManager()->SetArtificialTimeOutState();
			pMashine->SetLastMashineState(pMashine->GetCurrentMashineState());
		}

	pMashine->GetAcceptingSocket()->OnTimerEvent();
	pMashine->GetConnectingSocket()->OnTimerEvent();

		if ( (pMashine->GetConnectingSocket()->GetConnectionRetriesManager()->IsTimeExpired()) )
		{
			//pMashine->GetConnectingSocket()->CloseSocket();
			//pMashine->GetConnectingSocket()->GetConnectManager()->TerminateAnotherThread();
			pMashine->GetConnectingSocket()->DoConnectTo();
		}
}
// Конец свободных функций

CMashinesCollection::CMashinesCollection(CMasterBoundStorer* pStorer)
{
	try{
		pStorer->ReadMashinesCollection(this);

	}catch(CAnyLogableException& Error){
		DoDeleteEverything();
		
		std::string ErrorString = "CMashinesCollection::CMashinesCollection failed: ";
		ErrorString += Error.what();
		throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
	}catch(...){
		DoDeleteEverything();

		throw CAnyLogableException("An unknown error occured in CMashinesCollection::CMashinesCollection", bDoNotWriteDuplicates);
	}
}

CMashinesCollection::~CMashinesCollection()
{
	DoDeleteEverything();
}

void CMashinesCollection::DoDeleteEverything()
{
	Clear();
}
// End of DoDeleteEverything()

CMashineData* CMashinesCollection::FindMashine(const DWORD& Aipishnick)
{
	for (iterator _Element = GetData()->begin();
			_Element != GetData()->end(); ++_Element)
		if ((**_Element).GetIPAddress() == Aipishnick)
			return *_Element;

	return 0;
}
// end ofCMashineData* FindMashine


void CMashinesCollection::OnTimerEvent()
{
	EnumMashines(TimerEventFunction, 0);
}
// End of OnTimerEvent()


void CMashinesCollection::EnumMashines(
		CEnumMashinesFunction* pFunction, void* pParam)
{
	for (iterator Iter = GetData()->begin();
		Iter != GetData()->end(); ++Iter)
	{
		pFunction(*Iter, pParam);
	}
}
// End of EnumMashines
