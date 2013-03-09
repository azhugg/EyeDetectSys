// DlgLeftDocked.cpp : 实现文件
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgLeftDocked.h"
#include "afxdialogex.h"
#include "LoadImageListAdmin.h"
#include "AppPtrManage.h"


// CDlgLeftDocked 对话框

IMPLEMENT_DYNAMIC(CDlgLeftDocked, CDialogEx)

CDlgLeftDocked::CDlgLeftDocked(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLeftDocked::IDD, pParent)
{
	OutputDebugString(_T("===创建CDlgLeftDocked===\r\n"));
}

CDlgLeftDocked::~CDlgLeftDocked()
{
}

void CDlgLeftDocked::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DETAILINFO, m_DetailInfo);
	DDX_Control(pDX, IDC_MFCSHELLTREE1, m_FileTree);
}


BEGIN_MESSAGE_MAP(CDlgLeftDocked, CDialogEx)
//	ON_NOTIFY(NM_CLICK, IDC_MFCSHELLTREE1, &CDlgLeftDocked::OnNMClickMfcshelltree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE1, &CDlgLeftDocked::OnSelchangedMfcshelltree1)
END_MESSAGE_MAP()


// //重绘控件的大小


BOOL CDlgLeftDocked::RelayoutCtrl(CRect rcClientArea)
{
	//重载控件
	CRect  rect=rcClientArea;
	rect.top=rect.top+5;
	rect.bottom=rect.Height()*2/3-3;
	rect.left+=5;
	rect.right-=5;

	m_FileTree.MoveWindow(rect);

	rect.top=rect.bottom+5;
	rect.bottom=rcClientArea.bottom-5;
	m_DetailInfo.MoveWindow(rect);

	return TRUE;
}


BOOL CDlgLeftDocked::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_FileTree.Expand(m_FileTree.GetRootItem(), TVE_EXPAND);
	m_FileTree.EnableShellContextMenu(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDlgLeftDocked::OnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM  hSel=pNMTreeView->itemNew.hItem;
	if(hSel!=NULL)
	{
		CString   strFolder=_T("");
		m_FileTree.GetItemPath(strFolder,hSel);

		CFileFind  finder;
		//检验路径是否正确
		CString  str=strFolder+_T("\\*.*");
		BOOL  bWork=finder.FindFile(str);
	
		while(bWork)
		{
			bWork=finder.FindNextFile();
			if (finder.IsDots())
			{
				NotifyOther(strFolder);
				break;
			}	
		}
	
	}
	*pResult = 0;
}

//
BOOL CDlgLeftDocked::NotifyOther(CString  strFolder)
{
	//	
	if (theAppPtr.GetAppViewPtr()!=NULL)
	{
		theAppPtr.GetAppViewPtr()->m_LoadImageAdmin.LoadImage(strFolder);
	}	
	return TRUE;
}
