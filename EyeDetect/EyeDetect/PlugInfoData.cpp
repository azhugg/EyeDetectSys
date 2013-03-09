#include "StdAfx.h"
#include "PlugInfoData.h"

extern  CStringW CStrA2CStrW(const CStringA &cstrSrcA);
extern  CStringA CStrW2CStrA(const CStringW &cstrSrcW);

CStringW CStrA2CStrW(const CStringA &cstrSrcA)
{
	int len = MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len];
	memset(wstr, 0, len*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, wstr, len);
	CStringW cstrDestW = wstr;
	delete[] wstr;

	return cstrDestW;
}

CStringA CStrW2CStrA(const CStringW &cstrSrcW)
{
     int len = WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, NULL, 0, NULL, NULL);
	 char *str = new char[len];
	 memset(str, 0, len);
	 WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, str, len, NULL, NULL);
	 CStringA cstrDestA = str;
	 delete[] str;
	 
	 return cstrDestA;
}

CPlugInfoData::CPlugInfoData(void):m_pXMLDoc(NULL),m_strFile(_T("")),m_PlugList(0)
{

}


CPlugInfoData::~CPlugInfoData(void)
{
	if (m_pXMLDoc!=NULL)
	{
		delete m_pXMLDoc;
		m_pXMLDoc=NULL;		
	}
}


BOOL  CPlugInfoData::LoadPlugInfoFile(LPCTSTR  FilePath)
{
	if (FilePath==NULL || m_pXMLDoc!=NULL)
	{
		return FALSE;
	}

	m_strFile.Format(_T("%s"),FilePath);
	
	OutputDebugString(m_strFile);

	////////////////////////////////////////
	//此处需要将Unicode字符串转为Mutibyte字符串
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,FilePath,-1,NULL,0,NULL,FALSE);
	char  *pChar=new char[dwMinSize+1];
	memset(pChar,0,sizeof(char)*(dwMinSize+1));

	WideCharToMultiByte(CP_OEMCP,NULL,FilePath,-1,pChar,dwMinSize+1,NULL,FALSE);
	
	m_pXMLDoc=new TiXmlDocument(pChar);
	m_pXMLDoc->LoadFile(pChar);

	if (m_pXMLDoc==NULL)
	{
		delete  []pChar;
		pChar=NULL;
		return FALSE;
	}

	delete  []pChar;
	pChar=NULL;

	//如果配置文件存在则便利获取信息
	GetPlugCount();

	return  TRUE;
}

//记载并获取插件个数
UINT  CPlugInfoData::GetPlugCount()
{
	UINT   iPlugNum=0;
	if (m_pXMLDoc==NULL)
	{
		iPlugNum=0;
	}
	else
	{
		//进行遍历
		TiXmlElement * pRoot= m_pXMLDoc->RootElement();
		if (pRoot!=NULL)
		{
			TiXmlElement  *pPlug=pRoot->FirstChildElement("Plug");
			while (pPlug!=NULL)
			{
				iPlugNum++;
				//////////////////////////////////////////////////////////////////////////
				//加载Plug信息，先加载MultiByte类型的
				//stDllInfo  dllInfo;
				boost::shared_ptr<stDllInfo>  pDllInfo(new stDllInfo);

				CStringA  str;
				str.Format("%s",pPlug->Attribute("DllName"));

				CString  strw;
				strw=CStrA2CStrW(str);				

				int   nType=0;
				pPlug->Attribute("Type",&nType);

				//填写动态库名称与类型
				pDllInfo->strDllName=strw;
				pDllInfo->nDllType=nType;

				//填写动态库注视
				TiXmlElement  *pDetail=pPlug->FirstChildElement("comment");
				if (pDetail!=NULL)
				{
					CStringA   strA;
					strA.Format("%s",pDetail->Attribute("str"));
					CString    strW;
					strW=CStrA2CStrW(strA);
					pDllInfo->strDllComment=strW;
				}
				else
				{
					pDllInfo->strDllComment=_T("未设置");
				}

				//ConfigFile
				TiXmlElement  *pConfigFile=pPlug->FirstChildElement("ConfigFile");
				if(pConfigFile!=NULL)
				{
					CStringA   strA;
					strA.Format("%s",pConfigFile->Attribute("Path"));
					CString    strW;
					strW=CStrA2CStrW(strA);
					pDllInfo->strINIFile=strW;
				}
				else
				{
					pDllInfo->strINIFile=_T("未设置");
				}

				//Btn名称 Text
				TiXmlElement  *pTextFile=pPlug->FirstChildElement("Text");
				if(pConfigFile!=NULL)
				{
					CStringA   strA;
					strA.Format("%s",pTextFile->Attribute("text"));
					CString    strW;
					strW=CStrA2CStrW(strA);
					pDllInfo->strBtnText=strW;
				}
				else
				{
					pDllInfo->strBtnText=_T("未设置");
				}

				//ICON名称
				TiXmlElement  *pICONFile=pPlug->FirstChildElement("ICON");
				if(pConfigFile!=NULL)
				{
					CStringA   strA;
					strA.Format("%s",pICONFile->Attribute("Name"));
					CString    strW;
					strW=CStrA2CStrW(strA);
					pDllInfo->strBmpSrc=strW;
				}
				else
				{
					pDllInfo->strBmpSrc=_T("未设置");
				}

				m_PlugList.push_back(pDllInfo);
								
				//////////////////////////////////////////////////////////////////////////
				pPlug=pPlug->NextSiblingElement("Plug");
			}
		}

	}
	return  iPlugNum;
}


