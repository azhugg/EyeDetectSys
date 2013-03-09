// TestDlg.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CTestDlgApp

BEGIN_MESSAGE_MAP(CTestDlgApp, CWinApp)
END_MESSAGE_MAP()


// CTestDlgApp 构造

CTestDlgApp::CTestDlgApp():m_pImageProc(NULL),m_nRef(0)
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CTestDlgApp 对象

CTestDlgApp theApp;


// CTestDlgApp 初始化

BOOL CTestDlgApp::InitInstance()
{
	CWinApp::InitInstance();
	OutputDebugString(_T("初始化动态库"));
	return TRUE;
}

#include  "ImageProc.h"

BOOL WINAPI Plug_CreateObject(void ** pobj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (theApp.m_nRef>0)
		return  FALSE;

	CImageProc  *pInterface= new  CImageProc;

	theApp.m_pImageProc=pInterface;

	(*pobj)=(LPVOID)pInterface;

	theApp.m_nRef=1;
	
	return  *pobj != NULL;
}

BOOL WINAPI  Plug_DestroyObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (theApp.m_pImageProc!=NULL)
	{
		delete   theApp.m_pImageProc;
		theApp.m_pImageProc=NULL;
		theApp.m_nRef=0;
	}

	return  TRUE;
}

int CTestDlgApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	OutputDebugString(_T("退出动态库"));
	return CWinApp::ExitInstance();
}
