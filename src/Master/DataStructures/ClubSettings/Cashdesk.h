#ifndef _LX_CASHDESK_H_INCLUDED__
#define _LX_CASHDESK_H_INCLUDED__

#include "..\Constants.h"
#include "..\CashLogger.h"
#include "Operator.h"

/*
	����� ��������� �������� �������, �.�. �������� ������
	� ���, ������� ����� � �����, ��������� �������� ������
	�����, ���������� �����...

	��� ���� � ����������� ������.
*/
class CCashdesk
{
	DoDeleteEverything()
	{
		if (m_pLogger)
		{
			delete m_pLogger;
			m_pLogger = 0;
		}
	};
public:
	CCashdesk(CCashStorer *pCashStorer)
	{
		try{
			m_pLogger = 0;
			try{
				m_pLogger = new CCashLogger;
				pCashStorer->ReadCash(this);
			}catch(...){
				DoDeleteEverything();
				throw;
			}
		}catch(CAnyLogableException &e){
			throw CAnyLogableException(std::string(
				(std::string)"CCashdesk constructor failed: " +
				(std::string)e.what()).c_str(), e.GetWriteDuplicatesToLog());
		}catch(...){
			throw CAnyLogableException("CCashdesk constructor failed", bDoNotWriteDuplicates);
		}
	};

	virtual ~CCashdesk(){DoDeleteEverything();};

	// ��������� ��������� �����
	void SetInitialSum(const CCurrency &Sum, const std::string &comment="")
	{
		/*char cBuff[20];
		std::string sStr;
		sStr = (std::string)"��������� "+
			(std::string)_itoa(Sum, cBuff, 10) +" ("+ comment +")";

		m_pLogger->AddLogEntry(sStr.c_str(),bWriteDuplicates);*/
		m_Sum = Sum;
	};

	// ������ ����������� �����
	CCurrency GetSum()const{return m_Sum;};

	// ���������� � �����
	void AddSum(const CCurrency& Sum, const std::string &comment/*�����������*/, CTimeStorage& EventTime)
	{
		//if (m_Sum<-Sum)
		//	throw std::logic_error(sMesNegativeCash.c_str());

		char cBuff[20];
		std::string sPoint = Sum>0?"\n\t\t+":"\n\t\t";
		sPoint += (std::string)_itoa(Sum, cBuff, 10);
		sPoint += " ������. "+ comment +"\t\n�����: ";

		// ���������� ��������
		m_Sum += Sum;

		sPoint += (std::string)_itoa(m_Sum, cBuff, 10) +"\n===\n";

		m_pLogger->SetTimeStamp(EventTime);
		m_pLogger->AddLogEntry(sPoint.c_str(), bWriteDuplicates);
	};

	CCashLogger* GetLogger(){return m_pLogger;};

	void SetPermission(const CPermission a_Permission)
		{m_Permission = a_Permission;};
	CPermission GetPermission()const{return m_Permission;};

protected:
	CCurrency m_Sum;
	CCashLogger *m_pLogger;
	CPermission m_Permission;
};

#endif //_LX_CASHDESK_H_INCLUDED__
