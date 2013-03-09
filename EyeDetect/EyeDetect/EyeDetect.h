
// EyeDetect.h : EyeDetect 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "ParamDefine.h"

#include "AppPtrManage.h"
#include "SysFileSet.h"
#include "PlugInfoData.h"


// CEyeDetectApp:
// 有关此类的实现，请参阅 EyeDetect.cpp
//



class CEyeDetectApp : public CWinAppEx
{
public:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR  m_gdiplusToken;
	CPlugInfoData  m_PlugInfo;

	

	CSysFileSet  m_sysFileSet;//文件集(提供各种配置文件、日志文件的接口)

	CEyeDetectApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();



// 实现
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


