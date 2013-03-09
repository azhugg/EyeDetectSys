// DlgRightDocked.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgRightDocked.h"
#include "afxdialogex.h"
#include "AppPtrManage.h"


// CDlgRightDocked �Ի���

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


// CDlgRightDocked ��Ϣ�������


BOOL CDlgRightDocked::RelayoutCtrl(CRect rcClientArea)
{
	//���ؿؼ�
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	theAppPtr.SetDlgRightDockedPtr(this);

	//
	m_ImgList.ModifyStyle(0,LVS_ICON);
	m_ImgList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ImgList.SetIconSpacing(CSize(150, 150));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//��ʾIconͼ��
BOOL CDlgRightDocked::ShowImgList(void)
{
	//ɾ�����е�����ʾ��
	m_ImgList.DeleteAllItems();

	
	CImageList  *pImageList=&(m_ProcImageAdmin.m_ImageIconList);
	m_ImgList.SetImageList(pImageList,LVSIL_NORMAL);

	//�������ǿյ�
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}
