#pragma once


// CDlgPlugExec �Ի���

#define   WM_SELFDEF_BTN   (WM_USER+100)
class CDlgPlugExec : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPlugExec)

public:
	CDlgPlugExec(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPlugExec();

// �Ի�������
	enum { IDD = IDD_DIALOG_PLUGADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL RelayoutCtrl(CRect rcClientArea);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT  OnSelfDefBtn(WPARAM  wParam, LPARAM  lParam);

public:

private:
	typedef   std::list<boost::shared_ptr<CMFCButton>>  BUTTONLIST;
	BUTTONLIST   m_ButtonList;
	CRect      m_LastBtnPos;
	BOOL AddBtn(CString BmpPath,CString strBtnName, CString strDetail);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	BOOL RelayButton(void);
	BOOL LoadDll(CString strDllPath,int nIndex);
	BOOL RunBtn(int nBtnIndex);
};
