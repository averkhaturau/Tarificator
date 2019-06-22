#ifndef __CLIENTEXCHANGEADDITION_H__
#define __CLIENTEXCHANGEADDITION_H__

#include "..\DataStructures\ClubSettings\BusyInterval.h"
#include "..\..\Slave\Slave\MultiThreadManager.h"


// Predefinition
class CMashineData;
class CClientExchangeDialog;

class CExchangeDialogParams : public CThreadParameters
{
	private:
	protected:
		CBusyInterval m_OldInterval;
		CBusyInterval m_NewInterval;
		CMashineData* m_pMashine;
		CClientExchangeDialog* m_pClientExchangeDialog;
	public:
		CExchangeDialogParams()
		{
			m_pMashine = 0;
			m_pClientExchangeDialog = 0;
		};

		// Обертки
		inline void SetOldInterval(CBusyInterval* pNew) {m_OldInterval = *pNew;};
		inline CBusyInterval* GetOldInterval() {return &m_OldInterval;};
		inline void SetNewInterval(CBusyInterval* pNew) {m_NewInterval = *pNew;};
		inline CBusyInterval* GetNewInterval() {return &m_NewInterval;};
		inline CMashineData* GetMashine() {return m_pMashine;};
		inline void SetMashine(CMashineData* pNew) {m_pMashine = pNew;};
		inline CClientExchangeDialog* GetClientExchangeDialog() {return m_pClientExchangeDialog;};
		inline void SetClientExchangeDialog(CClientExchangeDialog* pNew) {m_pClientExchangeDialog = pNew;};
};


#endif // __CLIENTEXCHANGEADDITION_H__