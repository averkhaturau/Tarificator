#if !defined(AFX_BUSYVIEW_H__B71CC6F2_21AF_4BDE_8C9B_35D4DE233F1C__INCLUDED_)
#define AFX_BUSYVIEW_H__B71CC6F2_21AF_4BDE_8C9B_35D4DE233F1C__INCLUDED_

#include "RealDragHeaderControl.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Predefinitions
class CInterfaceDoc;
class CRealDragHeaderControl;
class CLineControlsCollection;
class CMashineLineControl;
class CIntervalsLineControl;


class CBusyView : public CScrollView
{
private:
	void DoDeleteEverything();
protected:
	CRealDragHeaderControl* m_pHeaderControl;
	CLineControlsCollection* m_pLineControlsCollection;
	// Высота каждой линии
	DWORD m_dwLineHeight;
	// Высота CRealDragHeaderControl
	DWORD m_dwHeaderHeight;
	// Для внутреннего использования
	DWORD m_dwOldScrollLines;
	// Для внутреннего использования
	UINT m_uiTimerIdentifier;
	// Юзается для рисования линии текущего времени
	LOGPEN m_CurrentTimeLogPen;

	void ReSizeControls();
	// Вызывается из OnSize и пр.. iItem - номер Item'а, который
	// ресайзится.
	void ReSizeHeader(int iItem = 0);
	void OnScroll(bool bCheckInvalidate = false, signed long int sliPos = 0);

	CBusyView();
	virtual ~CBusyView();

	void CreateLineControl(CMashineLineControl* pLine, UINT uiLineID,
				DWORD dwRow);
	void CreateHeaderControl();


	DECLARE_DYNCREATE(CBusyView)

	//{{AFX_MSG(CBusyView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTest();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnEndTrack(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CInterfaceDoc* GetDocument();

	// Вызывается из OnTimer и из CIntervalsLineControl::OnPaint
	void OnCalcCurrentTimeLine();

	void RefreshAllLineData();

	// Обертки
	void SetLineHeight(DWORD dwNew) {m_dwLineHeight = dwNew;};
	DWORD GetLineHieght() {return m_dwLineHeight;};
	LOGPEN* GetCurrentTimeLogPen() {return &m_CurrentTimeLogPen;};
	CLineControlsCollection* GetLineControlsCollection() {return m_pLineControlsCollection;};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBusyView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL
};

#ifndef _DEBUG  // debug version in BusyView.cpp
inline CInterfaceDoc* CBusyView::GetDocument()
   { return (CInterfaceDoc*)m_pDocument; }
#endif


#endif // !defined(AFX_BUSYVIEW_H__B71CC6F2_21AF_4BDE_8C9B_35D4DE233F1C__INCLUDED_)
