#include "StdAfx.h"
#include "AppPtrManage.h"


CAppPtrManage::CAppPtrManage(void)
	:m_pDoc(NULL),m_pMainFrm(NULL),m_pView(NULL),m_pDlgRight(NULL)//初始化变量
{

}


CAppPtrManage::~CAppPtrManage(void)
{

}

CMainFrame	*  CAppPtrManage::GetAppMainFrmPtr()
{
	return  m_pMainFrm;
}

CEyeDetectView  * CAppPtrManage::GetAppViewPtr()
{
	return  m_pView;
}
CEyeDetectDoc  * CAppPtrManage::GetAppDocPtr()
{
	return   m_pDoc;
}

void   CAppPtrManage::SetAppMainFrmPtr(CMainFrame * ptr)
{
	assert(ptr);
	m_pMainFrm=ptr;
}
void    CAppPtrManage::SetAppViewPtr(CEyeDetectView * ptr)
{
	assert(ptr);
	m_pView=ptr;
}
void	CAppPtrManage::SetAppDocPtr(CEyeDetectDoc * ptr)
{
	assert(ptr);
	m_pDoc=ptr;
}

void    CAppPtrManage::SetDlgRightDockedPtr(CDlgRightDocked * ptr)
{
	assert(ptr);
	m_pDlgRight=ptr;
}

CDlgRightDocked  * CAppPtrManage::GetDlgRightDockedPtr()
{
	return  m_pDlgRight;
}

CAppPtrManage   theAppPtr;


