# Microsoft Developer Studio Project File - Name="Operator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Operator - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Operator.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Operator.mak" CFG="Operator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Operator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Operator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Operator - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Interface\Release"
# PROP Intermediate_Dir "..\Interface\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SHLWAPI.LIB ws2_32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Operator.exe"

!ELSEIF  "$(CFG)" == "Operator - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Interface\Debug"
# PROP Intermediate_Dir "..\Interface\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SHLWAPI.LIB ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/Operator.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Operator - Win32 Release"
# Name "Operator - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Operator.ico
# End Source File
# Begin Source File

SOURCE=.\res\Operator.rc2
# End Source File
# End Group
# Begin Group "Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OperatorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OperatorDlg.h
# End Source File
# End Group
# Begin Group "App"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Operators.cpp
# End Source File
# Begin Source File

SOURCE=.\Operators.h
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\Saving\DayHistory.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Saving\DayHistory.h
# End Source File
# Begin Source File

SOURCE=.\Operator.rc
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryClass.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryClass.h
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
# End Group
# Begin Group "From MasterDataStructures"

# PROP Default_Filter ""
# Begin Group "MasterManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\MasterManager\MasterManager.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\MasterManager\MasterManager.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\MasterManager\MasterManagerAttribute.cpp
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
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\IntervalAddition.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TarifInterval.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TarifInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeException.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeInterval.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeInterval.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\TimeStorage.cpp
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
# End Group
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ClubState.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\ClubState.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\MashineData.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\MashineData.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\ClubSettings\MashinesCollection.cpp
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
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\AsyncExchanger.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Commander.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Commander.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Incoming.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Incoming.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Listener.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Listener.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Outcoming.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Outcoming.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Receiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Receiver.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiverParamsCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiverParamsCollection.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Sender.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Sender.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Class.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Class.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Listener.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Listener.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Receiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Receiver.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Sender.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_Sender.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_SocketHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TCP_IP_SocketHolder.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\Slave\Slave\ErrorsLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ErrorsLogger.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Exceptions.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Logger.cpp
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

SOURCE=..\..\Slave\Slave\ManagersCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\MultiThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\NamesCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\NetworkParametersDataReader.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiveManagersCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiveManagersCollection.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\ReceiveMulthiThreadManager.cpp
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
# End Source File
# Begin Source File

SOURCE=..\DataStructures\FileUpdateManager.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\UpdateManager.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\UpdateManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\DataStructures\CashLogger.cpp
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
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Saving\MasterRegistryStorer.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataReader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataReader.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataWriter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryDataWriter.h
# End Source File
# End Group
# Begin Group "Communicator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterCommunicator.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterCommunicator.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\MasterMessages.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterTCP_IP_Communicator.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Communicator\MasterTCP_IP_Communicator.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\Messages.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TimeOutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\TimeOutManager.h
# End Source File
# End Group
# Begin Group "Others No. 1"

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
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Encryptor.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Hasher.cpp
# End Source File
# Begin Source File

SOURCE=..\DataStructures\Cryptography\Hasher.h
# End Source File
# End Group
# Begin Group "Logon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Logon\Collect.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Logon\collect.h
# End Source File
# Begin Source File

SOURCE=..\Logon\Comm.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Logon\comm.h
# End Source File
# Begin Source File

SOURCE=..\Logon\Security.c
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
# End Group
# End Target
# End Project
