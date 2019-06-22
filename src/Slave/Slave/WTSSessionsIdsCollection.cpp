#include "stdafx.h"

#include "WTSSessionsIdsCollection.h"
#include "Messages.h"


CWTSSessionsIdsCollection::CWTSSessionsIdsCollection()
{

}
// End of CWTSSessionsIdsCollection()


CWTSSessionsIdsCollection::~CWTSSessionsIdsCollection()
{

}
// End of ~CWTSSessionsIdsCollection()


bool CWTSSessionsIdsCollection::IsThereId(DWORD a_dwSessionId)
{
	CWTSSessionsIdsCollectionAncestor::iterator Iter = GetData()->begin(),
				EndIter = GetData()->end();
		for (; Iter != EndIter; ++Iter)
		{
				if ( **Iter == a_dwSessionId )
				{
					return true;
				}
		}

	return false;
}
// End of IsThereId
