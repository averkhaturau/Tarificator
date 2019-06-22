/*
	������� ������� � ������, ��� ������� �� ��������
*/
#ifndef _LX_MASTERREGISTRYSTORER_H_INCLUDED_
#define _LX_MASTERREGISTRYSTORER_H_INCLUDED_


#include "..\stdafx.h"
#include "..\..\..\Slave\Slave\TCP_IP_SocketHolder.h"
#include "MasterBoundStorer.h"
#include "DayHistory.h"
#include "..\..\..\Slave\Slave\RegistryDataReader.h"
#include "..\..\..\Slave\Slave\RegistryDataWriter.h"
#include "..\..\..\Slave\Slave\LoggerParametersReader.h"
#include "..\ClubSettings\BusyInterval.h"
#include "..\ClubSettings\BusyIntervalHist.h"
#include "..\ClubSettings\CycleInterval.h"
#include "..\..\..\Slave\Slave\RegistryFileManager.h"
#include "..\..\DataStructures\WindowsVersionDefiner.h"
#include "..\..\DataStructures\FinantialLoggerParametersReader.h"


// ������ ��������� ��� ������� ������������.
class CMasterRegistryStorer : public CMasterBoundStorer,
	public CRegistryDataReader, public CRegistryDataWriter,
	protected CDayHistory, public CLoggerParametersReader,
	public CRegistryFileManager, public CFinantialLoggerParametersReader
{
public:
	CMasterRegistryStorer();
	virtual ~CMasterRegistryStorer();

	virtual void ReadFileUpdateManager(CFileUpdateManager* pFileUpdateManager);

	virtual void ReadWorkingInterval(CIntervalsAncestor* TimeInterval);

	// ��������� �� ������� ������ MashinesCollection
	virtual void ReadMashinesCollection(
		CMashinesCollection* pMashinesCollection);

	virtual void ReadMashinesCollectionHistory(
		CMashinesCollection* pMashinesCollection,
		CInterval& ReadInterval);

	// ������ �������� ����
	virtual void ReadTarifPlansCollection(CTarifPlansCollection* pTarifPlan);

	// ������ ����������
	virtual void ReadOperatorsCollection(
		COperatorsCollection* pOperatorsCollection);

	// ������� � ������ MashinesCollection
	virtual void SaveMashinesCollection(
		CMashinesCollection* pMashinesCollection);

	virtual void SaveMashinesCollectionToHistory(
			CMashinesCollection* pMashinesCollection);

	// ��� ������� ���������� ���������� ���������,
	// �������� ���� ����� ������������ ��� ������������ ����������
	virtual void ChangeInterval(
		const unsigned long MashineNumber,
		const unsigned long IntervalNumber,
		CBusyInterval* pInterval);

	virtual void SaveOperatorsToHistrory(COperatorsCollection* pOperatorColl);
	virtual void SaveOperatorsChanged(COperatorsCollection* pOperatorColl);

	virtual void SaveTarifPlansToHistrory(CTarifPlansCollection* pTarifPlansColl);

	virtual void SaveBusyIntervalsToHistory(int iMachine, CBusyIntervalsCollection* pBusyIntervalsCollection);

	virtual void ReadCommonTCP_IP_SocketHolderData(CTCP_IP_SocketHolder* pHolder);

	// ������ �� ������� ������ ��� TCP_IP_Sender'�
	virtual void ReadTCP_IP_SenderData(CTCP_IP_Sender* pTCP_IP_Sender);

	// ������ �� ������� ������ ��� TCP_IP_Listener'�
	virtual void ReadTCP_IP_ListenerData(CTCP_IP_Listener* pTCP_IP_Listener);

	// ������ �� ������� ������ ��� TCP_IP_Receiver'�
	virtual void ReadTCP_IP_ReceiverData(CTCP_IP_Receiver* pReceiver);

	// ������ �� ������� ������ ��� SocketHolder'�, �� �������� ������
	// ����� ������������ � slave
	virtual void ReadMasterConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder);

	virtual void ReadMasterManager(CMasterManager* pManager);

	// �������
	virtual void ReadSlaveConnectedSocketHolder(CTCP_IP_SocketHolder* pHolder)
	{};

	// ������ ������ ��� Logger'a
	virtual void ReadErrorLoggerData(CErrorsLogger* pLogger);

	virtual void ReadKeyboardLoggerData(CKeyboardLogger* pLogger) {};

	virtual void ReadClubState(CClubState* pClubState);

	// true, ���� ���� �� ���� �������� ��� ������ �� ��������� �
	// �������� � ������ � history
	virtual bool SaveClubStateToHistory(CClubState* pClubState, const CTimeStorage& TimeToSplitHistory);


	virtual void ReadFinantialHistLoggerData(CFinantialHistoryLogger* pFinantialLogger);

	// for CashStorer
	virtual void ReadCash(CCashdesk *Cash);
	virtual void SaveCash(CCashdesk *Cash);

protected:
	CWindowsVersionDefiner m_Definer;

	// ����� �� ������ ���-�� � �����
	bool m_IsStorageChanged;

	inline CTimeStorage ReadHourMinuteTime(const std::string& sSubKeyName);

	void CMasterRegistryStorer::SaveHourMinuteTime(
		const std::string &sSubKeyName, const CTimeStorage &Time);

	inline void ReadOperatorsFromKey(const std::string &RegistryPath,
		COperatorsCollection* pOperatorsCollection);

	inline void ReadTarifPlansCollFromKey(
		const std::string &RegistryPath,
		CTarifPlansCollection* pTarifPlan);

	inline void ReadMashinesCollectionFundamental(
		const std::string &RegistryPath,
		CMashinesCollection* pMashinesCollection);

	inline void ReadBusyIntervalsFromKey(const std::string &RegistryPath,
		CBusyIntervalsCollection* pBusyIntervalsCollection);

	inline void SaveBusyIntervalsToKey(const std::string &RegistryPath,
		CBusyIntervalsCollection* pBusyIntervalsCollection);

	inline void SaveMashinesCollectionToKey(const std::string
		&RegistryPath, CMashinesCollection* pMashinesCollection, bool bWriteBIC = true);

	inline void SaveOperatorsToKey(const std::string &RegistryPath,
		COperatorsCollection* pOperatorColl);

	inline void SaveBusyIntervalHistToHKEY(CBusyIntervalHist* pBIH, HKEY& OpenedKey);

	inline void SaveTarifPlansToKey(const std::string &RegistryPath,
		CTarifPlansCollection* pTarifPlansColl);

	inline void DoReadCommonTCP_IP_SocketHolderData(PHKEY phkKey, CTCP_IP_SocketHolder* pHolder);

	inline void DoReadMasterConnectedSocketHolder(PHKEY phkKey, CTCP_IP_SocketHolder* pHolder);

	inline void DoReadTCP_IP_ReceiverData(PHKEY phkKey, CTCP_IP_Receiver* pReceiver);

	inline void DoReadMasterManagerFuflo(PHKEY phkKey, CMasterManager* pManager);

public:
	void FlushHistToFile();

	void FlushCurrToFile();
protected:
	inline void RestoreRegFromFile();

	CFileUpdateManager* m_pHistFileUpdateManager;
	CFileUpdateManager* m_pCurrFileUpdateManager;
	CFileUpdateManager* m_pYestFileUpdateManager;

private:
	inline std::string MashinesCollectionSaveToStr();
	//inline std::string OperatorCollectionSaveToStr();
	//inline std::string TarifPlansSaveToStr();
	inline std::string TodayHistoryKey();
};

#endif // _LX_MASTERREGISTRYSTORER_H_INCLUDED_