#pragma once


// CDlgImageView 对话框

class CDlgImageView : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImageView)
private:
	CString  m_strImagePath;

public:
	CDlgImageView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgImageView();

// 对话框数据
	enum { IDD = IDD_DLG_IMGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL SetImagePath(CString strImagePath);
	afx_msg void OnPaint();
};
