#ifndef __MASHINELINECONTROL_H__
#define __MASHINELINECONTROL_H__

#include "IntervalsLineControl.h"
#include "MashineNameControl.h"
#include "MashineStatusControl.h"
//#include "MashinePlanControl.h"


// �����, ������������ ��� �������� � ����� � ������
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

		// ����� � �������� ����������
		DWORD m_dwIntervalsLength;
		// ����� � �������� �����
		DWORD m_dwNameLength;
		// ����� � �������� �������
		DWORD m_dwStatusLength;
		// ����� � �������� ��������� �����
		DWORD m_dwTarifLength;
		// ��������������� �������
		CMashineData* m_pMashineData;

		// �������� Create ��� �������. ���������� -1, ���� ���������,
		// 0, ���� �������.
		int DoCreateLine(CLineControl* pLine);

		//{{AFX_MSG(CMashineLineControl)
		afx_msg int OnCreate(LPCREATESTRUCT);
		//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	public:
		// �����������
		CMashineLineControl();
		// ����������
		virtual ~CMashineLineControl();

		void RefreshLineData();

		// �������
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
