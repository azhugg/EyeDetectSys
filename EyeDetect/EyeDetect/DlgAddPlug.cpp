// DlgAddPlug.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgAddPlug.h"
#include "afxdialogex.h"
#include "XUnzip.h"
#include "XZip.h"
#include "PlugInfoData.h"


// CDlgAddPlug �Ի���

IMPLEMENT_DYNAMIC(CDlgAddPlug, CDialogEx)

CDlgAddPlug::CDlgAddPlug(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddPlug::IDD, pParent),m_strFile(_T("")),m_pPlugFile(new stPlugfile)
{
	m_pPlugFile->strBmpFile=_T("");
	m_pPlugFile->strDllFile=_T("");
	m_pPlugFile->strINIFile=_T("");
}

CDlgAddPlug::~CDlgAddPlug()
{

}

void CDlgAddPlug::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAddPlug, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FINDPLUG, &CDlgAddPlug::OnBnClickedBtnFindplug)
	ON_BN_CLICKED(IDOK, &CDlgAddPlug::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddPlug::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgAddPlug ��Ϣ�������

//���Ҳ������λ��
void CDlgAddPlug::OnBnClickedBtnFindplug()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���Ҳ������λ��
	CFileDialog  dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					_T("ZipFile (*.plug)|*.plug||"));
	if(IDOK==dlg.DoModal())
	{
		GetDlgItem(IDC_EDIT_PLUGPATH)->SetWindowText(dlg.GetPathName());
		GetZipFileInfo(dlg.GetPathName());
		m_strFile=dlg.GetPathName();
	}
}

//�Բ���ļ��н��н�ѹ��
BOOL  CDlgAddPlug::GetZipFileInfo(CString  strZipFile)
{
#ifdef _UNICODE
	ZIPENTRYW ze;
#else
	ZIPENTRY ze; 
#endif

	TCHAR   *pSrcChar=new  TCHAR[255];
	memset(pSrcChar,0,sizeof(TCHAR)*255);
	memcpy(pSrcChar,strZipFile.GetBuffer(strZipFile.GetLength()),strZipFile.GetLength()*sizeof(TCHAR));

	HZIP hz = OpenZip(pSrcChar, 0, ZIP_FILENAME);

	if (hz)
	{
		GetZipItem(hz,-1,&ze);
		int  numitems = ze.index;
		
		for(int i=0; i<numitems; i++)
		{
			GetZipItem(hz,i,&ze);
			CString   str;
			str.Format(_T("%s"),ze.name);

			//ͼ���ļ���ʾ
			if (str.Right(3)==_T("bmp")||str.Right(3)==_T("png"))
			{
				GetDlgItem(IDC_EDIT_PLUGICON)->SetWindowText(str);

				CString  strTemp;
				strTemp.Format(_T("C:\\%s"),str);

				TCHAR  * pTemp = new TCHAR[255];
				memset(pTemp,0,sizeof(TCHAR)*255);

				memcpy(pTemp,strTemp.GetBuffer(strTemp.GetLength()),strTemp.GetLength()*sizeof(TCHAR));
				if(UnzipItem(hz,i,pTemp,0,ZIP_FILENAME)==ZR_OK)
				{
					m_pPlugFile->strBmpFile=strTemp;
				}
				else
				{
					m_pPlugFile->strBmpFile=_T("");
				}

				delete []pTemp;
				pTemp=NULL;
			}
			//��̬���ļ�
			else if(str.Right(3)==_T("dll"))
			{
				GetDlgItem(IDC_EDIT_DLLNAME)->SetWindowText(str);

				CString  strTemp;
				strTemp.Format(_T("C:\\%s"),str);

				TCHAR  * pTemp = new TCHAR[255];
				memset(pTemp,0,sizeof(TCHAR)*255);

				memcpy(pTemp,strTemp.GetBuffer(strTemp.GetLength()),strTemp.GetLength()*sizeof(TCHAR));
				if(UnzipItem(hz,i,pTemp,0,ZIP_FILENAME)==ZR_OK)
				{
					m_pPlugFile->strDllFile=strTemp;
				}
				else
				{
					m_pPlugFile->strDllFile=_T("");
				}

				delete []pTemp;
				pTemp=NULL;
			}
			//�����ļ�
			else if (str.Right(3)==_T("ini")|| str.Right(3)==_T("xml"))
			{
				GetDlgItem(IDC_EDIT_CONFIG)->SetWindowText(str);

				CString  strTemp;
				strTemp.Format(_T("C:\\%s"),str);

				TCHAR  * pTemp = new TCHAR[255];
				memset(pTemp,0,sizeof(TCHAR)*255);

				memcpy(pTemp,strTemp.GetBuffer(strTemp.GetLength()),strTemp.GetLength()*sizeof(TCHAR));
				if(UnzipItem(hz,i,pTemp,0,ZIP_FILENAME)==ZR_OK)
				{
					m_pPlugFile->strINIFile=strTemp;
				}
				else
				{
					m_pPlugFile->strINIFile=_T("");
				}

				delete []pTemp;
				pTemp=NULL;
			}

		
		
		}
	}

	CloseZip(hz);

	delete  []pSrcChar;
	pSrcChar=NULL;


	return TRUE;
}

