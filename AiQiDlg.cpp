// AiQiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <afxinet.h>
#include "AiQi.h"
#include "AiQiDlg.h"

#include "BrainBoxDlg.h" //我的对话框新类
#include "SettingsDlg.h" //我的对话框新类

#include "MyFc.h" //中文分词


#include "YUAN_struct.h"

#include "YUAN_system.h"


#include "TextOutBox.h" //文字输出

#include "MyColor.h" //颜色定义

#include "My_ZiBianMa.h" //字编码


#ifdef _DEBUG
#define new DEBUG_NEW
#endif










TEXT_INPUT_BOX TextInputBox[ TextInputBox_String_SUM ];



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAiQiDlg 对话框




CAiQiDlg::CAiQiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAiQiDlg::IDD, pParent)
	//, MainTextOut(_T(""))
	, input_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);



    FC_text = _T(""); //中文分词

    input_text_0 = _T(""); //备份输入内容
	AI_Question_text  = _T(""); //电脑提问的字符串

	Enter = 0;
	Flow_run = 0;


    Command_Flag = 0;

    P_layer_0_max_E_YUAN = NULL;
    P_layer_0_max_E_YUAN_AI_Think_Choose = NULL;

    P_layer_1_max_E_YUAN = NULL;
    P_layer_1_max_E_YUAN_AI_Think_Choose = NULL;

    P_layer_2_max_E_YUAN = NULL;
    P_layer_2_max_E_YUAN_AI_Think_Choose = NULL;

    AI_Think_Choose_Contacts_Number=0;//AI思考后选择的联系表的编

    P_User_Answer_objective_YUAN = NULL;  //用户的目标元
    P_AUTO_Question_select_YUAN = NULL;  //自动提问选中的元


    Last_Layer_0_Max_E_YUAN_Name="没有最强活跃元"; //最近一次最强活跃元的名称

    AI_AUTO_Question_Ready_Time = 300;
    AI_AUTO_Question_Ready_MAX_Time = 300;

    AUTO_Learning_Ready_Time = 50;
    AUTO_Learning_Ready_MAX_Time = 50;

	AUTO_Learning_i=1;

    Think_flag = 0;
    Think_time = 20;
    Think_MAX_time = 20;


    User_Answer_Flag = 0;
    User_Answer_Time = 220;
    User_Answer_MAX_Time = 220;


    AI_YES_Flag = 0;
    AI_YES_Time = 20;
    AI_YES_MAX_Time =20;

    AI_NO_Flag = 0;
    AI_NO_Time = 20;
    AI_NO_MAX_Time= 20;

    AI_Happy_Flag = 0; //奖励 高兴
    AI_Happy_Time = 20;
    AI_Happy_MAX_Time = 20;

    AI_Sad_Flag = 0;  //惩罚 伤心
    AI_Sad_Time = 20;
    AI_Sad_MAX_Time = 20;

    AI_Have_Feelings_Flag = 0;
    AI_Have_Feelings_Time = 20;
    AI_Have_Feelings_MAX_Time= 20;

    AI_Welcome_Flag = 0;  //启动 欢迎
    AI_Welcome_Time = 20;
    AI_Welcome_MAX_Time = 20;



    Waiting_For_Assessment_Flag = 0; //等待评估 回答
    Waiting_For_Assessment_Time = 80;
    Waiting_For_Assessment_MAX_Time = 80;


    AI_do_not_know = 0; //AI不知道答案

	AI_Question_Kind=0; //电脑提问的类型   1对元存储的字符串提问    2对于用户输入的字符串提问



 if (LoadLibrary("RICHED20.DLL") == NULL) //RichEdit控件初始化
{

 AfxMessageBox("riched20.dll没有找到!");

 PostMessage(WM_QUIT,0,0);

} 

AfxInitRichEdit2(); //RichEdit控件初始化


 //一些初始化函数

 load_system_config_file("config/system.txt");       //读取system配置文件

 YUAN=new YUAN_UNIT;  //分配内存

 YUAN->Init();


 init_rand(); //初始化随机数


 TEXT_OUT_BOX_INIT();


 D.init("CK/CK.txt"); //加载词典


 CK_DC= _T(""); //逻辑处理中用的 动词词库
 TxtFileRead_to_CString("CK/DongCi.txt",&CK_DC); //加载TXT文件到字符串



 CK_SXBQ= _T(""); //概念处理中用的 属性标签
 TxtFileRead_to_CString("CK/SXBQ.txt",&CK_SXBQ); //加载TXT文件到字符串


 CK_XRC= _T(""); //概念处理中用的 形容词词库
 TxtFileRead_to_CString("CK/XRC.txt",&CK_XRC); //加载TXT文件到字符串


  City_Weather_Number= _T(""); //城市天气代码
 TxtFileRead_to_CString("data/city_weather_number.txt",&City_Weather_Number); //加载TXT文件到字符串



if(Auto_Load_And_Save_Memory_Flag ==1) //自动加载和保存记忆
{
  CBrainBoxDlg a;
  a.Load_Memory_File_XML(2,"记忆文件/AiQi的记忆.xml");


}




 Display_Startup_Message=1; //显示启动信息





 TEXT_INPUT_BOX_INIT();



}




void CAiQiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_MainDlg_OUTPUT_EDIT, m_edit);
	//DDX_Text(pDX, IDC_MainDlg_OUTPUT_EDIT, MainTextOut);
	DDX_Text(pDX, IDC_MainDlg_INPUT_EDIT, input_text);
	DDX_Control(pDX, IDC_RICHEDIT21, MyRichEdit);
}

BEGIN_MESSAGE_MAP(CAiQiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CAiQiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_ON_BRAINBOX, &CAiQiDlg::OnBnClickedButtonOnBrainbox)

	ON_BN_CLICKED(IDC_BUTTON_ON_LOAD_CL, &CAiQiDlg::OnFileRead_ChatLibrary)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_Setting, &CAiQiDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_ON_Online_Learning, &CAiQiDlg::OnBnClickedButtonOnOnlineLearning)
	ON_BN_CLICKED(IDC_BUTTON_Help, &CAiQiDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// CAiQiDlg 消息处理程序

BOOL CAiQiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码



  //初始化输出框的字体大小
 // pEdt=(CEdit*)GetDlgItem(IDC_MainDlg_OUTPUT_EDIT);
 // m_editFont.CreatePointFont(120,"宋体");
 // pEdt->SetFont(&m_editFont); 


 if(Edit_Brain == 0) //编辑BrainBox开启或关闭
  {
   GetDlgItem(IDC_BUTTON_ON_BRAINBOX)-> EnableWindow(FALSE);
  }

CButton* popenbtn=(CButton*)GetDlgItem(IDC_BUTTON1);
popenbtn->SetFocus();


/*
//按钮图片
HBITMAP   BmpButton_Setting;   
BmpButton_Setting = LoadBitmap(AfxGetInstanceHandle(),   
    MAKEINTRESOURCE(IDB_BITMAP_BmpButton_Setting)); // IDB_BITMAP_TEST为资源图片ID  

((CButton *)GetDlgItem(IDC_BUTTON_Setting))->SetBitmap(BmpButton_Setting); 
*/

	return 0;  
	// 除非将焦点设置到控件，否则返回 TRUE
}

void CAiQiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAiQiDlg::OnPaint()
{

	/*
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	*/


	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here



/*

//Debug_Text信息
//双缓存显示///////////////////////////////////////////

CDC *pDC=GetDC();

int nWidth=300,nHeight=400;



CDC MemDC; //定义一个显示设备对象
CBitmap MemBitmap;//定义一个位图对象
MemDC.CreateCompatibleDC(NULL);//建立与屏幕显示兼容的内存显示设备
MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight); //下面建立一个与屏幕显示兼容的位图，窗口的大小
CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap); //将位图选入到内存显示设备中


MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(250,251,247));

//绘图--------------------------

//TEXT_OUT_BOX_OutAll(2,6, 0,14,&MemDC); //输出



////////我的Debug调试显示信息
CString Debug_Text;

MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(250,251,247));


Debug_Text.Format("AI调试信息");
  //MemDC.TextOut(10,10,Debug_Text);
  TextOut_SongTi(10, 10,14,BLUE,Debug_Text,&MemDC);

Debug_Text.Format("AI自动提问倒记时=%d",AI_AUTO_Question_Ready_Time);

  TextOut_SongTi(10,50, 14,BLUE,Debug_Text,&MemDC);

if(P_AUTO_Question_select_YUAN == NULL)
Debug_Text.Format("自动提问选择的元=无");
else
Debug_Text.Format("自动提问选择的元=%s",P_AUTO_Question_select_YUAN->name);
  TextOut_SongTi(10,70, 14,BLUE,Debug_Text,&MemDC);


if(P_layer_1_max_E_YUAN == NULL)
Debug_Text.Format("概念层最活跃的元=无");
else
Debug_Text.Format("概念层最活跃的元=%s",P_layer_1_max_E_YUAN->name);
  TextOut_SongTi(10,110, 14,BLUE,Debug_Text,&MemDC);

if(P_layer_1_max_E_YUAN_AI_Think_Choose == NULL)
Debug_Text.Format("概念层被AI选择的元=无");
else
Debug_Text.Format("概念层被AI选择的元=%s",P_layer_1_max_E_YUAN_AI_Think_Choose->name);
  TextOut_SongTi(10,130, 14,BLUE,Debug_Text,&MemDC);

if(P_layer_2_max_E_YUAN == NULL)
Debug_Text.Format("方法层最活跃的元=无");
else
Debug_Text.Format("方法层最活跃的元=%s",P_layer_2_max_E_YUAN->name);
  TextOut_SongTi(10,150, 14,BLUE,Debug_Text,&MemDC);

if(P_layer_2_max_E_YUAN_AI_Think_Choose == NULL)
Debug_Text.Format("方法层被AI选择的元=无");
else
Debug_Text.Format("方法层被AI选择的元=%s",P_layer_2_max_E_YUAN_AI_Think_Choose->name);
  TextOut_SongTi(10,170, 14,BLUE,Debug_Text,&MemDC);


Debug_Text.Format("AI等待用户给回答评价=%d   倒计时=%d",Waiting_For_Assessment_Flag,Waiting_For_Assessment_Time);
  TextOut_SongTi(10,190, 14,BLUE,Debug_Text,&MemDC);


if(Run_FC_Flag==1)
{

 Debug_Text.Format("中文分词结果：");
  TextOut_SongTi(10,230, 14,BLUE,Debug_Text,&MemDC);
 Debug_Text.Format("%s",FC_text);
  TextOut_SongTi(10,250, 14,BLUE,Debug_Text,&MemDC);

}
else
{
 Debug_Text.Format("中文分词功能已关闭");
  TextOut_SongTi(10,230, 14,BLUE,Debug_Text,&MemDC);
}



CString DC;

//查找文本中的第一个动词，并且返回它
if(Find_Text_DC(FC_text,&DC))
  {
	  Debug_Text.Format("第一个动词:%s",DC);
   TextOut_SongTi(10,270, 14,RGB(115,0,255),Debug_Text,&MemDC);
  }




Debug_Text.Format("掌握知识点：%d  回答能力值：%d ",YUAN_Layer_SUM[1],YUAN_Layer_SUM[2]);
  TextOut_SongTi(10,310, 14,RGB(115,0,255),Debug_Text,&MemDC);

////////

//--------------------------

pDC->BitBlt(578,12,nWidth,nHeight,&MemDC,0,0,SRCCOPY); //将内存中的图拷贝到屏幕上进行显示

MemDC.SelectObject(pOldBit); //绘图完成后的清理
MemBitmap.DeleteObject();
MemDC.DeleteDC(); 



ReleaseDC(pDC); //释放CDC资源


*/









if(Display_Startup_Message==1) //显示启动信息
{

 TEXT_OUT_BOX_SAY_3("您好！我是智能助手AiQi，欢迎使用。",1); //数据显示在屏幕上

 AI_Welcome_Flag=1; //启动 欢迎 表情

 Display_Startup_Message=0;

}







//双缓存显示2///////////////////////////////////////////

CDC *pDC2=GetDC();


int nWidth2=188,nHeight2=298; 



CDC MemDC2; //定义一个显示设备对象
CBitmap MemBitmap2;//定义一个位图对象
MemDC2.CreateCompatibleDC(NULL);//建立与屏幕显示兼容的内存显示设备
MemBitmap2.CreateCompatibleBitmap(pDC2,nWidth2,nHeight2); //下面建立一个与屏幕显示兼容的位图，窗口的大小
CBitmap *pOldBit2=MemDC2.SelectObject(&MemBitmap2); //将位图选入到内存显示设备中


MemDC2.FillSolidRect(0, 0,nWidth2,nHeight2,RGB(255,255,255));

//绘图--------------------------




Change_Face(0, 0,&MemDC2); //变表情  0,0 是申请的坐标






//显示知识点信息
CString TT;
TT.Format("掌握知识点：%d",YUAN_SUM);
  TextOut_SongTi(38,228, 20,RGB(8,117,80),TT,&MemDC2);
TT.Format("回答能力值：%d ",YUAN_CONTACTS_SUM);
  TextOut_SongTi(38,248, 20,RGB(8,117,80),TT,&MemDC2);



//显示自动提问时间
if(AI_AUTO_Question_Flag==1)
{


 Display_AUTO_Question_Time(0, 146,AI_AUTO_Question_Ready_Time,AI_AUTO_Question_Ready_MAX_Time,&MemDC2); 

}



//--------------------------

pDC2->BitBlt(450,17,nWidth2,nHeight2,&MemDC2,0,0,SRCCOPY); //将内存中的图拷贝到屏幕上进行显示

MemDC2.SelectObject(pOldBit2); //绘图完成后的清理
MemBitmap2.DeleteObject();
MemDC2.DeleteDC(); 


ReleaseDC(pDC2); //释放CDC资源






}




//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAiQiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






int CAiQiDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码



   SetTimer(1,100,NULL);   //元运行主引擎

   SetTimer(36,100,NULL);  //屏幕显示 


  SetTimer(30,100,NULL); //定时器 流处理

  SetTimer(31,100,NULL); //定时器 自动提问

  SetTimer(33,100,NULL); //定时器 MyDebug


  SetTimer(38,100,NULL);  //等待评估 回答



  //CSayDlg::SendMessage(WM_SETICON,ICON_SMALL,(LPARAM)hIcon);  //发送消息更改窗口图标


if(Run_FC_Flag==1)
 FC_text="中文分词功能已开启";
else
 FC_text="中文分词功能已关闭"; 

string s=FC_text.GetBuffer(0);

 s = D.SegmentWord(s); //对字符串进行中文分词

FC_text = s.c_str();  




	return 0;
}



void CAiQiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值




