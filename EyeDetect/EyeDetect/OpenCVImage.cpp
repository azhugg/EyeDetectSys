#include "StdAfx.h"
#include "OpenCVImage.h"


extern CStringW CStrA2CStrW(const CStringA &cstrSrcA);
extern CStringA CStrW2CStrA(const CStringW &cstrSrcW);



COpenCVImage::COpenCVImage(void)
{
	m_pImage=NULL;
	m_pBitmapInfo=NULL;
}

//根据名称进行构造
COpenCVImage::COpenCVImage(CString  imagePath)
{
	m_pImage=NULL;
	m_pBitmapInfo=NULL;
	LoadImage(imagePath);
}

//利用IplImage创建
COpenCVImage::COpenCVImage(IplImage * pImage)
{
	m_pBitmapInfo=CreateMapInfo(pImage);
	cvFlip(pImage);
	m_pImage=pImage;
}

COpenCVImage::~COpenCVImage(void)
{
	if (m_pImage!=NULL)
	{
		OutputDebugString(_T("===释放内存m_pImage===\r\n"));
		cvReleaseImage(&m_pImage);
		m_pImage=NULL;
	}
	if (m_pBitmapInfo!=NULL)
	{
		OutputDebugString(_T("===释放内存m_pBitmapInfo===\r\n"));
		free(m_pBitmapInfo);
		m_pBitmapInfo=NULL;
	}
}

IplImage  *  COpenCVImage::GetOpenCVPtr()
{
	return  m_pImage;
}

BOOL   COpenCVImage::LoadImage(CString  strPath)
{

//如果是Unicode编码则需要以下转换
#ifdef _UNICODE
	CStringA  str=CStrW2CStrA(strPath);
	IplImage *pImage=cvLoadImage(str);
	if (pImage!=NULL)//证明载入成功
	{
		if (m_pImage!=NULL)
		{
			cvReleaseImage(&m_pImage);
			m_pImage=NULL;
		}

		m_pBitmapInfo=CreateMapInfo(pImage);

		cvFlip(pImage);
		m_pImage=pImage;		
		return  TRUE;
	}
	else//证明载入失败
	{
		return FALSE;
	}
#endif
	return  TRUE;
}

LPBITMAPINFO  COpenCVImage::CreateMapInfo(IplImage* workImg)
{
	if (m_pBitmapInfo!=NULL)
	{
		free(m_pBitmapInfo);
		m_pBitmapInfo=NULL;
	}

	BITMAPINFOHEADER  BIH={40,1,1,1,8,0,0,0,0,0,0};
	LPBITMAPINFO lpBmi;
	int          wid, hei, bits, colors,i;	

	RGBQUAD  ColorTab[256];
	wid =workImg->width;    
	hei =workImg->height;
	bits=workImg->depth*workImg->nChannels;

	if (bits>8) 
		colors=0;
	else 
		colors=1<<bits;

	lpBmi=(LPBITMAPINFO)malloc(40+4*colors);
	BIH.biWidth=wid;     
	BIH.biHeight  =hei;
	BIH.biBitCount=(BYTE) bits;
	memcpy(lpBmi,&BIH,40);                   //  复制位图信息头
	if (bits==8) 
	{                           //  256 色位图
		for (i=0;i<256;i++)  
		{                //  设置灰阶调色板
			ColorTab[i].rgbRed=ColorTab[i].rgbGreen=ColorTab[i].rgbBlue=(BYTE) i;
		}
		memcpy(lpBmi->bmiColors, ColorTab, 1024);
	}	

	return(lpBmi);
}



void COpenCVImage::DrawImgtoHDC(HDC hDC, RECT srcImageRect, RECT destHDCRect)
{
	ASSERT(hDC);
	if (m_pImage!=NULL && m_pBitmapInfo!=NULL)
	{
		::SetStretchBltMode(hDC,COLORONCOLOR);
		::StretchDIBits(hDC,destHDCRect.left, destHDCRect.top,destHDCRect.right-destHDCRect.left,destHDCRect.bottom-destHDCRect.top,
			srcImageRect.left,srcImageRect.top,srcImageRect.right-srcImageRect.left,srcImageRect.bottom-srcImageRect.top,
			m_pImage->imageData,m_pBitmapInfo,DIB_RGB_COLORS, SRCCOPY);
	}

}

void  COpenCVImage::DrawStrechImgtoHDC(HDC hDC, RECT destHDCRect)
{
	ASSERT(hDC);
	if (m_pImage!=NULL && m_pBitmapInfo!=NULL)
	{
		int   imageWidth = m_pImage->width;
		int   imageHeight= m_pImage->height;
		::SetStretchBltMode(hDC,COLORONCOLOR);
		::StretchDIBits(hDC,destHDCRect.left, destHDCRect.top,destHDCRect.right-destHDCRect.left,destHDCRect.bottom-destHDCRect.top,
			0,0,imageWidth,imageHeight,
			m_pImage->imageData,m_pBitmapInfo,DIB_RGB_COLORS, SRCCOPY);
	}
}

//获取IplImage的指针
Gdiplus::Bitmap *  COpenCVImage::IplImage2GDI(IplImage * pImage)
{

	CreateMapInfo(pImage);
	//24位图和8位图的BITMAPINFO是固定的，要提前创建好，一次即可
	Gdiplus::Bitmap*  pBitmap = Gdiplus::Bitmap::FromBITMAPINFO(m_pBitmapInfo,
															pImage->imageData);

	return  pBitmap;
}
