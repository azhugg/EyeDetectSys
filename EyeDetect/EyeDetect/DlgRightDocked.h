#pragma once

#include "ProcImageListAdmin.h"
// CDlgRightDocked 对话框

class CDlgRightDocked : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRightDocked)

public:
	CDlgRightDocked(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRightDocked();

// 对话框数据
	enum { IDD = IDD_DLG_RIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProcImageListAdmin   m_ProcImageAdmin;
	BOOL RelayoutCtrl(CRect rcClientArea);
	CListCtrl m_ImgList;
	virtual BOOL OnInitDialog();
	BOOL ShowImgList(void);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
};
