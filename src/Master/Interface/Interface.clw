; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInterfaceApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Interface.h"
LastPage=0

ClassCount=11
Class1=CInterfaceApp
Class2=CInterfaceDoc
Class3=CBusyView
Class4=CMainFrame

ResourceCount=23
Resource1=IDD_PSWRD_DIALOG (Russian)
Resource2=IDD_TAKE_OFF_DIALOG
Resource3=IDD_CLIENT_EXCHANGE_DIALOG
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_INTERFTYPE (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Class7=CLineControl
Resource6=IDD_PSWRD_DIALOG
Resource7=IDD_NEW_INTERVAL_DIALOG
Class8=CPswrdDialog
Resource8=IDR_MAINTOOLBAR
Resource9=IDR_MAINFRAME
Resource10=IDD_CLIENT_PAYBACK_DIALOG
Class9=CTakeOfDlg
Class10=CBusyViewLX
Resource11=IDD_SHUTDOWN_DIALOG
Resource12=IDR_INTERFTYPE (Russian)
Class11=CShutdownDialog
Resource13=IDD_ABOUTBOX (Russian)
Resource14=IDD_NEW_INTERVAL_DIALOG (Russian)
Resource15=IDD_SHUTDOWN_DIALOG (Russian)
Resource16=IDD_ABOUTBOX
Resource17=IDD_CLIENT_PAYBACK_DIALOG (Russian)
Resource18=IDR_INTERFTYPE
Resource19=IDR_MAINFRAME (Russian)
Resource20=IDD_CLIENT_EXCHANGE_DIALOG (Russian)
Resource21=IDD_TAKE_OFF_DIALOG (Russian)
Resource22=IDR_MAINTOOLBAR (Russian)
Resource23=IDR_MAINFRAME (English (U.S.))

[CLS:CInterfaceApp]
Type=0
HeaderFile=Interface.h
ImplementationFile=Interface.cpp
Filter=N
LastObject=CInterfaceApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CInterfaceDoc]
Type=0
HeaderFile=InterfaceDoc.h
ImplementationFile=InterfaceDoc.cpp
Filter=N
LastObject=CInterfaceDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CBusyView]
Type=0
HeaderFile=BusyView.h
ImplementationFile=BusyView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_SHUTDOWN_HOSTS


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=ID_APP_EXIT


[CLS:CAboutDlg]
Type=0
HeaderFile=Interface.cpp
ImplementationFile=Interface.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342177294

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_INTERFTYPE]
Type=1
Class=CBusyView
Command1=ID_LOGGED_OFF
Command2=ID_INTERVALS_NEW
Command3=ID_MENU_TAKEOFF
Command4=ID_SHUTDOWN_HOSTS
Command5=ID_VIEW_SHOW_BUSY_VIEW
Command6=ID_VIEW_SHOW_BUSY_VIEWLX
Command7=ID_VIEW_SHOW_CASH_VIEW
Command8=ID_VIEW_STATUS_BAR
Command9=ID_WINDOW_CASCADE
Command10=ID_WINDOW_TILE_HORZ
Command11=ID_WINDOW_ARRANGE
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[MNU:IDR_INTERFTYPE (English (U.S.))]
Type=1
Class=CBusyView
Command1=ID_FILE_GETRANDOMINTERVALS
Command2=ID_APP_EXIT
Command3=ID_VIEW_STATUS_BAR
Command4=ID_WINDOW_NEW
Command5=ID_WINDOW_CASCADE
Command6=ID_WINDOW_TILE_HORZ
Command7=ID_WINDOW_ARRANGE
Command8=ID_INTERVALS_NEW
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_STATUS_BAR
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_INTERVALS_NEW
Command2=ID_NEXT_PANE
Command3=ID_PREV_PANE
CommandCount=3

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CLineControl]
Type=0
HeaderFile=linecontrol.h
ImplementationFile=linecontrol.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CLineControl

