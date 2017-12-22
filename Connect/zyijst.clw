; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=AddFriend
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "zyijst.h"

ClassCount=4
Class1=CZyijstApp
Class2=CZyijstDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ZYIJST_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG1
Class4=AddFriend
Resource4=IDD_ABOUTBOX
Resource5=IDR_MENU1

[CLS:CZyijstApp]
Type=0
HeaderFile=zyijst.h
ImplementationFile=zyijst.cpp
Filter=N

[CLS:CZyijstDlg]
Type=0
HeaderFile=zyijstDlg.h
ImplementationFile=zyijstDlg.cpp
Filter=D
LastObject=IDCANCEL
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=zyijstDlg.h
ImplementationFile=zyijstDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ZYIJST_DIALOG]
Type=1
Class=CZyijstDlg
ControlCount=7
Control1=IDC_STATIC,button,1342178055
Control2=IDC_FriendLIST,listbox,1352728835
Control3=IDC_STATIC,button,1342177287
Control4=IDC_StartBTN,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_AddBTN,button,1342242816
Control7=IDC_HIDEBTN,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=AddFriend
ControlCount=4
Control1=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDCANCEL,button,1342242816
Control4=IDOK,button,1342242816

[CLS:AddFriend]
Type=0
HeaderFile=AddFriend.h
ImplementationFile=AddFriend.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_SUBMENU1
Command2=ID_SUBMENU2
CommandCount=2

