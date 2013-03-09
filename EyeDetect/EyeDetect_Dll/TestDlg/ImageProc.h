#pragma once
#include "e:\practise\eyedetect\eyedetect\eyedetect_interface.h"
#include "resource.h"
#include "DlgShowImg.h"

class CImageProc :
	public IImageProc
{
public:
	CImageProc(void);
	~CImageProc(void);
	HICON   GetIcon(); 					 	//加载一个图标
	DWORD   ShowDlg();  						//显示对话框
	DWORD   LoadIplImagePtr(IMGVECT * pInputImg);                  //加载图像
	DWORD   SetDlgRect(const RECT rcDlg);

	//2013年2月17日添加
	DWORD  SetDefaultFolder(const CString strFolder); //设置缺省文件夹，用于暂时存储处理结果图片
	DWORD  GetProcImageCount(); //获取处理后的图像计数

	DWORD  SetPlugConfigFile(const CString strFilePath);//设置插件的配置文件路径
	DWORD  GetPlugUUID(CString& strUUID);  //获取该控件的UUID号码(该号码遵循GPL标准)	

private:
	HICON   m_hIcon;
	boost::shared_ptr<CDlgShowImg>   m_pDlgShowImg;              //显示图片的对话框

};

