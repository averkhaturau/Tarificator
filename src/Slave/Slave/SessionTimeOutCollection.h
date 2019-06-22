#ifndef __SESSIONTIMEOUTCOLLECTION_H__
#define __SESSIONTIMEOUTCOLLECTION_H__

#include "..\..\Master\DataStructures\ActiveContainer.h"
#include "SessionTimeOutManager.h"

#include <list>


class CSessionTimeOutCollection : public CActiveContainer<CSessionTimeOutManager, std::list<CSessionTimeOutManager*> >
{
	private:
	protected:
	public:
		CSessionTimeOutCollection();
		~CSessionTimeOutCollection();
};


#endif // __SESSIONTIMEOUTCOLLECTION_H__