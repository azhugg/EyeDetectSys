#include "StdAfx.h"
#include "SysFileSet.h"


CSysFileSet::CSysFileSet(void):m_strConfigFilePath(_T("")),
							   m_strPlugConfigPath(_T("")),
							   m_strTemporaryFolder(_T(""))
							   
{
	m_strAppPath=_T("");
	m_strTemporaryFolder=_T("");
	LoadAppPath();
}


CSysFileSet::~CSysFileSet(void)
{

}

CString  CSysFileSet::GetConfigFilePath()
{
	if (m_strAppPath!=_T(""))
	{
		if (m_strConfigFilePath==_T(""))
		{
			m_strConfigFilePath=m_strAppPath+_T("\\SysConfig.xml");
		}
	}
	return  m_strConfigFilePath;
}
CString  CSysFileSet::GetPlugConfigPath()
{
	if (m_strAppPath!=_T(""))
	{
		if (m_strPlugConfigPath==_T(""))
		{
			m_strPlugConfigPath=m_strAppPath+_T("\\Config\\PlugAdmin.xml");
		}
	}
	return  m_strPlugConfigPath;
}

BOOL     CSysFileSet::ScanFile()
{
	return   TRUE;
}

BOOL   CSysFileSet::LoadAppPath()
{
	TCHAR  str[MAX_PATH];
		
	CString  AppPath;
	GetModuleFileName(NULL, str, sizeof(str));

	AppPath.Format(_T("%s"),str);

	int  Pos=AppPath.ReverseFind(_T('\\'));
	CString  strFileName = _T("");

	if (Pos!=-1)
	{		
		strFileName=AppPath.Left(Pos);		
	}

	m_strAppPath=strFileName;

	return  TRUE;
	
}

CString  CSysFileSet::GetAppPath()
{
	return  m_strAppPath;
}


CString  CSysFileSet::GetTemporaryFolder()
{
	if (m_strAppPath!=_T(""))
	{
		m_strTemporaryFolder=m_strAppPath+_T("\\TempImg");
	}

	return  m_strTemporaryFolder;
}