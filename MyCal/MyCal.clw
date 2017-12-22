; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyDFTDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyCal.h"
LastPage=0

ClassCount=8
Class1=CMyCalApp
Class2=CMyCalDoc
Class3=CMyCalView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDD_WAVE_DIAL
Class5=CAboutDlg
Class6=CMyCalDialog
Resource3=IDD_CAL_DIALOG
Resource4=IDD_ABOUTBOX
Class7=CMyWaveDialog
Class8=CMyDFTDialog
Resource5=IDD_DFT_DIAL

[CLS:CMyCalApp]
Type=0
HeaderFile=MyCal.h
ImplementationFile=MyCal.cpp
Filter=N

[CLS:CMyCalDoc]
Type=0
HeaderFile=MyCalDoc.h
ImplementationFile=MyCalDoc.cpp
Filter=N

[CLS:CMyCalView]
Type=0
HeaderFile=MyCalView.h
ImplementationFile=MyCalView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDD_DFT_DIALOG




[CLS:CAboutDlg]
Type=0
HeaderFile=MyCal.cpp
ImplementationFile=MyCal.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=IDD_CAL_DIALOG
Command17=IDD_WAVE_DIALOG
Command18=IDD_DFT_DIALOG
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_CAL_DIALOG]
Type=1
Class=CMyCalDialog
ControlCount=25
Control1=IDC_EDIT_VALUE,edit,1350631552
Control2=IDC_BUTTON_1,button,1342242816
Control3=IDC_BUTTON_2,button,1342242816
Control4=IDC_BUTTON_3,button,1342242816
Control5=IDC_BUTTON_4,button,1342242816
Control6=IDC_BUTTON_5,button,1342242816
Control7=IDC_BUTTON_6,button,1342242816
Control8=IDC_BUTTON_A,button,1342242816
Control9=IDC_BUTTON_B,button,1342242816
Control10=IDC_BUTTON_C,button,1342242816
Control11=IDC_BUTTON_ADD,button,1342242816
Control12=IDC_BUTTON_SUB,button,1342242816
Control13=IDC_BUTTON_MUL,button,1342242816
Control14=IDC_BUTTON_DIV,button,1342242816
Control15=IDC_RADIO_HEX,button,1342177289
Control16=IDC_RADIO_DEC,button,1342177289
Control17=IDC_RADIO_OCT,button,1342177289
Control18=IDC_RADIO_BIN,button,1342177289
Control19=IDC_BUTTON_AC,button,1342242816
Control20=IDC_BUTTON_BK,button,1342242816
Control21=IDC_BUTTON_0,button,1342242816
Control22=IDC_BUTTON_EQUAL,button,1342242816
Control23=IDC_BUTTON_AND,button,1342242816
Control24=IDC_BUTTON_OR,button,1342242816
Control25=IDC_BUTTON_XOR,button,1342242816

[CLS:CMyCalDialog]
Type=0
HeaderFile=MyCalDialog.h
ImplementationFile=MyCalDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CMyCalDialog
VirtualFilter=dWC

[DLG:IDD_WAVE_DIAL]
Type=1
Class=CMyWaveDialog
ControlCount=16
Control1=IDC_EDIT_VALUE,edit,1350631552
Control2=IDC_BUTTON_SIN,button,1342242816
Control3=IDC_BUTTON_COS,button,1342242816
Control4=IDC_RADIO_DEG,button,1342177289
Control5=IDC_RADIO_RAD,button,1342177289
Control6=IDC_BUTTON_PLOT,button,1342242816
Control7=IDC_BUTTON_0,button,1342242816
Control8=IDC_BUTTON_1,button,1342242816
Control9=IDC_BUTTON_2,button,1342242816
Control10=IDC_BUTTON_3,button,1342242816
Control11=IDC_BUTTON_4,button,1342242816
Control12=IDC_BUTTON_5,button,1342242816
Control13=IDC_BUTTON_6,button,1342242816
Control14=IDC_BUTTON_7,button,1342242816
Control15=IDC_BUTTON_8,button,1342242816
Control16=IDC_BUTTON_9,button,1342242816

[DLG:IDD_DFT_DIAL]
Type=1
Class=CMyDFTDialog
ControlCount=3
Control1=IDC_DATA_INPUT,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_BUTTON_DFT,button,1342242816

[CLS:CMyWaveDialog]
Type=0
HeaderFile=MyWaveDialog.h
ImplementationFile=MyWaveDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_9
VirtualFilter=dWC

[CLS:CMyDFTDialog]
Type=0
HeaderFile=MyDFTDialog.h
ImplementationFile=MyDFTDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DATA_INPUT
VirtualFilter=dWC

