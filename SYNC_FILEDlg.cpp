// SYNC_FILEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SYNC_FILE.h"
#include "SYNC_FILEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "windows.h"
#include "winbase.h"
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSYNC_FILEDlg dialog

CSYNC_FILEDlg::CSYNC_FILEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSYNC_FILEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSYNC_FILEDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSYNC_FILEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSYNC_FILEDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSYNC_FILEDlg, CDialog)
	//{{AFX_MSG_MAP(CSYNC_FILEDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DIFF_TOOL_CHOOSE, OnDiffToolChoose)
	ON_BN_CLICKED(IDDIFF, OnDiff)
	ON_CBN_EDITCHANGE(IDC_COMBO_DEST_DIR, OnEditchangeDestDir)
	ON_BN_CLICKED(IDC_BROWSER_REMOTE_DIR, OnBrowserRemoteDir)
	ON_BN_CLICKED(IDC_BROWSER_LOCAL_DIR, OnBrowserLocalDir)
	ON_BN_CLICKED(IDOVERWRITE, OnOverwrite)
	ON_BN_CLICKED(ID_EXPLOTER_REMOTE_ROOT, OnExploterRemoteRoot)
	ON_BN_CLICKED(ID_EXPLOTER_LOCAL_ROOT, OnExploterLocalRoot)
	ON_BN_CLICKED(ID_EXPLOTER_REMOTE_FILE, OnExploterRemoteFile)
	ON_BN_CLICKED(ID_EXPLOTER_LOCAL_FILE, OnExploterLocalFile)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyToClip)
	ON_CBN_SELENDOK(IDC_COMBO_DEST_DIR, OnSelendokComboDestDir)
	ON_CBN_SELCHANGE(IDC_COMBO_DEST_DIR, OnSelchangeComboDestDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSYNC_FILEDlg message handlers

BOOL CSYNC_FILEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	 
	m_SyncConfig=new CSyncConfig();
	if (!m_SyncConfig->m_DiffTool.IsEmpty())
		GetDlgItem(IDC_DIFF_TOOL_NAME)->SetWindowText(m_SyncConfig->m_DiffTool);


	if (!m_SyncConfig->m_LocalPath.IsEmpty())
		GetDlgItem(IDC_DIFF_LOCAL_DIR)->SetWindowText(m_SyncConfig->m_LocalPath);

	for(int i=0;i<m_SyncConfig->m_szRemotePath.GetSize();i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_DEST_DIR))->InsertString(i,m_SyncConfig->m_szRemotePath[i]);
	}
	
	((CComboBox*)GetDlgItem(IDC_COMBO_DEST_DIR))->SetCurSel(0);
	m_RemoteDir=m_SyncConfig->GetRemotePath();

	GetDlgItem(IDC_EDIT_LOCAL)->SetWindowText(m_argvFile);
	//MessageBox(m_argvFile);
	m_RelativeFileName=m_argvFile;
	
	if(m_RelativeFileName.Replace(m_SyncConfig->m_LocalPath,NULL)==0)
	{
		m_Error=SYNC_ERROR_LOCAL_DIR_WRONG;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(_T("!!!! Please Set Local Path"));
	}
	else
	{
		m_RemoteFileName=m_RemoteDir+m_RelativeFileName;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(m_RemoteFileName);
	}

//	if(m_argvCmd=="sa")
//	{
//		SendDlgItemMessage(IDDIFF,0,0,0);
//	}
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSYNC_FILEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSYNC_FILEDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSYNC_FILEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CSYNC_FILEDlg::OnDiffToolChoose() 
{
	// TODO: Add your control notification handler code here

	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if(dlg.DoModal()==IDOK)
	{
		m_SyncConfig->m_DiffTool=dlg.GetPathName();
		GetDlgItem(IDC_DIFF_TOOL_NAME)->SetWindowText(m_SyncConfig->m_DiffTool);
	}

}

void CSYNC_FILEDlg::OnDiff() 
{
	// TODO: Add your control notification handler code here
	CString DiffCmd='"'+m_SyncConfig->m_DiffTool+'"'+' '+m_argvFile+' '+m_RemoteFileName;	
	//system(DiffCmd);
	WinExec(DiffCmd, SW_SHOW);
	delete m_SyncConfig;
	m_SyncConfig=NULL;
	CDialog::OnCancel();
}

