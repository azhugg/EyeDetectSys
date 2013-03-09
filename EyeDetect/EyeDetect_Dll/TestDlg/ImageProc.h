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
	HICON   GetIcon(); 					 	//����һ��ͼ��
	DWORD   ShowDlg();  						//��ʾ�Ի���
	DWORD   LoadIplImagePtr(IMGVECT * pInputImg);                  //����ͼ��
	DWORD   SetDlgRect(const RECT rcDlg);

	//2013��2��17�����
	DWORD  SetDefaultFolder(const CString strFolder); //����ȱʡ�ļ��У�������ʱ�洢������ͼƬ
	DWORD  GetProcImageCount(); //��ȡ������ͼ�����

	DWORD  SetPlugConfigFile(const CString strFilePath);//���ò���������ļ�·��
	DWORD  GetPlugUUID(CString& strUUID);  //��ȡ�ÿؼ���UUID����(�ú�����ѭGPL��׼)	

private:
	HICON   m_hIcon;
	boost::shared_ptr<CDlgShowImg>   m_pDlgShowImg;              //��ʾͼƬ�ĶԻ���

};

