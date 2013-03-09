#pragma once
#include "EyeDetect_Interface.h"
#include "OpenCVImage.h"

typedef  std::vector<COpenCVImage *>   COpenCVImageVector;


//处像处理队列管理  
class CProcImageListAdmin
{
public:
	CProcImageListAdmin(void);
	~CProcImageListAdmin(void);
	
	BOOL   AddTailImage(CString  strImagePath);

	BOOL   RemoveAllImage();

	BOOL   DeleteImage(UINT  indexImage);

	IMGVECT  *  GetImageVector();		//导出IplImage的接口

public:
	CImageList   m_ImageIconList;
	CStringList  m_ImagePathList;
	boost::shared_ptr<COpenCVImageVector>   m_pOpenCVImageVector;

	BOOL AddIcon(CString strImagePath);	
	BOOL AddIcon(IplImage *pImage);
	BOOL AddIplImagePtr(CString strImagePath);
private:
	BOOL RemoveAllImageVector(void);
	boost::shared_ptr<IMGVECT>  m_pIplImageVect;
};

