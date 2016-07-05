

#include "stdafx.h"
#include "YUAN_system.h"


#include <math.h>
#include <dos.h>
#include <time.h>


YUAN_UNIT *P_select_YUAN=NULL;     //被选择的元 指针
int select_linker_ID_1=-1;         //被选择的连接起点元
int select_linker_ID_2=-1;         //被选择的连接目标元
int select_linker_sum=0;          //选择连接的数量

bool show_info=FALSE;  //显示调试信息
bool show_YUAN_E=TRUE;  //显示元活跃强度值
bool show_YUAN_name=TRUE;  //显示元的名称
float set_E_X=100;    //设置活跃启动效应增益值


bool run_try=1;  //运行尝试

float set_try_E_X=0;    //设置尝试选择后增益值

YUAN_UNIT *P_max_E_YUAN=NULL;     //最强活跃强度的元 指针

//float ZhuYi_threshold=100;    //注意的阀值

int Run_Learn=0;  //运行学习

int Run_Forgot=0;  //运行遗忘
int _Run_Forgot=0;  //运行遗忘


 bool AUTO_Learning_Flag = 0;; //自动学习

 bool AI_AUTO_Question_Flag = 0;
 bool AI_Feedback_Question_Flag = 0;


int MyDebugX;

 bool Run_FC_Flag = 1;
 bool Edit_Brain = 0; //编辑BrainBox

 int YUAN_RUN_MAIN_Flag=1;


 bool Auto_Load_And_Save_Memory_Flag = 1;
 CString Current_Memory_File_Name = _T("");//当前打开的记忆文件名

int test=0;  //测试



/////////////////////////////////2D数学函数////////////////////////////////////
#define PI 3.1415

void MOVE_TO3(int oa,int *PX,int *PY,int D)  /*移动到*/
{
  double px=*PX,py=*PY;

 px+=D*cos(oa*PI/180);
 py+=D*sin(oa*PI/180);

 *PX=(int)px;
 *PY=(int)py;

}




int Round(float x)  /*四舍五入*/
{
 return((int)(x+0.5));
}



int DZ(int X1,int Y1,int X2,int Y2)  /*两点距离*/
{

 return  (int)  sqrt( fabs((float)((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1))));
}


int XDZ(int X1,int Y1,int X2,int Y2,int D)
{
 if(abs(X1-X2)<=D && abs(Y1-Y2)<=D) return 1;
 else return 0;

}



void ASK_ABC(float x1,float y1,float x2,float y2,float *A,float *B,float *C)  /*求点ABC*/
{


 /*直线的一般方程式 AX+BY+C=0 */
 *A=y2-y1;
 *B=x1-x2;
 *C=y1*(x2-x1)-x1*(y2-y1);

}




void ASK_Q(float x1,float y1,float x2,float y2,float px,float py,float *Qx,float *Qy)  /*求点到直线的垂足坐标*/
{
 float A,B,C;

 /*直线的一般方程式 AX+BY+C=0 */
 A=y2-y1;
 B=x1-x2;
 C=y1*(x2-x1)-x1*(y2-y1);

 *Qx=(B*B*px-A*B*py-A*C)/(A*A+B*B);
 *Qy=(-A*B*px+A*A*py-B*C)/(A*A+B*B);

}





int ASK_PLD(float x1,float y1,float x2,float y2,float px,float py)  /*求点到直线的距离*/
{
 float A,B,C;
 float d;


 ASK_ABC(x1,y1,x2,y2,&A,&B,&C);

 /*直线的一般方程式 AX+BY+C=0 */


 d=(float) fabs( (A*px+B*py+C) / sqrt(A*A+B*B) );   /*点到直线的距离*/


 Round(d);


 return((int)d);

}









