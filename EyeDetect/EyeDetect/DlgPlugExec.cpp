// DlgPlugExec.cpp : 实现文件
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgPlugExec.h"
#include "afxdialogex.h"


// CDlgPlugExec 对话框

IMPLEMENT_DYNAMIC(CDlgPlugExec, CDialogEx)

CDlgPlugExec::CDlgPlugExec(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPlugExec::IDD, pParent),m_LastBtnPos(0,0,0,0),m_ButtonList()
{
	
}

CDlgPlugExec::~CDlgPlugExec()
{

}

void CDlgPlugExec::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}


BEGIN_MESSAGE_MAP(CDlgPlugExec, CDialogEx)
	ON_MESSAGE(WM_SELFDEF_BTN,OnSelfDefBtn)
END_MESSAGE_MAP()


// CDlgPlugExec 消息处理程序

BOOL CDlgPlugExec::RelayoutCtrl(CRect rcClientArea)
{
	CRect  rect=rcClientArea;
	rect.top=rect.top+5;
	rect.bottom-=5;
	rect.left+=5;
	rect.right-=5;

	MoveWindow(rcClientArea);	

	return TRUE;
}


BOOL CDlgPlugExec::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	//AddBtn(_T("E:\\practise\\EyeDetect\\Debug\\Resource\\2.bmp"),_T("测试按钮"),_T("扯一下淡"));
	RelayButton();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//添加按钮到窗口，BmpPath是位图的路径，strDetail是按钮的细节
BOOL CDlgPlugExec::AddBtn(CString BmpPath,CString strBtnName, CString strDetail)
{
	CFileFind  finder;
	if (!finder.FindFile(BmpPath))
	{
		return   FALSE;
	}

	//获取图片,并添加到图标序列
	Gdiplus::Image Img(BmpPath);	
	Gdiplus::Bitmap * IconBmp=(Gdiplus::Bitmap *)Img.GetThumbnailImage(50,50,NULL,NULL);
	HBITMAP   hBmp;
	IconBmp->GetHBITMAP(NULL,&hBmp);


	//设置当前按钮的ID
	UINT   BtnID=IDC_BTN_DYNAMIC+m_ButtonList.size()+1;
	boost::shared_ptr<CMFCButton>  pBtn(new CMFCButton); 
	pBtn->Create(strDetail,0x4001000b,CRect(0,0,100,100),this,BtnID);
	pBtn->SetImage(hBmp);
	pBtn->m_bTransparent=TRUE; 
	pBtn->SetWindowText(strBtnName);
	pBtn->SetTooltip(strDetail);

	pBtn->m_bTopImage=TRUE;
	pBtn->m_bRightImage=FALSE;

	pBtn->ShowWindow(SW_SHOW);
	pBtn->SizeToContent();
	pBtn->Invalidate();

	//移动按钮的放置位置
	if (m_ButtonList.size()==0)
	{
		CRect  rect(0,0,0,0);
		pBtn->GetWindowRect(rect);
		m_LastBtnPos.left=5;
		m_LastBtnPos.top=5;
		m_LastBtnPos.right=m_LastBtnPos.left+rect.Width();
		m_LastBtnPos.bottom=m_LastBtnPos.top+rect.Height();
		pBtn->MoveWindow(m_LastBtnPos);
	}
	else //其他情况下
	{
		CRect  rect(0,0,0,0);
		pBtn->GetWindowRect(rect);
		m_LastBtnPos.top=m_LastBtnPos.bottom+5;
		m_LastBtnPos.right=m_LastBtnPos.left+rect.Width();
		m_LastBtnPos.bottom=m_LastBtnPos.top+rect.Height();
		pBtn->MoveWindow(m_LastBtnPos);
	}

	//将按钮压入链表
	m_ButtonList.push_back(pBtn);

	return TRUE;
}

BOOL  bProtectRun=TRUE;
BOOL CDlgPlugExec::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_LBUTTONDOWN && bProtectRun)
	{
		//防止消息重叠产生错误
		bProtectRun=FALSE;
		UINT  nID=GetWindowLong(pMsg->hwnd,GWL_ID);
		::PostMessage(this->GetSafeHwnd(),WM_SELFDEF_BTN,nID,nID);
		bProtectRun=TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDlgPlugExec::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	OutputDebugString(_T("=====销毁窗口CDlgPlugExec====\r\n"));
	return CDialogEx::DestroyWindow();
}


