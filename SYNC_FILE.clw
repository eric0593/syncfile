; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSYNC_FILEDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SYNC_FILE.h"

ClassCount=3
Class1=CSYNC_FILEApp
Class2=CSYNC_FILEDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SYNC_FILE_DIALOG

[CLS:CSYNC_FILEApp]
Type=0
HeaderFile=SYNC_FILE.h
ImplementationFile=SYNC_FILE.cpp
Filter=N

[CLS:CSYNC_FILEDlg]
Type=0
HeaderFile=SYNC_FILEDlg.h
ImplementationFile=SYNC_FILEDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_COMBO_DEST_DIR

[CLS:CAboutDlg]
Type=0
HeaderFile=SYNC_FILEDlg.h
ImplementationFile=SYNC_FILEDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SYNC_FILE_DIALOG]
Type=1
Class=CSYNC_FILEDlg
ControlCount=17
Control1=IDDIFF,button,1342242817
Control2=ID_EXPLOTER_REMOTE_FILE,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BROWSER_REMOTE_DIR,button,1342242816
Control5=RemoteFile,static,1342308352
Control6=IDC_DIFF_LOCAL_DIR,edit,1350631552
Control7=IDC_DIFF_TOOL_CHOOSE,button,1342242816
Control8=IDC_COMBO_DEST_DIR,combobox,1344340226
Control9=IDOVERWRITE,button,1342242817
Control10=IDC_DIFF_TOOL_NAME,edit,1350631552
Control11=IDC_BROWSER_LOCAL_DIR,button,1342242816
Control12=ID_EXPLOTER_LOCAL_FILE,button,1342242816
Control13=ID_EXPLOTER_REMOTE_ROOT,button,1342242816
Control14=ID_EXPLOTER_LOCAL_ROOT,button,1342242816
Control15=IDC_EDIT_LOCAL,edit,1484849280
Control16=IDC_EDIT_REMOTE,edit,1484849280
Control17=IDC_BUTTON1,button,1342242816

