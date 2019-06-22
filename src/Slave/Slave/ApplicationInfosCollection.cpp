#include "stdafx.h"

#include "ApplicationInfosCollection.h"
#include "Messages.h"

#include <string>


CApplicationInfosCollection::CApplicationInfosCollection()
{

}
// End of CApplicationInfosCollection()


CApplicationInfosCollection::~CApplicationInfosCollection()
{

}
// End of ~CApplicationInfosCollection()


CApplicationInfo* CApplicationInfosCollection::LookForSessionId(DWORD a_dwSessionId)
{
	CApplicationInfosCollectionContainer::iterator Iter = GetData()->begin(),
				EndIter = GetData()->end();
		for (; Iter != EndIter; ++Iter)
				if ( (*Iter)->GetSessionId() == a_dwSessionId )
					break;

		if (Iter != EndIter)
			return *Iter;
		else
			return 0;
}
// End of LookForSessionId


CApplicationInfosCollection::CBaseContainer::reference CApplicationInfosCollection::AddApplication(DWORD a_dwSessionId, DWORD a_dwMainThreadId, HANDLE a_hProcess, HANDLE a_hThread)
{
	CApplicationInfo Info;
	Info.SetSessionID(a_dwSessionId);
	Info.SetMainThreadId(a_dwMainThreadId);
	Info.SetProcessHandle(a_hProcess);
	Info.SetThreadHandle(a_hThread);
	//*(Info.GetUserName()) = a_sUserName;

	return AddResident(Info);
}
// End of AddApplication