CString TT;

  CString SXBQ,SXBQ_text;
  int SXBQ_N;

    if(nIDEvent==1) //1号定时器处理代码;
      {

		if(YUAN_RUN_MAIN_Flag==1)
        YUAN_RUN_MAIN();  //元运行主引擎
 
      }



    if(nIDEvent==36) //36号定时器处理代码;
      {
       //刷新显示屏幕
 
       OnPaint();
 
      }



    if(nIDEvent==38) //38号定时器处理代码; 等待评估 回答
      {
       //等待评估 回答
 

 



       if(Waiting_For_Assessment_Flag==1)
	   {
           Waiting_For_Assessment_Time--;

 


           if(Waiting_For_Assessment_Time<=0) //用户评估已经到了
             {
              Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;


              Waiting_For_Assessment_Flag=0;


             }



	   }





      }




    if(nIDEvent==30) //30号定时器处理代码;
    {

      if(Think_flag==1)
	  {
        Think_time--;

          //改变窗口标题
         //SetWindowText("请稍候，正在处理中...");
        ((CEdit*)GetDlgItem(IDC_MainDlg_INPUT_EDIT))-> EnableWindow(FALSE);//SetReadOnly(TRUE); //把输入框屏蔽






        if(Think_time<=0) //思考时间结束 对最活跃的元 进行评估

		{
         Think_time=Think_MAX_time;
         Think_flag=0;


                ((CEdit*)GetDlgItem(IDC_MainDlg_INPUT_EDIT))-> EnableWindow(TRUE);//SetReadOnly(TRUE); //把输入框恢复
	   	
                ((CEdit*)GetDlgItem(IDC_MainDlg_INPUT_EDIT))->SetFocus(); //恢复编辑框的鼠标焦点

				//相关处理-------------------------











               if(Command_Flag==1)  //<普通激活>                对输入字符串的内容进行模糊匹配，并且输出一个（最优）结果
			   {



 //得到最活跃的元
 P_layer_0_max_E_YUAN=YUAN->Find_layer_max_E_YUAN_P(30,0);

 //AI选择后 保存 等待评价的 元
 P_layer_0_max_E_YUAN_AI_Think_Choose=NULL; 


 int input_text_word_sum=Return_String_Words_Sum(input_text_0); //返回输入字符串中单词的数量



 if(P_layer_0_max_E_YUAN!=NULL)
 {
  Last_Layer_0_Max_E_YUAN_Name = P_layer_0_max_E_YUAN->name; //保存 最近一次最强活跃元的名称
 }
 else
 {
  Last_Layer_0_Max_E_YUAN_Name.Empty();
 }



 //统计当前所有活跃元，记录成列表-------------------------------------

 CString Active_YUAN_List;//活跃元列表 

 Active_YUAN_List=Generate_Active_YUAN_List(); //生成活跃元列表 记录所有当前激活的元的名称



 CString Active_YUAN_List_MC; //激活的元中的名词列表
 CString Active_YUAN_List_XRC; //激活的元中的形容词列表

 int SUM=Return_String_Words_Sum(Active_YUAN_List); //返回字符串中单词的数量
 CString Word;

  for(int i=1; i<=SUM ; i++)
  {
   Word=Return_String_N_Word(Active_YUAN_List,i); //返回字符串第N个单词

   if(IS_XRC(Word)) //是形容词
     {
      Active_YUAN_List_XRC += Word+" "; //追加到形容词列表
     }
   else   //是名词
     {
      Active_YUAN_List_MC += Word+" "; //追加到名词列表
     } 
  }

 if(Active_YUAN_List_XRC.IsEmpty()) Active_YUAN_List_XRC="没有";

 //TEXT_OUT_BOX_SAY_3("活跃名词列表："+Active_YUAN_List_MC,0); //数据在屏幕上输出
 //TEXT_OUT_BOX_SAY_3("活跃形容词列表："+Active_YUAN_List_XRC,0); //数据在屏幕上输出

 //----------------





//有几率的主动判别语句类型-------------------------------------



  int KeNeng=Xrand(0,100); //生成可能性

       if(KeNeng>=0 && KeNeng<=70)
         {

             if(Recognition_ZWB_Form(input_text_0)==1 ) //是主谓宾语句格式------

               {

                  //AfxMessageBox("这是主谓宾语句，建立命题");

                 //[形式处理] 建立命题  格式： 记住 S谓P  、 记住 S
                 Form_Create_ZWB_EX(input_text_0); //带有结果输出的命题建立函数

                 goto HDCL_END;


               }


             if(Recognition_SXBQ_Form(input_text_0)==1 ) //是带标签记忆的建立语句格式------

               {

                  //AfxMessageBox("这是带标签语句，建立命题格式");



                 //标签记忆的建立函数
                 Form_Create_SXBQ_EX(input_text_0); //带有结果输出的标签记忆建立函数

                 goto HDCL_END;


               }


	    }



   //无活跃反应-------------------------------------------------------



     if(Active_YUAN_List.IsEmpty()) //如果没有活跃的元，直接退出
	   {





         //用户输入是多个词语=====
          if(input_text_word_sum!=1)
          {



		    TT.Format("我无法理解你说的话");

            AI_NO_Flag=1;

		    AI_do_not_know = 1; //AI不知道答案

		    TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
            goto HDCL_END;



          }
         //用户输入是单个词语=====
	     else
	     {

	    	TT.Format("我不知道...脑子里没感觉");

            AI_NO_Flag=1;

	    	AI_do_not_know = 1; //AI不知道答案

		    TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
            goto HDCL_END;
	     }




	   }
          





  //有活跃反应----------------------------------------------------------


  SXBQ_text=input_text_0;


  //查找文本中的第一个属性标签词，并且返回它
  SXBQ_N = Find_Text_SXBQ(SXBQ_text, &SXBQ);
  if(SXBQ_N == -1) 
    {
     //goto SXBQPD_END;
    }

  else
    {

      CString YUAN_Data_List; //带标签的数据表


      SXBQ_text.Replace("的 "+SXBQ,SXBQ);
      Format_String(&SXBQ_text); //格式化字符串 去掉多余空格

     if(Return_String_N_Word(SXBQ_text,2) == SXBQ ) //第二个词是标签
       {
          // AfxMessageBox("!!!");

			 CString YUAN_name = Return_String_N_Word(SXBQ_text,1); //第一个词是元名称

			
			 YUAN_Data_List.Empty();

           //查找元带标签的联系表数据 返回该数据
           Find_YUAN_Contacts_Label_Data(YUAN_name , SXBQ ,&YUAN_Data_List);

           if(YUAN_Data_List.IsEmpty()!=1) //该元有标签
		     {
              TEXT_OUT_BOX_SAY_3(YUAN_Data_List+"..",1); //数据在屏幕上输出


              goto HDCL_END;

		     }
		  // else AfxMessageBox("!!!");

       }


	 else  //不是一般属性格式
	  {
        if(P_layer_0_max_E_YUAN!=NULL)//有最活跃的元
		  {
			 YUAN_Data_List.Empty();

            //查找元带标签的联系表数据 返回该数据
            Find_YUAN_Contacts_Label_Data(P_layer_0_max_E_YUAN->name , SXBQ ,&YUAN_Data_List);

            if(YUAN_Data_List.IsEmpty()!=1) //该元有标签
		      {
               TEXT_OUT_BOX_SAY_3(YUAN_Data_List+"...",1); //数据在屏幕上输出


               goto HDCL_END;

		      }
		  }

	  }



    }



    //SXBQPD_END:;


   //-------------------

  //TEXT_OUT_BOX_SAY_3("用户输入是单个词语",1); //数据在屏幕上输出

       KeNeng=Xrand(0,100); //生成可能性

       if(KeNeng>=0 && KeNeng<=40) //挑选最活跃元，运行一条元数据+++++++++++++
         {

		    if(P_layer_0_max_E_YUAN!=NULL) //0层有最活跃的元
              {

                      keneng1:;

                     int nn=0;
                     int Contacts_Sum=P_layer_0_max_E_YUAN->Contacts->Get_Sum();


                     if(Contacts_Sum!=1) //如果联系表中有多条信息
                       {
                         int xn=Xrand(0,100);

                          if(xn<=5)
                            {
                             TT.Format("%s",P_layer_0_max_E_YUAN->Contacts->data); //选取联系表根做答案

		                     TT.Replace( " ", NULL );
                             //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
                             Run_YUAN_Contacts_Data(TT); //运行一条概念单元意义表数据
                            }


                        else{
                              nn=Xrand(1,Contacts_Sum-1); //随机从联系表中选取一条做答案输出
                              TT.Format("%s",P_layer_0_max_E_YUAN->Contacts->Get_n_data(nn));

		                      TT.Replace( " ", NULL );
                              //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
                              Run_YUAN_Contacts_Data(TT); //运行一条概念单元意义表数据							  
                            }

                       } 


                     else    //如果联系表中只有一条信息
                       {
                        TT.Format("%s",P_layer_0_max_E_YUAN->Contacts->data); //选取联系表根做答案


		                TT.Replace( " ", NULL );
                        //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
                        Run_YUAN_Contacts_Data(TT); //运行一条概念单元意义表数据
                       }




                     int xx=Xrand(1,100);

                     if(xx<=100) //有100%的可能，电脑会请求用户评价回答  触发隐藏式评价机制
					 {
                      //AI_Have_Feelings_Flag=1; //AI有感觉 并启动用户对回答的评分
			          Waiting_For_Assessment_Flag=1; //AI回答后触发评价时间
                      Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;

					  //TT.Format("我回答正确吗？可以评价，或继续");
					  //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

					  P_layer_0_max_E_YUAN_AI_Think_Choose=P_layer_0_max_E_YUAN; //AI选择后 保存 等待评价的 元
					  AI_Think_Choose_Contacts_Number=nn;
					  

					 }

			  }

			else//0层没有最活跃的元
			  {
				TT.Format("我不知道...");

                AI_NO_Flag=1;

				AI_do_not_know = 1; //AI不知道答案

				TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

				
			  }


			goto HDCL_END;

         }

	   else if (KeNeng>40 && KeNeng<=50) //挑选活跃列表中一个元，说出这个元的名字++++++++++++
         {
              CString D_NAME;
              int SUM=Return_String_Words_Sum(Active_YUAN_List); //返回字符串中单词的数量

              if(SUM==1)
                {
                D_NAME=Active_YUAN_List;
                }
              else
                {
                 int n=0;
                 n=Xrand(1,SUM); //随机选取一个元
                 D_NAME=Return_String_N_Word(Active_YUAN_List,n); //返回字符串第N个单词
                }

               TEXT_OUT_BOX_SAY_3("我感觉到"+D_NAME,1); //数据在屏幕上输出

			   goto HDCL_END;

         }

	   else if(KeNeng>50 && KeNeng<=100) //输出活跃元列表+++++++++++++
         {
            //  TEXT_OUT_BOX_SAY_3("我脑中有这些东西在活跃："+Active_YUAN_List,1); //数据在屏幕上输出





              if(Active_YUAN_List_XRC!="没有") //有形容词
                {
                 int n=0;
                 int SUM;
                 CString MC_Word,XRC_Word;


                 SUM=Return_String_Words_Sum(Active_YUAN_List_XRC); //返回字符串中单词的数量
                 n=Xrand(1,SUM); //随机选取一个元  提取形容词
                 XRC_Word=Return_String_N_Word(Active_YUAN_List_XRC,n); //返回字符串第N个单词


                 SUM=Return_String_Words_Sum(Active_YUAN_List_MC); //返回字符串中单词的数量
                 n=Xrand(1,SUM); //随机选取一个元  提取名词
                 MC_Word=Return_String_N_Word(Active_YUAN_List_MC,n); //返回字符串第N个单词

				 //形容词+名词 ，词语组合输出：----------------
				 int nn=Xrand(0,100); 
				 if(nn>=0 && nn<=30) 
				 {
				  TEXT_OUT_BOX_SAY_3(XRC_Word +"的"+MC_Word,1); //数据在屏幕上输出 
				 }

				 else if(nn>30 && nn<=60) 
				 {
				  TEXT_OUT_BOX_SAY_3(XRC_Word +"的存在",1); //数据在屏幕上输出 
				 }

				 else if(nn>60 && nn<=85) 
				 {
				  TEXT_OUT_BOX_SAY_3(XRC_Word +"的感觉",1); //数据在屏幕上输出 
				 }
                 
				 else if (nn>85 && nn<=100) 
				 { 
				  TEXT_OUT_BOX_SAY_3("像"+MC_Word+"的感觉"+"，"+"是"+XRC_Word +"的"+"东西"+"。",1);//数据在屏幕上输出
				 }

				 goto HDCL_END;

                }

			  else 
			  {

                  goto keneng1;
			  }


         }


















				
          HDCL_END:;
				
			   }




                //----------------

			   else if(Command_Flag==10)  //<逻辑提问语句 求命题真值>  用户输入一句话，"?"作关键字，让AI判断该语句是否和记忆逻辑匹配
			   {






                     //TT.Format("逻辑提问语句10"); 
                     //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                     //得到答案（方法层最活跃的元）



                       CString text_DC;
					   CString Contacts_data_DC;
                       YUAN_UNIT *MAX_PF_YUAN=NULL;
                       CString MAX_PF_YUAN_Contacts_data;

                       Find_Text_DC(input_text_0, &text_DC);//查找文本中的第一个动词，并且返回它



					   if(text_DC.IsEmpty()!=1)//=========有动词
					   {

						   CString LL;
						   CString RR;


                         //  TT.Format("中文分词=%s",input_text_0); 
                         //   TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
                         //  TT.Format("动词=%s",text_DC); 
                         //   TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                           CString FouDingDC; //否定动词


						   FouDingDC="不 "+text_DC;
                           if(input_text_0.Find(FouDingDC)!=-1) //有否定动词
						   {

                            

						   Split_X_String(input_text_0,FouDingDC,&LL,&RR); //把字符串以X为分割，变成2个字符窜


 
                           RR=FouDingDC+RR;


                         //  TT.Format("输入有否定动词=%s",FouDingDC); 
                         //   TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

						   }

						   else  //只有肯定动词
						   {
						   Split_X_String(input_text_0,text_DC,&LL,&RR); //把字符串以X为分割，变成2个字符窜


 
                           RR=text_DC+RR;
                           FouDingDC.Empty();

						   }

                         

                         //  TT.Format("RR=%s",RR); 
                         //  TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


//AfxMessageBox(RR);

 
                          Find_YUAN_Contacts(RR,60,  &MAX_PF_YUAN, &MAX_PF_YUAN_Contacts_data);  //查找最相似的联系表数据 返回该数据 和 元指针  前提该元状态是1

					     Find_Text_DC(MAX_PF_YUAN_Contacts_data, &Contacts_data_DC);

                          //TT.Format("逻辑提问语句10  有动词"); 
                          //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
           //&& Contacts_data_DC==text_DC
                          if(MAX_PF_YUAN!=NULL ) //YUAN数据里有最相似的联系表数据
						  {

                             int nn=0;
							 CString nnT;

                             CString  FouDingDC2;
								 
								 
								FouDingDC2 ="不"+text_DC;




                               if(FouDingDC.IsEmpty()==1) //输入中没有否定动词
							   {
                                 if(MAX_PF_YUAN_Contacts_data.Find(FouDingDC2)==-1) //数据中没有否定
								   {
                                    nn=1;
								   }
								 else
								   {
                                    nn=2;
								   }
							   }


							   else  //输入中有否定动词
							   {
                                 if(MAX_PF_YUAN_Contacts_data.Find(FouDingDC2)==-1) //数据中没有否定
								   {
                                    nn=2;
								   }
								 else
								   {
                                    nn=1;
								   }
							   }










                               if(nn==1)
					             {

					               nnT="是";

 

					              }

                               else if(nn==2)
					              {

					                nnT="不";



				               	}
						 



                            //TT.Format("恩，我觉得%s%s",LL,MAX_PF_YUAN_Contacts_data);

                             MAX_PF_YUAN_Contacts_data.Replace( "<", NULL );
                             MAX_PF_YUAN_Contacts_data.Replace( ">", NULL );

                              TT.Format("%s，我认为%s%s",nnT,LL,MAX_PF_YUAN_Contacts_data); 


                            TT.Replace( " ", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
						  }

						  else//没有找到相似的数据
						  {
                            TT.Format("我不知道啊。。。"); 

                            TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                            AI_NO_Flag=1;

						  }



					   }

					   else //=========无动词
					   {
                        
            

					     //TT.Format("逻辑提问语句10  无动词"); 
                         //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


                         YUAN_UNIT *MC_YUAN=YUAN->Find_layer_max_E_YUAN_P(30,0);

						 if(MC_YUAN!=NULL)//有名词的元相应
						 {
                          int nn=0;
                          int Contacts_Sum=MC_YUAN->Contacts->Get_Sum();
                          if(Contacts_Sum!=1) //如果联系表中有多条信息
                            {
                             nn=Xrand(0,Contacts_Sum-1); //随机从联系表中选取一条做答案输出
                             TT.Format("%s",MC_YUAN->Contacts->Get_n_data(nn));
                            } 
                          else //如果联系表中只有一条信息
                            {
                             TT.Format("%s",MC_YUAN->Contacts->data); //选取联系表根做答案
                            }

		                    TT.Replace( " ", NULL );
							TT.Replace( "<", NULL );
							TT.Replace( ">", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

						 }

						 else
						 {
                           TT.Format("我不知道这个东西是什么。。。"); 

                           TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                            AI_NO_Flag=1;
						 }


					   }







			   }



                //---------------




			   else if(Command_Flag==11) //<逻辑提问语句 填空>        用户输入一句话，"什么"作关键字，让AI先对记忆逻辑匹配，然后对输入语句中"什么"进行填空
			   {
                    // TT.Format("逻辑提问语句11"); 
                     //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                    CString text_DC;
                    CString LL;
                    CString RR;
                       YUAN_UNIT *MAX_PF_YUAN=NULL;
                       CString MAX_PF_YUAN_Contacts_data;

					//有动词=================================
                    if(Find_Text_DC(input_text_0, &text_DC))//查找文本中的第一个动词，并且返回它
					{

                     //TT.Format("有动词"); 
                     //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


                       Split_X_String(input_text_0,text_DC,&LL,&RR); //把字符串以X为分割，变成2个字符窜


                         //判断什么在动词前面=======
					   if(LL.Find("什么") !=-1 && RR.Find("什么") ==-1)
					   {
                         //TT.Format("什么在动词左边"); 
                         //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


                                       //整理否定动词
                                       CString FDDC;

                                       FDDC="不"+text_DC; 

                                       LL=LL+text_DC;
                                       LL.Replace( " ", NULL );

                                       if(LL.Find(FDDC)==-1) //没有否定动词
                                       {
                                        LL.Replace( text_DC, NULL );

                                       }

                                       else           //有否定动词
                                       {
                                        text_DC=FDDC;
                                        LL.Replace( FDDC, NULL );
                                         //TT.Format("有否定动词！");
                                         // TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                                       }


                         CString XD="<"+text_DC+">";
                         Find_YUAN_X_Contacts(XD+RR,150,  &MAX_PF_YUAN, &MAX_PF_YUAN_Contacts_data);  //查找最相似的联系表数据 返回该数据 和 元指针  无状态所有元  联系表数据权值最大的一个元



						 if(MAX_PF_YUAN!=NULL ) //YUAN数据里有最相似的联系表数据
						 {



                            TT.Format("我觉得%s%s",MAX_PF_YUAN->name,text_DC+RR);
							TT.Replace( " ", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

					       }
                         else
							 {


                                 if(text_DC=="是")
						           {

                                    TT.Format("什么%s%s...主人你考倒我了，我帮你网上查查吧，哈~",text_DC,RR); 
							        TT.Replace( " ", NULL );
                                    TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

						            CString CiTiao=RR;
                                    CString m_web_good_information = Get_CiTiao_Information_From_Web(CiTiao); //从网络上获取词条信息并返回
						            TEXT_OUT_BOX_SAY_3(m_web_good_information,1); //数据在屏幕上输出
						           }

								 else
								 {
                                  TT.Format("我不知道...什么%s",text_DC+RR); 
							      TT.Replace( " ", NULL );
                                  TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

							      AI_NO_Flag=1;

							     }
						     }

					   }


                         //判断什么在动词后面=======
					   if(LL.Find("什么") ==-1 && RR.Find("什么") !=-1)
					   {
                        // TT.Format("什么在动词右边"); 
                        // TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出



                                       //整理否定动词
                                       CString FDDC;

                                       FDDC="不"+text_DC; 

                                       LL=LL+text_DC;
                                       LL.Replace( " ", NULL );

                                       if(LL.Find(FDDC)==-1) //没有否定动词
                                       {
                                        LL.Replace( text_DC, NULL );

                                       }

                                       else           //有否定动词
                                       {
                                        text_DC=FDDC;
                                        LL.Replace( FDDC, NULL );
                                        //TT.Format("有否定动词！");
                                         //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                                       }

                          //  TT.Format("动词：%s",text_DC);
                          //  TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

						





                         Find_YUAN_X_Contacts_DC(text_DC+RR,50,&MAX_PF_YUAN, &MAX_PF_YUAN_Contacts_data,text_DC);

						 if(MAX_PF_YUAN!=NULL ) //YUAN数据里有最相似的联系表数据
						   {
						    MAX_PF_YUAN_Contacts_data.Replace( "<", NULL );
                            MAX_PF_YUAN_Contacts_data.Replace( ">", NULL );


                            TT.Format("我觉得%s%s",LL,MAX_PF_YUAN_Contacts_data);




							TT.Replace( " ", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

					       }
                         else if (MAX_PF_YUAN==NULL ) 
						   {


                                 if(text_DC=="是")
						           {

                                    TT.Format("%s%s什么...主人你考倒我了，我帮你网上查查吧，哈~",LL,text_DC); 
							        TT.Replace( " ", NULL );
                                    TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

						            CString CiTiao=LL;
                                    CString m_web_good_information = Get_CiTiao_Information_From_Web(CiTiao); //从网络上获取词条信息并返回
						            TEXT_OUT_BOX_SAY_3(m_web_good_information,1); //数据在屏幕上输出
						           }

								 else
								   {
                                    TT.Format("我不知道...%s%s什么",LL,text_DC); 
							        TT.Replace( " ", NULL );
                                    TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                                    AI_NO_Flag=1;

								   }

							  
						   }



					   }


					}

                    //没有动词==============================
					else
					{
                     TT.Format("没有动词"); 
                     TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出



					}
					



                     




			   }













                //---------------------------------




                //改变窗口标题
                //SetWindowText("请输入");


		}

	  }



	}



    if(nIDEvent==31) //31号定时器处理代码; 自动提问  和 等待反馈
    {


      //-----------------------回答的反应
      if(AI_YES_Flag==1)
	  {
           AI_YES_Time--;

 


           if(AI_YES_Time<=0) //AI 完成
             {
              AI_YES_Time=AI_YES_MAX_Time;


              AI_YES_Flag=0;


             }



	  }

	




      if(AI_NO_Flag==1)
	  {
           AI_NO_Time--;

 


           if(AI_NO_Time<=0) //AI 未完成
             {
              AI_NO_Time=AI_NO_MAX_Time;


              AI_NO_Flag=0;



             if(AI_do_not_know == 1) //AI不知道答案
               {
                 AI_do_not_know = 0;


                 if(AI_Feedback_Question_Flag == 1)
				 {

                  int nn=Xrand(1,100);
                  CString TT;

                  if(nn<=80) //有80%的可能，电脑会提出，刚才输入是什么的问题
                    {



                      AI_Question_text=input_text_0; //这里必须是input_text_0 保存有刚才用户输入的字符串信息  把这个字符串赋予 电脑提问的字符串

                      TT.Format("可不可以告诉我，“%s”对应的回答是什么？",AI_Question_text);
                      TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


                     TEXT_OUT_BOX_SAY_3("请输入答案",1); //数据在屏幕上输出


                       AI_Question_Kind=2;   //电脑对于用户输入的字符串提问

                       User_Answer_Flag=1;  //用户回答 开启
                       User_Answer_Time = User_Answer_MAX_Time;

                    }

				 }

               }








             }



	  }


      if(AI_Happy_Flag==1)
	  {
           AI_Happy_Time--;

 


           if(AI_Happy_Time<=0) //奖励 高兴
             {
              AI_Happy_Time=AI_Happy_MAX_Time;


              AI_Happy_Flag=0;


             }



	  }
	  



      if(AI_Sad_Flag==1)
	  {
           AI_Sad_Time--;

 


           if(AI_Sad_Time<=0) //惩罚 伤心
             {
              AI_Sad_Time=AI_Sad_MAX_Time;


              AI_Sad_Flag=0;


             }



	  }



      if(AI_Welcome_Flag==1)
	  {
           AI_Welcome_Time--;

 


           if(AI_Welcome_Time<=0) //启动 欢迎
             {
              AI_Welcome_Time=AI_Welcome_MAX_Time;


              AI_Welcome_Flag=0;


             }



	  }




      if(AI_Have_Feelings_Flag==1)
	  {
           AI_Have_Feelings_Time--;

 
           if(AI_Have_Feelings_Time==19) 
		   {
			   Waiting_For_Assessment_Flag=1; //AI回答后触发评价时间
               Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;
		   }



           if(AI_Have_Feelings_Time<=0) //AI有概念存在的感觉
             {
              AI_Have_Feelings_Time=AI_Have_Feelings_MAX_Time;


              AI_Have_Feelings_Flag=0;

              

             }



	  }



      //-----------------------自动学习

      if(AUTO_Learning_Flag==1)
	  {
           AUTO_Learning_Ready_Time--;

 


         if(AUTO_Learning_Ready_Time<=0) //自动学习时间到了 
           {
              AUTO_Learning_Ready_Time=AUTO_Learning_Ready_MAX_Time;


              //TEXT_OUT_BOX_SAY_3("网上学习",0); //数据在屏幕上输出



              // AUTO_Learning(AUTO_Learning_i); //自动学习
			  AUTO_Learning_2(); //自动学习
/*
			   			  AUTO_Learning_i++;
						  if(AUTO_Learning_i>YUAN_SUM)
						    {
								AUTO_Learning_Flag=0;
								TEXT_OUT_BOX_SAY_3("网上学习已结束",0); //数据在屏幕上输出

								}

								*/


		   }




	  }



      //-----------------------回答的反应



      if(AI_AUTO_Question_Flag==1)
	  {
           AI_AUTO_Question_Ready_Time--;

 


         if(AI_AUTO_Question_Ready_Time<=0) //自动提问时间到了 
           {
              AI_AUTO_Question_Ready_Time=AI_AUTO_Question_Ready_MAX_Time;




                  AUTO_Question_2(); //自动提问   对元存储的字符串提问
	              if(P_AUTO_Question_select_YUAN != NULL )  
		            {
                        User_Answer_Flag=1;
                        P_User_Answer_objective_YUAN =  P_AUTO_Question_select_YUAN;

                        AI_Question_Kind=1;  //电脑提问的类型 1对元存储的字符串提问

		            }





  







          }



	  }




      if(User_Answer_Flag==1)
	  {
           User_Answer_Time--;

 


           if(User_Answer_Time<=0) //用户反馈时间已经到了
             {
              User_Answer_Time=User_Answer_MAX_Time;


              User_Answer_Flag=0;
			  P_User_Answer_objective_YUAN = NULL;

			  AI_Question_Kind=0;

             }



	  }

	}


   if(nIDEvent==33) //33号定时器处理代码  MyDebug()
   {

    MyDebug();

   }



	CDialog::OnTimer(nIDEvent);
}













void CAiQiDlg::YUAN_RUN_MAIN()  //元运行主引擎
{
 float W=0; //W统计强度输入数值





   YUAN_UNIT *tmp;
   LINK_UNIT *linker_tmp;
   YUAN_UNIT *tmpY;

   float aE=0,bE=0; //连接双方的E值比较


  tmp=YUAN;


  int YuanSum=0; //统计元数目
  int YuanContactsSum=0; //统计元联系表数目
  int ln=0; //统计每层的元数目

   for(ln=0;ln<8;ln++)
   {
    YUAN_Layer_SUM[ln]=0;
   }


  for(;;) //遍历所有元
  {


      linker_tmp=tmp->linker; //把当前元的连接root赋予linker_tmp

    if(tmp->ID!=0) //0号元以外
     {


      W=0; //W统计初始化




     //统计每层的元数目
     ln=tmp->Layer;
     YUAN_Layer_SUM[ln]++;



      for(;;) //遍历所有连接
	  {





           //IF连接它的元是激发状态
           if(YUAN->ID_return_P(linker_tmp->linker_ID) ->state==1)
             {  

/*
              //W统计所有影响该元激发的因素，进行求和 
              
              W=W + linker_tmp->linker_weight + (YUAN->ID_return_P (linker_tmp->linker_ID) ->E) * WL;
			  //W=W + linker_tmp->linker_weight ;
*/

aE=YUAN->ID_return_P (linker_tmp->linker_ID) ->E;
bE=tmp->E;

if(aE>bE)
{
 W=W + linker_tmp->linker_weight + (aE-bE)* WL;
}

else
{
 W=W + linker_tmp->linker_weight;

}






             }








          if(_Run_Forgot==1 && Run_Forgot==1) //运行遗忘
		  {
            if(linker_tmp->linker_weight>0)
			{
			  linker_tmp->linker_weight-=Forgot_Weight;
			  if(linker_tmp->linker_weight<=0) linker_tmp->linker_weight=0;
			}
            else if(linker_tmp->linker_weight<0)
			{
              linker_tmp->linker_weight+=Forgot_Weight;
			  if(linker_tmp->linker_weight>=0) linker_tmp->linker_weight=0;
			}


            if(linker_tmp->linker_weight==0)//IF连接是0就消失
			{

             YUAN->Del_a_link(linker_tmp->linker_ID,tmp->ID);
			}

		  }









           if(linker_tmp->next==NULL)
             {
              break;
             }

           linker_tmp=linker_tmp->next;      

	  }  //遍历所有连接END

     }





   if(W!=0) 
   {
	   tmp->E =0;
   tmp->E = W + tmp->E_X ; // 反应强度为所有激活的连接因素

   }

   if(W==0 && tmp->E_X!=0) //无连接的刺激，但有增益
   {
	   tmp->E =0;
     tmp->E = W + tmp->E_X ; 
   }



      if(tmp->E!=0)
	  {
       tmp->E-=E_minus;   // 反应强度衰减
       if(tmp->E<0) tmp->E=0;
      }







   //元的 临界值 和 疲劳值 判断来决定状态
   if(tmp->E >= tmp->threshold + tmp->fag) //激活因素大于阀值 则激活

     {
      if(tmp->state==0)//原来是状态是0
        {

              tmp->state=2;
              
              tmp->Learn_Ready_Time=Learn_Ready_Time_MAX;

        }
      else
        {

        }

     }

    else if (tmp->E < tmp->threshold) //激活因素小于阀值 则不激活
     {
      if(tmp->state==1 )//原来是状态是1
        {
              tmp->state=0;


            //对所有被该元连接的元的连接增加F_X,强度为连接值 衰减补丁
            tmpY=YUAN;

             for(;;)
             {
    
    

               if(tmpY->linker->Find_linker_ID(tmp->ID)==1) 
                 {
                  tmpY->E_X+= YUAN->Get_linker_weight(tmp->ID,tmpY->ID);

       
                 }

               if(tmpY->next==NULL)  { break;  }

               tmpY=tmpY->next;

             }


 
	    }



     }




 //准备激活机制
    if(tmp->state==2) 
	{
        //间接激活理论
        //激活数据表里以“是”标签开头的元
      Find_YUAN_Contacts_Label_Activation_YUAN(tmp,"<是>",80);//激活<是>标签开头的联系表中的数据 对应的元
	  Find_YUAN_Contacts_Label_Inhibit_YUAN(tmp,"<不是>",80);//抑制<不是>标签开头的联系表中的数据 对应的元

      Find_YUAN_Contacts_Label_Activation_YUAN(tmp,"<因果>",80);//激活<因果>标签开头的联系表中的数据 对应的元

     Find_YUAN_Contacts_Label_Activation_YUAN(tmp,"<包含>",70);//激活<包含>标签开头的联系表中的数据 对应的元
      tmp->state=1;

	}




 //学习机制
    if(tmp->state==1) 
       { 
        if(Run_Learn==1)
          {
           tmp->Learn_Ready_Time--;
           if(tmp->Learn_Ready_Time<=0)
             {
              tmp->Learn_Ready_Time=Learn_Ready_Time_MAX;
              tmp->Learning(); //学习机制
           

             }

         }
 
       }  




     //疲劳值变化

     if(tmp->state==1)
       {
         float fag_x = (float)(fag_add/20 *tmp->Layer );  //疲劳增加根据层级越高越大
         tmp->fag += fag_x + tmp->E/10000;
 
       }

     else if(tmp->state==0)
       {
         tmp->fag -= fag_minus;
         if(tmp->fag <= 0) tmp->fag=0;

       }

 



     if(tmp->E_X!=0)  //活跃强度增益值变化
	 {
      if(tmp->E_X>0) 
        {
         tmp->E_X-=0.5f;
         if(tmp->E_X<=0) tmp->E_X=0;
        }

      if(tmp->E_X<0) 
        {
         tmp->E_X+=0.5f;
         if(tmp->E_X>=0) tmp->E_X=0;
        }
	 }





    if(tmp->ID!=0) 
	{
	 YuanSum++;//统计元总数
     YuanContactsSum += tmp->Contacts->Get_Sum();//统计联系表个数
	}


    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END


YUAN_SUM=YuanSum;
YUAN_CONTACTS_SUM=YuanContactsSum;
//delete tmp;
// delete linker_tmp;
//delete tmpY;
}











void CAiQiDlg::Draw_Face(int x, int y,int Kind,CDC *pDC) //画表情
{

  int dx;

  CBitmap bitmap;   //创建图位对象
  bitmap.LoadBitmap(IDB_AiQiDlg_Pic_Face);  //加载图位对象 ID

  CDC dcMemory;  //创建CDC对象
  dcMemory.CreateCompatibleDC(pDC);  //创建与pDC兼容的内存设备环境
  dcMemory.SelectObject(&bitmap);  //将图位选入内存设备环境中

  if(Kind>=0 && Kind<=10) dx=Kind*188;
  else dx=0;


   pDC->BitBlt(x,y,188,188,&dcMemory,dx,0,SRCCOPY);  //将内存设备环境复制到当前设备环境中




}





void CAiQiDlg::Change_Face(int x, int y,CDC *pDC) //变表情
{
 int Kind=0;

 if(Think_flag==1) Kind=1;

 if(User_Answer_Flag==1)   Kind=4;

 if(AI_YES_Flag==1)  Kind=2;

 if(AI_NO_Flag==1)  Kind=9;

 if(Waiting_For_Assessment_Flag==1) 
 { 
	 Kind=6;
     if(Think_flag==1) Kind=1;
 }

 if(AI_Have_Feelings_Flag==1) Kind=8;

 if(AI_Welcome_Flag==1) Kind=3;


 if(AI_Happy_Flag==1) Kind=5;
 if(AI_Sad_Flag==1) Kind=7;

 Draw_Face(x, y,Kind,pDC); //画表情


}

void CAiQiDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

   OnEnter();




}




















































void CAiQiDlg::Inhibitory_Layer_YUAN(int Layer) //抑制某层的所有元
{
  YUAN_UNIT *tmp=YUAN;


  for(;;)
  {
    


    if(tmp->Layer==Layer) 
      {
       tmp->state=0;
       tmp->E=0;
	   tmp->E_X=0;
      }

    if(tmp->next==NULL)  {  break;  }

    tmp=tmp->next;

  }





}






CString CAiQiDlg::String_mc_format(CString text) //把用[]框起来的特殊名词格式化 分词后整理
{
 int i=0,zz=0;
 CString tt,tmpch;

 int end=0;

 if(text.IsEmpty()==1)  return text;  //检查字符串是否为空


 //text.Replace( " 【", "[" );
 //text.Replace( " 】", "]" ); 


   while(1)   // 检测[]是否对称
  {
   if(text[i]=='\0') //流的末尾  
          {
           break; //启动关闭
          } 

       if(text[i]=='[') 
         { 
           zz=1;
         }

       if(text[i]==']') 
        {
          if(zz==1) zz=2;
         }


    i++;


  }

 if(zz!=2)  return text;


 i=0; zz=0;

   while(1)   // 检测[]是否对称
  {
   if(text[i]=='\0') //流的末尾  
          {
           break; //启动关闭
          } 

       if(text[i]=='[') 
         { 
           tt+=" ";
           i++;

           while(1)
               {
                 if(text[i]==' ') 
                  {
                    i++;
                    continue;

                  }

                 if(text[i]==']') 
                  {
                   tt+=" ";
                   zz=1;
                    
                    break;

                  }

                 tt+=text[i];
                 i++;

               }


         }

	   if(zz==1)
	   {
         zz=0;
	   }
      else
	  {
        tt+=text[i];

 

	  }

       i++;



  }



return tt;



}










CString CAiQiDlg::ZWFC(CString text)   //中文分词
{
  
  CString TT=text;

  TT.Replace( "？", "?" ); //防止 中文？会变成空 bug



     //防止 分词出错意外跳出 bug
     if(TT=="!"){ TT="-.-";}
     if(TT=="\"") {TT="-.-"; }
     if(TT=="'") {TT="-.-"; }
     if(TT=="，") {TT="-.-"; }
     if(TT==".") {TT="-.-"; }
     if(TT=="。") {TT="-.-"; }
	 if(TT==",") {TT="-.-"; }





  string fs=TT.GetBuffer(0);

  fs = D.SegmentWord(fs); //对字符串进行中文分词

  TT = fs.c_str();  

  TT=String_mc_format(TT); //把用[]框起来的特殊名词格式化 分词后整理

 return TT;
}






void CAiQiDlg::Format_String(CString *_text) //格式化字符串 去掉空格 和 *
{
 

 int i=0;
 CString tt,tmpch;

 CString text=*_text;

 int end=0;

 if(text.IsEmpty()==1)  return;  //检查字符串是否为空
 text.TrimLeft(); //去除左边的空格
 text.TrimRight(); //去除右边的空格



   while(1)  //替换* 边空格
  {

   if(text[i]=='\0') //流的末尾  
          {
           break; //启动关闭
          } 


     if(text[i]=='*') { text.SetAt(i,' '); }

    i++;

  }




   i=0;


tt.Empty();




 while(1)

 {


   while(1)  //跳掉前面的空格 
  {
   if(text[i]=='\0') //流的末尾  
          {
           end=1;break; //启动关闭
          } 

       if(text[i]==' ') {     i++; continue; }

  else {break;}

  }


  if(end==1) break;




  tmpch.Empty();

  for(;;)  //读取有空格的文字 
  {

   // tmpch.Format("%c",text[i]);

    tmpch+=text[i];

    i++;

    if(text[i]==' '  || text[i]=='\0') //发现文字 或者结束符
      {

  

    	if(text[i]=='\0') //流的末尾
		{
           tmpch+='\0';
           end=1;; //启动关闭
            break;
				   
		}

        tmpch+=' ';
        break;

      }



   }//for


    tt+=tmpch;



     



 }






*_text=tt;

}















int CAiQiDlg::Return_String_Words_Sum(CString text) //返回字符串中单词的数量
{
 
 int sum=0;
 int i=0;
 CString tt,tmpch;

 int end=0;

 if(text.IsEmpty()==1)  return 0;  //检查字符串是否为空



   while(1)  //跳掉前面的空格 和 *
  {
   if(text[i]=='\0') //流的末尾  
          {
           end=1;break; //启动关闭
          } 

       if(text[i]==' ') {     i++; continue; }
  else if(text[i]=='*') {     i++; continue;  }
  else {break;}

  }






 while(1)

 {


   while(1)  //跳掉前面的空格 和 *
  {
   if(text[i]=='\0') //流的末尾  
          {
           end=1;break; //启动关闭
          } 

       if(text[i]==' ') {     i++; continue; }
  else if(text[i]=='*') {     i++; continue;  }
  else {break;}

  }


  if(end==1) break;

  tt.Empty();

  for(;;)  //读取有空格的文字 
  {


    i++;

    if(text[i]==' ' || text[i]=='\0') //发现文字 或者结束符
      {
               

	if(text[i]=='\0') //流的末尾
	  {

           end=1;; //启动关闭

				   
	   }


        break;

      }



   }//for


 

 sum++;

     



 }



 return sum;

}














void CAiQiDlg::Return_String_SN_start_end(CString text,int SN,int *SN_start,int *SN_end) //返回字符串中 第SN个单词 偏移的地址 开始 结束
{
 
 int sum=0;
 int i=0;
 
 int n_start=-1,n_end=-1;



 int end=0;

 if(text.IsEmpty()==1)  end=1;  //检查字符串是否为空



   while(1)  //跳掉前面的空格 和 *
  {
   if(text[i]=='\0') //流的末尾  
          {
           end=1;break; //启动关闭
          } 

       if(text[i]==' ') {     i++; continue; }
 
  else {break;}

  }


 int iii=Return_String_Words_Sum(text); //返回字符串中单词的数量
 if(iii==0) end=1;
 if(iii<SN) end=1;

 while(1)

 {


   while(1)  //跳掉前面的空格 和 *
  {
   if(text[i]=='\0') //流的末尾  
          {
           end=1;break; //启动关闭
          } 

       if(text[i]==' ') {     i++; continue; }

  else {break;}

  }


  if(end==1) break;

  if(SN-sum==1) n_start=i;



  for(;;)  //读取有空格的文字 
  {


    i++;

    if(text[i]==' ' || text[i]=='\0') //发现文字 或者结束符
      {
               

	if(text[i]=='\0') //流的末尾
	  {

           end=1; //启动关闭

				   
	   }


	if(SN-sum==1)
	  {

            n_end=i-1; 

           end=1; //启动关闭

				   
	   }


        break;

      }



   }//for


 

 sum++;

     



 }



 *SN_start=n_start;
 *SN_end=n_end;

}














CString CAiQiDlg::Return_String_N_Word(CString text,int i) //返回字符串第N个单词
{

 int t_start,t_end;
 CString get_text;

 int SUM=Return_String_Words_Sum(text); //返回字符串中单词的数量

  get_text.Empty();

 if(SUM<i) return get_text;







   Return_String_SN_start_end(text,i,&t_start,&t_end); //返回字符串中 第SN个单词 偏移的地址 开始 结束


   get_text = text.Mid(t_start, t_end-t_start+1);



 return get_text; 
}







CString CAiQiDlg::Format_De_CString(CString text) //格式化带“的”字的字符串，并且去除“的”
{
 CString D_text;
 CString Word;
 CString QM_Word;



 int i;

 int SUM=Return_String_Words_Sum(text); //返回字符串中单词的数量

  for(i=1; i<=SUM ; i++)
  {
     Word=Return_String_N_Word(text,i); //返回字符串第N个单词

     if(Word=="的")
       {
         if(SUM>1 && i!=SUM)//不是第一个词 不是最后一个
           {

             if( IS_DC(Return_String_N_Word(text,i+1)) ) //后一个单词是动词
               {
                QM_Word=Return_String_N_Word(text,i-1);//得到前一个单词
                D_text.Replace( QM_Word+" ",  QM_Word ); //替换前面带空格的单词
				D_text+="的 ";
                continue;
               }


            QM_Word=Return_String_N_Word(text,i-1);//得到前一个单词
            D_text.Replace( QM_Word+" ",  QM_Word ); //替换前面带空格的单词


            Word=Return_String_N_Word(text,i+1); //得到后一个单词
            D_text+=Word;
            D_text+=" ";  //组合
            i+=1;
            continue;
           }

         if(i==SUM)//是最后一个
           continue;


       }


    D_text+=Word;
    D_text+=" ";
     
  }

 return D_text;

}







CString CAiQiDlg::Format_XRC_De_CString(CString text) //格式化字符串中形容词的“的”，去除“的”
{
 CString D_text;
 CString Word;
 CString QM_Word;



 int i;

 int SUM=Return_String_Words_Sum(text); //返回字符串中单词的数量

  for(i=1; i<=SUM ; i++)
  {
     Word=Return_String_N_Word(text,i); //返回字符串第N个单词

     if(Word=="的")
       {
         if(SUM>1 && i!=SUM)//不是第一个词 不是最后一个
           {

             if( IS_XRC(Return_String_N_Word(text,i-1)) ) //前一个单词是形容词
               {

                continue;
               }


           }


         if(i==SUM)//是最后一个
           continue;


       }


    D_text+=Word;
    D_text+=" ";
     
  }

 return D_text;

}








//用户回答  让电脑选择的（提问）元 和 用户的回答的词语之间建立联系
void CAiQiDlg::User_Answer_YUAN_Is( YUAN_UNIT *S_YUAN, CString text)
{
 CString tt;

 if(S_YUAN == NULL) return;



 //////////判断电脑选择的（提问）元的层级
 if(S_YUAN->Layer == 0)  //////////字符层
   {
    tt.Format("%s 是 %s",S_YUAN->name,text);

    //形式处理  带“是”的字符串   通过创生概念层1的元  联系字符与字符 （建立了X是Y的概念） 比如： 圆的 红的 甜的 是 苹果
    Form_Is_4(tt) ;
   }


 else if(S_YUAN->Layer == 1)  //////////概念层
  {


   YUAN_UNIT *new_YUAN_Y = NULL;

   int b=0;


   ///建立Y元 目标（符号）元

   b=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元

    if(b==-1) //没有 
	{
	 //建立新元
     YUAN->New();
	 new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,600),Xrand(10,360));
     YUAN->Set_name(new_YUAN_Y->ID,text);

     YUAN->Set_threshold(new_YUAN_Y->ID,new_YUAN_Y->threshold + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;
	}

    else //有
	{

	 new_YUAN_Y=YUAN->ID_return_P(b);
	}



    //设置连接

    if(YUAN->Find_linker(S_YUAN->ID,new_YUAN_Y->ID)==0) //原来和目标元没有连接
      {
          float fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10
          YUAN->Link(S_YUAN->ID,new_YUAN_Y->ID,60+fdz);  //连接元

      }


   





  }






}







void CAiQiDlg::Activation_YUAN(CString text,int power) //激活某个元
{
 int b;
 YUAN_UNIT *tmp;


   //根据字符串tt 处理  
    b=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元

     //如果没有
     if(b==-1) 
       {
         ;
       }

     //如果存在

       else
       {
         tmp=YUAN->ID_return_P(b);

         if(tmp->state==1)
           {

           }
         else if(tmp->state==0)
		{
         YUAN->Set_state(b,2);
		}


        YUAN->Add_E_X(b,(float)power);//增加表达强度效应

       }




}




void CAiQiDlg::Inhibit_YUAN(CString text,int power) //抑制某个元
{
 int b;
 YUAN_UNIT *tmp;


   //根据字符串tt 处理  
    b=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元

     //如果没有
     if(b==-1) 
       {
         ;
       }

     //如果存在

       else
       {
         tmp=YUAN->ID_return_P(b);

         if(tmp->state==1)
           {

           }
         else if(tmp->state==0)
		{
         
		}


        YUAN->Add_E_X(b,((float) -power));//增加表达强度效应



       }




}









void CAiQiDlg::Activation_Text_YUAN(CString text) //激活字符串里的所有元
{

 int i;


 int t_start,t_end;
 CString get_text;

 int YUAN_SUM = Return_String_Words_Sum(text); //返回字符串中单词的数量






       if(YUAN_SUM == 0) goto Activation_Text_YUAN_END;
 

 
 for(i=1;i <= YUAN_SUM ; i++)
 {
   


   get_text.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //返回字符串中 第SN个单词 偏移的地址 开始 结束

   //get_text = input_text.Mid(t_start, t_end-t_start+1);
   get_text = text.Mid(t_start, t_end-t_start+1);

   Activation_YUAN(get_text,20); //激活某个元 状态变2












 }







 Activation_Text_YUAN_END:;


}












void CAiQiDlg::Recognition_Command(int *Command_Flag,CString *input_text)  //识别语句命令
{
  CString text_DC;
  CString LL,RR;
 CString text=*input_text;







 if(text.Find("@ 查看 概念") !=-1 )
  {




   text.Replace( "@ 查看 概念", NULL );

   *input_text=text;
   *Command_Flag=30;




   return;

  }



 if(text.Find("@ 删除 概念 数据") !=-1 )
  {




   text.Replace( "@ 删除 概念 数据", NULL );
   text.Replace( "（", "(" );
   text.Replace( "）", ")" );

   *input_text=text;
   *Command_Flag=32;




   return;

  }

 if(text.Find("@ 删除 概念") !=-1 )
  {




   text.Replace( "@ 删除 概念", NULL );

   *input_text=text;
   *Command_Flag=31;




   return;

  }





 if(text.Find("@ 分词") !=-1 )
  {




   text.Replace( "@ 分词", NULL );

   *input_text=text;
   *Command_Flag=36;




   return;

  }


 if(text.Find("@ 网上 学习") !=-1 )
  {




   text.Replace( "@ 网上 学习", NULL );

   *input_text=text;
   *Command_Flag=35;




   return;

  }


 if(text.Find("天气") !=-1 )
  {

   CString text0=text;

   text.Replace( "天气", NULL );


   int Words_Sum= Return_String_Words_Sum(text); //返回字符串中单词的数量
   if(Words_Sum==1)
     {



      *input_text=text;
      *Command_Flag=37;


      return;

     }

   else
    {
     text=text0;
    }

  }




 if(text.Find("@ 天气") !=-1 )
  {




   text.Replace( "@ 天气", NULL );

   *input_text=text;
   *Command_Flag=37;




   return;

  }


 if(text.Find("@ 网页") !=-1 )
  {




   text.Replace( "@ 网页", NULL );

   *input_text=text;
   *Command_Flag=50;




   return;

  }



 if(text.Find("如果") !=-1 && text.Find("那么") !=-1)
  {


   *input_text=text;
   *Command_Flag=3;

   return;

  }


 if(text.Find("上句") !=-1 && text.Find("下句") !=-1)
  {



   *input_text=text;
   *Command_Flag=7;

   return;

  }




 //去除额外标点
   text.Replace( "，", " " );
   text.Replace( ",", " " );
   text.Replace( "。", " " );
   text.Replace( ".", " " );


   text.Replace( "你 ", "AiQi " );
   text.Replace( "我 ", "主人 " );

   text.Replace( "谁 ", "什么 " );





//防止都是空格 空格会变空出错
int e=0;
int char_n=text.GetLength();;
	CString cc;
for (int i=1; i<char_n; i++)
{

	cc=text.GetAt(i);
  if(cc == " ") { e++;}

}


cc=text.GetAt(0);
if(e==char_n-1 && cc ==" "){text="-.-!";}

if(text.IsEmpty()) {text="-.-!";}


 //AfxMessageBox(text);




 if(text.Find("@ 激活") !=-1 )
  {

   text.Replace( "@ 激活", NULL );

   *input_text=text;
   *Command_Flag=40;

   return;

  }


 if(text.Find("@ 格式化 的") !=-1 )
  {

   text.Replace( "@ 格式化 的", NULL );

   *input_text=text;
   *Command_Flag=45;

   return;

  }






 if(text.Find("记住 ") !=-1 )
  {

   text.Replace( "记住 ", NULL );

   *input_text=text;
   *Command_Flag=2;


   return;

  }







 if(text.Find("属于") !=-1 )
  {



   text.Replace( "属于", "是" );



   *input_text=text;
   *Command_Flag=3;

   return;

  }






 //逻辑提问处理
 if(text.Find("?") !=-1||text.Find("吗") !=-1||text.Find("是不是")!=-1 )
  {


   text.Replace( "?", NULL );
   text.Replace( "了", NULL );
   text.Replace( "吗", NULL );


   if(text.Find("是不是")!=-1)
   {
    text.Replace( "是不是", "XDongCi" );

    Split_X_String(text,"XDongCi",&LL,&RR); //把字符串以X为分割，变成2个字符窜


    if(!Find_Text_DC(RR, &text_DC)) //后面没有动词了
	{
    text.Replace( "XDongCi",  "是" );

	}
	else
	{
     text.Replace( "XDongCi", NULL );//后面有动词

	}

   }

    text.Replace( "不",  "不 " );



 int Words_Sum= Return_String_Words_Sum(text); //返回字符串中单词的数量

				if(Words_Sum==0) //单词数量为0  防止输入变成空
				{
					
                     text="?";  

					 *input_text=text;
					 *Command_Flag=1;
                     return;
				}

				else if(Words_Sum==1) //单词数量为1
				{
					
                   if(Return_String_N_Word(text,1)=="是") //是吗 的处理
				   {

					 *input_text=text;
					 *Command_Flag=1;
                     return;
				   }

				}




   *input_text=text;
   *Command_Flag=10;

   if(text.Find("什么") !=-1)
   *Command_Flag=11;

   return;

  }


 //逻辑提问处理 什么
 if(text.Find("什么") !=-1 )
  {

    text.Replace( "不",  "不 " );

    if(!Find_Text_DC(text, &text_DC)) //后面没有动词了
	{
    text.Replace( "什么",  NULL );

      int Words_Sum= Return_String_Words_Sum(text); //返回字符串中单词的数量

				if(Words_Sum==0) //单词数量为0
				{
					

                     text="?";
				}



       *input_text=text;
	   *Command_Flag=1;
      return;
	}


	else //有动词
	{


	}


   *input_text=text;
   *Command_Flag=11;

   return;

  }


/*
 if(Recognition_ZWB_Form(text)==1 )
  {






   *input_text=text;
   *Command_Flag=8;




   return;

  }
*/


    *input_text=text;
   *Command_Flag=1;

}







//我的RichEdit控件输出
void CAiQiDlg::MyRichEdit_TextOut(CRichEditCtrl *PMyRichEdit,unsigned long color,int size,int bold,CString str)
{

//设置字体
CHARFORMAT cf;
ZeroMemory(&cf, sizeof(CHARFORMAT));
cf.cbSize = sizeof(CHARFORMAT);

cf.dwMask|=CFM_BOLD;
if(bold==0)
cf.dwEffects&=~CFE_BOLD;//设置粗体，用cf.dwEffects|=CFE_BOLD;
else
cf.dwEffects|=CFE_BOLD;

cf.dwEffects&=~CFE_BOLD; //普通

cf.dwMask|=CFM_ITALIC;
cf.dwEffects&=~CFE_ITALIC;//设置斜体，用cf.dwEffects|=CFE_ITALIC;
cf.dwMask|=CFM_UNDERLINE;
cf.dwEffects&=~CFE_UNDERLINE;//设置斜体，用cf.dwEffects|=CFE_UNDERLINE;
cf.dwMask|=CFM_COLOR;
cf.crTextColor = color;//设置颜色
cf.dwMask|=CFM_SIZE;
cf.yHeight =size;//设置高度
cf.dwMask|=CFM_FACE;
strcpy_s(cf.szFaceName ,_T("微软雅黑"));//设置字体
//strcpy_s(cf.szFaceName ,_T("宋体"));//设置字体
//strcpy_s(cf.szFaceName ,_T("Fixedsys"));//设置字体
PMyRichEdit->SetSelectionCharFormat(cf); 



PMyRichEdit->SetSel(-1, -1);
PMyRichEdit->ReplaceSel( (LPCTSTR)str ); 


}



void CAiQiDlg::TEXT_OUT_BOX_SAY_3(CString text,int flag) //数据在屏幕上输出  使用RichEdit控件
{
  CString SYS_text;
  CString AI_text;
  CString Ren_text;

  CString _MainTextOut;

  CTime time = CTime::GetCurrentTime();
  CString TTime = time.Format("%H:%M:%S");



  SYS_text.Format(">系统： ");
  AI_text.Format(">AiQi： ");
  Ren_text.Format(">主人： ");



  unsigned long Tcolor;

         if(flag==0) {  _MainTextOut = SYS_text;  MyRichEdit_TextOut(&MyRichEdit,RGB(255,0,224),260,0, _MainTextOut);  Tcolor=RGB(50,50,50);}
    else if(flag==1) {  _MainTextOut = AI_text;  MyRichEdit_TextOut(&MyRichEdit,RGB(0,0,255),260,0, _MainTextOut);  Tcolor=RGB(2,153,123);}
    else if(flag==2) {  _MainTextOut = Ren_text;  MyRichEdit_TextOut(&MyRichEdit,RGB(0,0,255),260,0, _MainTextOut);  Tcolor=RGB(0,0,0);}
    else  {  _MainTextOut = " ";  }

MyRichEdit_TextOut(&MyRichEdit,RGB(179,179,179),260,0, TTime);

  _MainTextOut = "\r\n"; //换行
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,0, _MainTextOut);

  _MainTextOut = " ";
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,0, _MainTextOut);

  _MainTextOut =text;
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,1, _MainTextOut);



  _MainTextOut = "\r\n"; //换行
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,0, _MainTextOut);






   MyRichEdit.SetSel(-1, -1); // 在RichEdit控件最后行输出
   MyRichEdit.ReplaceSel( (LPCTSTR) _MainTextOut ); 





    MyRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM,0);  //跳转到最后一行


}




