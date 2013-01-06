// SYNC_FILE.h : main header file for the SYNC_FILE application
//

#if !defined(AFX_SYNC_FILE_H__6CDF1533_8092_4C40_AF14_0B05B7FF502B__INCLUDED_)
#define AFX_SYNC_FILE_H__6CDF1533_8092_4C40_AF14_0B05B7FF502B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSYNC_FILEApp:
// See SYNC_FILE.cpp for the implementation of this class
//

class CSYNC_FILEApp : public CWinApp
{
public:
	CSYNC_FILEApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSYNC_FILEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSYNC_FILEApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNC_FILE_H__6CDF1533_8092_4C40_AF14_0B05B7FF502B__INCLUDED_)
