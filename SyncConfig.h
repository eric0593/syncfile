#pragma once

#include "CIniFile.h"

#define SYNC_CFG_REMOTE_DIR_HISTORY_MAX     20

#define SYNC_CFG_SECTION             _T("MAIN_SETTINGS")
#define SYNC_CFG_DIFF_TOOL           _T("DIFF_TOOL")
#define SYNC_CFG_LOCAL_DIR			 _T("LOCAL_DIR")
#define SYNC_CFG_REMOTE_DIR_FORMAT           _T("REMOTE_DIR_%d")  


class CSyncConfig
{
public:
    CString                 m_Empty;
    CStringArray            m_szRemotePath;    // MBN文件所在路径    
	CString m_RemoteDir;
	CString m_DiffTool;
	CString m_LocalPath;
	CIniFile *m_pIniFile;


    CSyncConfig(void);
    ~CSyncConfig(void);
	void ResetConfig(void);
	public:CString  &GetRemotePath(void) {return (m_szRemotePath.GetSize()>0)?m_szRemotePath[0]:m_Empty;};    
    CStringArray           &GetRemotePathHist(void)                {return m_szRemotePath;};
    void                    SetRemotePath(const CString &szPath, int nIdx=0);

};
