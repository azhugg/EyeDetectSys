#pragma once

#include "ProcImageListAdmin.h"
// CDlgRightDocked �Ի���

class CDlgRightDocked : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRightDocked)

public:
	CDlgRightDocked(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRightDocked();

// �Ի�������
	enum { IDD = IDD_DLG_RIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CProcImageListAdmin   m_ProcImageAdmin;
	BOOL RelayoutCtrl(CRect rcClientArea);
	CListCtrl m_ImgList;
	virtual BOOL OnInitDialog();
	BOOL ShowImgList(void);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
};
