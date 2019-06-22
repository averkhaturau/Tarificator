/* Implementation of CTarifInterval */
#include "stdafx.h"

#include "TarifInterval.h"

CTarifInterval::CTarifInterval()
{
	m_Tarif = 0; // Ставка не установлена
}

CTarifInterval::~CTarifInterval()
{
}

void CTarifInterval::SetTarif(CCurrency Tarif)
{
	m_Tarif = Tarif;
}

CCurrency CTarifInterval::GetTarif() const
{
	return m_Tarif;
}

bool CTarifInterval::IsValidTimeInterval() const
{
	return (IsValidTimeInterval()) && (m_Tarif!=0);
}