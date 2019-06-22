#ifndef __SLAVESERVICE_H__
#define __SLAVESERVICE_H__


#include "NTService\NTService.h"

class CSlaveService : public CNTService
{
	private:
	protected:
		HINSTANCE m_hInst;
	public:
		CSlaveService(HINSTANCE a_hInst);
		virtual ~CSlaveService();

		virtual void Run();
		virtual BOOL OnInit();
    virtual void OnStop();
    virtual void OnInterrogate();
    virtual void OnPause();
    virtual void OnContinue();
    virtual void OnShutdown();
    virtual BOOL OnUserControl(DWORD dwOpcode);

};


#endif //__SLAVESERVICE_H__