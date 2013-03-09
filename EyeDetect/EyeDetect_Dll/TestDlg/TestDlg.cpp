// TestDlg.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CTestDlgApp

BEGIN_MESSAGE_MAP(CTestDlgApp, CWinApp)
END_MESSAGE_MAP()


// CTestDlgApp ����

CTestDlgApp::CTestDlgApp():m_pImageProc(NULL),m_nRef(0)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTestDlgApp ����

CTestDlgApp theApp;


// CTestDlgApp ��ʼ��

BOOL CTestDlgApp::InitInstance()
{
	CWinApp::InitInstance();
	OutputDebugString(_T("��ʼ����̬��"));
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
	// TODO: �ڴ����ר�ô����/����û���
	OutputDebugString(_T("�˳���̬��"));
	return CWinApp::ExitInstance();
}
