#pragma once
//����ͼ������й���
class CLoadImageListAdmin
{
public:
	CLoadImageListAdmin(void);

	~CLoadImageListAdmin(void);

	BOOL LoadImage(CString   strFolder);

	CStringList    m_strImagePathList;  //ͼƬȫ·��
	CImageList     m_ImageIconList;		//ͼ���б�

private:	

public:
	BOOL LoadIcon(CString strImgPath);
private:
	BOOL m_IsLoadedIcon;
};

