#pragma once


// CDlgImageView �Ի���

class CDlgImageView : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImageView)
private:
	CString  m_strImagePath;

public:
	CDlgImageView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImageView();

// �Ի�������
	enum { IDD = IDD_DLG_IMGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL SetImagePath(CString strImagePath);
	afx_msg void OnPaint();
};
