#ifndef __MASHINESSELECTIONCONTROL_H__
#define __MASHINESSELECTIONCONTROL_H__

#include "..\DataStructures\ClubSettings\MashinesCollection.h"
#include "DoubleListSelectionControl.h"


class CMashinesSelectionControl : public CDoubleListSelectionControl
{
	private:
		void DoDeleteEverything();
	protected:
		// Ответственность снаружи
		CMashinesCollection* m_pMashines;

		virtual void CreateAllItems();

		static void CreateItems(CDoubleListSelectionControl* a_pControl, void* a_pData);
	public:
		CMashinesSelectionControl();
		virtual ~CMashinesSelectionControl();

		void SetMashinesCollection(CMashinesCollection* a_pNew);

		DWORD GetFirstSelectedMashinePosition();
		CMashineData* GetNextMashine(DWORD a_dwPosition);

		// Обертки
		CMashinesCollection* GetMashinesCollection() {return m_pMashines;};
};


#endif // __MASHINESSELECTIONCONTROL_H__