[DLG:IDD_NEW_INTERVAL_DIALOG]
Type=1
Class=?
ControlCount=25
Control1=IDC_STATIC,static,1342308352
Control2=IDC_MASHINE_COMBO,combobox,1344340227
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TARIF_COMBO,combobox,1344340227
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_FROM_TIME_CURRENT_RADIO,button,1342242825
Control8=IDC_FROM_TIME_AS_SOON_AS_RADIO,button,1342242825
Control9=IDC_FROM_TIME_TIME_RADIO,button,1342242825
Control10=IDC_STATIC,button,1342177287
Control11=IDC_LENGTH_MONEY_RADIO,button,1342373897
Control12=IDC_LENGTH_TIME_RADIO,button,1342242825
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_CLINETNAME_EDIT,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_ACTION_COMBO,combobox,1344339971
Control19=IDC_STATIC,static,1342308352
Control20=IDC_INTERVAL_CHOICE_COMBO,combobox,1344340227
Control21=IDC_STOP_RIGHT_NOW_CHECK,button,1342242819
Control22=IDC_STATIC,static,1342308352
Control23=IDC_TOTAL_STATIC,static,1342308352
Control24=IDC_ADDITIONAL_TOTAL_STATIC,static,1342308352
Control25=IDC_OLD_OPERATOR_STATIC,static,1342308352

[DLG:IDD_PSWRD_DIALOG]
Type=1
Class=CPswrdDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OPERATOR_COMBO,combobox,1344340227
Control6=IDC_PSWRD_EDIT,edit,1350631584
Control7=IDC_LOGON_CHECK,button,1073807363

[CLS:CPswrdDialog]
Type=0
HeaderFile=PswrdDialog.h
ImplementationFile=PswrdDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LOGON_CHECK
VirtualFilter=dWC

[DLG:IDD_CLIENT_PAYBACK_DIALOG]
Type=1
Class=?
ControlCount=11
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OLD_PRICE_STATIC,static,1342308354
Control6=IDC_NEW_PRICE_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308352
Control8=IDC_SUM_STATIC,static,1342308354
Control9=IDC_CLIENT_MONEY_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CHANGE_STATIC,static,1342308354

[DLG:IDD_CLIENT_EXCHANGE_DIALOG]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1476460544
Control3=IDC_OLD_CLIENT_STATIC,static,1342308352
Control4=IDC_NEW_CLIENT_STATIC,static,1342308352

[DLG:IDD_TAKE_OFF_DIALOG]
Type=1
Class=CTakeOfDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC_CL1,static,1342308352
Control6=IDC_STATIC_CL2,static,1342308352

[CLS:CTakeOfDlg]
Type=0
HeaderFile=TakeOfDlg.h
ImplementationFile=TakeOfDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTakeOfDlg
VirtualFilter=dWC

[CLS:CBusyViewLX]
Type=0
HeaderFile=busyviewlx.h
ImplementationFile=busyviewlx.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CBusyViewLX

[TB:IDR_MAINTOOLBAR]
Type=1
Class=?
Command1=ID_INTERVALS_NEW
Command2=ID_INTERVALS_NEW
Command3=ID_SHUTDOWN_HOSTS
Command4=ID_SHUTDOWN_HOSTS
Command5=ID_LOGGED_OFF
CommandCount=5

[DLG:IDD_SHUTDOWN_DIALOG]
Type=1
Class=CShutdownDialog
ControlCount=4
Control1=ID_BUTTON_SHUTDOWN,button,1342242816
Control2=IDCANCEL,button,1342242817
Control3=IDC_STATIC_MASHINES,static,1342308352
Control4=IDC_BUTTON_REBOOT,button,1342242816

[CLS:CShutdownDialog]
Type=0
HeaderFile=ShutdownDialog.h
ImplementationFile=ShutdownDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_REBOOT
VirtualFilter=dWC