void CAiQiDlg::OnEnter() //按了回车键的响应
{

UpdateData();
if( input_text=="") return;


 

 CString tt;
 CString LL,RR;
 CString text_DC;

       UpdateData(); //更新输入信息


               if(Waiting_For_Assessment_Flag==1)//等待用户评估 忽略其他操作
                 { 

				   Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;
				  
                   if(input_text=="是"||input_text=="是的"||input_text=="对"||input_text=="yes")
				   {

                     Waiting_For_Assessment_Flag=0;

                   // UpdateData();

                    TEXT_OUT_BOX_SAY_3(input_text,2); //数据在屏幕上输出


                    input_text.Empty(); //	清空输入
                    
                   UpdateData(0);
				    // m_edit.LineScroll(m_edit.GetLineCount()); //把输入框拖条移到最下面

				    Waiting_For_Assessment_Flag=0;

					AI_Happy_Flag=1;
 

					CString ttt;
 


                    Return_Award_To_AI_X(P_layer_0_max_E_YUAN_AI_Think_Choose,AI_Think_Choose_Contacts_Number);  //奖励AI  对最强选择元的肯定

				    return   ;

				   }


                   if(input_text=="不"||input_text=="不是"||input_text=="否"||input_text=="错"||input_text=="no")
				   {
                       Waiting_For_Assessment_Flag=0;
                   // UpdateData();

                    TEXT_OUT_BOX_SAY_3(input_text,2); //数据在屏幕上输出

                    input_text.Empty(); //	清空输入
                    
                      UpdateData(0);
					  //m_edit.LineScroll(m_edit.GetLineCount()); //把输入框拖条移到最下面

				    Waiting_For_Assessment_Flag=0;

					AI_Sad_Flag=1;


					Return_Punishment_To_AI_X(P_layer_0_max_E_YUAN_AI_Think_Choose,AI_Think_Choose_Contacts_Number);  //惩罚AI  对最强选择元的否定
                    

				    return  ;

				   }

                 }




         if(Flow_run==0) //流没有运行
		 {
           UpdateData();

            Enter=1;

           //显示用户输入的数据
			TEXT_OUT_BOX_SAY_3(input_text,2); //数据在屏幕上输出 






//========================
//中文分词
if(Run_FC_Flag==1)
{


   input_text = ZWFC(input_text);//中文分词




   //input_text=Format_De_CString(input_text); //格式化带“的”字的字符串，并且去除“的”

   input_text=Format_XRC_De_CString(input_text);  //格式化字符串中形容词的“的”，去除“的”

  FC_text = input_text;
}
//========================

int jxs=0;

CString xt=input_text;
xt.Replace(" ", NULL );
if(xt=="继续" || xt=="继续说" || xt=="然后呢" || xt=="还有呢" )
{
 if(TextInputBox[0].text.IsEmpty()!=1)
   {
    input_text=TextInputBox[0].text;
   }
 else
   {
    input_text="?";

   }

 jxs=1; //判断继续说
}


//---------------------------



//比较输入的前3句语句是否相同



      for(int n=TextInputBox_String_SUM-1;n>0;n--)
         {

          TextInputBox[n].text=TextInputBox[n-1].text;


         }



 TextInputBox[0].text=input_text;


      int bj=0;
      for(int n=0;n<TextInputBox_String_SUM-1;n++)
         {

          if(TextInputBox[n].text==TextInputBox[n+1].text) bj++;


         }

     if(bj==TextInputBox_String_SUM-1  && jxs==0)
       {

        int KeNeng=Xrand(0,100); //生成可能性

        if(KeNeng>=0 && KeNeng<=40)
          {
           TEXT_OUT_BOX_SAY_3("主人，换个话题聊吧",1); //数据在屏幕上输出
          }
        else if(KeNeng>40 && KeNeng<=70)
          {

           TEXT_OUT_BOX_SAY_3("主人，你是复读机吗，聊点别的吧",1); //数据在屏幕上输出
          }
        else
          {

           TEXT_OUT_BOX_SAY_3("主人，怎么总是这句啊，问点别的吧",1); //数据在屏幕上输出
          }

       }

//---------------------------




      //-------------------判定语句类型

          Command_Flag=1; //默认设定是普通激活


		  CString input_text_X=input_text; //保存整理后的输入


          Recognition_Command(&Command_Flag,&input_text_X);  //识别语句命令 并且把输入信息整理翻译成普通句



            if(input_text_X=="") 
              {
                TEXT_OUT_BOX_SAY_3("无法处理，请输入正确内容。",1); //数据在屏幕上输出

				 input_text.Empty(); //	清空输入

		         UpdateData(0);

                return;  
              }


     //-------------------



			if(User_Answer_Flag==1 && User_Answer_Time>0)  //提问开启后的反馈 用户回答有效时间
			{

			  //判断当前电脑提问的类型 
			  if(AI_Question_Kind==1) //1对元存储的字符串提问
			  {
			   Command_Flag=5;
			  }


			  else if(AI_Question_Kind==2) //2对于用户输入的字符串提问
			  {
 			  Command_Flag=6;
			  }



			}
 


/*
CString DD;  // Command_Flag 调试追踪
DD.Format("Command_Flag=%d\n输入=[%s]",Command_Flag,input_text_X);
AfxMessageBox(DD);
*/


      //-------------------根据类型处理

	    	if(Command_Flag==1)  //普通 激活
			{





			 Think_flag=1; 


              Inhibitory_Layer_YUAN(0); //抑制0层的所有元
			   Inhibitory_Layer_YUAN(1); //抑制1层的所有元
			    Inhibitory_Layer_YUAN(2); //抑制2层的所有元
 






              Input_Activation_YUAN(input_text_X);  //通过输入的字符串 激活元 模糊匹配的
 

			  CString D_YUAN_NAME;
			  D_YUAN_NAME=input_text_X;
              D_YUAN_NAME.Replace( " ", NULL );
			  Activation_YUAN(D_YUAN_NAME,50); //激活特定元

			  Input_Activation_YUAN_By_Contacts_2(input_text_X);  //通过对输入的字符串和元联系表比较，来增加元活跃度 比较<是><内容>标签
             
			}

         //-----------------
	    	else if(Command_Flag==2)  //记住， 建立知识 
			{

  
		



CString DC; //谓语动词

input_text_X.Replace( "不", "不 " ); //补丁 带“不”的词，把“不”字拆开

  //查找文本中的第一个动词，并且返回它
  if(Find_Text_DC(input_text_X, &DC)) 
    {

     //AfxMessageBox("有动词");


             if(Return_String_Words_Sum(input_text_X)==1) //返回字符串中单词的数量
			 {
              int r=Form_Remember_X(input_text_X); //形式处理  记忆字符串 生成一个概念 


              if(r==1)  //1正常建立

                {


			      TEXT_OUT_BOX_SAY_3("好的，记住了。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				  goto Command_Flag_2_END;

				 }
			 }


             if(Recognition_SXBQ_Form(input_text_X)==1 ) //是带标签记忆的建立语句格式------

               {

                  //AfxMessageBox("这是带标签语句，建立命题格式");



                 //标签记忆的建立函数
                 Form_Create_SXBQ_EX(input_text_X); //带有结果输出的标签记忆建立函数

          
                   goto Command_Flag_2_END;

               }



             if(Recognition_ZWB_Form(input_text_X)==1 ) //是主谓宾语句格式------

               {

                  //AfxMessageBox("这是主谓宾语句，建立命题");

                 //[形式处理] 建立命题  格式： 记住 S谓P  、 记住 S
                 Form_Create_ZWB_EX(input_text_X); //带有结果输出的命题建立函数

               
                 goto Command_Flag_2_END;

               }







    }

  else   //如果没有动词
   {


     //AfxMessageBox("无动词");

     int r=Form_Remember_X(input_text_X); //形式处理  记忆字符串 生成一个概念 


              if(r==1)  //1正常建立

                {


			      TEXT_OUT_BOX_SAY_3("好的，记住了。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				 }


  }




   Command_Flag_2_END:;










			}





        //-----------------  




	    	else if(Command_Flag==3)  //形式处理，如果x那么Y  ，建立概念与概念之间的条件反射关系，输入X输出Y
			{
            



              if(Form_IF_X_THEN_Y(input_text_X)==1)
                {
                  CString XT;
                  XT.Format("好的，我记下了。%s",input_text_X);
                  TEXT_OUT_BOX_SAY_3(XT,1); //数据在屏幕上输出
 			      AI_YES_Flag=1;
                }
 
              else
                {
                 TEXT_OUT_BOX_SAY_3("语法错误！请用以下语法输入：如果X那么Y，X和Y是句子",1); //数据在屏幕上输出

                }




			}

/*

          //-----------------

	    	else if(Command_Flag==4)  //测试
			{

              


                Split_X_String(input_text_X,"和",&LL,&RR); 

                int pf=Assess_To_Two_String(LL,RR); //对两个字符串相似度打分

                CString XT;
                XT.Format("两个字符串评分为%d",pf);
                TEXT_OUT_BOX_SAY_3(XT,0); //数据在屏幕上输出
			 



             
			}

*/

        //-----------------  
	    	else if(Command_Flag==7)  ////形式处理，上下句关系，输入X输出Y
			{
            



              if(Form_ShangXiaWen(input_text_X)==1) //形式处理，上下句关系，输入X输出Y
                {
 
                  TEXT_OUT_BOX_SAY_3("好的，上下句已经记住。",1); //数据在屏幕上输出
 			      AI_YES_Flag=1;
                }
 
              else
                {
                 TEXT_OUT_BOX_SAY_3("语法错误！请用以下语法输入：上句X下句Y，X和Y是句子",1); //数据在屏幕上输出

                }




			}
          //-----------------



          //-----------------
/*
	    	else if(Command_Flag==8)  //识别主谓宾语句格式
			{

              


 
                CString XT;
                XT.Format("主谓宾语句格式");
                TEXT_OUT_BOX_SAY_3(XT,0); //数据在屏幕上输出

 



              int r=Form_Create_ZWB(input_text_X); //[形式处理] 建立命题  格式： 记住 S谓P  、 记住 S


              if(r==1)  //1正常建立

                {


			      TEXT_OUT_BOX_SAY_3("哦，记住了。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				 }

              else if(r==2)  //2以前有关系强化

                {


			      TEXT_OUT_BOX_SAY_3("恩，我觉得也是这样的。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				 }

			  else

			     {
                  TEXT_OUT_BOX_SAY_3("语法错误！",1); //数据在屏幕上输出

			     }


			




			 



             
			}
          //-----------------

*/





	    	else if(Command_Flag==30)  //查看命令 查看@概念名
			{


                          //命令：显示元的数据
                          Cmd_Display_YUAN_Data( input_text_X );




             
			}



          //-----------------

	    	else if(Command_Flag==31)  //删除概念命令 @删除概念 概念名
			{


                          //命令：删除元
                          Cmd_Del_YUAN( input_text_X );




             
			}




          //-----------------

	    	else if(Command_Flag==32)  //删除概念数据命令 @删除概念数据 概念名(数据ID)
			{
                         CString NAME;
                         CString TT;
                         CString TX=input_text_X;
                         int X_weizhi;
                         int X_ID;


                         TX.Replace( " ", NULL );


                           if(TX.Find("(")!=-1 && TX.Find(")")!=-1)
                             {



                                X_weizhi=TX.Find("(");
                                NAME=TX.Left(X_weizhi);
                                if(NAME.IsEmpty()!=1)
                                  {

                                    TX.Replace( NAME, NULL );
                                    TX.Replace( "(", NULL );
                                    TX.Replace( ")", NULL );





                                     X_ID=atoi(TX);

                                   //TT.Format("概念名=%s 数据%d",NAME,X_ID);
                                   //TEXT_OUT_BOX_SAY_3(TT,0); //数据在屏幕上输出

									 //命令：删除元数据
                                     Cmd_Del_YUAN_Contacts(NAME,X_ID);


                                  }
                                else
                                  {
                                   TT.Format("错误，概念名不能为空！");
                                   TEXT_OUT_BOX_SAY_3(TT,0); //数据在屏幕上输出
                                  }



                               }
                           else
                             {
                              TT.Format("命令输入格式错误，缺少()。");
                              TEXT_OUT_BOX_SAY_3(TT,0); //数据在屏幕上输出
                            }

             
			}



         //-----------------




	    	else if(Command_Flag==35)  //从网络上学习词条
			{


                     CString CT=input_text_X;
					 CString TX;    

                     CT.Replace( " ", NULL );

                     int n = Learn_CiTiao_From_Web(CT); //从网络上学习词条信息

             

                         TX.Format("学习[%s]词条完毕，共学习了%d条新数据",CT,n);
                         TEXT_OUT_BOX_SAY_3(TX,1); //数据在屏幕上输出
             
			}

          //-----------------



	    	else if(Command_Flag==36)  //分词命令 分词@语句
			{


                          TEXT_OUT_BOX_SAY_3(input_text_X,0); //数据显示在屏幕上 
                          




             
			}
         //-----------------



	    	else if(Command_Flag==37)  //从网络上获取天气信息
			{

                           CString x=input_text_X;
                           x.Replace( " ", NULL );

			               CString TX;    
                          CString TT;

                          CString city_number;


                            CString CityName=x;




                          

                            city_number=Get_City_Weather_Number(CityName);  //返回城市天气代码

                            if(city_number=="没有找到")
                              {
                               TT.Format("没有相关地区的天气数据。");
                               TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                              }
                            else
                              {


                                //TT.Format("城市代码=%s",city_number);
                                //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                               CString CT;
                               CT=Get_Weather_Information_From_Web(city_number); //从网络上获取天气信息并返回

                                   TX= CityName + "  "+ CT +"C";  
      
                               TT.Format("%s",TX);
                               TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


                              }


             
			}

         //-----------------



	    	else if(Command_Flag==40)  //测试 激活
			{

              Input_Activation_YUAN(input_text_X);  //输入激活元

			 



             
			}


          //-----------------







	    	else if(Command_Flag==45)  //测试  格式化的
			{

                CString XT;
				CString TT;

                //TT=Format_De_CString(input_text_X); //格式化带“的”字的字符串，并且去除“的”
                TT=Format_XRC_De_CString(input_text_X);  //格式化字符串中形容词的“的”，去除“的”

                XT.Format("%s",TT);
                TEXT_OUT_BOX_SAY_3(XT,0); //数据在屏幕上输出

			 



             
			}


          //-----------------

	    	else if(Command_Flag==50)  //测试
			{


              CString TWeb;
              CString TX;

			  TWeb="http://"+input_text_X;

			     TWeb.Replace( " ", NULL );

               ShellExecute(NULL, "open", TWeb , NULL, NULL, SW_SHOWNORMAL);

                         TX.Format("正在帮您打开网站：%s",TWeb);
                         TEXT_OUT_BOX_SAY_3(TX,1); //数据在屏幕上输出



             
			}
         //-----------------

	    	else if(Command_Flag==5)  //用户对元存储的字符串提问 的回答
			{
             CString TT,TX;

             TT=input_text_X;

			 TT.Replace( " ", NULL );
             TT.Replace( P_User_Answer_objective_YUAN->name + "是", NULL );
			 TT.Replace( "是", NULL );

             Form_X_IS_Y( P_User_Answer_objective_YUAN->name, TT);  //[形式处理] 建立X是Y关系  生成两个独立的概念





                         TX.Format("哦，已记下，%s 是 %s",P_User_Answer_objective_YUAN->name,TT);
                         TEXT_OUT_BOX_SAY_3(TX,1); //数据在屏幕上输出





			 P_User_Answer_objective_YUAN= NULL;

			 User_Answer_Flag=0;

             AI_Question_Kind=0; 





			 AI_YES_Flag=1;



			}

      //-------------------

	    	else if(Command_Flag==6)  //用户对于输入的字符串提问 的回答
			{
             CString TX;

                        

                         Form_X_QA( AI_Question_text, input_text_X );  //[形式处理] 建立X概念 问与答关系  X概念生成一条文本数据用来回答

                         TX.Format("哦，知道了，%s 回答是 %s",AI_Question_text, input_text_X);
                         TEXT_OUT_BOX_SAY_3(TX,1); //数据在屏幕上输出




			 User_Answer_Flag=0;

                         AI_Question_Kind=0; 


   


			 AI_YES_Flag=1;



			}

      //-------------------

	    	else if(Command_Flag==10)  //逻辑提问 求真值 开关"？" "?"
			{




			 Think_flag=1; 


			   Inhibitory_Layer_YUAN(0); //抑制0层的所有元
			   Inhibitory_Layer_YUAN(1); //抑制1层的所有元
			   Inhibitory_Layer_YUAN(2); //抑制2层的所有元

              if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
               Activation_YUAN(Last_Layer_0_Max_E_YUAN_Name,100); //激活上次对话（最近一次）最强活跃元



               //补丁 字符串过长而评分无法激活主语元，忽视了主语的激活 
               Find_Text_DC(input_text_X, &text_DC);//查找文本中的第一个动词，并且返回它

					   if(text_DC.IsEmpty()!=1)//=========有动词
					   {

                         Split_X_String(input_text_X,text_DC,&LL,&RR); //把字符串以X为分割，变成2个字符窜


 						  if(LL=="他 " || LL=="她 " ||LL=="它 "||LL=="这 ") //缺省情况下，用来补全上一句的主语
						   {
							   if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
                                   LL=Last_Layer_0_Max_E_YUAN_Name;
						   }

                          Input_Activation_YUAN(LL);  //通过输入的字符串 激活元

					   }

					   else
					   {

			            Input_Activation_YUAN(input_text_X);  //通过输入的字符串 激活元
					   }

			}

      //-------------------

	    	else if(Command_Flag==11)  //逻辑提问 求填空  开关"什么"
			{
			 Think_flag=1; 


			   Inhibitory_Layer_YUAN(0); //抑制0层的所有元
			   Inhibitory_Layer_YUAN(1); //抑制1层的所有元
			   Inhibitory_Layer_YUAN(2); //抑制2层的所有元



              if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
               Activation_YUAN(Last_Layer_0_Max_E_YUAN_Name,100); //激活上次对话（最近一次）最强活跃元


                    CString text_DC;
                    CString LL;
                    CString RR;




					//有动词=================================
                    if(Find_Text_DC(input_text_X, &text_DC))//查找文本中的第一个动词，并且返回它
					{


                       Split_X_String(input_text_X,text_DC,&LL,&RR); //把字符串以X为分割，变成2个字符窜
                       RR=text_DC+RR;




                         //判断什么在动词前面=======
					   if(LL.Find("什么") !=-1 && RR.Find("什么") ==-1)
					   {

 

					   }

                         //判断什么在动词后面=======
					   if(LL.Find("什么") ==-1 && RR.Find("什么") !=-1)
					   {
   

						  if(LL=="他 " || LL=="她 " ||LL=="它 "||LL=="这 ") //缺省情况下，用来补全上一句的主语
						   {
							   if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
                                   LL=Last_Layer_0_Max_E_YUAN_Name;
						   }


                           Input_Activation_YUAN(LL);  //通过输入的字符串 激活元

					   }


					}

                    //没有动词==============================
					else
					{
                     Input_Activation_YUAN(input_text_X);  //通过输入的字符串 激活元

					}
					












			}

      //-------------------


//ShiBie_Commanf_Flag_END:;



           //备份输入内容
            Format_String(&input_text_X); //格式化字符串
			input_text_0 = input_text_X;

					input_text.Empty(); //	清空输入




		   UpdateData(0);



		 }





}





BOOL CAiQiDlg::PreTranslateMessage(MSG* pMsg)  //自定义键盘响应函数 重写的
{
	// TODO: 在此添加专用代码和/或调用基类






 if(pMsg->message == WM_KEYDOWN)
  {
     
     AI_AUTO_Question_Ready_Time=AI_AUTO_Question_Ready_MAX_Time+10; //自动提问重新记数

     if(AUTO_Learning_Flag==1)
	 {
	   AUTO_Learning_Flag=0; //自动学习停止
	   TEXT_OUT_BOX_SAY_3("自动学习已停止",0); //数据在屏幕上输出
	 }

     if(User_Answer_Flag==1)
        User_Answer_Time = User_Answer_MAX_Time;


     if(pMsg->wParam==27)  //按了ESC
 
	   {

           OnClose();

	 }


     if(pMsg->wParam==VK_RETURN)  //按了回车键
 
	   {

         OnEnter();


         return   TRUE;   //为了不让回车退出程序
	   }


  }




	return CDialog::PreTranslateMessage(pMsg);
}










void CAiQiDlg::AUTO_Question_2() //自动提问2  对元存储的字符串提问
{

 if( AI_AUTO_Question_Flag != 1) return;

 if( YUAN_SUM == 0) return;

 int n=0;
 n=Xrand(1,YUAN_SUM); //随机选取一个数字


 P_AUTO_Question_select_YUAN = NULL;
 P_AUTO_Question_select_YUAN = YUAN->n_return_P(n);  //得到随机选择的元的指针




int nn=Xrand(1,100);

if(nn<=20)  //20%几率选择 概念层的元
  {
   if(P_AUTO_Question_select_YUAN->Layer==1){}
   else {P_AUTO_Question_select_YUAN = NULL; return;}
  }

else if(nn>20)  //80%几率选择 符号层的元
 {
   if(P_AUTO_Question_select_YUAN->Layer==0){}
   else {P_AUTO_Question_select_YUAN = NULL;return; }

 }






 CString TT;
 


 if(P_AUTO_Question_select_YUAN != NULL)  //有这个元
   {


     if(P_AUTO_Question_select_YUAN->Layer==0)
       {

        TT.Format("%s是什么？",P_AUTO_Question_select_YUAN->name);
        TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


      }


     else if(P_AUTO_Question_select_YUAN->Layer==1)
       {

       // TT.Format("（%s）组合在一起的概念是什么？",P_AUTO_Question_select_YUAN->Way);
        //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


      }






   }



}









void CAiQiDlg::MyDebug()
{


MyDebugX=User_Answer_Time;

//MyDebugX=1000;

}


















void CAiQiDlg::Split_X_String(CString S_CString,CString X_CString,CString *D_CString1,CString *D_CString2) //把字符串以X为分割，变成2个字符窜
{
  CString L,R;

  int X_CString_length=X_CString.GetLength();//字符串的长度
  int S_CString_length=S_CString.GetLength();//字符串的长度

  int X_weizhi=S_CString.Find(X_CString);




  if(X_weizhi==-1)
    {

      return;
     }

  if(X_CString_length+X_weizhi==S_CString_length)
    {

      return;
     }

  if(X_weizhi==0)
    {

      return;
     }
  






  L=S_CString.Left(X_weizhi);
  R=S_CString.Mid(X_weizhi+X_CString_length);

  *D_CString1=L;
  *D_CString2=R;

}






void CAiQiDlg::Split_X_String_Head(CString X_CString,CString *S_CString) //把字符串以X为头分割 取后面部分
{
  CString tmp=*S_CString,R;

  int X_CString_length=X_CString.GetLength();//分割词字符串的长度
  int S_CString_length=tmp.GetLength();//原来字符串的长度

  int X_weizhi=tmp.Find(X_CString); //分割词的位置




  if(X_weizhi==-1) //没找到分割词的位置
    {

      return;
     }

  if(X_CString_length+X_weizhi==S_CString_length)
    {

      return; //分割词后无内容
     }


  







  R=tmp.Mid(X_weizhi+X_CString_length);


  *S_CString=R;

}







//删除字符串第N个词，并且返回它  必须先分词
bool CAiQiDlg::Del_String_N_Word(CString *SX,int N)
{
 int i;

 CString text=*SX;
 CString t;

 int t_start,t_end;
 CString get_word;

  int WORD_SUM = Return_String_Words_Sum(text); //返回字符串中单词的数量


   t.Empty();


  if( WORD_SUM == 0 ) {return 0;}
   if( WORD_SUM == 1 ) {return 0;}
   if( N > WORD_SUM ) {return 0;}
    if( N <= 0 ) {return 0;}

  for(i=1;i <=  WORD_SUM ; i++)
  {
   


   get_word.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //返回字符串中 第SN个单词 偏移的地址 开始 结束


   get_word = text.Mid(t_start, t_end-t_start+1);

   if(i==N) {continue;}

      t += get_word;

      if(i !=  WORD_SUM) 
      t += " ";
  }


 



 if(t.IsEmpty())
  return 0;

 else
 {

  *SX=t;
  return 1;

 }

}














//形式处理  带“是”的字符串   通过创生概念层1的元  联系字符与字符 （建立了X是Y的概念） 比如： 圆的 红的 甜的 是 苹果
int CAiQiDlg::Form_Is_4(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;

 int L_Words_Sum=0,R_Words_Sum=0;





 int a=0,b=0,i=0;
float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X
 YUAN_UNIT *new_YUAN_Y=NULL; //符号元Y
 YUAN_UNIT *new_YUAN_G=NULL; //概念元G
 YUAN_UNIT *new_YUAN_F=NULL; //方法元F

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *

 //把字符串以X为分割，变成2个字符窜
 Split_X_String(S_CString,"是",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }

 Format_String(&L); //格式化字符串 去掉空格 和 *
 Format_String(&R); //格式化字符串 去掉空格 和 *


 //得到单词个数
L_Words_Sum= Return_String_Words_Sum(L); //返回字符串中单词的数量
R_Words_Sum= Return_String_Words_Sum(R); //返回字符串中单词的数量

////////建立G元 中间（概念）元

//通过WAY检查概念是否存在 防止概念的重复建立

  //new_YUAN_G=YUAN->Way_return_P(1,L);
new_YUAN_G=NULL;
  if(new_YUAN_G == NULL) //不存在
  {

     YUAN->New();
     new_YUAN_G=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_G->ID,Xrand(60,740),Xrand(200,380));
 

     YUAN->Set_threshold(new_YUAN_G->ID,60 * L_Words_Sum * 2/3 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     YUAN->Set_Layer(new_YUAN_G->ID,1); //设置为层1

	 //YUAN->Set_Way(new_YUAN_G->ID,1,L); //设置元的 输出方法

  }

  else //原来存在
  {

  }


////////建立F元 输出（方法）元

//通过WAY检查概念是否存在 防止概念的重复建立

  //new_YUAN_F=YUAN->Way_return_P(2,R);
new_YUAN_F= NULL;
  if(new_YUAN_F == NULL) //不存在
  {

     YUAN->New();
     new_YUAN_F=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_F->ID,Xrand(10,740),Xrand(10,100));
 

     YUAN->Set_threshold(new_YUAN_F->ID,new_YUAN_F->threshold + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     YUAN->Set_Layer(new_YUAN_F->ID,2); //设置为层2

     //if(R.IsEmpty())
	 //YUAN->Set_Way(new_YUAN_F->ID,2,"没有"); //设置元的 输出方法
    // else
    //     YUAN->Set_Way(new_YUAN_F->ID,2,R); //设置元的 输出方法

  }

  else //原来存在
  {

  }









        if(YUAN->Find_linker(new_YUAN_G->ID,new_YUAN_F->ID)==0) //原来和目标元没有连接
		{
          fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10
          YUAN->Link(new_YUAN_G->ID,new_YUAN_F->ID,70+fdz);  //连接元

		}

        else if(YUAN->Find_linker(new_YUAN_G->ID,new_YUAN_F->ID)==1)//原来有连接
        {
          fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10
          YUAN->Set_linker_weight_ADD(new_YUAN_G->ID,new_YUAN_F->ID,10);  //设置连接强度增值或减值
        }









////////建立X元 条件（符号）元

i=0;
tt.Empty();
tmpch.Empty();
int end=0;

 while(1) 
 {
  if(end==1) break;


tt.Empty();
tmpch.Empty();

  for(;;)  //读取逗号前的文字
  {
 
   tmpch.Format("%c",L[i]);
   tt+=tmpch;
   i++;



    if(L[i]==' ' || L[i]=='\0') //发现文字 ,
    {

     a=YUAN->Find_name_return_ID(tt); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(60,740),Xrand(420,600));
     YUAN->Set_name(new_YUAN_X->ID,tt);

     YUAN->Set_threshold(new_YUAN_X->ID,new_YUAN_X->threshold + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;



	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

	 }


////设置连接





        if(YUAN->Find_linker(new_YUAN_X->ID,new_YUAN_G->ID)==0) //原来和目标元没有连接
		{




          fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10

        
          YUAN->Link(new_YUAN_X->ID,new_YUAN_G->ID,60 +fdz);  //连接元 根据个数来调节连接强度

		}

        else if(YUAN->Find_linker(new_YUAN_X->ID,new_YUAN_G->ID)==1)//原来有连接
        {
          fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10
          YUAN->Set_linker_weight_ADD(new_YUAN_X->ID,new_YUAN_G->ID,20);  //设置连接强度增值或减值
        }




/////////////





       if(  L[i]=='\0') //发现结束符
	   {
        end=1; break;
	   }



    i++; break;

   }






 }//for

 }//while





////////建立Y元 目标（符号）元

 
end=0;
i=0;
tt.Empty();
tmpch.Empty();


 while(1) 
 {
  if(end==1) break;


tt.Empty();
tmpch.Empty();



  for(;;)  //读取逗号前的文字
  {
 
   tmpch.Format("%c",R[i]);
   tt+=tmpch;
   i++;



    if(R[i]==' ' || R[i]=='\0') //发现文字 ,
    {

     a=YUAN->Find_name_return_ID(tt); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(420,600));
     YUAN->Set_name(new_YUAN_Y->ID,tt);

     YUAN->Set_threshold(new_YUAN_Y->ID,new_YUAN_Y->threshold + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;



	 }

     else //有这个元
	 {

      new_YUAN_Y=YUAN->ID_return_P(a);

	 }


////设置连接





        if(YUAN->Find_linker(new_YUAN_F->ID,new_YUAN_Y->ID)==0) //原来和方法元没有连接
		{
          fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10
          YUAN->Link(new_YUAN_F->ID,new_YUAN_Y->ID,20+fdz);  //连接元

		}

        else if(YUAN->Find_linker(new_YUAN_F->ID,new_YUAN_Y->ID)==1)//原来有连接
        {
          fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10
          YUAN->Set_linker_weight_ADD(new_YUAN_F->ID,new_YUAN_Y->ID,10);  //设置连接强度增值或减值
        }




/////////////





       if(  R[i]=='\0') //发现结束符
	   {
        end=1; break;
	   }



    i++; break;

   }






 }//for

 }//while


///////////////////////////////



    return 1;



}








//形式处理  记忆字符串 生成一个概念 
int CAiQiDlg::Form_Remember_X(CString text) 
{





 CString   S_CString= text; 



 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *





int index=0;


text.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,text);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,text); //设置元的 输入方法



     new_YUAN_X->Contacts->Set_data(0,text); //保存到联系表root里

	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

            if(new_YUAN_X->Contacts->Find_Data_Return_N(text)==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(text,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }












    return 1;




}




