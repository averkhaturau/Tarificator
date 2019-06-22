#include "stdafx.h"

#include "MashinesSelectionControl.h"




CMashinesSelectionControl::CMashinesSelectionControl()
{
	m_pMashines = 0;
}
// End of CMashinesSelectionControl()


CMashinesSelectionControl::~CMashinesSelectionControl()
{
	DoDeleteEverything();
}
// End of ~CMashinesSelectionControl()


void CMashinesSelectionControl::DoDeleteEverything()
{

}
// End of DoDeleteEverything()


void CMashinesSelectionControl::SetMashinesCollection(CMashinesCollection* a_pNew)
{
	m_pMashines = a_pNew;

	Fill();
}
// End of SetMashinesCollection


DWORD CMashinesSelectionControl::GetFirstSelectedMashinePosition()
{
	return 0;
}
// End of GetFirstSelectedMashinePosition()


CMashineData* CMashinesSelectionControl::GetNextMashine(DWORD a_dwPosition)
{
		if ( !m_pMashines )
			return 0;

		if ( a_dwPosition >= m_pAddedList->GetCount() )
			return 0;

	return &((*m_pMashines)[m_pAddedList->GetItemData(a_dwPosition)]);
}
// End of GetNextMashine


void CMashinesSelectionControl::CreateAllItems()
{
	int iRes = 0;
	CMashinesCollection::iterator Iter = m_pMashines->GetData()->begin(),
				EndIter = m_pMashines->GetData()->end();
		for (int i = 0; Iter < EndIter; ++i, ++Iter)
		{
			iRes = m_pNotAddedList->AddString((char*)(*Iter)->GetMashineName().c_str());
			m_pNotAddedList->SetItemData(iRes, i);
		}
}
// End of CreateAllItems

