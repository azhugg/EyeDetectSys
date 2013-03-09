
#include "StdAfx.h"
#include "ImageProc.h"
#include "resource.h"

#include "DlgShowImg.h"


CImageProc::CImageProc(void):m_pDlgShowImg(new CDlgShowImg)
{
	//加载图标
	m_hIcon = NULL;

}


CImageProc::~CImageProc(void)
{
	//释放资源
	if (m_hIcon)
		DeleteObject(m_hIcon);

	if (m_pDlgShowImg)
	{
		OutputDebugString(_T("=====释放m_pDlgShowImg====\r\n"));
		//m_pDlgShowImg->
		//delete   m_pDlgShowImg;
		//m_pDlgShowImg = NULL;
	}
}

HICON  CImageProc::GetIcon()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return  m_hIcon;
}
DWORD  CImageProc::ShowDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pDlgShowImg==NULL)
	{
		return  1;
	}
	
	if (m_pDlgShowImg->DoModal()==IDOK)
	{

		return 0;
	}	

	return  0;
}

DWORD   CImageProc::LoadIplImagePtr(IMGVECT * pInputImg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pDlgShowImg==NULL)
	{
		return 1;
	}
	if (pInputImg==NULL)
	{
		return 2;
	}
	if (pInputImg->size()==0)
	{
		return 0;
	}

	m_pDlgShowImg->SetInputImgVector(pInputImg);

	return  0;
}

DWORD   CImageProc::SetDlgRect(const RECT rcDlg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if ((0>=(rcDlg.right-rcDlg.left))||(0>=(rcDlg.bottom-rcDlg.top)))
	{
		return 1;
	}
	if (m_pDlgShowImg==NULL)
	{
		return  1;
	}

	m_pDlgShowImg->SetDlgSize(rcDlg);

	return  0;
}



//设置缺省文件夹，用于设置当前默认暂存文件夹的路径
DWORD  CImageProc::SetDefaultFolder(const CString strFolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_pDlgShowImg->m_strFolderPath=strFolder;
	return  0;
}

//获取图像的数目，如果该值<=0，那么表明没有返回值，如果该值>0表明有返回图像
DWORD  CImageProc::GetProcImageCount()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int  Res=m_pDlgShowImg->m_pOutImgVect->size();
	return   Res;
}

//2013年2月22日添加
//设置插件的配置文件路径
DWORD  CImageProc::SetPlugConfigFile(const CString strFilePath)
{
	return  0;
}

//获取该控件的UUID号码(该号码遵循GPL标准)
DWORD  CImageProc::GetPlugUUID(CString& strUUID)
{
	return  0;
}
