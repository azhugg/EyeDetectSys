#pragma once
#include "DlgLeftDocked.h"

// CLeftDockedPane

class CLeftDockedPane : public CDockablePane
{
	DECLARE_DYNAMIC(CLeftDockedPane)

public:
	CDlgLeftDocked   m_DlgLeftBar;

	CLeftDockedPane();
	virtual ~CLeftDockedPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