BOOL CPlugInfoData::AddPlug(stDllInfo  dllInfo)
{
	if (m_pXMLDoc==NULL)
	{
		return  FALSE;
	}
	TiXmlElement *PlugElement = new TiXmlElement("Plug");

	//添加Dll名称元素
	CStringA   strA=CStrW2CStrA(dllInfo.strDllName);
	PlugElement->SetAttribute("DllName", strA);

	//添加Dlltype元素
	PlugElement->SetAttribute("Type", dllInfo.nDllType);

	//创建comment元素
	TiXmlElement *commentElement = new TiXmlElement("comment");
	strA=CStrW2CStrA(dllInfo.strDllComment);
	commentElement->SetAttribute("str",strA);	
	PlugElement->LinkEndChild(commentElement);

	//创建Date元素time
	TiXmlElement *dateElement = new TiXmlElement("Date");
	strA=CStrW2CStrA(_T("未设置"));
	dateElement->SetAttribute("date",strA);	
	PlugElement->LinkEndChild(dateElement);

	//创建ConfigFile：Path
	TiXmlElement *configElement = new TiXmlElement("ConfigFile");
	strA=CStrW2CStrA(dllInfo.strINIFile);
	configElement->SetAttribute("Path",strA);	
	PlugElement->LinkEndChild(configElement);

	//创建ICON：Name
	TiXmlElement *nameElement = new TiXmlElement("ICON");
	strA=CStrW2CStrA(dllInfo.strBmpSrc);
	nameElement->SetAttribute("Name",strA);	
	PlugElement->LinkEndChild(nameElement);

	//创建Text: text
	TiXmlElement *textElement = new TiXmlElement("Text");
	strA=CStrW2CStrA(dllInfo.strBtnText);
	textElement->SetAttribute("text",strA);	
	PlugElement->LinkEndChild(textElement);


	//获取Root根节点
	TiXmlElement * pRoot= m_pXMLDoc->RootElement();
	if (pRoot!=NULL)
	{
		pRoot->LinkEndChild(PlugElement);
		strA=CStrW2CStrA(m_strFile);
		m_pXMLDoc->SaveFile(strA);
	}
	
	return TRUE;
}


BOOL CPlugInfoData::ReloadPlug(void)
{
	//查看m_pXMLDoc是否存在
	if (m_pXMLDoc==NULL)
	{
		return  FALSE;
	}

	//卸载所有以前的信息
	if (!m_PlugList.empty())
	{
		while (!m_PlugList.empty())
		{
			boost::shared_ptr<stDllInfo> pTemp=m_PlugList.front();
			pTemp.reset();
			m_PlugList.pop_front();
		}
	}

	//重新加载一次
	GetPlugCount();

	return TRUE;
}


stDllInfo * CPlugInfoData::GetPlugInfo(UINT nIndex)
{
	if (nIndex >= m_PlugList.size())
	{
		return NULL;
	}

	int  i=0;
	boost::shared_ptr<stDllInfo>  *pPlugInfo=NULL;
	PLUGDLLINFO::iterator  iPtr=m_PlugList.begin();
	for (iPtr; iPtr!=m_PlugList.end(); iPtr++,i++)
	{
		if (i==nIndex)
		{
			pPlugInfo=&(*iPtr);
			break;
		}
	}

	return  pPlugInfo->get();
}