//形式处理  记忆字符串 生成一个概念 
int CAiQiDlg::Form_Remember_X2(CString text) 
{





 CString   S_CString= text; 



 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *

//--------------

int De_Flag=0;

CString Debug_Text;
 CString L;
 CString DL;
 CString DR;

L=text;
DL.Empty();
DR.Empty();


if(L.Find("的") !=-1)
{
 //把字符串以"的"为分割，变成2个字符窜
 Split_X_String(L,"的",&DL,&DR); 
    DL.Replace( " ", NULL );
    DR.Replace( " ", NULL );

 if(DL.IsEmpty() || DR.IsEmpty())  //"的"前后必须有内容
   {
    ;
   }
 else
   {

    Debug_Text.Format("发现复合名词>> 左边:%s  右边:%s",DL,DR);
    TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

    De_Flag=1;
   }

}

else
{
 De_Flag=0;
}
//--------------






text.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,text);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,text); //设置元的 输入方法



     new_YUAN_X->Contacts->Set_data(0,text); //保存到联系表root里

            if(De_Flag==1) //是复合名词
              {
                   DR="是"+DR;
                   new_YUAN_X->Contacts->Add(DR,60);
              }

	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

            if(new_YUAN_X->Contacts->Find_Data_Return_N(text)==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(text,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }












    return 1;




}