void CSYNC_FILEDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	delete m_SyncConfig;
	m_SyncConfig=NULL;
	CDialog::OnCancel();
}





void CSYNC_FILEDlg::OnEditchangeDestDir() 
{
	// TODO: Add your control notification handler code here
	m_RelativeFileName=m_argvFile;
	
	if(m_RelativeFileName.Replace(m_SyncConfig->m_LocalPath,NULL)==0)
	{
		m_Error=SYNC_ERROR_LOCAL_DIR_WRONG;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(_T("!!!! Please Set Local Path"));
	}
	else
	{	
		GetDlgItem(IDC_EDIT_REMOTE)->GetWindowText(m_RemoteDir);
		if (!m_RemoteDir.IsEmpty())
			m_RemoteFileName=m_RemoteDir+m_RelativeFileName;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(m_RemoteFileName);
		RedrawWindow(); 
	}
}


void CSYNC_FILEDlg::OnBrowserRemoteDir() 
{
	// TODO: Add your control notification handler code here

	CString sFolderPath;
	char Buffer[MAX_PATH];
	BROWSEINFO bi;
//初始化入口参数bi开始
	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;//初始化制定的root目录很不容易，
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = "修改接收路径";
//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	bi.ulFlags = BIF_EDITBOX;//包括文件

	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME;
//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		m_SyncConfig->SetRemotePath(Buffer,0);
	}
	   	   
	//释放内存
	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) return;
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
	m_RemoteDir=m_SyncConfig->GetRemotePath();
	((CComboBox*)GetDlgItem(IDC_COMBO_DEST_DIR))->InsertString(0,m_SyncConfig->GetRemotePath());
	((CComboBox*)GetDlgItem(IDC_COMBO_DEST_DIR))->SetCurSel(0);

	m_RelativeFileName=m_argvFile;
	
	if(m_RelativeFileName.Replace(m_SyncConfig->m_LocalPath,NULL)==0)
	{
		m_Error=SYNC_ERROR_LOCAL_DIR_WRONG;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(_T("!!!! Please Set Local Path"));
	}
	else
	{
		m_RemoteFileName=m_RemoteDir+m_RelativeFileName;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(m_RemoteFileName);
		RedrawWindow(); 
	}
}

void CSYNC_FILEDlg::OnBrowserLocalDir() 
{
	// TODO: Add your control notification handler code here
	CString sFolderPath;
	char Buffer[MAX_PATH];
	BROWSEINFO bi;
//初始化入口参数bi开始
	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;//初始化制定的root目录很不容易，
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = "修改接收路径";
//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	bi.ulFlags = BIF_EDITBOX;//包括文件

	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME;
//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);	
		m_SyncConfig->m_LocalPath=Buffer;
		if(m_SyncConfig->m_LocalPath.GetAt(m_SyncConfig->m_LocalPath.GetLength()-1) != '\\')
		{
		   m_SyncConfig->m_LocalPath+="\\";
		}
	}
	   	   
	//释放内存
	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) return;
	lpMalloc->Free(pIDList);
	lpMalloc->Release();

	m_RelativeFileName=m_argvFile;
	if(!m_RelativeFileName.IsEmpty()&&m_RelativeFileName.Replace(m_SyncConfig->m_LocalPath,NULL)==0)
	{
		m_Error=SYNC_ERROR_LOCAL_DIR_WRONG;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(_T("!!!! Please Set Local Path"));
	}
	else
	{
		m_RemoteFileName=m_RemoteDir+m_RelativeFileName;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(m_RemoteFileName);
	}
	GetDlgItem(IDC_DIFF_LOCAL_DIR)->SetWindowText(m_SyncConfig->m_LocalPath);	
}

void CSYNC_FILEDlg::OnOverwrite() 
{	
	DWORD ret;
	CString CopyCmd="copy "+m_argvFile+' '+m_RemoteFileName;
	// TODO: Add your control notification handler code here
	ret=GetFileAttributes(m_RemoteFileName);
	if(0/*ret==0xFFFFFFFF*/)
	{
		MessageBox("File dont exist");
		delete m_SyncConfig;
		m_SyncConfig=NULL;
		CDialog::OnCancel();
	}
	//WinExec(CopyCmd, SW_SHOW);
	system(CopyCmd);
	delete m_SyncConfig;
	m_SyncConfig=NULL;
	CDialog::OnCancel();
}

