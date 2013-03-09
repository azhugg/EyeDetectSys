// DlgPlugAdmin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgPlugAdmin.h"
#include "afxdialogex.h"
#include "DlgAddPlug.h"



// CDlgPlugAdmin �Ի���

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


// CDlgPlugAdmin ��Ϣ�������


BOOL CDlgPlugAdmin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListPlug.SetExtendedStyle(LVS_EX_HEADERDRAGDROP|
					LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	CRect  rect;
	m_ListPlug.GetClientRect(rect);
	m_ListPlug.InsertColumn(0,_T("���"),LVCFMT_CENTER, rect.Width()/7);
	m_ListPlug.InsertColumn(1,_T("����"),LVCFMT_CENTER, rect.Width()*3/7);
	m_ListPlug.InsertColumn(2,_T("��ע"),LVCFMT_CENTER, rect.Width()*3/7);


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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgPlugAdmin::OnBnClickedBtnAddplug()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgAddPlug  dlg;
	if (IDOK==dlg.DoModal())//��Ӷ�̬��֮��ˢ���б�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
