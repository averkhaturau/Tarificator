#ifndef __BUSYCHILDFRAME_H__
#define __BUSYCHILDFRAME_H__

#include "ChildFrmWithoutClose.h"


class CBusyChildFrame : public CChildFrameWithoutClose
{
	private:
	protected:
		void OnUpdateFrameTitle(BOOL bAddToTitle);

		DECLARE_MESSAGE_MAP()
		DECLARE_DYNCREATE(CBusyChildFrame)
	public:
		CBusyChildFrame();
		virtual ~CBusyChildFrame();

		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


#endif // __BUSYCHILDFRAME_H__