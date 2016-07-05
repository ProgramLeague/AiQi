#include "LINK_struct.h"
#include "Contacts_Struct.h"


#ifndef YUAN_struct 
#define YUAN_struct





struct YUAN_UNIT{ 
	              int ID;
                  int data;//数据域
                  int x;
				  int y;
                  CString name;

                  CString Mark;

				  int state;
				  float threshold; //阈值

				  float E;   //活跃强度值
				  float E_X; //活跃强度增益值 是一个不断变化的状态值，0稳定

				  int A_time;

				  int Wait_Start_Time;

				  float fag;    //疲劳值

				  int Layer; //元的层级变量  

				  int Learn_Ready_Time;//学习准备时间


				  LINK_UNIT *linker;
				  CONTACTS_UNIT *Contacts;

                  YUAN_UNIT *next;//指针域

                  YUAN_UNIT *ID_return_P(int ID);
                  YUAN_UNIT *n_return_P(int n);
				  YUAN_UNIT *name_return_P(CString name);

                  void Init();

				  void New();
				  void Set_xy(int ID,int x,int y);
                  void Set_data(int ID,int data);
                  void Set_name(int ID,CString name);

				  void Set_state(int ID,int state);
				  void Set_threshold(int ID,float threshold);
                  void Set_Layer(int ID,int Layer);

                  void Set_E_X(int ID,float E_X);
				  void Add_E_X(int ID,float E_X);

				  void Del_a_link(int ID1,int ID2);
				  void Del_ID_all_link(int ID);
				  void Del_ID(int ID);

				  void Linker_Weight_Change(int ID1,int ID2,float Change);  //变化 元ID1 到 ID2 的连接权值

				  bool Find_ID(int ID);
                  int Find_name_return_ID(CString name);
                  bool Find_linker(int ID1,int ID2);  //查找元ID1 到 ID2 的连接是否存在

				  int Find_max_E_ID();
                  YUAN_UNIT *Find_max_E_YUAN_P(float threshold,int mix_layer);
				  YUAN_UNIT *Find_layer_max_E_YUAN_P(float threshold,int Layer);


				  void Link(int ID_1,int ID_2,float weight);
                  void Set_linker_weight(int ID_1,int ID_2,float weight);
                  void Set_linker_weight_ADD(int ID_1,int ID_2,float ADD);
                  float Get_linker_weight(int ID1,int ID2); 




                  void Get_Link_List(int ID,CString *LL,int *sum);//得到某ID的元,连接其他元的联系表和数量


                  void Add_Contacts(CString text);  //增加 元的一条联系表内容
                  void Del_Contacts(CString text);  //删除 元的一条联系表内容
                  void Set_Contacts(CString text);  //修改 元的一条联系表内容

                  void  Set_Mark(int ID,CString Mark_Text);

                  void Learning();

                  void FreeAll(YUAN_UNIT *root);




				};



extern YUAN_UNIT *YUAN;

extern int YUAN_ID_X;                     //记录命名的ID变化
extern int YUAN_SUM;                      //记录元的总数
extern int YUAN_Layer_SUM[8];             //记录每层元的总数
extern int YUAN_CONTACTS_SUM;            //记录元的联系表总数

extern int A_time_max;                 //元激活持续总时间
extern int Wait_Start_Time_MAX;   //元等待激活时间
extern float LE;                       //连接强度的增加值,学习效率
extern float WL;                       //连接强度上增加的  元F值的比率
extern float fag_add;             //元疲劳值增加的数值
extern float fag_minus;           //元疲劳值减少的数值
extern float E_minus;   // 反应强度衰减

extern int Learn_Ready_Time_MAX; //学习强化准备时间
extern float Forgot_Weight;           //遗忘量

void load_YUAN_config_file(char filename[]);       //读取YUAN配置文件




#endif