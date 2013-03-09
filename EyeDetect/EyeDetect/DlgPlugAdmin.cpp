// DlgPlugAdmin.cpp : 实现文件
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgPlugAdmin.h"
#include "afxdialogex.h"
#include "DlgAddPlug.h"



// CDlgPlugAdmin 对话框

IMPLEMENT_DYNAMIC(CDlgPlugAdmin, CDialogEx)

CDlgPlugAdmin::CDlgPlugAdmin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPlugAdmin::IDD, pParent),m_pPlugInfo(NULL)
{

}

CDlgPlugAdmin::~CDlgPlugAdmin()
{
}

void CDlgPlugAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PLUG, m_ListPlug);
}


BEGIN_MESSAGE_MAP(CDlgPlugAdmin, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADDPLUG, &CDlgPlugAdmin::OnBnClickedBtnAddplug)
	ON_BN_CLICKED(IDC_BTN_DELPLUG, &CDlgPlugAdmin::OnBnClickedBtnDelplug)
END_MESSAGE_MAP()


// CDlgPlugAdmin 消息处理程序


BOOL CDlgPlugAdmin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListPlug.SetExtendedStyle(LVS_EX_HEADERDRAGDROP|
					LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	CRect  rect;
	m_ListPlug.GetClientRect(rect);
	m_ListPlug.InsertColumn(0,_T("序号"),LVCFMT_CENTER, rect.Width()/7);
	m_ListPlug.InsertColumn(1,_T("名称"),LVCFMT_CENTER, rect.Width()*3/7);
	m_ListPlug.InsertColumn(2,_T("备注"),LVCFMT_CENTER, rect.Width()*3/7);


	if (m_pPlugInfo!=NULL)
	{
		typedef  std::list<boost::shared_ptr<stDllInfo>>  DLLPLUGINFO;
		DLLPLUGINFO::iterator  i=m_pPlugInfo->m_PlugList.begin();
		int   Index=1;
		CString  IndexString=_T("");
		for (i;i!=m_pPlugInfo->m_PlugList.end();i++,Index++)
		{
			IndexString.Format(_T("%d"),Index);
			m_ListPlug.InsertItem(Index-1,IndexString);
			m_ListPlug.SetItemText(Index-1,1,i->get()->strDllName);
			m_ListPlug.SetItemText(Index-1,2,i->get()->strDllComment);
		}
		if (m_pPlugInfo->m_PlugList.empty())
		{
			GetDlgItem(IDC_BTN_DELPLUG)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_MODIFYPLUG)->EnableWindow(FALSE);
		}
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgPlugAdmin::OnBnClickedBtnAddplug()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgAddPlug  dlg;
	if (IDOK==dlg.DoModal())//添加动态库之后刷新列表
	{
		ResetList();
	}
}


BOOL CDlgPlugAdmin::ResetList(void)
{

	if (m_pPlugInfo!=NULL)
	{
		m_ListPlug.DeleteAllItems();
		typedef  std::list<boost::shared_ptr<stDllInfo>>  DLLPLUGINFO;
		DLLPLUGINFO::iterator  i=m_pPlugInfo->m_PlugList.begin();
		int   Index=1;
		CString  IndexString=_T("");
		for (i;i!=m_pPlugInfo->m_PlugList.end();i++,Index++)
		{
			IndexString.Format(_T("%d"),Index);
			m_ListPlug.InsertItem(Index-1,IndexString);
			m_ListPlug.SetItemText(Index-1,1,i->get()->strDllName);
			m_ListPlug.SetItemText(Index-1,2,i->get()->strDllComment);
		}
	}

	if (m_pPlugInfo->m_PlugList.empty())
	{
		GetDlgItem(IDC_BTN_DELPLUG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_MODIFYPLUG)->EnableWindow(TRUE);
	}

	return TRUE;
}


void CDlgPlugAdmin::OnBnClickedBtnDelplug()
{
	// TODO: 在此添加控件通知处理程序代码

}
