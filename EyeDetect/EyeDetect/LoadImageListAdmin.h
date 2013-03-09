#pragma once
//加载图像的序列管理
class CLoadImageListAdmin
{
public:
	CLoadImageListAdmin(void);

	~CLoadImageListAdmin(void);

	BOOL LoadImage(CString   strFolder);

	CStringList    m_strImagePathList;  //图片全路径
	CImageList     m_ImageIconList;		//图标列表

private:	

public:
	BOOL LoadIcon(CString strImgPath);
private:
	BOOL m_IsLoadedIcon;
};

