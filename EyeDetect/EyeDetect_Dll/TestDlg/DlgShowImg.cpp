// DlgShowImg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDlg.h"
#include "DlgShowImg.h"
#include "afxdialogex.h"
#include "OpenCVImage.h"


// CDlgShowImg �Ի���

IMPLEMENT_DYNAMIC(CDlgShowImg, CDialogEx)

CDlgShowImg::CDlgShowImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowImg::IDD, pParent),m_pImgVect(NULL),m_indexImg(0),m_WndRect(0,0,0,0)
{
	m_pOutImgVect=NULL;
	m_pOutImgVect=new IMGVECT;
	m_strFolderPath=_T("");
}

CDlgShowImg::~CDlgShowImg()
{
	if (!m_pOutImgVect->empty())
	{
		while (!m_pOutImgVect->empty())
		{
			m_pOutImgVect->pop_back();
		}
	}

	delete  m_pOutImgVect;
	m_pOutImgVect=NULL;
}

void CDlgShowImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowImg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_DISP, &CDlgShowImg::OnBnClickedBtnDisp)
	ON_BN_CLICKED(IDC_BTN_DISPNEXT, &CDlgShowImg::OnBnClickedBtnDispnext)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgShowImg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgShowImg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDlgShowImg ��Ϣ�������


void CDlgShowImg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	
}


BOOL CDlgShowImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ���������������ճ�ʼ�����ν�������
	if((m_WndRect.Width()>200) && (m_WndRect.Height()>200))
	{
		MoveWindow(m_WndRect);

		CRect   rcRect(0,0,0,0);
		GetClientRect(rcRect);
		//�ƶ�ͼ����ʾ��
		CRect  Disprect(0,0,0,0);
		Disprect.left=rcRect.left;
		Disprect.top=rcRect.top;
		Disprect.right=rcRect.right-150;
		Disprect.bottom=rcRect.bottom;
		GetDlgItem(IDC_STATIC_IMG)->MoveWindow(Disprect);

		CRect   Btnrect(0,0,0,0);
		Btnrect.left=rcRect.right-140;
		Btnrect.right=rcRect.right-10;
		Btnrect.top=Disprect.top;
		Btnrect.bottom=Btnrect.top+40;
		GetDlgItem(IDC_BTN_DISP)->MoveWindow(Btnrect);

		Btnrect.top+=50;
		Btnrect.bottom+=50;
		GetDlgItem(IDC_BTN_DISPNEXT)->MoveWindow(Btnrect);

		Btnrect.top+=50;
		Btnrect.bottom+=50;
		GetDlgItem(IDC_BTN_DISPNEXT)->MoveWindow(Btnrect);

		Btnrect.top+=50;
		Btnrect.bottom+=50;
		GetDlgItem(IDC_BUTTON3)->MoveWindow(Btnrect);

		Btnrect.top+=50;
		Btnrect.bottom+=50;
		GetDlgItem(IDC_BUTTON6)->MoveWindow(Btnrect);

		Btnrect.top+=50;
		Btnrect.bottom+=50;
		GetDlgItem(IDOK)->MoveWindow(Btnrect);

		Btnrect.top+=50;
		Btnrect.bottom+=50;
		GetDlgItem(IDCANCEL)->MoveWindow(Btnrect);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgShowImg::OnBnClickedBtnDisp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pImgVect!=NULL)
	{
		if (m_pImgVect->size()>0)
		{
			m_indexImg=0;
			IMGVECT::iterator  ind=(*m_pImgVect).begin();
			IplImage  *temp=(*ind);

			COpenCVImage  image(temp);
			HDC  hDC=GetDlgItem(IDC_STATIC_IMG)->GetDC()->GetSafeHdc();	

			if (hDC!=NULL)
			{
				CRect  rect;
				GetDlgItem(IDC_STATIC_IMG)->GetClientRect(rect);

				RECT  HDCRect;
				HDCRect.left=rect.left;
				HDCRect.top=rect.top;
				HDCRect.right=rect.right;
				HDCRect.bottom=rect.bottom;

				image.DrawStrechImgtoHDC(hDC, HDCRect);
			}
		}
	}
}


void CDlgShowImg::OnBnClickedBtnDispnext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pImgVect!=NULL)
	{
		int   Cout=m_pImgVect->size();
		CString   str;
		str.Format(_T("===�ܹ�ͼƬ������:%d,��ǰ��ʾ��%d��===\r\n"),Cout, m_indexImg);

		if (m_pImgVect->size()>0&&(m_pImgVect->size()>=(m_indexImg+1)))
		{
			//IMGVECT::iterator  ind=(*m_pImgVect).begin();
			IplImage  *temp=(*m_pImgVect)[m_indexImg];

			COpenCVImage  image(temp);
			HDC  hDC=GetDlgItem(IDC_STATIC_IMG)->GetDC()->GetSafeHdc();	
			
			boost::shared_ptr<COpenCVImage>  pGrayImg(new COpenCVImage);
			pGrayImg->Color2Gray(temp);

			if (hDC!=NULL)
			{
				CRect  rect;
				GetDlgItem(IDC_STATIC_IMG)->GetClientRect(rect);

				RECT  HDCRect;
				HDCRect.left=rect.left;
				HDCRect.top=rect.top;
				HDCRect.right=rect.right;
				HDCRect.bottom=rect.bottom;

				pGrayImg->DrawStrechImgtoHDC(hDC, HDCRect);

				LPIPLIMAGE  pOut=pGrayImg->GetOpenCVPtr();
				m_pOutImgVect->push_back(pOut);
				if (m_strFolderPath!=_T(""))
				{
					CString   str;
					str.Format(_T("%s\\%d.bmp"),m_strFolderPath,m_pOutImgVect->size());
					pGrayImg->SaveImage(str);
				}				
				
			}
			m_indexImg++;
		}
	}



}


BOOL CDlgShowImg::SetInputImgVector(IMGVECT * pImgVect)
{
	m_pImgVect = pImgVect;
	return TRUE;
}

//���öԻ����С
BOOL CDlgShowImg::SetDlgSize(RECT rcRect)
{
	m_WndRect.left = rcRect.left;
	m_WndRect.top=rcRect.top;
	m_WndRect.right=rcRect.right;
	m_WndRect.bottom=rcRect.bottom;

	return TRUE;
}


void CDlgShowImg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgShowImg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
