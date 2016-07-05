// AiQiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <afxinet.h>
#include "AiQi.h"
#include "AiQiDlg.h"

#include "BrainBoxDlg.h" //�ҵĶԻ�������
#include "SettingsDlg.h" //�ҵĶԻ�������

#include "MyFc.h" //���ķִ�


#include "YUAN_struct.h"

#include "YUAN_system.h"


#include "TextOutBox.h" //�������

#include "MyColor.h" //��ɫ����

#include "My_ZiBianMa.h" //�ֱ���


#ifdef _DEBUG
#define new DEBUG_NEW
#endif










TEXT_INPUT_BOX TextInputBox[ TextInputBox_String_SUM ];



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAiQiDlg �Ի���




CAiQiDlg::CAiQiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAiQiDlg::IDD, pParent)
	//, MainTextOut(_T(""))
	, input_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);



    FC_text = _T(""); //���ķִ�

    input_text_0 = _T(""); //������������
	AI_Question_text  = _T(""); //�������ʵ��ַ���

	Enter = 0;
	Flow_run = 0;


    Command_Flag = 0;

    P_layer_0_max_E_YUAN = NULL;
    P_layer_0_max_E_YUAN_AI_Think_Choose = NULL;

    P_layer_1_max_E_YUAN = NULL;
    P_layer_1_max_E_YUAN_AI_Think_Choose = NULL;

    P_layer_2_max_E_YUAN = NULL;
    P_layer_2_max_E_YUAN_AI_Think_Choose = NULL;

    AI_Think_Choose_Contacts_Number=0;//AI˼����ѡ�����ϵ��ı�

    P_User_Answer_objective_YUAN = NULL;  //�û���Ŀ��Ԫ
    P_AUTO_Question_select_YUAN = NULL;  //�Զ�����ѡ�е�Ԫ


    Last_Layer_0_Max_E_YUAN_Name="û����ǿ��ԾԪ"; //���һ����ǿ��ԾԪ������

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

    AI_Happy_Flag = 0; //���� ����
    AI_Happy_Time = 20;
    AI_Happy_MAX_Time = 20;

    AI_Sad_Flag = 0;  //�ͷ� ����
    AI_Sad_Time = 20;
    AI_Sad_MAX_Time = 20;

    AI_Have_Feelings_Flag = 0;
    AI_Have_Feelings_Time = 20;
    AI_Have_Feelings_MAX_Time= 20;

    AI_Welcome_Flag = 0;  //���� ��ӭ
    AI_Welcome_Time = 20;
    AI_Welcome_MAX_Time = 20;



    Waiting_For_Assessment_Flag = 0; //�ȴ����� �ش�
    Waiting_For_Assessment_Time = 80;
    Waiting_For_Assessment_MAX_Time = 80;


    AI_do_not_know = 0; //AI��֪����

	AI_Question_Kind=0; //�������ʵ�����   1��Ԫ�洢���ַ�������    2�����û�������ַ�������



 if (LoadLibrary("RICHED20.DLL") == NULL) //RichEdit�ؼ���ʼ��
{

 AfxMessageBox("riched20.dllû���ҵ�!");

 PostMessage(WM_QUIT,0,0);

} 

AfxInitRichEdit2(); //RichEdit�ؼ���ʼ��


 //һЩ��ʼ������

 load_system_config_file("config/system.txt");       //��ȡsystem�����ļ�

 YUAN=new YUAN_UNIT;  //�����ڴ�

 YUAN->Init();


 init_rand(); //��ʼ�������


 TEXT_OUT_BOX_INIT();


 D.init("CK/CK.txt"); //���شʵ�


 CK_DC= _T(""); //�߼��������õ� ���ʴʿ�
 TxtFileRead_to_CString("CK/DongCi.txt",&CK_DC); //����TXT�ļ����ַ���



 CK_SXBQ= _T(""); //��������õ� ���Ա�ǩ
 TxtFileRead_to_CString("CK/SXBQ.txt",&CK_SXBQ); //����TXT�ļ����ַ���


 CK_XRC= _T(""); //��������õ� ���ݴʴʿ�
 TxtFileRead_to_CString("CK/XRC.txt",&CK_XRC); //����TXT�ļ����ַ���


  City_Weather_Number= _T(""); //������������
 TxtFileRead_to_CString("data/city_weather_number.txt",&City_Weather_Number); //����TXT�ļ����ַ���



if(Auto_Load_And_Save_Memory_Flag ==1) //�Զ����غͱ������
{
  CBrainBoxDlg a;
  a.Load_Memory_File_XML(2,"�����ļ�/AiQi�ļ���.xml");


}




 Display_Startup_Message=1; //��ʾ������Ϣ





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


// CAiQiDlg ��Ϣ�������

BOOL CAiQiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������



  //��ʼ�������������С
 // pEdt=(CEdit*)GetDlgItem(IDC_MainDlg_OUTPUT_EDIT);
 // m_editFont.CreatePointFont(120,"����");
 // pEdt->SetFont(&m_editFont); 


 if(Edit_Brain == 0) //�༭BrainBox������ر�
  {
   GetDlgItem(IDC_BUTTON_ON_BRAINBOX)-> EnableWindow(FALSE);
  }

CButton* popenbtn=(CButton*)GetDlgItem(IDC_BUTTON1);
popenbtn->SetFocus();


/*
//��ťͼƬ
HBITMAP   BmpButton_Setting;   
BmpButton_Setting = LoadBitmap(AfxGetInstanceHandle(),   
    MAKEINTRESOURCE(IDB_BITMAP_BmpButton_Setting)); // IDB_BITMAP_TESTΪ��ԴͼƬID  

((CButton *)GetDlgItem(IDC_BUTTON_Setting))->SetBitmap(BmpButton_Setting); 
*/

	return 0;  
	// ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAiQiDlg::OnPaint()
{

	/*
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//Debug_Text��Ϣ
//˫������ʾ///////////////////////////////////////////

CDC *pDC=GetDC();

int nWidth=300,nHeight=400;



CDC MemDC; //����һ����ʾ�豸����
CBitmap MemBitmap;//����һ��λͼ����
MemDC.CreateCompatibleDC(NULL);//��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight); //���潨��һ������Ļ��ʾ���ݵ�λͼ�����ڵĴ�С
CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap); //��λͼѡ�뵽�ڴ���ʾ�豸��


MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(250,251,247));

//��ͼ--------------------------

//TEXT_OUT_BOX_OutAll(2,6, 0,14,&MemDC); //���



////////�ҵ�Debug������ʾ��Ϣ
CString Debug_Text;

MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(250,251,247));


Debug_Text.Format("AI������Ϣ");
  //MemDC.TextOut(10,10,Debug_Text);
  TextOut_SongTi(10, 10,14,BLUE,Debug_Text,&MemDC);

Debug_Text.Format("AI�Զ����ʵ���ʱ=%d",AI_AUTO_Question_Ready_Time);

  TextOut_SongTi(10,50, 14,BLUE,Debug_Text,&MemDC);

if(P_AUTO_Question_select_YUAN == NULL)
Debug_Text.Format("�Զ�����ѡ���Ԫ=��");
else
Debug_Text.Format("�Զ�����ѡ���Ԫ=%s",P_AUTO_Question_select_YUAN->name);
  TextOut_SongTi(10,70, 14,BLUE,Debug_Text,&MemDC);


if(P_layer_1_max_E_YUAN == NULL)
Debug_Text.Format("��������Ծ��Ԫ=��");
else
Debug_Text.Format("��������Ծ��Ԫ=%s",P_layer_1_max_E_YUAN->name);
  TextOut_SongTi(10,110, 14,BLUE,Debug_Text,&MemDC);

if(P_layer_1_max_E_YUAN_AI_Think_Choose == NULL)
Debug_Text.Format("����㱻AIѡ���Ԫ=��");
else
Debug_Text.Format("����㱻AIѡ���Ԫ=%s",P_layer_1_max_E_YUAN_AI_Think_Choose->name);
  TextOut_SongTi(10,130, 14,BLUE,Debug_Text,&MemDC);

if(P_layer_2_max_E_YUAN == NULL)
Debug_Text.Format("���������Ծ��Ԫ=��");
else
Debug_Text.Format("���������Ծ��Ԫ=%s",P_layer_2_max_E_YUAN->name);
  TextOut_SongTi(10,150, 14,BLUE,Debug_Text,&MemDC);

if(P_layer_2_max_E_YUAN_AI_Think_Choose == NULL)
Debug_Text.Format("�����㱻AIѡ���Ԫ=��");
else
Debug_Text.Format("�����㱻AIѡ���Ԫ=%s",P_layer_2_max_E_YUAN_AI_Think_Choose->name);
  TextOut_SongTi(10,170, 14,BLUE,Debug_Text,&MemDC);


Debug_Text.Format("AI�ȴ��û����ش�����=%d   ����ʱ=%d",Waiting_For_Assessment_Flag,Waiting_For_Assessment_Time);
  TextOut_SongTi(10,190, 14,BLUE,Debug_Text,&MemDC);


if(Run_FC_Flag==1)
{

 Debug_Text.Format("���ķִʽ����");
  TextOut_SongTi(10,230, 14,BLUE,Debug_Text,&MemDC);
 Debug_Text.Format("%s",FC_text);
  TextOut_SongTi(10,250, 14,BLUE,Debug_Text,&MemDC);

}
else
{
 Debug_Text.Format("���ķִʹ����ѹر�");
  TextOut_SongTi(10,230, 14,BLUE,Debug_Text,&MemDC);
}



CString DC;

//�����ı��еĵ�һ�����ʣ����ҷ�����
if(Find_Text_DC(FC_text,&DC))
  {
	  Debug_Text.Format("��һ������:%s",DC);
   TextOut_SongTi(10,270, 14,RGB(115,0,255),Debug_Text,&MemDC);
  }




Debug_Text.Format("����֪ʶ�㣺%d  �ش�����ֵ��%d ",YUAN_Layer_SUM[1],YUAN_Layer_SUM[2]);
  TextOut_SongTi(10,310, 14,RGB(115,0,255),Debug_Text,&MemDC);

////////

//--------------------------

pDC->BitBlt(578,12,nWidth,nHeight,&MemDC,0,0,SRCCOPY); //���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ

MemDC.SelectObject(pOldBit); //��ͼ��ɺ������
MemBitmap.DeleteObject();
MemDC.DeleteDC(); 



ReleaseDC(pDC); //�ͷ�CDC��Դ


*/









if(Display_Startup_Message==1) //��ʾ������Ϣ
{

 TEXT_OUT_BOX_SAY_3("���ã�������������AiQi����ӭʹ�á�",1); //������ʾ����Ļ��

 AI_Welcome_Flag=1; //���� ��ӭ ����

 Display_Startup_Message=0;

}







//˫������ʾ2///////////////////////////////////////////

CDC *pDC2=GetDC();


int nWidth2=188,nHeight2=298; 



CDC MemDC2; //����һ����ʾ�豸����
CBitmap MemBitmap2;//����һ��λͼ����
MemDC2.CreateCompatibleDC(NULL);//��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
MemBitmap2.CreateCompatibleBitmap(pDC2,nWidth2,nHeight2); //���潨��һ������Ļ��ʾ���ݵ�λͼ�����ڵĴ�С
CBitmap *pOldBit2=MemDC2.SelectObject(&MemBitmap2); //��λͼѡ�뵽�ڴ���ʾ�豸��


MemDC2.FillSolidRect(0, 0,nWidth2,nHeight2,RGB(255,255,255));

//��ͼ--------------------------




Change_Face(0, 0,&MemDC2); //�����  0,0 �����������






//��ʾ֪ʶ����Ϣ
CString TT;
TT.Format("����֪ʶ�㣺%d",YUAN_SUM);
  TextOut_SongTi(38,228, 20,RGB(8,117,80),TT,&MemDC2);
TT.Format("�ش�����ֵ��%d ",YUAN_CONTACTS_SUM);
  TextOut_SongTi(38,248, 20,RGB(8,117,80),TT,&MemDC2);



//��ʾ�Զ�����ʱ��
if(AI_AUTO_Question_Flag==1)
{


 Display_AUTO_Question_Time(0, 146,AI_AUTO_Question_Ready_Time,AI_AUTO_Question_Ready_MAX_Time,&MemDC2); 

}



//--------------------------

pDC2->BitBlt(450,17,nWidth2,nHeight2,&MemDC2,0,0,SRCCOPY); //���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ

MemDC2.SelectObject(pOldBit2); //��ͼ��ɺ������
MemBitmap2.DeleteObject();
MemDC2.DeleteDC(); 


ReleaseDC(pDC2); //�ͷ�CDC��Դ






}




//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAiQiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






int CAiQiDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������



   SetTimer(1,100,NULL);   //Ԫ����������

   SetTimer(36,100,NULL);  //��Ļ��ʾ 


  SetTimer(30,100,NULL); //��ʱ�� ������

  SetTimer(31,100,NULL); //��ʱ�� �Զ�����

  SetTimer(33,100,NULL); //��ʱ�� MyDebug


  SetTimer(38,100,NULL);  //�ȴ����� �ش�



  //CSayDlg::SendMessage(WM_SETICON,ICON_SMALL,(LPARAM)hIcon);  //������Ϣ���Ĵ���ͼ��


if(Run_FC_Flag==1)
 FC_text="���ķִʹ����ѿ���";
else
 FC_text="���ķִʹ����ѹر�"; 

string s=FC_text.GetBuffer(0);

 s = D.SegmentWord(s); //���ַ����������ķִ�

FC_text = s.c_str();  




	return 0;
}



void CAiQiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ




CString TT;

  CString SXBQ,SXBQ_text;
  int SXBQ_N;

    if(nIDEvent==1) //1�Ŷ�ʱ���������;
      {

		if(YUAN_RUN_MAIN_Flag==1)
        YUAN_RUN_MAIN();  //Ԫ����������
 
      }



    if(nIDEvent==36) //36�Ŷ�ʱ���������;
      {
       //ˢ����ʾ��Ļ
 
       OnPaint();
 
      }



    if(nIDEvent==38) //38�Ŷ�ʱ���������; �ȴ����� �ش�
      {
       //�ȴ����� �ش�
 

 



       if(Waiting_For_Assessment_Flag==1)
	   {
           Waiting_For_Assessment_Time--;

 


           if(Waiting_For_Assessment_Time<=0) //�û������Ѿ�����
             {
              Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;


              Waiting_For_Assessment_Flag=0;


             }



	   }





      }




    if(nIDEvent==30) //30�Ŷ�ʱ���������;
    {

      if(Think_flag==1)
	  {
        Think_time--;

          //�ı䴰�ڱ���
         //SetWindowText("���Ժ����ڴ�����...");
        ((CEdit*)GetDlgItem(IDC_MainDlg_INPUT_EDIT))-> EnableWindow(FALSE);//SetReadOnly(TRUE); //�����������






        if(Think_time<=0) //˼��ʱ����� �����Ծ��Ԫ ��������

		{
         Think_time=Think_MAX_time;
         Think_flag=0;


                ((CEdit*)GetDlgItem(IDC_MainDlg_INPUT_EDIT))-> EnableWindow(TRUE);//SetReadOnly(TRUE); //�������ָ�
	   	
                ((CEdit*)GetDlgItem(IDC_MainDlg_INPUT_EDIT))->SetFocus(); //�ָ��༭�����꽹��

				//��ش���-------------------------











               if(Command_Flag==1)  //<��ͨ����>                �������ַ��������ݽ���ģ��ƥ�䣬�������һ�������ţ����
			   {



 //�õ����Ծ��Ԫ
 P_layer_0_max_E_YUAN=YUAN->Find_layer_max_E_YUAN_P(30,0);

 //AIѡ��� ���� �ȴ����۵� Ԫ
 P_layer_0_max_E_YUAN_AI_Think_Choose=NULL; 


 int input_text_word_sum=Return_String_Words_Sum(input_text_0); //���������ַ����е��ʵ�����



 if(P_layer_0_max_E_YUAN!=NULL)
 {
  Last_Layer_0_Max_E_YUAN_Name = P_layer_0_max_E_YUAN->name; //���� ���һ����ǿ��ԾԪ������
 }
 else
 {
  Last_Layer_0_Max_E_YUAN_Name.Empty();
 }



 //ͳ�Ƶ�ǰ���л�ԾԪ����¼���б�-------------------------------------

 CString Active_YUAN_List;//��ԾԪ�б� 

 Active_YUAN_List=Generate_Active_YUAN_List(); //���ɻ�ԾԪ�б� ��¼���е�ǰ�����Ԫ������



 CString Active_YUAN_List_MC; //�����Ԫ�е������б�
 CString Active_YUAN_List_XRC; //�����Ԫ�е����ݴ��б�

 int SUM=Return_String_Words_Sum(Active_YUAN_List); //�����ַ����е��ʵ�����
 CString Word;

  for(int i=1; i<=SUM ; i++)
  {
   Word=Return_String_N_Word(Active_YUAN_List,i); //�����ַ�����N������

   if(IS_XRC(Word)) //�����ݴ�
     {
      Active_YUAN_List_XRC += Word+" "; //׷�ӵ����ݴ��б�
     }
   else   //������
     {
      Active_YUAN_List_MC += Word+" "; //׷�ӵ������б�
     } 
  }

 if(Active_YUAN_List_XRC.IsEmpty()) Active_YUAN_List_XRC="û��";

 //TEXT_OUT_BOX_SAY_3("��Ծ�����б�"+Active_YUAN_List_MC,0); //��������Ļ�����
 //TEXT_OUT_BOX_SAY_3("��Ծ���ݴ��б�"+Active_YUAN_List_XRC,0); //��������Ļ�����

 //----------------





//�м��ʵ������б��������-------------------------------------



  int KeNeng=Xrand(0,100); //���ɿ�����

       if(KeNeng>=0 && KeNeng<=70)
         {

             if(Recognition_ZWB_Form(input_text_0)==1 ) //����ν������ʽ------

               {

                  //AfxMessageBox("������ν����䣬��������");

                 //[��ʽ����] ��������  ��ʽ�� ��ס SνP  �� ��ס S
                 Form_Create_ZWB_EX(input_text_0); //���н����������⽨������

                 goto HDCL_END;


               }


             if(Recognition_SXBQ_Form(input_text_0)==1 ) //�Ǵ���ǩ����Ľ�������ʽ------

               {

                  //AfxMessageBox("���Ǵ���ǩ��䣬���������ʽ");



                 //��ǩ����Ľ�������
                 Form_Create_SXBQ_EX(input_text_0); //���н������ı�ǩ���佨������

                 goto HDCL_END;


               }


	    }



   //�޻�Ծ��Ӧ-------------------------------------------------------



     if(Active_YUAN_List.IsEmpty()) //���û�л�Ծ��Ԫ��ֱ���˳�
	   {





         //�û������Ƕ������=====
          if(input_text_word_sum!=1)
          {



		    TT.Format("���޷������˵�Ļ�");

            AI_NO_Flag=1;

		    AI_do_not_know = 1; //AI��֪����

		    TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
            goto HDCL_END;



          }
         //�û������ǵ�������=====
	     else
	     {

	    	TT.Format("�Ҳ�֪��...������û�о�");

            AI_NO_Flag=1;

	    	AI_do_not_know = 1; //AI��֪����

		    TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
            goto HDCL_END;
	     }




	   }
          





  //�л�Ծ��Ӧ----------------------------------------------------------


  SXBQ_text=input_text_0;


  //�����ı��еĵ�һ�����Ա�ǩ�ʣ����ҷ�����
  SXBQ_N = Find_Text_SXBQ(SXBQ_text, &SXBQ);
  if(SXBQ_N == -1) 
    {
     //goto SXBQPD_END;
    }

  else
    {

      CString YUAN_Data_List; //����ǩ�����ݱ�


      SXBQ_text.Replace("�� "+SXBQ,SXBQ);
      Format_String(&SXBQ_text); //��ʽ���ַ��� ȥ������ո�

     if(Return_String_N_Word(SXBQ_text,2) == SXBQ ) //�ڶ������Ǳ�ǩ
       {
          // AfxMessageBox("!!!");

			 CString YUAN_name = Return_String_N_Word(SXBQ_text,1); //��һ������Ԫ����

			
			 YUAN_Data_List.Empty();

           //����Ԫ����ǩ����ϵ������ ���ظ�����
           Find_YUAN_Contacts_Label_Data(YUAN_name , SXBQ ,&YUAN_Data_List);

           if(YUAN_Data_List.IsEmpty()!=1) //��Ԫ�б�ǩ
		     {
              TEXT_OUT_BOX_SAY_3(YUAN_Data_List+"..",1); //��������Ļ�����


              goto HDCL_END;

		     }
		  // else AfxMessageBox("!!!");

       }


	 else  //����һ�����Ը�ʽ
	  {
        if(P_layer_0_max_E_YUAN!=NULL)//�����Ծ��Ԫ
		  {
			 YUAN_Data_List.Empty();

            //����Ԫ����ǩ����ϵ������ ���ظ�����
            Find_YUAN_Contacts_Label_Data(P_layer_0_max_E_YUAN->name , SXBQ ,&YUAN_Data_List);

            if(YUAN_Data_List.IsEmpty()!=1) //��Ԫ�б�ǩ
		      {
               TEXT_OUT_BOX_SAY_3(YUAN_Data_List+"...",1); //��������Ļ�����


               goto HDCL_END;

		      }
		  }

	  }



    }



    //SXBQPD_END:;


   //-------------------

  //TEXT_OUT_BOX_SAY_3("�û������ǵ�������",1); //��������Ļ�����

       KeNeng=Xrand(0,100); //���ɿ�����

       if(KeNeng>=0 && KeNeng<=40) //��ѡ���ԾԪ������һ��Ԫ����+++++++++++++
         {

		    if(P_layer_0_max_E_YUAN!=NULL) //0�������Ծ��Ԫ
              {

                      keneng1:;

                     int nn=0;
                     int Contacts_Sum=P_layer_0_max_E_YUAN->Contacts->Get_Sum();


                     if(Contacts_Sum!=1) //�����ϵ�����ж�����Ϣ
                       {
                         int xn=Xrand(0,100);

                          if(xn<=5)
                            {
                             TT.Format("%s",P_layer_0_max_E_YUAN->Contacts->data); //ѡȡ��ϵ�������

		                     TT.Replace( " ", NULL );
                             //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
                             Run_YUAN_Contacts_Data(TT); //����һ�����Ԫ���������
                            }


                        else{
                              nn=Xrand(1,Contacts_Sum-1); //�������ϵ����ѡȡһ���������
                              TT.Format("%s",P_layer_0_max_E_YUAN->Contacts->Get_n_data(nn));

		                      TT.Replace( " ", NULL );
                              //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
                              Run_YUAN_Contacts_Data(TT); //����һ�����Ԫ���������							  
                            }

                       } 


                     else    //�����ϵ����ֻ��һ����Ϣ
                       {
                        TT.Format("%s",P_layer_0_max_E_YUAN->Contacts->data); //ѡȡ��ϵ�������


		                TT.Replace( " ", NULL );
                        //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
                        Run_YUAN_Contacts_Data(TT); //����һ�����Ԫ���������
                       }




                     int xx=Xrand(1,100);

                     if(xx<=100) //��100%�Ŀ��ܣ����Ի������û����ۻش�  ��������ʽ���ۻ���
					 {
                      //AI_Have_Feelings_Flag=1; //AI�ио� �������û��Իش������
			          Waiting_For_Assessment_Flag=1; //AI�ش�󴥷�����ʱ��
                      Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;

					  //TT.Format("�һش���ȷ�𣿿������ۣ������");
					  //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

					  P_layer_0_max_E_YUAN_AI_Think_Choose=P_layer_0_max_E_YUAN; //AIѡ��� ���� �ȴ����۵� Ԫ
					  AI_Think_Choose_Contacts_Number=nn;
					  

					 }

			  }

			else//0��û�����Ծ��Ԫ
			  {
				TT.Format("�Ҳ�֪��...");

                AI_NO_Flag=1;

				AI_do_not_know = 1; //AI��֪����

				TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

				
			  }


			goto HDCL_END;

         }

	   else if (KeNeng>40 && KeNeng<=50) //��ѡ��Ծ�б���һ��Ԫ��˵�����Ԫ������++++++++++++
         {
              CString D_NAME;
              int SUM=Return_String_Words_Sum(Active_YUAN_List); //�����ַ����е��ʵ�����

              if(SUM==1)
                {
                D_NAME=Active_YUAN_List;
                }
              else
                {
                 int n=0;
                 n=Xrand(1,SUM); //���ѡȡһ��Ԫ
                 D_NAME=Return_String_N_Word(Active_YUAN_List,n); //�����ַ�����N������
                }

               TEXT_OUT_BOX_SAY_3("�Ҹо���"+D_NAME,1); //��������Ļ�����

			   goto HDCL_END;

         }

	   else if(KeNeng>50 && KeNeng<=100) //�����ԾԪ�б�+++++++++++++
         {
            //  TEXT_OUT_BOX_SAY_3("����������Щ�����ڻ�Ծ��"+Active_YUAN_List,1); //��������Ļ�����





              if(Active_YUAN_List_XRC!="û��") //�����ݴ�
                {
                 int n=0;
                 int SUM;
                 CString MC_Word,XRC_Word;


                 SUM=Return_String_Words_Sum(Active_YUAN_List_XRC); //�����ַ����е��ʵ�����
                 n=Xrand(1,SUM); //���ѡȡһ��Ԫ  ��ȡ���ݴ�
                 XRC_Word=Return_String_N_Word(Active_YUAN_List_XRC,n); //�����ַ�����N������


                 SUM=Return_String_Words_Sum(Active_YUAN_List_MC); //�����ַ����е��ʵ�����
                 n=Xrand(1,SUM); //���ѡȡһ��Ԫ  ��ȡ����
                 MC_Word=Return_String_N_Word(Active_YUAN_List_MC,n); //�����ַ�����N������

				 //���ݴ�+���� ��������������----------------
				 int nn=Xrand(0,100); 
				 if(nn>=0 && nn<=30) 
				 {
				  TEXT_OUT_BOX_SAY_3(XRC_Word +"��"+MC_Word,1); //��������Ļ����� 
				 }

				 else if(nn>30 && nn<=60) 
				 {
				  TEXT_OUT_BOX_SAY_3(XRC_Word +"�Ĵ���",1); //��������Ļ����� 
				 }

				 else if(nn>60 && nn<=85) 
				 {
				  TEXT_OUT_BOX_SAY_3(XRC_Word +"�ĸо�",1); //��������Ļ����� 
				 }
                 
				 else if (nn>85 && nn<=100) 
				 { 
				  TEXT_OUT_BOX_SAY_3("��"+MC_Word+"�ĸо�"+"��"+"��"+XRC_Word +"��"+"����"+"��",1);//��������Ļ�����
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

			   else if(Command_Flag==10)  //<�߼�������� ��������ֵ>  �û�����һ�仰��"?"���ؼ��֣���AI�жϸ�����Ƿ�ͼ����߼�ƥ��
			   {






                     //TT.Format("�߼��������10"); 
                     //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                     //�õ��𰸣����������Ծ��Ԫ��



                       CString text_DC;
					   CString Contacts_data_DC;
                       YUAN_UNIT *MAX_PF_YUAN=NULL;
                       CString MAX_PF_YUAN_Contacts_data;

                       Find_Text_DC(input_text_0, &text_DC);//�����ı��еĵ�һ�����ʣ����ҷ�����



					   if(text_DC.IsEmpty()!=1)//=========�ж���
					   {

						   CString LL;
						   CString RR;


                         //  TT.Format("���ķִ�=%s",input_text_0); 
                         //   TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
                         //  TT.Format("����=%s",text_DC); 
                         //   TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                           CString FouDingDC; //�񶨶���


						   FouDingDC="�� "+text_DC;
                           if(input_text_0.Find(FouDingDC)!=-1) //�з񶨶���
						   {

                            

						   Split_X_String(input_text_0,FouDingDC,&LL,&RR); //���ַ�����XΪ�ָ���2���ַ���


 
                           RR=FouDingDC+RR;


                         //  TT.Format("�����з񶨶���=%s",FouDingDC); 
                         //   TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

						   }

						   else  //ֻ�п϶�����
						   {
						   Split_X_String(input_text_0,text_DC,&LL,&RR); //���ַ�����XΪ�ָ���2���ַ���


 
                           RR=text_DC+RR;
                           FouDingDC.Empty();

						   }

                         

                         //  TT.Format("RR=%s",RR); 
                         //  TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


//AfxMessageBox(RR);

 
                          Find_YUAN_Contacts(RR,60,  &MAX_PF_YUAN, &MAX_PF_YUAN_Contacts_data);  //���������Ƶ���ϵ������ ���ظ����� �� Ԫָ��  ǰ���Ԫ״̬��1

					     Find_Text_DC(MAX_PF_YUAN_Contacts_data, &Contacts_data_DC);

                          //TT.Format("�߼��������10  �ж���"); 
                          //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
           //&& Contacts_data_DC==text_DC
                          if(MAX_PF_YUAN!=NULL ) //YUAN�������������Ƶ���ϵ������
						  {

                             int nn=0;
							 CString nnT;

                             CString  FouDingDC2;
								 
								 
								FouDingDC2 ="��"+text_DC;




                               if(FouDingDC.IsEmpty()==1) //������û�з񶨶���
							   {
                                 if(MAX_PF_YUAN_Contacts_data.Find(FouDingDC2)==-1) //������û�з�
								   {
                                    nn=1;
								   }
								 else
								   {
                                    nn=2;
								   }
							   }


							   else  //�������з񶨶���
							   {
                                 if(MAX_PF_YUAN_Contacts_data.Find(FouDingDC2)==-1) //������û�з�
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

					               nnT="��";

 

					              }

                               else if(nn==2)
					              {

					                nnT="��";



				               	}
						 



                            //TT.Format("�����Ҿ���%s%s",LL,MAX_PF_YUAN_Contacts_data);

                             MAX_PF_YUAN_Contacts_data.Replace( "<", NULL );
                             MAX_PF_YUAN_Contacts_data.Replace( ">", NULL );

                              TT.Format("%s������Ϊ%s%s",nnT,LL,MAX_PF_YUAN_Contacts_data); 


                            TT.Replace( " ", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
						  }

						  else//û���ҵ����Ƶ�����
						  {
                            TT.Format("�Ҳ�֪����������"); 

                            TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                            AI_NO_Flag=1;

						  }



					   }

					   else //=========�޶���
					   {
                        
            

					     //TT.Format("�߼��������10  �޶���"); 
                         //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


                         YUAN_UNIT *MC_YUAN=YUAN->Find_layer_max_E_YUAN_P(30,0);

						 if(MC_YUAN!=NULL)//�����ʵ�Ԫ��Ӧ
						 {
                          int nn=0;
                          int Contacts_Sum=MC_YUAN->Contacts->Get_Sum();
                          if(Contacts_Sum!=1) //�����ϵ�����ж�����Ϣ
                            {
                             nn=Xrand(0,Contacts_Sum-1); //�������ϵ����ѡȡһ���������
                             TT.Format("%s",MC_YUAN->Contacts->Get_n_data(nn));
                            } 
                          else //�����ϵ����ֻ��һ����Ϣ
                            {
                             TT.Format("%s",MC_YUAN->Contacts->data); //ѡȡ��ϵ�������
                            }

		                    TT.Replace( " ", NULL );
							TT.Replace( "<", NULL );
							TT.Replace( ">", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

						 }

						 else
						 {
                           TT.Format("�Ҳ�֪�����������ʲô������"); 

                           TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                            AI_NO_Flag=1;
						 }


					   }







			   }



                //---------------




			   else if(Command_Flag==11) //<�߼�������� ���>        �û�����һ�仰��"ʲô"���ؼ��֣���AI�ȶԼ����߼�ƥ�䣬Ȼ������������"ʲô"�������
			   {
                    // TT.Format("�߼��������11"); 
                     //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                    CString text_DC;
                    CString LL;
                    CString RR;
                       YUAN_UNIT *MAX_PF_YUAN=NULL;
                       CString MAX_PF_YUAN_Contacts_data;

					//�ж���=================================
                    if(Find_Text_DC(input_text_0, &text_DC))//�����ı��еĵ�һ�����ʣ����ҷ�����
					{

                     //TT.Format("�ж���"); 
                     //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


                       Split_X_String(input_text_0,text_DC,&LL,&RR); //���ַ�����XΪ�ָ���2���ַ���


                         //�ж�ʲô�ڶ���ǰ��=======
					   if(LL.Find("ʲô") !=-1 && RR.Find("ʲô") ==-1)
					   {
                         //TT.Format("ʲô�ڶ������"); 
                         //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


                                       //����񶨶���
                                       CString FDDC;

                                       FDDC="��"+text_DC; 

                                       LL=LL+text_DC;
                                       LL.Replace( " ", NULL );

                                       if(LL.Find(FDDC)==-1) //û�з񶨶���
                                       {
                                        LL.Replace( text_DC, NULL );

                                       }

                                       else           //�з񶨶���
                                       {
                                        text_DC=FDDC;
                                        LL.Replace( FDDC, NULL );
                                         //TT.Format("�з񶨶��ʣ�");
                                         // TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                                       }


                         CString XD="<"+text_DC+">";
                         Find_YUAN_X_Contacts(XD+RR,150,  &MAX_PF_YUAN, &MAX_PF_YUAN_Contacts_data);  //���������Ƶ���ϵ������ ���ظ����� �� Ԫָ��  ��״̬����Ԫ  ��ϵ������Ȩֵ����һ��Ԫ



						 if(MAX_PF_YUAN!=NULL ) //YUAN�������������Ƶ���ϵ������
						 {



                            TT.Format("�Ҿ���%s%s",MAX_PF_YUAN->name,text_DC+RR);
							TT.Replace( " ", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

					       }
                         else
							 {


                                 if(text_DC=="��")
						           {

                                    TT.Format("ʲô%s%s...�����㿼�����ˣ��Ұ������ϲ��ɣ���~",text_DC,RR); 
							        TT.Replace( " ", NULL );
                                    TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

						            CString CiTiao=RR;
                                    CString m_web_good_information = Get_CiTiao_Information_From_Web(CiTiao); //�������ϻ�ȡ������Ϣ������
						            TEXT_OUT_BOX_SAY_3(m_web_good_information,1); //��������Ļ�����
						           }

								 else
								 {
                                  TT.Format("�Ҳ�֪��...ʲô%s",text_DC+RR); 
							      TT.Replace( " ", NULL );
                                  TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

							      AI_NO_Flag=1;

							     }
						     }

					   }


                         //�ж�ʲô�ڶ��ʺ���=======
					   if(LL.Find("ʲô") ==-1 && RR.Find("ʲô") !=-1)
					   {
                        // TT.Format("ʲô�ڶ����ұ�"); 
                        // TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����



                                       //����񶨶���
                                       CString FDDC;

                                       FDDC="��"+text_DC; 

                                       LL=LL+text_DC;
                                       LL.Replace( " ", NULL );

                                       if(LL.Find(FDDC)==-1) //û�з񶨶���
                                       {
                                        LL.Replace( text_DC, NULL );

                                       }

                                       else           //�з񶨶���
                                       {
                                        text_DC=FDDC;
                                        LL.Replace( FDDC, NULL );
                                        //TT.Format("�з񶨶��ʣ�");
                                         //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                                       }

                          //  TT.Format("���ʣ�%s",text_DC);
                          //  TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

						





                         Find_YUAN_X_Contacts_DC(text_DC+RR,50,&MAX_PF_YUAN, &MAX_PF_YUAN_Contacts_data,text_DC);

						 if(MAX_PF_YUAN!=NULL ) //YUAN�������������Ƶ���ϵ������
						   {
						    MAX_PF_YUAN_Contacts_data.Replace( "<", NULL );
                            MAX_PF_YUAN_Contacts_data.Replace( ">", NULL );


                            TT.Format("�Ҿ���%s%s",LL,MAX_PF_YUAN_Contacts_data);




							TT.Replace( " ", NULL );
                            TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

					       }
                         else if (MAX_PF_YUAN==NULL ) 
						   {


                                 if(text_DC=="��")
						           {

                                    TT.Format("%s%sʲô...�����㿼�����ˣ��Ұ������ϲ��ɣ���~",LL,text_DC); 
							        TT.Replace( " ", NULL );
                                    TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

						            CString CiTiao=LL;
                                    CString m_web_good_information = Get_CiTiao_Information_From_Web(CiTiao); //�������ϻ�ȡ������Ϣ������
						            TEXT_OUT_BOX_SAY_3(m_web_good_information,1); //��������Ļ�����
						           }

								 else
								   {
                                    TT.Format("�Ҳ�֪��...%s%sʲô",LL,text_DC); 
							        TT.Replace( " ", NULL );
                                    TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                                    AI_NO_Flag=1;

								   }

							  
						   }



					   }


					}

                    //û�ж���==============================
					else
					{
                     TT.Format("û�ж���"); 
                     TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����



					}
					



                     




			   }













                //---------------------------------




                //�ı䴰�ڱ���
                //SetWindowText("������");


		}

	  }



	}



    if(nIDEvent==31) //31�Ŷ�ʱ���������; �Զ�����  �� �ȴ�����
    {


      //-----------------------�ش�ķ�Ӧ
      if(AI_YES_Flag==1)
	  {
           AI_YES_Time--;

 


           if(AI_YES_Time<=0) //AI ���
             {
              AI_YES_Time=AI_YES_MAX_Time;


              AI_YES_Flag=0;


             }



	  }

	




      if(AI_NO_Flag==1)
	  {
           AI_NO_Time--;

 


           if(AI_NO_Time<=0) //AI δ���
             {
              AI_NO_Time=AI_NO_MAX_Time;


              AI_NO_Flag=0;



             if(AI_do_not_know == 1) //AI��֪����
               {
                 AI_do_not_know = 0;


                 if(AI_Feedback_Question_Flag == 1)
				 {

                  int nn=Xrand(1,100);
                  CString TT;

                  if(nn<=80) //��80%�Ŀ��ܣ����Ի�������ղ�������ʲô������
                    {



                      AI_Question_text=input_text_0; //���������input_text_0 �����иղ��û�������ַ�����Ϣ  ������ַ������� �������ʵ��ַ���

                      TT.Format("�ɲ����Ը����ң���%s����Ӧ�Ļش���ʲô��",AI_Question_text);
                      TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


                     TEXT_OUT_BOX_SAY_3("�������",1); //��������Ļ�����


                       AI_Question_Kind=2;   //���Զ����û�������ַ�������

                       User_Answer_Flag=1;  //�û��ش� ����
                       User_Answer_Time = User_Answer_MAX_Time;

                    }

				 }

               }








             }



	  }


      if(AI_Happy_Flag==1)
	  {
           AI_Happy_Time--;

 


           if(AI_Happy_Time<=0) //���� ����
             {
              AI_Happy_Time=AI_Happy_MAX_Time;


              AI_Happy_Flag=0;


             }



	  }
	  



      if(AI_Sad_Flag==1)
	  {
           AI_Sad_Time--;

 


           if(AI_Sad_Time<=0) //�ͷ� ����
             {
              AI_Sad_Time=AI_Sad_MAX_Time;


              AI_Sad_Flag=0;


             }



	  }



      if(AI_Welcome_Flag==1)
	  {
           AI_Welcome_Time--;

 


           if(AI_Welcome_Time<=0) //���� ��ӭ
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
			   Waiting_For_Assessment_Flag=1; //AI�ش�󴥷�����ʱ��
               Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;
		   }



           if(AI_Have_Feelings_Time<=0) //AI�и�����ڵĸо�
             {
              AI_Have_Feelings_Time=AI_Have_Feelings_MAX_Time;


              AI_Have_Feelings_Flag=0;

              

             }



	  }



      //-----------------------�Զ�ѧϰ

      if(AUTO_Learning_Flag==1)
	  {
           AUTO_Learning_Ready_Time--;

 


         if(AUTO_Learning_Ready_Time<=0) //�Զ�ѧϰʱ�䵽�� 
           {
              AUTO_Learning_Ready_Time=AUTO_Learning_Ready_MAX_Time;


              //TEXT_OUT_BOX_SAY_3("����ѧϰ",0); //��������Ļ�����



              // AUTO_Learning(AUTO_Learning_i); //�Զ�ѧϰ
			  AUTO_Learning_2(); //�Զ�ѧϰ
/*
			   			  AUTO_Learning_i++;
						  if(AUTO_Learning_i>YUAN_SUM)
						    {
								AUTO_Learning_Flag=0;
								TEXT_OUT_BOX_SAY_3("����ѧϰ�ѽ���",0); //��������Ļ�����

								}

								*/


		   }




	  }



      //-----------------------�ش�ķ�Ӧ



      if(AI_AUTO_Question_Flag==1)
	  {
           AI_AUTO_Question_Ready_Time--;

 


         if(AI_AUTO_Question_Ready_Time<=0) //�Զ�����ʱ�䵽�� 
           {
              AI_AUTO_Question_Ready_Time=AI_AUTO_Question_Ready_MAX_Time;




                  AUTO_Question_2(); //�Զ�����   ��Ԫ�洢���ַ�������
	              if(P_AUTO_Question_select_YUAN != NULL )  
		            {
                        User_Answer_Flag=1;
                        P_User_Answer_objective_YUAN =  P_AUTO_Question_select_YUAN;

                        AI_Question_Kind=1;  //�������ʵ����� 1��Ԫ�洢���ַ�������

		            }





  







          }



	  }




      if(User_Answer_Flag==1)
	  {
           User_Answer_Time--;

 


           if(User_Answer_Time<=0) //�û�����ʱ���Ѿ�����
             {
              User_Answer_Time=User_Answer_MAX_Time;


              User_Answer_Flag=0;
			  P_User_Answer_objective_YUAN = NULL;

			  AI_Question_Kind=0;

             }



	  }

	}


   if(nIDEvent==33) //33�Ŷ�ʱ���������  MyDebug()
   {

    MyDebug();

   }



	CDialog::OnTimer(nIDEvent);
}













void CAiQiDlg::YUAN_RUN_MAIN()  //Ԫ����������
{
 float W=0; //Wͳ��ǿ��������ֵ





   YUAN_UNIT *tmp;
   LINK_UNIT *linker_tmp;
   YUAN_UNIT *tmpY;

   float aE=0,bE=0; //����˫����Eֵ�Ƚ�


  tmp=YUAN;


  int YuanSum=0; //ͳ��Ԫ��Ŀ
  int YuanContactsSum=0; //ͳ��Ԫ��ϵ����Ŀ
  int ln=0; //ͳ��ÿ���Ԫ��Ŀ

   for(ln=0;ln<8;ln++)
   {
    YUAN_Layer_SUM[ln]=0;
   }


  for(;;) //��������Ԫ
  {


      linker_tmp=tmp->linker; //�ѵ�ǰԪ������root����linker_tmp

    if(tmp->ID!=0) //0��Ԫ����
     {


      W=0; //Wͳ�Ƴ�ʼ��




     //ͳ��ÿ���Ԫ��Ŀ
     ln=tmp->Layer;
     YUAN_Layer_SUM[ln]++;



      for(;;) //������������
	  {





           //IF��������Ԫ�Ǽ���״̬
           if(YUAN->ID_return_P(linker_tmp->linker_ID) ->state==1)
             {  

/*
              //Wͳ������Ӱ���Ԫ���������أ�������� 
              
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








          if(_Run_Forgot==1 && Run_Forgot==1) //��������
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


            if(linker_tmp->linker_weight==0)//IF������0����ʧ
			{

             YUAN->Del_a_link(linker_tmp->linker_ID,tmp->ID);
			}

		  }









           if(linker_tmp->next==NULL)
             {
              break;
             }

           linker_tmp=linker_tmp->next;      

	  }  //������������END

     }





   if(W!=0) 
   {
	   tmp->E =0;
   tmp->E = W + tmp->E_X ; // ��Ӧǿ��Ϊ���м������������

   }

   if(W==0 && tmp->E_X!=0) //�����ӵĴ̼�����������
   {
	   tmp->E =0;
     tmp->E = W + tmp->E_X ; 
   }



      if(tmp->E!=0)
	  {
       tmp->E-=E_minus;   // ��Ӧǿ��˥��
       if(tmp->E<0) tmp->E=0;
      }







   //Ԫ�� �ٽ�ֵ �� ƣ��ֵ �ж�������״̬
   if(tmp->E >= tmp->threshold + tmp->fag) //�������ش��ڷ�ֵ �򼤻�

     {
      if(tmp->state==0)//ԭ����״̬��0
        {

              tmp->state=2;
              
              tmp->Learn_Ready_Time=Learn_Ready_Time_MAX;

        }
      else
        {

        }

     }

    else if (tmp->E < tmp->threshold) //��������С�ڷ�ֵ �򲻼���
     {
      if(tmp->state==1 )//ԭ����״̬��1
        {
              tmp->state=0;


            //�����б���Ԫ���ӵ�Ԫ����������F_X,ǿ��Ϊ����ֵ ˥������
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




 //׼���������
    if(tmp->state==2) 
	{
        //��Ӽ�������
        //�������ݱ����ԡ��ǡ���ǩ��ͷ��Ԫ
      Find_YUAN_Contacts_Label_Activation_YUAN(tmp,"<��>",80);//����<��>��ǩ��ͷ����ϵ���е����� ��Ӧ��Ԫ
	  Find_YUAN_Contacts_Label_Inhibit_YUAN(tmp,"<����>",80);//����<����>��ǩ��ͷ����ϵ���е����� ��Ӧ��Ԫ

      Find_YUAN_Contacts_Label_Activation_YUAN(tmp,"<���>",80);//����<���>��ǩ��ͷ����ϵ���е����� ��Ӧ��Ԫ

     Find_YUAN_Contacts_Label_Activation_YUAN(tmp,"<����>",70);//����<����>��ǩ��ͷ����ϵ���е����� ��Ӧ��Ԫ
      tmp->state=1;

	}




 //ѧϰ����
    if(tmp->state==1) 
       { 
        if(Run_Learn==1)
          {
           tmp->Learn_Ready_Time--;
           if(tmp->Learn_Ready_Time<=0)
             {
              tmp->Learn_Ready_Time=Learn_Ready_Time_MAX;
              tmp->Learning(); //ѧϰ����
           

             }

         }
 
       }  




     //ƣ��ֵ�仯

     if(tmp->state==1)
       {
         float fag_x = (float)(fag_add/20 *tmp->Layer );  //ƣ�����Ӹ��ݲ㼶Խ��Խ��
         tmp->fag += fag_x + tmp->E/10000;
 
       }

     else if(tmp->state==0)
       {
         tmp->fag -= fag_minus;
         if(tmp->fag <= 0) tmp->fag=0;

       }

 



     if(tmp->E_X!=0)  //��Ծǿ������ֵ�仯
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
	 YuanSum++;//ͳ��Ԫ����
     YuanContactsSum += tmp->Contacts->Get_Sum();//ͳ����ϵ�����
	}


    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND


YUAN_SUM=YuanSum;
YUAN_CONTACTS_SUM=YuanContactsSum;
//delete tmp;
// delete linker_tmp;
//delete tmpY;
}











void CAiQiDlg::Draw_Face(int x, int y,int Kind,CDC *pDC) //������
{

  int dx;

  CBitmap bitmap;   //����ͼλ����
  bitmap.LoadBitmap(IDB_AiQiDlg_Pic_Face);  //����ͼλ���� ID

  CDC dcMemory;  //����CDC����
  dcMemory.CreateCompatibleDC(pDC);  //������pDC���ݵ��ڴ��豸����
  dcMemory.SelectObject(&bitmap);  //��ͼλѡ���ڴ��豸������

  if(Kind>=0 && Kind<=10) dx=Kind*188;
  else dx=0;


   pDC->BitBlt(x,y,188,188,&dcMemory,dx,0,SRCCOPY);  //���ڴ��豸�������Ƶ���ǰ�豸������




}





void CAiQiDlg::Change_Face(int x, int y,CDC *pDC) //�����
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

 Draw_Face(x, y,Kind,pDC); //������


}

void CAiQiDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

   OnEnter();




}




















































void CAiQiDlg::Inhibitory_Layer_YUAN(int Layer) //����ĳ�������Ԫ
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






CString CAiQiDlg::String_mc_format(CString text) //����[]���������������ʸ�ʽ�� �ִʺ�����
{
 int i=0,zz=0;
 CString tt,tmpch;

 int end=0;

 if(text.IsEmpty()==1)  return text;  //����ַ����Ƿ�Ϊ��


 //text.Replace( " ��", "[" );
 //text.Replace( " ��", "]" ); 


   while(1)   // ���[]�Ƿ�Գ�
  {
   if(text[i]=='\0') //����ĩβ  
          {
           break; //�����ر�
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

   while(1)   // ���[]�Ƿ�Գ�
  {
   if(text[i]=='\0') //����ĩβ  
          {
           break; //�����ر�
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










CString CAiQiDlg::ZWFC(CString text)   //���ķִ�
{
  
  CString TT=text;

  TT.Replace( "��", "?" ); //��ֹ ���ģ����ɿ� bug



     //��ֹ �ִʳ����������� bug
     if(TT=="!"){ TT="-.-";}
     if(TT=="\"") {TT="-.-"; }
     if(TT=="'") {TT="-.-"; }
     if(TT=="��") {TT="-.-"; }
     if(TT==".") {TT="-.-"; }
     if(TT=="��") {TT="-.-"; }
	 if(TT==",") {TT="-.-"; }





  string fs=TT.GetBuffer(0);

  fs = D.SegmentWord(fs); //���ַ����������ķִ�

  TT = fs.c_str();  

  TT=String_mc_format(TT); //����[]���������������ʸ�ʽ�� �ִʺ�����

 return TT;
}






void CAiQiDlg::Format_String(CString *_text) //��ʽ���ַ��� ȥ���ո� �� *
{
 

 int i=0;
 CString tt,tmpch;

 CString text=*_text;

 int end=0;

 if(text.IsEmpty()==1)  return;  //����ַ����Ƿ�Ϊ��
 text.TrimLeft(); //ȥ����ߵĿո�
 text.TrimRight(); //ȥ���ұߵĿո�



   while(1)  //�滻* �߿ո�
  {

   if(text[i]=='\0') //����ĩβ  
          {
           break; //�����ر�
          } 


     if(text[i]=='*') { text.SetAt(i,' '); }

    i++;

  }




   i=0;


tt.Empty();




 while(1)

 {


   while(1)  //����ǰ��Ŀո� 
  {
   if(text[i]=='\0') //����ĩβ  
          {
           end=1;break; //�����ر�
          } 

       if(text[i]==' ') {     i++; continue; }

  else {break;}

  }


  if(end==1) break;




  tmpch.Empty();

  for(;;)  //��ȡ�пո������ 
  {

   // tmpch.Format("%c",text[i]);

    tmpch+=text[i];

    i++;

    if(text[i]==' '  || text[i]=='\0') //�������� ���߽�����
      {

  

    	if(text[i]=='\0') //����ĩβ
		{
           tmpch+='\0';
           end=1;; //�����ر�
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















int CAiQiDlg::Return_String_Words_Sum(CString text) //�����ַ����е��ʵ�����
{
 
 int sum=0;
 int i=0;
 CString tt,tmpch;

 int end=0;

 if(text.IsEmpty()==1)  return 0;  //����ַ����Ƿ�Ϊ��



   while(1)  //����ǰ��Ŀո� �� *
  {
   if(text[i]=='\0') //����ĩβ  
          {
           end=1;break; //�����ر�
          } 

       if(text[i]==' ') {     i++; continue; }
  else if(text[i]=='*') {     i++; continue;  }
  else {break;}

  }






 while(1)

 {


   while(1)  //����ǰ��Ŀո� �� *
  {
   if(text[i]=='\0') //����ĩβ  
          {
           end=1;break; //�����ر�
          } 

       if(text[i]==' ') {     i++; continue; }
  else if(text[i]=='*') {     i++; continue;  }
  else {break;}

  }


  if(end==1) break;

  tt.Empty();

  for(;;)  //��ȡ�пո������ 
  {


    i++;

    if(text[i]==' ' || text[i]=='\0') //�������� ���߽�����
      {
               

	if(text[i]=='\0') //����ĩβ
	  {

           end=1;; //�����ر�

				   
	   }


        break;

      }



   }//for


 

 sum++;

     



 }



 return sum;

}














void CAiQiDlg::Return_String_SN_start_end(CString text,int SN,int *SN_start,int *SN_end) //�����ַ����� ��SN������ ƫ�Ƶĵ�ַ ��ʼ ����
{
 
 int sum=0;
 int i=0;
 
 int n_start=-1,n_end=-1;



 int end=0;

 if(text.IsEmpty()==1)  end=1;  //����ַ����Ƿ�Ϊ��



   while(1)  //����ǰ��Ŀո� �� *
  {
   if(text[i]=='\0') //����ĩβ  
          {
           end=1;break; //�����ر�
          } 

       if(text[i]==' ') {     i++; continue; }
 
  else {break;}

  }


 int iii=Return_String_Words_Sum(text); //�����ַ����е��ʵ�����
 if(iii==0) end=1;
 if(iii<SN) end=1;

 while(1)

 {


   while(1)  //����ǰ��Ŀո� �� *
  {
   if(text[i]=='\0') //����ĩβ  
          {
           end=1;break; //�����ر�
          } 

       if(text[i]==' ') {     i++; continue; }

  else {break;}

  }


  if(end==1) break;

  if(SN-sum==1) n_start=i;



  for(;;)  //��ȡ�пո������ 
  {


    i++;

    if(text[i]==' ' || text[i]=='\0') //�������� ���߽�����
      {
               

	if(text[i]=='\0') //����ĩβ
	  {

           end=1; //�����ر�

				   
	   }


	if(SN-sum==1)
	  {

            n_end=i-1; 

           end=1; //�����ر�

				   
	   }


        break;

      }



   }//for


 

 sum++;

     



 }



 *SN_start=n_start;
 *SN_end=n_end;

}














CString CAiQiDlg::Return_String_N_Word(CString text,int i) //�����ַ�����N������
{

 int t_start,t_end;
 CString get_text;

 int SUM=Return_String_Words_Sum(text); //�����ַ����е��ʵ�����

  get_text.Empty();

 if(SUM<i) return get_text;







   Return_String_SN_start_end(text,i,&t_start,&t_end); //�����ַ����� ��SN������ ƫ�Ƶĵ�ַ ��ʼ ����


   get_text = text.Mid(t_start, t_end-t_start+1);



 return get_text; 
}







CString CAiQiDlg::Format_De_CString(CString text) //��ʽ�������ġ��ֵ��ַ���������ȥ�����ġ�
{
 CString D_text;
 CString Word;
 CString QM_Word;



 int i;

 int SUM=Return_String_Words_Sum(text); //�����ַ����е��ʵ�����

  for(i=1; i<=SUM ; i++)
  {
     Word=Return_String_N_Word(text,i); //�����ַ�����N������

     if(Word=="��")
       {
         if(SUM>1 && i!=SUM)//���ǵ�һ���� �������һ��
           {

             if( IS_DC(Return_String_N_Word(text,i+1)) ) //��һ�������Ƕ���
               {
                QM_Word=Return_String_N_Word(text,i-1);//�õ�ǰһ������
                D_text.Replace( QM_Word+" ",  QM_Word ); //�滻ǰ����ո�ĵ���
				D_text+="�� ";
                continue;
               }


            QM_Word=Return_String_N_Word(text,i-1);//�õ�ǰһ������
            D_text.Replace( QM_Word+" ",  QM_Word ); //�滻ǰ����ո�ĵ���


            Word=Return_String_N_Word(text,i+1); //�õ���һ������
            D_text+=Word;
            D_text+=" ";  //���
            i+=1;
            continue;
           }

         if(i==SUM)//�����һ��
           continue;


       }


    D_text+=Word;
    D_text+=" ";
     
  }

 return D_text;

}







CString CAiQiDlg::Format_XRC_De_CString(CString text) //��ʽ���ַ��������ݴʵġ��ġ���ȥ�����ġ�
{
 CString D_text;
 CString Word;
 CString QM_Word;



 int i;

 int SUM=Return_String_Words_Sum(text); //�����ַ����е��ʵ�����

  for(i=1; i<=SUM ; i++)
  {
     Word=Return_String_N_Word(text,i); //�����ַ�����N������

     if(Word=="��")
       {
         if(SUM>1 && i!=SUM)//���ǵ�һ���� �������һ��
           {

             if( IS_XRC(Return_String_N_Word(text,i-1)) ) //ǰһ�����������ݴ�
               {

                continue;
               }


           }


         if(i==SUM)//�����һ��
           continue;


       }


    D_text+=Word;
    D_text+=" ";
     
  }

 return D_text;

}








//�û��ش�  �õ���ѡ��ģ����ʣ�Ԫ �� �û��Ļش�Ĵ���֮�佨����ϵ
void CAiQiDlg::User_Answer_YUAN_Is( YUAN_UNIT *S_YUAN, CString text)
{
 CString tt;

 if(S_YUAN == NULL) return;



 //////////�жϵ���ѡ��ģ����ʣ�Ԫ�Ĳ㼶
 if(S_YUAN->Layer == 0)  //////////�ַ���
   {
    tt.Format("%s �� %s",S_YUAN->name,text);

    //��ʽ����  �����ǡ����ַ���   ͨ�����������1��Ԫ  ��ϵ�ַ����ַ� ��������X��Y�ĸ�� ���磺 Բ�� ��� ��� �� ƻ��
    Form_Is_4(tt) ;
   }


 else if(S_YUAN->Layer == 1)  //////////�����
  {


   YUAN_UNIT *new_YUAN_Y = NULL;

   int b=0;


   ///����YԪ Ŀ�꣨���ţ�Ԫ

   b=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ

    if(b==-1) //û�� 
	{
	 //������Ԫ
     YUAN->New();
	 new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,600),Xrand(10,360));
     YUAN->Set_name(new_YUAN_Y->ID,text);

     YUAN->Set_threshold(new_YUAN_Y->ID,new_YUAN_Y->threshold + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;
	}

    else //��
	{

	 new_YUAN_Y=YUAN->ID_return_P(b);
	}



    //��������

    if(YUAN->Find_linker(S_YUAN->ID,new_YUAN_Y->ID)==0) //ԭ����Ŀ��Ԫû������
      {
          float fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10
          YUAN->Link(S_YUAN->ID,new_YUAN_Y->ID,60+fdz);  //����Ԫ

      }


   





  }






}







void CAiQiDlg::Activation_YUAN(CString text,int power) //����ĳ��Ԫ
{
 int b;
 YUAN_UNIT *tmp;


   //�����ַ���tt ����  
    b=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ

     //���û��
     if(b==-1) 
       {
         ;
       }

     //�������

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


        YUAN->Add_E_X(b,(float)power);//���ӱ��ǿ��ЧӦ

       }




}




void CAiQiDlg::Inhibit_YUAN(CString text,int power) //����ĳ��Ԫ
{
 int b;
 YUAN_UNIT *tmp;


   //�����ַ���tt ����  
    b=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ

     //���û��
     if(b==-1) 
       {
         ;
       }

     //�������

       else
       {
         tmp=YUAN->ID_return_P(b);

         if(tmp->state==1)
           {

           }
         else if(tmp->state==0)
		{
         
		}


        YUAN->Add_E_X(b,((float) -power));//���ӱ��ǿ��ЧӦ



       }




}









void CAiQiDlg::Activation_Text_YUAN(CString text) //�����ַ����������Ԫ
{

 int i;


 int t_start,t_end;
 CString get_text;

 int YUAN_SUM = Return_String_Words_Sum(text); //�����ַ����е��ʵ�����






       if(YUAN_SUM == 0) goto Activation_Text_YUAN_END;
 

 
 for(i=1;i <= YUAN_SUM ; i++)
 {
   


   get_text.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //�����ַ����� ��SN������ ƫ�Ƶĵ�ַ ��ʼ ����

   //get_text = input_text.Mid(t_start, t_end-t_start+1);
   get_text = text.Mid(t_start, t_end-t_start+1);

   Activation_YUAN(get_text,20); //����ĳ��Ԫ ״̬��2












 }







 Activation_Text_YUAN_END:;


}












void CAiQiDlg::Recognition_Command(int *Command_Flag,CString *input_text)  //ʶ���������
{
  CString text_DC;
  CString LL,RR;
 CString text=*input_text;







 if(text.Find("@ �鿴 ����") !=-1 )
  {




   text.Replace( "@ �鿴 ����", NULL );

   *input_text=text;
   *Command_Flag=30;




   return;

  }



 if(text.Find("@ ɾ�� ���� ����") !=-1 )
  {




   text.Replace( "@ ɾ�� ���� ����", NULL );
   text.Replace( "��", "(" );
   text.Replace( "��", ")" );

   *input_text=text;
   *Command_Flag=32;




   return;

  }

 if(text.Find("@ ɾ�� ����") !=-1 )
  {




   text.Replace( "@ ɾ�� ����", NULL );

   *input_text=text;
   *Command_Flag=31;




   return;

  }





 if(text.Find("@ �ִ�") !=-1 )
  {




   text.Replace( "@ �ִ�", NULL );

   *input_text=text;
   *Command_Flag=36;




   return;

  }


 if(text.Find("@ ���� ѧϰ") !=-1 )
  {




   text.Replace( "@ ���� ѧϰ", NULL );

   *input_text=text;
   *Command_Flag=35;




   return;

  }


 if(text.Find("����") !=-1 )
  {

   CString text0=text;

   text.Replace( "����", NULL );


   int Words_Sum= Return_String_Words_Sum(text); //�����ַ����е��ʵ�����
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




 if(text.Find("@ ����") !=-1 )
  {




   text.Replace( "@ ����", NULL );

   *input_text=text;
   *Command_Flag=37;




   return;

  }


 if(text.Find("@ ��ҳ") !=-1 )
  {




   text.Replace( "@ ��ҳ", NULL );

   *input_text=text;
   *Command_Flag=50;




   return;

  }



 if(text.Find("���") !=-1 && text.Find("��ô") !=-1)
  {


   *input_text=text;
   *Command_Flag=3;

   return;

  }


 if(text.Find("�Ͼ�") !=-1 && text.Find("�¾�") !=-1)
  {



   *input_text=text;
   *Command_Flag=7;

   return;

  }




 //ȥ��������
   text.Replace( "��", " " );
   text.Replace( ",", " " );
   text.Replace( "��", " " );
   text.Replace( ".", " " );


   text.Replace( "�� ", "AiQi " );
   text.Replace( "�� ", "���� " );

   text.Replace( "˭ ", "ʲô " );





//��ֹ���ǿո� �ո���ճ���
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




 if(text.Find("@ ����") !=-1 )
  {

   text.Replace( "@ ����", NULL );

   *input_text=text;
   *Command_Flag=40;

   return;

  }


 if(text.Find("@ ��ʽ�� ��") !=-1 )
  {

   text.Replace( "@ ��ʽ�� ��", NULL );

   *input_text=text;
   *Command_Flag=45;

   return;

  }






 if(text.Find("��ס ") !=-1 )
  {

   text.Replace( "��ס ", NULL );

   *input_text=text;
   *Command_Flag=2;


   return;

  }







 if(text.Find("����") !=-1 )
  {



   text.Replace( "����", "��" );



   *input_text=text;
   *Command_Flag=3;

   return;

  }






 //�߼����ʴ���
 if(text.Find("?") !=-1||text.Find("��") !=-1||text.Find("�ǲ���")!=-1 )
  {


   text.Replace( "?", NULL );
   text.Replace( "��", NULL );
   text.Replace( "��", NULL );


   if(text.Find("�ǲ���")!=-1)
   {
    text.Replace( "�ǲ���", "XDongCi" );

    Split_X_String(text,"XDongCi",&LL,&RR); //���ַ�����XΪ�ָ���2���ַ���


    if(!Find_Text_DC(RR, &text_DC)) //����û�ж�����
	{
    text.Replace( "XDongCi",  "��" );

	}
	else
	{
     text.Replace( "XDongCi", NULL );//�����ж���

	}

   }

    text.Replace( "��",  "�� " );



 int Words_Sum= Return_String_Words_Sum(text); //�����ַ����е��ʵ�����

				if(Words_Sum==0) //��������Ϊ0  ��ֹ�����ɿ�
				{
					
                     text="?";  

					 *input_text=text;
					 *Command_Flag=1;
                     return;
				}

				else if(Words_Sum==1) //��������Ϊ1
				{
					
                   if(Return_String_N_Word(text,1)=="��") //���� �Ĵ���
				   {

					 *input_text=text;
					 *Command_Flag=1;
                     return;
				   }

				}




   *input_text=text;
   *Command_Flag=10;

   if(text.Find("ʲô") !=-1)
   *Command_Flag=11;

   return;

  }


 //�߼����ʴ��� ʲô
 if(text.Find("ʲô") !=-1 )
  {

    text.Replace( "��",  "�� " );

    if(!Find_Text_DC(text, &text_DC)) //����û�ж�����
	{
    text.Replace( "ʲô",  NULL );

      int Words_Sum= Return_String_Words_Sum(text); //�����ַ����е��ʵ�����

				if(Words_Sum==0) //��������Ϊ0
				{
					

                     text="?";
				}



       *input_text=text;
	   *Command_Flag=1;
      return;
	}


	else //�ж���
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







//�ҵ�RichEdit�ؼ����
void CAiQiDlg::MyRichEdit_TextOut(CRichEditCtrl *PMyRichEdit,unsigned long color,int size,int bold,CString str)
{

//��������
CHARFORMAT cf;
ZeroMemory(&cf, sizeof(CHARFORMAT));
cf.cbSize = sizeof(CHARFORMAT);

cf.dwMask|=CFM_BOLD;
if(bold==0)
cf.dwEffects&=~CFE_BOLD;//���ô��壬��cf.dwEffects|=CFE_BOLD;
else
cf.dwEffects|=CFE_BOLD;

cf.dwEffects&=~CFE_BOLD; //��ͨ

cf.dwMask|=CFM_ITALIC;
cf.dwEffects&=~CFE_ITALIC;//����б�壬��cf.dwEffects|=CFE_ITALIC;
cf.dwMask|=CFM_UNDERLINE;
cf.dwEffects&=~CFE_UNDERLINE;//����б�壬��cf.dwEffects|=CFE_UNDERLINE;
cf.dwMask|=CFM_COLOR;
cf.crTextColor = color;//������ɫ
cf.dwMask|=CFM_SIZE;
cf.yHeight =size;//���ø߶�
cf.dwMask|=CFM_FACE;
strcpy_s(cf.szFaceName ,_T("΢���ź�"));//��������
//strcpy_s(cf.szFaceName ,_T("����"));//��������
//strcpy_s(cf.szFaceName ,_T("Fixedsys"));//��������
PMyRichEdit->SetSelectionCharFormat(cf); 



PMyRichEdit->SetSel(-1, -1);
PMyRichEdit->ReplaceSel( (LPCTSTR)str ); 


}



void CAiQiDlg::TEXT_OUT_BOX_SAY_3(CString text,int flag) //��������Ļ�����  ʹ��RichEdit�ؼ�
{
  CString SYS_text;
  CString AI_text;
  CString Ren_text;

  CString _MainTextOut;

  CTime time = CTime::GetCurrentTime();
  CString TTime = time.Format("%H:%M:%S");



  SYS_text.Format(">ϵͳ�� ");
  AI_text.Format(">AiQi�� ");
  Ren_text.Format(">���ˣ� ");



  unsigned long Tcolor;

         if(flag==0) {  _MainTextOut = SYS_text;  MyRichEdit_TextOut(&MyRichEdit,RGB(255,0,224),260,0, _MainTextOut);  Tcolor=RGB(50,50,50);}
    else if(flag==1) {  _MainTextOut = AI_text;  MyRichEdit_TextOut(&MyRichEdit,RGB(0,0,255),260,0, _MainTextOut);  Tcolor=RGB(2,153,123);}
    else if(flag==2) {  _MainTextOut = Ren_text;  MyRichEdit_TextOut(&MyRichEdit,RGB(0,0,255),260,0, _MainTextOut);  Tcolor=RGB(0,0,0);}
    else  {  _MainTextOut = " ";  }

MyRichEdit_TextOut(&MyRichEdit,RGB(179,179,179),260,0, TTime);

  _MainTextOut = "\r\n"; //����
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,0, _MainTextOut);

  _MainTextOut = " ";
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,0, _MainTextOut);

  _MainTextOut =text;
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,1, _MainTextOut);



  _MainTextOut = "\r\n"; //����
  MyRichEdit_TextOut(&MyRichEdit,Tcolor,260,0, _MainTextOut);






   MyRichEdit.SetSel(-1, -1); // ��RichEdit�ؼ���������
   MyRichEdit.ReplaceSel( (LPCTSTR) _MainTextOut ); 





    MyRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM,0);  //��ת�����һ��


}




void CAiQiDlg::OnEnter() //���˻س�������Ӧ
{

UpdateData();
if( input_text=="") return;


 

 CString tt;
 CString LL,RR;
 CString text_DC;

       UpdateData(); //����������Ϣ


               if(Waiting_For_Assessment_Flag==1)//�ȴ��û����� ������������
                 { 

				   Waiting_For_Assessment_Time=Waiting_For_Assessment_MAX_Time;
				  
                   if(input_text=="��"||input_text=="�ǵ�"||input_text=="��"||input_text=="yes")
				   {

                     Waiting_For_Assessment_Flag=0;

                   // UpdateData();

                    TEXT_OUT_BOX_SAY_3(input_text,2); //��������Ļ�����


                    input_text.Empty(); //	�������
                    
                   UpdateData(0);
				    // m_edit.LineScroll(m_edit.GetLineCount()); //������������Ƶ�������

				    Waiting_For_Assessment_Flag=0;

					AI_Happy_Flag=1;
 

					CString ttt;
 


                    Return_Award_To_AI_X(P_layer_0_max_E_YUAN_AI_Think_Choose,AI_Think_Choose_Contacts_Number);  //����AI  ����ǿѡ��Ԫ�Ŀ϶�

				    return   ;

				   }


                   if(input_text=="��"||input_text=="����"||input_text=="��"||input_text=="��"||input_text=="no")
				   {
                       Waiting_For_Assessment_Flag=0;
                   // UpdateData();

                    TEXT_OUT_BOX_SAY_3(input_text,2); //��������Ļ�����

                    input_text.Empty(); //	�������
                    
                      UpdateData(0);
					  //m_edit.LineScroll(m_edit.GetLineCount()); //������������Ƶ�������

				    Waiting_For_Assessment_Flag=0;

					AI_Sad_Flag=1;


					Return_Punishment_To_AI_X(P_layer_0_max_E_YUAN_AI_Think_Choose,AI_Think_Choose_Contacts_Number);  //�ͷ�AI  ����ǿѡ��Ԫ�ķ�
                    

				    return  ;

				   }

                 }




         if(Flow_run==0) //��û������
		 {
           UpdateData();

            Enter=1;

           //��ʾ�û����������
			TEXT_OUT_BOX_SAY_3(input_text,2); //��������Ļ����� 






//========================
//���ķִ�
if(Run_FC_Flag==1)
{


   input_text = ZWFC(input_text);//���ķִ�




   //input_text=Format_De_CString(input_text); //��ʽ�������ġ��ֵ��ַ���������ȥ�����ġ�

   input_text=Format_XRC_De_CString(input_text);  //��ʽ���ַ��������ݴʵġ��ġ���ȥ�����ġ�

  FC_text = input_text;
}
//========================

int jxs=0;

CString xt=input_text;
xt.Replace(" ", NULL );
if(xt=="����" || xt=="����˵" || xt=="Ȼ����" || xt=="������" )
{
 if(TextInputBox[0].text.IsEmpty()!=1)
   {
    input_text=TextInputBox[0].text;
   }
 else
   {
    input_text="?";

   }

 jxs=1; //�жϼ���˵
}


//---------------------------



//�Ƚ������ǰ3������Ƿ���ͬ



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

        int KeNeng=Xrand(0,100); //���ɿ�����

        if(KeNeng>=0 && KeNeng<=40)
          {
           TEXT_OUT_BOX_SAY_3("���ˣ����������İ�",1); //��������Ļ�����
          }
        else if(KeNeng>40 && KeNeng<=70)
          {

           TEXT_OUT_BOX_SAY_3("���ˣ����Ǹ��������ĵ��İ�",1); //��������Ļ�����
          }
        else
          {

           TEXT_OUT_BOX_SAY_3("���ˣ���ô������䰡���ʵ��İ�",1); //��������Ļ�����
          }

       }

//---------------------------




      //-------------------�ж��������

          Command_Flag=1; //Ĭ���趨����ͨ����


		  CString input_text_X=input_text; //��������������


          Recognition_Command(&Command_Flag,&input_text_X);  //ʶ��������� ���Ұ�������Ϣ���������ͨ��



            if(input_text_X=="") 
              {
                TEXT_OUT_BOX_SAY_3("�޷�������������ȷ���ݡ�",1); //��������Ļ�����

				 input_text.Empty(); //	�������

		         UpdateData(0);

                return;  
              }


     //-------------------



			if(User_Answer_Flag==1 && User_Answer_Time>0)  //���ʿ�����ķ��� �û��ش���Чʱ��
			{

			  //�жϵ�ǰ�������ʵ����� 
			  if(AI_Question_Kind==1) //1��Ԫ�洢���ַ�������
			  {
			   Command_Flag=5;
			  }


			  else if(AI_Question_Kind==2) //2�����û�������ַ�������
			  {
 			  Command_Flag=6;
			  }



			}
 


/*
CString DD;  // Command_Flag ����׷��
DD.Format("Command_Flag=%d\n����=[%s]",Command_Flag,input_text_X);
AfxMessageBox(DD);
*/


      //-------------------�������ʹ���

	    	if(Command_Flag==1)  //��ͨ ����
			{





			 Think_flag=1; 


              Inhibitory_Layer_YUAN(0); //����0�������Ԫ
			   Inhibitory_Layer_YUAN(1); //����1�������Ԫ
			    Inhibitory_Layer_YUAN(2); //����2�������Ԫ
 






              Input_Activation_YUAN(input_text_X);  //ͨ��������ַ��� ����Ԫ ģ��ƥ���
 

			  CString D_YUAN_NAME;
			  D_YUAN_NAME=input_text_X;
              D_YUAN_NAME.Replace( " ", NULL );
			  Activation_YUAN(D_YUAN_NAME,50); //�����ض�Ԫ

			  Input_Activation_YUAN_By_Contacts_2(input_text_X);  //ͨ����������ַ�����Ԫ��ϵ��Ƚϣ�������Ԫ��Ծ�� �Ƚ�<��><����>��ǩ
             
			}

         //-----------------
	    	else if(Command_Flag==2)  //��ס�� ����֪ʶ 
			{

  
		



CString DC; //ν�ﶯ��

input_text_X.Replace( "��", "�� " ); //���� ���������Ĵʣ��ѡ������ֲ�

  //�����ı��еĵ�һ�����ʣ����ҷ�����
  if(Find_Text_DC(input_text_X, &DC)) 
    {

     //AfxMessageBox("�ж���");


             if(Return_String_Words_Sum(input_text_X)==1) //�����ַ����е��ʵ�����
			 {
              int r=Form_Remember_X(input_text_X); //��ʽ����  �����ַ��� ����һ������ 


              if(r==1)  //1��������

                {


			      TEXT_OUT_BOX_SAY_3("�õģ���ס�ˡ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				  goto Command_Flag_2_END;

				 }
			 }


             if(Recognition_SXBQ_Form(input_text_X)==1 ) //�Ǵ���ǩ����Ľ�������ʽ------

               {

                  //AfxMessageBox("���Ǵ���ǩ��䣬���������ʽ");



                 //��ǩ����Ľ�������
                 Form_Create_SXBQ_EX(input_text_X); //���н������ı�ǩ���佨������

          
                   goto Command_Flag_2_END;

               }



             if(Recognition_ZWB_Form(input_text_X)==1 ) //����ν������ʽ------

               {

                  //AfxMessageBox("������ν����䣬��������");

                 //[��ʽ����] ��������  ��ʽ�� ��ס SνP  �� ��ס S
                 Form_Create_ZWB_EX(input_text_X); //���н����������⽨������

               
                 goto Command_Flag_2_END;

               }







    }

  else   //���û�ж���
   {


     //AfxMessageBox("�޶���");

     int r=Form_Remember_X(input_text_X); //��ʽ����  �����ַ��� ����һ������ 


              if(r==1)  //1��������

                {


			      TEXT_OUT_BOX_SAY_3("�õģ���ס�ˡ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				 }


  }




   Command_Flag_2_END:;










			}





        //-----------------  




	    	else if(Command_Flag==3)  //��ʽ�������x��ôY  ���������������֮������������ϵ������X���Y
			{
            



              if(Form_IF_X_THEN_Y(input_text_X)==1)
                {
                  CString XT;
                  XT.Format("�õģ��Ҽ����ˡ�%s",input_text_X);
                  TEXT_OUT_BOX_SAY_3(XT,1); //��������Ļ�����
 			      AI_YES_Flag=1;
                }
 
              else
                {
                 TEXT_OUT_BOX_SAY_3("�﷨�������������﷨���룺���X��ôY��X��Y�Ǿ���",1); //��������Ļ�����

                }




			}

/*

          //-----------------

	    	else if(Command_Flag==4)  //����
			{

              


                Split_X_String(input_text_X,"��",&LL,&RR); 

                int pf=Assess_To_Two_String(LL,RR); //�������ַ������ƶȴ��

                CString XT;
                XT.Format("�����ַ�������Ϊ%d",pf);
                TEXT_OUT_BOX_SAY_3(XT,0); //��������Ļ�����
			 



             
			}

*/

        //-----------------  
	    	else if(Command_Flag==7)  ////��ʽ�������¾��ϵ������X���Y
			{
            



              if(Form_ShangXiaWen(input_text_X)==1) //��ʽ�������¾��ϵ������X���Y
                {
 
                  TEXT_OUT_BOX_SAY_3("�õģ����¾��Ѿ���ס��",1); //��������Ļ�����
 			      AI_YES_Flag=1;
                }
 
              else
                {
                 TEXT_OUT_BOX_SAY_3("�﷨�������������﷨���룺�Ͼ�X�¾�Y��X��Y�Ǿ���",1); //��������Ļ�����

                }




			}
          //-----------------



          //-----------------
/*
	    	else if(Command_Flag==8)  //ʶ����ν������ʽ
			{

              


 
                CString XT;
                XT.Format("��ν������ʽ");
                TEXT_OUT_BOX_SAY_3(XT,0); //��������Ļ�����

 



              int r=Form_Create_ZWB(input_text_X); //[��ʽ����] ��������  ��ʽ�� ��ס SνP  �� ��ס S


              if(r==1)  //1��������

                {


			      TEXT_OUT_BOX_SAY_3("Ŷ����ס�ˡ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				 }

              else if(r==2)  //2��ǰ�й�ϵǿ��

                {


			      TEXT_OUT_BOX_SAY_3("�����Ҿ���Ҳ�������ġ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				 }

			  else

			     {
                  TEXT_OUT_BOX_SAY_3("�﷨����",1); //��������Ļ�����

			     }


			




			 



             
			}
          //-----------------

*/





	    	else if(Command_Flag==30)  //�鿴���� �鿴@������
			{


                          //�����ʾԪ������
                          Cmd_Display_YUAN_Data( input_text_X );




             
			}



          //-----------------

	    	else if(Command_Flag==31)  //ɾ���������� @ɾ������ ������
			{


                          //���ɾ��Ԫ
                          Cmd_Del_YUAN( input_text_X );




             
			}




          //-----------------

	    	else if(Command_Flag==32)  //ɾ�������������� @ɾ���������� ������(����ID)
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

                                   //TT.Format("������=%s ����%d",NAME,X_ID);
                                   //TEXT_OUT_BOX_SAY_3(TT,0); //��������Ļ�����

									 //���ɾ��Ԫ����
                                     Cmd_Del_YUAN_Contacts(NAME,X_ID);


                                  }
                                else
                                  {
                                   TT.Format("���󣬸���������Ϊ�գ�");
                                   TEXT_OUT_BOX_SAY_3(TT,0); //��������Ļ�����
                                  }



                               }
                           else
                             {
                              TT.Format("���������ʽ����ȱ��()��");
                              TEXT_OUT_BOX_SAY_3(TT,0); //��������Ļ�����
                            }

             
			}



         //-----------------




	    	else if(Command_Flag==35)  //��������ѧϰ����
			{


                     CString CT=input_text_X;
					 CString TX;    

                     CT.Replace( " ", NULL );

                     int n = Learn_CiTiao_From_Web(CT); //��������ѧϰ������Ϣ

             

                         TX.Format("ѧϰ[%s]������ϣ���ѧϰ��%d��������",CT,n);
                         TEXT_OUT_BOX_SAY_3(TX,1); //��������Ļ�����
             
			}

          //-----------------



	    	else if(Command_Flag==36)  //�ִ����� �ִ�@���
			{


                          TEXT_OUT_BOX_SAY_3(input_text_X,0); //������ʾ����Ļ�� 
                          




             
			}
         //-----------------



	    	else if(Command_Flag==37)  //�������ϻ�ȡ������Ϣ
			{

                           CString x=input_text_X;
                           x.Replace( " ", NULL );

			               CString TX;    
                          CString TT;

                          CString city_number;


                            CString CityName=x;




                          

                            city_number=Get_City_Weather_Number(CityName);  //���س�����������

                            if(city_number=="û���ҵ�")
                              {
                               TT.Format("û����ص������������ݡ�");
                               TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                              }
                            else
                              {


                                //TT.Format("���д���=%s",city_number);
                                //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                               CString CT;
                               CT=Get_Weather_Information_From_Web(city_number); //�������ϻ�ȡ������Ϣ������

                                   TX= CityName + "  "+ CT +"C";  
      
                               TT.Format("%s",TX);
                               TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


                              }


             
			}

         //-----------------



	    	else if(Command_Flag==40)  //���� ����
			{

              Input_Activation_YUAN(input_text_X);  //���뼤��Ԫ

			 



             
			}


          //-----------------







	    	else if(Command_Flag==45)  //����  ��ʽ����
			{

                CString XT;
				CString TT;

                //TT=Format_De_CString(input_text_X); //��ʽ�������ġ��ֵ��ַ���������ȥ�����ġ�
                TT=Format_XRC_De_CString(input_text_X);  //��ʽ���ַ��������ݴʵġ��ġ���ȥ�����ġ�

                XT.Format("%s",TT);
                TEXT_OUT_BOX_SAY_3(XT,0); //��������Ļ�����

			 



             
			}


          //-----------------

	    	else if(Command_Flag==50)  //����
			{


              CString TWeb;
              CString TX;

			  TWeb="http://"+input_text_X;

			     TWeb.Replace( " ", NULL );

               ShellExecute(NULL, "open", TWeb , NULL, NULL, SW_SHOWNORMAL);

                         TX.Format("���ڰ�������վ��%s",TWeb);
                         TEXT_OUT_BOX_SAY_3(TX,1); //��������Ļ�����



             
			}
         //-----------------

	    	else if(Command_Flag==5)  //�û���Ԫ�洢���ַ������� �Ļش�
			{
             CString TT,TX;

             TT=input_text_X;

			 TT.Replace( " ", NULL );
             TT.Replace( P_User_Answer_objective_YUAN->name + "��", NULL );
			 TT.Replace( "��", NULL );

             Form_X_IS_Y( P_User_Answer_objective_YUAN->name, TT);  //[��ʽ����] ����X��Y��ϵ  �������������ĸ���





                         TX.Format("Ŷ���Ѽ��£�%s �� %s",P_User_Answer_objective_YUAN->name,TT);
                         TEXT_OUT_BOX_SAY_3(TX,1); //��������Ļ�����





			 P_User_Answer_objective_YUAN= NULL;

			 User_Answer_Flag=0;

             AI_Question_Kind=0; 





			 AI_YES_Flag=1;



			}

      //-------------------

	    	else if(Command_Flag==6)  //�û�����������ַ������� �Ļش�
			{
             CString TX;

                        

                         Form_X_QA( AI_Question_text, input_text_X );  //[��ʽ����] ����X���� ������ϵ  X��������һ���ı����������ش�

                         TX.Format("Ŷ��֪���ˣ�%s �ش��� %s",AI_Question_text, input_text_X);
                         TEXT_OUT_BOX_SAY_3(TX,1); //��������Ļ�����




			 User_Answer_Flag=0;

                         AI_Question_Kind=0; 


   


			 AI_YES_Flag=1;



			}

      //-------------------

	    	else if(Command_Flag==10)  //�߼����� ����ֵ ����"��" "?"
			{




			 Think_flag=1; 


			   Inhibitory_Layer_YUAN(0); //����0�������Ԫ
			   Inhibitory_Layer_YUAN(1); //����1�������Ԫ
			   Inhibitory_Layer_YUAN(2); //����2�������Ԫ

              if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
               Activation_YUAN(Last_Layer_0_Max_E_YUAN_Name,100); //�����ϴζԻ������һ�Σ���ǿ��ԾԪ



               //���� �ַ��������������޷���������Ԫ������������ļ��� 
               Find_Text_DC(input_text_X, &text_DC);//�����ı��еĵ�һ�����ʣ����ҷ�����

					   if(text_DC.IsEmpty()!=1)//=========�ж���
					   {

                         Split_X_String(input_text_X,text_DC,&LL,&RR); //���ַ�����XΪ�ָ���2���ַ���


 						  if(LL=="�� " || LL=="�� " ||LL=="�� "||LL=="�� ") //ȱʡ����£�������ȫ��һ�������
						   {
							   if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
                                   LL=Last_Layer_0_Max_E_YUAN_Name;
						   }

                          Input_Activation_YUAN(LL);  //ͨ��������ַ��� ����Ԫ

					   }

					   else
					   {

			            Input_Activation_YUAN(input_text_X);  //ͨ��������ַ��� ����Ԫ
					   }

			}

      //-------------------

	    	else if(Command_Flag==11)  //�߼����� �����  ����"ʲô"
			{
			 Think_flag=1; 


			   Inhibitory_Layer_YUAN(0); //����0�������Ԫ
			   Inhibitory_Layer_YUAN(1); //����1�������Ԫ
			   Inhibitory_Layer_YUAN(2); //����2�������Ԫ



              if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
               Activation_YUAN(Last_Layer_0_Max_E_YUAN_Name,100); //�����ϴζԻ������һ�Σ���ǿ��ԾԪ


                    CString text_DC;
                    CString LL;
                    CString RR;




					//�ж���=================================
                    if(Find_Text_DC(input_text_X, &text_DC))//�����ı��еĵ�һ�����ʣ����ҷ�����
					{


                       Split_X_String(input_text_X,text_DC,&LL,&RR); //���ַ�����XΪ�ָ���2���ַ���
                       RR=text_DC+RR;




                         //�ж�ʲô�ڶ���ǰ��=======
					   if(LL.Find("ʲô") !=-1 && RR.Find("ʲô") ==-1)
					   {

 

					   }

                         //�ж�ʲô�ڶ��ʺ���=======
					   if(LL.Find("ʲô") ==-1 && RR.Find("ʲô") !=-1)
					   {
   

						  if(LL=="�� " || LL=="�� " ||LL=="�� "||LL=="�� ") //ȱʡ����£�������ȫ��һ�������
						   {
							   if(Last_Layer_0_Max_E_YUAN_Name.IsEmpty()!=1)
                                   LL=Last_Layer_0_Max_E_YUAN_Name;
						   }


                           Input_Activation_YUAN(LL);  //ͨ��������ַ��� ����Ԫ

					   }


					}

                    //û�ж���==============================
					else
					{
                     Input_Activation_YUAN(input_text_X);  //ͨ��������ַ��� ����Ԫ

					}
					












			}

      //-------------------


//ShiBie_Commanf_Flag_END:;



           //������������
            Format_String(&input_text_X); //��ʽ���ַ���
			input_text_0 = input_text_X;

					input_text.Empty(); //	�������




		   UpdateData(0);



		 }





}





BOOL CAiQiDlg::PreTranslateMessage(MSG* pMsg)  //�Զ��������Ӧ���� ��д��
{
	// TODO: �ڴ����ר�ô����/����û���






 if(pMsg->message == WM_KEYDOWN)
  {
     
     AI_AUTO_Question_Ready_Time=AI_AUTO_Question_Ready_MAX_Time+10; //�Զ��������¼���

     if(AUTO_Learning_Flag==1)
	 {
	   AUTO_Learning_Flag=0; //�Զ�ѧϰֹͣ
	   TEXT_OUT_BOX_SAY_3("�Զ�ѧϰ��ֹͣ",0); //��������Ļ�����
	 }

     if(User_Answer_Flag==1)
        User_Answer_Time = User_Answer_MAX_Time;


     if(pMsg->wParam==27)  //����ESC
 
	   {

           OnClose();

	 }


     if(pMsg->wParam==VK_RETURN)  //���˻س���
 
	   {

         OnEnter();


         return   TRUE;   //Ϊ�˲��ûس��˳�����
	   }


  }




	return CDialog::PreTranslateMessage(pMsg);
}










void CAiQiDlg::AUTO_Question_2() //�Զ�����2  ��Ԫ�洢���ַ�������
{

 if( AI_AUTO_Question_Flag != 1) return;

 if( YUAN_SUM == 0) return;

 int n=0;
 n=Xrand(1,YUAN_SUM); //���ѡȡһ������


 P_AUTO_Question_select_YUAN = NULL;
 P_AUTO_Question_select_YUAN = YUAN->n_return_P(n);  //�õ����ѡ���Ԫ��ָ��




int nn=Xrand(1,100);

if(nn<=20)  //20%����ѡ�� ������Ԫ
  {
   if(P_AUTO_Question_select_YUAN->Layer==1){}
   else {P_AUTO_Question_select_YUAN = NULL; return;}
  }

else if(nn>20)  //80%����ѡ�� ���Ų��Ԫ
 {
   if(P_AUTO_Question_select_YUAN->Layer==0){}
   else {P_AUTO_Question_select_YUAN = NULL;return; }

 }






 CString TT;
 


 if(P_AUTO_Question_select_YUAN != NULL)  //�����Ԫ
   {


     if(P_AUTO_Question_select_YUAN->Layer==0)
       {

        TT.Format("%s��ʲô��",P_AUTO_Question_select_YUAN->name);
        TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


      }


     else if(P_AUTO_Question_select_YUAN->Layer==1)
       {

       // TT.Format("��%s�������һ��ĸ�����ʲô��",P_AUTO_Question_select_YUAN->Way);
        //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


      }






   }



}









void CAiQiDlg::MyDebug()
{


MyDebugX=User_Answer_Time;

//MyDebugX=1000;

}


















void CAiQiDlg::Split_X_String(CString S_CString,CString X_CString,CString *D_CString1,CString *D_CString2) //���ַ�����XΪ�ָ���2���ַ���
{
  CString L,R;

  int X_CString_length=X_CString.GetLength();//�ַ����ĳ���
  int S_CString_length=S_CString.GetLength();//�ַ����ĳ���

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






void CAiQiDlg::Split_X_String_Head(CString X_CString,CString *S_CString) //���ַ�����XΪͷ�ָ� ȡ���沿��
{
  CString tmp=*S_CString,R;

  int X_CString_length=X_CString.GetLength();//�ָ���ַ����ĳ���
  int S_CString_length=tmp.GetLength();//ԭ���ַ����ĳ���

  int X_weizhi=tmp.Find(X_CString); //�ָ�ʵ�λ��




  if(X_weizhi==-1) //û�ҵ��ָ�ʵ�λ��
    {

      return;
     }

  if(X_CString_length+X_weizhi==S_CString_length)
    {

      return; //�ָ�ʺ�������
     }


  







  R=tmp.Mid(X_weizhi+X_CString_length);


  *S_CString=R;

}







//ɾ���ַ�����N���ʣ����ҷ�����  �����ȷִ�
bool CAiQiDlg::Del_String_N_Word(CString *SX,int N)
{
 int i;

 CString text=*SX;
 CString t;

 int t_start,t_end;
 CString get_word;

  int WORD_SUM = Return_String_Words_Sum(text); //�����ַ����е��ʵ�����


   t.Empty();


  if( WORD_SUM == 0 ) {return 0;}
   if( WORD_SUM == 1 ) {return 0;}
   if( N > WORD_SUM ) {return 0;}
    if( N <= 0 ) {return 0;}

  for(i=1;i <=  WORD_SUM ; i++)
  {
   


   get_word.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //�����ַ����� ��SN������ ƫ�Ƶĵ�ַ ��ʼ ����


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














//��ʽ����  �����ǡ����ַ���   ͨ�����������1��Ԫ  ��ϵ�ַ����ַ� ��������X��Y�ĸ�� ���磺 Բ�� ��� ��� �� ƻ��
int CAiQiDlg::Form_Is_4(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;

 int L_Words_Sum=0,R_Words_Sum=0;





 int a=0,b=0,i=0;
float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX
 YUAN_UNIT *new_YUAN_Y=NULL; //����ԪY
 YUAN_UNIT *new_YUAN_G=NULL; //����ԪG
 YUAN_UNIT *new_YUAN_F=NULL; //����ԪF

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *

 //���ַ�����XΪ�ָ���2���ַ���
 Split_X_String(S_CString,"��",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }

 Format_String(&L); //��ʽ���ַ��� ȥ���ո� �� *
 Format_String(&R); //��ʽ���ַ��� ȥ���ո� �� *


 //�õ����ʸ���
L_Words_Sum= Return_String_Words_Sum(L); //�����ַ����е��ʵ�����
R_Words_Sum= Return_String_Words_Sum(R); //�����ַ����е��ʵ�����

////////����GԪ �м䣨���Ԫ

//ͨ��WAY�������Ƿ���� ��ֹ������ظ�����

  //new_YUAN_G=YUAN->Way_return_P(1,L);
new_YUAN_G=NULL;
  if(new_YUAN_G == NULL) //������
  {

     YUAN->New();
     new_YUAN_G=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_G->ID,Xrand(60,740),Xrand(200,380));
 

     YUAN->Set_threshold(new_YUAN_G->ID,60 * L_Words_Sum * 2/3 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     YUAN->Set_Layer(new_YUAN_G->ID,1); //����Ϊ��1

	 //YUAN->Set_Way(new_YUAN_G->ID,1,L); //����Ԫ�� �������

  }

  else //ԭ������
  {

  }


////////����FԪ �����������Ԫ

//ͨ��WAY�������Ƿ���� ��ֹ������ظ�����

  //new_YUAN_F=YUAN->Way_return_P(2,R);
new_YUAN_F= NULL;
  if(new_YUAN_F == NULL) //������
  {

     YUAN->New();
     new_YUAN_F=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_F->ID,Xrand(10,740),Xrand(10,100));
 

     YUAN->Set_threshold(new_YUAN_F->ID,new_YUAN_F->threshold + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     YUAN->Set_Layer(new_YUAN_F->ID,2); //����Ϊ��2

     //if(R.IsEmpty())
	 //YUAN->Set_Way(new_YUAN_F->ID,2,"û��"); //����Ԫ�� �������
    // else
    //     YUAN->Set_Way(new_YUAN_F->ID,2,R); //����Ԫ�� �������

  }

  else //ԭ������
  {

  }









        if(YUAN->Find_linker(new_YUAN_G->ID,new_YUAN_F->ID)==0) //ԭ����Ŀ��Ԫû������
		{
          fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10
          YUAN->Link(new_YUAN_G->ID,new_YUAN_F->ID,70+fdz);  //����Ԫ

		}

        else if(YUAN->Find_linker(new_YUAN_G->ID,new_YUAN_F->ID)==1)//ԭ��������
        {
          fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10
          YUAN->Set_linker_weight_ADD(new_YUAN_G->ID,new_YUAN_F->ID,10);  //��������ǿ����ֵ���ֵ
        }









////////����XԪ ���������ţ�Ԫ

i=0;
tt.Empty();
tmpch.Empty();
int end=0;

 while(1) 
 {
  if(end==1) break;


tt.Empty();
tmpch.Empty();

  for(;;)  //��ȡ����ǰ������
  {
 
   tmpch.Format("%c",L[i]);
   tt+=tmpch;
   i++;



    if(L[i]==' ' || L[i]=='\0') //�������� ,
    {

     a=YUAN->Find_name_return_ID(tt); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(60,740),Xrand(420,600));
     YUAN->Set_name(new_YUAN_X->ID,tt);

     YUAN->Set_threshold(new_YUAN_X->ID,new_YUAN_X->threshold + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;



	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

	 }


////��������





        if(YUAN->Find_linker(new_YUAN_X->ID,new_YUAN_G->ID)==0) //ԭ����Ŀ��Ԫû������
		{




          fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10

        
          YUAN->Link(new_YUAN_X->ID,new_YUAN_G->ID,60 +fdz);  //����Ԫ ���ݸ�������������ǿ��

		}

        else if(YUAN->Find_linker(new_YUAN_X->ID,new_YUAN_G->ID)==1)//ԭ��������
        {
          fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10
          YUAN->Set_linker_weight_ADD(new_YUAN_X->ID,new_YUAN_G->ID,20);  //��������ǿ����ֵ���ֵ
        }




/////////////





       if(  L[i]=='\0') //���ֽ�����
	   {
        end=1; break;
	   }



    i++; break;

   }






 }//for

 }//while





////////����YԪ Ŀ�꣨���ţ�Ԫ

 
end=0;
i=0;
tt.Empty();
tmpch.Empty();


 while(1) 
 {
  if(end==1) break;


tt.Empty();
tmpch.Empty();



  for(;;)  //��ȡ����ǰ������
  {
 
   tmpch.Format("%c",R[i]);
   tt+=tmpch;
   i++;



    if(R[i]==' ' || R[i]=='\0') //�������� ,
    {

     a=YUAN->Find_name_return_ID(tt); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(420,600));
     YUAN->Set_name(new_YUAN_Y->ID,tt);

     YUAN->Set_threshold(new_YUAN_Y->ID,new_YUAN_Y->threshold + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;



	 }

     else //�����Ԫ
	 {

      new_YUAN_Y=YUAN->ID_return_P(a);

	 }


////��������





        if(YUAN->Find_linker(new_YUAN_F->ID,new_YUAN_Y->ID)==0) //ԭ���ͷ���Ԫû������
		{
          fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10
          YUAN->Link(new_YUAN_F->ID,new_YUAN_Y->ID,20+fdz);  //����Ԫ

		}

        else if(YUAN->Find_linker(new_YUAN_F->ID,new_YUAN_Y->ID)==1)//ԭ��������
        {
          fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10
          YUAN->Set_linker_weight_ADD(new_YUAN_F->ID,new_YUAN_Y->ID,10);  //��������ǿ����ֵ���ֵ
        }




/////////////





       if(  R[i]=='\0') //���ֽ�����
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








//��ʽ����  �����ַ��� ����һ������ 
int CAiQiDlg::Form_Remember_X(CString text) 
{





 CString   S_CString= text; 



 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *





int index=0;


text.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,text);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,text); //����Ԫ�� ���뷽��



     new_YUAN_X->Contacts->Set_data(0,text); //���浽��ϵ��root��

	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

            if(new_YUAN_X->Contacts->Find_Data_Return_N(text)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(text,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }












    return 1;




}




//��ʽ����  �����ַ��� ����һ������ 
int CAiQiDlg::Form_Remember_X2(CString text) 
{





 CString   S_CString= text; 



 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *

//--------------

int De_Flag=0;

CString Debug_Text;
 CString L;
 CString DL;
 CString DR;

L=text;
DL.Empty();
DR.Empty();


if(L.Find("��") !=-1)
{
 //���ַ�����"��"Ϊ�ָ���2���ַ���
 Split_X_String(L,"��",&DL,&DR); 
    DL.Replace( " ", NULL );
    DR.Replace( " ", NULL );

 if(DL.IsEmpty() || DR.IsEmpty())  //"��"ǰ�����������
   {
    ;
   }
 else
   {

    Debug_Text.Format("���ָ�������>> ���:%s  �ұ�:%s",DL,DR);
    TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

    De_Flag=1;
   }

}

else
{
 De_Flag=0;
}
//--------------






text.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,text);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,text); //����Ԫ�� ���뷽��



     new_YUAN_X->Contacts->Set_data(0,text); //���浽��ϵ��root��

            if(De_Flag==1) //�Ǹ�������
              {
                   DR="��"+DR;
                   new_YUAN_X->Contacts->Add(DR,60);
              }

	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

            if(new_YUAN_X->Contacts->Find_Data_Return_N(text)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(text,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }












    return 1;




}


//[��ʽ����] ��������   ��ʽ�� ��ס SνP  �� ��ס S
int CAiQiDlg::Form_Create_Proposition_X(CString text) 
{




  CString DC; //ν�ﶯ��


  
  text.Replace( "��", "�� " ); //���� ���������Ĵʣ��ѡ������ֲ�


 if(text.IsEmpty())  //����������
   {
    return -1;

   }


  if(Find_Text_DC(text, &DC))  //�����ı��еĵ�һ�����ʣ����ҷ�����
    {
     ;

    }

  else   //���û�ж���
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

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX




 CString tt,tmpch;

L.Empty();
R.Empty();


  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո�



   CString ff; //���� ���������Ĵʣ��ѡ������ֲ�
   ff="�� "+DC;
   if(S_CString.Find(ff)!=-1) DC="�� "+DC;



 //���ַ����� ���� Ϊ�ָ���2���ַ���
 Split_X_String(S_CString,DC,&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())  //����ǰ�����������
   {
    return -1;

   }

 Format_String(&L); //��ʽ���ַ��� ȥ���ո�
 Format_String(&R); //��ʽ���ַ��� ȥ���ո�

 CString TX; //�Ѷ��ʼ��ұ� R���ַ���
 DC+=" ";
 TX=DC+R;
 R=TX;


 //�õ����ʸ���
L_Words_Sum= Return_String_Words_Sum(L); //�����ַ����е��ʵ�����
R_Words_Sum= Return_String_Words_Sum(R); //�����ַ����е��ʵ�����


///////////////////////////////






int index=0;

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //����Ԫ�� ���뷽��



     new_YUAN_X->Contacts->Set_data(0,R); //���浽��ϵ��root��

	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(R,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }




















    return 1;



}










//[��ʽ����] ��������   ��ʽ�� ��ס SνP  �� ��ס S
int CAiQiDlg::Form_Create_Proposition_X2(CString text) 
{


  CString Debug_Text;

  CString DC; //ν�ﶯ��

  CString S_CString= text; 

  CString L;
  CString R;


  int r_flag=1; //����ֵ 1��������   2��ǰ�й�ϵǿ��  -1ʧ��




  int a=0,b=0,i=0;
  float fdz=0;

  YUAN_UNIT *new_YUAN_X=NULL; //����ԪX




  CString tt,tmpch;



  
  text.Replace( "��", "�� " ); //���� ���������Ĵʣ��ѡ������ֲ�


 if(text.IsEmpty())  //����������
   {
    return -1;
   }

  //�����ı��еĵ�һ�����ʣ����ҷ�����
  if(Find_Text_DC(text, &DC)) 
    {
     ;
    }

  else   //���û�ж���
   {
     int r;

ptgn:;

     r=Form_Remember_X(text); //��ʽ����  �����ַ��� ����һ������ 

     //----------

     //�鿴�Ƿ��Ǵ�"��"��������

     int De_Flag=0;



      CString DL;
      CString DR;


     DL.Empty();
     DR.Empty();


     if(text.Find("��") !=-1)
     {
      //���ַ�����"��"Ϊ�ָ���2���ַ���
      Split_X_String(text,"��",&DL,&DR); 
         DL.Replace( " ", NULL );
         DR.Replace( " ", NULL );

      if(DL.IsEmpty() || DR.IsEmpty())  //"��"ǰ�����������
        {
         ;
        }
      else
        {

         //Debug_Text.Format("���ָ�������>> ���:%s  �ұ�:%s",DL,DR);
         //TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

          int rr;
          rr=Form_Remember_X(DL); //��ʽ����  �����ַ��� ����һ������
          rr=Form_Remember_X(DR); //��ʽ����  �����ַ��� ����һ������


          CString mc_text=text; //ȥ��text��Ŀո�
          mc_text.Replace( " ", NULL );

          int aa;
          aa=YUAN->Find_name_return_ID(mc_text); //�����Ƿ���һ�������Ԫ

         //Debug_Text.Format("��������>> ����:%s  ID:%d ",mc_text,aa);
         //TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���


          if(aa!=-1)
            {
             YUAN_UNIT *YUAN_X=NULL;
             YUAN_X=YUAN->ID_return_P(aa);

             //CString XDL="<����>"+DL;
             CString XDR="<��>"+DR;

           //  if(YUAN_X->Contacts->Find_Data_Return_N(XDL)==-1) //ԭ�� û��������ϵ��Ϣ
                  //  {
	              //   YUAN_X->Contacts->Add(XDL,60);
                  //  }
             if(YUAN_X->Contacts->Find_Data_Return_N(XDR)==-1) //ԭ�� û��������ϵ��Ϣ
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


  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո�



   CString ff; //���� ���������Ĵʣ��ѡ������ֲ�
   ff="�� "+DC;
   if(S_CString.Find(ff)!=-1) DC="�� "+DC;

   if(S_CString.Find("����")!=-1 && DC=="��") DC="����";


 //���ַ����� ���� Ϊ�ָ���2���ַ���
 Split_X_String(S_CString,DC,&L,&R); 




 if(L.IsEmpty() || R.IsEmpty())  //����ǰ�����������
   {

     goto ptgn;

    //return -1;
   }



/*
         Debug_Text.Format("����:[%s]",DC);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���
         Debug_Text.Format("S_CString:[%s]",S_CString);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���
         Debug_Text.Format("L:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���
         Debug_Text.Format("R:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

*/





///////////////////////////////













//------------


	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

	 DC.Replace( " ", NULL );




         DC="<"+DC+">"; //ν����ϱ�ǩ




//------------




    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //���浽��ϵ������root��


     new_YUAN_X->Contacts->Add(DC+R,60); //���浽��ϵ��1��

	 }



     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

          int Find_Contacts_N;

          Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(DC+R);

              if(Find_Contacts_N==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(DC+R,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //ǿ����ϵ ����Ȩֵ����
				 r_flag=2;

               }

	 }





//------------

    b=YUAN->Find_name_return_ID(R); //�����Ƿ���һ�������Ԫ


     if(b==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,R);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;



     new_YUAN_X->Contacts->Set_data(0,R); //���浽��ϵ������root��


	 }

     else //�����Ԫ
	 {
          ;

	 }












    return r_flag;



}










//[��ʽ����] ���������Ĺ�ϵ������X���Y
int CAiQiDlg::Form_ShangXiaWen(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;

 int L_Words_Sum=0,R_Words_Sum=0;


 if(text.Find("�Ͼ�") ==-1 && text.Find("�¾�") ==-1){return -1;}


  //ȥ��������
   text.Replace( "��", NULL );
   text.Replace( ",", NULL );
   text.Replace( "��", NULL );
   text.Replace( ".", NULL );

   //ȥ���ո�
   text.Replace( " ", NULL );


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *


   S_CString.Replace( "�Ͼ�", NULL );
 //���ַ�����XΪ�ָ���2���ַ���
 Split_X_String(S_CString,"�¾�",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }

 Format_String(&L); //��ʽ���ַ��� ȥ���ո�
 Format_String(&R); //��ʽ���ַ��� ȥ���ո�


 //�õ����ʸ���
L_Words_Sum= Return_String_Words_Sum(L); //�����ַ����е��ʵ�����
R_Words_Sum= Return_String_Words_Sum(R); //�����ַ����е��ʵ�����




int index=0;

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


    // YUAN->Set_Way(new_YUAN_X->ID,1,L); //����Ԫ�� ���뷽��



     new_YUAN_X->Contacts->Set_data(0,R); //���浽��ϵ��root��

	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(R,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }













    return 1;



}









//[��ʽ����] ���������ϵ   ���x��ôY  ������һ�����������ϵ�������X���Y
int CAiQiDlg::Form_IF_THEN_X(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;

 int L_Words_Sum=0,R_Words_Sum=0;


 if(text.Find("���") ==-1 && text.Find("��ô") ==-1){return -1;}


  //ȥ��������
   text.Replace( "��", NULL );
   text.Replace( ",", NULL );
   text.Replace( "��", NULL );
   text.Replace( ".", NULL );


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *


   S_CString.Replace( "���", NULL );
 //���ַ�����XΪ�ָ���2���ַ���
 Split_X_String(S_CString,"��ô",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }

 Format_String(&L); //��ʽ���ַ��� ȥ���ո�
 Format_String(&R); //��ʽ���ַ��� ȥ���ո�


 //�õ����ʸ���
L_Words_Sum= Return_String_Words_Sum(L); //�����ַ����е��ʵ�����
R_Words_Sum= Return_String_Words_Sum(R); //�����ַ����е��ʵ�����




int index=0;

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


    // YUAN->Set_Way(new_YUAN_X->ID,1,L); //����Ԫ�� ���뷽��



     new_YUAN_X->Contacts->Set_data(0,R); //���浽��ϵ��root��

	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(R,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }













    return 1;



}




//[��ʽ����] ���������ϵ   ���x��ôY  ������һ�����������ϵ�������X���Y
int CAiQiDlg::Form_IF_THEN_X2(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;
 CString TT;

 if(text.Find("���") ==-1 && text.Find("��ô") ==-1){return -1;}


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX
 YUAN_UNIT *new_YUAN_Y=NULL; //����ԪY

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *


   S_CString.Replace( "���", NULL );
 //���ַ�����XΪ�ָ���2���ַ���
 Split_X_String(S_CString,"��ô",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }




	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //����Ԫ�� ���뷽��

     TT.Format("<��ô>%s",R);
     new_YUAN_X->Contacts->Set_data(0,TT); //���浽��ϵ��root��

	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(R)==-1) //ԭ�� û��������ϵ��Ϣ
               {
                    TT.Format("<��ô>%s",R);
	            new_YUAN_X->Contacts->Add(TT,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }



//------------
    b=YUAN->Find_name_return_ID(R); //�����Ƿ���һ�������Ԫ

     if(b==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_Y->ID,R);

     YUAN->Set_threshold(new_YUAN_Y->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_Y->ID,1,L); //����Ԫ�� ���뷽��

     TT.Format("<���>%s",L);
     new_YUAN_Y->Contacts->Set_data(0,TT); //���浽��ϵ��root��

	 }

     else //�����Ԫ
	 {

      new_YUAN_Y=YUAN->ID_return_P(b);

              if(new_YUAN_Y->Contacts->Find_Data_Return_N(L)==-1) //ԭ�� û��������ϵ��Ϣ
               {
                    TT.Format("<���>%s",L);
	            new_YUAN_Y->Contacts->Add(TT,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }
















    return 1;



}















//[��ʽ����] ���������ϵ   ���x��ôY  ������һ�����������ϵ�������X���Y
int CAiQiDlg::Form_IF_X_THEN_Y(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;
 CString TT;

 if(text.Find("���") ==-1 && text.Find("��ô") ==-1){return -1;}


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX
 YUAN_UNIT *new_YUAN_Y=NULL; //����ԪY

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *


   S_CString.Replace( "���", NULL );
 //���ַ�����XΪ�ָ���2���ַ���
 Split_X_String(S_CString,"��ô",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }




	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //����Ԫ�� ���뷽��


     new_YUAN_X->Contacts->Set_data(0,L); //���浽��ϵ��root��

     TT.Format("<���>%s",R);
      new_YUAN_X->Contacts->Add(TT,60); //���浽��ϵ��1��


	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

	   int Find_Contacts_N;

   TT.Format("<���>%s",R);

   Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(TT)==-1) //ԭ�� û��������ϵ��Ϣ
               {
                 
	            new_YUAN_X->Contacts->Add(TT,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //ǿ����ϵ ����Ȩֵ����
               }

	 }



//------------
    b=YUAN->Find_name_return_ID(R); //�����Ƿ���һ�������Ԫ

     if(b==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_Y->ID,R);

     YUAN->Set_threshold(new_YUAN_Y->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_Y->ID,1,L); //����Ԫ�� ���뷽��



     new_YUAN_Y->Contacts->Set_data(0,R); //���浽��ϵ��root��

     //TT.Format("<���>%s",L);
     // new_YUAN_X->Contacts->Add(TT,60); //���浽��ϵ��1��




	 }

     else //�����Ԫ
	 {
/*
      new_YUAN_Y=YUAN->ID_return_P(b);

	  int Find_Contacts_N;

      TT.Format("<���>%s",L);

	  Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_Y->Contacts->Find_Data_Return_N(TT)==-1) //ԭ�� û��������ϵ��Ϣ
               {
                
	            new_YUAN_Y->Contacts->Add(TT,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //ǿ����ϵ ����Ȩֵ����
               }

*/			   

	 }
















    return 1;



}




/*


//[��ʽ����] ���������ϵ   ���x��ôY  ������һ�����������ϵ�������X���Y
int CAiQiDlg::Form_IF_X_THEN_Y_2(CString text) 
{
 CString   S_CString= text; 

 CString L;
 CString R;
 CString TT;

 if(text.Find("���") ==-1 && text.Find("��ô") ==-1){return -1;}


 int a=0,b=0,i=0;
 float fdz=0;

 YUAN_UNIT *new_YUAN_X=NULL; //����ԪX
 YUAN_UNIT *new_YUAN_Y=NULL; //����ԪY

 CString tt,tmpch;




  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո� �� *


   S_CString.Replace( "���", NULL );
 //���ַ�����XΪ�ָ���2���ַ���
 Split_X_String(S_CString,"��ô",&L,&R); 



 if(L.IsEmpty() || R.IsEmpty())
   {
    return -1;

   }




	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_X->ID,1,L); //����Ԫ�� ���뷽��


     new_YUAN_X->Contacts->Set_data(0,L); //���浽��ϵ��root��

     TT.Format("<��ô>%s",R);
      new_YUAN_X->Contacts->Add(TT,60); //���浽��ϵ��1��


	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

	   int Find_Contacts_N;

   TT.Format("<��ô>%s",R);

   Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(TT)==-1) //ԭ�� û��������ϵ��Ϣ
               {
                 
	            new_YUAN_X->Contacts->Add(TT,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //ǿ����ϵ ����Ȩֵ����
               }

	 }



//------------
    b=YUAN->Find_name_return_ID(R); //�����Ƿ���һ�������Ԫ

     if(b==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_Y=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_Y->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_Y->ID,R);

     YUAN->Set_threshold(new_YUAN_Y->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;

     //YUAN->Set_Way(new_YUAN_Y->ID,1,L); //����Ԫ�� ���뷽��



     new_YUAN_X->Contacts->Set_data(0,R); //���浽��ϵ��root��

     TT.Format("<���>%s",L);
      new_YUAN_X->Contacts->Add(TT,60); //���浽��ϵ��1��




	 }

     else //�����Ԫ
	 {

      new_YUAN_Y=YUAN->ID_return_P(b);

	  int Find_Contacts_N;

      TT.Format("<���>%s",L);

	  Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(TT);

              if(new_YUAN_Y->Contacts->Find_Data_Return_N(TT)==-1) //ԭ�� û��������ϵ��Ϣ
               {
                
	            new_YUAN_Y->Contacts->Add(TT,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {
                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //ǿ����ϵ ����Ȩֵ����
               }

	 }
















    return 1;



}

*/






void CAiQiDlg::Form_X_QA(CString text1, CString text2)   //[��ʽ����] ����X���� ������ϵ  X��������һ���ı����������ش�
{
   CString tt;
   YUAN_UNIT *YUAN_X=NULL;


   text1.Replace( " ", NULL );
   text2.Replace( " ", NULL );


     int aa;
     aa=YUAN->Find_name_return_ID(text1); //�����Ƿ���һ�������Ԫ

     if(aa!=-1) //ԭ���и���Ԫ
       {

        YUAN_X=YUAN->ID_return_P(aa);


        if(YUAN_X->Contacts->Find_Data_Return_N(text2)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            YUAN_X->Contacts->Add(text2,60);
               }


       }

   else //ԭ��û�и���Ԫ
   {

	 //������Ԫ
     YUAN->New();
     YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(YUAN_X->ID,text1);

     YUAN->Set_threshold(YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


     YUAN_X->Contacts->Set_data(0,text1); //���浽��ϵ��root��
     YUAN_X->Contacts->Add(text2,60); //���浽��ϵ��1��

   }


}







//[��ʽ����] ����X��Y��ϵ  �������������ĸ���
void CAiQiDlg::Form_X_IS_Y(CString X,CString Y) 
{


  CString Debug_Text;

  CString TC; 



  CString L=X;
  CString R=Y;


  int a=0,b=0,i=0;
  float fdz=0;

  YUAN_UNIT *new_YUAN_X=NULL; //����ԪX



  CString tt,tmpch;



 if(L.IsEmpty() || R.IsEmpty())  //����ǰ�����������
   {
    return ;
   }



///////////////////////////////





//------------


	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

         R.Replace( "��", NULL );



        TC.Format("<��>%s",R);

//------------




    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //���浽��ϵ������root��


     new_YUAN_X->Contacts->Add(TC,60); //���浽��ϵ��1��

	 }

     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

              if(new_YUAN_X->Contacts->Find_Data_Return_N(TC)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(TC,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

               }

	 }





//------------

    b=YUAN->Find_name_return_ID(R); //�����Ƿ���һ�������Ԫ


     if(b==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,R);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;



     new_YUAN_X->Contacts->Set_data(0,R); //���浽��ϵ������root��


	 }

     else //�����Ԫ
	 {
          ;

	 }






    return ;



}











void CAiQiDlg::Return_Award_To_AI(YUAN_UNIT *X_YUAN)  //����AI  ����ǿѡ��Ԫ�Ŀ϶�
{
 

  LINK_UNIT *linker_tmp=NULL;

  YUAN_UNIT *tmp_YUAN=NULL;



 if(X_YUAN != NULL) 
  {
     linker_tmp=X_YUAN->linker;

      for(;;) //������������
	  {

            tmp_YUAN=YUAN->ID_return_P(linker_tmp->linker_ID);

           //IF��������Ԫ�Ǽ���״̬
           if(tmp_YUAN->state==1)
             {



                   YUAN->Linker_Weight_Change(tmp_YUAN->ID, X_YUAN->ID, 10);  //�仯 ԪID1 �� ID2 ������Ȩֵ




              
             }


           if(linker_tmp->next==NULL)
	     {
              break;
	     }

           linker_tmp=linker_tmp->next;      

	 }  //������������END




  }


}










void CAiQiDlg::Return_Punishment_To_AI(YUAN_UNIT *X_YUAN)  //�ͷ�AI  ����ǿѡ��Ԫ�ķ�
{
 

  LINK_UNIT *linker_tmp=NULL;

  YUAN_UNIT *tmp_YUAN=NULL;



 if(X_YUAN != NULL) 
  {
     linker_tmp=X_YUAN->linker;

      for(;;) //������������
	  {

            tmp_YUAN=YUAN->ID_return_P(linker_tmp->linker_ID);

           //IF��������Ԫ�Ǽ���״̬
           if(tmp_YUAN->state==1)
             {



                   YUAN->Linker_Weight_Change(tmp_YUAN->ID, X_YUAN->ID, -20);  //�仯 ԪID1 �� ID2 ������Ȩֵ




              
             }


           if(linker_tmp->next==NULL)
	     {
              break;
	     }

           linker_tmp=linker_tmp->next;      

	 }  //������������END




  }


}






void CAiQiDlg::Return_Award_To_AI_X(YUAN_UNIT *X_YUAN,int n)  //����AI  ����ǿѡ��Ԫ�� ��ϵ������϶�
{
 
  float weight=X_YUAN->Contacts->Get_n_weight(n);
 
  X_YUAN->Contacts->Set_weight(n,weight+10);

}



void CAiQiDlg::Return_Punishment_To_AI_X(YUAN_UNIT *X_YUAN,int n)  //�ͷ�AI  ����ǿѡ��Ԫ�� ��ϵ�������
{

  float weight=X_YUAN->Contacts->Get_n_weight(n);
 
  X_YUAN->Contacts->Set_weight(n,weight-20); 

  weight=X_YUAN->Contacts->Get_n_weight(n);
  if(weight<=0) //���ȨֵΪ0 ɾ����ϵ������
    {
     if(n==0) //��root
       {
        X_YUAN->Contacts->Set_data(0,"�Ҳ����...");
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


	// TODO: �ڴ���ӿؼ�֪ͨ����������


  CBrainBoxDlg  dlg;


  dlg.DoModal();
}











//����TXT�ļ����ַ���
void CAiQiDlg::TxtFileRead_to_CString(CString FileName,CString *CStr) 
{
 

 CString Str;

    FILE *fp;
    errno_t err;//����ļ�����

    LPCTSTR filename=FileName;  

 if((err = fopen_s(&fp,filename,"r")) !=0)
	{
          CString ET;
          ET.Format("����%s�ļ����ܶ�ȡ!!",FileName);
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











//�Ƿ��Ƕ��� �Ͷ��ʴʿ��еĴ���Ƚ�
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






//�����ı��еĵ�һ�����ʣ����ҷ�����  �����ȷִ�
bool CAiQiDlg::Find_Text_DC(CString text,CString *DC)
{
 int i;
 CString t;

 int t_start,t_end;
 CString get_text;

  int CI_SUM = Return_String_Words_Sum(text); //�����ַ����е��ʵ�����



   t.Empty();


  if( CI_SUM == 0) goto Find_Text_DC_END;
 

 
  for(i=1;i <=  CI_SUM ; i++)
  {
   


   get_text.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //�����ַ����� ��SN������ ƫ�Ƶĵ�ַ ��ʼ ����


   get_text = text.Mid(t_start, t_end-t_start+1);


   //�Ƿ��Ƕ��� �Ͷ��ʴʿ��еĴ���Ƚ�
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







//�Ƿ������� �����Ա�ǩ�еĴ���Ƚ�
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







//ʶ�����ǩ����Ľ�������ʽ
int CAiQiDlg::Recognition_SXBQ_Form(CString text) 
{



  CString S_CString= text; 


  int text_word_sum;

  CString Word;
  CString SXBQ;
  //CString x;

  int SXBQ_N;


 if(text.IsEmpty())  //����������
   {
    return -1;
   }


  Format_String(&S_CString); //��ʽ���ַ��� ȥ������ո�



  //�����ı��еĵ�һ�����Դʣ����ҷ�����
  SXBQ_N = Find_Text_SXBQ(S_CString, &SXBQ);
  if(SXBQ_N == -1) 
    {
     return -1;
    }


 //x.Format("�� %s",SXBQ);
 S_CString.Replace("�� "+SXBQ,SXBQ);

 Format_String(&S_CString); //��ʽ���ַ��� ȥ������ո�


 text_word_sum = Return_String_Words_Sum(S_CString);
 if(text_word_sum<3)  //�������3����
   {
    return -1;
   }








  Word=Return_String_N_Word(S_CString,2); //�����ַ�����N������
 if(IS_SXBQ(Word) ==0 ) //�ڶ����ʱ����Ǳ�ǩ
   {
     return -1;
   }







  return 1;




}












//��ǩ����Ľ�������
int CAiQiDlg::Form_Create_SXBQ(CString text) 
{

  int r_flag=1; //����ֵ 1��������   2��ǰ�й�ϵǿ��  -1ʧ��

 
  CString S_CString= text; 


  int text_word_sum;

  CString Word;
  CString SXBQ;

  int SXBQ_N;




  CString L;
  CString R;

  int a=0;

  YUAN_UNIT *new_YUAN_X=NULL; //Ŀ��ԪX


 if(text.IsEmpty())  //����������
   {
    r_flag=-1;
    return r_flag;
   }


  Format_String(&S_CString); //��ʽ���ַ��� ȥ������ո�



  //�����ı��еĵ�һ�����Դʣ����ҷ�����
  SXBQ_N = Find_Text_SXBQ(S_CString, &SXBQ);
  if(SXBQ_N == -1) 
    {
    r_flag=-1;
    return r_flag;

    }



 S_CString.Replace("�� "+SXBQ,SXBQ);

 Format_String(&S_CString); //��ʽ���ַ��� ȥ������ո�


 text_word_sum = Return_String_Words_Sum(S_CString);
 if(text_word_sum<3)  //�������3����
   {
    r_flag=-1;
    return r_flag;

   }




  Word=Return_String_N_Word(S_CString,2); //�����ַ�����N������
 if(IS_SXBQ(Word) ==0 ) //�ڶ����ʱ����Ǳ�ǩ
   {
    r_flag=-1;
    return r_flag;
   }



 //���ַ����� ���� Ϊ�ָ���2���ַ���
 Split_X_String(S_CString,SXBQ,&L,&R); 

	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

   //AfxMessageBox(L);
   //AfxMessageBox(R);



    SXBQ = "<"+SXBQ+">"; //���ϱ�ǩ






    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //���浽��ϵ������root��


     new_YUAN_X->Contacts->Add(SXBQ+R,60); //���浽��ϵ��1��

	 }



     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

          int Find_Contacts_N;

          Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(SXBQ+R);

              if(Find_Contacts_N==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(SXBQ+R,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //ǿ����ϵ ����Ȩֵ����
				 r_flag=2;

               }

	 }










    return r_flag;




}







void CAiQiDlg::Form_Create_SXBQ_EX(CString text) //���н���ı�ǩ����Ľ�������
{

              int r=Form_Create_SXBQ(text); //[��ʽ����] ��������ǩ�ļ���


              if(r==1)  //1��������

                {


			      TEXT_OUT_BOX_SAY_3("Ŷ��������Լ�ס�ˡ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				 }

              else if(r==2)  //2��ǰ�й�ϵǿ��

                {


			      TEXT_OUT_BOX_SAY_3("�����Ҿ���Ҳ�����������ԡ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				 }

			  else

			     {
                  TEXT_OUT_BOX_SAY_3("�﷨����",1); //��������Ļ�����

			     }


			


}










//�Ƿ������ݴ� �����ݴʴʿ��еĴ���Ƚ�
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



//�����ı��еĵ�һ�����ԣ����ҷ�����  �����ȷִ�
int CAiQiDlg::Find_Text_SXBQ(CString text,CString *SX)
{
 int i;
 CString t;

 int t_start,t_end;
 CString get_text;

  int CI_SUM = Return_String_Words_Sum(text); //�����ַ����е��ʵ�����



   t.Empty();


  if( CI_SUM == 0) goto Find_Text_SXBQ_END;
 

 
  for(i=1;i <=  CI_SUM ; i++)
  {
   


   get_text.Empty();

   Return_String_SN_start_end(text,i,&t_start,&t_end); //�����ַ����� ��SN������ ƫ�Ƶĵ�ַ ��ʼ ����


   get_text = text.Mid(t_start, t_end-t_start+1);


   //�Ƿ������� �����Դʿ��еĴ���Ƚ�
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







void CAiQiDlg::OnFileRead_ChatLibrary()  //��ȡ���Ͽ��ļ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

CString XT,TT;




  CString FileName;

  CFileDialog FileDlg(TRUE);
  FileDlg.m_ofn.lpstrTitle="�ļ���";
  FileDlg.m_ofn.lpstrFilter="�ı��ļ�(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";

	
  if(FileDlg.DoModal() == IDOK )
  {


            XT.Format("���ڼ����������Ͽ��ļ�,���Ժ�...");
            TEXT_OUT_BOX_SAY_3(XT,0); //��������Ļ�����
            UpdateWindow( );//���������ػ�

       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 

Current_Memory_File_Name = _T("");//��ǰ�򿪵ļ����ļ���

   //TEXT_OUT_BOX_CLS();


    FileName=FileDlg.GetPathName();



    FILE *fp;
	 errno_t err;//����ļ�����
    //	const char *filename = (LPCTSTR)FileName; //ת������ ���¸����ļ���

    LPCTSTR filename=FileName;  //��ֹ0x73d311c7���� 0x00000004�ڴ治�ܶ�

    if((err=fopen_s(&fp,filename,"r")) !=0)
	{

     AfxMessageBox("����������ļ����ܶ�!!");
	}



   ///////////////////////////////////////////////////////////////

       YUAN->FreeAll(YUAN);  //�������

	   //int tmp_ID_X;
       char ch;
       //int n,i;

	   int end=0;



	   YUAN_ID_X=0;
       YUAN_SUM=0;  //Ԫ������Ϊ0

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

            XT.Format("�Ѽ�������>> ��:%s",L);
            TEXT_OUT_BOX_SAY_3(XT,0); //��������Ļ�����

			XT.Format("�Ѽ�������>> ��:%s",R);
            TEXT_OUT_BOX_SAY_3(XT,0); //��������Ļ�����


            

*/


 CL_SUM++;

            TT.Format("�Ͼ�%s�¾�%s",L,R);
/*
//========================
//���ķִ�


   TT = ZWFC(TT);//���ķִ�


//========================

*/





            Form_ShangXiaWen(TT); //[��ʽ����] ���������Ĺ�ϵ������X���Y


            L.Empty();
            R.Empty();

            js=1; ch=fgetc(fp); 

          }
     }






         while(1) //����
	{

          ch=fgetc(fp);  


		   if(ch==EOF) //����
		   { 
                    end=1;  break;
		   }

		   if(ch=='\n') //�س�
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



            XT.Format("�Ѽ���%d�������������ݣ����䵽AiQi�ļ����",CL_SUM);
            TEXT_OUT_BOX_SAY_3(XT,0); //��������Ļ�����

               AI_YES_Flag=1;


  

   fclose(fp);

  }


YUAN_RUN_MAIN_Flag=1;



}








int CAiQiDlg::Assess_To_Two_String(CString S,CString D) //�������ַ������ƶȴ��  S������  D�Ƕ���
{
 int zpf=0;
 int pf1=0; //��������
 int pf2=0;
 int pf3=0;

CString Debug_Text;

 S = ZWFC(S);//���ķִ�
 D = ZWFC(D);//���ķִ�

  Format_String(&S); //��ʽ���ַ��� ȥ���ո�
  Format_String(&D); //��ʽ���ַ��� ȥ���ո�



 //�õ����ʸ���
 int S_Words_Sum= Return_String_Words_Sum(S); //�����ַ����е��ʵ�����
 int D_Words_Sum= Return_String_Words_Sum(D); //�����ַ����е��ʵ�����

 //������ͬ����---------------------------20
 pf1=20; 
 int  pjf1 = 20 / S_Words_Sum;

 pf1 = 20 - pjf1 * (abs(S_Words_Sum-D_Words_Sum));
 if(pf1<=0) pf1=0;






 //�������ͬ����--------------------------- 
 pf2=0;
int pjf2=30;

 CString SS,DD;

 int Z_OK=0;

int i;

  for(i=1;i <= S_Words_Sum ; i++)
     {
      SS.Empty();


      SS=Return_String_N_Word(S,i); //�����ַ�����N������
      if(D.Find(SS) !=-1 )

            { Z_OK++;}








     }





pf2=pjf2*Z_OK;




 //�������ͬ,����λ��Ҳ��ͬ����---------------------------����ӷ�
 pf3=0;


 Z_OK=0;
  int Z_NO=0;

 if(S_Words_Sum==D_Words_Sum)

 {
  for(i=1;i <= S_Words_Sum ; i++)
     {
      SS.Empty();
      DD.Empty();

      SS=Return_String_N_Word(S,i); //�����ַ�����N������
      DD=Return_String_N_Word(D,i); //�����ַ�����N������

	  if(SS==DD) { Z_OK++;}
	  else{Z_NO++;}

     }


 }


pf3=10*Z_OK - 30*Z_NO;


 //---------------------------


// Debug_Text.Format("pf1=%d,pf2=%d,pf3=%d",pf1,pf2,pf3);
 //TEXT_OUT_BOX_SAY_3(Debug_Text,0); //��������Ļ�����



 zpf=pf1+pf2+pf3;
 if(zpf>1000) zpf=1000;
 if(zpf<0) zpf=0;

 return zpf;
}






void CAiQiDlg::Input_Activation_YUAN(CString text)  //ͨ����������ַ�����Ԫ���֣����������ָߵ�Ԫ
{
   YUAN_UNIT *tmp;


   int pf;
				 
				 
				 
				

  tmp=YUAN;


  for(;;) //��������Ԫ
  {


    if(tmp->ID!=0) //0��Ԫ����
     {

      
      pf=0;



      CString TT;

	  TT=tmp->name;

      TT = ZWFC(TT);//���ķִ�
      Format_String(&TT); //��ʽ���ַ��� ȥ���ո�

      pf=Assess_To_Two_String(text,TT); //�������ַ������ƶȴ��

	  pf=(int)(pf*3.0f); //��Ծ��=����X3

      if(pf>=100)
        {
         //tmp->state=1;
         //tmp->E_X=(float)pf;
		  YUAN->Set_state(tmp->ID,2); //׼������
		  YUAN->Add_E_X(tmp->ID,(float)pf);//���ӱ��ǿ��ЧӦ����
        }


     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND



}









void CAiQiDlg::Input_Activation_YUAN_By_Contacts(CString text)  //ͨ����������ַ�����Ԫ��ϵ�����֣�������Ԫ��Ծ��
{
  YUAN_UNIT *tmp;
  CONTACTS_UNIT *P_YUAN_Contacts;

  int pf=0;

  tmp=YUAN;

  float E_X;


  for(;;) //��������Ԫ
  {


    if(tmp->ID!=0) //0��Ԫ����
     {

      




   //������ϵ��
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {



      CString TT;

	  TT=P_YUAN_Contacts->data;

      TT = ZWFC(TT);//���ķִ�
      Format_String(&TT); //��ʽ���ַ��� ȥ���ո�

     pf=Assess_To_Two_String(text,TT); //�������ַ������ƶȴ��

    E_X=(float)pf/5;

    YUAN->Add_E_X(tmp->ID,E_X);//���ӱ��ǿ��ЧӦ����

 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //������ϵ��end


          




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND




}








void CAiQiDlg::Input_Activation_YUAN_By_Contacts_2(CString text)  //ͨ����������ַ�����Ԫ���ݱȽϣ�������Ԫ��Ծ�ȣ��Ƚ�<��><����>��ǩ
{
  YUAN_UNIT *tmp;
  CONTACTS_UNIT *P_YUAN_Contacts;



  tmp=YUAN;


   CString text_x; //ȥ���ո��
   text_x=text;
   text_x.Replace( " ", NULL );
   int text_x_l=text_x.GetLength();//�ַ����ĳ���

  for(;;) //��������Ԫ
  {


    if(tmp->ID!=0) //0��Ԫ����
     {


   //������ϵ��
   P_YUAN_Contacts=tmp->Contacts;
   for(;;)
   {



      CString TT;

	  TT=P_YUAN_Contacts->data;

      if(TT.Find("<��>")!=-1) //��<��>�ı�ǩ
        {
          TT.Replace( "<��>", NULL );

          if(text.Find(TT)!=-1)
		    {

             YUAN->Add_E_X(tmp->ID,80);//���ӱ��ǿ��ЧӦ����
		    }

        }

      else if(TT.Find("<����>")!=-1) //��<����>�ı�ǩ
        {
 
			if(text_x_l>=8)//ƥ�䳤����8���ֽ���Ч
			{
             if(TT.Find(text_x)!=-1) //���Ҵ�<����>��ǩ�������Ƿ��к�����һ��������
		       {

                YUAN->Add_E_X(tmp->ID,80);//���ӱ��ǿ��ЧӦ����
		       }

			}

        }





 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //������ϵ��end


          




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND




}












void CAiQiDlg::Find_YUAN_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts)  //���������Ƶ���ϵ������ ���ظ����� �� Ԫָ��
{
   YUAN_UNIT *tmp;


   int pf=0;
   int MAX_pf=20;

   YUAN_UNIT  *MAX_pf_YUAN=NULL;
   CString MAX_pf_YUAN_Contacts;
				 
   CONTACTS_UNIT *P_YUAN_Contacts;				 
				 
			

  tmp=YUAN;

  


  MAX_pf_YUAN_Contacts.Empty();

  for(;;) //��������Ԫ
  {


    if(tmp->ID!=0) //0��Ԫ����
     {

      


       if(tmp->state==1)
         {

   //������ϵ��
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {

 

     pf=Assess_To_Two_String(text,P_YUAN_Contacts->data); //�������ַ������ƶȴ��

     if(pf>MAX_pf && pf>=sspf) //������߷� �������
       {
        MAX_pf=pf;
        MAX_pf_YUAN=tmp; //����Ԫ
        MAX_pf_YUAN_Contacts=P_YUAN_Contacts->data;//��������Ԫ��ϵ������

       }

 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //������ϵ��end


          }




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND


*YUAN_p=MAX_pf_YUAN;
*YUAN_Contacts=MAX_pf_YUAN_Contacts;


}








void CAiQiDlg::Find_YUAN_X_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts)  //���������Ƶ���ϵ������ ���ظ����� �� Ԫָ�� û��״̬����
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

  for(;;) //��������Ԫ
  {


    if(tmp->ID!=0) //0��Ԫ����
     {

      




   //������ϵ��
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {

        float xr=(float)Xrand(1,1000)/100 ; //������� 0.01~10



     pf=(float) Assess_To_Two_String(text,P_YUAN_Contacts->data) + xr ; //�������ַ������ƶȴ��

	 weight=P_YUAN_Contacts->weight  + xr ;


 //CString TT;
 //TT.Format("���֣�%s  ԭ�ģ�%s   ���ݣ�%s  ���֣�%0.2f",tmp->name ,text ,P_YUAN_Contacts->data,pf);
 //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����



     if(pf>MAX_pf && pf>=sspf && weight>=MAX_weight) //������߷� �������
       {
 



        MAX_pf=pf ;
		MAX_weight=weight ;
        MAX_pf_YUAN=tmp; //����Ԫ
        MAX_pf_YUAN_Contacts=P_YUAN_Contacts->data;//��������Ԫ��ϵ������

       }

 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //������ϵ��end


          




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND


*YUAN_p=MAX_pf_YUAN;
*YUAN_Contacts=MAX_pf_YUAN_Contacts;


}







void CAiQiDlg::Find_YUAN_X_Contacts_DC(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts,CString DC)  //���������Ƶ���ϵ������ ���ظ����� �� Ԫָ�� û��״̬���� ������ϵ����Ķ��ʶ���
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

  for(;;) //��������Ԫ
  {


//if(end==1) break;

    if(tmp->ID!=0) //0��Ԫ����
     {

      
    if(tmp->state==1)
	{



   //������ϵ��
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {


      YUAN_Contacts_DC.Empty();

      TT=ZWFC(P_YUAN_Contacts->data);   //���ķִ�
 
      Find_Text_DC(TT,&YUAN_Contacts_DC);


if(!YUAN_Contacts_DC.IsEmpty())
{ 
 CString LL,RR;
 Split_X_String(P_YUAN_Contacts->data,YUAN_Contacts_DC,&LL,&RR); //���ַ�����XΪ�ָ���2���ַ���

 if(LL.Find("��")!=-1) YUAN_Contacts_DC="��"+YUAN_Contacts_DC;

}


        float xr=(float)Xrand(1,1000)/100 ; //������� 0.01~10

      weight=P_YUAN_Contacts->weight + xr ;



//CString TT;
//TT.Format("���ݣ�%s  ���ʣ�%s weight��%0.2f",P_YUAN_Contacts->data,YUAN_Contacts_DC,weight);
//TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����




	  if(YUAN_Contacts_DC==DC && weight>=MAX_weight)
	  {
      



		MAX_weight=weight;
        MAX_pf_YUAN=tmp; //����Ԫ
        MAX_pf_YUAN_Contacts=P_YUAN_Contacts->data;//��������Ԫ��ϵ������

 

//end=1; break;

	  }
 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //������ϵ��end


          
	}



     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND


*YUAN_p=MAX_pf_YUAN;


*YUAN_Contacts=MAX_pf_YUAN_Contacts;


if(MAX_weight<=sspf)
{
 *YUAN_p=NULL;

}


}







//����ָ��ĳԪ����ϵ������ �����ԡ�text����ǩ��ͷ���ַ����Ԫ
void CAiQiDlg::Find_YUAN_Contacts_Label_Activation_YUAN(YUAN_UNIT *YUAN_p,CString text,int power)  
{


   CONTACTS_UNIT *P_YUAN_Contacts;

   CString RR;


  //������ϵ��
   P_YUAN_Contacts=YUAN_p->Contacts;



   for(;;)
   {

    text.Replace( " ", NULL);


    if(P_YUAN_Contacts->data.Find(text)==0) //�����������
	{


     RR=P_YUAN_Contacts->data;

     //���ַ�����XΪͷ�ָ� ȡ���沿��
     Split_X_String_Head(text,&RR);
     if(!RR.IsEmpty())
     Activation_YUAN(RR, power); //����ĳ��Ԫ ״̬��1

	}


 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //������ϵ��end






}



//����ָ��ĳԪ����ϵ������ �����ԡ�text����ǩ��ͷ���ַ����Ԫ
void CAiQiDlg::Find_YUAN_Contacts_Label_Inhibit_YUAN(YUAN_UNIT *YUAN_p,CString text,int power)  
{


   CONTACTS_UNIT *P_YUAN_Contacts;

   CString RR;


  //������ϵ��
   P_YUAN_Contacts=YUAN_p->Contacts;



   for(;;)
   {

    if(P_YUAN_Contacts->data.Find(text)==0) //�����������
	{

     RR=P_YUAN_Contacts->data;

     //���ַ�����XΪͷ�ָ� ȡ���沿��
     Split_X_String_Head(text,&RR);
     if(!RR.IsEmpty())
     Inhibit_YUAN(RR, power); // ����ĳ��Ԫ ״̬��1

	}


 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;


   }

   //������ϵ��end






}











void CAiQiDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

		// CString TT;
		// TT.Format("��ǰ�ļ�����%s",Current_Memory_File_Name);

       //     AfxMessageBox(TT);


if(Auto_Load_And_Save_Memory_Flag ==1) //�Զ����غͱ������
{
 //��ǰ�򿪵ļ����ļ���
	if(Current_Memory_File_Name.Find("AiQi�ļ���") !=-1)
   {
		//CString TT;
		//TT.Format("�Զ����棺�����ļ�/AiQi�ļ���.bbf");

           //AfxMessageBox(TT);
     CBrainBoxDlg a;
     a.Save_Memory_File_XML(2,Current_Memory_File_Name);

   }
}



}




















void CAiQiDlg::Run_YUAN_Contacts_Data(CString Data) //����һ�����Ԫ���������
{

 
  CString TT=Data;



 //ʶ���������������


if(TT.Find("<")!=-1&&TT.Find(">")!=-1) //�Ǳ�ǩ���
{

 if(TT.Find("<��>")!=-1) 
  {
   TT.Replace( "<��>", "��" );
   TEXT_OUT_BOX_SAY_3("�Ҿ��ã�"+TT,1); //������ʾ����Ļ��
  }

 else if(TT.Find("<����>")!=-1)
  {
   TT.Replace( "<����>", "����" );
   TEXT_OUT_BOX_SAY_3("�Ҹо���"+TT,1); //������ʾ����Ļ��
  }

  else if(TT.Find("<���>")!=-1) 
  {
   TT.Replace( "<���>", NULL);
   TEXT_OUT_BOX_SAY_3("����..."+TT,1); //������ʾ����Ļ��
  }

 else if(TT.Find("<�ű�����>")!=-1) //ִ�нű�����
  {
   TT.Replace( "<�ű�����>", NULL );

   Run_Script(TT);

  }

 else 
  {
   TT.Replace( "<", NULL );
   TT.Replace( ">", NULL );
   TEXT_OUT_BOX_SAY_3("�Ҽǵã�"+TT,1); //������ʾ����Ļ��
  }

}

 else //��ͨ���� 
  {
   TT.Replace( " ", NULL );

   TEXT_OUT_BOX_SAY_3(TT,1); //������ʾ����Ļ��
  }


 


}


//���нű�����=======================================================================



void CAiQiDlg::Run_Script(CString Data) //���нű�
{

 int Data_length=Data.GetLength();//�ַ����ĳ���
 CString Command;

 int i=0;
    //��ȡһ�� ;�����Ľű����
   while(1)
   {
    if(i>Data_length) break;

    Command += Data[i];

    
    if(Data[i]==';')
      {

       Command.Replace( ";", NULL );

       Run_Scr_Command(Command); //��������ѡ��ִ�нű�

       Command.Empty();

      }


    i++;
   }


}



void CAiQiDlg::Scr_Command_Out_Text(CString Command)  //�ű� �������
{
   Command.Replace( "�������", NULL );
   Command.Replace( "(", NULL );
   Command.Replace( ")", NULL );
   Command.Replace( "��", NULL );
   Command.Replace( "��", NULL );


   CString TT;
   TT=Command;
   TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
}

void CAiQiDlg::Scr_Command_Open_Web(CString Command) //�ű� ����ҳ
{

   Command.Replace( "����վ", NULL );
   Command.Replace( "(", NULL );
   Command.Replace( ")", NULL );
   Command.Replace( "��", NULL );
   Command.Replace( "��", NULL );

   CString TWeb;

   TWeb="http://"+Command;

			     TWeb.Replace( " ", NULL );

               ShellExecute(NULL, "open", TWeb , NULL, NULL, SW_SHOWNORMAL);



   CString TT;
   TT="����վ��" + Command;
   TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
}




void CAiQiDlg::Scr_Command_Weather_Forecast(CString Command)  //�ű� �������
{
   Command.Replace( "��ѯ����", NULL );
   Command.Replace( "(", NULL );
   Command.Replace( ")", NULL );
   Command.Replace( "��", NULL );
   Command.Replace( "��", NULL );



                           CString x=Command;
                           x.Replace( " ", NULL );

			               CString TX;    
                          CString TT;

                          CString city_number;


                            CString CityName=x;




                          

                            city_number=Get_City_Weather_Number(CityName);  //���س�����������

                            if(city_number=="û���ҵ�")
                              {
                               TT.Format("û����ص������������ݡ�");
                               TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                              }
                            else
                              {


                               //TT.Format("���д���=%s",city_number);
                               //TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����

                               CString CT;
                               CT=Get_Weather_Information_From_Web(city_number); //�������ϻ�ȡ������Ϣ������

                                   TX= CityName + "  "+ CT +"C";  
      
                               TT.Format("%s",TX);
                               TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����


                              }


}







void CAiQiDlg::Run_Scr_Command(CString Command) //��������ѡ��ִ�нű�
{
 if(Command.Find("�������") !=-1 )       Scr_Command_Out_Text(Command);
 else if(Command.Find("����վ") !=-1 )  Scr_Command_Open_Web(Command);
 else if(Command.Find("��ѯ����") !=-1 )  Scr_Command_Weather_Forecast(Command);

 else
  {
   CString TT;
   TT="����ִ�������ű���� " + Command;
   TEXT_OUT_BOX_SAY_3(TT,1); //��������Ļ�����
  }
}









//�����ʾԪ������
void CAiQiDlg::Cmd_Display_YUAN_Data( CString text)
{
   CString TT;
   CString ST;
   YUAN_UNIT *YUAN_X=NULL;
   CONTACTS_UNIT *P_YUAN_Contacts;



  text.Replace( " ", NULL );

     int aa;
     aa=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ

     if(aa!=-1)
       {

        YUAN_X=YUAN->ID_return_P(aa);


     ST.Format("����:%s\r\n ",YUAN_X->name);
          TT+=ST;
     ST.Format("----------------------------\r\n ");
          TT+=ST;

   //������ϵ��
   P_YUAN_Contacts=YUAN_X->Contacts;

   int n=0;
   int ID;

   for(;;)
   {




        ID=P_YUAN_Contacts->ID;

	   ST.Format("[����%d]:%s\r\n ",ID,P_YUAN_Contacts->data);


     TT+=ST;


 
    if(P_YUAN_Contacts->next==NULL)
	{
         break;
	}
    P_YUAN_Contacts=P_YUAN_Contacts->next;

    n++;

   }

   //������ϵ��end


              TEXT_OUT_BOX_SAY_3(TT,0); //������� 


       }

else
{

     TT.Format("���󣬸���[%s]�����ڡ�",text);
     TEXT_OUT_BOX_SAY_3(TT,0); //�������

}


}





//���ɾ��Ԫ
void CAiQiDlg::Cmd_Del_YUAN( CString text)
{
   CString TT;

   YUAN_UNIT *YUAN_X=NULL;




  text.Replace( " ", NULL );

     int aa;
     aa=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ

     if(aa!=-1)
       {



        YUAN->Del_ID(aa);

        TT.Format("����[%s]�Ѿ�ɾ���� ",text);




              TEXT_OUT_BOX_SAY_3(TT,0); //������� 


       }

else
{

     TT.Format("���󣬸���[%s]�����ڡ�",text);
     TEXT_OUT_BOX_SAY_3(TT,0); //�������

}


}






//���ɾ��Ԫ����
void CAiQiDlg::Cmd_Del_YUAN_Contacts( CString text,int Contacts_ID)
{
   CString TT;

   YUAN_UNIT *YUAN_X=NULL;
   CONTACTS_UNIT *P_YUAN_Contacts=NULL;


  if(Contacts_ID==0)
         
           {
            TT.Format("���󣬲���ɾ������[%s]�ĸ����ݣ�",text);
            TEXT_OUT_BOX_SAY_3(TT,0); //�������

            return;
           }


  text.Replace( " ", NULL );

     int aa;
     aa=YUAN->Find_name_return_ID(text); //�����Ƿ���һ�������Ԫ

     if(aa!=-1)
       {


         YUAN_X=YUAN->ID_return_P(aa);


         P_YUAN_Contacts=YUAN_X->Contacts->ID_return_P(Contacts_ID);
         if(P_YUAN_Contacts!=NULL)
           {



           }
         else
           {
            TT.Format("���󣬸���[%s]�е�����[%d]�����ڡ�",text,Contacts_ID);
            TEXT_OUT_BOX_SAY_3(TT,0); //�������

            return;
           }



         YUAN_X->Contacts->Del(Contacts_ID);

  








        TT.Format("����[%s]�е�����[%d]�������Ѿ�ɾ���� ",text,Contacts_ID);

        


              TEXT_OUT_BOX_SAY_3(TT,0); //������� 


       }

 else
 {

     TT.Format("���󣬸���[%s]�����ڡ�",text);
     TEXT_OUT_BOX_SAY_3(TT,0); //�������

 }


}




CString CAiQiDlg::CString_Extraction_Content(CString text,CString a,CString b)   //�ַ�����ȡ�м�����
{
  
 CString strOut;


 int len = a.GetLength();

 int nStart=text.Find(a)+len;
 int nEnd=text.Find(b,nStart);

 strOut=text.Mid(nStart,nEnd-nStart);



 return strOut;
}




CString CAiQiDlg::Get_CiTiao_Information_From_Web(CString CiTiao) //�������ϻ�ȡ������Ϣ������
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







     CString content; //����


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

  //���CHttpFile������������
  char *pStr = content.GetBuffer(content.GetLength()); //ȡ��str�����ԭʼ�ַ���
  int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0); //ȡ�����軺��Ķ���
  wchar_t *pBuffer = (wchar_t*)malloc(nBufferSize * sizeof(wchar_t));//���뻺��ռ�
  MultiByteToWideChar(CP_UTF8, 0, pStr, -1 , pBuffer, nBufferSize*sizeof(wchar_t));//ת��

  CString xx(pBuffer);
  content=xx;



  m_web_text=content; //����

  free(pBuffer); //�ͷŻ���




  //��ȡ ������Ϣ����

  CString str_a = "content=\""+m_my_ct+"-";

  m_web_good_information.Empty();

  m_web_good_information = CString_Extraction_Content(m_web_text,str_a,"\" name=\"description");   //�ַ�����ȡ�м�����

  if(m_web_good_information.IsEmpty()==1) //��ҳû�д�������
  {

   m_web_good_information="û�в�ѯ��";
  }



  //ȥ�����ܵĶ�����ҳ����
  if(m_web_good_information.Find("www.w3.org") || m_web_good_information.Find("<meta content=\"") || m_web_good_information.Find("_�����ٿ�</title>"))
    {


     CString xt;
     xt.Format("_�����ٿ�");


     int nFirst = m_web_good_information.Find(xt);
     m_web_good_information = m_web_good_information.Mid( nFirst+0);

     //�˳�������Ϣ
	 m_web_good_information.Replace( "\n", NULL );
	 m_web_good_information.Replace( "\r", NULL );
     m_web_good_information.Replace( "<meta content=\"", NULL );
     m_web_good_information.Replace( "</title>", NULL );
     m_web_good_information.Replace( "_�����ٿ�", NULL );

    }








 TT=m_web_good_information;

 return TT;

}






CString CAiQiDlg::Get_Weather_Information_From_Web(CString city_number) //�������ϻ�ȡ������Ϣ������
{
 CString TT;


 CString m_web_url;
 CString m_web_text;
 CString m_web_good_information;




 //m_web_url="http://www.weather.com.cn/weather1d/101020100.shtml";


 m_web_url="http://www.weather.com.cn/weather1d/" + city_number + ".shtml" ;







     CString content; //����


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

   //���CHttpFile������������
   char *pStr = content.GetBuffer(content.GetLength()); //ȡ��str�����ԭʼ�ַ���
   int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0); //ȡ�����軺��Ķ���
   wchar_t *pBuffer = (wchar_t*)malloc(nBufferSize * sizeof(wchar_t));//���뻺��ռ�
   MultiByteToWideChar(CP_UTF8, 0, pStr, -1 , pBuffer, nBufferSize*sizeof(wchar_t));//ת��

   CString xx(pBuffer);
   content=xx;



   m_web_text=content; //����

   free(pBuffer); //�ͷŻ���




   //��ȡ ������Ϣ����



   m_web_good_information.Empty();


   m_web_good_information = CString_Extraction_Content(m_web_text,"<input type=\"hidden\" id=\"hidden_title\" value=\"","C\" />");   //�ַ�����ȡ�м�����

   if(m_web_good_information.IsEmpty()==1) //��ҳû�д�������
   {

    m_web_good_information="û�в�ѯ��";
   }


  TT=m_web_good_information;

  return TT;

}




int CAiQiDlg::Learn_CiTiao_From_Web(CString CiTiao) //��������ѧϰ������Ϣ  ����ѧϰ����������
{

  CString m_web_good_information = Get_CiTiao_Information_From_Web(CiTiao); //�������ϻ�ȡ������Ϣ������

 
  int aa;

  YUAN_UNIT *new_YUAN_X=NULL; //����ԪX

  int New_Data_Sum=0;
  int Old_Data_Sum=0;
  int Learn_Data_Sum=0;

  //------------




    aa=YUAN->Find_name_return_ID(CiTiao); //�����Ƿ���һ�������Ԫ


     if(aa==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,CiTiao);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


     new_YUAN_X->Contacts->Set_data(0,CiTiao); //���浽��ϵ������root��




	 }

     else //�����Ԫ
	 {

            new_YUAN_X=YUAN->ID_return_P(aa);
            Old_Data_Sum = new_YUAN_X->Contacts->Get_Sum(); //ͳ�����ݱ����


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

 a[0]=S.Find("��");
 a[1]=S.Find("��");

 if(a[0]==-1&&a[1]==-1)
   {
       break;//��û���ҵ�������
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

        H=S.Left(X_weizhi); //��ȡһ�� ��������


//TEXT_OUT_BOX_SAY_3("��ȡ���ݣ�"+H,0); //��������Ļ�����






//������ѧϰ
int fwz;
int fx=0;
//-------
fwz = H.Find( "Ϊ" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "��" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "����" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "����" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( "ָ" );
if(fwz==0) { fx=1; goto fx1;}
//-------
fwz = H.Find( CiTiao+"��" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( CiTiao+"ָ" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( CiTiao+"��ָ" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------

fwz = H.Find( "ͨ����" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( "��˼��" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( "һ��ָ" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------
fwz = H.Find( "��Ϊ" );
if(fwz!=-1) { fx=1; goto fx1;}
//-------



fx=1;//��ѧϰ


fx1:
if(fx==1) //ѧϰ
{
              if(new_YUAN_X->Contacts->Find_Data_Return_N(H)==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(H,60);
				New_Data_Sum++;
               }


}







 
   
    //��һ��������㿪ʼ
    if(a_n==0) {S=S.Mid(X_weizhi+2);}
    else if(a_n==1) {S=S.Mid(X_weizhi+2);}





}



 Learn_Data_Sum = New_Data_Sum - Old_Data_Sum; //ͳ����ѧϰ����������
 if(Learn_Data_Sum<0)  Learn_Data_Sum=0;

 return Learn_Data_Sum;

}









void CAiQiDlg::Display_AUTO_Question_Time(int x, int y,int Time,int MAX_Time,CDC *pDC) //��ʾ�Զ�����ʱ��
{
 float dx;

 float time,MAX_time;

 MAX_time=(float)MAX_Time;
 time=(float)Time;

 dx= (float)(188 / MAX_time)   * time;



 pDC->FillSolidRect(x,y,x+(int)dx,2,RGB(112,180,158));

}







//ʶ����ν������ʽ
int CAiQiDlg::Recognition_ZWB_Form(CString text) //����ͱ��ﲿ�ֿ�����һ�����ʣ�Ҳ������һ�����ʡ� ν�ﶯ�ʱ�����һ��
{


  //CString Debug_Text;

  CString DC,_DC; //ν�ﶯ��

  CString S_CString= text; 

  CString L;
  CString R;

  int LN,RN;


//text.Replace( "��", NULL ); 

 text.Replace( "��", "�� " ); //���� ���������Ĵʣ��ѡ������ֲ�

 if(text.IsEmpty())  //����������
   {
    return -1;
   }

  //�����ı��еĵ�һ�����ʣ����ҷ�����
  if(Find_Text_DC(text, &DC)!=1) 
    {
     return -1;
    }



  L.Empty();
  R.Empty();


  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո�


   CString ff; //���� ���������Ĵʣ��ѡ������ֲ�
   ff="�� "+DC;
   if(S_CString.Find(ff)!=-1) DC="�� "+DC;

   if(S_CString.Find("����")!=-1 && DC=="��") DC="����";



 //���ַ����� ���� Ϊ�ָ���2���ַ���
 Split_X_String(S_CString,DC,&L,&R); 

 if(L.IsEmpty() || R.IsEmpty())  //����ǰ�����������
   {
    return -1;
   }

  LN=Return_String_Words_Sum(L); //�����ַ����е��ʵ�����
  RN=Return_String_Words_Sum(R); 

/*
  if(LN==1)
    {
         Debug_Text.Format("��ߵ�����:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

    }
  else
    {
         Debug_Text.Format("�ұ߶����:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

    } 
   
  if(RN==1)
    {
         Debug_Text.Format("�ұߵ�����:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

    }    
  else
    {
         Debug_Text.Format("�ұ߶����:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

    }   
*/

  if(Find_Text_DC(L, &_DC)==1) //����ж����˳�
    {
     return -1;
    }

 // if(Find_Text_DC(R, &_DC)==1) //����ж����˳�
 //   {
  //   return -1;
 //   }

   L.Replace( "��", NULL );
   R.Replace( "��", NULL );

        // Debug_Text.Format("������ν������ʽ��[%s]%s[%s]",L,DC,R);
        // TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

  return 1;




}




//[��ʽ����] ������ν����ϵ ��ʶ���������ݴ� ���ϴ��Ա�ǩ
int CAiQiDlg::Form_Create_ZWB(CString text)
{


  CString Debug_Text;

  CString DC; //ν�ﶯ��

  CString S_CString= text; 

  CString L;
  CString R;


  int R_IS_XRC=0;


  int r_flag=1; //����ֵ 1��������   2��ǰ�й�ϵǿ��  -1ʧ��




  int a=0,b=0,i=0;
  float fdz=0;

  YUAN_UNIT *new_YUAN_X=NULL; //����ԪX




  CString tt,tmpch;



  
  text.Replace( "��", "�� " ); //���� ���������Ĵʣ��ѡ������ֲ�


 if(text.IsEmpty())  //����������
   {
    return -1;
   }

  //�����ı��еĵ�һ�����ʣ����ҷ�����
  if(Find_Text_DC(text, &DC)) 
    {
     ;
    }

  else   //���û�ж���
   {
     int r;

     r=Form_Remember_X(text); //��ʽ����  �����ַ��� ����һ������ 

     //----------



        //AfxMessageBox("����һ������");



         return  r;
        }

 

L.Empty();
R.Empty();


  Format_String(&S_CString); //��ʽ���ַ��� ȥ���ո�



   CString ff; //���� ���������Ĵʣ��ѡ������ֲ�
   ff="�� "+DC;
   if(S_CString.Find(ff)!=-1) DC="�� "+DC;

   if(S_CString.Find("����")!=-1 && DC=="��") DC="����";


 //���ַ����� ���� Ϊ�ָ���2���ַ���
 Split_X_String(S_CString,DC,&L,&R); 




 if(L.IsEmpty() || R.IsEmpty())  //����ǰ�����������
   {
    return -1;
   }



/*
         Debug_Text.Format("����:[%s]",DC);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���
         Debug_Text.Format("S_CString:[%s]",S_CString);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���
         Debug_Text.Format("L:[%s]",L);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���
         Debug_Text.Format("R:[%s]",R);
         TEXT_OUT_BOX_SAY_3(Debug_Text,0); //������ʾ�ڴ���

*/





///////////////////////////////













//------------


	 L.Replace( " ", NULL );
	 R.Replace( " ", NULL );

   L.Replace( "��", NULL );
   R.Replace( "��", NULL );

	 DC.Replace( " ", NULL );




         DC="<"+DC+">"; //ν����ϱ�ǩ







//------------



  R_IS_XRC = IS_XRC(R);

//------------



    a=YUAN->Find_name_return_ID(L); //�����Ƿ���һ�������Ԫ


     if(a==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,L);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


     new_YUAN_X->Contacts->Set_data(0,L); //���浽��ϵ������root��


     new_YUAN_X->Contacts->Add(DC+R,60); //���浽��ϵ��1��

	 }



     else //�����Ԫ
	 {

      new_YUAN_X=YUAN->ID_return_P(a);

          int Find_Contacts_N;

          Find_Contacts_N = new_YUAN_X->Contacts->Find_Data_Return_N(DC+R);

              if(Find_Contacts_N==-1) //ԭ�� û��������ϵ��Ϣ
               {
	            new_YUAN_X->Contacts->Add(DC+R,60);
               }
              else //ԭ�� ��������ϵ��Ϣ
               {

                 new_YUAN_X->Contacts->Set_weight_ADD(Find_Contacts_N,10); //ǿ����ϵ ����Ȩֵ����
				 r_flag=2;

               }

	 }





//------------

    b=YUAN->Find_name_return_ID(R); //�����Ƿ���һ�������Ԫ


     if(b==-1) //û�����Ԫ
	 {

	 //������Ԫ
     YUAN->New();
     new_YUAN_X=YUAN->ID_return_P(YUAN_ID_X);

     YUAN->Set_xy(new_YUAN_X->ID,Xrand(10,740),Xrand(20,590));
     YUAN->Set_name(new_YUAN_X->ID,R);

     YUAN->Set_threshold(new_YUAN_X->ID,50 + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;



     new_YUAN_X->Contacts->Set_data(0,R); //���浽��ϵ������root��


	 }

     else //�����Ԫ
	 {
          new_YUAN_X=YUAN->ID_return_P(b);

	 }




    if(R_IS_XRC==1) 
      {
       if(new_YUAN_X->Mark.Find("[��]")==-1)
         {
           new_YUAN_X->Mark = "[��]";
         }
           
      }







    return r_flag;



}






void CAiQiDlg::Form_Create_ZWB_EX(CString text) //���н����������⽨������
{

              int r=Form_Create_ZWB(text); //[��ʽ����] ��������  ��ʽ�� ��ס SνP  �� ��ס S


              if(r==1)  //1��������

                {


			      TEXT_OUT_BOX_SAY_3("Ŷ����ס�ˡ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				 }

              else if(r==2)  //2��ǰ�й�ϵǿ��

                {


			      TEXT_OUT_BOX_SAY_3("�����Ҿ���Ҳ�������ġ�",1); //��������Ļ�����
  
				  AI_YES_Flag=1;

				 }

			  else

			     {
                  TEXT_OUT_BOX_SAY_3("�﷨����",1); //��������Ļ�����

			     }


			


}











CString CAiQiDlg::Get_City_Weather_Number(CString CityName)  //���س�����������
{
  CString TT;
  CString A;
  int X_weizhi;

  if(CityName.IsEmpty()==1)
    {
      TT="û���ҵ�";
      return TT;
    }


  
  X_weizhi = City_Weather_Number.Find(CityName);

  if(X_weizhi==-1)
    {
     TT="û���ҵ�";
     
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









CString CAiQiDlg::Generate_Active_YUAN_List() //���ɻ�ԾԪ�б� һ����������ַ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

  CSettingsDlg  dlg;


  dlg.DoModal();

}






void CAiQiDlg::AUTO_Learning(int i) //�Զ�ѧϰ 
{

 if( AUTO_Learning_Flag != 1) return;

 if( YUAN_SUM == 0) return;

CString TX;  



 YUAN_UNIT *P_AUTO_Learning_select_YUAN;

TX.Format("һ���и���%d������ǰѡ��%d",YUAN_SUM,i);
 TEXT_OUT_BOX_SAY_3(TX,0); //��������Ļ�����


 P_AUTO_Learning_select_YUAN = YUAN->n_return_P(i);  //�õ����ѡ���Ԫ��ָ��

 if( P_AUTO_Learning_select_YUAN == NULL) {AUTO_Learning_Flag = 0; TEXT_OUT_BOX_SAY_3("����",0); return;}

 CString CT=P_AUTO_Learning_select_YUAN->name;
   

 CT.Replace( " ", NULL );

 int n = Learn_CiTiao_From_Web(CT); //��������ѧϰ������Ϣ

             

 TX.Format("����ѧϰ����[%s]��ϣ���ѧϰ��%d��������",CT,n);
 TEXT_OUT_BOX_SAY_3(TX,0); //��������Ļ�����


}









void CAiQiDlg::AUTO_Learning_2() //�Զ�ѧϰ 
{

 if( AUTO_Learning_Flag != 1) return;

 if( YUAN_SUM == 0) return;

CString TX;  

 int i=0;
 i=Xrand(1,YUAN_SUM); //���ѡȡһ������

 YUAN_UNIT *P_AUTO_Learning_select_YUAN;

//TX.Format("һ���и���%d������ǰѡ��%d",YUAN_SUM,i);
 //TEXT_OUT_BOX_SAY_3(TX,0); //��������Ļ�����


 P_AUTO_Learning_select_YUAN = YUAN->n_return_P(i);  //�õ����ѡ���Ԫ��ָ��

 if( P_AUTO_Learning_select_YUAN == NULL) {AUTO_Learning_Flag = 0; TEXT_OUT_BOX_SAY_3("����",0); return;}

 CString CT=P_AUTO_Learning_select_YUAN->name;
   

 CT.Replace( " ", NULL );

 int n = Learn_CiTiao_From_Web(CT); //��������ѧϰ������Ϣ

             

 TX.Format("����ѧϰ����[%s]��ϣ���ѧϰ��%d��������",CT,n);
 TEXT_OUT_BOX_SAY_3(TX,0); //��������Ļ�����


}







void CAiQiDlg::OnBnClickedButtonOnOnlineLearning()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������




   AUTO_Learning_Flag=1; //�Զ�ѧϰ��ʼ
   AUTO_Learning_Ready_Time=0;

//AUTO_Learning_i=1;
   TEXT_OUT_BOX_SAY_3("�Զ�ѧϰ��ʼ",0); //��������Ļ�����

}








void TEXT_INPUT_BOX_INIT()
{
 for(int n=0;n<TextInputBox_String_SUM;n++)
 {
  TextInputBox[n].text=_T(" ");



 }



}
















//����Ԫ����ǩ����ϵ������ ���ظ�����
bool CAiQiDlg::Find_YUAN_Contacts_Label_Data(CString YUAN_name , CString Label ,CString *YUAN_Data_List)
{

  YUAN_UNIT *tmp;

			 
  CONTACTS_UNIT *P_YUAN_Contacts;				 


  tmp=YUAN;


  CString Data_List;

  CString TT;

  Data_List.Empty();

  for(;;) //��������Ԫ
  {


    if(tmp->ID!=0) //0��Ԫ����
     {

      


       if(tmp->state==1 && tmp->name==YUAN_name)
         {

   //������ϵ��
   P_YUAN_Contacts=tmp->Contacts;



   for(;;)
   {

     if(P_YUAN_Contacts->data.Find(Label)!=-1) //�ҵ��˱�ǩ
	{
		


        TT=P_YUAN_Contacts->data;

         Split_X_String_Head("<"+Label+">",&TT); //ȥ��ǰ��ı�ǩ

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

   //������ϵ��end


          }




     }




    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //��������ԪEND



 if(Data_List.IsEmpty()!=1)
  {
   Format_String(&Data_List); //��ʽ���ַ��� ȥ������ո�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
  CAboutDlg  dlg;


  dlg.DoModal();

}