[DLG:IDD_PSWRD_DIALOG (Russian)]
Type=1
Class=CPswrdDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OPERATOR_COMBO,combobox,1344340227
Control6=IDC_PSWRD_EDIT,edit,1350631584
Control7=IDC_LOGON_CHECK,button,1073807363

[DLG:IDD_NEW_INTERVAL_DIALOG (Russian)]
Type=1
Class=?
ControlCount=25
Control1=IDC_STATIC,static,1342308352
Control2=IDC_MASHINE_COMBO,combobox,1344340227
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TARIF_COMBO,combobox,1344340227
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_FROM_TIME_CURRENT_RADIO,button,1342242825
Control8=IDC_FROM_TIME_AS_SOON_AS_RADIO,button,1342242825
Control9=IDC_FROM_TIME_TIME_RADIO,button,1342242825
Control10=IDC_STATIC,button,1342177287
Control11=IDC_LENGTH_MONEY_RADIO,button,1342373897
Control12=IDC_LENGTH_TIME_RADIO,button,1342242825
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_CLINETNAME_EDIT,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_ACTION_COMBO,combobox,1344339971
Control19=IDC_STATIC,static,1342308352
Control20=IDC_INTERVAL_CHOICE_COMBO,combobox,1344340227
Control21=IDC_STOP_RIGHT_NOW_CHECK,button,1342242819
Control22=IDC_STATIC,static,1342308352
Control23=IDC_TOTAL_STATIC,static,1342308352
Control24=IDC_ADDITIONAL_TOTAL_STATIC,static,1342308352
Control25=IDC_OLD_OPERATOR_STATIC,static,1342308352

[DLG:IDD_CLIENT_PAYBACK_DIALOG (Russian)]
Type=1
Class=?
ControlCount=11
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OLD_PRICE_STATIC,static,1342308354
Control6=IDC_NEW_PRICE_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308352
Control8=IDC_SUM_STATIC,static,1342308354
Control9=IDC_CLIENT_MONEY_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CHANGE_STATIC,static,1342308354

[DLG:IDD_ABOUTBOX (Russian)]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342177294

[DLG:IDD_CLIENT_EXCHANGE_DIALOG (Russian)]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1476460544
Control3=IDC_OLD_CLIENT_STATIC,static,1342308352
Control4=IDC_NEW_CLIENT_STATIC,static,1342308352

[DLG:IDD_TAKE_OFF_DIALOG (Russian)]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC_CL1,static,1342308352
Control6=IDC_STATIC_CL2,static,1342308352

[DLG:IDD_SHUTDOWN_DIALOG (Russian)]
Type=1
Class=?
ControlCount=4
Control1=ID_BUTTON_SHUTDOWN,button,1342242816
Control2=IDCANCEL,button,1342242817
Control3=IDC_STATIC_MASHINES,static,1342308352
Control4=IDC_BUTTON_REBOOT,button,1342242816

[MNU:IDR_MAINFRAME (Russian)]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_INTERFTYPE (Russian)]
Type=1
Class=CBusyView
Command1=ID_LOGGED_OFF
Command2=ID_INTERVALS_NEW
Command3=ID_MENU_TAKEOFF
Command4=ID_SHUTDOWN_HOSTS
Command5=ID_VIEW_SHOW_BUSY_VIEW
Command6=ID_VIEW_SHOW_BUSY_VIEWLX
Command7=ID_VIEW_SHOW_CASH_VIEW
Command8=ID_VIEW_STATUS_BAR
Command9=ID_WINDOW_CASCADE
Command10=ID_WINDOW_TILE_HORZ
Command11=ID_WINDOW_ARRANGE
Command12=ID_APP_ABOUT
CommandCount=12

[TB:IDR_MAINTOOLBAR (Russian)]
Type=1
Class=?
Command1=ID_INTERVALS_NEW
Command2=ID_INTERVALS_NEW
Command3=ID_SHUTDOWN_HOSTS
Command4=ID_SHUTDOWN_HOSTS
Command5=ID_LOGGED_OFF
CommandCount=5

