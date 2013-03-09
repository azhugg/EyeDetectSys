#include "StdAfx.h"
#include "LoadImageListAdmin.h"
#include "AppPtrManage.h"


CLoadImageListAdmin::CLoadImageListAdmin(void)
	: m_IsLoadedIcon(FALSE)
{
	m_ImageIconList.Create(150,150,ILC_COLORDDB|ILC_COLOR32,1,1);

}


CLoadImageListAdmin::~CLoadImageListAdmin(void)
{

}

//根据文件夹的路径载入图片的路径
BOOL CLoadImageListAdmin::LoadImage(CString   strFolder)
{
	CString  str=strFolder+_T("\\*.*");

	CFileFind  finder;
	BOOL  bWork=finder.FindFile(str);
	int   i=0;

	while(bWork)
	{
		bWork=finder.FindNextFile();
		if (!finder.IsDirectory())
		{
			CString   FileName= finder.GetFilePath();//Name();
			int  Pos=FileName.ReverseFind(_T('.'));
			if (Pos!=-1)
			{
				CString ExtendName=FileName.Right(FileName.GetLength()-Pos-1);
				//支持JPG格式
				if (ExtendName==_T("jpg")|| ExtendName==_T("tif"))
				{
					//当该文件夹下有图片时卸载原来加载的
					if (0==i && m_IsLoadedIcon)
					{
						m_ImageIconList.DeleteImageList();
						m_ImageIconList.Create(150,150,ILC_COLORDDB|ILC_COLOR32,1,1);
						m_strImagePathList.RemoveAll();
					}
					
					i++;
					m_IsLoadedIcon = TRUE;
					m_strImagePathList.AddTail(FileName);
					LoadIcon(FileName);
				}
			}
		}
	
	}	

	theAppPtr.GetAppViewPtr()->ShowLoadImage();
	
	return FALSE;
}


BOOL CLoadImageListAdmin::LoadIcon(CString strImgPath)
{	
	Gdiplus::Image Img(strImgPath);
	int   srcWidth=Img.GetWidth();
	int   srcHeight=Img.GetHeight();

	Gdiplus::Bitmap * IconBmp=(Gdiplus::Bitmap *)Img.GetThumbnailImage(150,150,NULL,NULL);
	HBITMAP   hBmp;
	IconBmp->GetHBITMAP(Gdiplus::Color(255,255,255),&hBmp);

	CBitmap  *pImage=CBitmap::FromHandle(hBmp);
	int  Index=m_ImageIconList.Add(pImage,RGB(255,255,255));

	return TRUE;
}
