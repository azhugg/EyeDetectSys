#pragma once

#include "tinystr.h"
#include "tinyxml.h"

typedef  struct  s_DllInfo
{
	CString   strDllName;     //动态库名称
	UINT      nDllType;		  //DLLType
	CString   strDllComment;  //dll的功能提示，显示在Tooltip当中
	CString   strBmpSrc;      //图标名称
	CString   strBtnText;     //Btn的名称必须小于等于四个字
	CString   strINIFile;     //初始化插件的INI文件名称(后期可以改为XML文件)
}stDllInfo;

class CPlugInfoData
{
public:
	CPlugInfoData(void);
	~CPlugInfoData(void);

	BOOL  LoadPlugInfoFile(LPCTSTR  FilePath);
	

	typedef   std::list<boost::shared_ptr<stDllInfo>>  PLUGDLLINFO;
	PLUGDLLINFO  m_PlugList;

private:
	TiXmlDocument  * m_pXMLDoc;
	TiXmlElement   * m_pCurPlug;

	UINT  GetPlugCount();

	TCHAR		* m_pErrorDisp;
	CString     m_strFile;

public:
	BOOL AddPlug(stDllInfo  dllInfo);
	BOOL ReloadPlug(void);
	stDllInfo * GetPlugInfo(UINT nIndex);
};

