
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "LeftDockedPane.h"
#include "RightDockablePane.h"
#include "PlugDock.h"


class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	CLeftDockedPane   m_leftDockedPane;
	CRightDockablePane  m_rightDockedPane;
	CPlugDock           m_PlugDockPane;


// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

//���������
	CMFCToolBar       m_PlugToolBar;


// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void	OnApplicationLook(UINT id);
	afx_msg void	OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMenuPlugadd();
	// //���������
	bool LoadLeftDockedPane(void);
	bool LoadRightDockedPane(void);
	afx_msg void OnMenuOption();

	afx_msg void OnMenuAddbtn();
	bool LoadPlugDockpane(void);
	afx_msg void OnDestroy();
};


