#ifndef __APPLICATIONINFOSCOLLECTION_H__
#define __APPLICATIONINFOSCOLLECTION_H__

#include "..\..\Master\DataStructures\ActiveContainer.h"
#include "ApplicationInfo.h"

#include <list>


typedef std::list<CApplicationInfo*> CApplicationInfosCollectionContainer;

class CApplicationInfosCollection : public CActiveContainer<CApplicationInfo, CApplicationInfosCollectionContainer>
{
	private:
	protected:
	public:
		CApplicationInfosCollection();
		~CApplicationInfosCollection();

		CApplicationInfo* LookForSessionId(DWORD a_dwSessionId);

		CBaseContainer::reference AddApplication(DWORD a_dwSessionId, DWORD a_dwMainThreadId, HANDLE a_hProcess, HANDLE a_hThread);
};


#endif // __APPLICATIONINFOSCOLLECTION_H__