#pragma once


// CDlgOption 对话框

class CDlgOption : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOption)

public:
	CDlgOption(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOption();

// 对话框数据
	enum { IDD = IDD_DLG_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
