# Microsoft Developer Studio Project File - Name="Slave" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Slave - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Slave.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Slave.mak" CFG="Slave - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Slave - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Slave - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Slave - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 shlwapi.lib WS2_32.LIB ADSIid.Lib Winmm.lib Wtsapi32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Slave - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib WS2_32.LIB ADSIid.Lib Winmm.lib Wtsapi32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Slave - Win32 Release"
# Name "Slave - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Orion_big.bmp
# End Source File
# Begin Source File

SOURCE=.\Orion_small.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# Begin Source File

SOURCE=.\Traffic_small.bmp
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Constants.h
# End Source File
# Begin Source File

SOURCE=.\Exceptions.h
# End Source File
# Begin Source File

SOURCE=.\GlobalVariables.h
# End Source File
# Begin Source File

SOURCE=.\MasterMessages.h
# End Source File
# Begin Source File

SOURCE=.\Messages.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SlaveMain.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TimerHandler.h
# End Source File
# Begin Source File

SOURCE=.\WriteTextMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteTextMessage.h
# End Source File
# End Group
# Begin Group "Logger"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ErrorsLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorsLogger.h
# End Source File
# Begin Source File

SOURCE=.\KeyboardLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyboardLogger.h
# End Source File
# Begin Source File

SOURCE=.\Logger.cpp
# End Source File
# Begin Source File

SOURCE=.\Logger.h
# End Source File
# Begin Source File

SOURCE=.\LoggerWithFullFileName.cpp

!IF  "$(CFG)" == "Slave - Win32 Release"

!ELSEIF  "$(CFG)" == "Slave - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LoggerWithFullFileName.h
# End Source File
# End Group
# Begin Group "SlaveDataReader"

# PROP Default_Filter ""
# Begin Group "Abstract"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LoggerParametersReader.h
# End Source File
# Begin Source File

SOURCE=.\NetworkParametersDataReader.h
# End Source File
# Begin Source File

SOURCE=.\SlaveDataReader.h
# End Source File
# End Group
# Begin Group "Shared"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataReader.h
# End Source File
# Begin Source File

SOURCE=.\RegistryClass.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryClass.h
# End Source File
# Begin Source File

SOURCE=.\RegistryDataReader.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryDataReader.h
# End Source File
# Begin Source File

SOURCE=.\RegistryDataWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryDataWriter.h
# End Source File
# Begin Source File

SOURCE=.\RegistryFileManager.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryFileManager.h
# End Source File
# End Group
# Begin Group "Concrete"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SlaveRegistryDataReader.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveRegistryDataReader.h
# End Source File
# End Group
# End Group
# Begin Group "SlaveManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SlaveManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveManager.h
# End Source File
# End Group
# Begin Group "NamesCollection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NamesCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\NamesCollection.h
# End Source File
# End Group
# Begin Group "Communicator"

# PROP Default_Filter ""
# Begin Group "Abstract_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Listener.cpp
# End Source File
# Begin Source File

SOURCE=.\Listener.h
# End Source File
# Begin Source File

SOURCE=.\Receiver.cpp
# End Source File
# Begin Source File

SOURCE=.\Receiver.h
# End Source File
# Begin Source File

SOURCE=.\Sender.cpp
# End Source File
# Begin Source File

SOURCE=.\Sender.h
# End Source File
# Begin Source File

SOURCE=.\SlaveCommunicator.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveCommunicator.h
# End Source File
# End Group
# Begin Group "Shared_"

# PROP Default_Filter ""
# Begin Group "Commander"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Commander.cpp
# End Source File
# Begin Source File

SOURCE=.\Commander.h
# End Source File
# Begin Source File

SOURCE=.\Incoming.cpp
# End Source File
# Begin Source File

SOURCE=.\Incoming.h
# End Source File
# Begin Source File

SOURCE=.\Outcoming.cpp
# End Source File
# Begin Source File

SOURCE=.\Outcoming.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AsyncExchanger.cpp
# End Source File
# Begin Source File

SOURCE=.\AsyncExchanger.h
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Class.cpp
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Class.h
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Listener.cpp
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Listener.h
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Receiver.cpp
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Receiver.h
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Sender.cpp
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_Sender.h
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_SocketHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\TCP_IP_SocketHolder.h
# End Source File
# End Group
# Begin Group "Concrete_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SlaveTPC_IP_Communicator.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveTPC_IP_Communicator.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AdditionalRecievedData.cpp
# End Source File
# Begin Source File

