
// EyeDetectView.h : CEyeDetectView 类的接口
//

#pragma once
#include "LoadImageListAdmin.h"
#include "ProcImageListAdmin.h"

class CEyeDetectView : public CListView
{
protected: // 仅从序列化创建
	CEyeDetectView();
	DECLARE_DYNCREATE(CEyeDetectView)

// 特性
public:
	CEyeDetectDoc* GetDocument() const;
	
// 操作
public:
	CLoadImageListAdmin  m_LoadImageAdmin;  //加载图像管理类

// 重写
public:
	//virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用



// 实现
public:
	virtual ~CEyeDetectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuViewpopReloadimg();
	afx_msg void OnMenuViewpopAddimg();
	void ShowLoadImage(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuViewimg();
	afx_msg void OnMenuPlugadd();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // EyeDetectView.cpp 中的调试版本
inline CEyeDetectDoc* CEyeDetectView::GetDocument() const
   { return reinterpret_cast<CEyeDetectDoc*>(m_pDocument); }
#endif

