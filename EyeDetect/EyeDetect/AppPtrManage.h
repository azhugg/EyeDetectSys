#pragma once
//一定要注意主框架的包含顺序不能乱
#include "EyeDetect.h"
#include "MainFrm.h"
#include "EyeDetectDoc.h"
#include "EyeDetectView.h"

//其他的包含顺序可以随意
#include  "RightDockablePane.h"
#include  "LeftDockedPane.h"

class CAppPtrManage
{
public:	
	CAppPtrManage(void);

	~CAppPtrManage(void);
public:
	CMainFrame	*  GetAppMainFrmPtr();
	CEyeDetectView  * GetAppViewPtr();
	CEyeDetectDoc  * GetAppDocPtr();

	void      SetAppMainFrmPtr(CMainFrame * ptr);
	void      SetAppViewPtr(CEyeDetectView * ptr);
	void	  SetAppDocPtr(CEyeDetectDoc * ptr);
	void      SetDlgRightDockedPtr(CDlgRightDocked * ptr);
	CDlgRightDocked  * GetDlgRightDockedPtr();


private:
	CMainFrame		* m_pMainFrm;
	CEyeDetectView  * m_pView;
	CEyeDetectDoc   * m_pDoc;
	CDlgRightDocked * m_pDlgRight;
};

extern   CAppPtrManage   theAppPtr;

