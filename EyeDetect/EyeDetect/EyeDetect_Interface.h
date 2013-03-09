#ifndef   EYEDETECT_INTERFACE_123456
#define   EYEDETECT_INTERFACE_123456
//�ӿ��ļ������д����඼Ӧ�������ڴ���
//ʹ�õ�OpenCV�汾:OpenCV 1.0(����ʹ�������汾)
//���ߣ�������
//˵�����ӿ���Ҫ������������ͼ����̬����֮�������
//���ڣ�2013��1��28��
//�汾��1.0.0.0
//ע�����1.ÿ�η����°汾�Ľӿڣ�������̬��Ҫע�����
//			2.���ӿ���ҪSTL��openCV��֧�֣������ڹ��������������
//			  ���ֿ⣬��ο���������

#include  "cv.h"
#include  "highgui.h"
#include  <vector>

typedef  std::vector<IplImage *>    IMGVECT;						//ͼ��������
typedef BOOL (WINAPI * PFN_Plug_CreateObject)(void ** pobj);     //��������
typedef BOOL (WINAPI * PFN_Plug_DestroyObject)();				//�ͷŶ���

class   IImageProc
{
public:
	virtual  HICON  GetIcon()=0; 					 	//����һ��ͼ��,Ŀǰ�ýӿ��Ѿ���ʹ����
	virtual  DWORD  ShowDlg()=0;  						//��ʾ�Ի���
	virtual  DWORD  LoadIplImagePtr(IMGVECT * pInputImg)=0;  //����IplImageָ�뼯

	//2013��1��30�����
	virtual  DWORD  SetDlgRect(const RECT rcDlg)=0;          //���öԻ���Ĵ�С

	//2013��2��17�����
	virtual  DWORD  SetDefaultFolder(const CString strFolder)=0; //����ȱʡ�ļ��У�������ʱ�洢������ͼƬ
	virtual  DWORD  GetProcImageCount()=0; //��ȡ������ͼ�����

	//2013��2��22�����
	virtual  DWORD  SetPlugConfigFile(const CString strFilePath)=0;//���ò���������ļ�·��
	virtual  DWORD  GetPlugUUID(CString& strUUID)=0;  //��ȡ�ÿؼ���UUID����(�ú�����ѭGPL��׼)	

};
#endif