// AiQiDlg.h : ͷ�ļ�
//
#include "YUAN_struct.h"	// Added by ClassView
#pragma once#include "afxwin.h"
#include "afxcmn.h"








#define TextInputBox_String_SUM 3




class TEXT_INPUT_BOX
{ 

 public:


 CString text;


};


extern TEXT_INPUT_BOX TextInputBox[ TextInputBox_String_SUM ];

void TEXT_INPUT_BOX_INIT();




// CAiQiDlg �Ի���
class CAiQiDlg : public CDialog
{
// ����
public:
	CAiQiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);






public:


	//CFont m_editFont; //���������
    //CEdit *pEdt;


	YUAN_UNIT *P_User_Answer_objective_YUAN;  //�û��ش��Ŀ��Ԫ
	YUAN_UNIT *P_AUTO_Question_select_YUAN;  //�Զ�����ѡ�е�Ԫ

	YUAN_UNIT *P_layer_0_max_E_YUAN;   //��0��ǿ��Ծǿ�ȵ�Ԫ ָ��
	YUAN_UNIT *P_layer_0_max_E_YUAN_AI_Think_Choose;  //AIѡ��� ��0��ǿ��Ծǿ�ȵ�Ԫ ���� �ȴ����۵�  �������

	YUAN_UNIT *P_layer_1_max_E_YUAN;   //��1��ǿ��Ծǿ�ȵ�Ԫ ָ��
	YUAN_UNIT *P_layer_1_max_E_YUAN_AI_Think_Choose;  //AIѡ��� ��1��ǿ��Ծǿ�ȵ�Ԫ ���� �ȴ����۵�  �������

	YUAN_UNIT *P_layer_2_max_E_YUAN;   //��2��ǿ��Ծǿ�ȵ�Ԫ ָ��
	YUAN_UNIT *P_layer_2_max_E_YUAN_AI_Think_Choose;  //AIѡ��� ��2��ǿ��Ծǿ�ȵ�Ԫ ���� �ȴ����۵�  �������

	int AI_Think_Choose_Contacts_Number;//AI˼����ѡ�����ϵ��ı��



    CString Last_Layer_0_Max_E_YUAN_Name; //���һ����ǿ��ԾԪ������



  int AI_AUTO_Question_Ready_Time;  //�Զ�����
  int AI_AUTO_Question_Ready_MAX_Time;


  int AUTO_Learning_Ready_Time;  //�Զ�ѧϰ
  int AUTO_Learning_Ready_MAX_Time;
  int AUTO_Learning_i;

CString FC_text; //���ķִ�


CString	input_text_0; //������������
CString	AI_Question_text; //�������ʵ��ַ���

  int Flow_run;
  bool Enter;

int Command_Flag; //��������־


int Display_Startup_Message;  //��ʾ������Ϣ

bool User_Answer_Flag;  //�û��ش�
int User_Answer_Time;
int User_Answer_MAX_Time;

bool Think_flag;    //AI˼��
int Think_time;
int Think_MAX_time;

bool AI_YES_Flag; //�϶��ش� ���
int AI_YES_Time;
int AI_YES_MAX_Time;

bool AI_NO_Flag;  //�񶨻ش� δ���
int AI_NO_Time;
int AI_NO_MAX_Time;

bool AI_Happy_Flag; //���� ����
int AI_Happy_Time;
int AI_Happy_MAX_Time;

bool AI_Sad_Flag;  //�ͷ� ����
int AI_Sad_Time;
int AI_Sad_MAX_Time;

bool AI_Welcome_Flag;  //���� ��ӭ
int AI_Welcome_Time;
int AI_Welcome_MAX_Time;


bool AI_Have_Feelings_Flag;  //�ио�
int AI_Have_Feelings_Time;
int AI_Have_Feelings_MAX_Time;



bool Waiting_For_Assessment_Flag; //�ȴ����� �ش�
int Waiting_For_Assessment_Time;
int Waiting_For_Assessment_MAX_Time;


int AI_do_not_know; //AI��֪����

int AI_Question_Kind; //�������ʵ����� 1��Ԫ�洢���ַ�������    2�����û�������ַ�������



CString CK_DC;    //�߼��������õ� ���ʴʿ�
CString CK_SXBQ;  //�߼��������õ� ���Ա�ǩ
CString CK_XRC;   //�߼��������õ� ���ݴʴʿ�

CString City_Weather_Number; //������������

////////




void Inhibitory_Layer_YUAN(int Layer); //����ĳ�������Ԫ

CString String_mc_format(CString text); //����[]���������������ʸ�ʽ�� �ִʺ�����

CString ZWFC(CString text); //���ķִ�

void Format_String(CString *_text); //��ʽ���ַ��� ȥ���ո� �� *


int Return_String_Words_Sum(CString text); //�����ַ����е��ʵ�����

void Return_String_SN_start_end(CString text,int SN,int *SN_start,int *SN_end); //�����ַ����� ��SN������ ƫ�Ƶĵ�ַ ��ʼ ����

