// PlugDock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "PlugDock.h"


// CPlugDock

IMPLEMENT_DYNAMIC(CPlugDock, CDockablePane)

CPlugDock::CPlugDock()
{

}

CPlugDock::~CPlugDock()
{
}


BEGIN_MESSAGE_MAP(CPlugDock, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPlugDock ��Ϣ�������




int CPlugDock::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect  rect;
	rect.SetRectEmpty();

	if (!m_DlgPlugExec.Create(IDD_DIALOG_PLUGADMIN,this))
	{
		OutputDebugString(_T("δ�ܴ������ѡ�����"));
		return -1;
	}

	m_DlgPlugExec.ShowWindow(SW_SHOW);

	return 0;
}


void CPlugDock::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_DlgPlugExec.SetWindowPos (this, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_DlgPlugExec.ShowWindow(SW_SHOW);

	CRect   rect;
	GetClientRect(rect);
	//rect.right=rect.left+80;
	m_DlgPlugExec.RelayoutCtrl(rect);

}
