// TestDlg.h : TestDlg DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ImageProc.h"


// CTestDlgApp
// �йش���ʵ�ֵ���Ϣ������� TestDlg.cpp
//

class CTestDlgApp : public CWinApp
{
public:
	CTestDlgApp();
	CImageProc   *m_pImageProc;
	int   m_nRef;

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
