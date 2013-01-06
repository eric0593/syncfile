#include "StdAfx.h"
#include "CIniFile.h"

CIniFile::CIniFile(LPCTSTR lpszFileName)
{
    m_szFileName = lpszFileName;
}

CIniFile::~CIniFile(void)
{
}

CString CIniFile::GetValue(LPCTSTR lpSection, LPCTSTR lpKey, const CString &szDefVal) 
{ 
    TCHAR lpValue[MAX_PATH] ={0}; 
    GetPrivateProfileString(lpSection,lpKey,szDefVal,lpValue,MAX_PATH,m_szFileName); 
    return lpValue; 
}

int CIniFile::GetIntValue(LPCTSTR lpSection, LPCTSTR lpKey, int nDefVal)
{
    return GetPrivateProfileInt(lpSection,lpKey,nDefVal,m_szFileName); 
}

BOOL CIniFile::DelSection(LPCTSTR lpSection) 
{ 
    return WritePrivateProfileString(lpSection,NULL,NULL,m_szFileName);
}

BOOL CIniFile::SetValue(LPCTSTR lpSection, LPCTSTR lpKey, CString &szValue)
{
    return WritePrivateProfileString(lpSection,lpKey,szValue,m_szFileName);
}

BOOL CIniFile::SetIntValue(LPCTSTR lpSection, LPCTSTR lpKey, int nValue)
{
    CString szValue;
    szValue.Format(_T("%d"),nValue);
    return WritePrivateProfileString(lpSection,lpKey,szValue,m_szFileName);
}

BOOL CIniFile::DelKey(LPCTSTR lpSection, LPCTSTR lpKey) 
{ 
    return WritePrivateProfileString(lpSection,lpKey,NULL,m_szFileName);
} 

int CIniFile::GetSections(CStringArray& arrSection) 
{ 
    /* 
    本函数基础： 
    GetPrivateProfileSectionNames - 从 ini 文件中获得 Section 的名称 
    如果 ini 中有两个 Section: [sec1] 和 [sec2]，则返回的是 'sec1',0,'sec2',0,0 ，当你不知道   
    ini 中有哪些 section 的时候可以用这个 api 来获取名称 
    */ 
    int i;   
    int iPos=0;   
    int iMaxCount; 
    TCHAR chSectionNames[MAX_ALLSECTIONS]={0}; //总的提出来的字符串 
    TCHAR chSection[MAX_SECTIONS]={0}; //存放一个段名。 

    GetPrivateProfileSectionNames(chSectionNames,MAX_ALLSECTIONS,m_szFileName); 
    //以下循环，截断到两个连续的0 
    for(i=0;i<MAX_ALLSECTIONS;i++) 
    { 
       if (chSectionNames[i]==0) 
        if (chSectionNames[i]==chSectionNames[i+1]) 
         break; 
    } 
    iMaxCount=i+1; //要多一个0号元素。即找出全部字符串的结束部分。 
    arrSection.RemoveAll();//清空原数组 
    for(i=0;i<iMaxCount;i++) 
    { 
       chSection[iPos++]=chSectionNames[i]; 
       if(chSectionNames[i]==0) 
       {   
        arrSection.Add(chSection); 
        memset(chSection,0,MAX_SECTIONS); 
        iPos=0; 
       } 
    } 
    return (int)arrSection.GetSize(); 
} 

int CIniFile::GetKeyValues(CStringArray& arrKey,CStringArray& arrValue, LPCTSTR lpSection) 
{ 
    /* 
    本函数基础： 
    GetPrivateProfileSection- 从 ini 文件中获得一个Section的全部键名及值名 
    如果ini中有一个段，其下有 "段1=值1" "段2=值2"，则返回的是 '段1=值1',0,'段2=值2',0,0 ，当你不知道   
    获得一个段中的所有键及值可以用这个。 
    */ 
    int i;   
    int iPos=0; 
    CString strKeyValue; 
    int iMaxCount; 
    TCHAR chKeyNames[MAX_ALLKEYS]={0}; //总的提出来的字符串 
    TCHAR chKey[MAX_KEY]={0}; //提出来的一个键名 
    GetPrivateProfileSection(lpSection,chKeyNames,MAX_ALLKEYS,m_szFileName); 
    for(i=0;i<MAX_ALLKEYS;i++) 
    { 
       if (chKeyNames[i]==0) 
        if (chKeyNames[i]==chKeyNames[i+1]) 
         break; 
    } 
    iMaxCount=i+1; //要多一个0号元素。即找出全部字符串的结束部分。 
    arrKey.RemoveAll();//清空原数组 
    arrValue.RemoveAll(); 
    for(i=0;i<iMaxCount;i++) 
    { 
       chKey[iPos++]=chKeyNames[i]; 
       if(chKeyNames[i]==0) 
       { 
        strKeyValue=chKey; 
        arrKey.Add(strKeyValue.Left(strKeyValue.Find(_T("=")))); 
        arrValue.Add(strKeyValue.Mid(strKeyValue.Find(_T("="))+1)); 
        memset(chKey,0,MAX_KEY); 
        iPos=0; 
       } 
    } 
    return (int)arrKey.GetSize(); 
}

BOOL CIniFile::DelAllSections(void) 
{
    int nSection; 
    CStringArray arrSection; 
    nSection=GetSections(arrSection); 
    
    for(int i=0;i<nSection;i++) 
    { 
        DelSection(arrSection[i]);
    } 
    return TRUE; 
} 

