// AiQiDlg.h : 头文件
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




// CAiQiDlg 对话框
class CAiQiDlg : public CDialog
{
// 构造
public:
	CAiQiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);






public:


	//CFont m_editFont; //输入框字体
    //CEdit *pEdt;


	YUAN_UNIT *P_User_Answer_objective_YUAN;  //用户回答的目标元
	YUAN_UNIT *P_AUTO_Question_select_YUAN;  //自动提问选中的元

	YUAN_UNIT *P_layer_0_max_E_YUAN;   //层0最强活跃强度的元 指针
	YUAN_UNIT *P_layer_0_max_E_YUAN_AI_Think_Choose;  //AI选择后 层0最强活跃强度的元 保存 等待评价的  如果存在

	YUAN_UNIT *P_layer_1_max_E_YUAN;   //层1最强活跃强度的元 指针
	YUAN_UNIT *P_layer_1_max_E_YUAN_AI_Think_Choose;  //AI选择后 层1最强活跃强度的元 保存 等待评价的  如果存在

	YUAN_UNIT *P_layer_2_max_E_YUAN;   //层2最强活跃强度的元 指针
	YUAN_UNIT *P_layer_2_max_E_YUAN_AI_Think_Choose;  //AI选择后 层2最强活跃强度的元 保存 等待评价的  如果存在

	int AI_Think_Choose_Contacts_Number;//AI思考后选择的联系表的编号



    CString Last_Layer_0_Max_E_YUAN_Name; //最近一次最强活跃元的名称



  int AI_AUTO_Question_Ready_Time;  //自动提问
  int AI_AUTO_Question_Ready_MAX_Time;


  int AUTO_Learning_Ready_Time;  //自动学习
  int AUTO_Learning_Ready_MAX_Time;
  int AUTO_Learning_i;

CString FC_text; //中文分词


CString	input_text_0; //备份输入内容
CString	AI_Question_text; //电脑提问的字符串

  int Flow_run;
  bool Enter;

int Command_Flag; //命令语句标志


int Display_Startup_Message;  //显示启动信息

bool User_Answer_Flag;  //用户回答
int User_Answer_Time;
int User_Answer_MAX_Time;

bool Think_flag;    //AI思考
int Think_time;
int Think_MAX_time;

bool AI_YES_Flag; //肯定回答 完成
int AI_YES_Time;
int AI_YES_MAX_Time;

bool AI_NO_Flag;  //否定回答 未完成
int AI_NO_Time;
int AI_NO_MAX_Time;

bool AI_Happy_Flag; //奖励 高兴
int AI_Happy_Time;
int AI_Happy_MAX_Time;

bool AI_Sad_Flag;  //惩罚 伤心
int AI_Sad_Time;
int AI_Sad_MAX_Time;

bool AI_Welcome_Flag;  //启动 欢迎
int AI_Welcome_Time;
int AI_Welcome_MAX_Time;


bool AI_Have_Feelings_Flag;  //有感觉
int AI_Have_Feelings_Time;
int AI_Have_Feelings_MAX_Time;



bool Waiting_For_Assessment_Flag; //等待评估 回答
int Waiting_For_Assessment_Time;
int Waiting_For_Assessment_MAX_Time;


int AI_do_not_know; //AI不知道答案

int AI_Question_Kind; //电脑提问的类型 1对元存储的字符串提问    2对于用户输入的字符串提问



CString CK_DC;    //逻辑处理中用的 动词词库
CString CK_SXBQ;  //逻辑处理中用的 属性标签
CString CK_XRC;   //逻辑处理中用的 形容词词库

CString City_Weather_Number; //城市天气代码

////////




void Inhibitory_Layer_YUAN(int Layer); //抑制某层的所有元

CString String_mc_format(CString text); //把用[]框起来的特殊名词格式化 分词后整理

CString ZWFC(CString text); //中文分词

void Format_String(CString *_text); //格式化字符串 去掉空格 和 *


int Return_String_Words_Sum(CString text); //返回字符串中单词的数量

void Return_String_SN_start_end(CString text,int SN,int *SN_start,int *SN_end); //返回字符串中 第SN个单词 偏移的地址 开始 结束

CString Return_String_N_Word(CString text,int i); //返回字符串第N个单词

CString Format_De_CString(CString text); //格式化带“的”字的字符串，并且去除“的”