CString Return_String_N_Word(CString text,int i); //�����ַ�����N������

CString Format_De_CString(CString text); //��ʽ�������ġ��ֵ��ַ���������ȥ�����ġ�

CString Format_XRC_De_CString(CString text); //��ʽ���ַ��������ݴʵġ��ġ���ȥ�����ġ�



//�û��ش�  �õ���ѡ��ģ����ʣ�Ԫ �� �û��Ļش�Ĵ���֮�佨����ϵ
void User_Answer_YUAN_Is( YUAN_UNIT *S_YUAN, CString text);




void Activation_YUAN(CString text,int power); //����ĳ��Ԫ

void Activation_Text_YUAN(CString text); //�����ַ����������Ԫ

void Inhibit_YUAN(CString text,int power); //����ĳ��Ԫ

//����ָ��ĳԪ����ϵ������ �����ԡ�text����ǩ��ͷ���ַ����Ԫ
void Find_YUAN_Contacts_Label_Inhibit_YUAN(YUAN_UNIT *YUAN_p,CString text,int power); 

void Recognition_Command(int *Command_Flag,CString *input_text);  //ʶ���������


void TEXT_OUT_BOX_SAY_3(CString text,int flag); //��������Ļ�����


//�ҵ�RichEdit�ؼ����
void MyRichEdit_TextOut(CRichEditCtrl *PMyRichEdit,unsigned long color,int size,int bold,CString str);


void AUTO_Question_2(); //�Զ�����2  ��Ԫ�洢���ַ�������


void MyDebug(); //�ҵ�DeBug

void OnEnter(); //���˻س�������Ӧ



void Split_X_String(CString S_CString,CString X_CString,CString *D_CString1,CString *D_CString2); //���ַ�����XΪ�ָ���2���ַ���

void Split_X_String_Head(CString X_CString,CString *S_CString); //���ַ�����XΪͷ�ָ� ȡ���沿��

//ɾ���ַ�����N���ʣ����ҷ�����  �����ȷִ�
bool CAiQiDlg::Del_String_N_Word(CString *SX,int N);








//��ʽ����  �����ǡ����ַ���   ͨ�����������1��Ԫ  ��ϵ�ַ����ַ� ��������X��Y�ĸ�� ���磺 Բ�� ��� ��� �� ƻ��
int Form_Is_4(CString text);


//��ʽ����  �����ַ��� ����һ������ �ظ�����ɼ�ǿ����
int Form_Remember_X(CString text);

//��ʽ����  �����ַ��� ����һ������ �ظ�����ɼ�ǿ����  �������� ����ǿ��
int Form_Remember_X2(CString text);


//[��ʽ����] ��������   ������������(��)��������    ��ʽ�� ��ס SνP  �� ��ס S
int Form_Create_Proposition_X(CString text);

//[��ʽ����] ��������   ������������(��)��������    ��ʽ�� ��ס SνP  �� ��ס S
int Form_Create_Proposition_X2(CString text);




//[��ʽ����] ���������ϵ   ���x��ôY  ������һ�����������ϵ�������X���Y
int Form_IF_THEN_X(CString text);

//[��ʽ����] ���������ϵ   ���x��ôY  ������һ�����������ϵ�������X���Y
int Form_IF_THEN_X2(CString text);

//[��ʽ����] ���������ϵ   ���x��ôY  ������һ�����������ϵ�������X���Y
int CAiQiDlg::Form_IF_X_THEN_Y(CString text);

 //[��ʽ����] ����X���� ������ϵ  X��������һ���ı����������ش�
void Form_X_QA(CString text1, CString text2);  

//[��ʽ����] ���������Ĺ�ϵ������X���Y
int Form_ShangXiaWen(CString text); 


//[��ʽ����] ����X��Y��ϵ  �������������ĸ���
void Form_X_IS_Y(CString X,CString Y); 






CString Generate_Active_YUAN_List(); //���ɻ�ԾԪ�б� һ����������ַ���



void Return_Award_To_AI(YUAN_UNIT *X_YUAN);  //����AI  ����ǿѡ��Ԫ�Ŀ϶�
void Return_Punishment_To_AI(YUAN_UNIT *X_YUAN);  //�ͷ�AI  ����ǿѡ��Ԫ�ķ�


//����AI  ����ǿѡ��Ԫ�� ��ϵ������϶�
void Return_Award_To_AI_X(YUAN_UNIT *X_YUAN,int n);  

//�ͷ�AI  ����ǿѡ��Ԫ�� ��ϵ�������
void Return_Punishment_To_AI_X(YUAN_UNIT *X_YUAN,int n);  



//�����ʾԪ������
void Cmd_Display_YUAN_Data( CString text);

//���ɾ��Ԫ
void Cmd_Del_YUAN( CString text);

//���ɾ��Ԫ����
void Cmd_Del_YUAN_Contacts( CString text,int Contacts_ID);



