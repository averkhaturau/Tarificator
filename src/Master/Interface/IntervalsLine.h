#ifndef _LX_INTERVALSLINE_H___
#define _LX_INTERVALSLINE_H___

#include "LineControl.h"
#include "..\DataStructures\ClubSettings\BusyIntervalsCollection.h"
#include "..\DataStructures\ClubSettings\CycleColoredInterval.h"
#include "..\DataStructures\ClubSettings\MashinesCollection.h"



const char cIntervalsLineControlClassName[50] = "LineControl";

class CIntervalsLine : public CLineControl
{
	friend class CIntervalsCell;
protected:
	// ����������, ��� ������.
	CColoredIntervalsCollection m_ColoredIntervalsCollection;
	// ���������� �������
	CCycleColoredInterval m_ClientInterval;
	// �������������� �������� �� BusyView, ����� �� ����
	// IntervalsLine ����� ���� � ����� � ��� �� ���������
	DWORD m_dwCurrentTimeLinePosition;
	DWORD m_dwOldCurrentTimeLinePosition;
	// ��������������� �������
	CMashineData* m_pMashineData;

	void DoDrawInterval(CColoredIntervalsCollection::iterator Iter, CDC* pDC);
	// ��������� ����� �� x � ����������� ���� �� �����
	CTimeStorage PointToTime(DWORD dwPoint);

	//{{AFX_MSG(CIntervalsLine)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	// ����������� �� ���������
	CIntervalsLine();
	// ����������
	virtual ~CIntervalsLine();

	// ��������� ����� � ����� �� x � ����������� ����. ���� Time �����
	// ��� ������� ����������� - ��������� �������������.
	signed long int TimeToPoint(CTimeContainer Time);
	// ���������� �� ������� �� BusyView. ���������, ���� ��
	// ������������ ������� ��-�� ������������ �������
	// CurrentTime-�����.
	void CheckCurrentTimeUpdate();

	// �������
	inline CCycleColoredInterval* GetMainInterval() {return &m_ClientInterval;};
	inline CColoredIntervalsCollection* GetIntervalsCollection() { return &m_ColoredIntervalsCollection;};
	void SetCurrentTimeLinePosition(DWORD dwNew) {m_dwCurrentTimeLinePosition = dwNew;};
	DWORD GetCurrentTimeLinePosition() {return m_dwCurrentTimeLinePosition;};
	CMashineData* GetMashineData() {return m_pMashineData;};
	void SetMashineData(CMashineData* a_pNew) {m_pMashineData = a_pNew;};
};


#endif //_LX_INTERVALSLINE_H___
