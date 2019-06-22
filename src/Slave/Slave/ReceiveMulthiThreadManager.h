#ifndef __RECEIVEMULTITHREADMANAGER_H__
#define __RECEIVEMULTITHREADMANAGER_H__

#include "MultiThreadManager.h"
#include "ReceiverParamsCollection.h"


// ќтличаетс€ от CMultiThreadManager'а только тем, что имеет
// указатель на соответствующий CReceiveParameters, чтобы при TimeOut
// ставить ему Used = false
class CReceiveMultiThreadManager : public CMultiThreadManager
{
	private:
	protected:
		// ќтветственность снаружи
		CReceiveParameters* m_pReceiveParameters;
	public:
		//  онструктор по умолчанию
		CReceiveMultiThreadManager();
		~CReceiveMultiThreadManager();

		// ѕровер€ет Expired и если надо - грохаетс€. ¬озвращает true,
		// если пришлось убить поток.
		bool OnTimerEvent();

		// ќбертки
		CReceiveParameters* GetReceiveParameters() {return m_pReceiveParameters;};
		void SetReceiveParameters(CReceiveParameters* pNew) {m_pReceiveParameters = pNew;};
};


#endif // __RECEIVEMULTITHREADMANAGER_H__