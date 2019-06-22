#ifndef __REALDRAGHEADERCONTROL_H__
#define __REALDRAGHEADERCONTROL_H__

//#include "AFXCMN.H"

#define HDN_REALMOVE           (HDN_FIRST-35)

class CRealDragHeaderControl : public CHeaderCtrl
{
	private:
	protected:
		bool m_bTracking;
		CPoint m_LastPoint;
		NMHEADER m_NMHeader;

		afx_msg void OnMouseMove(UINT nFlags, CPoint point);

		virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);

		DECLARE_MESSAGE_MAP()
	public:
		// Конструктор
		CRealDragHeaderControl();
		// Деструктор
		virtual ~CRealDragHeaderControl();
};


#endif // __REALDRAGHEADERCONTROL_H__