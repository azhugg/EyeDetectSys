#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxshelltreectrl.h"


// CDlgLeftDocked 对话框

class CDlgLeftDocked : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLeftDocked)

public:
	CDlgLeftDocked(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLeftDocked();

// 对话框数据
	enum { IDD = IDD_DLG_LEFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL RelayoutCtrl(CRect rcClientArea);
	CStatic m_DetailInfo;
	CMFCShellTreeCtrl m_FileTree;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult);

//定义信息关联函数,一旦选定文件路径就触发
	BOOL NotifyOther(CString  strFolder);
};
