#pragma once


// CDlgShowImg 对话框

class CDlgShowImg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowImg)

public:
	CDlgShowImg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShowImg();

// 对话框数据
	enum { IDD = IDD_DLG_SHOWIMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDisp();
	afx_msg void OnBnClickedBtnDispnext();
	BOOL SetInputImgVector(IMGVECT * pImgVect);

	IMGVECT    * m_pImgVect;  //输入的图像序列

	IMGVECT    * m_pOutImgVect;//输出的图像序列

	UINT       m_indexImg;

	CString    m_strFolderPath; //暂存文件夹名称
	
	BOOL SetDlgSize(RECT rcRect);
private:

	CRect     m_WndRect;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
};