void CSYNC_FILEDlg::OnExploterRemoteRoot() 
{
	CString ExplorerRemoteRootCmd="explorer "+m_RemoteDir;
	//TODO: Add your control notification handler code here
	WinExec(ExplorerRemoteRootCmd, SW_SHOW);

	//system(ExplorerRemoteRootCmd); 
	delete m_SyncConfig;
	m_SyncConfig=NULL;
	CDialog::OnCancel();
}

void CSYNC_FILEDlg::OnExploterLocalRoot() 
{
	CString ExplorerLocalRootCmd="explorer "+m_SyncConfig->m_LocalPath;
	// TODO: Add your control notification handler code here
	//system(ExplorerLocalRootCmd);
		WinExec(ExplorerLocalRootCmd, SW_SHOW);

		delete m_SyncConfig;
	m_SyncConfig=NULL;
	CDialog::OnCancel();
	
}

void CSYNC_FILEDlg::OnExploterRemoteFile() 
{
	CString ExplorerRemoteRootCmd="explorer /e,/select,"+m_RemoteFileName;
	// TODO: Add your control notification handler code here
	//system(ExplorerRemoteRootCmd);
	WinExec(ExplorerRemoteRootCmd, SW_SHOW);

		delete m_SyncConfig;
	m_SyncConfig=NULL;
	CDialog::OnCancel();
}

void CSYNC_FILEDlg::OnExploterLocalFile() 
{
	CString ExplorerLocalRootCmd="explorer /e,/select,"+m_argvFile;
	// TODO: Add your control notification handler code here
	//system(ExplorerLocalRootCmd);
		WinExec(ExplorerLocalRootCmd, SW_SHOW);

		delete m_SyncConfig;
	m_SyncConfig=NULL;
	CDialog::OnCancel();
	
}

void CSYNC_FILEDlg::OnCopyToClip() 
{
	// TODO: Add your control notification handler code here
        HGLOBAL hClip; 
        //定义一个HGLOBAL句柄变量用来指向分配的内存块
        if (OpenClipboard())
        {
            EmptyClipboard();                            //将剪贴板内容清空
            hClip=GlobalAlloc(GMEM_MOVEABLE,m_RelativeFileName.GetLength()+1); 
            //在堆上分配可移动的内存块，程序返回一个内存句柄
            char * buff;                                 //定义指向字符型的指针变量
            buff=(char*)GlobalLock(hClip);
            //对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加1
            strcpy(buff,m_RelativeFileName);
            //将用户输入的数据复制到指针变量中，实际上就是复制到分配的内存块中
            GlobalUnlock(hClip);
            //数据写入完毕，进行解锁操作，并将引用计数器数字减1
            SetClipboardData(CF_TEXT,hClip);
            //将存放有数据的内存块放入剪贴板的资源管理中
            CloseClipboard();
            //关闭剪贴板，释放剪贴板资源的占用权
            MessageBox("已将数据存入剪贴板");
        }
		delete m_SyncConfig;
		m_SyncConfig=NULL;
		CDialog::OnCancel();
}



void CSYNC_FILEDlg::OnSelendokComboDestDir() 
{
	m_RelativeFileName=m_argvFile;
}

void CSYNC_FILEDlg::OnSelchangeComboDestDir() 
{
	int CurSel;
	// TODO: Add your control notification handler code here

	m_RelativeFileName=m_argvFile;
	if(!m_RelativeFileName.IsEmpty()&&m_RelativeFileName.Replace(m_SyncConfig->m_LocalPath,NULL)==0)
	{
		m_Error=SYNC_ERROR_LOCAL_DIR_WRONG;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(_T("!!!! Please Set Local Path"));
	}
	else
	{
		CurSel=((CComboBox*)GetDlgItem(IDC_COMBO_DEST_DIR))->GetCurSel();
		m_RemoteDir= m_SyncConfig->m_szRemotePath[CurSel];
		m_SyncConfig->SetRemotePath(m_RemoteDir,0);
		m_RemoteFileName=m_RemoteDir+m_RelativeFileName;
		GetDlgItem(IDC_EDIT_REMOTE)->SetWindowText(m_RemoteFileName);
		RedrawWindow(); 
	}
	
}





