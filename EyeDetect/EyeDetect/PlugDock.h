#pragma once


// CPlugDock
#include "DlgPlugExec.h"

class CPlugDock : public CDockablePane
{
	DECLARE_DYNAMIC(CPlugDock)

public:
	CPlugDock();
	virtual ~CPlugDock();

	CDlgPlugExec  m_DlgPlugExec;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


