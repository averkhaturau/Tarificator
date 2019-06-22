/* Implementation of CMashineData */
#include "stdafx.h"

#include "MashineData.h"


CMashineData::CMashineData()
{
	m_bWaitingForClientExchange = 0;
	m_LastMashineState = msUnknown;
}
// End of CMashineData()


CMashineData::CMashineData(MyT& AnotherMashine) :
		m_AcceptingSocket(*AnotherMashine.GetAcceptingSocket()),
		m_ConnectingSocket(*AnotherMashine.GetConnectingSocket()),
		m_tomSuccessCommunication(*AnotherMashine.GetLastSuccessCommunication())
{
	GetMashineName() = AnotherMashine.GetMashineName();
	SetTarifPlansNumbers(*AnotherMashine.GetTarifPlansNumbers());
	SetBusyIntervalsCollection(AnotherMashine.GetBusyIntervalsCollection());

	m_bWaitingForClientExchange = 0;
	m_LastMashineState = msUnknown;
}
// End of CMashineData


CMashineData::~CMashineData()
{
}

void CMashineData::SetBusyIntervalsCollection(CBusyIntervalsCollection* GetBusyIntervalsCollection)
{
	m_BusyIntervalsCollection.operator =(*GetBusyIntervalsCollection);
}

void CMashineData::SetIPAddress(const DWORD& MyIPAddress)
{
	m_ConnectingSocket.SetAddressToConnectTo(MyIPAddress);
}

std::string& CMashineData::GetMashineName()
{
	return m_MashineName;
}

DWORD CMashineData::GetIPAddress() const
{
	return m_ConnectingSocket.GetAddressToConnectTo();
}