int InterLine(float fAx,float fAy,float fBx,float fBy,float fCx,float fCy,float fDx,float fDy) /*判断两直线相交*/
{


float x,y; /*交点*/


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




int PLDX(int Ax,int Ay,int Bx,int By,int Px,int Py,int d)   //检查是否有障碍 判断点是否靠近直线d的距离处 
{


 float Cx,Cy; /*垂足坐标*/



 int CP,CA,CB,AB;


 if(DZ(Px,Py,Ax,Ay)<=d) return (1);   /*有障碍*/

 if(DZ(Px,Py,Bx,By)<=d) return (1);   /*有障碍*/




 CP= ASK_PLD((float)Ax,(float)Ay,(float)Bx,(float)By,(float)Px,(float)Py);  /*点到直线的距离*/


 if( CP <= d ) 
   {

    ASK_Q((float)Ax,(float)Ay,(float)Bx,(float)By,(float)Px,(float)Py,&Cx,&Cy); /*求出垂足坐标*/

    CA=DZ((int)Cx,(int)Cy,Ax,Ay);
    CB=DZ((int)Cx,(int)Cy,Bx,By);
    AB=DZ((int)Ax,(int)Ay,Bx,By);

    if( -2 <= AB-(CA+CB) && AB-(CA+CB) <= 2 )  /*检查垂足是否在线内 误差值2*/
      {
       return (1);   /*有障碍*/
      }
    
     
   }

 
 return(0); /*无障碍*/


}




int ASK_a(int X1,int Y1,int X2,int Y2)   /*得到中心点到目标点的角度*/
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


   m=atan2(duibian,linbian)/3.1415*180;    /*atan2返回y/x的反正切值*/

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





bool Touch_box(int x1,int y1,int x2,int y2,int px,int py) /*判断点于BOX的接触*/
{
 int x3,y3,x4,y4;

 if(x2>x1) {x3=x1; x4=x2;} /*调整坐标*/
 else {x3=x2; x4=x1;}

 if(y2>y1) {y3=y1; y4=y2;}
 else {y3=y2; y4=y1;}

 if(px>=x3 && px<=x4 && py>=y3 && py<=y4) return TRUE;
 else return FALSE;
}



//////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////随机数函数////////////////////////////////////

#define random(num)   (rand() % (num))   /*定义random函数*/

int R;/*由当前系统时间产生真正的随机数种子*/
struct tm *t;
time_t timer;


void init_rand()
{
  //取系统时间得到随机数种子  小时+秒
 timer=time(NULL);
 t=localtime(&timer);
 R=t->tm_hour + t->tm_sec;
 srand(R);


}



int Xrand(int A,int B)    /*随机数发生器A—B*/
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



void load_system_config_file(char filename[])       //读取system配置文件
{

 

 FILE *fp;
 errno_t err;//检测文件问题

 int n;

 float e;

 int end=0;

 if((err = fopen_s(&fp,filename,"r")) !=0)
    {
     AfxMessageBox("config/system.txt没有找到!");

    }

  //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
 Edit_Brain=TRUE;  //编辑BrainBox开启或关闭
 else 
 Edit_Brain=FALSE;
 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
 show_YUAN_E=TRUE;  //显示元活跃强度值
 else 
 show_YUAN_E=FALSE;
 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
 show_YUAN_name=TRUE;  //显示元的文本
 else 
 show_YUAN_name=FALSE;

 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%f",&e);

 set_E_X=e;   //启动效应增益




  //------------------
/*
 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%f",&e);

 ZhuYi_threshold=e;   //注意的阀值



*/
 //------------------



 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%f",&e);

 set_try_E_X=e;   //启动尝试后的增益




  //------------------



 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 Run_Learn=n;   //运行学习


  //------------------




 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 _Run_Forgot=n;   //运行遗忘


 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
  AI_AUTO_Question_Flag=TRUE;  //自发提问标志
 else 
  AI_AUTO_Question_Flag=FALSE;

 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
  AI_Feedback_Question_Flag=TRUE;  //反馈发问标志
 else 
  AI_Feedback_Question_Flag=FALSE;


 //------------------

 while(1)
 {
  if(fgetc(fp)==61)break;   //61 =
 }

 fscanf_s(fp,"%d",&n);

 if(n==1)
  Auto_Load_And_Save_Memory_Flag=TRUE;  //自动加载和保存记忆
 else 
  Auto_Load_And_Save_Memory_Flag=FALSE;

 



 //------------------


 fclose(fp);

}


