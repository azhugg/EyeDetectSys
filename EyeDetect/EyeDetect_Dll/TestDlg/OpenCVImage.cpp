#include "StdAfx.h"
#include "OpenCVImage.h"


CStringW CStrA2CStrW(const CStringA &cstrSrcA)
{
	int len = MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len];
	memset(wstr, 0, len*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, wstr, len);
	CStringW cstrDestW = wstr;
	delete[] wstr;

	return cstrDestW;
}

CStringA CStrW2CStrA(const CStringW &cstrSrcW)
{
	int len = WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, NULL, 0, NULL, NULL);
	char *str = new char[len];
	memset(str, 0, len);
	WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, str, len, NULL, NULL);
	CStringA cstrDestA = str;
	delete[] str;

	return cstrDestA;
}

COpenCVImage::COpenCVImage(void):m_TypeCreate(0)
{
	m_pImage=NULL;
	m_pBitmapInfo=NULL;
}

//根据名称进行构造
COpenCVImage::COpenCVImage(CString  imagePath):m_TypeCreate(0)
{
	LoadImage(imagePath);
}

COpenCVImage::COpenCVImage(IplImage * pImage):m_TypeCreate(1)
{
	m_pBitmapInfo=NULL;
	m_pBitmapInfo=CreateMapInfo(pImage);
	m_pImage=pImage;
}


COpenCVImage::~COpenCVImage(void)
{
	if (m_pImage!=NULL && 0==m_TypeCreate)
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

//彩色图变成灰度图
void  COpenCVImage::Color2Gray(IplImage * pSrcImage)
{
	//如果不是三通道真彩图则退出
	if (pSrcImage->nChannels!=3)
	{
		return;
	}

	if (m_pImage!=NULL && 0==m_TypeCreate)
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

	m_pImage=cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U,1 );
	cvCvtColor(pSrcImage,m_pImage,CV_RGB2GRAY);

	//腐蚀膨胀方式
	//IplConvKernel *element =0;
	//element = cvCreateStructuringElementEx( 8, 8, 1, 1, CV_SHAPE_ELLIPSE, 0);
	//cvErode( m_pImage, m_pImage, element, 5);
	//cvDilate( m_pImage, m_pImage, element, 5);	
	
	m_pBitmapInfo=CreateMapInfo(m_pImage);

}

COpenCVImage::operator LPIPLIMAGE()
{
	OutputDebugString(_T("===jinru===\r\n"));
	if (m_pImage==NULL||m_pBitmapInfo==NULL)
	{
		return NULL;
	}
	if (m_pBitmapInfo!=NULL)
	{
		OutputDebugString(_T("===释放内存m_pBitmapInfo===\r\n"));
		free(m_pBitmapInfo);
		m_pBitmapInfo=NULL;
	}
	
	return   m_pImage;
}

BOOL  COpenCVImage::SaveImage(const CString  StrImgFile)
{
	CStringA   str;
	str=CStrW2CStrA(StrImgFile);
	
	if (m_pImage!=NULL)
	{
		cvSaveImage(str,m_pImage);
	}

	return   TRUE;
}