//���ȷ��֮����Ҫ��xml�ļ��м�¼�����Ϣ�����ҿ�������
void CDlgAddPlug::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����д����Ϣ�Ƿ�����������ͬʱ��дstDllInfo
	boost::shared_ptr<stDllInfo>  pDllInfo(new stDllInfo);
	CString  strName=_T("");
	GetDlgItem(IDC_EDIT_BTNNAME)->GetWindowText(strName);
	if (strName!=_T(""))
	{
		pDllInfo->strBtnText=strName;
	}
	else
	{
		AfxMessageBox(_T("�������û����д"));
		return ;
	}

	strName=_T("");
	GetDlgItem(IDC_EDIT_COMMENT)->GetWindowText(strName);
	if (strName!=_T(""))
	{
		pDllInfo->strDllComment=strName;
	}
	else
	{
		AfxMessageBox(_T("û����дע��"));
		return ;
	}	
	pDllInfo->nDllType=1;

	GetDlgItem(IDC_EDIT_CONFIG)->GetWindowText(strName);
	if (strName!=_T(""))
	{
		pDllInfo->strINIFile=strName;
	}
	else
	{
		AfxMessageBox(_T("û��ѡ���κ����"));
		return  ;
	}

	GetDlgItem(IDC_EDIT_DLLNAME)->GetWindowText(strName);
	if (strName!=_T(""))
	{
		pDllInfo->strDllName=strName;
	}
	else
	{
		AfxMessageBox(_T("û��ѡ���κ����"));
		return  ;
	}

	GetDlgItem(IDC_EDIT_PLUGICON)->GetWindowText(strName);
	if (strName!=_T(""))
	{
		pDllInfo->strBmpSrc=strName;
	}
	else
	{
		AfxMessageBox(_T("û��ѡ���κ����"));
		return  ;
	}

	//���ݴ���ļ�����ֲָ��λ��
	//����ͼƬ�ļ�
	if (m_pPlugFile->strBmpFile!=_T(""))
	{
		CString  str=((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath();
		CString  destStr;
		int Pos=m_pPlugFile->strBmpFile.ReverseFind(_T('\\'));
		int Length=m_pPlugFile->strBmpFile.GetLength();
		CString str1=m_pPlugFile->strBmpFile.Right(Length-Pos-1);
		destStr.Format(_T("%s\\Resource\\%s"),str,str1);
		MoveFile(m_pPlugFile->strBmpFile,destStr);

	}
	//���涯̬���ļ�
	if (m_pPlugFile->strDllFile!=_T(""))
	{
		CString  str=((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath();
		CString  destStr;
		int Pos=m_pPlugFile->strDllFile.ReverseFind(_T('\\'));
		int Length=m_pPlugFile->strDllFile.GetLength();
		CString str1=m_pPlugFile->strDllFile.Right(Length-Pos-1);
		destStr.Format(_T("%s\\%s"),str,str1);
		MoveFile(m_pPlugFile->strDllFile,destStr);
	}
	//���������ļ�
	if (m_pPlugFile->strINIFile!=_T(""))
	{
		CString  str=((CEyeDetectApp*)AfxGetApp())->m_sysFileSet.GetAppPath();
		CString  destStr;
		int Pos=m_pPlugFile->strINIFile.ReverseFind(_T('\\'));
		int Length=m_pPlugFile->strINIFile.GetLength();
		CString str1=m_pPlugFile->strINIFile.Right(Length-Pos-1);
		destStr.Format(_T("%s\\Config\\%s"),str,str1);
		MoveFile(m_pPlugFile->strINIFile,destStr);
	}
	//����dll��Ϣ��ӽ�PluginfoData
	((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.AddPlug(*(pDllInfo.get()));

	//��������CListCtrl
	((CEyeDetectApp*)AfxGetApp())->m_PlugInfo.ReloadPlug();

	//���°�ť�б�
	theAppPtr.GetAppMainFrmPtr()->m_PlugDockPane.m_DlgPlugExec.RelayButton();

	CDialogEx::OnOK();
}


BOOL CDlgAddPlug::MoveFile(CString strSrcFilePath , CString strDestFilePath)
{
	TCHAR   *pSrcChar=new  TCHAR[255];
	memset(pSrcChar,0,sizeof(TCHAR)*255);
	memcpy(pSrcChar,strSrcFilePath.GetBuffer(strSrcFilePath.GetLength()),strSrcFilePath.GetLength()*sizeof(TCHAR));

	TCHAR   *pDestChar=new  TCHAR[255];
	memset(pDestChar,0,sizeof(TCHAR)*255);
	memcpy(pDestChar,strDestFilePath.GetBuffer(strDestFilePath.GetLength()),strDestFilePath.GetLength()*sizeof(TCHAR));

	SHFILEOPSTRUCT  FileOp={0};
	FileOp.fFlags = FOF_NOCONFIRMATION| FOF_SILENT;
	FileOp.pFrom=pSrcChar;
	FileOp.pTo=pDestChar;

	FileOp.wFunc=FO_MOVE;

	int  res=SHFileOperation(&FileOp);

	delete  []pDestChar;
	pDestChar=NULL;

	delete  []pSrcChar;
	pSrcChar=NULL;

	return  res==0;	
}


BOOL CDlgAddPlug::DeleteFile(CString strSrcFilePath)
{
	TCHAR   *pSrcChar=new  TCHAR[255];
	memset(pSrcChar,0,sizeof(TCHAR)*255);
	memcpy(pSrcChar,strSrcFilePath.GetBuffer(strSrcFilePath.GetLength()),strSrcFilePath.GetLength()*sizeof(TCHAR));

	SHFILEOPSTRUCT  FileOp={0};
	FileOp.fFlags = FOF_NOCONFIRMATION| FOF_SILENT;
	FileOp.pFrom=pSrcChar;
	FileOp.pTo=NULL;

	FileOp.wFunc=FO_DELETE;

	int  res=SHFileOperation(&FileOp);

	delete  []pSrcChar;
	pSrcChar=NULL;

	return  res==0;	
}


void CDlgAddPlug::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pPlugFile->strBmpFile!=_T(""))
	{
		DeleteFile(m_pPlugFile->strBmpFile);
	}
	if (m_pPlugFile->strDllFile!=_T(""))
	{
		DeleteFile(m_pPlugFile->strDllFile);
	}
	if (m_pPlugFile->strINIFile!=_T(""))
	{
		DeleteFile(m_pPlugFile->strINIFile);
	}	

	CDialogEx::OnCancel();
}


BOOL CDlgAddPlug::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT_BTNNAME)->SetWindowText(_T("��ť����"));
	GetDlgItem(IDC_EDIT_COMMENT)->SetWindowText(_T("<��������������˵��>"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
