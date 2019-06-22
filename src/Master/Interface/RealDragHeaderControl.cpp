#include "stdafx.h"

#include "RealDragHeaderControl.h"
#include "AdditionalResource.h"


BEGIN_MESSAGE_MAP(CRealDragHeaderControl, CHeaderCtrl)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


CRealDragHeaderControl::CRealDragHeaderControl()
{
	m_bTracking = false;
	m_LastPoint = (0, 0);
	//m_NMHeader = (0, 0, 0, 0);
}
// End of CRealDragHeaderControl()


CRealDragHeaderControl::~CRealDragHeaderControl()
{
}
// End of ~CRealDragHeaderControl()


BOOL CRealDragHeaderControl::OnChildNotify(UINT message,
			WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR* pnmh = (LPNMHDR)lParam; 
		if (message == WM_NOTIFY)
		{
				if (pnmh->code == HDN_BEGINTRACK)
				{
					m_bTracking = true;

					LPNMHEADER phdn = (LPNMHEADER)lParam;
					m_NMHeader = *phdn;
				}
				if (pnmh->code == HDN_ENDTRACK)
					m_bTracking = false;
		}

	return CHeaderCtrl::OnChildNotify(message, wParam, lParam, pResult);
}
// OnChildNotify


void CRealDragHeaderControl::OnMouseMove(UINT nFlags, CPoint point)
{
	CHeaderCtrl::OnMouseMove(nFlags, point);
		if (m_bTracking)
		{
				if (m_LastPoint != point)
				{
					NMHDR Header;
					Header.hwndFrom = m_hWnd;
					Header.idFrom = dwHeaderID;
					Header.code = HDN_REALMOVE;

					m_NMHeader.hdr = Header;

					::SendMessage(GetOwner()->m_hWnd, WM_NOTIFY, (WPARAM)&m_NMHeader, (LPARAM)&m_NMHeader);

					m_LastPoint = point;
				}
		}
}
// OnMouseMove
