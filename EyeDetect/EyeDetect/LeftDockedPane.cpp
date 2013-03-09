// LeftDockedPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "LeftDockedPane.h"


// CLeftDockedPane

IMPLEMENT_DYNAMIC(CLeftDockedPane, CDockablePane)

CLeftDockedPane::CLeftDockedPane()
{

}

CLeftDockedPane::~CLeftDockedPane()
{
}


BEGIN_MESSAGE_MAP(CLeftDockedPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CLeftDockedPane ��Ϣ�������




int CLeftDockedPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������


	CRect  rect;
	rect.SetRectEmpty();

	if (!m_DlgLeftBar.Create(IDD_DLG_LEFT,this))
	{
		OutputDebugString(_T("δ�ܴ������ѡ�����"));
		return -1;
	}

	m_DlgLeftBar.ShowWindow(SW_SHOW);

	return 0;
}


void CLeftDockedPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_DlgLeftBar.SetWindowPos (this, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_DlgLeftBar.ShowWindow(SW_SHOW);

	CRect   rect;
	GetClientRect(rect);
	m_DlgLeftBar.RelayoutCtrl(rect);

}