BOOL CDlgPlugExec::RelayButton(void)
{
	//将所有已有的按钮删除
	if (m_ButtonList.size()!=0)
	{
		while(!m_ButtonList.empty())
		{
			boost::shared_ptr<CMFCButton> pBtn=m_ButtonList.front();
			pBtn->ShowWindow(SW_HIDE);
			pBtn->DestroyWindow();
			pBtn.reset();
			m_ButtonList.pop_front();
		}	
	}

	//根据列表重新添加
	typedef   std::list<boost::shared_ptr<stDllInfo>>  PLUGDLLINFO;
	PLUGDLLINFO  *pList=&(((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.m_PlugList);
	CString   strTemp=((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath();
	CString   strBmp;
	strBmp.Format(_T("%s\\Resource"),strTemp);

	int  num=pList->size();

	for (PLUGDLLINFO::iterator i= pList->begin(); i!=pList->end();i++)
	{
		CString   IconPath;
		IconPath.Format(_T("%s\\%s"),strBmp,(*i)->strBmpSrc);
		AddBtn(IconPath,(*i)->strBtnText,(*i)->strDllComment);	
	}

	return TRUE;
}

//加载Dll动态库
BOOL CDlgPlugExec::LoadDll(CString strDllPath,int nIndex)
{
	//加载动态库
	HINSTANCE   hIns=LoadLibrary(strDllPath);
	
	//如果加载成功
	if (hIns)
	{
		PFN_Plug_CreateObject  pFunc =(PFN_Plug_CreateObject)GetProcAddress(
			hIns, "Plug_CreateObject");

		//如果加载指针成功
		if (pFunc)
		{
			//获取动态库函数指针
			IImageProc  *pObj=NULL;
			(*pFunc)((LPVOID*)&pObj);
			if (!pObj)
			{
				return  FALSE;
			}


			//第一步：给插件传入INI文件路径
			CString     strConfigPath;
			strConfigPath.Format(_T("%s\\Config\\%s"),((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath(),
							((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.GetPlugInfo(nIndex)->strINIFile);
			pObj->SetPlugConfigFile(strConfigPath);

			//第二步: 传入导出结果文件夹路径
			pObj->SetDefaultFolder(((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetTemporaryFolder());

			//第三步：传入对话框大小
			RECT  objRect;
			objRect.left=0;
			objRect.top=0;
			objRect.right=100;
			objRect.bottom=100;
			pObj->SetDlgRect(objRect);

			//第四步：导入待处理图像队列
			IMGVECT  * pVect=theAppPtr.GetAppMainFrmPtr()->m_rightDockedPane.m_DlgRightBar.m_ProcImageAdmin.GetImageVector();
			pVect->size();
			pObj->LoadIplImagePtr(pVect);

			//第五步：显示窗口,获取最终的处理结果
			if(pObj->ShowDlg()==0)
			{
				if (pObj->GetProcImageCount()!=0)
				{
					//删除所有图片
					theAppPtr.GetDlgRightDockedPtr()->m_ProcImageAdmin.RemoveAllImage();

					//获取暂存的图片
					for (int i=0; i<pObj->GetProcImageCount(); i++)
					{
						CString   str;
						str.Format(_T("%s\\%d.bmp"),((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetTemporaryFolder(),i+1);
						theAppPtr.GetDlgRightDockedPtr()->m_ProcImageAdmin.AddTailImage(str);
					}
					theAppPtr.GetDlgRightDockedPtr()->ShowImgList();
				}
			}			

			//结束并销毁资源
			PFN_Plug_DestroyObject   pDesFunc=(PFN_Plug_DestroyObject)GetProcAddress(
				hIns, "Plug_DestroyObject");

			(*pDesFunc)();

		}

		//如果加载指针失败
		else
		{
			CString   str=_T("获取Dll入口指针Plug_CreateObject失败");			
			AfxMessageBox(str);
		}
	}
	else
	{
		CString   str;
		str.Format(_T("加载动态库%s失败"),strDllPath);
		AfxMessageBox(str);
	}

	//释放动态库资源
	BOOL  bFinish=FreeLibrary(hIns);

	return TRUE;
}


BOOL CDlgPlugExec::RunBtn(int nBtnIndex)
{

	//获取当前需要加载的动态库路径
	CString   strDllPath=_T("");
	CString   strDllName=_T("");
	stDllInfo  *pDllInfo=((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.GetPlugInfo(nBtnIndex);

	if (pDllInfo==NULL)
	{
		return  FALSE;
	}

	strDllName=pDllInfo->strDllName;
	//如果没有获取到dll那就返回失败
	if(_T("")==strDllName)
	{
		return  FALSE;
	}

	//获取完整路径
	strDllPath.Format(_T("%s\\%s"),((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath(),strDllName);

	//查询文件是否存在
	CFileFind  finder;
	if (!finder.FindFile(strDllPath))
	{
		return  FALSE;
	}

	//开始加载
	LoadDll(strDllPath,nBtnIndex);

	return TRUE;
}


LRESULT  CDlgPlugExec::OnSelfDefBtn(WPARAM  wParam, LPARAM  lParam)
{
	UINT   nID=(UINT)wParam;
	RunBtn(nID-IDC_BTN_DYNAMIC-1);

	return  0;
}