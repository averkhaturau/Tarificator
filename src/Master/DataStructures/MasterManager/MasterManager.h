 // MasterManager.h

#ifndef _LX_MASTERMANAGER_H__INCLUDED_
#define _LX_MASTERMANAGER_H__INCLUDED_

#include "..\Communicator\MasterTCP_IP_Communicator.h"
#include "..\Saving\MasterBoundStorer.h"
#include "..\ClubSettings\Cashdesk.h"
#include "..\ClubSettings\ClubState.h"


class CMasterManager
{
public:
	typedef void CALLBACK CTimerProcedure(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);

	explicit CMasterManager(CMasterBoundStorer* pStorer);
	virtual ~CMasterManager();

	void StartTimer(CTimerProcedure* Procedure);
	void OnTimerEvent();

	// Обертки
	CClubState* GetClubState() {return m_pClubState;};
	CMasterTCP_IP_Communicator* GetCommunicator() {return m_pCommunicator;};
	UINT GetTimerPeriod() {return m_uiMasterTimerPeriod;};
	void SetTimerPeriod(UINT uiNew) {m_uiMasterTimerPeriod = uiNew;};

	CTimeStorage GetTimeSplitHist() const
		{ return m_TimeSplitHistoryAfter; };

	void SetTimeSplitHist(const CTimeStorage& SplitAfter)
		{ m_TimeSplitHistoryAfter = SplitAfter; };


	CCashdesk* GetCash(){return m_pCashdesk;};

private:
	void DoDeleteEverything();

protected:
	// Состояние клуба
	CClubState* m_pClubState;
	CMasterTCP_IP_Communicator* m_pCommunicator;
	// Период сработки таймера
	UINT m_uiMasterTimerPeriod;
	// Таймер
	UINT_PTR m_uiMasterTimerIdentifier;
	// Время, через которое кидать прошедшие интервалы в историю, удаляя их
	CTimeStorage m_TimeSplitHistoryAfter;

	// Кассовый аппарат
	CCashdesk *m_pCashdesk;
};

#endif // _LX_MASTERMANAGER_H__INCLUDED_
