#ifndef   EYEDETECT_INTERFACE_123456
#define   EYEDETECT_INTERFACE_123456
//接口文件，所有处理类都应当派生于此类
//使用的OpenCV版本:OpenCV 1.0(请勿使用其他版本)
//作者：刘子青
//说明：接口主要用于主程序与图像处理动态库插件之间的连接
//日期：2013年1月28日
//版本：1.0.0.0
//注意事项：1.每次发布新版本的接口，各个动态库要注意更新
//			2.本接口需要STL与openCV的支持，具体在工程中如何设置这
//			  两种库，请参考其他资料

#include  "cv.h"
#include  "highgui.h"
#include  <vector>

typedef  std::vector<IplImage *>    IMGVECT;						//图像处理序列
typedef BOOL (WINAPI * PFN_Plug_CreateObject)(void ** pobj);     //创建对象
typedef BOOL (WINAPI * PFN_Plug_DestroyObject)();				//释放对象

class   IImageProc
{
public:
	virtual  HICON  GetIcon()=0; 					 	//加载一个图标,目前该接口已经不使用了
	virtual  DWORD  ShowDlg()=0;  						//显示对话框
	virtual  DWORD  LoadIplImagePtr(IMGVECT * pInputImg)=0;  //加载IplImage指针集

	//2013年1月30日添加
	virtual  DWORD  SetDlgRect(const RECT rcDlg)=0;          //设置对话框的大小

	//2013年2月17日添加
	virtual  DWORD  SetDefaultFolder(const CString strFolder)=0; //设置缺省文件夹，用于暂时存储处理结果图片
	virtual  DWORD  GetProcImageCount()=0; //获取处理后的图像计数

	//2013年2月22日添加
	virtual  DWORD  SetPlugConfigFile(const CString strFilePath)=0;//设置插件的配置文件路径
	virtual  DWORD  GetPlugUUID(CString& strUUID)=0;  //获取该控件的UUID号码(该号码遵循GPL标准)	

};
#endif