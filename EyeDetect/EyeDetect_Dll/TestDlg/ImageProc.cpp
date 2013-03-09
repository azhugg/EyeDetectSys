
#include "StdAfx.h"
#include "ImageProc.h"
#include "resource.h"

#include "DlgShowImg.h"


CImageProc::CImageProc(void):m_pDlgShowImg(new CDlgShowImg)
{
	//����ͼ��
	m_hIcon = NULL;

}


CImageProc::~CImageProc(void)
{
	//�ͷ���Դ
	if (m_hIcon)
		DeleteObject(m_hIcon);

	if (m_pDlgShowImg)
	{
		OutputDebugString(_T("=====�ͷ�m_pDlgShowImg====\r\n"));
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



//����ȱʡ�ļ��У��������õ�ǰĬ���ݴ��ļ��е�·��
DWORD  CImageProc::SetDefaultFolder(const CString strFolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_pDlgShowImg->m_strFolderPath=strFolder;
	return  0;
}

//��ȡͼ�����Ŀ�������ֵ<=0����ô����û�з���ֵ�������ֵ>0�����з���ͼ��
DWORD  CImageProc::GetProcImageCount()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int  Res=m_pDlgShowImg->m_pOutImgVect->size();
	return   Res;
}

//2013��2��22�����
//���ò���������ļ�·��
DWORD  CImageProc::SetPlugConfigFile(const CString strFilePath)
{
	return  0;
}

//��ȡ�ÿؼ���UUID����(�ú�����ѭGPL��׼)
DWORD  CImageProc::GetPlugUUID(CString& strUUID)
{
	return  0;
}
