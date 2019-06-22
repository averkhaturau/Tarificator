#ifndef __USUALCHILDFRM_H__
#define __USUALCHILDFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUsualChildFrame : public CMDIChildWnd
{
	protected:
		DECLARE_MESSAGE_MAP()

		DECLARE_DYNCREATE(CUsualChildFrame)

	public:
		CUsualChildFrame();
		virtual ~CUsualChildFrame();

		//{{AFX_VIRTUAL(CChildFrame)
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		//}}AFX_VIRTUAL

	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif
};

#endif // __USUALCHILDFRM_H__
