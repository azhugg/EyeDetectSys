#pragma once

//主要用于获取软件所需的各种配置文件路径
class  CSysFileSet
{
public:
	CSysFileSet(void);
	~CSysFileSet(void);
	CString  GetConfigFilePath();
	CString  GetPlugConfigPath();
	CString  GetAppPath();
	CString  GetTemporaryFolder();
	BOOL     ScanFile();//检索文件集

private:
	BOOL      LoadAppPath();
	CString   m_strConfigFilePath;
	CString   m_strPlugConfigPath;
	CString   m_strAppPath;
	CString   m_strTemporaryFolder;
};

