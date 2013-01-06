#pragma once
#include "afx.h"

#define MAX_ALLSECTIONS         10240
#define MAX_SECTIONS            1024
#define MAX_ALLKEYS             10240
#define MAX_KEY                 1024

class CIniFile
{
public:
	CIniFile(LPCTSTR lpszFileName);
    ~CIniFile(void);
    
    CString         GetValue(LPCTSTR lpSection, LPCTSTR lpKey, const CString &szDefVal = _T(""));
    int             GetIntValue(LPCTSTR lpSection, LPCTSTR lpKey, int nDefVal = 0);
    BOOL            SetValue(LPCTSTR lpSection, LPCTSTR lpKey, CString &szValue);
    BOOL            SetIntValue(LPCTSTR lpSection, LPCTSTR lpKey, int nValue);
    BOOL            DelSection(LPCTSTR lpSection);
    BOOL            DelKey(LPCTSTR lpSection, LPCTSTR lpKey);
    int             GetSections(CStringArray& arrSection);
    int             GetKeyValues(CStringArray& arrKey,CStringArray& arrValue, LPCTSTR lpSection);
    BOOL            DelAllSections(void);
    
private:
    CString         m_szFileName;
};
