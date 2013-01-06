#include "StdAfx.h"
#include "SyncConfig.h"


CSyncConfig::CSyncConfig(void)
{
	CString DefDiffTool=_T("C:\\Program Files\\Beyond Compare\\BCompare.exe");
	CString szTemp;
	int i=0,j=0;
	CString szPath;

	m_pIniFile = new CIniFile(_T("C:\\setting.ini"));

	m_DiffTool=m_pIniFile->GetValue(SYNC_CFG_SECTION, SYNC_CFG_DIFF_TOOL,DefDiffTool);
	if (m_DiffTool.IsEmpty())
		m_pIniFile->SetValue(SYNC_CFG_SECTION, SYNC_CFG_DIFF_TOOL,DefDiffTool);

	m_LocalPath=m_pIniFile->GetValue(SYNC_CFG_SECTION, SYNC_CFG_LOCAL_DIR);

	for (i=0;i<SYNC_CFG_REMOTE_DIR_HISTORY_MAX;i++)
	{
		szTemp.Format(SYNC_CFG_REMOTE_DIR_FORMAT, i);
		szPath=m_pIniFile->GetValue(SYNC_CFG_SECTION, szTemp);
		SetRemotePath(szPath,-1);
	}  
}

CSyncConfig::~CSyncConfig(void)
{

    CString szTemp;

    for(int i=0;i<m_szRemotePath.GetSize();i++)
    {
        szTemp.Format(SYNC_CFG_REMOTE_DIR_FORMAT, i);
        m_pIniFile->SetValue(SYNC_CFG_SECTION, szTemp, m_szRemotePath[i]);
    }
    
	m_pIniFile->SetValue(SYNC_CFG_SECTION, SYNC_CFG_DIFF_TOOL, m_DiffTool);
	

    if(!m_LocalPath.IsEmpty()&&m_LocalPath.GetAt(m_LocalPath.GetLength()-1) != '\\')
    {
       m_LocalPath+="\\";
    }
	m_pIniFile->SetValue(SYNC_CFG_SECTION, SYNC_CFG_LOCAL_DIR, m_LocalPath);

    if(m_pIniFile)
    {
        delete m_pIniFile;
    }

}

void CSyncConfig::ResetConfig(void)
{
   
}

void CSyncConfig::SetRemotePath(const CString &szPath, int nIdx)
{
	CString szTemp = szPath;
    if(szPath.IsEmpty())
    {
        return ;
    }

    for(int i=0; i<m_szRemotePath.GetSize(); i++)
    {
        if(m_szRemotePath[i] == szTemp)
        {
            m_szRemotePath.RemoveAt(i);

        }
    }

    if(m_szRemotePath.GetSize()>= SYNC_CFG_REMOTE_DIR_HISTORY_MAX)
    {
        m_szRemotePath.RemoveAt(SYNC_CFG_REMOTE_DIR_HISTORY_MAX-1);
    }
	if(szPath.GetAt(szTemp.GetLength()-1)!='\\')
	{
		szTemp+="\\";
	}
	if(nIdx==-1)
		m_szRemotePath.InsertAt(m_szRemotePath.GetSize(), szTemp);
	else
		m_szRemotePath.InsertAt(nIdx, szTemp);
}

