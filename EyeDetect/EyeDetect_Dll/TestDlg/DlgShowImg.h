#pragma once


// CDlgShowImg �Ի���

class CDlgShowImg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowImg)

public:
	CDlgShowImg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowImg();

// �Ի�������
	enum { IDD = IDD_DLG_SHOWIMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDisp();
	afx_msg void OnBnClickedBtnDispnext();
	BOOL SetInputImgVector(IMGVECT * pImgVect);

	IMGVECT    * m_pImgVect;  //�����ͼ������

	IMGVECT    * m_pOutImgVect;//�����ͼ������

	UINT       m_indexImg;

	CString    m_strFolderPath; //�ݴ��ļ�������
	
	BOOL SetDlgSize(RECT rcRect);
private:

	CRect     m_WndRect;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
};
