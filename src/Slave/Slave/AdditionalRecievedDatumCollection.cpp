#include "stdafx.h"

#include "AdditionalRecievedDatumCollection.h"


CAdditionalRecievedDatumCollection::CAdditionalRecievedDatumCollection()
{

}
// End of CAdditionalRecievedDatumCollection()


CAdditionalRecievedDatumCollection::~CAdditionalRecievedDatumCollection()
{

}
// End of ~CAdditionalRecievedDatumCollection()


CAdditionalRecievedData* CAdditionalRecievedDatumCollection::GetFreeData()
{
	CActiveContainerResizable<CAdditionalRecievedData>::iterator Iter = GetData()->begin(), EndIter = GetData()->end();
		for (; Iter < EndIter; ++Iter)
		{
			(*Iter)->CheckForExpiration();
				if ( !(*Iter)->GetIsUsed() )
					return *Iter;
		}
	return 0;
}
// End of GetFreeData()
