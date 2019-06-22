#if !defined(AFX_BUSYVIEW_H__4A284521_E272_4107_973D_EDE73F70B7C7__INCLUDED_)
#define AFX_BUSYVIEW_H__4A284521_E272_4107_973D_EDE73F70B7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MashineLinesGrid.h"
#include "..\DataStructures\ClubSettings\MashinesCollection.h"


// Predefinitions
class CInterfaceDoc;

// BusyView
class CBusyView : public CView
{
	private:
	protected:
		UINT m_uiTimerIdentifier;
		CImageList m_ImageList;
		CMashineLinesGrid m_Grid;

		void DoReLayOut();

		CInterfaceDoc* GetDocument();

		DECLARE_DYNCREATE(CBusyView)
		DECLARE_MESSAGE_MAP()

		virtual void OnDraw(CDC* pDC);

		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnDestroy();

			#ifdef _DEBUG
				virtual void AssertValid() const;
				virtual void Dump(CDumpContext& dc) const;
			#endif // _DEBUG
	public:
		CBusyView();
		virtual ~CBusyView();

		void GetSelectedMashines(CMashinesCollection* a_pSelectedMashines);

		virtual void OnInitialUpdate();

		void Refresh();
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BUSYVIEW_H__4A284521_E272_4107_973D_EDE73F70B7C7__INCLUDED_)
