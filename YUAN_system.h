#include "YUAN_struct.h"


#ifndef LINK_system 
#define LINK_system



extern YUAN_UNIT *P_select_YUAN;  //��ѡ���Ԫ ָ��
extern int select_linker_ID_1;      //��ѡ����������Ԫ
extern int select_linker_ID_2;      //��ѡ�������Ŀ��Ԫ
extern int select_linker_sum;   //ѡ�����ӵ�����

extern bool show_info;  //��ʾ������Ϣ
extern bool show_YUAN_E;  //��ʾԪ��Ծǿ��ֵ
extern bool show_YUAN_name;  //��ʾԪ���ı�
extern float set_E_X;    //���û�Ծ����ЧӦ����ֵ

extern bool run_try;  //���г��� ���������

extern float set_try_E_X;    //���ó��� ���������ѡ����Ծ����ֵ 

extern int Run_Learn;  //����ѧϰ


extern int Run_Forgot;  //��������
extern int _Run_Forgot;  //��������





extern  bool AI_AUTO_Question_Flag; //�Է����ʱ�־
extern  bool AI_Feedback_Question_Flag; //�������ʱ�־

extern  bool AUTO_Learning_Flag; //�Զ�ѧϰ

extern bool Run_FC_Flag; //ʹ�÷ִ�
extern bool Edit_Brain;  //��ʹ��BrainBox�༭�����ļ�


extern int YUAN_RUN_MAIN_Flag;

extern bool Auto_Load_And_Save_Memory_Flag;
extern CString Current_Memory_File_Name;//��ǰ�򿪵ļ����ļ���

//-------------------------------------------------------

extern YUAN_UNIT *P_max_E_YUAN;     //��ǿ��Ծǿ�ȵ�Ԫ ָ��

//extern float ZhuYi_threshold;    //ע��ķ�ֵ





extern int test;  //����

extern int MyDebugX;

//-------------------------------------------------------

//2D��ѧ����/////////////////////////////////////////////////////////////////////
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
extern int R;/*�ɵ�ǰϵͳʱ��������������������*/
extern struct tm *t;
extern  time_t timer;


void init_rand();
int Xrand(int A,int B);




///////////////////////////////////////////////////////////////////////

void load_system_config_file(char filename[]);       //��ȡsystem�����ļ�

#endif
