// SettingsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AiQi.h"
#include "SettingsDlg.h"

#include "YUAN_system.h"


// CSettingsDlg 对话框

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialog)

CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
	//, check1(FALSE)
	//, check2(FALSE)
	//, check3(FALSE)
	, check4(FALSE)
	, check5(FALSE)
	, check6(FALSE)
	, check7(FALSE)
{

}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Check(pDX, IDC_CHECK1, check1);
	//DDX_Check(pDX, IDC_CHECK2, check2);
	//DDX_Check(pDX, IDC_CHECK3, check3);
	DDX_Check(pDX, IDC_CHECK4, check4);
	DDX_Check(pDX, IDC_CHECK5, check5);
	DDX_Check(pDX, IDC_CHECK6, check6);
	DDX_Check(pDX, IDC_CHECK7, check7);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSettingsDlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON2, &CSettingsDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSettingsDlg 消息处理程序

void CSettingsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

UpdateData();

/*
 if(check1 == TRUE)
   {
    Run_Learn=1;
   }
   else
   {
    Run_Learn=0;
   }



 
 if(check2 == TRUE)
   {
    _Run_Forgot=1;
   }
   else
   {
    _Run_Forgot=0;
   }



 if(check3 == TRUE)
   {
    run_try=1;
   }
   else
   {
    run_try=0;
   }

*/

 if(check4 == TRUE)
   {
    AI_AUTO_Question_Flag=1;
   }
   else
   {
    AI_AUTO_Question_Flag=0;
   }



 
 if(check5 == TRUE)
   {
    Run_FC_Flag=1;
   }
   else
   {
    Run_FC_Flag=0;
   }



 if(check6 == TRUE)
   {
    Auto_Load_And_Save_Memory_Flag=1;
   }
   else
   {
    Auto_Load_And_Save_Memory_Flag=0;
   }



 if(check7 == TRUE)
   {
    AI_Feedback_Question_Flag=1;
   }
   else
   {
    AI_Feedback_Question_Flag=0;
   }





  UpdateData(0);

  OnOK();


}

int CSettingsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码


/*

 if(Run_Learn == TRUE)
   {
    check1=1;
   }
   else
   {
    check1=0;
   }


 if(_Run_Forgot == TRUE)
   {
    check2=1;
   }
   else
   {
    check2=0;
   }


 if(run_try == TRUE)
   {
    check3=1;
   }
   else
   {
    check3=0;
   }
*/

 if(AI_AUTO_Question_Flag == TRUE)
   {
    check4=1;
   }
   else
   {
    check4=0;
   }


 if(AI_Feedback_Question_Flag == TRUE)
   {
    check7=1;
   }
   else
   {
    check7=0;
   }





 if(Run_FC_Flag == TRUE)
   {
    check5=1;
   }
   else
   {
    check5=0;
   }


 if(Auto_Load_And_Save_Memory_Flag == TRUE)
   {
    check6=1;
   }
   else
   {
    check6=0;
   }



	return 0;
}

void CSettingsDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

  OnCancel();
}
