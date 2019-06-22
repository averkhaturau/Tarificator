# Microsoft Developer Studio Project File - Name="Interface" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Interface - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Interface.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Interface.mak" CFG="Interface - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Interface - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Interface - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Interface - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib SHLWAPI.LIB COMMODE.OBJ /nologo /stack:0x10000 /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 COMMODE.OBJ ws2_32.lib SHLWAPI.LIB /nologo /stack:0x10000 /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Interface - Win32 Release"
# Name "Interface - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\AdditionalResource.h
# End Source File
# Begin Source File

SOURCE=.\RES\Cursor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Interface.ico
# End Source File
# Begin Source File

SOURCE=.\res\Interface.rc2
# End Source File
# Begin Source File

SOURCE=.\res\InterfaceDoc.ico
# End Source File
# Begin Source File

SOURCE=.\RES\smallico.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=".\Res\Окончательный вариант.bmp"
# End Source File
# End Group
# Begin Group "MFC Document Architecture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BusyChildFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\BusyChildFrame.h
# End Source File
# Begin Source File

SOURCE=.\BusyView.cpp
# End Source File
# Begin Source File

SOURCE=.\BusyView.h
# End Source File
# Begin Source File

SOURCE=.\ButtonsBarView.h
# End Source File
# Begin Source File

SOURCE=.\CashChildFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\CashChildFrame.h
# End Source File
# Begin Source File

SOURCE=.\CashView.cpp
# End Source File
# Begin Source File

SOURCE=.\CashView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrmWithoutClose.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrmWithoutClose.h
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# Begin Source File

SOURCE=.\Interface.rc
# End Source File
# Begin Source File

SOURCE=.\InterfaceDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceDoc.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UsualChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\UsualChildFrm.h
# End Source File
# End Group
# Begin Group "From MasterDataStructures"

# PROP Default_Filter ""
# Begin Group "MasterManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\MasterManager\MasterManager.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\MasterManager\MasterManager.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\MasterManager\MasterManagerAttribute.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\MasterManager\MasterManagerAttribute.h
# End Source File
# End Group
# Begin Group "ClubSettings"

# PROP Default_Filter ""
# Begin Group "Intervals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\AppHistoryInterval.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\AppHistoryInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\BusyInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\BusyIntervalEvent.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ColoredInterval.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ColoredInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ColoredTimeClass.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\CycleColoredInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\CycleInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\IntervalAddition.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\IntervalAddition.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\RemainingTimeDescription.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TarifInterval.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TarifInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeException.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeInterval.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeStorage.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeStorage.h
# End Source File
# End Group
# Begin Group "IntervalsCollections"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\AppIntervalsCollection.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\BusyIntervalHist.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\BusyIntervalHist.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\BusyIntervalsCollection.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\BusyIntervalsCollection.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ColoredIntervalsCollection.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\IntervalsStorage.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TarifPlan.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TarifPlansCollection.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TarifPlanSpec.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\Cashdesk.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ClubState.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ClubState.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\MashineData.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\MashineData.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\MashinesCollection.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\MashinesCollection.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\Operator.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\Operator.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\OperatorsCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\OperatorsCollection.h
# End Source File
# End Group
# Begin Group "Slave Project"

# PROP Default_Filter ""
# Begin Group "Communicator_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Slave\Slave\AdditionalRecievedData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\AdditionalRecievedData.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\AdditionalRecievedDatumCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\AdditionalRecievedDatumCollection.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\AsyncExchanger.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\AsyncExchanger.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Commander.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Commander.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Incoming.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Incoming.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Listener.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Listener.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Outcoming.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Outcoming.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Receiver.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Receiver.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiverParamsCollection.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiverParamsCollection.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Sender.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Sender.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Class.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Class.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Listener.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Listener.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Receiver.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Receiver.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Sender.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Sender.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_SocketHolder.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_SocketHolder.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\Slave\Slave\ErrorsLogger.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ErrorsLogger.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Exceptions.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Logger.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Logger.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\LoggerParametersReader.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\LoggerWithFullFileName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\LoggerWithFullFileName.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ManagersCollection.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\MultiThreadManager.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\MultiThreadManager.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\NamesCollection.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\NetworkParametersDataReader.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiveManagersCollection.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiveManagersCollection.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiveMulthiThreadManager.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiveMulthiThreadManager.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryFileManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryFileManager.h
# End Source File
# End Group
# Begin Group "Saving"

