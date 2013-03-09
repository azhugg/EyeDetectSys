#include "StdAfx.h"
#include "ProcImageListAdmin.h"
#include "OpenCVImage.h"



CProcImageListAdmin::CProcImageListAdmin(void):m_pOpenCVImageVector(new COpenCVImageVector),
												m_pIplImageVect(new IMGVECT)
{
	m_ImageIconList.Create(120,120,ILC_COLORDDB|ILC_COLOR32,1,1);	
}


CProcImageListAdmin::~CProcImageListAdmin(void)
{
	//释放资源
	if (!m_pOpenCVImageVector->empty())
	{
		while(!m_pOpenCVImageVector->empty())
		{
			int  m=m_pOpenCVImageVector->size();
			COpenCVImage *pImage=(*m_pOpenCVImageVector)[m-1];
			delete  pImage;
			m_pOpenCVImageVector->pop_back();
		}
	}	
}


BOOL   CProcImageListAdmin::AddTailImage(CString  strImagePath)
{
	//添加图片路径
	m_ImagePathList.AddTail(strImagePath);
	AddIcon(strImagePath);
	AddIplImagePtr(strImagePath);
	
	return  FALSE;
}
BOOL   CProcImageListAdmin::RemoveAllImage()
{
	m_ImageIconList.DeleteImageList();
	m_ImageIconList.Create(120,120,ILC_COLORDDB|ILC_COLOR32,1,1);

	m_ImagePathList.RemoveAll();

	RemoveAllImageVector();


	return   FALSE;
}
BOOL   CProcImageListAdmin::DeleteImage(UINT  indexImage)
{
	return  FALSE;
}


BOOL CProcImageListAdmin::AddIcon(CString strImagePath)
{
	Gdiplus::Image Img(strImagePath);
	int   srcWidth=Img.GetWidth();
	int   srcHeight=Img.GetHeight();

	Gdiplus::Bitmap * IconBmp=(Gdiplus::Bitmap *)Img.GetThumbnailImage(120,120,NULL,NULL);
	HBITMAP   hBmp;
	IconBmp->GetHBITMAP(Gdiplus::Color(255,255,255),&hBmp);

	CBitmap  *pImage=CBitmap::FromHandle(hBmp);
	int  Index=m_ImageIconList.Add(pImage,RGB(255,255,255));

	return TRUE;
}

BOOL  CProcImageListAdmin::AddIcon(IplImage *pImage)
{
	return  TRUE;
}


//将图片添加到处理队列
BOOL CProcImageListAdmin::AddIplImagePtr(CString strImagePath)
{
	//获取Image
	COpenCVImage*  pImage=new COpenCVImage(strImagePath);
	m_pOpenCVImageVector->push_back(pImage);

	return  TRUE;
	
}
//处理队列的IplImage队列
IMGVECT  *  CProcImageListAdmin::GetImageVector()
{
	m_pIplImageVect.reset(new IMGVECT);
	COpenCVImageVector::iterator  ImgIndex=m_pOpenCVImageVector->begin();

	for (ImgIndex;ImgIndex!= m_pOpenCVImageVector->end(); ImgIndex++)
	{
		IplImage * pTemp=(*ImgIndex)->GetOpenCVPtr();
		m_pIplImageVect->push_back(pTemp);
	}

	return   m_pIplImageVect.get();
}


BOOL CProcImageListAdmin::RemoveAllImageVector(void)
{

	while (!m_pOpenCVImageVector->empty())
	{
		COpenCVImage *pImag=m_pOpenCVImageVector->back();
		delete  pImag;
		pImag=NULL;
		m_pOpenCVImageVector->pop_back();
	}
	return TRUE;
}
