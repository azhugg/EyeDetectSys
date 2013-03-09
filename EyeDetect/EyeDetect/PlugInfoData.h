#pragma once

#include "tinystr.h"
#include "tinyxml.h"

typedef  struct  s_DllInfo
{
	CString   strDllName;     //��̬������
	UINT      nDllType;		  //DLLType
	CString   strDllComment;  //dll�Ĺ�����ʾ����ʾ��Tooltip����
	CString   strBmpSrc;      //ͼ������
	CString   strBtnText;     //Btn�����Ʊ���С�ڵ����ĸ���
	CString   strINIFile;     //��ʼ�������INI�ļ�����(���ڿ��Ը�ΪXML�ļ�)
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

