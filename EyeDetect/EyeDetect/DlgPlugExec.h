#pragma once


// CDlgPlugExec 对话框

#define   WM_SELFDEF_BTN   (WM_USER+100)
class CDlgPlugExec : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPlugExec)

public:
	CDlgPlugExec(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPlugExec();

// 对话框数据
	enum { IDD = IDD_DIALOG_PLUGADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
