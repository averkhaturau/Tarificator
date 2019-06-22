#ifndef __CASHCHILDFRAME_H__
#define __CASHCHILDFRAME_H__

#include "UsualChildFrm.h"


class CCashChildFrame : public CUsualChildFrame
{
	private:
	protected:
		void OnUpdateFrameTitle(BOOL bAddToTitle);

		DECLARE_MESSAGE_MAP()

		DECLARE_DYNCREATE(CCashChildFrame)
	public:
		CCashChildFrame();
		virtual ~CCashChildFrame();

		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


#endif // __CASHCHILDFRAME_H__