//ʶ����ν������ʽ
int Recognition_ZWB_Form(CString text);


//[��ʽ����] ������ν����ϵ ��ʶ���������ݴ� ���ϴ��Ա�ǩ
int Form_Create_ZWB(CString text);


void Form_Create_ZWB_EX(CString text); //���н����������⽨������



void YUAN_RUN_MAIN();


void Draw_Face(int x, int y,int Kind,CDC *pDC); //������
void Change_Face(int x, int y,CDC *pDC); //�����


//����TXT�ļ����ַ���
void TxtFileRead_to_CString(CString FileName,CString *CStr);

//�Ƿ��Ƕ��� �Ͷ��ʴʿ��еĴ���Ƚ�
bool IS_DC(CString str);


//�����ı��еĵ�һ�����ʣ����ҷ�����
bool Find_Text_DC(CString text,CString *DC);



//�Ƿ������ݴ� �����ݴʴʿ��еĴ���Ƚ�
bool IS_XRC(CString str);




//�Ƿ������� �����Դʿ��еĴ���Ƚ�
bool IS_SXBQ(CString str);

//ʶ�����ǩ����Ľ�������ʽ
int Recognition_SXBQ_Form(CString text);


//��ǩ����Ľ�������
int Form_Create_SXBQ(CString text); 

//���н���ı�ǩ����Ľ�������
void Form_Create_SXBQ_EX(CString text);


//�����ı��еĵ�һ�����ԣ����ҷ�����  �����ȷִ�
int Find_Text_SXBQ(CString text,CString *SX);


//�������ַ������ƶȴ��
int Assess_To_Two_String(CString S,CString D);


void Input_Activation_YUAN(CString text);  //���뼤��Ԫ

void Input_Activation_YUAN_By_Contacts(CString text);  //ͨ����������ַ�����Ԫ��ϵ�����֣�������Ԫ��Ծ��
void Input_Activation_YUAN_By_Contacts_2(CString text);  //ͨ����������ַ�����Ԫ���ݱȽϣ�������Ԫ��Ծ�ȣ��Ƚ�[��]��ǩ

//���������Ƶ���ϵ������ ���ظ����� �� Ԫָ�� ��״̬����
void Find_YUAN_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts);

 //���������Ƶ���ϵ������ ���ظ����� �� Ԫָ�� û��״̬����
void Find_YUAN_X_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts); 

  //���������Ƶ���ϵ������ ���ظ����� �� Ԫָ�� û��״̬���� ������ϵ����Ķ��ʶ���
void Find_YUAN_X_Contacts_DC(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts,CString DC);

//����ָ��ĳԪ����ϵ������ �����ԡ�text����ǩ��ǩ���ַ����Ԫ
void Find_YUAN_Contacts_Label_Activation_YUAN(YUAN_UNIT *YUAN_p,CString text,int power);


//����Ԫ����ǩ����ϵ������ ���ظ�����
bool Find_YUAN_Contacts_Label_Data(CString YUAN_name , CString Label ,CString *YUAN_Data_List);


//-------------
CString CString_Extraction_Content(CString text,CString a,CString b);   //�ַ�����ȡ�м�����
CString Get_CiTiao_Information_From_Web(CString CiTiao); //�������ϻ�ȡ������Ϣ������
int Learn_CiTiao_From_Web(CString CiTiao); //��������ѧϰ������Ϣ

//-------------
CString Get_Weather_Information_From_Web(CString city_number); //�������ϻ�ȡ������Ϣ������


//-------------�ű�����

void Run_YUAN_Contacts_Data(CString Data); //����һ�����Ԫ���������

void Run_Script(CString Data); //���нű�

void Scr_Command_Out_Text(CString Command);
void Scr_Command_Open_Web(CString Command);
void Scr_Command_Weather_Forecast(CString Command);

void Run_Scr_Command(CString Command); //��������ѡ��ִ�нű�


//-------------
void Display_AUTO_Question_Time(int x, int y,int Time,int MAX_Time,CDC *pDC); //��ʾ�Զ�����ʱ��
CString Get_City_Weather_Number(CString CityName);  //���س�����������

//-------------



void AUTO_Learning(int i); //�Զ�ѧϰ
void AUTO_Learning_2(); //�Զ�ѧϰ



afx_msg void OnBnClickedButton1();
virtual BOOL PreTranslateMessage(MSG* pMsg);
//CEdit m_edit;
CString MainTextOut;
CString input_text;
afx_msg void OnBnClickedButtonOnBrainbox();
CRichEditCtrl MyRichEdit;

afx_msg void OnFileRead_ChatLibrary(); //��ȡ���Ͽ��ļ�
afx_msg void OnDestroy();
afx_msg void OnBnClickedButtonSetting();
afx_msg void OnBnClickedButtonOnOnlineLearning();
afx_msg void OnBnClickedButtonHelp();
};