//[形式处理] 建立命题   格式： 记住 S谓P  、 记住 S
int CAiQiDlg::Form_Create_Proposition_X(CString text) 
{




  CString DC; //谓语动词


  
  text.Replace( "不", "不 " ); //补丁 带“不”的词，把“不”字拆开


 if(text.IsEmpty())  //必须有内容
   {
    return -1;

   }


  if(Find_Text_DC(text, &DC))  //查找文本中的第一个动词，并且返回它
    {
     ;

    }

  else   //如果没有动词
   {
     int r=Form_Remember_X(text);

    return  r;
   }


 CString   S_CString= text; 

 CString L;
 CString R;

 int L_Words_Sum=0,R_Words_Sum=0;





 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X




 CString tt,tmpch;

L.Empty();
R.Empty();


  Format_String(&S_CString); //格式化字符串 去掉空格



   CString ff; //补丁 带“不”的词，把“不”字拆开
   ff="不 "+DC;
   if(S_CString.Find(ff)!=-1) DC="不 "+DC;



 //把字符串以 动词 为分割，变成2个字符窜
 Split_X_String(S_CString,DC,&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())  //动词前后必须有内容
   {
    return -1;

   }

 Format_String(&L); //格式化字符串 去掉空格
 Format_String(&R); //格式化字符串 去掉空格

 CString TX; //把动词加右边 R的字符窜
 DC+=" ";
 TX=DC+R;
 R=TX;


 //得到单词个数
L_Words_Sum= Return_String_Words_Sum(L); //返回字符串中单词的数量
R_Words_Sum= Return_String_Words_Sum(R); //返回字符串中单词的数量


///////////////////////////////






int index=0;

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //设置元的 输入方法



     new_YUAN_X->Contacts->Set_data(0,R); //保存到联系表root里

	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(R,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }




















    return 1;



}










//[形式处理] 建立命题   格式： 记住 S谓P  、 记住 S
int CAiQiDlg::Form_Create_Proposition_X2(CString text) 
{


  CString Debug_Text;

  CString DC; //谓语动词

  CString S_CString= text; 

  CString L;
  CString R;


  int r_flag=1; //返回值 1正常建立   2以前有关系强化  -1失败




  int a=0,b=0,i=0;
  float fdz=0;

  YUAN_UNIT *new_YUAN_X=NULL; //符号元X




  CString tt,tmpch;



  
  text.Replace( "不", "不 " ); //补丁 带“不”的词，把“不”字拆开


 if(text.IsEmpty())  //必须有内容
   {
    return -1;
   }

  //查找文本中的第一个动词，并且返回它
  if(Find_Text_DC(text, &DC)) 
    {
     ;
    }

  else   //如果没有动词
   {
     int r;

ptgn:;

     r=Form_Remember_X(text); //形式处理  记忆字符串 生成一个概念 

     //----------

     //查看是否是带"的"复合名词

     int De_Flag=0;



      CString DL;
      CString DR;


     DL.Empty();
     DR.Empty();


     if(text.Find("的") !=-1)
     {
      //把字符串以"的"为分割，变成2个字符窜
      Split_X_String(text,"的",&DL,&DR); 
         DL.Replace( " ", NULL );
         DR.Replace( " ", NULL );

      if(DL.IsEmpty() || DR.IsEmpty())  //"的"前后必须有内容
        {
         ;
        }
      else
        {

         //Debug_Text.Format("发现复合名词>> 左边:%s  右边:%s",DL,DR);
         //TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

          int rr;
          rr=Form_Remember_X(DL); //形式处理  记忆字符串 生成一个概念
          rr=Form_Remember_X(DR); //形式处理  记忆字符串 生成一个概念


          CString mc_text=text; //去掉text里的空格
          mc_text.Replace( " ", NULL );

          int aa;
          aa=YUAN->Find_name_return_ID(mc_text); //查找是否有一样概念的元

         //Debug_Text.Format("复合名词>> 名称:%s  ID:%d ",mc_text,aa);
         //TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口


          if(aa!=-1)
            {
             YUAN_UNIT *YUAN_X=NULL;
             YUAN_X=YUAN->ID_return_P(aa);

             //CString XDL="<属于>"+DL;
             CString XDR="<是>"+DR;

           //  if(YUAN_X->Contacts->Find_Data_Return_N(XDL)==-1) //原来 没有这条联系信息
                  //  {
	              //   YUAN_X->Contacts->Add(XDL,60);
                  //  }
             if(YUAN_X->Contacts->Find_Data_Return_N(XDR)==-1) //原来 没有这条联系信息
                    {
	                 YUAN_X->Contacts->Add(XDR,60);
                    }

            }



         De_Flag=1;
        }

     }

     else
     {


      De_Flag=0;
     }
//----------



         return  r;
        }

 

L.Empty();
R.Empty();


  Format_String(&S_CString); //格式化字符串 去掉空格



   CString ff; //补丁 带“不”的词，把“不”字拆开
   ff="不 "+DC;
   if(S_CString.Find(ff)!=-1) DC="不 "+DC;

   if(S_CString.Find("不是")!=-1 && DC=="是") DC="不是";


 //把字符串以 动词 为分割，变成2个字符窜
 Split_X_String(S_CString,DC,&L,&R); 




 if(L.IsEmpty() || R.IsEmpty())  //动词前后必须有内容
   {

     goto ptgn;

    //return -1;
   }



/*
         Debug_Text.Format("动词:[%s]",DC);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口
         Debug_Text.Format("S_CString:[%s]",S_CString);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口
         Debug_Text.Format("L:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口
         Debug_Text.Format("R:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

*/





///////////////////////////////













//------------


	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

	 DC.Replace( " ", NULL );




         DC="<"+DC+">"; //谓语加上标签




//------------




    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //保存到联系表数据root里


     new_YUAN_X->Contacts->Add(DC+R,60); //保存到联系表1里

	 }



     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

          int Find_Contacts_N;

          Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(DC+R);

              if(Find_Contacts_N==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(DC+R,60);
               }
              else //原来 有这条联系信息
               {

                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //强化联系 数据权值增加
				 r_flag=2;

               }

	 }





