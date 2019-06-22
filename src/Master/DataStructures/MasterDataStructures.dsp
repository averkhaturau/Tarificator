# Microsoft Developer Studio Project File - Name="MasterDataStructures" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MasterDataStructures - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MasterDataStructures.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MasterDataStructures.mak" CFG="MasterDataStructures - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MasterDataStructures - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MasterDataStructures - Win32 PreRelease" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"msvcrt.lib"

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MasterDataStructures___Win32_PreRelease"
# PROP BASE Intermediate_Dir "MasterDataStructures___Win32_PreRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PreRelease"
# PROP Intermediate_Dir "PreRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /w /W0 /GX /Z7 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /subsystem:windows /machine:I386 /out:"Release/MasterDataStructures.exe"
# ADD LINK32 WS2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"PreRelease/MasterTest.exe"

!ENDIF 

# Begin Target

# Name "MasterDataStructures - Win32 Release"
# Name "MasterDataStructures - Win32 PreRelease"
# Begin Group "MasterManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MasterManager\MasterManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MasterManager\MasterManager.h
# End Source File
# Begin Source File

SOURCE=.\MasterManager\MasterManagerAttribute.cpp
# End Source File
# Begin Source File

SOURCE=.\MasterManager\MasterManagerAttribute.h
# End Source File
# End Group
# Begin Group "ClubSettings"

# PROP Default_Filter ""
# Begin Group "Intervals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClubSettings\AppHistoryInterval.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\AppHistoryInterval.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\BusyInterval.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\BusyIntervalEvent.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\ColoredInterval.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\ColoredInterval.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\ColoredTimeClass.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\CycleColoredInterval.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\CycleInterval.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\IntervalAddition.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\IntervalAddition.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TarifInterval.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TarifInterval.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TimeException.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TimeInterval.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TimeInterval.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TimeStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TimeStorage.h
# End Source File
# End Group
# Begin Group "IntervalsCollections"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClubSettings\AppIntervalsCollection.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\BusyIntervalHist.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\BusyIntervalHist.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\BusyIntervalsCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\BusyIntervalsCollection.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\ColoredIntervalsCollection.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\IntervalsStorage.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TarifPlan.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\TarifPlansCollection.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ClubSettings\ClubState.cpp

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ClubSettings\ClubState.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\MashineData.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\MashineData.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\MashinesCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\MashinesCollection.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\Operator.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\Operator.h
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\OperatorsCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubSettings\OperatorsCollection.h
# End Source File
# End Group
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\test.cpp
# End Source File
# End Group
# Begin Group "Slave Project"

# PROP Default_Filter ""
# Begin Group "Communicator_"

# PROP Default_Filter ""
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
# Begin Group "UpdateManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DataStructures\FileUpdateManager.cpp

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\FileUpdateManager.h
# End Source File
# Begin Source File

SOURCE=..\DataStructures\UpdateManager.cpp

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DataStructures\UpdateManager.h
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
# Begin Source File

SOURCE=.\Saving\DayHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\Saving\DayHistory.h
# End Source File
# Begin Source File

SOURCE=.\FinantialHistoryLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\FinantialHistoryLogger.h
# End Source File
# Begin Source File

SOURCE=.\FinantialLoggerParametersReader.h
# End Source File
# Begin Source File

SOURCE=.\Saving\MasterBoundStorer.h
# End Source File
# Begin Source File

SOURCE=.\Saving\MasterRegistryStorer.cpp
# End Source File
# Begin Source File

SOURCE=.\Saving\MasterRegistryStorer.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryClass.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\RegistryClass.h
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

SOURCE=.\Communicator\MasterCommunicator.cpp
# End Source File
# Begin Source File

SOURCE=.\Communicator\MasterCommunicator.h
# End Source File
# Begin Source File

SOURCE=..\..\Slave\Slave\MasterMessages.h
# End Source File
# Begin Source File

SOURCE=.\Communicator\MasterTCP_IP_Communicator.cpp
# End Source File
# Begin Source File

SOURCE=.\Communicator\MasterTCP_IP_Communicator.h
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
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ActiveContainer.h
# End Source File
# Begin Source File

SOURCE=.\ActiveContainerResizable.h
# End Source File
# Begin Source File

SOURCE=.\Constants.h

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GlobalVariables.h
# End Source File
# Begin Source File

SOURCE=.\TimerHandler.h
# End Source File
# Begin Source File

SOURCE=.\WindowsVersionDefiner.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowsVersionDefiner.h
# End Source File
# End Group
# Begin Group "Security"

# PROP Default_Filter ""
# Begin Group "Cryptography"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Cryptography\Cryptor.h
# End Source File
# Begin Source File

SOURCE=.\Cryptography\Encryptor.cpp
# End Source File
# Begin Source File

SOURCE=.\Cryptography\Encryptor.h
# End Source File
# Begin Source File

SOURCE=.\Cryptography\Hasher.cpp
# End Source File
# Begin Source File

SOURCE=.\Cryptography\Hasher.h
# End Source File
# End Group
# Begin Group "Logon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Logon\collect.c

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

# ADD CPP /Za
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Logon\collect.h
# End Source File
# Begin Source File

SOURCE=..\Logon\comm.c

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

# ADD CPP /Za
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Logon\comm.h
# End Source File
# Begin Source File

SOURCE=..\Logon\security.c

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

# ADD CPP /Za
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Logon\security.h
# End Source File
# Begin Source File

SOURCE=..\Logon\SSPLogon.c

!IF  "$(CFG)" == "MasterDataStructures - Win32 Release"

# ADD CPP /Za
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "MasterDataStructures - Win32 PreRelease"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Logon\SSPLogon.h
# End Source File
# Begin Source File

SOURCE=..\Logon\StdAfx.h
# End Source File
# End Group
# End Group
# End Target
# End Project