# PROP Default_Filter ""
# Begin Group "UpdateManager No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\FileUpdateManager.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\FileUpdateManager.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\UpdateManager.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\UpdateManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\DataStructures\CashLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\CashLogger.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\CashStorer.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Saving\DayHistory.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Saving\DayHistory.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\FinantialHistoryLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\FinantialHistoryLogger.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\FinantialLoggerParametersReader.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Saving\MasterBoundStorer.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Saving\MasterRegistryStorer.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Saving\MasterRegistryStorer.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryClass.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryClass.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataReader.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataReader.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataWriter.cpp

!IF  "$(CFG)" == "Interface - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Interface - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataWriter.h
# End Source File
# End Group
# Begin Group "Communicator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterCommunicator.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterCommunicator.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\MasterMessages.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterTCP_IP_Communicator.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterTCP_IP_Communicator.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Messages.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TimeOutManager.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TimeOutManager.h
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\ActiveContainer.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ActiveContainerResizable.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Constants.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\GlobalVariables.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\TimerHandler.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\WindowsVersionDefiner.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\WindowsVersionDefiner.h
# End Source File
# End Group
# Begin Group "Security"

# PROP Default_Filter ""
# Begin Group "Cryptography"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Cryptor.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Encryptor.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Encryptor.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Hasher.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Hasher.h
# End Source File
# End Group
# Begin Group "Logon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Logon\collect.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Logon\collect.h
# End Source File
# Begin Source File

SOURCE=..\Logon\comm.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Logon\comm.h
# End Source File
# Begin Source File

SOURCE=..\Logon\DomainNameDefiner.cpp
# End Source File
# Begin Source File

SOURCE=..\Logon\DomainNameDefiner.h
# End Source File
# Begin Source File

SOURCE=..\Logon\security.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Logon\security.h
# End Source File
# Begin Source File

SOURCE=..\Logon\SSPLogon.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Logon\SSPLogon.h
# End Source File
# Begin Source File

SOURCE=..\Logon\StdAfx.h
# End Source File
# End Group
# End Group
# Begin Group "Holidays"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\SpecDaysCollection.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\SpecdaysCollStorer.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\SpecialDay.h
# End Source File
# End Group
# End Group
# Begin Group "Specific"

# PROP Default_Filter ""
# Begin Group "MashinesSelectionControl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DoubleListSelectionControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DoubleListSelectionControl.h
# End Source File
# Begin Source File

SOURCE=.\MashinesSelectionControl.cpp
# End Source File
# Begin Source File

SOURCE=.\MashinesSelectionControl.h
# End Source File
# End Group
# Begin Group "GridControl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GridCtrlSource\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridCell.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrlSource\TitleTip.h
# End Source File
# End Group
# Begin Group "MashineLinesGrid"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IntervalsCell.cpp
# End Source File
# Begin Source File

SOURCE=.\IntervalsCell.h
# End Source File
# Begin Source File

SOURCE=.\MashineLinesGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\MashineLinesGrid.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\IntervalsLine.cpp
# End Source File
# Begin Source File

SOURCE=.\IntervalsLine.h
# End Source File
# Begin Source File

SOURCE=.\LineControl.cpp
# End Source File
# Begin Source File

SOURCE=.\LineControl.h
# End Source File
# End Group
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Group "From Lab1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IntEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\IntEdit.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ClientPaybackDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientPaybackDialog.h
# End Source File
# Begin Source File

SOURCE=.\NewIntervalDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewIntervalDialog.h
# End Source File
# Begin Source File

SOURCE=.\PswrdDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PswrdDialog.h
# End Source File
# Begin Source File

SOURCE=.\ShutdownDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ShutdownDialog.h
# End Source File
# Begin Source File

SOURCE=.\TakeOfDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TakeOfDlg.h
# End Source File
# End Group
# End Target
# End Project