//------------

    b=YUAN->Find_name_return_ID(R); //查找是否有一样概念的元


     if(b==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,R);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;



     new_YUAN_X->Contacts->Set_data(0,R); //保存到联系表数据root里


	 }

     else //有这个元
	 {
          ;

	 }












    return r_flag;



}










//[形式处理] 建立上下文关系，输入X输出Y
int CAiQiDlg::Form_ShangXiaWen(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;

 int L_Words_Sum=0,R_Words_Sum=0;


 if(text.Find("上句") ==-1 && text.Find("下句") ==-1){return -1;}


  //去除额外标点
   text.Replace( "，", NULL );
   text.Replace( ",", NULL );
   text.Replace( "。", NULL );
   text.Replace( ".", NULL );

   //去除空格
   text.Replace( " ", NULL );


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *


   S_CString.Replace( "上句", NULL );
 //把字符串以X为分割，变成2个字符窜
 Split_X_String(S_CString,"下句",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }

 Format_String(&L); //格式化字符串 去掉空格
 Format_String(&R); //格式化字符串 去掉空格


 //得到单词个数
L_Words_Sum= Return_String_Words_Sum(L); //返回字符串中单词的数量
R_Words_Sum= Return_String_Words_Sum(R); //返回字符串中单词的数量




int index=0;

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


    // YUAN->Set_Way(new_YUAN_X->ID,1,L); //设置元的 输入方法



     new_YUAN_X->Contacts->Set_data(0,R); //保存到联系表root里

	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(R,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }













    return 1;



}









//[形式处理] 建立反射关系   如果x那么Y  ，建立一个条件反射关系概念，输入X输出Y
int CAiQiDlg::Form_IF_THEN_X(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;

 int L_Words_Sum=0,R_Words_Sum=0;


 if(text.Find("如果") ==-1 && text.Find("那么") ==-1){return -1;}


  //去除额外标点
   text.Replace( "，", NULL );
   text.Replace( ",", NULL );
   text.Replace( "。", NULL );
   text.Replace( ".", NULL );


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *


   S_CString.Replace( "如果", NULL );
 //把字符串以X为分割，变成2个字符窜
 Split_X_String(S_CString,"那么",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }

 Format_String(&L); //格式化字符串 去掉空格
 Format_String(&R); //格式化字符串 去掉空格


 //得到单词个数
L_Words_Sum= Return_String_Words_Sum(L); //返回字符串中单词的数量
R_Words_Sum= Return_String_Words_Sum(R); //返回字符串中单词的数量




int index=0;

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


    // YUAN->Set_Way(new_YUAN_X->ID,1,L); //设置元的 输入方法



     new_YUAN_X->Contacts->Set_data(0,R); //保存到联系表root里

	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(R,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }













    return 1;



}




//[形式处理] 建立反射关系   如果x那么Y  ，建立一个条件反射关系概念，输入X输出Y
int CAiQiDlg::Form_IF_THEN_X2(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;
 CString TT;

 if(text.Find("如果") ==-1 && text.Find("那么") ==-1){return -1;}


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X
 YUAN_UNIT *new_YUAN_Y=NULL; //符号元Y

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *


   S_CString.Replace( "如果", NULL );
 //把字符串以X为分割，变成2个字符窜
 Split_X_String(S_CString,"那么",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }




	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //设置元的 输入方法

     TT.Format("<那么>%s",R);
     new_YUAN_X->Contacts->Set_data(0,TT); //保存到联系表root里

	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //原来 没有这条联系信息
               {
                    TT.Format("<那么>%s",R);
	            new_YUAN_X->Contacts->Add(TT,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }



//------------
    b=YUAN->Find_name_return_ID(R); //查找是否有一样概念的元

     if(b==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_Y->ID,R);

     YUAN->Set_threshold(new_YUAN_Y->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_Y->ID,1,L); //设置元的 输入方法

     TT.Format("<如果>%s",L);
     new_YUAN_Y->Contacts->Set_data(0,TT); //保存到联系表root里

	 }

     else //有这个元
	 {

      new_YUAN_Y=YUAN->ID_return_P(b);

              if(new_YUAN_Y->Contacts->Find_Data_Return_N(L)==-1) //原来 没有这条联系信息
               {
                    TT.Format("<如果>%s",L);
	            new_YUAN_Y->Contacts->Add(TT,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }
















    return 1;



}















//[形式处理] 建立反射关系   如果x那么Y  ，建立一个条件反射关系概念，输入X输出Y
int CAiQiDlg::Form_IF_X_THEN_Y(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;
 CString TT;

 if(text.Find("如果") ==-1 && text.Find("那么") ==-1){return -1;}


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X
 YUAN_UNIT *new_YUAN_Y=NULL; //符号元Y

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *


   S_CString.Replace( "如果", NULL );
 //把字符串以X为分割，变成2个字符窜
 Split_X_String(S_CString,"那么",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }




	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //设置元的 输入方法


     new_YUAN_X->Contacts->Set_data(0,L); //保存到联系表root里

     TT.Format("<因果>%s",R);
      new_YUAN_X->Contacts->Add(TT,60); //保存到联系表1里


	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

	   int Find_Contacts_N;

   TT.Format("<因果>%s",R);

   Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(TT)==-1) //原来 没有这条联系信息
               {
                 
	            new_YUAN_X->Contacts->Add(TT,60);
               }
              else //原来 有这条联系信息
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //强化联系 数据权值增加
               }

	 }



//------------
    b=YUAN->Find_name_return_ID(R); //查找是否有一样概念的元

     if(b==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_Y->ID,R);

     YUAN->Set_threshold(new_YUAN_Y->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_Y->ID,1,L); //设置元的 输入方法



     new_YUAN_Y->Contacts->Set_data(0,R); //保存到联系表root里

     //TT.Format("<如果>%s",L);
     // new_YUAN_X->Contacts->Add(TT,60); //保存到联系表1里




	 }

     else //有这个元
	 {
/*
      new_YUAN_Y=YUAN->ID_return_P(b);

	  int Find_Contacts_N;

      TT.Format("<如果>%s",L);

	  Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_Y->Contacts->Find_Data_Return_N(TT)==-1) //原来 没有这条联系信息
               {
                
	            new_YUAN_Y->Contacts->Add(TT,60);
               }
              else //原来 有这条联系信息
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //强化联系 数据权值增加
               }

*/			   

	 }
















    return 1;



}




/*


//[形式处理] 建立反射关系   如果x那么Y  ，建立一个条件反射关系概念，输入X输出Y
int CAiQiDlg::Form_IF_X_THEN_Y_2(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;
 CString TT;

 if(text.Find("如果") ==-1 && text.Find("那么") ==-1){return -1;}


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //符号元X
 YUAN_UNIT *new_YUAN_Y=NULL; //符号元Y

 CString tt,tmpch;




  Format_String(&S_CString); //格式化字符串 去掉空格 和 *


   S_CString.Replace( "如果", NULL );
 //把字符串以X为分割，变成2个字符窜
 Split_X_String(S_CString,"那么",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }




	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //设置元的 输入方法


     new_YUAN_X->Contacts->Set_data(0,L); //保存到联系表root里

     TT.Format("<那么>%s",R);
      new_YUAN_X->Contacts->Add(TT,60); //保存到联系表1里


	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

	   int Find_Contacts_N;

   TT.Format("<那么>%s",R);

   Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(TT)==-1) //原来 没有这条联系信息
               {
                 
	            new_YUAN_X->Contacts->Add(TT,60);
               }
              else //原来 有这条联系信息
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //强化联系 数据权值增加
               }

	 }



//------------
    b=YUAN->Find_name_return_ID(R); //查找是否有一样概念的元

     if(b==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_Y->ID,R);

     YUAN->Set_threshold(new_YUAN_Y->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;

     //YUAN->Set_Way(new_YUAN_Y->ID,1,L); //设置元的 输入方法



     new_YUAN_X->Contacts->Set_data(0,R); //保存到联系表root里

     TT.Format("<如果>%s",L);
      new_YUAN_X->Contacts->Add(TT,60); //保存到联系表1里




	 }

     else //有这个元
	 {

      new_YUAN_Y=YUAN->ID_return_P(b);

	  int Find_Contacts_N;

      TT.Format("<如果>%s",L);

	  Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_Y->Contacts->Find_Data_Return_N(TT)==-1) //原来 没有这条联系信息
               {
                
	            new_YUAN_Y->Contacts->Add(TT,60);
               }
              else //原来 有这条联系信息
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //强化联系 数据权值增加
               }

	 }
















    return 1;



}

*/






void CAiQiDlg::Form_X_QA(CString text1, CString text2)   //[形式处理] 建立X概念 问与答关系  X概念生成一条文本数据用来回答
{
   CString tt;
   YUAN_UNIT *YUAN_X=NULL;


   text1.Replace( " ", NULL );
   text2.Replace( " ", NULL );


     int aa;
     aa=YUAN->Find_name_return_ID(text1); //查找是否有一样概念的元

     if(aa!=-1) //原来有概念元
       {

        YUAN_X=YUAN->ID_return_P(aa);


        if(YUAN_X->Contacts->Find_Data_Return_N(text2)==-1) //原来 没有这条联系信息
               {
	            YUAN_X->Contacts->Add(text2,60);
               }


       }

   else //原来没有概念元
   {

	 //建立新元
     YUAN->New();
     YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(YUAN_X->ID,text1);

     YUAN->Set_threshold(YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


     YUAN_X->Contacts->Set_data(0,text1); //保存到联系表root里
     YUAN_X->Contacts->Add(text2,60); //保存到联系表1里

   }


}







//[形式处理] 建立X是Y关系  生成两个独立的概念
void CAiQiDlg::Form_X_IS_Y(CString X,CString Y) 
{


  CString Debug_Text;

  CString TC; 



  CString L=X;
  CString R=Y;


  int a=0,b=0,i=0;
  float fdz=0;

  YUAN_UNIT *new_YUAN_X=NULL; //概念元X



  CString tt,tmpch;



 if(L.IsEmpty() || R.IsEmpty())  //动词前后必须有内容
   {
    return ;
   }



///////////////////////////////





//------------


	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

         R.Replace( "是", NULL );



        TC.Format("<是>%s",R);

//------------




    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //保存到联系表数据root里


     new_YUAN_X->Contacts->Add(TC,60); //保存到联系表1里

	 }

     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(TC)==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(TC,60);
               }
              else //原来 有这条联系信息
               {

               }

	 }





//------------

    b=YUAN->Find_name_return_ID(R); //查找是否有一样概念的元


     if(b==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,R);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;



     new_YUAN_X->Contacts->Set_data(0,R); //保存到联系表数据root里


	 }

     else //有这个元
	 {
          ;

	 }






    return ;



}











void CAiQiDlg::Return_Award_To_AI(YUAN_UNIT *X_YUAN)  //奖励AI  对最强选择元的肯定
{
 

  LINK_UNIT *linker_tmp=NULL;

  YUAN_UNIT *tmp_YUAN=NULL;



 if(X_YUAN != NULL) 
  {
     linker_tmp=X_YUAN->linker;

      for(;;) //遍历所有连接
	  {

            tmp_YUAN=YUAN->ID_return_P(linker_tmp->linker_ID);

           //IF连接它的元是激发状态
           if(tmp_YUAN->state==1)
             {



                   YUAN->Linker_Weight_Change(tmp_YUAN->ID, X_YUAN->ID, 10);  //变化 元ID1 到 ID2 的连接权值




              
             }


           if(linker_tmp->next==NULL)
	     {
              break;
	     }

           linker_tmp=linker_tmp->next;      

	 }  //遍历所有连接END




  }


}










void CAiQiDlg::Return_Punishment_To_AI(YUAN_UNIT *X_YUAN)  //惩罚AI  对最强选择元的否定
{
 

  LINK_UNIT *linker_tmp=NULL;

  YUAN_UNIT *tmp_YUAN=NULL;



 if(X_YUAN != NULL) 
  {
     linker_tmp=X_YUAN->linker;

      for(;;) //遍历所有连接
	  {

            tmp_YUAN=YUAN->ID_return_P(linker_tmp->linker_ID);

           //IF连接它的元是激发状态
           if(tmp_YUAN->state==1)
             {



                   YUAN->Linker_Weight_Change(tmp_YUAN->ID, X_YUAN->ID, -20);  //变化 元ID1 到 ID2 的连接权值




              
             }


           if(linker_tmp->next==NULL)
	     {
              break;
	     }

           linker_tmp=linker_tmp->next;      

	 }  //遍历所有连接END




  }


}






void CAiQiDlg::Return_Award_To_AI_X(YUAN_UNIT *X_YUAN,int n)  //奖励AI  对最强选择元的 联系表输出肯定
{
 
  float weight=X_YUAN->Contacts->Get_n_weight(n);
 
  X_YUAN->Contacts->Set_weight(n,weight+10);

}



void CAiQiDlg::Return_Punishment_To_AI_X(YUAN_UNIT *X_YUAN,int n)  //惩罚AI  对最强选择元的 联系表输出否定
{

  float weight=X_YUAN->Contacts->Get_n_weight(n);
 
  X_YUAN->Contacts->Set_weight(n,weight-20); 

  weight=X_YUAN->Contacts->Get_n_weight(n);
  if(weight<=0) //如果权值为0 删除联系表数据
    {
     if(n==0) //是root
       {
        X_YUAN->Contacts->Set_data(0,"我不清楚...");
        X_YUAN->Contacts->Set_weight(0,10); 
       }
     else 
      {
       X_YUAN->Contacts->Del(n);
      }
    }

}






void CAiQiDlg::OnBnClickedButtonOnBrainbox()
{


	// TODO: 在此添加控件通知处理程序代码


  CBrainBoxDlg  dlg;


  dlg.DoModal();
}











//加载TXT文件到字符串
void CAiQiDlg::TxtFileRead_to_CString(CString FileName,CString *CStr) 
{
 

 CString Str;

    FILE *fp;
    errno_t err;//检测文件问题

    LPCTSTR filename=FileName;  

 if((err = fopen_s(&fp,filename,"r")) !=0)
	{
          CString ET;
          ET.Format("错误，%s文件不能读取!!",FileName);
          AfxMessageBox(ET);
		   PostMessage(WM_QUIT,0,0);
	}



   ///////////////////////////////////////////////////////////////

 char ch;
	   
 CString tmpch;
 
  Str.Empty();

  while(!feof(fp))
       {
          ch=fgetc(fp);





          tmpch.Format("%c",ch);

          Str+=tmpch;
 


      }


   fclose(fp);



 *CStr=Str;
	
}











//是否是动词 和动词词库中的词语比较
bool CAiQiDlg::IS_DC(CString str)
{
 int nn;

 int l=str.GetLength();

 if(l==2)
 {
  str="\n"+str+"\n";

 }

  nn=CK_DC.Find(str);


 if(nn!=-1)
   {
     return 1;
   }
 else
    return 0;

}






//查找文本中的第一个动词，并且返回它  必须先分词
bool CAiQiDlg::Find_Text_DC(CString text,CString *DC)
{
 int i;
 CString t;

 int t_start,t_end;
 CString get_text;

  int CI_SUM = Return_String_Words_Sum(text); //返回字符串中单词的数量



   t.Empty();


  if( CI_SUM == 0) goto Find_Text_DC_END;
 

 
  for(i=1;i <=  CI_SUM ; i++)
  {
   


   get_text.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //返回字符串中 第SN个单词 偏移的地址 开始 结束


   get_text = text.Mid(t_start, t_end-t_start+1);


   //是否是动词 和动词词库中的词语比较
   if(IS_DC(get_text))
     {
      t=get_text;
      break;
     } 

  }


 


 Find_Text_DC_END:;



 if(t.IsEmpty())
  return 0;

 else
 {

  *DC=t;
  return 1;

 }

}







//是否是属性 和属性标签中的词语比较
bool CAiQiDlg::IS_SXBQ(CString str)
{
 int nn;

 int l=str.GetLength();

 if(l==2)
 {
  str="\n"+str+"\n";

 }

  nn=CK_SXBQ.Find(str);


 if(nn!=-1)
   {
     return 1;
   }
 else
    return 0;

}







//识别带标签记忆的建立语句格式
int CAiQiDlg::Recognition_SXBQ_Form(CString text) 
{



  CString S_CString= text; 


  int text_word_sum;

  CString Word;
  CString SXBQ;
  //CString x;

  int SXBQ_N;


 if(text.IsEmpty())  //必须有内容
   {
    return -1;
   }


  Format_String(&S_CString); //格式化字符串 去掉多余空格



  //查找文本中的第一个属性词，并且返回它
  SXBQ_N = Find_Text_SXBQ(S_CString, &SXBQ);
  if(SXBQ_N == -1) 
    {
     return -1;
    }


 //x.Format("的 %s",SXBQ);
 S_CString.Replace("的 "+SXBQ,SXBQ);

 Format_String(&S_CString); //格式化字符串 去掉多余空格


 text_word_sum = Return_String_Words_Sum(S_CString);
 if(text_word_sum<3)  //必须大于3个词
   {
    return -1;
   }








  Word=Return_String_N_Word(S_CString,2); //返回字符串第N个单词
 if(IS_SXBQ(Word) ==0 ) //第二个词必须是标签
   {
     return -1;
   }







  return 1;




}












//标签记忆的建立函数
int CAiQiDlg::Form_Create_SXBQ(CString text) 
{

  int r_flag=1; //返回值 1正常建立   2以前有关系强化  -1失败

 
  CString S_CString= text; 


  int text_word_sum;

  CString Word;
  CString SXBQ;

  int SXBQ_N;




  CString L;
  CString R;

  int a=0;

  YUAN_UNIT *new_YUAN_X=NULL; //目标元X


 if(text.IsEmpty())  //必须有内容
   {
    r_flag=-1;
    return r_flag;
   }


  Format_String(&S_CString); //格式化字符串 去掉多余空格



  //查找文本中的第一个属性词，并且返回它
  SXBQ_N = Find_Text_SXBQ(S_CString, &SXBQ);
  if(SXBQ_N == -1) 
    {
    r_flag=-1;
    return r_flag;

    }



 S_CString.Replace("的 "+SXBQ,SXBQ);

 Format_String(&S_CString); //格式化字符串 去掉多余空格


 text_word_sum = Return_String_Words_Sum(S_CString);
 if(text_word_sum<3)  //必须大于3个词
   {
    r_flag=-1;
    return r_flag;

   }




  Word=Return_String_N_Word(S_CString,2); //返回字符串第N个单词
 if(IS_SXBQ(Word) ==0 ) //第二个词必须是标签
   {
    r_flag=-1;
    return r_flag;
   }



 //把字符串以 动词 为分割，变成2个字符窜
 Split_X_String(S_CString,SXBQ,&L,&R); 

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

   //AfxMessageBox(L);
   //AfxMessageBox(R);



    SXBQ = "<"+SXBQ+">"; //加上标签






    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //保存到联系表数据root里


     new_YUAN_X->Contacts->Add(SXBQ+R,60); //保存到联系表1里

	 }



     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

          int Find_Contacts_N;

          Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(SXBQ+R);

              if(Find_Contacts_N==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(SXBQ+R,60);
               }
              else //原来 有这条联系信息
               {

                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //强化联系 数据权值增加
				 r_flag=2;

               }

	 }










    return r_flag;




}







