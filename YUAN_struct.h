#include "LINK_struct.h"
#include "Contacts_Struct.h"


#ifndef YUAN_struct 
#define YUAN_struct





struct YUAN_UNIT{ 
	              int ID;
                  int data;//������
                  int x;
				  int y;
                  CString name;

                  CString Mark;

				  int state;
				  float threshold; //��ֵ

				  float E;   //��Ծǿ��ֵ
				  float E_X; //��Ծǿ������ֵ ��һ�����ϱ仯��״ֵ̬��0�ȶ�

				  int A_time;

				  int Wait_Start_Time;

				  float fag;    //ƣ��ֵ

				  int Layer; //Ԫ�Ĳ㼶����  

				  int Learn_Ready_Time;//ѧϰ׼��ʱ��


				  LINK_UNIT *linker;
				  CONTACTS_UNIT *Contacts;

                  YUAN_UNIT *next;//ָ����

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

				  void Linker_Weight_Change(int ID1,int ID2,float Change);  //�仯 ԪID1 �� ID2 ������Ȩֵ

				  bool Find_ID(int ID);
                  int Find_name_return_ID(CString name);
                  bool Find_linker(int ID1,int ID2);  //����ԪID1 �� ID2 �������Ƿ����

				  int Find_max_E_ID();
                  YUAN_UNIT *Find_max_E_YUAN_P(float threshold,int mix_layer);
				  YUAN_UNIT *Find_layer_max_E_YUAN_P(float threshold,int Layer);


				  void Link(int ID_1,int ID_2,float weight);
                  void Set_linker_weight(int ID_1,int ID_2,float weight);
                  void Set_linker_weight_ADD(int ID_1,int ID_2,float ADD);
                  float Get_linker_weight(int ID1,int ID2); 




                  void Get_Link_List(int ID,CString *LL,int *sum);//�õ�ĳID��Ԫ,��������Ԫ����ϵ�������


                  void Add_Contacts(CString text);  //���� Ԫ��һ����ϵ������
                  void Del_Contacts(CString text);  //ɾ�� Ԫ��һ����ϵ������
                  void Set_Contacts(CString text);  //�޸� Ԫ��һ����ϵ������

                  void  Set_Mark(int ID,CString Mark_Text);

                  void Learning();

                  void FreeAll(YUAN_UNIT *root);




				};



extern YUAN_UNIT *YUAN;

extern int YUAN_ID_X;                     //��¼������ID�仯
extern int YUAN_SUM;                      //��¼Ԫ������
extern int YUAN_Layer_SUM[8];             //��¼ÿ��Ԫ������
extern int YUAN_CONTACTS_SUM;            //��¼Ԫ����ϵ������

extern int A_time_max;                 //Ԫ���������ʱ��
extern int Wait_Start_Time_MAX;   //Ԫ�ȴ�����ʱ��
extern float LE;                       //����ǿ�ȵ�����ֵ,ѧϰЧ��
extern float WL;                       //����ǿ�������ӵ�  ԪFֵ�ı���
extern float fag_add;             //Ԫƣ��ֵ���ӵ���ֵ
extern float fag_minus;           //Ԫƣ��ֵ���ٵ���ֵ
extern float E_minus;   // ��Ӧǿ��˥��

extern int Learn_Ready_Time_MAX; //ѧϰǿ��׼��ʱ��
extern float Forgot_Weight;           //������

void load_YUAN_config_file(char filename[]);       //��ȡYUAN�����ļ�




#endif