#pragma once

//���ߣ�������
//��;����Ҫ����OpenCV��MFC֮��Ľ���

#include  "cv.h"
#include  "highgui.h"

class COpenCVImage
{
public:
	COpenCVImage(void);

	COpenCVImage(CString  imagePath);

	COpenCVImage(IplImage * pImage);

	~COpenCVImage(void);

	//��ȡOpenCVָ��
	IplImage  *  GetOpenCVPtr();

	//����ͼ��
	BOOL   LoadImage(CString  strPath);

	//��DC��ʾͼ��(���Ը����������εĴ�С��������ƽ����ʾ)
	void  DrawImgtoHDC(HDC hDC, RECT srcImageRect, RECT destHDCRect);

	//��DC��ʾͼ��(ȫ��������ʾ)
	void  DrawStrechImgtoHDC(HDC hDC, RECT destHDCRect);

	//IplImageתGDI+��Bitmap��ʽ����ת��ֻ������һ��ָ�룬���������ڴ�
	Gdiplus::Bitmap *  IplImage2GDI(IplImage * pImage);


private:
	LPBITMAPINFO  CreateMapInfo(IplImage* workImg);
	IplImage      * m_pImage;
	LPBITMAPINFO  m_pBitmapInfo;	
};

