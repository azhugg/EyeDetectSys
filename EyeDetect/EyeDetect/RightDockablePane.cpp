// RightDockablePane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "RightDockablePane.h"


// CRightDockablePane

IMPLEMENT_DYNAMIC(CRightDockablePane, CDockablePane)

CRightDockablePane::CRightDockablePane()
{

}

CRightDockablePane::~CRightDockablePane()
{
}


BEGIN_MESSAGE_MAP(CRightDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CRightDockablePane ��Ϣ�������




int CRightDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect  rect;
	rect.SetRectEmpty();

	if (!m_DlgRightBar.Create(IDD_DLG_RIGHT,this))
	{
		OutputDebugString(_T("δ�ܴ������ѡ�����"));
		return -1;
	}

	m_DlgRightBar.ShowWindow(SW_SHOW);

	return 0;
}


void CRightDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_DlgRightBar.SetWindowPos (this, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_DlgRightBar.ShowWindow(SW_SHOW);

	CRect   rect;
	GetClientRect(rect);
	m_DlgRightBar.RelayoutCtrl(rect);
}
