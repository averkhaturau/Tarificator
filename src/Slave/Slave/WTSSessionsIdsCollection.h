#ifndef __WTSSESSIONIDSCOLLECTION_H__
#define __WTSSESSIONIDSCOLLECTION_H__

#include "..\..\Master\DataStructures\ActiveContainerResizable.h"


typedef CActiveContainerResizable<DWORD> CWTSSessionsIdsCollectionAncestor;

class CWTSSessionsIdsCollection : public CActiveContainerResizable<DWORD>
{
	private:
	protected:
	public:
		CWTSSessionsIdsCollection();
		virtual ~CWTSSessionsIdsCollection();

		bool IsThereId(DWORD a_dwSessionId);
};


#endif // __WTSSESSIONIDSCOLLECTION_H__