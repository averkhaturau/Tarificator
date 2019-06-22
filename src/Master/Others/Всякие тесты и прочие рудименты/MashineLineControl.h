#ifndef __MASHINELINECONTROL_H__
#define __MASHINELINECONTROL_H__

#include "IntervalsLineControl.h"
#include "MashineNameControl.h"
#include "MashineStatusControl.h"
//#include "MashinePlanControl.h"


// Класс, агрегирующий три контрола с инфой о машине
class CMashineLineControl : public CWnd
{
	private:
		void ChoseWidthAccodingToAttributes();
		void DoDeleteEverything();
	protected:
		CIntervalsLineControl* m_pIntervalsLineControl;
		CMashineNameControl* m_pMashineNameControl;
		CMashineStatusControl* m_pMashineStatusControl;
		//CMashinePlanControl *m_pMashinePlanControl;

		// Длина в пикселах интервалов
		DWORD m_dwIntervalsLength;
		// Длина в пикселах имени
		DWORD m_dwNameLength;
		// Длина в пикселах статуса
		DWORD m_dwStatusLength;
		// Длина в пикселах тарифного плана
		DWORD m_dwTarifLength;
		// Ответственность снаружи
		CMashineData* m_pMashineData;

		// Вызывает Create для линейки. Возвращает -1, если неуспешно,
		// 0, если успешно.
		int DoCreateLine(CLineControl* pLine);

		//{{AFX_MSG(CMashineLineControl)
		afx_msg int OnCreate(LPCREATESTRUCT);
		//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	public:
		// Конструктор
		CMashineLineControl();
		// Деструктор
		virtual ~CMashineLineControl();

		void RefreshLineData();

		// Обертки
		CMashineNameControl* GetMashineNameControl() {return m_pMashineNameControl;};
		CIntervalsLineControl* GetIntervalsLineControl(){return m_pIntervalsLineControl;};
		CMashineStatusControl* GetMashineStatusControl() {return m_pMashineStatusControl;};
		DWORD GetIntervalsLength() {return m_dwIntervalsLength;};
		DWORD GetNameLength() {return m_dwNameLength;};
		DWORD GetStatusLength() {return m_dwStatusLength;};
		void SetIntervalsLength(DWORD dwNew);
		void SetNameLength(DWORD dwNew);
		void SetStatusLength(DWORD dwNew);

		void SetMashineData(CMashineData* pNew);
		CMashineData* GetMashineData() {return m_pMashineData;};
};


#endif // __MASHINELINECONTROL_H__
