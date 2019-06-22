#include "stdafx.h"

#include "WTSApplicationWaitersCollection.h"
#include "Exceptions.h"
#include "Messages.h"

#include <string>


CWTSApplicationWaitersCollection::CWTSApplicationWaitersCollection()
{

}
// End of CWTSApplicationWaitersCollection()


CWTSApplicationWaitersCollection::~CWTSApplicationWaitersCollection()
{

}
// End of ~CWTSApplicationWaitersCollection()


void CWTSApplicationWaitersCollection::AddApplication(HANDLE a_hProcess, DWORD a_dwThreadId, DWORD a_dwSessionId)
{
		try
		{
			CWTSApplicationWaiter* pWaiter = new CWTSApplicationWaiter;
			pWaiter->SetThreadId(a_dwThreadId);
			pWaiter->SetSessionId(a_dwSessionId);
			pWaiter->StartWaiting(a_hProcess);
			GetData()->push_back(pWaiter);
		}
		catch(CAnyLogableException& Error)
		{
			throw CAnyLogableException(((std::string)"An error occured in CApplicationWaitersCollection::OnWaitedApplicationEnded: " + Error.what()).c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CApplicationWaitersCollection::OnWaitedApplicationEnded", bDoNotWriteDuplicates);
		}
}
// End of AddApplication


void CWTSApplicationWaitersCollection::OnWaitedApplicationEnded(CWTSApplicationWaiter* a_pWaiter)
{
	DeleteResident(*a_pWaiter);
}
// End of OnWaitedApplicationEnded


CWTSApplicationWaiter* CWTSApplicationWaitersCollection::LookForSessionId(DWORD a_dwSessionId)
{
	CWTSApplicationWaitersCollectionContainer::iterator Iter = GetData()->begin(),
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
