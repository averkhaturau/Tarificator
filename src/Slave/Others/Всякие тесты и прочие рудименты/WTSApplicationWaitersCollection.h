#ifndef __APPLICATIONWAITERSCOLLECTION_H__
#define __APPLICATIONWAITERSCOLLECTION_H__

#include "WTSApplicationWaiter.h"
#include "..\..\Master\DataStructures\ActiveContainer.h"

#include <list>


typedef std::list<CWTSApplicationWaiter*> CWTSApplicationWaitersCollectionContainer;

class CWTSApplicationWaitersCollection : public CActiveContainer< CWTSApplicationWaiter, CWTSApplicationWaitersCollectionContainer >
{
	private:
	protected:
	public:
		CWTSApplicationWaitersCollection();
		virtual ~CWTSApplicationWaitersCollection();

		void AddApplication(HANDLE a_hProcess, DWORD a_dwThreadId, DWORD a_dwSessionId);

		void OnWaitedApplicationEnded(CWTSApplicationWaiter* a_pWaiter);

		CWTSApplicationWaiter* LookForSessionId(DWORD a_dwSessionId);
};


#endif // __APPLICATIONWAITERSCOLLECTION_H__