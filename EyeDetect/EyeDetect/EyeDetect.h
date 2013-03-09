
// EyeDetect.h : EyeDetect Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "ParamDefine.h"

#include "AppPtrManage.h"
#include "SysFileSet.h"
#include "PlugInfoData.h"


// CEyeDetectApp:
// �йش����ʵ�֣������ EyeDetect.cpp
//



class CEyeDetectApp : public CWinAppEx
{
public:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR  m_gdiplusToken;
	CPlugInfoData  m_PlugInfo;

	

	CSysFileSet  m_sysFileSet;//�ļ���(�ṩ���������ļ�����־�ļ��Ľӿ�)

	CEyeDetectApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();



// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	BOOL CreateFolder(void);

	void  DeleteDirectory(CString strDir);
};

extern CEyeDetectApp theApp;


