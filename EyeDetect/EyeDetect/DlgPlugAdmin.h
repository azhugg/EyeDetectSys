#pragma once

#include "PlugInfoData.h"

// CDlgPlugAdmin �Ի���

class CDlgPlugAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPlugAdmin)

public:
	CDlgPlugAdmin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPlugAdmin();
	CPlugInfoData  * m_pPlugInfo;

// �Ի�������
	enum { IDD = IDD_DLG_PLUGADMIN };
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListPlug;
	afx_msg void OnBnClickedBtnAddplug();
	BOOL ResetList(void);
	afx_msg void OnBnClickedBtnDelplug();
};
