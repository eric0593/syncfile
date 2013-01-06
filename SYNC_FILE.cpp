// SYNC_FILE.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SYNC_FILE.h"
#include "SYNC_FILEDlg.h"

#include "CmdLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSYNC_FILEApp

BEGIN_MESSAGE_MAP(CSYNC_FILEApp, CWinApp)
	//{{AFX_MSG_MAP(CSYNC_FILEApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSYNC_FILEApp construction

CSYNC_FILEApp::CSYNC_FILEApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSYNC_FILEApp object

CSYNC_FILEApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSYNC_FILEApp initialization

BOOL CSYNC_FILEApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSYNC_FILEDlg dlg;
	CString Argv=m_lpCmdLine;
//	int CmdStart;

	//dlg.argvFile=m_lpCmdLine[0];
	//dlg.argvCmd=m_lpCmdLine[1];
//	CmdStart = Argv.Find(_T(' '),0);
//	dlg.m_argvFile = Argv.Mid(3,Argv.GetLength());
//	dlg.m_argvCmd = Argv.Mid(0,2);
dlg.m_argvFile=Argv;
	int nResponse = dlg.DoModal();	
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
