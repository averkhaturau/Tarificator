# Microsoft Developer Studio Project File - Name="ProceduresDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ProceduresDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProceduresDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProceduresDLL.mak" CFG="ProceduresDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProceduresDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ProceduresDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProceduresDLL - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PROCEDURESDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /w /W0 /GX /O2 /D "_USRDLL" /D "PROCEDURESDLL_EXPORTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "ProceduresDLL - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PROCEDURESDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PROCEDURESDLL_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:"ProceduresDLL.def" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ProceduresDLL - Win32 Release"
# Name "ProceduresDLL - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Group "From Master"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Master\DataStructures\ClubSettings\TimeStorage.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\Master\DataStructures\ClubSettings\TimeStorage.h
# End Source File
# End Group
# Begin Group "From Slave"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Slave\ErrorsLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\KeyboardLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\Logger.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\LoggerWithFullFileName.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\Messages.h
# End Source File
# Begin Source File

SOURCE=..\Slave\MultiThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\NamesCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryClass.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\RegistryDataWriter.cpp
# End Source File
# Begin Source File

SOURCE=..\Slave\TimeOutManager.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ProceduresDLL - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ProceduresDLL - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "ProceduresDLL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ProceduresDLL.cpp

!IF  "$(CFG)" == "ProceduresDLL - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "ProceduresDLL - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ProceduresDLL.def
# End Source File
# Begin Source File

SOURCE=.\ProceduresDLL.h
# End Source File
# End Group
# Begin Group "CharInput"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CharInput.cpp
# End Source File
# Begin Source File

SOURCE=.\CharInput.h
# End Source File
# Begin Source File

SOURCE=.\InputsCollection.h
# End Source File
# End Group
# End Target
# End Project
