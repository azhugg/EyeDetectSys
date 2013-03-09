#pragma once

#include "PlugInfoData.h"

// CDlgPlugAdmin 对话框

class CDlgPlugAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPlugAdmin)

public:
	CDlgPlugAdmin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPlugAdmin();
	CPlugInfoData  * m_pPlugInfo;

// 对话框数据
	enum { IDD = IDD_DLG_PLUGADMIN };
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListPlug;
	afx_msg void OnBnClickedBtnAddplug();
	BOOL ResetList(void);
	afx_msg void OnBnClickedBtnDelplug();
};
