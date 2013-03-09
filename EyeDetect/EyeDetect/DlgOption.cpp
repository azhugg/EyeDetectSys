// DlgOption.cpp : 实现文件
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgOption.h"
#include "afxdialogex.h"


// CDlgOption 对话框

IMPLEMENT_DYNAMIC(CDlgOption, CDialogEx)

CDlgOption::CDlgOption(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOption::IDD, pParent)
{

}

CDlgOption::~CDlgOption()
{
}

void CDlgOption::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOption, CDialogEx)
END_MESSAGE_MAP()


// CDlgOption 消息处理程序
