
// EyeDetectView.h : CEyeDetectView ��Ľӿ�
//

#pragma once
#include "LoadImageListAdmin.h"
#include "ProcImageListAdmin.h"

class CEyeDetectView : public CListView
{
protected: // �������л�����
	CEyeDetectView();
	DECLARE_DYNCREATE(CEyeDetectView)

// ����
public:
	CEyeDetectDoc* GetDocument() const;
	
// ����
public:
	CLoadImageListAdmin  m_LoadImageAdmin;  //����ͼ�������

// ��д
public:
	//virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���



// ʵ��
public:
	virtual ~CEyeDetectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // EyeDetectView.cpp �еĵ��԰汾
inline CEyeDetectDoc* CEyeDetectView::GetDocument() const
   { return reinterpret_cast<CEyeDetectDoc*>(m_pDocument); }
#endif

