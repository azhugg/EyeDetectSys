// DlgPlugExec.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgPlugExec.h"
#include "afxdialogex.h"


// CDlgPlugExec �Ի���

IMPLEMENT_DYNAMIC(CDlgPlugExec, CDialogEx)

CDlgPlugExec::CDlgPlugExec(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPlugExec::IDD, pParent),m_LastBtnPos(0,0,0,0),m_ButtonList()
{
	
}

CDlgPlugExec::~CDlgPlugExec()
{

}

void CDlgPlugExec::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}


BEGIN_MESSAGE_MAP(CDlgPlugExec, CDialogEx)
	ON_MESSAGE(WM_SELFDEF_BTN,OnSelfDefBtn)
END_MESSAGE_MAP()


// CDlgPlugExec ��Ϣ�������

BOOL CDlgPlugExec::RelayoutCtrl(CRect rcClientArea)
{
	CRect  rect=rcClientArea;
	rect.top=rect.top+5;
	rect.bottom-=5;
	rect.left+=5;
	rect.right-=5;

	MoveWindow(rcClientArea);	

	return TRUE;
}


BOOL CDlgPlugExec::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	//AddBtn(_T("E:\\practise\\EyeDetect\\Debug\\Resource\\2.bmp"),_T("���԰�ť"),_T("��һ�µ�"));
	RelayButton();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//��Ӱ�ť�����ڣ�BmpPath��λͼ��·����strDetail�ǰ�ť��ϸ��
BOOL CDlgPlugExec::AddBtn(CString BmpPath,CString strBtnName, CString strDetail)
{
	CFileFind  finder;
	if (!finder.FindFile(BmpPath))
	{
		return   FALSE;
	}

	//��ȡͼƬ,����ӵ�ͼ������
	Gdiplus::Image Img(BmpPath);	
	Gdiplus::Bitmap * IconBmp=(Gdiplus::Bitmap *)Img.GetThumbnailImage(50,50,NULL,NULL);
	HBITMAP   hBmp;
	IconBmp->GetHBITMAP(NULL,&hBmp);


	//���õ�ǰ��ť��ID
	UINT   BtnID=IDC_BTN_DYNAMIC+m_ButtonList.size()+1;
	boost::shared_ptr<CMFCButton>  pBtn(new CMFCButton); 
	pBtn->Create(strDetail,0x4001000b,CRect(0,0,100,100),this,BtnID);
	pBtn->SetImage(hBmp);
	pBtn->m_bTransparent=TRUE; 
	pBtn->SetWindowText(strBtnName);
	pBtn->SetTooltip(strDetail);

	pBtn->m_bTopImage=TRUE;
	pBtn->m_bRightImage=FALSE;

	pBtn->ShowWindow(SW_SHOW);
	pBtn->SizeToContent();
	pBtn->Invalidate();

	//�ƶ���ť�ķ���λ��
	if (m_ButtonList.size()==0)
	{
		CRect  rect(0,0,0,0);
		pBtn->GetWindowRect(rect);
		m_LastBtnPos.left=5;
		m_LastBtnPos.top=5;
		m_LastBtnPos.right=m_LastBtnPos.left+rect.Width();
		m_LastBtnPos.bottom=m_LastBtnPos.top+rect.Height();
		pBtn->MoveWindow(m_LastBtnPos);
	}
	else //���������
	{
		CRect  rect(0,0,0,0);
		pBtn->GetWindowRect(rect);
		m_LastBtnPos.top=m_LastBtnPos.bottom+5;
		m_LastBtnPos.right=m_LastBtnPos.left+rect.Width();
		m_LastBtnPos.bottom=m_LastBtnPos.top+rect.Height();
		pBtn->MoveWindow(m_LastBtnPos);
	}

	//����ťѹ������
	m_ButtonList.push_back(pBtn);

	return TRUE;
}

BOOL  bProtectRun=TRUE;
BOOL CDlgPlugExec::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message==WM_LBUTTONDOWN && bProtectRun)
	{
		//��ֹ��Ϣ�ص���������
		bProtectRun=FALSE;
		UINT  nID=GetWindowLong(pMsg->hwnd,GWL_ID);
		::PostMessage(this->GetSafeHwnd(),WM_SELFDEF_BTN,nID,nID);
		bProtectRun=TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDlgPlugExec::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	OutputDebugString(_T("=====���ٴ���CDlgPlugExec====\r\n"));
	return CDialogEx::DestroyWindow();
}


