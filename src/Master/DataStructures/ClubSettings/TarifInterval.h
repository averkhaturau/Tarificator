/*
	CTarifInterval - ��������� �������� ������ ���
	������, ����� � ���� ����� ��������������� ����
	�����, � ����� �������, ����� ���������,
	���  ������, ������� ��� ������, ��� ��������...
*/

#ifndef _LX_TARIFINTERVAL_H_INCLUDED_
#define _LX_TARIFINTERVAL_H_INCLUDED_

#include "CycleInterval.h"
#include "..\Constants.h"

class CTarifInterval : public CCycleInterval
{
	public:
		CTarifInterval();
		CTarifInterval(const CTimeStorage& Start, const CTimeStorage& Finish,
			const CCurrency Tarif)
		{
			SetInterval(Start, Finish);
			SetTarif(Tarif);
		};

		virtual ~CTarifInterval();

		// ������ � m_Tarif
		void SetTarif(CCurrency Tarif);
		CCurrency GetTarif() const;

		virtual bool IsValidTimeInterval() const;

	protected:
		// ������ �� �������� ������� (���� �� ���)
		CCurrency m_Tarif;
};

#endif // _LX_TARIFINTERVAL_H_INCLUDED_