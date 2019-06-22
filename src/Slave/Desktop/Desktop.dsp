# Microsoft Developer Studio Project File - Name="Desktop" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Desktop - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Desktop.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Desktop.mak" CFG="Desktop - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Desktop - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Desktop - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Desktop - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib LIBCMT.LIB Wtsapi32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "Desktop - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib LIBCMT.LIB Wtsapi32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "Desktop - Win32 Release"
# Name "Desktop - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Cursor_big.bmp
# End Source File
# Begin Source File

SOURCE=.\Cursor_small.bmp
# End Source File
# Begin Source File

SOURCE=.\Orion_big.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BigPictureDescription.h
# End Source File
# Begin Source File

SOURCE=.\ClubDefiner.h
# End Source File
# Begin Source File

SOURCE=.\DesktopMain.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SmallPictureDescription.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "DesktopEmulator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DesktopEmulator.cpp
# End Source File
# Begin Source File

SOURCE=.\DesktopEmulator.h
# End Source File
# Begin Source File

SOURCE=.\IconsWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\IconsWindow.h
# End Source File
# Begin Source File

SOURCE=.\RemainingTimeSlaveDescription.h
# End Source File
# End Group
# Begin Group "IconButton"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IconButton.cpp
# End Source File
# Begin Source File

SOURCE=.\IconButton.h
# End Source File
# Begin Source File

SOURCE=.\IconButtonsCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\IconButtonsCollection.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutInfo.h
# End Source File
# End Group
# Begin Group "StatusBar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AboutButton.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutButton.h
# End Source File
# Begin Source File

SOURCE=.\StatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusBar.h
# End Source File
# End Group
# Begin Group "AboutDialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AboutDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutDialog.h
# End Source File
# End Group
# Begin Group "ApplicationWaiter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ApplicationWaiter.cpp
# End Source File
# Begin Source File

SOURCE=.\ApplicationWaiter.h
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
# Begin Group "From Slave"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Slave\ApplicationInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\ApplicationInfosCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\ErrorsLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\ErrorsLogger.h
# End Source File
# Begin Source File

SOURCE=..\Slave\InvertedTimeOutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\InvertedTimeOutManager.h
# End Source File
# Begin Source File

SOURCE=..\Slave\KeyboardLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\KeyboardLogger.h
# End Source File
# Begin Source File

SOURCE=..\Slave\Logger.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\Logger.h
# End Source File
# Begin Source File

SOURCE=..\Slave\LoggerWithFullFileName.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\LoggerWithFullFileName.h
# End Source File
# Begin Source File

SOURCE=..\Slave\MultiThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\MultiThreadManager.h
# End Source File
# Begin Source File

SOURCE=..\Slave\NamesCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\NamesCollection.h
# End Source File
# Begin Source File

SOURCE=..\Slave\NewUserDefiner.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\NewUserDefiner.h
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryClass.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryClass.h
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryDataReader.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryDataReader.h
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryDataWriter.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryDataWriter.h
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryFileManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryFileManager.h
# End Source File
# Begin Source File

SOURCE=..\Slave\SlaveRegistryDataReader.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\SlaveRegistryDataReader.h
# End Source File
# Begin Source File

SOURCE=..\Slave\TimeOutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\TimeOutManager.h
# End Source File
# End Group
# Begin Group "TaskbarEmulator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TaskbarEmulator.cpp
# End Source File
# Begin Source File

SOURCE=.\TaskbarEmulator.h
# End Source File
# Begin Source File

SOURCE=.\TaskButton.cpp
# End Source File
# Begin Source File

SOURCE=.\TaskButton.h
# End Source File
# Begin Source File

SOURCE=.\TaskButtonsCollection.h
# End Source File
# End Group
# End Target
# End Project