BOOL CDlgPlugExec::RelayButton(void)
{
	//���������еİ�ťɾ��
	if (m_ButtonList.size()!=0)
	{
		while(!m_ButtonList.empty())
		{
			boost::shared_ptr<CMFCButton> pBtn=m_ButtonList.front();
			pBtn->ShowWindow(SW_HIDE);
			pBtn->DestroyWindow();
			pBtn.reset();
			m_ButtonList.pop_front();
		}	
	}

	//�����б��������
	typedef   std::list<boost::shared_ptr<stDllInfo>>  PLUGDLLINFO;
	PLUGDLLINFO  *pList=&(((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.m_PlugList);
	CString   strTemp=((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath();
	CString   strBmp;
	strBmp.Format(_T("%s\\Resource"),strTemp);

	int  num=pList->size();

	for (PLUGDLLINFO::iterator i= pList->begin(); i!=pList->end();i++)
	{
		CString   IconPath;
		IconPath.Format(_T("%s\\%s"),strBmp,(*i)->strBmpSrc);
		AddBtn(IconPath,(*i)->strBtnText,(*i)->strDllComment);	
	}

	return TRUE;
}

//����Dll��̬��
BOOL CDlgPlugExec::LoadDll(CString strDllPath,int nIndex)
{
	//���ض�̬��
	HINSTANCE   hIns=LoadLibrary(strDllPath);
	
	//������سɹ�
	if (hIns)
	{
		PFN_Plug_CreateObject  pFunc =(PFN_Plug_CreateObject)GetProcAddress(
			hIns, "Plug_CreateObject");

		//�������ָ��ɹ�
		if (pFunc)
		{
			//��ȡ��̬�⺯��ָ��
			IImageProc  *pObj=NULL;
			(*pFunc)((LPVOID*)&pObj);
			if (!pObj)
			{
				return  FALSE;
			}


			//��һ�������������INI�ļ�·��
			CString     strConfigPath;
			strConfigPath.Format(_T("%s\\Config\\%s"),((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath(),
							((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.GetPlugInfo(nIndex)->strINIFile);
			pObj->SetPlugConfigFile(strConfigPath);

			//�ڶ���: ���뵼������ļ���·��
			pObj->SetDefaultFolder(((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetTemporaryFolder());

			//������������Ի����С
			RECT  objRect;
			objRect.left=0;
			objRect.top=0;
			objRect.right=100;
			objRect.bottom=100;
			pObj->SetDlgRect(objRect);

			//���Ĳ������������ͼ�����
			IMGVECT  * pVect=theAppPtr.GetAppMainFrmPtr()->m_rightDockedPane.m_DlgRightBar.m_ProcImageAdmin.GetImageVector();
			pVect->size();
			pObj->LoadIplImagePtr(pVect);

			//���岽����ʾ����,��ȡ���յĴ�����
			if(pObj->ShowDlg()==0)
			{
				if (pObj->GetProcImageCount()!=0)
				{
					//ɾ������ͼƬ
					theAppPtr.GetDlgRightDockedPtr()->m_ProcImageAdmin.RemoveAllImage();

					//��ȡ�ݴ��ͼƬ
					for (int i=0; i<pObj->GetProcImageCount(); i++)
					{
						CString   str;
						str.Format(_T("%s\\%d.bmp"),((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetTemporaryFolder(),i+1);
						theAppPtr.GetDlgRightDockedPtr()->m_ProcImageAdmin.AddTailImage(str);
					}
					theAppPtr.GetDlgRightDockedPtr()->ShowImgList();
				}
			}			

			//������������Դ
			PFN_Plug_DestroyObject   pDesFunc=(PFN_Plug_DestroyObject)GetProcAddress(
				hIns, "Plug_DestroyObject");

			(*pDesFunc)();

		}

		//�������ָ��ʧ��
		else
		{
			CString   str=_T("��ȡDll���ָ��Plug_CreateObjectʧ��");			
			AfxMessageBox(str);
		}
	}
	else
	{
		CString   str;
		str.Format(_T("���ض�̬��%sʧ��"),strDllPath);
		AfxMessageBox(str);
	}

	//�ͷŶ�̬����Դ
	BOOL  bFinish=FreeLibrary(hIns);

	return TRUE;
}


BOOL CDlgPlugExec::RunBtn(int nBtnIndex)
{

	//��ȡ��ǰ��Ҫ���صĶ�̬��·��
	CString   strDllPath=_T("");
	CString   strDllName=_T("");
	stDllInfo  *pDllInfo=((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.GetPlugInfo(nBtnIndex);

	if (pDllInfo==NULL)
	{
		return  FALSE;
	}

	strDllName=pDllInfo->strDllName;
	//���û�л�ȡ��dll�Ǿͷ���ʧ��
	if(_T("")==strDllName)
	{
		return  FALSE;
	}

	//��ȡ����·��
	strDllPath.Format(_T("%s\\%s"),((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath(),strDllName);

	//��ѯ�ļ��Ƿ����
	CFileFind  finder;
	if (!finder.FindFile(strDllPath))
	{
		return  FALSE;
	}

	//��ʼ����
	LoadDll(strDllPath,nBtnIndex);

	return TRUE;
}


LRESULT  CDlgPlugExec::OnSelfDefBtn(WPARAM  wParam, LPARAM  lParam)
{
	UINT   nID=(UINT)wParam;
	RunBtn(nID-IDC_BTN_DYNAMIC-1);

	return  0;
}