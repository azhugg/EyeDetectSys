#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxshelltreectrl.h"


// CDlgLeftDocked �Ի���

class CDlgLeftDocked : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLeftDocked)

public:
	CDlgLeftDocked(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLeftDocked();

// �Ի�������
	enum { IDD = IDD_DLG_LEFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL RelayoutCtrl(CRect rcClientArea);
	CStatic m_DetailInfo;
	CMFCShellTreeCtrl m_FileTree;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult);

//������Ϣ��������,һ��ѡ���ļ�·���ʹ���
	BOOL NotifyOther(CString  strFolder);
};