CString Format_XRC_De_CString(CString text); //格式化字符串中形容词的“的”，去除“的”



//用户回答  让电脑选择的（提问）元 和 用户的回答的词语之间建立联系
void User_Answer_YUAN_Is( YUAN_UNIT *S_YUAN, CString text);




void Activation_YUAN(CString text,int power); //激活某个元

void Activation_Text_YUAN(CString text); //激活字符串里的所有元

void Inhibit_YUAN(CString text,int power); //抑制某个元

//查找指定某元的联系表数据 抑制以“text”标签开头的字符相关元
void Find_YUAN_Contacts_Label_Inhibit_YUAN(YUAN_UNIT *YUAN_p,CString text,int power); 

void Recognition_Command(int *Command_Flag,CString *input_text);  //识别语句命令


void TEXT_OUT_BOX_SAY_3(CString text,int flag); //数据在屏幕上输出


//我的RichEdit控件输出
void MyRichEdit_TextOut(CRichEditCtrl *PMyRichEdit,unsigned long color,int size,int bold,CString str);


void AUTO_Question_2(); //自动提问2  对元存储的字符串提问


void MyDebug(); //我的DeBug

void OnEnter(); //按了回车键的响应



void Split_X_String(CString S_CString,CString X_CString,CString *D_CString1,CString *D_CString2); //把字符串以X为分割，变成2个字符窜

void Split_X_String_Head(CString X_CString,CString *S_CString); //把字符串以X为头分割 取后面部分

//删除字符串第N个词，并且返回它  必须先分词
bool CAiQiDlg::Del_String_N_Word(CString *SX,int N);








//形式处理  带“是”的字符串   通过创生概念层1的元  联系字符与字符 （建立了X是Y的概念） 比如： 圆的 红的 甜的 是 苹果
int Form_Is_4(CString text);


//形式处理  记忆字符串 生成一个概念 重复输入可加强连接
int Form_Remember_X(CString text);

//形式处理  记忆字符串 生成一个概念 重复输入可加强连接  复合名词 功能强化
int Form_Remember_X2(CString text);


//[形式处理] 建立命题   主体属性连接(法)建立函数    格式： 记住 S谓P  、 记住 S
int Form_Create_Proposition_X(CString text);

//[形式处理] 建立命题   主体属性连接(法)建立函数    格式： 记住 S谓P  、 记住 S
int Form_Create_Proposition_X2(CString text);




//[形式处理] 建立反射关系   如果x那么Y  ，建立一个条件反射关系概念，输入X输出Y
int Form_IF_THEN_X(CString text);

//[形式处理] 建立反射关系   如果x那么Y  ，建立一个条件反射关系概念，输入X输出Y
int Form_IF_THEN_X2(CString text);

//[形式处理] 建立反射关系   如果x那么Y  ，建立一个条件反射关系概念，输入X输出Y
int CAiQiDlg::Form_IF_X_THEN_Y(CString text);

 //[形式处理] 建立X概念 问与答关系  X概念生成一条文本数据用来回答
void Form_X_QA(CString text1, CString text2);  

//[形式处理] 建立上下文关系，输入X输出Y
int Form_ShangXiaWen(CString text); 


//[形式处理] 建立X是Y关系  生成两个独立的概念
void Form_X_IS_Y(CString X,CString Y); 






CString Generate_Active_YUAN_List(); //生成活跃元列表 一组概念名的字符串



void Return_Award_To_AI(YUAN_UNIT *X_YUAN);  //奖励AI  对最强选择元的肯定
void Return_Punishment_To_AI(YUAN_UNIT *X_YUAN);  //惩罚AI  对最强选择元的否定


//奖励AI  对最强选择元的 联系表输出肯定
void Return_Award_To_AI_X(YUAN_UNIT *X_YUAN,int n);  

//惩罚AI  对最强选择元的 联系表输出否定
void Return_Punishment_To_AI_X(YUAN_UNIT *X_YUAN,int n);  



//命令：显示元的数据
void Cmd_Display_YUAN_Data( CString text);

//命令：删除元
void Cmd_Del_YUAN( CString text);

//命令：删除元数据
void Cmd_Del_YUAN_Contacts( CString text,int Contacts_ID);



//识别主谓宾语句格式
int Recognition_ZWB_Form(CString text);


