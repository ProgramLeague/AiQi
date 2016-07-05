#include "YUAN_struct.h"


#ifndef LINK_system 
#define LINK_system



extern YUAN_UNIT *P_select_YUAN;  //被选择的元 指针
extern int select_linker_ID_1;      //被选择的连接起点元
extern int select_linker_ID_2;      //被选择的连接目标元
extern int select_linker_sum;   //选择连接的数量

extern bool show_info;  //显示调试信息
extern bool show_YUAN_E;  //显示元活跃强度值
extern bool show_YUAN_name;  //显示元的文本
extern float set_E_X;    //设置活跃启动效应增益值

extern bool run_try;  //运行尝试 随机数精灵

extern float set_try_E_X;    //设置尝试 随机数精灵选择后活跃增益值 

extern int Run_Learn;  //运行学习


extern int Run_Forgot;  //运行遗忘
extern int _Run_Forgot;  //运行遗忘





extern  bool AI_AUTO_Question_Flag; //自发提问标志
extern  bool AI_Feedback_Question_Flag; //反馈发问标志

extern  bool AUTO_Learning_Flag; //自动学习

extern bool Run_FC_Flag; //使用分词
extern bool Edit_Brain;  //可使用BrainBox编辑记忆文件


extern int YUAN_RUN_MAIN_Flag;

extern bool Auto_Load_And_Save_Memory_Flag;
extern CString Current_Memory_File_Name;//当前打开的记忆文件名

//-------------------------------------------------------

extern YUAN_UNIT *P_max_E_YUAN;     //最强活跃强度的元 指针

//extern float ZhuYi_threshold;    //注意的阀值





extern int test;  //测试

extern int MyDebugX;

//-------------------------------------------------------

//2D数学函数/////////////////////////////////////////////////////////////////////
void MOVE_TO3(int oa,int *PX,int *PY,int D);
int DZ(int X1,int Y1,int X2,int Y2) ;
int XDZ(int X1,int Y1,int X2,int Y2,int D);
void ASK_ABC(float x1,float y1,float x2,float y2,float *A,float *B,float *C);
void ASK_Q(float x1,float y1,float x2,float y2,float px,float py,float *Qx,float *Qy);
int ASK_PLD(float x1,float y1,float x2,float y2,float px,float py);
int InterLine(float fAx,float fAy,float fBx,float fBy,float fCx,float fCy,float fDx,float fDy);
int PLDX(int Ax,int Ay,int Bx,int By,int Px,int Py,int d);
int ASK_a(int X1,int Y1,int X2,int Y2);
bool Touch_box(int x1,int y1,int x2,int y2,int px,int py);
///////////////////////////////////////////////////////////////////////
extern int R;/*由当前系统时间产生真正的随机数种子*/
extern struct tm *t;
extern  time_t timer;


void init_rand();
int Xrand(int A,int B);




///////////////////////////////////////////////////////////////////////

void load_system_config_file(char filename[]);       //读取system配置文件

#endif
