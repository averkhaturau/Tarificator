#ifndef _LX_MASHINELINEGRID_H_INCLUDED___
#define _LX_MASHINELINEGRID_H_INCLUDED___

#include "GridCtrlSource\GridCtrl.h"
#include "..\DataStructures\ClubSettings\MashinesCollection.h"
#include "..\DataStructures\ClubSettings\TarifPlansCollection.h"


class CMashineLinesGrid : public CGridCtrl
{
	friend class CBusyView;
	std::vector<int> m_vMashineIndexes;
protected:
	CMashinesCollection *m_pMashinesCollection;
	CTarifPlansCollection *m_pTarifPlansCollection;

	void DoRelayout();

    virtual void  OnFixedRowClick(CCellID& cell);

	BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data,
                          int low, int high);


	//{{AFX_MSG(CMashineLinesGrid)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	CMashineLinesGrid();

	void SetMashinesCollection(CMashinesCollection* a_pMashinesCollection)
		{ m_pMashinesCollection = a_pMashinesCollection; };

	void SetTarifPlansCollection(CTarifPlansCollection* a_pTarifPlansCollection)
		{ m_pTarifPlansCollection = a_pTarifPlansCollection; };

	// Отображение машин
	void DisplayMashines();

	void Refresh();

	void AddSelectedMashines(CMashinesCollection* a_pSelectedMashines);

};

#endif //_LX_MASHINELINEGRID_H_INCLUDED___