void CAiQiDlg::Form_Create_SXBQ_EX(CString text) //带有结果的标签记忆的建立函数
{

              int r=Form_Create_SXBQ(text); //[形式处理] 建立带标签的记忆


              if(r==1)  //1正常建立

                {


			      TEXT_OUT_BOX_SAY_3("哦，这个属性记住了。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				 }

              else if(r==2)  //2以前有关系强化

                {


			      TEXT_OUT_BOX_SAY_3("恩，我觉得也是这样的属性。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				 }

			  else

			     {
                  TEXT_OUT_BOX_SAY_3("语法错误！",1); //数据在屏幕上输出

			     }


			


}










//是否是形容词 和形容词词库中的词语比较
bool CAiQiDlg::IS_XRC(CString str)
{
 int nn;

 int l=str.GetLength();

 if(l==2)
 {
  str="\n"+str+"\n";

 }

  nn=CK_XRC.Find(str);


 if(nn!=-1)
   {
     return 1;
   }
 else
    return 0;

}



//查找文本中的第一个属性，并且返回它  必须先分词
int CAiQiDlg::Find_Text_SXBQ(CString text,CString *SX)
{
 int i;
 CString t;

 int t_start,t_end;
 CString get_text;

  int CI_SUM = Return_String_Words_Sum(text); //返回字符串中单词的数量



   t.Empty();


  if( CI_SUM == 0) goto Find_Text_SXBQ_END;
 

 
  for(i=1;i <=  CI_SUM ; i++)
  {
   


   get_text.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //返回字符串中 第SN个单词 偏移的地址 开始 结束


   get_text = text.Mid(t_start, t_end-t_start+1);


   //是否是属性 和属性词库中的词语比较
   if(IS_SXBQ(get_text))
     {
      t=get_text;
      break;
     } 

  }


 


 Find_Text_SXBQ_END:;



 if(t.IsEmpty())
  return -1;

 else
 {

  *SX=t;
  return i;

 }

}







void CAiQiDlg::OnFileRead_ChatLibrary()  //读取语料库文件
{
	// TODO: 在此添加控件通知处理程序代码

CString XT,TT;




  CString FileName;

  CFileDialog FileDlg(TRUE);
  FileDlg.m_ofn.lpstrTitle="文件打开";
  FileDlg.m_ofn.lpstrFilter="文本文件(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";

	
  if(FileDlg.DoModal() == IDOK )
  {


            XT.Format("正在加载聊天语料库文件,请稍候...");
            TEXT_OUT_BOX_SAY_3(XT,0); //数据在屏幕上输出
            UpdateWindow( );//窗口立即重绘

       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 

Current_Memory_File_Name = _T("");//当前打开的记忆文件名

   //TEXT_OUT_BOX_CLS();


    FileName=FileDlg.GetPathName();



    FILE *fp;
	 errno_t err;//检测文件问题
    //	const char *filename = (LPCTSTR)FileName; //转换类型 重新赋予文件名

    LPCTSTR filename=FileName;  //防止0x73d311c7操作 0x00000004内存不能读

    if((err=fopen_s(&fp,filename,"r")) !=0)
	{

     AfxMessageBox("错误操作，文件不能读!!");
	}



   ///////////////////////////////////////////////////////////////

       YUAN->FreeAll(YUAN);  //清空链表

	   //int tmp_ID_X;
       char ch;
       //int n,i;

	   int end=0;



	   YUAN_ID_X=0;
       YUAN_SUM=0;  //元的总数为0

	   YUAN_RUN_MAIN_Flag=0;

 /*--------------------------*/
 


CString L,R;

int js=1;

int CL_SUM=0;

L.Empty();
R.Empty();


 CString tmpch;





 while(1) 
{





 if(end==1) break;


   if(js==3)
     {
         if(!L.IsEmpty() && !R.IsEmpty())
           {


/*

            XT.Format("已加载内容>> 问:%s",L);
            TEXT_OUT_BOX_SAY_3(XT,0); //数据在屏幕上输出

			XT.Format("已加载内容>> 答:%s",R);
            TEXT_OUT_BOX_SAY_3(XT,0); //数据在屏幕上输出


            

*/


 CL_SUM++;

            TT.Format("上句%s下句%s",L,R);
/*
//========================
//中文分词


   TT = ZWFC(TT);//中文分词


//========================

*/





            Form_ShangXiaWen(TT); //[形式处理] 建立上下文关系，输入X输出Y


            L.Empty();
            R.Empty();

            js=1; ch=fgetc(fp); 

          }
     }






         while(1) //读行
	{

          ch=fgetc(fp);  


		   if(ch==EOF) //结束
		   { 
                    end=1;  break;
		   }

		   if(ch=='\n') //回车
		   { 
		    if(js==1) {js=2;break;}
		    else if(js==2)
		     {
						 
                      js=3;

                        break; 

                     }


                  
		   }




           tmpch.Format("%c",ch);

           if(js==1)
           L+=tmpch;

           else if(js==2)
           R+=tmpch;






	}








}




   //--------------------------



            XT.Format("已加载%d组聊天语料数据，灌输到AiQi的记忆里。",CL_SUM);
            TEXT_OUT_BOX_SAY_3(XT,0); //数据在屏幕上输出

               AI_YES_Flag=1;


  

   fclose(fp);

  }


YUAN_RUN_MAIN_Flag=1;



}








int CAiQiDlg::Assess_To_Two_String(CString S,CString D) //对两个字符串相似度打分  S是完型  D是对照
{
 int zpf=0;
 int pf1=0; //词数评分
 int pf2=0;
 int pf3=0;

CString Debug_Text;

 S = ZWFC(S);//中文分词
 D = ZWFC(D);//中文分词

  Format_String(&S); //格式化字符串 去掉空格
  Format_String(&D); //格式化字符串 去掉空格



 //得到单词个数
 int S_Words_Sum= Return_String_Words_Sum(S); //返回字符串中单词的数量
 int D_Words_Sum= Return_String_Words_Sum(D); //返回字符串中单词的数量

 //个数相同评分---------------------------20
 pf1=20; 
 int  pjf1 = 20 / S_Words_Sum;

 pf1 = 20 - pjf1 * (abs(S_Words_Sum-D_Words_Sum));
 if(pf1<=0) pf1=0;






 //词与词相同评分--------------------------- 
 pf2=0;
int pjf2=30;

 CString SS,DD;

 int Z_OK=0;

int i;

  for(i=1;i <= S_Words_Sum ; i++)
     {
      SS.Empty();


      SS=Return_String_N_Word(S,i); //返回字符串第N个单词
      if(D.Find(SS) !=-1 )

            { Z_OK++;}








     }





pf2=pjf2*Z_OK;




 //词与词相同,并且位置也相同评分---------------------------额外加分
 pf3=0;


 Z_OK=0;
  int Z_NO=0;

 if(S_Words_Sum==D_Words_Sum)

 {
  for(i=1;i <= S_Words_Sum ; i++)
     {
      SS.Empty();
      DD.Empty();

      SS=Return_String_N_Word(S,i); //返回字符串第N个单词
      DD=Return_String_N_Word(D,i); //返回字符串第N个单词

	  if(SS==DD) { Z_OK++;}
	  else{Z_NO++;}

     }


 }


pf3=10*Z_OK - 30*Z_NO;


 //---------------------------


// Debug_Text.Format("pf1=%d,pf2=%d,pf3=%d",pf1,pf2,pf3);
 //TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据在屏幕上输出



 zpf=pf1+pf2+pf3;
 if(zpf>1000) zpf=1000;
 if(zpf<0) zpf=0;

 return zpf;
}






void CAiQiDlg::Input_Activation_YUAN(CString text)  //通过对输入的字符串和元评分，来激活评分高的元
{
   YUAN_UNIT *tmp;


   int pf;
				 
				 
				 
				

  tmp=YUAN;


  for(;;) //遍历所有元
  {


    if(tmp->ID!=0) //0号元以外
     {

      
      pf=0;



      CString TT;

	  TT=tmp->name;

      TT = ZWFC(TT);//中文分词
      Format_String(&TT); //格式化字符串 去掉空格

      pf=Assess_To_Two_String(text,TT); //对两个字符串相似度打分

	  pf=(int)(pf*3.0f); //活跃度=评分X3

      if(pf>=100)
        {
         //tmp->state=1;
         //tmp->E_X=(float)pf;
		  YUAN->Set_state(tmp->ID,2); //准备激活
		  YUAN->Add_E_X(tmp->ID,(float)pf);//增加表达强度效应增加
        }


     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END



}









void CAiQiDlg::Input_Activation_YUAN_By_Contacts(CString text)  //通过对输入的字符串和元联系表评分，来增加元活跃度
{
  YUAN_UNIT *tmp;
  CONTACTS_UNIT *P_YUAN_Contacts;

  int pf=0;

  tmp=YUAN;

  float E_X;


  for(;;) //遍历所有元
  {


    if(tmp->ID!=0) //0号元以外
     {

      




   //遍历联系表
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {



      CString TT;

	  TT=P_YUAN_Contacts->data;

      TT = ZWFC(TT);//中文分词
      Format_String(&TT); //格式化字符串 去掉空格

     pf=Assess_To_Two_String(text,TT); //对两个字符串相似度打分

    E_X=(float)pf/5;

    YUAN->Add_E_X(tmp->ID,E_X);//增加表达强度效应增加

 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end


          




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END




}








void CAiQiDlg::Input_Activation_YUAN_By_Contacts_2(CString text)  //通过对输入的字符串和元数据比较，来增加元活跃度，比较<是><内容>标签
{
  YUAN_UNIT *tmp;
  CONTACTS_UNIT *P_YUAN_Contacts;



  tmp=YUAN;


   CString text_x; //去除空格的
   text_x=text;
   text_x.Replace( " ", NULL );
   int text_x_l=text_x.GetLength();//字符串的长度

  for(;;) //遍历所有元
  {


    if(tmp->ID!=0) //0号元以外
     {


   //遍历联系表
   P_YUAN_Contacts=tmp->Contacts;
   for(;;)
   {



      CString TT;

	  TT=P_YUAN_Contacts->data;

      if(TT.Find("<是>")!=-1) //有<是>的标签
        {
          TT.Replace( "<是>", NULL );

          if(text.Find(TT)!=-1)
		    {

             YUAN->Add_E_X(tmp->ID,80);//增加表达强度效应增加
		    }

        }

      else if(TT.Find("<内容>")!=-1) //有<内容>的标签
        {
 
			if(text_x_l>=8)//匹配长度是8个字节有效
			{
             if(TT.Find(text_x)!=-1) //查找带<内容>标签数据中是否有何输入一样的内容
		       {

                YUAN->Add_E_X(tmp->ID,80);//增加表达强度效应增加
		       }

			}

        }





 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end


          




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END




}












void CAiQiDlg::Find_YUAN_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts)  //查找最相似的联系表数据 返回该数据 和 元指针
{
   YUAN_UNIT *tmp;


   int pf=0;
   int MAX_pf=20;

   YUAN_UNIT  *MAX_pf_YUAN=NULL;
   CString MAX_pf_YUAN_Contacts;
				 
   CONTACTS_UNIT *P_YUAN_Contacts;				 
				 
			

  tmp=YUAN;

  


  MAX_pf_YUAN_Contacts.Empty();

  for(;;) //遍历所有元
  {


    if(tmp->ID!=0) //0号元以外
     {

      


       if(tmp->state==1)
         {

   //遍历联系表
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {

 

     pf=Assess_To_Two_String(text,P_YUAN_Contacts->data); //对两个字符串相似度打分

     if(pf>MAX_pf && pf>=sspf) //出现最高分 保存这个
       {
        MAX_pf=pf;
        MAX_pf_YUAN=tmp; //保存元
        MAX_pf_YUAN_Contacts=P_YUAN_Contacts->data;//保存这条元联系表数据

       }

 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end


          }




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END


*YUAN_p=MAX_pf_YUAN;
*YUAN_Contacts=MAX_pf_YUAN_Contacts;


}








void CAiQiDlg::Find_YUAN_X_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts)  //查找最相似的联系表数据 返回该数据 和 元指针 没有状态限制
{
   YUAN_UNIT *tmp;


   float pf=0;
   float MAX_pf=20;
   float weight=0;
   float MAX_weight=20;

   YUAN_UNIT  *MAX_pf_YUAN=NULL;
   CString MAX_pf_YUAN_Contacts;
				 
   CONTACTS_UNIT *P_YUAN_Contacts;				 
				 
			
text.Replace( " ", NULL);

  tmp=YUAN;


  MAX_pf_YUAN_Contacts.Empty();

  for(;;) //遍历所有元
  {


    if(tmp->ID!=0) //0号元以外
     {

      




   //遍历联系表
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {

        float xr=(float)Xrand(1,1000)/100 ; //随机因素 0.01~10



     pf=(float) Assess_To_Two_String(text,P_YUAN_Contacts->data) + xr ; //对两个字符串相似度打分

	 weight=P_YUAN_Contacts->weight  + xr ;


 //CString TT;
 //TT.Format("名字：%s  原文：%s   数据：%s  评分：%0.2f",tmp->name ,text ,P_YUAN_Contacts->data,pf);
 //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出



     if(pf>MAX_pf && pf>=sspf && weight>=MAX_weight) //出现最高分 保存这个
       {
 



        MAX_pf=pf ;
		MAX_weight=weight ;
        MAX_pf_YUAN=tmp; //保存元
        MAX_pf_YUAN_Contacts=P_YUAN_Contacts->data;//保存这条元联系表数据

       }

 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end


          




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END


*YUAN_p=MAX_pf_YUAN;
*YUAN_Contacts=MAX_pf_YUAN_Contacts;


}







void CAiQiDlg::Find_YUAN_X_Contacts_DC(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts,CString DC)  //查找最相似的联系表数据 返回该数据 和 元指针 没有状态限制 查找联系表里的动词短语
{
   YUAN_UNIT *tmp;
   CString TT;

   float weight=0;
   float MAX_weight=20;

   YUAN_UNIT  *MAX_pf_YUAN=NULL;
   CString MAX_pf_YUAN_Contacts;
				 
   CONTACTS_UNIT *P_YUAN_Contacts;				 
				 
		CString YUAN_Contacts_DC;	

  tmp=YUAN;

  int end=0;

  MAX_pf_YUAN_Contacts.Empty();

  for(;;) //遍历所有元
  {


//if(end==1) break;

    if(tmp->ID!=0) //0号元以外
     {

      
    if(tmp->state==1)
	{



   //遍历联系表
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {


      YUAN_Contacts_DC.Empty();

      TT=ZWFC(P_YUAN_Contacts->data);   //中文分词
 
      Find_Text_DC(TT,&YUAN_Contacts_DC);


if(!YUAN_Contacts_DC.IsEmpty())
{ 
 CString LL,RR;
 Split_X_String(P_YUAN_Contacts->data,YUAN_Contacts_DC,&LL,&RR); //把字符串以X为分割，变成2个字符窜

 if(LL.Find("不")!=-1) YUAN_Contacts_DC="不"+YUAN_Contacts_DC;

}


        float xr=(float)Xrand(1,1000)/100 ; //随机因素 0.01~10

      weight=P_YUAN_Contacts->weight + xr ;



//CString TT;
//TT.Format("数据：%s  动词：%s weight：%0.2f",P_YUAN_Contacts->data,YUAN_Contacts_DC,weight);
//TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出




	  if(YUAN_Contacts_DC==DC && weight>=MAX_weight)
	  {
      



		MAX_weight=weight;
        MAX_pf_YUAN=tmp; //保存元
        MAX_pf_YUAN_Contacts=P_YUAN_Contacts->data;//保存这条元联系表数据

 

//end=1; break;

	  }
 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end


          
	}



     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END


*YUAN_p=MAX_pf_YUAN;


*YUAN_Contacts=MAX_pf_YUAN_Contacts;


if(MAX_weight<=sspf)
{
 *YUAN_p=NULL;

}


}







//查找指定某元的联系表数据 激活以“text”标签开头的字符相关元
void CAiQiDlg::Find_YUAN_Contacts_Label_Activation_YUAN(YUAN_UNIT *YUAN_p,CString text,int power)  
{


   CONTACTS_UNIT *P_YUAN_Contacts;

   CString RR;


  //遍历联系表
   P_YUAN_Contacts=YUAN_p->Contacts;



   for(;;)
   {

    text.Replace( " ", NULL);


    if(P_YUAN_Contacts->data.Find(text)==0) //发现了这个字
	{


     RR=P_YUAN_Contacts->data;

     //把字符串以X为头分割 取后面部分
     Split_X_String_Head(text,&RR);
     if(!RR.IsEmpty())
     Activation_YUAN(RR, power); //激活某个元 状态变1

	}


 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end






}



//查找指定某元的联系表数据 抑制以“text”标签开头的字符相关元
void CAiQiDlg::Find_YUAN_Contacts_Label_Inhibit_YUAN(YUAN_UNIT *YUAN_p,CString text,int power)  
{


   CONTACTS_UNIT *P_YUAN_Contacts;

   CString RR;


  //遍历联系表
   P_YUAN_Contacts=YUAN_p->Contacts;



   for(;;)
   {

    if(P_YUAN_Contacts->data.Find(text)==0) //发现了这个字
	{

     RR=P_YUAN_Contacts->data;

     //把字符串以X为头分割 取后面部分
     Split_X_String_Head(text,&RR);
     if(!RR.IsEmpty())
     Inhibit_YUAN(RR, power); // 抑制某个元 状态变1

	}


 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end






}











void CAiQiDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

		// CString TT;
		// TT.Format("当前文件名：%s",Current_Memory_File_Name);

       //     AfxMessageBox(TT);


if(Auto_Load_And_Save_Memory_Flag ==1) //自动加载和保存记忆
{
 //当前打开的记忆文件名
	if(Current_Memory_File_Name.Find("AiQi的记忆") !=-1)
   {
		//CString TT;
		//TT.Format("自动保存：记忆文件/AiQi的记忆.bbf");

           //AfxMessageBox(TT);
     CBrainBoxDlg a;
     a.Save_Memory_File_XML(2,Current_Memory_File_Name);

   }
}



}




















void CAiQiDlg::Run_YUAN_Contacts_Data(CString Data) //运行一条概念单元意义表数据
{

 
  CString TT=Data;



 //识别意义表数据类型


if(TT.Find("<")!=-1&&TT.Find(">")!=-1) //是标签语句
{

 if(TT.Find("<是>")!=-1) 
  {
   TT.Replace( "<是>", "是" );
   TEXT_OUT_BOX_SAY_3("我觉得，"+TT,1); //数据显示在屏幕上
  }

 else if(TT.Find("<不是>")!=-1)
  {
   TT.Replace( "<不是>", "不是" );
   TEXT_OUT_BOX_SAY_3("我感觉，"+TT,1); //数据显示在屏幕上
  }

  else if(TT.Find("<因果>")!=-1) 
  {
   TT.Replace( "<因果>", NULL);
   TEXT_OUT_BOX_SAY_3("所以..."+TT,1); //数据显示在屏幕上
  }

 else if(TT.Find("<脚本命令>")!=-1) //执行脚本命令
  {
   TT.Replace( "<脚本命令>", NULL );

   Run_Script(TT);

  }

 else 
  {
   TT.Replace( "<", NULL );
   TT.Replace( ">", NULL );
   TEXT_OUT_BOX_SAY_3("我记得，"+TT,1); //数据显示在屏幕上
  }

}

 else //普通数据 
  {
   TT.Replace( " ", NULL );

   TEXT_OUT_BOX_SAY_3(TT,1); //数据显示在屏幕上
  }


 


}


//运行脚本函数=======================================================================



void CAiQiDlg::Run_Script(CString Data) //运行脚本
{

 int Data_length=Data.GetLength();//字符串的长度
 CString Command;

 int i=0;
    //读取一段 ;结束的脚本语句
   while(1)
   {
    if(i>Data_length) break;

    Command += Data[i];

    
    if(Data[i]==';')
      {

       Command.Replace( ";", NULL );

       Run_Scr_Command(Command); //根据命令选择执行脚本

       Command.Empty();

      }


    i++;
   }


}



void CAiQiDlg::Scr_Command_Out_Text(CString Command)  //脚本 输出文字
{
   Command.Replace( "输出文字", NULL );
   Command.Replace( "(", NULL );
   Command.Replace( ")", NULL );
   Command.Replace( "（", NULL );
   Command.Replace( "）", NULL );


   CString TT;
   TT=Command;
   TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
}

void CAiQiDlg::Scr_Command_Open_Web(CString Command) //脚本 打开网页
{

   Command.Replace( "打开网站", NULL );
   Command.Replace( "(", NULL );
   Command.Replace( ")", NULL );
   Command.Replace( "（", NULL );
   Command.Replace( "）", NULL );

   CString TWeb;

   TWeb="http://"+Command;

			     TWeb.Replace( " ", NULL );

               ShellExecute(NULL, "open", TWeb , NULL, NULL, SW_SHOWNORMAL);



   CString TT;
   TT="打开网站：" + Command;
   TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
}




void CAiQiDlg::Scr_Command_Weather_Forecast(CString Command)  //脚本 输出文字
{
   Command.Replace( "查询天气", NULL );
   Command.Replace( "(", NULL );
   Command.Replace( ")", NULL );
   Command.Replace( "（", NULL );
   Command.Replace( "）", NULL );



                           CString x=Command;
                           x.Replace( " ", NULL );

			               CString TX;    
                          CString TT;

                          CString city_number;


                            CString CityName=x;




                          

                            city_number=Get_City_Weather_Number(CityName);  //返回城市天气代码

                            if(city_number=="没有找到")
                              {
                               TT.Format("没有相关地区的天气数据。");
                               TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                              }
                            else
                              {


                               //TT.Format("城市代码=%s",city_number);
                               //TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出

                               CString CT;
                               CT=Get_Weather_Information_From_Web(city_number); //从网络上获取天气信息并返回

                                   TX= CityName + "  "+ CT +"C";  
      
                               TT.Format("%s",TX);
                               TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出


                              }


}







void CAiQiDlg::Run_Scr_Command(CString Command) //根据命令选择执行脚本
{
 if(Command.Find("输出文字") !=-1 )       Scr_Command_Out_Text(Command);
 else if(Command.Find("打开网站") !=-1 )  Scr_Command_Open_Web(Command);
 else if(Command.Find("查询天气") !=-1 )  Scr_Command_Weather_Forecast(Command);

 else
  {
   CString TT;
   TT="不能执行这条脚本语句 " + Command;
   TEXT_OUT_BOX_SAY_3(TT,1); //数据在屏幕上输出
  }
}









//命令：显示元的数据
void CAiQiDlg::Cmd_Display_YUAN_Data( CString text)
{
   CString TT;
   CString ST;
   YUAN_UNIT *YUAN_X=NULL;
   CONTACTS_UNIT *P_YUAN_Contacts;



  text.Replace( " ", NULL );

     int aa;
     aa=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元

     if(aa!=-1)
       {

        YUAN_X=YUAN->ID_return_P(aa);


     ST.Format("概念:%s\r\n ",YUAN_X->name);
          TT+=ST;
     ST.Format("----------------------------\r\n ");
          TT+=ST;

   //遍历联系表
   P_YUAN_Contacts=YUAN_X->Contacts;

   int n=0;
   int ID;

   for(;;)
   {




        ID=P_YUAN_Contacts->ID;

	   ST.Format("[数据%d]:%s\r\n ",ID,P_YUAN_Contacts->data);


     TT+=ST;


 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;

    n++;

   }

   //遍历联系表end


              TEXT_OUT_BOX_SAY_3(TT,0); //数据输出 


       }

else
{

     TT.Format("错误，概念[%s]不存在。",text);
     TEXT_OUT_BOX_SAY_3(TT,0); //数据输出

}


}





//命令：删除元
void CAiQiDlg::Cmd_Del_YUAN( CString text)
{
   CString TT;

   YUAN_UNIT *YUAN_X=NULL;




  text.Replace( " ", NULL );

     int aa;
     aa=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元

     if(aa!=-1)
       {



        YUAN->Del_ID(aa);

        TT.Format("概念[%s]已经删除。 ",text);




              TEXT_OUT_BOX_SAY_3(TT,0); //数据输出 


       }

else
{

     TT.Format("错误，概念[%s]不存在。",text);
     TEXT_OUT_BOX_SAY_3(TT,0); //数据输出

}


}






//命令：删除元数据
void CAiQiDlg::Cmd_Del_YUAN_Contacts( CString text,int Contacts_ID)
{
   CString TT;

   YUAN_UNIT *YUAN_X=NULL;
   CONTACTS_UNIT *P_YUAN_Contacts=NULL;


  if(Contacts_ID==0)
         
           {
            TT.Format("错误，不能删除概念[%s]的根数据！",text);
            TEXT_OUT_BOX_SAY_3(TT,0); //数据输出

            return;
           }


  text.Replace( " ", NULL );

     int aa;
     aa=YUAN->Find_name_return_ID(text); //查找是否有一样概念的元

     if(aa!=-1)
       {


         YUAN_X=YUAN->ID_return_P(aa);


         P_YUAN_Contacts=YUAN_X->Contacts->ID_return_P(Contacts_ID);
         if(P_YUAN_Contacts!=NULL)
           {



           }
         else
           {
            TT.Format("错误，概念[%s]中的数据[%d]不存在。",text,Contacts_ID);
            TEXT_OUT_BOX_SAY_3(TT,0); //数据输出

            return;
           }



         YUAN_X->Contacts->Del(Contacts_ID);

  








        TT.Format("概念[%s]中的数据[%d]的内容已经删除。 ",text,Contacts_ID);

        


              TEXT_OUT_BOX_SAY_3(TT,0); //数据输出 


       }

 else
 {

     TT.Format("错误，概念[%s]不存在。",text);
     TEXT_OUT_BOX_SAY_3(TT,0); //数据输出

 }


}




CString CAiQiDlg::CString_Extraction_Content(CString text,CString a,CString b)   //字符串提取中间内容
{
  
 CString strOut;


 int len = a.GetLength();

 int nStart=text.Find(a)+len;
 int nEnd=text.Find(b,nStart);

 strOut=text.Mid(nStart,nEnd-nStart);



 return strOut;
}




CString CAiQiDlg::Get_CiTiao_Information_From_Web(CString CiTiao) //从网络上获取词条信息并返回
{
 CString TT;

 CString m_my_ct = CiTiao;
 CString m_web_url;
 CString m_web_text;
 CString m_web_good_information;


m_my_ct.Replace( " ", NULL );

  char *mem_name = m_my_ct.GetBuffer(0);
  string memname="";
  GB2312ToUTF_8(memname,mem_name,512);

  CString Cstr=memname.c_str();  //string->CString 


  m_web_url="http://www.baike.com/wiki/"+URLEncode(Cstr);







     CString content; //内容


     CString url = m_web_url; 


     CInternetSession session("HttpClient"); 

     CHttpFile* pfile = (CHttpFile *)session.OpenURL(url); 
       
     DWORD dwStatusCode; 
     pfile -> QueryInfoStatusCode(dwStatusCode); 
     if(dwStatusCode == HTTP_STATUS_OK) 
     { 

         CString data; 
        while (pfile -> ReadString(data)) 
         { 
             content += data + "\r\n"; 
         } 
         content.TrimRight(); 

     } 
     pfile -> Close(); 
     delete pfile; 
     session.Close(); 

  //解决CHttpFile中文乱码问题
  char *pStr = content.GetBuffer(content.GetLength()); //取得str对象的原始字符串
  int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0); //取得所需缓存的多少
  wchar_t *pBuffer = (wchar_t*)malloc(nBufferSize * sizeof(wchar_t));//申请缓存空间
  MultiByteToWideChar(CP_UTF8, 0, pStr, -1 , pBuffer, nBufferSize*sizeof(wchar_t));//转码

  CString xx(pBuffer);
  content=xx;



  m_web_text=content; //内容

  free(pBuffer); //释放缓存




  //获取 有用信息数据

  CString str_a = "content=\""+m_my_ct+"-";

  m_web_good_information.Empty();

  m_web_good_information = CString_Extraction_Content(m_web_text,str_a,"\" name=\"description");   //字符串提取中间内容

  if(m_web_good_information.IsEmpty()==1) //网页没有词条解释
  {

   m_web_good_information="没有查询到";
  }



  //去除可能的多余网页代码
  if(m_web_good_information.Find("www.w3.org") || m_web_good_information.Find("<meta content=\"") || m_web_good_information.Find("_互动百科</title>"))
    {


     CString xt;
     xt.Format("_互动百科");


     int nFirst = m_web_good_information.Find(xt);
     m_web_good_information = m_web_good_information.Mid( nFirst+0);

     //滤除多余信息
	 m_web_good_information.Replace( "\n", NULL );
	 m_web_good_information.Replace( "\r", NULL );
     m_web_good_information.Replace( "<meta content=\"", NULL );
     m_web_good_information.Replace( "</title>", NULL );
     m_web_good_information.Replace( "_互动百科", NULL );

    }








 TT=m_web_good_information;

 return TT;

}






CString CAiQiDlg::Get_Weather_Information_From_Web(CString city_number) //从网络上获取天气信息并返回
{
 CString TT;


 CString m_web_url;
 CString m_web_text;
 CString m_web_good_information;




 //m_web_url="http://www.weather.com.cn/weather1d/101020100.shtml";


 m_web_url="http://www.weather.com.cn/weather1d/" + city_number + ".shtml" ;







     CString content; //内容


     CString url = m_web_url; 


     CInternetSession session("HttpClient"); 

     CHttpFile* pfile = (CHttpFile *)session.OpenURL(url); 
       
     DWORD dwStatusCode; 
     pfile -> QueryInfoStatusCode(dwStatusCode); 
     if(dwStatusCode == HTTP_STATUS_OK) 
     { 

         CString data; 
        while (pfile -> ReadString(data)) 
         { 
             content += data + "\r\n"; 
         } 
         content.TrimRight(); 

     } 
     pfile -> Close(); 
     delete pfile; 
     session.Close(); 

   //解决CHttpFile中文乱码问题
   char *pStr = content.GetBuffer(content.GetLength()); //取得str对象的原始字符串
   int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0); //取得所需缓存的多少
   wchar_t *pBuffer = (wchar_t*)malloc(nBufferSize * sizeof(wchar_t));//申请缓存空间
   MultiByteToWideChar(CP_UTF8, 0, pStr, -1 , pBuffer, nBufferSize*sizeof(wchar_t));//转码

   CString xx(pBuffer);
   content=xx;



   m_web_text=content; //内容

   free(pBuffer); //释放缓存




   //获取 有用信息数据



   m_web_good_information.Empty();


   m_web_good_information = CString_Extraction_Content(m_web_text,"<input type=\"hidden\" id=\"hidden_title\" value=\"","C\" />");   //字符串提取中间内容

   if(m_web_good_information.IsEmpty()==1) //网页没有词条解释
   {

    m_web_good_information="没有查询到";
   }


  TT=m_web_good_information;

  return TT;

}




int CAiQiDlg::Learn_CiTiao_From_Web(CString CiTiao) //从网络上学习词条信息  返回学习的数据条数
{

  CString m_web_good_information = Get_CiTiao_Information_From_Web(CiTiao); //从网络上获取词条信息并返回

 
  int aa;

  YUAN_UNIT *new_YUAN_X=NULL; //符号元X

  int New_Data_Sum=0;
  int Old_Data_Sum=0;
  int Learn_Data_Sum=0;

  //------------




    aa=YUAN->Find_name_return_ID(CiTiao); //查找是否有一样概念的元


     if(aa==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,CiTiao);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


     new_YUAN_X->Contacts->Set_data(0,CiTiao); //保存到联系表数据root里




	 }

     else //有这个元
	 {

            new_YUAN_X=YUAN->ID_return_P(aa);
            Old_Data_Sum = new_YUAN_X->Contacts->Get_Sum(); //统计数据表个数


	 }





//------------

 CString S=m_web_good_information;

 S.Replace("\r\n", "");


 int X_weizhi;
 int a_n;

 CString H;
 CString TT;

 int a[2];

 TT.Empty();

 while(1)
{

 H.Empty();

 
 X_weizhi=0;
 a_n=0;

 a[0]=S.Find("，");
 a[1]=S.Find("。");

 if(a[0]==-1&&a[1]==-1)
   {
       break;//都没有找到标点符号
   }
 else
   {


     for(int n=0;n<2;n++)
        {
         if(n==0 && X_weizhi==0 && a[0]!=-1) { X_weizhi=a[0]; a_n=0; continue;}

         if(n==0 && a[0]==-1) { X_weizhi=a[1]; a_n=1;}

         if(a[n]!=-1 &&  a[n]<X_weizhi) { X_weizhi=a[n]; a_n=n;}

        }


   }

        H=S.Left(X_weizhi); //提取一句 到标点符号


//TEXT_OUT_BOX_SAY_3("提取内容："+H,0); //数据在屏幕上输出






//有条件学习
int fwz;
int fx=0;
//-------
fwz = H.Find( "为" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "是" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "可以" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "属于" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "指" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( CiTiao+"是" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( CiTiao+"指" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( CiTiao+"是指" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------

fwz = H.Find( "通常是" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( "意思是" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( "一般指" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( "称为" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------



fx=1;//都学习


fx1:
if(fx==1) //学习
{
              if(new_YUAN_X->Contacts->Find_Data_Return_N(H)==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(H,60);
				New_Data_Sum++;
               }


}







 
   
    //下一句跳过标点开始
    if(a_n==0) {S=S.Mid(X_weizhi+2);}
    else if(a_n==1) {S=S.Mid(X_weizhi+2);}





}



 Learn_Data_Sum = New_Data_Sum - Old_Data_Sum; //统计新学习的数据条数
 if(Learn_Data_Sum<0)  Learn_Data_Sum=0;

 return Learn_Data_Sum;

}









void CAiQiDlg::Display_AUTO_Question_Time(int x, int y,int Time,int MAX_Time,CDC *pDC) //显示自动提问时间
{
 float dx;

 float time,MAX_time;

 MAX_time=(float)MAX_Time;
 time=(float)Time;

 dx= (float)(188 / MAX_time)   * time;



 pDC->FillSolidRect(x,y,x+(int)dx,2,RGB(112,180,158));

}







//识别主谓宾语句格式
int CAiQiDlg::Recognition_ZWB_Form(CString text) //主语和宾语部分可以是一个名词，也可以是一组名词。 谓语动词必须是一个
{


  //CString Debug_Text;

  CString DC,_DC; //谓语动词

  CString S_CString= text; 

  CString L;
  CString R;

  int LN,RN;


//text.Replace( "的", NULL ); 

 text.Replace( "不", "不 " ); //补丁 带“不”的词，把“不”字拆开

 if(text.IsEmpty())  //必须有内容
   {
    return -1;
   }

  //查找文本中的第一个动词，并且返回它
  if(Find_Text_DC(text, &DC)!=1) 
    {
     return -1;
    }



  L.Empty();
  R.Empty();


  Format_String(&S_CString); //格式化字符串 去掉空格


   CString ff; //补丁 带“不”的词，把“不”字拆开
   ff="不 "+DC;
   if(S_CString.Find(ff)!=-1) DC="不 "+DC;

   if(S_CString.Find("不是")!=-1 && DC=="是") DC="不是";



 //把字符串以 动词 为分割，变成2个字符窜
 Split_X_String(S_CString,DC,&L,&R); 

 if(L.IsEmpty() || R.IsEmpty())  //动词前后必须有内容
   {
    return -1;
   }

  LN=Return_String_Words_Sum(L); //返回字符串中单词的数量
  RN=Return_String_Words_Sum(R); 

/*
  if(LN==1)
    {
         Debug_Text.Format("左边单个词:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

    }
  else
    {
         Debug_Text.Format("右边多个词:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

    } 
   
  if(RN==1)
    {
         Debug_Text.Format("右边单个词:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

    }    
  else
    {
         Debug_Text.Format("右边多个词:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

    }   
*/

  if(Find_Text_DC(L, &_DC)==1) //如果有动词退出
    {
     return -1;
    }

 // if(Find_Text_DC(R, &_DC)==1) //如果有动词退出
 //   {
  //   return -1;
 //   }

   L.Replace( "的", NULL );
   R.Replace( "的", NULL );

        // Debug_Text.Format("建立主谓宾语句格式，[%s]%s[%s]",L,DC,R);
        // TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

  return 1;




}




//[形式处理] 建立主谓宾关系 可识别名词形容词 加上词性标签
int CAiQiDlg::Form_Create_ZWB(CString text)
{


  CString Debug_Text;

  CString DC; //谓语动词

  CString S_CString= text; 

  CString L;
  CString R;


  int R_IS_XRC=0;


  int r_flag=1; //返回值 1正常建立   2以前有关系强化  -1失败




  int a=0,b=0,i=0;
  float fdz=0;

  YUAN_UNIT *new_YUAN_X=NULL; //符号元X




  CString tt,tmpch;



  
  text.Replace( "不", "不 " ); //补丁 带“不”的词，把“不”字拆开


 if(text.IsEmpty())  //必须有内容
   {
    return -1;
   }

  //查找文本中的第一个动词，并且返回它
  if(Find_Text_DC(text, &DC)) 
    {
     ;
    }

  else   //如果没有动词
   {
     int r;

     r=Form_Remember_X(text); //形式处理  记忆字符串 生成一个概念 

     //----------



        //AfxMessageBox("生成一个概念");



         return  r;
        }

 

L.Empty();
R.Empty();


  Format_String(&S_CString); //格式化字符串 去掉空格



   CString ff; //补丁 带“不”的词，把“不”字拆开
   ff="不 "+DC;
   if(S_CString.Find(ff)!=-1) DC="不 "+DC;

   if(S_CString.Find("不是")!=-1 && DC=="是") DC="不是";


 //把字符串以 动词 为分割，变成2个字符窜
 Split_X_String(S_CString,DC,&L,&R); 




 if(L.IsEmpty() || R.IsEmpty())  //动词前后必须有内容
   {
    return -1;
   }



/*
         Debug_Text.Format("动词:[%s]",DC);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口
         Debug_Text.Format("S_CString:[%s]",S_CString);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口
         Debug_Text.Format("L:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口
         Debug_Text.Format("R:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //数据显示在窗口

*/





///////////////////////////////













//------------


	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

   L.Replace( "的", NULL );
   R.Replace( "的", NULL );

	 DC.Replace( " ", NULL );




         DC="<"+DC+">"; //谓语加上标签







//------------



  R_IS_XRC = IS_XRC(R);

//------------



    a=YUAN->Find_name_return_ID(L); //查找是否有一样概念的元


     if(a==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //保存到联系表数据root里


     new_YUAN_X->Contacts->Add(DC+R,60); //保存到联系表1里

	 }



     else //有这个元
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

          int Find_Contacts_N;

          Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(DC+R);

              if(Find_Contacts_N==-1) //原来 没有这条联系信息
               {
	            new_YUAN_X->Contacts->Add(DC+R,60);
               }
              else //原来 有这条联系信息
               {

                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //强化联系 数据权值增加
				 r_flag=2;

               }

	 }





//------------

    b=YUAN->Find_name_return_ID(R); //查找是否有一样概念的元


     if(b==-1) //没有这个元
	 {

	 //建立新元
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,R);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;



     new_YUAN_X->Contacts->Set_data(0,R); //保存到联系表数据root里


	 }

     else //有这个元
	 {
          new_YUAN_X=YUAN->ID_return_P(b);

	 }




    if(R_IS_XRC==1) 
      {
       if(new_YUAN_X->Mark.Find("[形]")==-1)
         {
           new_YUAN_X->Mark = "[形]";
         }
           
      }







    return r_flag;



}






void CAiQiDlg::Form_Create_ZWB_EX(CString text) //带有结果输出的命题建立函数
{

              int r=Form_Create_ZWB(text); //[形式处理] 建立命题  格式： 记住 S谓P  、 记住 S


              if(r==1)  //1正常建立

                {


			      TEXT_OUT_BOX_SAY_3("哦，记住了。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				 }

              else if(r==2)  //2以前有关系强化

                {


			      TEXT_OUT_BOX_SAY_3("恩，我觉得也是这样的。",1); //数据在屏幕上输出
  
				  AI_YES_Flag=1;

				 }

			  else

			     {
                  TEXT_OUT_BOX_SAY_3("语法错误！",1); //数据在屏幕上输出

			     }


			


}











CString CAiQiDlg::Get_City_Weather_Number(CString CityName)  //返回城市天气代码
{
  CString TT;
  CString A;
  int X_weizhi;

  if(CityName.IsEmpty()==1)
    {
      TT="没有找到";
      return TT;
    }


  
  X_weizhi = City_Weather_Number.Find(CityName);

  if(X_weizhi==-1)
    {
     TT="没有找到";
     
    }
  else
    {
     A=City_Weather_Number.Mid(X_weizhi-2,1);
     if(A=="A")
       {
        TT=City_Weather_Number.Mid(X_weizhi-13,12);
	   }
     else
       {
        TT=City_Weather_Number.Mid(X_weizhi-10,9);
       }



    }


  return TT;

}









CString CAiQiDlg::Generate_Active_YUAN_List() //生成活跃元列表 一组概念名的字符串
{
  YUAN_UNIT *tmp=YUAN;
  CString text;

  for(;;)
  {
    


    if(tmp->state==1) 
      {
       text+=tmp->name + " ";

      }

    if(tmp->next==NULL)  {  break;  }

    tmp=tmp->next;

  }


 return text;

}



void CAiQiDlg::OnBnClickedButtonSetting()
{
	// TODO: 在此添加控件通知处理程序代码

  CSettingsDlg  dlg;


  dlg.DoModal();

}






void CAiQiDlg::AUTO_Learning(int i) //自动学习 
{

 if( AUTO_Learning_Flag != 1) return;

 if( YUAN_SUM == 0) return;

CString TX;  



 YUAN_UNIT *P_AUTO_Learning_select_YUAN;

TX.Format("一共有概念%d个，当前选择%d",YUAN_SUM,i);
 TEXT_OUT_BOX_SAY_3(TX,0); //数据在屏幕上输出


 P_AUTO_Learning_select_YUAN = YUAN->n_return_P(i);  //得到随机选择的元的指针

 if( P_AUTO_Learning_select_YUAN == NULL) {AUTO_Learning_Flag = 0; TEXT_OUT_BOX_SAY_3("错误",0); return;}

 CString CT=P_AUTO_Learning_select_YUAN->name;
   

 CT.Replace( " ", NULL );

 int n = Learn_CiTiao_From_Web(CT); //从网络上学习词条信息

             

 TX.Format("网上学习词条[%s]完毕，共学习了%d条新数据",CT,n);
 TEXT_OUT_BOX_SAY_3(TX,0); //数据在屏幕上输出


}









void CAiQiDlg::AUTO_Learning_2() //自动学习 
{

 if( AUTO_Learning_Flag != 1) return;

 if( YUAN_SUM == 0) return;

CString TX;  

 int i=0;
 i=Xrand(1,YUAN_SUM); //随机选取一个数字

 YUAN_UNIT *P_AUTO_Learning_select_YUAN;

//TX.Format("一共有概念%d个，当前选择%d",YUAN_SUM,i);
 //TEXT_OUT_BOX_SAY_3(TX,0); //数据在屏幕上输出


 P_AUTO_Learning_select_YUAN = YUAN->n_return_P(i);  //得到随机选择的元的指针

 if( P_AUTO_Learning_select_YUAN == NULL) {AUTO_Learning_Flag = 0; TEXT_OUT_BOX_SAY_3("错误",0); return;}

 CString CT=P_AUTO_Learning_select_YUAN->name;
   

 CT.Replace( " ", NULL );

 int n = Learn_CiTiao_From_Web(CT); //从网络上学习词条信息

             

 TX.Format("网上学习词条[%s]完毕，共学习了%d条新数据",CT,n);
 TEXT_OUT_BOX_SAY_3(TX,0); //数据在屏幕上输出


}







void CAiQiDlg::OnBnClickedButtonOnOnlineLearning()
{
	// TODO: 在此添加控件通知处理程序代码




   AUTO_Learning_Flag=1; //自动学习开始
   AUTO_Learning_Ready_Time=0;

//AUTO_Learning_i=1;
   TEXT_OUT_BOX_SAY_3("自动学习开始",0); //数据在屏幕上输出

}








void TEXT_INPUT_BOX_INIT()
{
 for(int n=0;n<TextInputBox_String_SUM;n++)
 {
  TextInputBox[n].text=_T(" ");



 }



}
















//查找元带标签的联系表数据 返回该数据
bool CAiQiDlg::Find_YUAN_Contacts_Label_Data(CString YUAN_name , CString Label ,CString *YUAN_Data_List)
{

  YUAN_UNIT *tmp;

			 
  CONTACTS_UNIT *P_YUAN_Contacts;				 


  tmp=YUAN;


  CString Data_List;

  CString TT;

  Data_List.Empty();

  for(;;) //遍历所有元
  {


    if(tmp->ID!=0) //0号元以外
     {

      


       if(tmp->state==1 && tmp->name==YUAN_name)
         {

   //遍历联系表
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {

     if(P_YUAN_Contacts->data.Find(Label)!=-1) //找到了标签
	{
		


        TT=P_YUAN_Contacts->data;

         Split_X_String_Head("<"+Label+">",&TT); //去掉前面的标签

          if(TT.IsEmpty()!=1)
		  {
           Data_List += TT + " ";

		  }
        }


 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //遍历联系表end


          }




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END



 if(Data_List.IsEmpty()!=1)
  {
   Format_String(&Data_List); //格式化字符串 去掉多余空格
  }
 else
  {
   return 0;
  }

 *YUAN_Data_List=Data_List;
 return 1;

}



void CAiQiDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
  CAboutDlg  dlg;


  dlg.DoModal();

}
