#pragma once

//��Ҫ���ڻ�ȡ�������ĸ��������ļ�·��
class  CSysFileSet
{
public:
	CSysFileSet(void);
	~CSysFileSet(void);
	CString  GetConfigFilePath();
	CString  GetPlugConfigPath();
	CString  GetAppPath();
	CString  GetTemporaryFolder();
	BOOL     ScanFile();//�����ļ���

private:
	BOOL      LoadAppPath();
	CString   m_strConfigFilePath;
	CString   m_strPlugConfigPath;
	CString   m_strAppPath;
	CString   m_strTemporaryFolder;
};

