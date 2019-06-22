// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__806A3966_3429_45C9_A731_1406E7DEC9B1__INCLUDED_)
#define AFX_CHILDFRM_H__806A3966_3429_45C9_A731_1406E7DEC9B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChildFrameWithoutClose : public CMDIChildWnd
{
	protected:
		//{{AFX_MSG(CChildFrameWithoutClose)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSysCommand(UINT nID, LONG lParam);
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
		DECLARE_DYNCREATE(CChildFrameWithoutClose)

	public:
		CChildFrameWithoutClose();
		virtual ~CChildFrameWithoutClose();

		//{{AFX_VIRTUAL(CChildFrameWithoutClose)
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		//}}AFX_VIRTUAL

	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__806A3966_3429_45C9_A731_1406E7DEC9B1__INCLUDED_)
