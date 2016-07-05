

#include "stdafx.h"
#include "YUAN_system.h"


#include <math.h>
#include <dos.h>
#include <time.h>


YUAN_UNIT *P_select_YUAN=NULL;     //��ѡ���Ԫ ָ��
int select_linker_ID_1=-1;         //��ѡ����������Ԫ
int select_linker_ID_2=-1;         //��ѡ�������Ŀ��Ԫ
int select_linker_sum=0;          //ѡ�����ӵ�����

bool show_info=FALSE;  //��ʾ������Ϣ
bool show_YUAN_E=TRUE;  //��ʾԪ��Ծǿ��ֵ
bool show_YUAN_name=TRUE;  //��ʾԪ������
float set_E_X=100;    //���û�Ծ����ЧӦ����ֵ


bool run_try=1;  //���г���

float set_try_E_X=0;    //���ó���ѡ�������ֵ

YUAN_UNIT *P_max_E_YUAN=NULL;     //��ǿ��Ծǿ�ȵ�Ԫ ָ��

//float ZhuYi_threshold=100;    //ע��ķ�ֵ

int Run_Learn=0;  //����ѧϰ

int Run_Forgot=0;  //��������
int _Run_Forgot=0;  //��������


 bool AUTO_Learning_Flag = 0;; //�Զ�ѧϰ

 bool AI_AUTO_Question_Flag = 0;
 bool AI_Feedback_Question_Flag = 0;


int MyDebugX;

 bool Run_FC_Flag = 1;
 bool Edit_Brain = 0; //�༭BrainBox

 int YUAN_RUN_MAIN_Flag=1;


 bool Auto_Load_And_Save_Memory_Flag = 1;
 CString Current_Memory_File_Name = _T("");//��ǰ�򿪵ļ����ļ���

int test=0;  //����



/////////////////////////////////2D��ѧ����////////////////////////////////////
#define PI 3.1415

void MOVE_TO3(int oa,int *PX,int *PY,int D)  /*�ƶ���*/
{
  double px=*PX,py=*PY;

 px+=D*cos(oa*PI/180);
 py+=D*sin(oa*PI/180);

 *PX=(int)px;
 *PY=(int)py;

}




int Round(float x)  /*��������*/
{
 return((int)(x+0.5));
}



int DZ(int X1,int Y1,int X2,int Y2)  /*�������*/
{

 return  (int)  sqrt( fabs((float)((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1))));
}


int XDZ(int X1,int Y1,int X2,int Y2,int D)
{
 if(abs(X1-X2)<=D && abs(Y1-Y2)<=D) return 1;
 else return 0;

}



void ASK_ABC(float x1,float y1,float x2,float y2,float *A,float *B,float *C)  /*���ABC*/
{


 /*ֱ�ߵ�һ�㷽��ʽ AX+BY+C=0 */
 *A=y2-y1;
 *B=x1-x2;
 *C=y1*(x2-x1)-x1*(y2-y1);

}




void ASK_Q(float x1,float y1,float x2,float y2,float px,float py,float *Qx,float *Qy)  /*��㵽ֱ�ߵĴ�������*/
{
 float A,B,C;

 /*ֱ�ߵ�һ�㷽��ʽ AX+BY+C=0 */
 A=y2-y1;
 B=x1-x2;
 C=y1*(x2-x1)-x1*(y2-y1);

 *Qx=(B*B*px-A*B*py-A*C)/(A*A+B*B);
 *Qy=(-A*B*px+A*A*py-B*C)/(A*A+B*B);

}





int ASK_PLD(float x1,float y1,float x2,float y2,float px,float py)  /*��㵽ֱ�ߵľ���*/
{
 float A,B,C;
 float d;


 ASK_ABC(x1,y1,x2,y2,&A,&B,&C);

 /*ֱ�ߵ�һ�㷽��ʽ AX+BY+C=0 */


 d=(float) fabs( (A*px+B*py+C) / sqrt(A*A+B*B) );   /*�㵽ֱ�ߵľ���*/


 Round(d);


 return((int)d);

}









int InterLine(float fAx,float fAy,float fBx,float fBy,float fCx,float fCy,float fDx,float fDy) /*�ж���ֱ���ཻ*/
{


float x,y; /*����*/


float fLineAMinx;
float fLineAMiny;
float fLineAMaxx;
float fLineAMaxy;

float fLineBMinx;
float fLineBMiny;
float fLineBMaxx;
float fLineBMaxy;

float A1,B1,C1, A2,B2,C2;




ASK_ABC(fAx,fAy,fBx,fBy,&A1,&B1,&C1);
ASK_ABC(fCx,fCy,fDx,fDy,&A2,&B2,&C2);


if(A1*B2-A2*B1==0)
return 0;



x=-((C1*B2-C2*B1)/(A1*B2-A2*B1));
y=-((A1*C2-A2*C1)/(A1*B2-A2*B1));





fLineAMinx = fAx;
fLineAMiny = fAy;
fLineAMaxx = fAx;
fLineAMaxy = fAy;

if( fBx < fLineAMinx)
fLineAMinx = fBx;
if( fBy < fLineAMiny)
fLineAMiny = fBy;
if( fBx > fLineAMaxx)
fLineAMaxx = fBx;
if( fBy > fLineAMaxy)
fLineAMaxy = fBy;

fLineBMinx = fCx;
fLineBMiny = fCy;
fLineBMaxx = fCx;
fLineBMaxy = fCy;

if( fDx < fLineBMinx)
fLineBMinx = fDx;
if( fDy < fLineBMiny)
fLineBMiny = fDy;
if( fDx > fLineBMaxx)
fLineBMaxx = fDx;
if( fDy > fLineBMaxy)
fLineBMaxy = fDy;

if(x <= fLineAMaxx && x >= fLineAMinx && x <= fLineBMaxx && x >= fLineBMinx &&
y <= fLineAMaxy && y >= fLineAMiny && y <= fLineBMaxy && y >= fLineBMiny)
return 1;

return 0;
} 




