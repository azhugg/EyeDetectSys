#pragma once

//作者：刘子青
//用途：主要用于OpenCV与MFC之间的交互

#include  "cv.h"
#include  "highgui.h"

class COpenCVImage
{
public:
	COpenCVImage(void);

	COpenCVImage(CString  imagePath);

	COpenCVImage(IplImage * pImage);

	~COpenCVImage(void);

	//获取OpenCV指针
	IplImage  *  GetOpenCVPtr();

	//加载图像
	BOOL   LoadImage(CString  strPath);

	//向DC显示图像(可以根据两个矩形的大小进行缩放平移显示)
	void  DrawImgtoHDC(HDC hDC, RECT srcImageRect, RECT destHDCRect);

	//向DC显示图像(全幅拉伸显示)
	void  DrawStrechImgtoHDC(HDC hDC, RECT destHDCRect);

	//IplImage转GDI+的Bitmap格式，本转换只是生成一个指针，并不拷贝内存
	Gdiplus::Bitmap *  IplImage2GDI(IplImage * pImage);


private:
	LPBITMAPINFO  CreateMapInfo(IplImage* workImg);
	IplImage      * m_pImage;
	LPBITMAPINFO  m_pBitmapInfo;	
};

