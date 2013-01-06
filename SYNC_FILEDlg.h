// SYNC_FILEDlg.h : header file
//

#if !defined(AFX_SYNC_FILEDLG_H__0CD0B03D_1AEB_4199_921A_F3E931E70F46__INCLUDED_)
#define AFX_SYNC_FILEDLG_H__0CD0B03D_1AEB_4199_921A_F3E931E70F46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SyncConfig.h"
/////////////////////////////////////////////////////////////////////////////
// CSYNC_FILEDlg dialog

#define SYNC_ERROR_LOCAL_DIR_WRONG   0x01

class CSYNC_FILEDlg : public CDialog
{
// Construction
public:
	CSYNC_FILEDlg(CWnd* pParent = NULL);	// standard constructor
	CSyncConfig *m_SyncConfig;
	CString m_argvFile;
	CString m_argvCmd;
	CString m_RelativeFileName;
	CString m_RemoteFileName;
	CString m_RemoteDir;
	int m_Error;
// Dialog Data
	//{{AFX_DATA(CSYNC_FILEDlg)
	enum { IDD = IDD_SYNC_FILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSYNC_FILEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSYNC_FILEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowser();
	afx_msg void OnDiffToolChoose();
	afx_msg void OnDiff();
	virtual void OnCancel();
	afx_msg void OnChangeFolderName();
	afx_msg void OnChangeDiffToolName();
	afx_msg void OnEditchangeBrowserFiles();
	afx_msg void OnEditchangeDestDir();
	afx_msg void OverWrite();
	afx_msg void OnBrowserRemoteDir();
	afx_msg void OnBrowserLocalDir();
	afx_msg void OnOverwrite();
	afx_msg void OnExploterRemoteRoot();
	afx_msg void OnExploterLocalRoot();
	afx_msg void OnExploterRemoteFile();
	afx_msg void OnExploterLocalFile();
	afx_msg void OnCopyToClip();
	afx_msg void OnSelendokComboDestDir();
	afx_msg void OnSelchangeComboDestDir();
	afx_msg void OnCloseupComboDestDir();
	afx_msg void OnEditupdateComboDestDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNC_FILEDLG_H__0CD0B03D_1AEB_4199_921A_F3E931E70F46__INCLUDED_)