//[形式处理] 建立主谓宾关系 可识别名词形容词 加上词性标签
int Form_Create_ZWB(CString text);


void Form_Create_ZWB_EX(CString text); //带有结果输出的命题建立函数



void YUAN_RUN_MAIN();


void Draw_Face(int x, int y,int Kind,CDC *pDC); //画表情
void Change_Face(int x, int y,CDC *pDC); //变表情


//加载TXT文件到字符串
void TxtFileRead_to_CString(CString FileName,CString *CStr);

//是否是动词 和动词词库中的词语比较
bool IS_DC(CString str);


//查找文本中的第一个动词，并且返回它
bool Find_Text_DC(CString text,CString *DC);



//是否是形容词 和形容词词库中的词语比较
bool IS_XRC(CString str);




//是否是属性 和属性词库中的词语比较
bool IS_SXBQ(CString str);

//识别带标签记忆的建立语句格式
int Recognition_SXBQ_Form(CString text);


//标签记忆的建立函数
int Form_Create_SXBQ(CString text); 

//带有结果的标签记忆的建立函数
void Form_Create_SXBQ_EX(CString text);


//查找文本中的第一个属性，并且返回它  必须先分词
int Find_Text_SXBQ(CString text,CString *SX);


//对两个字符串相似度打分
int Assess_To_Two_String(CString S,CString D);


void Input_Activation_YUAN(CString text);  //输入激活元

void Input_Activation_YUAN_By_Contacts(CString text);  //通过对输入的字符串和元联系表评分，来增加元活跃度
void Input_Activation_YUAN_By_Contacts_2(CString text);  //通过对输入的字符串和元数据比较，来增加元活跃度，比较[是]标签

//查找最相似的联系表数据 返回该数据 和 元指针 有状态限制
void Find_YUAN_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts);

 //查找最相似的联系表数据 返回该数据 和 元指针 没有状态限制
void Find_YUAN_X_Contacts(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts); 

  //查找最相似的联系表数据 返回该数据 和 元指针 没有状态限制 查找联系表里的动词短语
void Find_YUAN_X_Contacts_DC(CString text,int sspf,YUAN_UNIT **YUAN_p,CString *YUAN_Contacts,CString DC);

//查找指定某元的联系表数据 激活以“text”标签标签的字符相关元
void Find_YUAN_Contacts_Label_Activation_YUAN(YUAN_UNIT *YUAN_p,CString text,int power);


//查找元带标签的联系表数据 返回该数据
bool Find_YUAN_Contacts_Label_Data(CString YUAN_name , CString Label ,CString *YUAN_Data_List);


//-------------
CString CString_Extraction_Content(CString text,CString a,CString b);   //字符串提取中间内容
CString Get_CiTiao_Information_From_Web(CString CiTiao); //从网络上获取词条信息并返回
int Learn_CiTiao_From_Web(CString CiTiao); //从网络上学习词条信息

//-------------
CString Get_Weather_Information_From_Web(CString city_number); //从网络上获取天气信息并返回


//-------------脚本部分

void Run_YUAN_Contacts_Data(CString Data); //运行一条概念单元意义表数据

void Run_Script(CString Data); //运行脚本

void Scr_Command_Out_Text(CString Command);
void Scr_Command_Open_Web(CString Command);
void Scr_Command_Weather_Forecast(CString Command);

void Run_Scr_Command(CString Command); //根据命令选择执行脚本


//-------------
void Display_AUTO_Question_Time(int x, int y,int Time,int MAX_Time,CDC *pDC); //显示自动提问时间
CString Get_City_Weather_Number(CString CityName);  //返回城市天气代码

//-------------



void AUTO_Learning(int i); //自动学习
void AUTO_Learning_2(); //自动学习



afx_msg void OnBnClickedButton1();
virtual BOOL PreTranslateMessage(MSG* pMsg);
//CEdit m_edit;
CString MainTextOut;
CString input_text;
afx_msg void OnBnClickedButtonOnBrainbox();
CRichEditCtrl MyRichEdit;

afx_msg void OnFileRead_ChatLibrary(); //读取语料库文件
afx_msg void OnDestroy();
afx_msg void OnBnClickedButtonSetting();
afx_msg void OnBnClickedButtonOnOnlineLearning();
afx_msg void OnBnClickedButtonHelp();
};