SOURCE=.\AdditionalRecievedData.h
# End Source File
# Begin Source File

SOURCE=.\AdditionalRecievedDatumCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\AdditionalRecievedDatumCollection.h
# End Source File
# Begin Source File

SOURCE=.\NetworkConstants.h
# End Source File
# Begin Source File

SOURCE=.\ReceiverParamsCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\ReceiverParamsCollection.h
# End Source File
# End Group
# Begin Group "MultiThreadManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ManagersCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\ManagersCollection.h
# End Source File
# Begin Source File

SOURCE=.\MultiThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiThreadManager.h
# End Source File
# Begin Source File

SOURCE=.\ReceiveManagersCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\ReceiveManagersCollection.h
# End Source File
# Begin Source File

SOURCE=.\ReceiveMulthiThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ReceiveMulthiThreadManager.h
# End Source File
# End Group
# Begin Group "From Master"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Master\DataStructures\ActiveContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\Master\DataStructures\ActiveContainerResizable.h
# End Source File
# Begin Source File

SOURCE=..\..\Master\DataStructures\ClubSettings\IntervalAddition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Master\DataStructures\ClubSettings\IntervalAddition.h
# End Source File
# Begin Source File

SOURCE=..\..\Master\DataStructures\ClubSettings\RemainingTimeDescription.h
# End Source File
# Begin Source File

SOURCE=..\..\Master\DataStructures\ClubSettings\TimeStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Master\DataStructures\ClubSettings\TimeStorage.h
# End Source File
# End Group
# Begin Group "TimeOutManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InvertedTimeOutManager.cpp
# End Source File
# Begin Source File

SOURCE=.\InvertedTimeOutManager.h
# End Source File
# Begin Source File

SOURCE=.\TimeOutManager.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeOutManager.h
# End Source File
# End Group
# Begin Group "NewUserDefiner"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NewUserDefiner.cpp
# End Source File
# Begin Source File

SOURCE=.\NewUserDefiner.h
# End Source File
# Begin Source File

SOURCE=.\WTSSessionsIdsCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\WTSSessionsIdsCollection.h
# End Source File
# End Group
# Begin Group "SlaveService"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NTService\NTServApp.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NTService\NTService.cpp
# End Source File
# Begin Source File

SOURCE=.\NTService\NTService.h
# End Source File
# Begin Source File

SOURCE=.\NTService\ntservmsg.h
# End Source File
# Begin Source File

SOURCE=.\NTService\ntservmsg.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SlaveService.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveService.h
# End Source File
# End Group
# Begin Group "SlaveSoundManager"

# PROP Default_Filter ""
# Begin Group "Wave"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Wave\INCLUDE\ANIMATE.H
# End Source File
# Begin Source File

SOURCE=.\Wave\SRC\WAVE.CPP
# End Source File
# Begin Source File

SOURCE=.\Wave\SRC\WAVEIDEV.CPP
# End Source File
# Begin Source File

SOURCE=.\Wave\SRC\WAVEODEV.CPP
# End Source File
# End Group
# Begin Source File

SOURCE=.\AsyncSoundPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\AsyncSoundPlayer.h
# End Source File
# Begin Source File

SOURCE=.\SlaveSoundManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveSoundManager.h
# End Source File
# Begin Source File

SOURCE=.\SoundEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundEntry.h
# End Source File
# Begin Source File

SOURCE=.\SoundsList.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundsList.h
# End Source File
# End Group
# Begin Group "From Desktop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Desktop\ApplicationWaiter.cpp
# End Source File
# Begin Source File

SOURCE=..\Desktop\ApplicationWaiter.h
# End Source File
# Begin Source File

SOURCE=..\Desktop\RemainingTimeSlaveDescription.h
# End Source File
# End Group
# Begin Group "ApplicationInfosCollection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ApplicationInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ApplicationInfo.h
# End Source File
# Begin Source File

SOURCE=.\ApplicationInfosCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\ApplicationInfosCollection.h
# End Source File
# End Group
# Begin Group "SessionTimeOutCollection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SessionTimeOutCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\SessionTimeOutCollection.h
# End Source File
# Begin Source File

SOURCE=.\SessionTimeOutManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SessionTimeOutManager.h
# End Source File
# End Group
# End Target
# End Project
