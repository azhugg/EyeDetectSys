// DlgRightDocked.cpp : 实现文件
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgRightDocked.h"
#include "afxdialogex.h"
#include "AppPtrManage.h"


// CDlgRightDocked 对话框

IMPLEMENT_DYNAMIC(CDlgRightDocked, CDialogEx)

CDlgRightDocked::CDlgRightDocked(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRightDocked::IDD, pParent)
{

}

CDlgRightDocked::~CDlgRightDocked()
{
}

void CDlgRightDocked::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMG, m_ImgList);
}


BEGIN_MESSAGE_MAP(CDlgRightDocked, CDialogEx)
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()


// CDlgRightDocked 消息处理程序


BOOL CDlgRightDocked::RelayoutCtrl(CRect rcClientArea)
{
	//重载控件
	CRect  rect=rcClientArea;
	rect.top=rect.top+5;
	rect.bottom-=5;
	rect.left+=5;
	rect.right-=5;

	m_ImgList.MoveWindow(rect);

	return 0;
}


BOOL CDlgRightDocked::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	theAppPtr.SetDlgRightDockedPtr(this);

	//
	m_ImgList.ModifyStyle(0,LVS_ICON);
	m_ImgList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ImgList.SetIconSpacing(CSize(150, 150));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//显示Icon图标
BOOL CDlgRightDocked::ShowImgList(void)
{
	//删除所有的已显示项
	m_ImgList.DeleteAllItems();

	
	CImageList  *pImageList=&(m_ProcImageAdmin.m_ImageIconList);
	m_ImgList.SetImageList(pImageList,LVSIL_NORMAL);

	//容器不是空的
	if(!m_ProcImageAdmin.m_ImagePathList.IsEmpty())
	{
		for (int i=0; i<m_ProcImageAdmin.m_ImagePathList.GetSize(); i++)
		{
			POSITION  POS= m_ProcImageAdmin.m_ImagePathList.FindIndex(i);
			CString  Temp =m_ProcImageAdmin.m_ImagePathList.GetAt(POS);

			int  Pos=Temp.ReverseFind(_T('\\'));
			if (Pos!=-1)
			{
				CString  strFileName = Temp.Right(Temp.GetLength()-Pos-1);
				m_ImgList.InsertItem(i,strFileName,i);
			}

		}
	}	

	return 0;
}


void CDlgRightDocked::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}
