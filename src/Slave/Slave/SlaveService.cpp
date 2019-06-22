#include "stdafx.h"

#include "SlaveService.h"
#include "Constants.h"
#include "SlaveRegistryDataReader.h"
#include "ErrorsLogger.h"
#include "TimerHandler.h"
#include "SlaveManager.h"
#include "Messages.h"
#include "SlaveTPC_IP_Communicator.h"
#include "TCP_IP_SocketHolder.h"
#include "NetworkConstants.h"

#include "fcntl.h"
#include "lmcons.h"



CSlaveService::CSlaveService(HINSTANCE a_hInst) : CNTService(sSlaveServiceName.c_str())
{
	m_hInst = a_hInst;
}
// End of CSlaveService()


CSlaveService::~CSlaveService()
{

}
// End of ~CSlaveService()


void CSlaveService::Run()
{
	// Чтобы файлы воспринимались как binary, а не как text, иначе - маздай
	_fmode = _O_BINARY;

		try
		{
			// Чтобы нельзя было запустить сразу 2 экземпляра проги.
			// Если один экземпляр запущен - в лог ничего не будет писАться,
			// хотя это легко сделать. В повторный запуск - нормальная
			// ситуация при каждой загрузке винды.
			//pSlaveManager->CheckMutex(sSlaveMutexName.c_str());

			pSlaveRegistryDataReader = 0;
			// Ридер начальных данных для логгера и копиера
			pSlaveRegistryDataReader = new CSlaveRegistryDataReader;
			pSlaveRegistryDataReader->SetKey(HKEY_LOCAL_MACHINE);
			pSlaveRegistryDataReader->SetSecurityAccessMask(KEY_READ);
			*(pSlaveRegistryDataReader->GetSubKeyName()) = sSlaveRegistryPath;

			pErrorsLogger = 0;
			// Теперь pLogger инициализирован
			pErrorsLogger = new CErrorsLogger(pSlaveRegistryDataReader);
			pErrorsLogger->GetProhibitionsTable()->resize(1);
			(*pErrorsLogger->GetProhibitionsTable())[0] = "One program copy is already running";

			pSlaveManager = new CSlaveManager(m_hInst,
						pSlaveRegistryDataReader, pErrorsLogger);





			/*HMODULE hDllModule = LoadLibrary( "c:\\Program Files\\Slave\\logon.dll" );
			typedef void CGetLoggedUserName(LPTSTR a_pName, DWORD a_dwMaxLength);
			CGetLoggedUserName* pGetUserNameFunction = (CGetLoggedUserName*)GetProcAddress(hDllModule, "GetLoggedUserName");

			char cBuffer[UNLEN + 1];
			pGetUserNameFunction(&(cBuffer[0]), UNLEN);*/



			HWINSTA hStation = OpenWindowStation("winsta0", true,
						WINSTA_ACCESSCLIPBOARD   |
						WINSTA_ACCESSGLOBALATOMS |
						WINSTA_CREATEDESKTOP     |
						WINSTA_ENUMDESKTOPS      |
						WINSTA_ENUMERATE         |
						WINSTA_EXITWINDOWS       |
						WINSTA_READATTRIBUTES    |
						WINSTA_READSCREEN        |
						WINSTA_WRITEATTRIBUTES   |
						MAXIMUM_ALLOWED);
			SetProcessWindowStation(hStation);






				// Персональный try для коммуникатора, чтобы если его не
				// удается создать - залочить комп.
				try
				{
					pCommunicator = new CSlaveTCP_IP_Communicator(pSlaveRegistryDataReader);
				}
				catch(CAnyLogableException& Error)
				{
						if (pErrorsLogger)
						{
							pErrorsLogger->AddLogEntry(&Error);
						}
				}
				catch(...)
				{
				}

				if (pSlaveRegistryDataReader)
				{
					delete pSlaveRegistryDataReader;
					pSlaveRegistryDataReader = 0;
				}

			// Регистрирует процесс как Service
			//pSlaveManager->RegisterService();

			pSlaveManager->StartTimer(TimerFunction);





			// Network test
			//CTCP_IP_SocketHolder* pSocketHolder = pCommunicator->GetConnectedSocketHolder();
			//pSocketHolder->DoConnectTo();
			//pCommunicator->SendUnLockSuccess();
			// End of network test

			//throw CAnyLogableException("Exit password typed....", bDoNotWriteDuplicates);





			PostThreadMessage(GetCurrentThreadId(), WM_NEED_TO_CHECK_STATE, 0, 0);


			CTCP_IP_SocketHolder TempSocketHolder;
			DWORD dwIP = 0;
			std::string Str;

			// Чтобы прога висела и ловила мессаги
			MSG theMessage;
				while ( (GetMessage(&theMessage, NULL, 0, 0)) && (m_bIsRunning) )
				{
					if (theMessage.message == WM_CLOSE)
					{
						throw CAnyLogableException("Exit password typed!", bDoNotWriteDuplicates);
					}
						// Чтобы исключения в процессе работы не приводили к выходу
						// из программы, и чтобы их можно было записАть в лог
						try
						{
							TranslateMessage(&theMessage);
							DispatchMessage(&theMessage);
								switch (theMessage.message)
								{
									case WM_RESTART_REQUIRED:
										pSlaveManager->RestartWindows();
									break;
									case WM_TURNOFF_REQUIRED:
										pSlaveManager->TurnOffComputer();
									break;

									case WM_NEW_USER_LOGGED:
										pSlaveManager->OnNewUserLogged();
									break;

									case WM_WRITE_DEBUG_MESSAGE:
										char cFirstBuffer[20], cSecondBuffer[20];
										_itoa(theMessage.wParam, &(cFirstBuffer[0]), 10);
										_itoa(theMessage.lParam, &(cSecondBuffer[0]), 10);
											if (pErrorsLogger)
											{
												pErrorsLogger->AddLogEntry( ((std::string)"Debug Message: " + cFirstBuffer + ", " + cSecondBuffer).c_str(), bWriteDuplicates );
											}
									break;

									case WM_WRITE_TEXT_MESSAGE:
										char cBuffer[20];
										_itoa(theMessage.lParam, &(cBuffer[0]), 10);
											if (pErrorsLogger)
											{
												pErrorsLogger->AddLogEntry( (*((std::string*)theMessage.wParam) + cBuffer).c_str(), bWriteDuplicates );
											}
										delete (std::string*)theMessage.wParam;
									break;

									/*case WM_DISABLE_LOCKER:
										pSlaveManager->GetGlobalLocker()->SetEnabled(false);
										throw CAnyLogableException("Disable locker password typed!", bWriteDuplicates);
									break;

									case WM_ENABLE_LOCKER:
										pSlaveManager->GetGlobalLocker()->SetEnabled(true);
										throw CAnyLogableException("Enable locker password typed!", bWriteDuplicates);
									break;*/

									case WM_CONNECTIONACCEPTED:
										TempSocketHolder.SetSocket(theMessage.wParam);
										dwIP = TempSocketHolder.ObtainIP();
										TempSocketHolder.SetSocket(INVALID_SOCKET);

											if (dwIP == pCommunicator->GetConnectedSocketHolder()->GetAddressToConnectTo())
											{
												//pCommunicator->GetAcceptedSocketHolder()->CloseSocket();
												pCommunicator->GetAcceptedSocketHolder()->SetSocket(theMessage.wParam);
												pCommunicator->GetAcceptedSocketHolder()->GetOpenConnectionManager()->OnBegin();

												pCommunicator->SetSocketToReceiveFrom(theMessage.wParam);
												pCommunicator->DoReceive(dwBufferLength);
											}
											else
											{
												TempSocketHolder.SetSocket(theMessage.wParam);
												TempSocketHolder.CloseSocket();
											}
									break;

									case WM_CONNECTED:
											if ( !(theMessage.lParam) )
											{
												TempSocketHolder.SetSocket(theMessage.wParam);
												dwIP = TempSocketHolder.ObtainIP();
												TempSocketHolder.SetSocket(INVALID_SOCKET);

													if ( dwIP == pCommunicator->GetConnectedSocketHolder()->GetAddressToConnectTo() )
													{
														//pCommunicator->GetConnectedSocketHolder()->CloseSocket();
														pCommunicator->GetConnectedSocketHolder()->SetSocket(theMessage.wParam);
														pCommunicator->SetSocketToSendTo(pCommunicator->GetConnectedSocketHolder()->GetSocket());
														pCommunicator->SendReCheckState();
														pCommunicator->GetConnectedSocketHolder()->GetOpenConnectionManager()->OnBegin();

														pCommunicator->SetSocketToReceiveFrom(pCommunicator->GetConnectedSocketHolder()->GetSocket());
														pCommunicator->DoReceive(dwBufferLength);
													}
													else
													{
														TempSocketHolder.SetSocket(theMessage.wParam);
														TempSocketHolder.CloseSocket();
													}
											}
											else
											{
												TempSocketHolder.SetSocket(theMessage.wParam);
												TempSocketHolder.CloseSocket();
											}
									break;

									case WM_DATARECEIVED:
											if (theMessage.lParam)
											{
												pCommunicator->OnDataReceived(((CReceiveParameters*)theMessage.wParam)->GetVectorBuffer()->begin(),
															theMessage.lParam, ((CReceiveParameters*)theMessage.wParam)->GetSocket(), 0);
												((CReceiveParameters*)theMessage.wParam)->SetUsed(false);
											}
											else
											{
											}
									break;

									case WM_NEED_TO_CHECK_STATE:
											if (pCommunicator->GetConnectedSocketHolder()->GetSocket() == INVALID_SOCKET)
											{
												pCommunicator->GetConnectedSocketHolder()->DoConnectTo();
											}
									break;

									/*case WM_CHECK_SPECIAL_KEYS:
										pSlaveManager->GetGlobalLocker()->GetKeyboardLocker()->OnReCheckSpecialKeys();
									break;

									case WM_SET_IS_USER_RESTRICTED:
										pSlaveManager->GetGlobalLocker()->GetKeyboardLocker()->SetIsUserRestricted(theMessage.wParam);;
									break;*/

									case WM_UNLOCK_REQUIRED:
									case WM_LOCK_REQUIRED:
										bool bError;

											try
											{
												TempSocketHolder.SetSocket(theMessage.wParam);
												dwIP = TempSocketHolder.ObtainIP();
												TempSocketHolder.SetSocket(INVALID_SOCKET);

													if (dwIP == pCommunicator->GetConnectedSocketHolder()->GetAddressToConnectTo())
													{
														// Если командует мастер
														bError = false;

														CAdditionalRecievedData* pAdditionalData = (CAdditionalRecievedData*)theMessage.lParam;
															if (pAdditionalData)
															{
																	if ( pAdditionalData->GetData()->size() == sizeof(CRemainingTimeDescription) )
																	{
																		memcpy(pSlaveManager->GetRemainingTime(),
																					pAdditionalData->GetData()->begin(),
																					pAdditionalData->GetData()->size());
																		pSlaveManager->GetRemainingTime()->SlaveCurrent = CurrentTime().GetTime();

																			//if (pSlaveManager->GetMultiThreadedDesktopEmulator()->GetDesktopEmulator())
																				//*pSlaveManager->GetMultiThreadedDesktopEmulator()->GetDesktopEmulator()->GetRemainingDescription() = *pSlaveManager->GetRemainingTime();
																		pSlaveManager->UpdateExchangeData();
																		pAdditionalData->SetIsUsed(false);

																		pSlaveManager->GetRemainingTime()->FillInvertedTimeOutManager( pSlaveManager->GetAssumedFinishManager() );
																		pSlaveManager->GetAssumedFinishManager()->SetEnabled(true);

																		pSlaveManager->GetRemainingTime()->FillInvertedTimeOutManager( pSlaveManager->GetEarlyWarnManager() );
																		pSlaveManager->GetEarlyWarnManager()->SetEnabled(!pSlaveManager->GetEarlyWarnManager()->CheckForExpiration());

																		pSlaveManager->GetRemainingTime()->FillInvertedTimeOutManager( pSlaveManager->GetLateWarnManager() );
																		pSlaveManager->GetLateWarnManager()->SetEnabled(!pSlaveManager->GetLateWarnManager()->CheckForExpiration());
																	}
															}
															else
															{
																pSlaveManager->GetAssumedFinishManager()->SetEnabled(false);
																pSlaveManager->GetRemainingTime()->FillWithZeros();
																pSlaveManager->GetRemainingTime()->FillInvertedTimeOutManager( pSlaveManager->GetAssumedFinishManager() );
															}

															if (theMessage.message == WM_LOCK_REQUIRED)
															{
																pSlaveManager->GetRemainingTime()->cUserNames[0] = '\0';
																pSlaveManager->SetMustBeLocked(true);
															}
															if (theMessage.message == WM_UNLOCK_REQUIRED)
															{
																pSlaveManager->SetMustBeLocked(false);
															}

														pSlaveManager->GetPermissionManager()->OnBegin();

															if (theMessage.wParam == pCommunicator->GetConnectedSocketHolder()->GetSocket())
															{
																pSlaveManager->GetCheckStateManager()->OnBegin();
															}

														pSlaveManager->OnTimerEvent();
													}
													else
													{
														// Если командует не мастер
														throw CAnyLogableException("An IP address of commander is not master address! 8-[]", bWriteDuplicates);
													}
											}
											catch(CAnyLogableException& Error)
											{
													if (pErrorsLogger)
													{
														pErrorsLogger->AddLogEntry(&Error);
													}
												bError = true;
											}
											catch(...)
											{
												bError = true;
											}

										pCommunicator->SetSocketToSendTo(theMessage.wParam);
											if (bError)
											{
													if (theMessage.message == WM_LOCK_REQUIRED)
														pCommunicator->SendLockFail();
													if (theMessage.message == WM_UNLOCK_REQUIRED)
														pCommunicator->SendUnLockFail();
											}
											else
											{
													if (theMessage.message == WM_LOCK_REQUIRED)
													{
														pCommunicator->SendLockSuccess();
													}
													if (theMessage.message == WM_UNLOCK_REQUIRED)
													{
														pCommunicator->SendUnLockSuccess();
													}
											}

											if (theMessage.wParam == pCommunicator->GetAcceptedSocketHolder()->GetSocket())
											{
												pCommunicator->GetAcceptedSocketHolder()->CloseSocket();
											}
											if (theMessage.wParam == pCommunicator->GetConnectedSocketHolder()->GetSocket())
											{
												pCommunicator->GetConnectedSocketHolder()->CloseSocket();
											}
									break;
								}
						}
						catch(CAnyLogableException& Error)
						{
								if (pErrorsLogger)
								{
									pErrorsLogger->AddLogEntry(&Error);
								}
						}
						catch(...)
						{
								if (pErrorsLogger)
								{
									pErrorsLogger->AddLogEntry("An unknown error occured in message loop", bDoNotWriteDuplicates);
								}
						}
				}
		}
		catch(CAnyLogableException& Error)
		{
				if (pErrorsLogger)
				{
					pErrorsLogger->AddLogEntry(&Error);
				}
		}
		catch(...)
		{
				if (pErrorsLogger)
				{
					pErrorsLogger->AddLogEntry("An unknown error occured in WinMain", bWriteDuplicates);
				}
		}

		try
		{
				if (pSlaveManager)
				{
					delete pSlaveManager;
					pSlaveManager = 0;
				}
				if (pSlaveRegistryDataReader)
				{
					delete pSlaveRegistryDataReader;
					pSlaveRegistryDataReader = 0;
				}
				if (pCommunicator)
				{
					delete pCommunicator;
					pCommunicator = 0;
				}
		}
		catch(CAnyLogableException& Error)
		{
				if (pErrorsLogger)
				{
					pErrorsLogger->AddLogEntry(&Error);
				}
		}
		catch(...)
		{
				if (pErrorsLogger)
				{
					pErrorsLogger->AddLogEntry("An unknown error while destroying", bWriteDuplicates);
				}
		}

		if (pErrorsLogger)
		{
			delete pErrorsLogger;
			pErrorsLogger = 0;
		}

	//Sleep(3000);
}
// End of Run()


BOOL CSlaveService::OnInit()
{
	//DebugMsg("CNTService::OnInit()");
	return TRUE;
}

void CSlaveService::OnStop()
{
	//DebugMsg("CNTService::OnStop()");
}

void CSlaveService::OnInterrogate()
{
	//DebugMsg("CNTService::OnInterrogate()");
}

void CSlaveService::OnPause()
{
	//DebugMsg("CNTService::OnPause()");
}

void CSlaveService::OnContinue()
{
	//DebugMsg("CNTService::OnContinue()");
}

void CSlaveService::OnShutdown()
{
	//DebugMsg("CNTService::OnShutdown()");
}

BOOL CSlaveService::OnUserControl(DWORD dwOpcode)
{
	//DebugMsg("CNTService::OnUserControl(%8.8lXH)", dwOpcode);
	return FALSE; // say not handled
}