int PLDX(int Ax,int Ay,int Bx,int By,int Px,int Py,int d)   //����Ƿ����ϰ� �жϵ��Ƿ񿿽�ֱ��d�ľ��봦 
{


 float Cx,Cy; /*��������*/



 int CP,CA,CB,AB;


 if(DZ(Px,Py,Ax,Ay)<=d) return (1);   /*���ϰ�*/

 if(DZ(Px,Py,Bx,By)<=d) return (1);   /*���ϰ�*/




 CP= ASK_PLD((float)Ax,(float)Ay,(float)Bx,(float)By,(float)Px,(float)Py);  /*�㵽ֱ�ߵľ���*/


 if( CP <= d ) 
   {

    ASK_Q((float)Ax,(float)Ay,(float)Bx,(float)By,(float)Px,(float)Py,&Cx,&Cy); /*�����������*/

    CA=DZ((int)Cx,(int)Cy,Ax,Ay);
    CB=DZ((int)Cx,(int)Cy,Bx,By);
    AB=DZ((int)Ax,(int)Ay,Bx,By);

    if( -2 <= AB-(CA+CB) && AB-(CA+CB) <= 2 )  /*��鴹���Ƿ������� ���ֵ2*/
      {
       return (1);   /*���ϰ�*/
      }
    
     
   }

 
 return(0); /*���ϰ�*/


}




int ASK_a(int X1,int Y1,int X2,int Y2)   /*�õ����ĵ㵽Ŀ���ĽǶ�*/
{
   double duibian,linbian;

   double m=0;

   if(X1==X2&&Y1==Y2){return(-1);}

   if(X2>X1)
   linbian=X2-X1;
   else
   linbian=X1-X2;

   if(Y2>Y1)
   duibian=Y2-Y1;
   else
   duibian=Y1-Y2;


   m=atan2(duibian,linbian)/3.1415*180;    /*atan2����y/x�ķ�����ֵ*/

        if(X1>X2&&Y1>Y2) {m=180+m;}

   else if(X1<X2&&Y1>Y2) {m=360-m;}

   else if(X1>X2&&Y1<Y2) {m=180-m;}

   else if(X1>X2&&Y1<Y2) {;}

   else if(X1<X2&&Y1==Y2) {m=0;}

   else if(X1==X2&&Y1<Y2) {m=90;}

   else if(X1>X2&&Y1==Y2) {m=180;}

   else if(X1==X2&&Y1>Y2) {m=270;}

   return((int)m);




}





bool Touch_box(int x1,int y1,int x2,int y2,int px,int py) /*�жϵ���BOX�ĽӴ�*/
{
 int x3,y3,x4,y4;

 if(x2>x1) {x3=x1; x4=x2;} /*��������*/
 else {x3=x2; x4=x1;}

 if(y2>y1) {y3=y1; y4=y2;}
 else {y3=y2; y4=y1;}

 if(px>=x3 && px<=x4 && py>=y3 && py<=y4) return TRUE;
 else return FALSE;
}



//////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////���������////////////////////////////////////

#define random(num)   (rand() % (num))   /*����random����*/

int R;/*�ɵ�ǰϵͳʱ��������������������*/
struct tm *t;
time_t timer;


void init_rand()
{
  //ȡϵͳʱ��õ����������  Сʱ+��
 timer=time(NULL);
 t=localtime(&timer);
 R=t->tm_hour + t->tm_sec;
 srand(R);


}



int Xrand(int A,int B)    /*�����������A��B*/
{
 int x;

 while(1)
    {
     x=random(B+1);

     if(x>=A) break;

    }

 return(x);

}







//////////////////////////////////////////////////////////////////



void load_system_config_file(char filename[])       //��ȡsystem�����ļ�
{

 

 FILE *fp;
 errno_t err;//����ļ�����

 int n;

 float e;

 int end=0;

 if((err = fopen_s(&fp,filename,"r")) !=0)
    {
     AfxMessageBox("config/system.txtû���ҵ�!");

    }

  //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
 Edit_Brain=TRUE;  //�༭BrainBox������ر�
 else 
 Edit_Brain=FALSE;
 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
 show_YUAN_E=TRUE;  //��ʾԪ��Ծǿ��ֵ
 else 
 show_YUAN_E=FALSE;
 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
 show_YUAN_name=TRUE;  //��ʾԪ���ı�
 else 
 show_YUAN_name=FALSE;

 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%f",&e);

 set_E_X=e;   //����ЧӦ����




  //------------------
/*
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%f",&e);

 ZhuYi_threshold=e;   //ע��ķ�ֵ



*/
 //------------------



 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%f",&e);

 set_try_E_X=e;   //�������Ժ������




  //------------------



 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 Run_Learn=n;   //����ѧϰ


  //------------------




 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 _Run_Forgot=n;   //��������


 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
  AI_AUTO_Question_Flag=TRUE;  //�Է����ʱ�־
 else 
  AI_AUTO_Question_Flag=FALSE;

 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
  AI_Feedback_Question_Flag=TRUE;  //�������ʱ�־
 else 
  AI_Feedback_Question_Flag=FALSE;


 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
  Auto_Load_And_Save_Memory_Flag=TRUE;  //�Զ����غͱ������
 else 
  Auto_Load_And_Save_Memory_Flag=FALSE;

 



 //------------------


 fclose(fp);

}


