#pragma once


// CDlgOption �Ի���

class CDlgOption : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOption)

public:
	CDlgOption(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOption();

// �Ի�������
	enum { IDD = IDD_DLG_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
