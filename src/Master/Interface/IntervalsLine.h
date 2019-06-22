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
	// Собственно, что рисуем.
	CColoredIntervalsCollection m_ColoredIntervalsCollection;
	// Клиентская область
	CCycleColoredInterval m_ClientInterval;
	// Централизовано задается из BusyView, чтобы на всех
	// IntervalsLine черта была в одном и том же положении
	DWORD m_dwCurrentTimeLinePosition;
	DWORD m_dwOldCurrentTimeLinePosition;
	// Ответственность снаружи
	CMashineData* m_pMashineData;

	void DoDrawInterval(CColoredIntervalsCollection::iterator Iter, CDC* pDC);
	// Переводит точку по x в координатах окна во время
	CTimeStorage PointToTime(DWORD dwPoint);

	//{{AFX_MSG(CIntervalsLine)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	// Конструктор по умолчанию
	CIntervalsLine();
	// Деструктор
	virtual ~CIntervalsLine();

	// Переводит время в точку по x в координатах окна. Если Time лежит
	// вне области отображения - результат непредсказуем.
	signed long int TimeToPoint(CTimeContainer Time);
	// Вызывается по таймеру из BusyView. Проверяет, надо ли
	// перерисовать контрол из-за изменившейся позиции
	// CurrentTime-линии.
	void CheckCurrentTimeUpdate();

	// Обертки
	inline CCycleColoredInterval* GetMainInterval() {return &m_ClientInterval;};
	inline CColoredIntervalsCollection* GetIntervalsCollection() { return &m_ColoredIntervalsCollection;};
	void SetCurrentTimeLinePosition(DWORD dwNew) {m_dwCurrentTimeLinePosition = dwNew;};
	DWORD GetCurrentTimeLinePosition() {return m_dwCurrentTimeLinePosition;};
	CMashineData* GetMashineData() {return m_pMashineData;};
	void SetMashineData(CMashineData* a_pNew) {m_pMashineData = a_pNew;};
};


#endif //_LX_INTERVALSLINE_H___
