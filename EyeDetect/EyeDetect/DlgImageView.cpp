// DlgImageView.cpp : 实现文件
//

#include "stdafx.h"
#include "EyeDetect.h"
#include "DlgImageView.h"
#include "afxdialogex.h"
//#include  "highgui.h"

#include "OpenCVImage.h"


// CDlgImageView 对话框

IMPLEMENT_DYNAMIC(CDlgImageView, CDialogEx)

CDlgImageView::CDlgImageView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgImageView::IDD, pParent)
{
	m_strImagePath=_T("");
}

CDlgImageView::~CDlgImageView()
{
}

void CDlgImageView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImageView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImageView 消息处理程序


BOOL CDlgImageView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HDC hDesktopDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	int xScrn = GetDeviceCaps(hDesktopDC, HORZRES);
	int yScrn = GetDeviceCaps(hDesktopDC, VERTRES);
	MoveWindow(0, 0, yScrn, yScrn);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgImageView::SetImagePath(CString strImagePath)
{
	m_strImagePath = strImagePath;
	return 0;
}


void CDlgImageView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	if(m_strImagePath!=_T(""))
	{
		HDC  hDC=dc.GetSafeHdc();
		CRect  rect;
		GetClientRect(rect);

		COpenCVImage  image;
		image.LoadImage(m_strImagePath);
		RECT  HDCRect;
		HDCRect.left=rect.left;
		HDCRect.top=rect.top;
		HDCRect.right=rect.right;
		HDCRect.bottom=rect.bottom;

		image.DrawStrechImgtoHDC(hDC, HDCRect);

	
/*		Gdiplus::Image  img(m_strImagePath);
		Gdiplus::Graphics  graph(hDC);

		graph.Clear(Gdiplus::Color(255,255,255));

		Gdiplus::Rect  rectF(rect.left,rect.top,rect.right,rect.bottom);
		graph.DrawImage(&img,rectF);

		Gdiplus::Pen  pen(Gdiplus::Color(0,255,0),2);
		graph.DrawLine(&pen,Gdiplus::Point(rect.left,rect.top+rect.Height()/2),
							Gdiplus::Point(rect.right,rect.top+rect.Height()/2));

		graph.DrawLine(&pen,Gdiplus::Point(rect.left+rect.Width()/2,rect.top),
							Gdiplus::Point(rect.left+rect.Width()/2,rect.bottom));	*/	


	}
}
