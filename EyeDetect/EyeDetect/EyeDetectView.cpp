
// EyeDetectView.cpp : CEyeDetectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。

#ifndef SHARED_HANDLERS
#include "EyeDetect.h"
#endif

#include "EyeDetectDoc.h"
#include "EyeDetectView.h"
#include "DlgImageView.h"

#include "DlgPlugAdmin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEyeDetectView

IMPLEMENT_DYNCREATE(CEyeDetectView, CListView)

BEGIN_MESSAGE_MAP(CEyeDetectView, CListView)
	// 标准打印命令
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDR_MENU_VIEWPOP_RELOADIMG, &CEyeDetectView::OnMenuViewpopReloadimg)
	ON_COMMAND(ID_MENU_VIEWPOP_ADDIMG, &CEyeDetectView::OnMenuViewpopAddimg)
	ON_COMMAND(ID_MENU_VIEWIMG, &CEyeDetectView::OnMenuViewimg)
	ON_COMMAND(ID_MENU_PLUGADD, &CEyeDetectView::OnMenuPlugadd)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CEyeDetectView 构造/析构

CEyeDetectView::CEyeDetectView()	
{
	// TODO: 在此处添加构造代码
}

CEyeDetectView::~CEyeDetectView()
{
}

BOOL CEyeDetectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改

	return CListView::PreCreateWindow(cs);
}


// CEyeDetectView 打印

void CEyeDetectView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	//载入View指针
	theAppPtr.SetAppViewPtr(this);
	
	CListCtrl  &listCtrl =GetListCtrl();
	listCtrl.ModifyStyle(0,LVS_ICON);
	listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	listCtrl.SetIconSpacing(CSize(200, 200));

}


void CEyeDetectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}


void CEyeDetectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEyeDetectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	
#endif
	CMenu   menu, *pSubMenu;
	menu.LoadMenu(IDR_MENU_VIEWPOP);
	pSubMenu=menu.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
}


// CEyeDetectView 诊断
#ifdef _DEBUG
void CEyeDetectView::AssertValid() const
{
	CListView::AssertValid();
}

void CEyeDetectView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CEyeDetectDoc* CEyeDetectView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEyeDetectDoc)));
	return (CEyeDetectDoc*)m_pDocument;
}
#endif //_DEBUG


// CEyeDetectView 消息处理程序
void CEyeDetectView::OnMenuViewpopReloadimg()
{
	// TODO: 在此添加命令处理程序代码

	// 获取的图片数目必须大于0
	if(GetListCtrl().GetSelectedCount()>0)
	{

		POSITION  pos=GetListCtrl().GetFirstSelectedItemPosition();
		theAppPtr.GetDlgRightDockedPtr()->m_ProcImageAdmin.RemoveAllImage();

		while (pos!=NULL)
		{
			int  nItem = GetListCtrl().GetNextSelectedItem(pos);
			POSITION  strPos=m_LoadImageAdmin.m_strImagePathList.FindIndex(nItem);
			//获取文件路径传给函数
			CString  strFolder=m_LoadImageAdmin.m_strImagePathList.GetAt(strPos);

			if (theAppPtr.GetDlgRightDockedPtr()!=NULL)
			{
				theAppPtr.GetDlgRightDockedPtr()->m_ProcImageAdmin.AddTailImage(strFolder);
			}		
			
		}
		//刷新显示
		theAppPtr.GetDlgRightDockedPtr()->ShowImgList();
	}
	
}


void CEyeDetectView::OnMenuViewpopAddimg()
{
	// 获取的图片数目必须大于0
	if(GetListCtrl().GetSelectedCount()>0)
	{

		POSITION  pos=GetListCtrl().GetFirstSelectedItemPosition();
		
		while (pos!=NULL)
		{
			int  nItem = GetListCtrl().GetNextSelectedItem(pos);
			POSITION  strPos=m_LoadImageAdmin.m_strImagePathList.FindIndex(nItem);
			//获取文件路径传给函数
			CString  strFolder=m_LoadImageAdmin.m_strImagePathList.GetAt(strPos);

			if (theAppPtr.GetDlgRightDockedPtr()!=NULL)
			{
				theAppPtr.GetDlgRightDockedPtr()->m_ProcImageAdmin.AddTailImage(strFolder);
			}		

		}
		//刷新显示
		theAppPtr.GetDlgRightDockedPtr()->ShowImgList();
	}
}


void CEyeDetectView::ShowLoadImage(void)
{
	GetListCtrl().DeleteAllItems();
	
	GetListCtrl().SetImageList(&(m_LoadImageAdmin.m_ImageIconList),LVSIL_NORMAL);

	//容器不是空的
	if(!m_LoadImageAdmin.m_strImagePathList.IsEmpty())
	{
		for (int i=0; i<m_LoadImageAdmin.m_strImagePathList.GetSize(); i++)
		{
			POSITION  POS= m_LoadImageAdmin.m_strImagePathList.FindIndex(i);
			CString  Temp = m_LoadImageAdmin.m_strImagePathList.GetAt(POS);

			
			int  Pos=Temp.ReverseFind(_T('\\'));
			if (Pos!=-1)
			{
				CString  strFileName = Temp.Right(Temp.GetLength()-Pos-1);
				GetListCtrl().InsertItem(i,strFileName,i);
			}
			
		}		

	}	
}


BOOL CEyeDetectView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CListView::PreTranslateMessage(pMsg);
}


void CEyeDetectView::OnMenuViewimg()
{
	// TODO: 在此添加命令处理程序代码

	if (GetListCtrl().GetSelectedCount()>0)
	{
		POSITION  pos=GetListCtrl().GetFirstSelectedItemPosition();

		if(pos!=NULL)
		{
			int  nItem = GetListCtrl().GetNextSelectedItem(pos);

			POSITION  POS= m_LoadImageAdmin.m_strImagePathList.FindIndex(nItem);
			CString  Temp = m_LoadImageAdmin.m_strImagePathList.GetAt(POS);

			CDlgImageView  dlg;
			dlg.SetImagePath(Temp);
			dlg.DoModal();
		}	
	}


}


void CEyeDetectView::OnMenuPlugadd()
{
	// TODO: 在此添加命令处理程序代码
	CDlgPlugAdmin   dlg;
	dlg.m_pPlugInfo=&(((CEyeDetectApp*)AfxGetApp())->m_PlugInfo);
	if(IDOK==dlg.DoModal())
	{

	}
}


void CEyeDetectView::OnSize(UINT nType, int cx, int cy)
{
	CListView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	ShowLoadImage();
}
