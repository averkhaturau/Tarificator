#ifndef _LX_BUTTONSBARVIEW_H__
#define _LX_BUTTONSBARVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// BusyView
class CButtonsBarView : public 
{
	private:
	protected:
		UINT m_uiTimerIdentifier;
		CImageList m_ImageList;
		CMashineLinesGrid m_Grid;

		void DoReLayOut();

		DECLARE_DYNCREATE(CBusyView)
		DECLARE_MESSAGE_MAP()

		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnDestroy();
		virtual void OnDraw(CDC* pDC);
			#ifdef _DEBUG
				virtual void AssertValid() const;
				virtual void Dump(CDumpContext& dc) const;
			#endif // _DEBUG

		CBusyView();
		virtual ~CBusyView();
	public:
		CInterfaceDoc* GetDocument();

		virtual void OnInitialUpdate();
};

//{{AFX_INSERT_LOCATION}}

#endif // _LX_BUTTONSBARVIEW_H__
