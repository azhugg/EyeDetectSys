
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "LeftDockedPane.h"
#include "RightDockablePane.h"
#include "PlugDock.h"


class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	CLeftDockedPane   m_leftDockedPane;
	CRightDockablePane  m_rightDockedPane;
	CPlugDock           m_PlugDockPane;


// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

//插件工具栏
	CMFCToolBar       m_PlugToolBar;


// 生成的消息映射函数
protected:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void	OnApplicationLook(UINT id);
	afx_msg void	OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMenuPlugadd();
	// //加载左边栏
	bool LoadLeftDockedPane(void);
	bool LoadRightDockedPane(void);
	afx_msg void OnMenuOption();

	afx_msg void OnMenuAddbtn();
	bool LoadPlugDockpane(void);
	afx_msg void OnDestroy();
};


