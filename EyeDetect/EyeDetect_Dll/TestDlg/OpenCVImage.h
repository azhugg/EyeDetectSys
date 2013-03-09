#pragma once

//���ߣ�������
//��;����Ҫ����OpenCV��MFC֮��Ľ���

#include  "cv.h"
#include  "highgui.h"

typedef   IplImage *      LPIPLIMAGE;

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

	//��ͼ�񴫽���ת��Ϊ�Ҷ�ͼ
	void  Color2Gray(IplImage * pSrcImage);

	//ǿ��ת������������COpenCVImageתΪIplImage��ָ��
	operator  LPIPLIMAGE();

	//����ͼƬ��ĳһ��ָ��λ��
	BOOL  SaveImage(const CString  StrImgFile);

private:
	LPBITMAPINFO  CreateMapInfo(IplImage* workImg);
	IplImage      * m_pImage;
	LPBITMAPINFO  m_pBitmapInfo;	
	UINT          m_TypeCreate;
};

