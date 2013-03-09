#pragma once
#include "DlgRightDocked.h"


// CRightDockablePane

class CRightDockablePane : public CDockablePane
{
	DECLARE_DYNAMIC(CRightDockablePane)

public:
	CDlgRightDocked   m_DlgRightBar;
	CRightDockablePane();
	virtual ~CRightDockablePane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


