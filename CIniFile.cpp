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
    ������������ 
    GetPrivateProfileSectionNames - �� ini �ļ��л�� Section ������ 
    ��� ini �������� Section: [sec1] �� [sec2]���򷵻ص��� 'sec1',0,'sec2',0,0 �����㲻֪��   
    ini ������Щ section ��ʱ���������� api ����ȡ���� 
    */ 
    int i;   
    int iPos=0;   
    int iMaxCount; 
    TCHAR chSectionNames[MAX_ALLSECTIONS]={0}; //�ܵ���������ַ��� 
    TCHAR chSection[MAX_SECTIONS]={0}; //���һ�������� 

    GetPrivateProfileSectionNames(chSectionNames,MAX_ALLSECTIONS,m_szFileName); 
    //����ѭ�����ضϵ�����������0 
    for(i=0;i<MAX_ALLSECTIONS;i++) 
    { 
       if (chSectionNames[i]==0) 
        if (chSectionNames[i]==chSectionNames[i+1]) 
         break; 
    } 
    iMaxCount=i+1; //Ҫ��һ��0��Ԫ�ء����ҳ�ȫ���ַ����Ľ������֡� 
    arrSection.RemoveAll();//���ԭ���� 
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
    ������������ 
    GetPrivateProfileSection- �� ini �ļ��л��һ��Section��ȫ��������ֵ�� 
    ���ini����һ���Σ������� "��1=ֵ1" "��2=ֵ2"���򷵻ص��� '��1=ֵ1',0,'��2=ֵ2',0,0 �����㲻֪��   
    ���һ�����е����м���ֵ����������� 
    */ 
    int i;   
    int iPos=0; 
    CString strKeyValue; 
    int iMaxCount; 
    TCHAR chKeyNames[MAX_ALLKEYS]={0}; //�ܵ���������ַ��� 
    TCHAR chKey[MAX_KEY]={0}; //�������һ������ 
    GetPrivateProfileSection(lpSection,chKeyNames,MAX_ALLKEYS,m_szFileName); 
    for(i=0;i<MAX_ALLKEYS;i++) 
    { 
       if (chKeyNames[i]==0) 
        if (chKeyNames[i]==chKeyNames[i+1]) 
         break; 
    } 
    iMaxCount=i+1; //Ҫ��һ��0��Ԫ�ء����ҳ�ȫ���ַ����Ľ������֡� 
    arrKey.RemoveAll();//���ԭ���� 
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

