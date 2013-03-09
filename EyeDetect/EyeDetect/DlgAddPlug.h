#pragma once


// CDlgAddPlug �Ի���
//���ڼ�¼Plug����Ϣ������Щ��Ϣ�ݴ�
typedef   struct  s_Plugfile
{
	CString  strBmpFile;
	CString  strDllFile;
	CString  strINIFile;
}stPlugfile;


class CDlgAddPlug : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddPlug)

public:
	CDlgAddPlug(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddPlug();

// �Ի�������
	enum { IDD = IDD_DLG_ADDPLUG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnFindplug();
	BOOL GetZipFileInfo(CString  strZipFile);	
	afx_msg void OnBnClickedOk();
	CString   m_strFile;
	boost::shared_ptr<stPlugfile>  m_pPlugFile;

	BOOL MoveFile(CString strSrcFilePath , CString strDestFilePath);
	BOOL DeleteFile(CString strSrcFilePath);
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
