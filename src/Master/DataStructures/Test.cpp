
//#include <windows.h>
#include "stdafx.h"
#include "MasterManager\MasterManager.h"
#include "ClubSettings\TimeStorage.h"
#include "ClubSettings\TimeException.h"
#include "ClubSettings\AppIntervalsCollection.h"
#include "ClubSettings\BusyIntervalsCollection.h"
#include "ClubSettings\TarifPlansCollection.h" 
#include "Saving\MasterRegistryStorer.h"
#include "ClubSettings\MashinesCollection.h"
#include "ClubSettings\OperatorsCollection.h"
#include "Saving\MasterRegistryStorer.h"
#include "..\..\Slave\Slave\Messages.h"
#include "..\..\Slave\Slave\MasterMessages.h"
#include "Constants.h"
#include "GlobalVariables.h"
#include "TimerHandler.h"
#include "..\..\Slave\Slave\NetworkConstants.h"
#include "ActiveContainerResizable.h"
#include "..\Logon\SSPLogon.h"
#include "Cryptography\Cryptor.h"


int APIENTRY WinMain(HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{

	const char* _boolmeaning[] = {"False", "True"};

	try{
		LPSYSTEMTIME _lpSysTime = new SYSTEMTIME;
		LPFILETIME _lpFileTime = new FILETIME;

		try{

			/*if( !SSP::SSPLogonUser("LX", "NetLogonTest", "pocemon"))
				throw CAnyLogableException("SSP LOGON FAILED!", bDoNotWriteDuplicates);*/


			CCryptor _Cryptor;

			__int64 i64Hash = _Cryptor.Str2i64("X0poшый пAsсw0rд №1");

			CMasterRegistryStorer _MRegStorer; // его тестируем

			pMasterManager = new CMasterManager(&_MRegStorer);
			pMasterManager->StartTimer(TimerFunction);

			_MRegStorer.SaveMashinesCollection(
				pMasterManager->GetClubState()->GetMashinesCollection());

			_MRegStorer.SaveOperatorsToHistrory(
			pMasterManager->GetClubState()->GetOperatorsCollection());

			_MRegStorer.SaveTarifPlansToHistrory(
			pMasterManager->GetClubState()->GetTarifPlansCollection());

			CBusyInterval _Busik(CTimeStorage(1), CTimeStorage(2),
				1, 1, "Федя", CurrentTime());
			_MRegStorer.ChangeInterval(0,0, &_Busik);

			_MRegStorer.SaveMashinesCollectionToKey("SOFTWARE\\_LX\\Test",
					pMasterManager->GetClubState()->GetMashinesCollection());

			CTCP_IP_SocketHolder TempSocketHolder;
			DWORD dwIP = 0;
			CMashineData* pMashine = 0;

			// Чтобы прога висела и ловила мессаги
			MSG theMessage;
			while ( GetMessage(&theMessage, NULL, 0, 0) )
			{
				if (theMessage.message == WM_CLOSE)
					throw CAnyLogableException("Get WM_CLOSE", bDoNotWriteDuplicates);
				// Чтобы исключения в процессе работы не приводили к выходу
				// из программы, и чтобы их можно было записАть в лог
				try
				{
					TranslateMessage(&theMessage);
					DispatchMessage(&theMessage);
					switch (theMessage.message)
					{
						case WM_CONNECTIONACCEPTED:
							TempSocketHolder.SetSocket(theMessage.wParam);
							dwIP = TempSocketHolder.ObtainIP();
							pMashine = pMasterManager->GetClubState()->
										GetMashinesCollection()->FindMashine(dwIP);

							if (pMashine)
							{
								pMashine->GetAcceptingSocket()->SetSocket(theMessage.wParam);
								pMashine->GetAcceptingSocket()->GetOpenConnectionManager()->OnBegin();
								pMasterManager->GetCommunicator()->SetSocketToReceiveFrom(theMessage.wParam);
								pMasterManager->GetCommunicator()->DoReceive(dwBufferLength);
								pMashine = 0;
							}
						break;

						case WM_CONNECTED:
							if ( !(theMessage.lParam) )
							{
								TempSocketHolder.SetSocket(theMessage.wParam);
								dwIP = TempSocketHolder.ObtainIP();
								pMashine = pMasterManager->GetClubState()->
											GetMashinesCollection()->FindMashine(dwIP);

									if (pMashine)
									{
										pMashine->GetConnectingSocket()->SetSocket(theMessage.wParam);
										PostThreadMessage(GetCurrentThreadId(), WM_RE_CHECK_STATE_REQUEST, theMessage.wParam, 0);
									}
							}
							else
							{
								
							}
						break;

						case WM_DATARECEIVED:
							CReceiveParameters* pParameters;
							pParameters = (CReceiveParameters*)theMessage.wParam;
								if ( theMessage.lParam )
								{
									pMasterManager->GetCommunicator()->OnDataReceived(pParameters->GetBuffer(), pParameters->GetSize(), pParameters->GetSocket(), 0);
									pParameters->SetUsed(false);
								}
								else
								{
									pParameters->SetUsed(false);
								}
						break;

						case WM_LOCK_SUCCESS_ACKNOWLEDGE:
						case WM_UNLOCK_SUCCESS_ACKNOWLEDGE:
						case WM_LOCK_FAIL_ACKNOWLEDGE:
						case WM_UNLOCK_FAIL_ACKNOWLEDGE:
						{
							TempSocketHolder.SetSocket(theMessage.wParam);
							dwIP = TempSocketHolder.ObtainIP();
							pMashine = pMasterManager->GetClubState()->
										GetMashinesCollection()->FindMashine(dwIP);

								if (pMashine)
								{
										if (theMessage.lParam == WM_LOCK_SUCCESS_ACKNOWLEDGE)
											pMashine->GetLastSuccessCommunication()->OnBegin();
										if (theMessage.lParam == WM_UNLOCK_SUCCESS_ACKNOWLEDGE)
											pMashine->GetLastSuccessCommunication()->OnBegin();

										if (theMessage.lParam == WM_LOCK_FAIL_ACKNOWLEDGE)
										{
											// Application-specific обработка
										}
										if (theMessage.lParam == WM_UNLOCK_FAIL_ACKNOWLEDGE)
										{
											// Application-specific обработка
										}


										if (theMessage.wParam == pMashine->GetAcceptingSocket()->GetSocket())
											pMashine->GetAcceptingSocket()->CloseSocket();
										if (theMessage.wParam == pMashine->GetConnectingSocket()->GetSocket())
											pMashine->GetConnectingSocket()->CloseSocket();

									pMashine = 0;
								}
								else
								{
									TempSocketHolder.SetSocket(theMessage.wParam);
									TempSocketHolder.CloseSocket();
								}
						}
						break;

						case WM_RE_CHECK_STATE_REQUEST:
						{
							TempSocketHolder.SetSocket(theMessage.wParam);
							dwIP = TempSocketHolder.ObtainIP();
							pMashine = pMasterManager->GetClubState()->
										GetMashinesCollection()->FindMashine(dwIP);
								if (pMashine)
								{
									pMasterManager->GetCommunicator()->SetSocketToSendTo(theMessage.wParam);
										if (pMashine->GetCurrentMashineState() != msBusy)
										{
											pMasterManager->GetCommunicator()->SendUnLockOrder();
										}
										else
										{
											pMasterManager->GetCommunicator()->SendLockOrder();
										}
									pMashine = 0;

									pMasterManager->GetCommunicator()->SetSocketToReceiveFrom(theMessage.wParam);
									pMasterManager->GetCommunicator()->DoReceive(dwBufferLength);
								}
						}
						break;

					}
				}
				catch(CAnyLogableException)
				{
				}
				catch(...)
				{
				}
			}

		}
		catch(CAnyLogableException &e)
		{
			MessageBox(0, e.what(), "CAnyLogableException", MB_ICONERROR);
 		}
		catch(std::exception &e)
		{
			MessageBox(0, e.what(), "std::exception", MB_ICONERROR);
 		}
		catch(...)
		{
			MessageBox(0, "Unknown exception", "Sorry", MB_ICONHAND);
		}

		delete _lpSysTime;
		delete _lpFileTime;
		if (pMasterManager)
		{
			delete pMasterManager;
			pMasterManager = 0;
		}

	}catch(...){
		MessageBox(0, "Unhandled exception deals with memory", "Sorry", MB_ICONHAND);
	}
	return 0;
}


















/*	Это тест для CTimeStorage
		LPSYSTEMTIME _lpSysTime = new SYSTEMTIME;
		GetSystemTime(_lpSysTime);
		CTimeStorage _time1;
		CTimeStorage _time2(_lpSysTime);
		CTimeStorage _time3(_time2.GetTime());
		GetSystemTime(_lpSysTime);
		_time1.SetTime(_lpSysTime);

		_time2.GetTime(_lpSysTime);

		delete _lpSysTime;

		MessageBox(0, _i64toa(_time1.GetTime(),buf, 16),"_time1 is",0);
		MessageBox(0, _i64toa(_time2.GetTime(),buf, 16),"_time2 is",0);
		MessageBox(0, _i64toa(_time3.GetTime(),buf, 16),"_time3 is",0);

		_time3 = _time1;

		MessageBox(0, _i64toa(_time1.GetTime(),buf, 16),"_time1 is",0);
		MessageBox(0, _i64toa(_time2.GetTime(),buf, 16),"_time2 is",0);
		MessageBox(0, _i64toa(_time3.GetTime(),buf, 16),"_time3 is",0);
*/

/*	Test for CBusyInterval

		CBusyInterval _BusyInterval_1;

		LPSYSTEMTIME _lpSysTime = new SYSTEMTIME;
		GetSystemTime(_lpSysTime);
		CTimeStorage _time2(_lpSysTime);
		delete _lpSysTime;
		CTimeStorage _time3(_time2.GetTime()+3);

		CBusyInterval _BusyInterval_2(_time2, _time3,
			CBusyInterval::tpnInternet);

		_BusyInterval_1.SetInterval(_time3, _time2);
		_BusyInterval_1.SetTarifPlan(CBusyInterval::tpnObsoleteMashine);

		CTimeStorage _Time_4, _Time_1;

		_BusyInterval_1.GetInterval(_Time_1, _Time_4);
		
		MessageBox(0, _i64toa(_Time_1.GetTime(),buf, 16),"_Time_1 is",0);
		MessageBox(0, _i64toa(_Time_4.GetTime(),buf, 16),"_Time_4 is",0);
*/

/*	CTimeTest
		LPSYSTEMTIME _lpSysTime = new SYSTEMTIME;
		LPFILETIME _lpFileTime = new FILETIME;
		GetSystemTime(_lpSysTime);
		CTimeStorage _time2(_lpSysTime);
		delete _lpSysTime;
		GetSystemTimeAsFileTime(_lpFileTime);
		CTimeStorage _time3(_lpFileTime);
		delete _lpFileTime;

		CTarifInterval::CCurrency _100rubley = 100;
		CTarifInterval _TarifInterval(_time3, _time2, _100rubley);

		MessageBox(0, _i64toa((_time3-_time2).GetTime(),buf, 16),"_Time2 is",0);
		MessageBox(0, _i64toa(_time3.GetTime()-_time2.GetTime(),buf, 16),"_Time3 is",0);
*/

/*		CIntervalsCollectionTest
			GetSystemTime(_lpSysTime);
			CTimeStorage _time2(_lpSysTime);
			GetSystemTimeAsFileTime(_lpFileTime);
			CTimeStorage _time3(_lpFileTime);
			CInterval _Interval_1(_time2, _time3);

			GetSystemTime(_lpSysTime);
			_time2.SetTime(_lpSysTime);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			CInterval _Interval_2(_time2, _time3);

			GetSystemTime(_lpSysTime);
			_time2.SetTime(_lpSysTime);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			CInterval _Interval_3(_time2, _time3);

			CIntervalsCollection<CInterval> _IntervalCollection;
			_IntervalCollection.AddInterval(&_Interval_1);
			_IntervalCollection.AddInterval(&_Interval_2);
			_IntervalCollection.AddInterval(&_Interval_3);

			GetSystemTime(_lpSysTime);
			_time2.SetTime(_lpSysTime);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			_Interval_2.SetInterval(_time2, _time3);
			_IntervalCollection.AddInterval(&_Interval_2);

			//MessageBox(0, _i64toa((_time3-_time2).GetTime(),buf, 16),"_Time2 is",0);
			MessageBox(0, _i64toa(_IntervalCollection.IsValidIntervalCollection(),buf, 16),"Validity of collection",0);
  */

/*		тест для CBusyIntervalsCollection
			GetSystemTime(_lpSysTime);
			CTimeStorage _time2(_lpSysTime);
			GetSystemTimeAsFileTime(_lpFileTime);
			CTimeStorage _time3(_lpFileTime);
			CBusyInterval _Interval_1(_time2, _time3, 3);

			Sleep(90);

			GetSystemTime(_lpSysTime);
			CTimeStorage _time1(_lpSysTime);

			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			Sleep(10);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time2.SetTime(_lpFileTime);
			CBusyInterval _Interval_2(_time3, _time2, 4);

			Sleep(30);

			GetSystemTimeAsFileTime(_lpFileTime);
			_time2.SetTime(_lpFileTime);
			Sleep(12);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			CBusyInterval _Interval_3(_time2, _time3, 0); 
			// глюк - не вызывается виртуальная IsValidIntervalCollection() для CBusyInterval

			CIntervalsCollection<CBusyInterval*> _IntervalCollection;
			_IntervalCollection.AddInterval(&_Interval_1);
			_IntervalCollection.AddInterval(&_Interval_2);
			_IntervalCollection.AddInterval(&_Interval_3);

			//MessageBox(0, _i64toa((_time3-_time2).GetTime(),_buf, 16),"_Time2 is",0);
			MessageBox(0, _boolmeaning[_IntervalCollection.IsValidIntervalCollection()&1],"Validity of collection",0);
*/

/*		CTarofINterval test
			GetSystemTime(_lpSysTime);
			CTimeStorage _time2(_lpSysTime);
			Sleep(13);
			GetSystemTimeAsFileTime(_lpFileTime);
			CTimeStorage _time3(_lpFileTime);
			CTarifInterval _Interval_1(_time2, _time3, 3);

			Sleep(90);

			GetSystemTime(_lpSysTime);
			CTimeStorage _time1(_lpSysTime);

			GetSystemTimeAsFileTime(_lpFileTime);
			_time2.SetTime(_lpFileTime);
			CTarifInterval _Interval_2(_time3, _time2, 4);

			Sleep(30);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			CTarifInterval _Interval_3(_time2, _time3, 1); 
			// глюк - не вызывается виртуальная IsValidIntervalCollection() для CBusyInterval

			CIntervalsCollection<CTarifInterval*> _IntervalCollection;
			_IntervalCollection.AddInterval(&_Interval_1);
			_IntervalCollection.AddInterval(&_Interval_2);
			_IntervalCollection.AddInterval(&_Interval_3);

			//MessageBox(0, _i64toa((_time3-_time2).GetTime(),_buf, 16),"_Time2 is",0);
			MessageBox(0, _boolmeaning[_IntervalCollection.IsValidIntervalCollection()&1],"Validity of collection",0);
*/

/*		CIntervalsCollection<CAppInterval*> test

			GetSystemTime(_lpSysTime);
			CTimeStorage _time2(_lpSysTime);
			GetSystemTimeAsFileTime(_lpFileTime);
			CTimeStorage _time3(_lpFileTime);
			CAppInterval _Interval_1(_time2, _time3, "Excel");

			Sleep(90);

			GetSystemTime(_lpSysTime);
			CTimeStorage _time1(_lpSysTime);

			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			Sleep(10);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time2.SetTime(_lpFileTime);
			CAppInterval _Interval_2(_time3, _time2, "NFS");

			Sleep(30);

			GetSystemTimeAsFileTime(_lpFileTime);
			_time2.SetTime(_lpFileTime);
			Sleep(12);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			CAppInterval _Interval_3(_time1, _time3, "Project IGI"); 


			CIntervalsCollection<CAppInterval*> _IntervalCollection;
			_IntervalCollection.AddInterval(&_Interval_1);
			_IntervalCollection.AddInterval(&_Interval_2);
			_IntervalCollection.AddInterval(&_Interval_3);

			//MessageBox(0, _i64toa((_time3-_time2).GetTime(),_buf, 16),"_Time2 is",0);
			MessageBox(0, _boolmeaning[_IntervalCollection.IsValidIntervalCollection()&1],"Validity of collection",0);
*/

/*
			GetSystemTime(_lpSysTime);
			CTimeStorage _time2(_lpSysTime);
			GetSystemTimeAsFileTime(_lpFileTime);
			CTimeStorage _time3(_lpFileTime);
			CAppInterval _Interval_1(_time2, _time3, "NFS");

			Sleep(90);

			GetSystemTime(_lpSysTime);
			CTimeStorage _time1(_lpSysTime);

			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			Sleep(10);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time2.SetTime(_lpFileTime);
			CAppInterval _Interval_2(_time3, _time2, "");// это неправильный интервал

			Sleep(30);

			GetSystemTimeAsFileTime(_lpFileTime);
			_time2.SetTime(_lpFileTime);
			Sleep(12);
			GetSystemTimeAsFileTime(_lpFileTime);
			_time3.SetTime(_lpFileTime);
			CAppInterval _Interval_3(_time2, _time3, "Project IGI");

			CIntervalsCollection<CAppInterval*> _IntervalCollection;
			_IntervalCollection.AddInterval(&_Interval_3);
			_IntervalCollection.AddInterval(&_Interval_1);
			_IntervalCollection.AddInterval(&_Interval_2);

			_Interval_2.SetAppName("AOE");
			//_Interval_2.SetFinishTime(_time1);

			MessageBox(0, _boolmeaning[_IntervalCollection.IsValidIntervalsCollection()&1],"Validity of collection",0);

			_IntervalCollection.DeleteBefore(_time1);
			_IntervalCollection.DeleteInterval(_Interval_2);

			//MessageBox(0, _i64toa((_time3-_time2).GetTime(),_buf, 16),"_Time2 is",0);
			MessageBox(0, _boolmeaning[_IntervalCollection.IsValidIntervalsCollection()&1],"Validity of collection",0);
*/

/*
			GetSystemTime(_lpSysTime);
			CTimeStorage _time2(_lpSysTime);

			++(_lpSysTime->wMinute);
			CTimeStorage _time1(_lpSysTime);

			--(_lpSysTime->wMinute);
			++(_lpSysTime->wHour);
			CTimeStorage _time3(_lpSysTime);

			MessageBox(0, _i64toa((_time1-_time2).GetTime(),_buf, 16),"Minute is",0);
			MessageBox(0, _i64toa((_time3-_time2).GetTime(),_buf, 16),"Hour is",0);
*/