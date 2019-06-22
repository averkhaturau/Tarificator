/*
	CMashineData описывает машину клуба
*/
#ifndef _LX_MASHINEDATA_H_INCLUDED_
#define _LX_MASHINEDATA_H_INCLUDED_

#include "..\stdafx.h"
#include <string>
#include <set>
#include "BusyIntervalsCollection.h"
#include "..\..\..\Slave\Slave\TimeOutManager.h"
#include "..\..\..\Slave\Slave\TCP_IP_SocketHolder.h"

enum MashineState {msBusy, msFree, msClientExchange, msUnknown};

class CMashineData
{
	typedef CMashineData MyT;
public:
	typedef std::set<DWORD> CTarifPlansNumbers;

	CMashineData();

	// копирующий
	CMashineData(MyT& AnotherMashine);

	virtual ~CMashineData();

	// Обращения к полям

	// Устанавливает готовый план
	void SetBusyIntervalsCollection(CBusyIntervalsCollection* pBusyIntervalsCollection);

	void SetIPAddress(const DWORD& MyIPAddress);

	std::string& GetMashineName();

	CTCP_IP_SocketHolder* GetConnectingSocket() {return &m_ConnectingSocket;};
	CTCP_IP_SocketHolder* GetAcceptingSocket()  {return &m_AcceptingSocket;};

	CBusyIntervalsCollection* GetBusyIntervalsCollection()
		{ return &m_BusyIntervalsCollection; };

	CTimeOutManager* GetLastSuccessCommunication()
		{ return &m_tomSuccessCommunication; };

	void SetBusyIntervalsCollection(CBusyIntervalsCollection& BIC)
		{ m_BusyIntervalsCollection = BIC; };

	DWORD GetIPAddress() const;

	CTarifPlansNumbers* GetTarifPlansNumbers()
	{
		return &m_TarifPlansNumbers;
	};

	void SetTarifPlansNumbers(const CTarifPlansNumbers& TPN)
		{ m_TarifPlansNumbers = TPN; };

	bool GetWaitingForClientExchange() const { return m_bWaitingForClientExchange; };

	void SetWaitingForClientExchange(const bool& WaitingForClientExchange)
		{ m_bWaitingForClientExchange = WaitingForClientExchange; };

	// копирующее присваивание
	/*MyT& operator=(const MyT& AnotherMashine)
	{
		SetMashineName(AnotherMashine.GetMashineName());
		SetTarifPlansNumbers(AnotherMashine.GetTarifPlansNumbers());
		SetBusyIntervalsCollection(AnotherMashine.GetBusyIntervalsCollection());
		return *this;
	};*/
//protected:
	bool IsMashineBusy()
	{
		return m_BusyIntervalsCollection.IsTimeInIntervals(CurrentTime());
	}
public:
	// для выяснения текущего состояния машины
	MashineState GetCurrentMashineState()
	{
		//if (GetLastSuccessCommunication()->IsTimeExpired())
		//	return msUnknown;
		return m_bWaitingForClientExchange?msClientExchange:
			(IsMashineBusy()?msBusy:msFree);
	};

	MashineState GetLastMashineState() {return m_LastMashineState;};
	void SetLastMashineState(MashineState NewState) {m_LastMashineState = NewState;};


protected:
	CTCP_IP_SocketHolder m_AcceptingSocket;	
	CTCP_IP_SocketHolder m_ConnectingSocket;
	std::string m_MashineName;
	CBusyIntervalsCollection m_BusyIntervalsCollection;
	CTarifPlansNumbers m_TarifPlansNumbers;
	// отмечает время последнего успешного коннекта с машиной
	CTimeOutManager m_tomSuccessCommunication;
	bool m_bWaitingForClientExchange;
	MashineState m_LastMashineState;
};

#endif //_LX_MASHINEDATA_H_INCLUDED_
