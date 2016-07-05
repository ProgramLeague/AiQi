// BrainBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AiQi.h"
#include "BrainBoxDlg.h"

#include "YUAN_struct.h"
#include "YUAN_system.h"

#include "YuanSetDlg.h" //我的对话框新类
#include "YuanLinkDlg.h" //我的对话框新类

#include "TextOutBox.h" //文字输出

#include "MyColor.h" //颜色定义


// CBrainBoxDlg 对话框

IMPLEMENT_DYNAMIC(CBrainBoxDlg, CDialog)

CBrainBoxDlg::CBrainBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrainBoxDlg::IDD, pParent)
	, BrainBox_Check1(FALSE)
{






}

CBrainBoxDlg::~CBrainBoxDlg()
{
}

void CBrainBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_BRAINBOX_CHECK1, BrainBox_Check1);
}


BEGIN_MESSAGE_MAP(CBrainBoxDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON5, &CBrainBoxDlg::OnNew)

	ON_BN_CLICKED(IDC_BUTTON_SetYuan, &CBrainBoxDlg::OnBnClickedButton_OnSetYuan)
	ON_BN_CLICKED(IDC_BUTTON_SetLinker, &CBrainBoxDlg::OnBnClickedButton_OnSetYuanLink)
	ON_BN_CLICKED(IDC_BUTTON_Del, &CBrainBoxDlg::OnBnClickedButton_OnDel)
	ON_BN_CLICKED(IDC_BUTTON_NewYuan, &CBrainBoxDlg::OnBnClickedButton_OnNewyuan)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_SetYUANState, &CBrainBoxDlg::OnBnClickedButton_OnSetYuanState)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON3, &CBrainBoxDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CBrainBoxDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CBrainBoxDlg 消息处理程序

void CBrainBoxDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值





    if(nIDEvent==2) //2号定时器处理代码; 显示相关
      {






      //更新按钮状态
      if(P_select_YUAN==NULL) //如果有选中的元
	    {
         GetDlgItem(IDC_BUTTON_SetYuan)-> EnableWindow(FALSE);
	    }
      else
	    {
        GetDlgItem(IDC_BUTTON_SetYuan)-> EnableWindow(TRUE);
	    }


/*
      if(BrainBox_Check1 == TRUE)
        {
			if(show_YUAN_E==0)
			{	 
				UpdateData();
             show_YUAN_E=1;
			 UpdateData(0);
			}
        }
      else
       {
			if(show_YUAN_E==1)
			{	 
				UpdateData();
             show_YUAN_E=0;
			 UpdateData(0);
			}
       }

*/


	  if(BST_CHECKED==((CButton*)GetDlgItem(IDC_BRAINBOX_CHECK1))->GetCheck()) //判断Check是否选中
	  {
       show_YUAN_E=1;
	  }

	  else
		  show_YUAN_E=0;



       if(select_linker_ID_1==-1 && select_linker_ID_2==-1) //如果没有有选中的连接
    	{
         GetDlgItem(IDC_BUTTON_SetLinker)-> EnableWindow(FALSE);
	    }
       else
        {
        GetDlgItem(IDC_BUTTON_SetLinker)-> EnableWindow(TRUE);
        }



        if(select_linker_ID_1==-1 && P_select_YUAN==NULL)
          { 
           GetDlgItem(IDC_BUTTON_DelYuan)-> EnableWindow(FALSE);
          }
		else
           GetDlgItem(IDC_BUTTON_DelYuan)-> EnableWindow(TRUE);


        if( P_select_YUAN==NULL)
          { 
           GetDlgItem(IDC_BUTTON_SetYUANState)-> EnableWindow(FALSE);
          }
		else
           GetDlgItem(IDC_BUTTON_SetYUANState)-> EnableWindow(TRUE);



       //刷新显示屏幕
       OnPaint();
 
      }


	CDialog::OnTimer(nIDEvent);
}

void CBrainBoxDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()





CDC *pDC=GetDC();



//双缓存显示///////////////////////////////////////////

int nWidth=800,nHeight=620;

  CString TT;
  YUAN_UNIT *tmp=YUAN;

CDC MemDC; //定义一个显示设备对象
CBitmap MemBitmap;//定义一个位图对象
MemDC.CreateCompatibleDC(NULL);//建立与屏幕显示兼容的内存显示设备
MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight); //下面建立一个与屏幕显示兼容的位图，窗口的大小
CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap); //将位图选入到内存显示设备中


MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));

//绘图------------------------------------------------


  CPen pen1,pen2,pen3;

  pen1.CreatePen(PS_SOLID,1,RGB(0,0,0));
  pen2.CreatePen(PS_DOT,1,RGB(190,190,190)); 
  pen3.CreatePen(PS_SOLID,1,RGB(180,180,180));



  if(YUAN_RUN_MAIN_Flag==1) //开启 元运行  防止数据过大不显示其他窗口
  //画所有元
  Draw_All_YUAN(&MemDC);




  //显示鼠标准备建立的连接
   if( mouse_R_LineTo_xy.x!=0 &&  mouse_R_LineTo_xy.y!=0)
   {
     MemDC.SelectObject(&pen2);
     MemDC.MoveTo(mouse_R_LineTo_xy);
     MemDC.LineTo(mouse_xy);
	 MemDC.SelectObject(&pen1);
   }

  //显示鼠标拖动圆的提示
   if(mouse_L_Move_YUAN_xy.x!=0 && mouse_L_Move_YUAN_xy.y!=0)
   {
     MemDC.SelectObject(&pen2);
     MemDC.Ellipse(mouse_xy.x-15,mouse_xy.y-15,mouse_xy.x+15,mouse_xy.y+15);
	 MemDC.SelectObject(&pen1);
   }




 if(show_info==TRUE)
 {

  int px=0,py=10;


  for(;;)
  {


 
   TT.Format("ID=%d  threshold=%0.2f  x=%d  y=%d  字符=%s  state=%d  A_time=%d",tmp->ID,tmp->threshold,tmp->x,tmp->y,tmp->name,tmp->state,tmp->A_time);

   MemDC.TextOut(px,py,TT);

    if(tmp->next==NULL)
	{

     break;
	}

    tmp=tmp->next;

    py+=18;

  }







//显示选择的元的ID编号
if(P_select_YUAN!=NULL)
   TT.Format("select_YUAN=%d",P_select_YUAN->ID);
else
   TT.Format("select_YUAN=没有");

   MemDC.TextOut(580,0,TT);


//显示被选择的连接

   TT.Format("linker= %d to %d  w=%0.2f",select_linker_ID_1,select_linker_ID_2,YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2) );
   MemDC.TextOut(580,20,TT);





 }


















/////显示信息/////////////////

CString YUAN_Data_Text;

//画线
  CPen pen4;
  pen4.CreatePen(PS_SOLID,1,RGB(242,242,242)); 

          MemDC.SelectObject(&pen4);
          MemDC.MoveTo(0,595); 
          MemDC.LineTo(800,595);


YUAN_Data_Text.Format("%d,%d ",mouse_xy.x,mouse_xy.y); //显示坐标
  TextOut_SongTi(740,600, 14,RGB(232,232,232),YUAN_Data_Text,&MemDC);





       //有选择的元
       if(P_select_YUAN!=NULL) 
         {

           YUAN_Data_Text.Format("概念ID：%d  名称：%s  状态：%d  阈值：%0.2f  疲劳值：%0.2f  活跃强度值：%0.2f",P_select_YUAN->ID,P_select_YUAN->name,P_select_YUAN->state,P_select_YUAN->threshold,P_select_YUAN->fag,P_select_YUAN->E);
		     
             TextOut_SongTi(4,600, 14,DARKGRAY,YUAN_Data_Text,&MemDC);

         }








   //选择连接


  float aE;
  float bE;
  float cE;
  float dE;

    
       if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1)
         {
           if(select_linker_sum==1)
             {


               aE=YUAN->ID_return_P(select_linker_ID_1) ->E;
               bE=YUAN->ID_return_P(select_linker_ID_2) ->E;

               if(aE>bE)
               {
               cE=(aE-bE)*WL;
               }

               else
               {
               cE=0;

               }


              YUAN_Data_Text.Format("获取单向连接：（连接：%d -> %d  强度：%0.2f + %0.2f）  ",select_linker_ID_1,select_linker_ID_2,YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2), cE);
             }


           else if(select_linker_sum==2)
             {



               aE=YUAN->ID_return_P(select_linker_ID_1) ->E;
               bE=YUAN->ID_return_P(select_linker_ID_2) ->E;

               if(aE>bE)
               {
               cE=(aE-bE)*WL;  dE=0;
               }

               else
               {
               cE=0;dE=(bE-aE)*WL;

               }





              YUAN_Data_Text.Format("获取双向连接：（连接：%d -> %d  强度：%0.2f + %0.2f） （连接：%d -> %d  强度：%0.2f + %0.2f）  ",select_linker_ID_1,select_linker_ID_2,YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2) , cE ,select_linker_ID_2,select_linker_ID_1,YUAN->Get_linker_weight(select_linker_ID_2,select_linker_ID_1) ,dE);
             





             }







          TextOut_SongTi(4,600, 14,DARKGRAY,YUAN_Data_Text,&MemDC);

         }






//------------------------------------------------

pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY); //将内存中的图拷贝到屏幕上进行显示

MemDC.SelectObject(pOldBit); //绘图完成后的清理
MemBitmap.DeleteObject();
MemDC.DeleteDC(); 














}

int CBrainBoxDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码


  hIcon=AfxGetApp()->LoadIcon(IDI_BrainBox);  //定义窗口图标
  CBrainBoxDlg::SendMessage(WM_SETICON,ICON_SMALL,(LPARAM)hIcon);  //发送消息更改窗口图标



 SetTimer(2,100,NULL);  //屏幕显示 



 m_move_YUAN=FALSE;

 mouse_R_LineTo_xy=0;
 mouse_L_Move_YUAN_xy=0;


 if(show_YUAN_E == TRUE)
   {
    BrainBox_Check1=1;
   }
   else
   {
    BrainBox_Check1=0;
   }




	return 0;
}










void CBrainBoxDlg::Draw_YUAN(int x, int y,int state,int Layer,CDC *pDC) //画元
{

  int dx;

  CBitmap bitmap;   //创建图位对象
  bitmap.LoadBitmap(IDB_BMP_YUAN);  //加载图位对象 ID

  CDC dcMemory;  //创建CDC对象
  dcMemory.CreateCompatibleDC(pDC);  //创建与pDC兼容的内存设备环境
  dcMemory.SelectObject(&bitmap);  //将图位选入内存设备环境中

  if(Layer==0) dx=0;
  else if(Layer==1) dx=32;
  else if(Layer==2) dx=64;
  else if(Layer==3) dx=96;
  else if(Layer==4) dx=128;
  else if(Layer==5) dx=160;
  else if(Layer==6) dx=192;
  else if(Layer==7) dx=224;
  else if(Layer==8) dx=256;
  else dx=0;

  if(state==0)
  {
   pDC->BitBlt(x-8,y-8,16,16,&dcMemory,dx,0,SRCCOPY);  //将内存设备环境复制到当前设备环境中
  }
  else if(state==1)
  {
   pDC->BitBlt(x-8,y-8,16,16,&dcMemory,dx+16,0,SRCCOPY);  //将内存设备环境复制到当前设备环境中
  }


}







void CBrainBoxDlg::Draw_YUAN_2(int x, int y,int state,float E,int Layer,CDC *pDC) //画元
{

  CPen pen,pen1,*oldpen;

  pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));

 CBrush brush,brush1,brush2,*oldbrush;
 int r=10;



 brush1.CreateSolidBrush(RGB(255,255,255));
 brush2.CreateSolidBrush(RGB(255,215,0));

 oldbrush=pDC->SelectObject(&brush);
 oldpen=pDC->SelectObject(&pen);

pDC->SelectObject(pen1);

  if(state==0)
  {
   pDC->SelectObject(brush1);
   r=8;
   pDC->Ellipse(x-r,y-r,x+r,y+r);
  }

  else if(state==1)
  {
   pDC->SelectObject(brush2);
   r=8+E/30;
   pDC->Ellipse(x-r,y-r,x+r,y+r);
  }


  pDC->SelectObject(&oldpen);
  pDC->SelectObject(oldbrush);


}



void CBrainBoxDlg::Draw_YUAN_name(int x, int y,float F,CString TT,CDC *pDC) //画元的名字
{

  int size=(int)F+100;

  CFont font,*oldfont;

  font.CreatePointFont(size,"宋体",NULL);

  oldfont=pDC->SelectObject(&font);

 

  pDC->SetTextColor(RGB(0,0,255));
  pDC->SetBkMode(TRANSPARENT);

  pDC->TextOut(x-10,y-40-(int)(F/10),TT);

  pDC->SelectObject(oldfont);
 

}


void CBrainBoxDlg::Draw_YUAN_name_2(int x, int y,int state,CString TT,CDC *pDC) //画元的名字
{

  int size=100;

  int x_py;
  int Length=TT.GetLength();
  x_py=x-Length*12/2/2-1;

  CFont font,*oldfont;



  font.CreatePointFont(size,"宋体",NULL);

  oldfont=pDC->SelectObject(&font);

  if(state==0)
   {

     pDC->SetTextColor(RGB(132,132,132));
     pDC->SetBkMode(TRANSPARENT);

     pDC->TextOut(x_py,y-8,TT);

   }


  else if(state==1)
   {
     //font.CreatePointFont(size+5,"宋体",NULL);
     //pDC->SelectObject(&font);
     pDC->SetTextColor(RGB(30,30,30));
     pDC->SetBkMode(TRANSPARENT);

     pDC->TextOut(x_py,y-8,TT);
	  //pDC->TextOut(x_py+1,y-8,TT);

   }

  pDC->SelectObject(oldfont);
 

}





void CBrainBoxDlg::Draw_All_YUAN(CDC *pDC)
{


  CPen pen1,pen2,pen3,pen4,pen5;

  pen1.CreatePen(PS_SOLID,1,RGB(150,150,150));
  pen2.CreatePen(PS_SOLID,1,RGB(0,0,0)); 
  pen3.CreatePen(PS_SOLID,1,RGB(255,222,0));
  pen4.CreatePen(PS_SOLID,1,RGB(255,56,56)); 
  pen5.CreatePen(PS_SOLID,2,RGB(0,255,0)); 

  YUAN_UNIT *tmp=YUAN;
//------------------------------------------------

    //画连接

  tmp=YUAN;

  LINK_UNIT *linker_tmp;

  int x1,y1,x2,y2;

  for(;;) //遍历元
  {




   //遍历元联系表
   CONTACTS_UNIT *P_YUAN_Contacts;
   CString RR;
   P_YUAN_Contacts=tmp->Contacts;

   for(;;)
   {


             int aa;
             YUAN_UNIT *tmp2=NULL;


    if(P_YUAN_Contacts->data.Find("<是>")==0) //当前数据带<是>标签
	{

     RR=P_YUAN_Contacts->data;
     RR.Replace( " ", NULL);
     RR.Replace( "<是>", NULL);

         if(!RR.IsEmpty())
           {

             aa=YUAN->Find_name_return_ID(RR); //查找是否有一样概念的元

             if(aa!=-1)
                 {
                    tmp2 = YUAN->ID_return_P(aa);

                   //画连接
			
                   x1=tmp->x;
	               y1=tmp->y;

	               x2=tmp2->x;
	               y2=tmp2->y;

                   pDC->SelectObject(&pen3);
                   pDC->MoveTo(x1,y1);
		           pDC->LineTo(x2,y2);



                  //画方向标识
		         int px=x2,py=y2,a;
		           a=ASK_a(x2,y2,x1,y1);
                   MOVE_TO3(a,&px,&py,10);
		           pDC->SelectObject(&pen3);
                   pDC->Rectangle(px-1,py-1,px+3,py+3);

                 }

           }


	}




    if(P_YUAN_Contacts->data.Find("<因果>")==0) //当前数据带[因果]标签
	{

     RR=P_YUAN_Contacts->data;
     RR.Replace( " ", NULL);
     RR.Replace( "<因果>", NULL);

         if(!RR.IsEmpty())
           {

             aa=YUAN->Find_name_return_ID(RR); //查找是否有一样概念的元

             if(aa!=-1)
                 {
                    tmp2 = YUAN->ID_return_P(aa);

                   //画连接
			
                   x1=tmp->x;
	               y1=tmp->y;

	               x2=tmp2->x;
	               y2=tmp2->y;

                   pDC->SelectObject(&pen3);
                   pDC->MoveTo(x1,y1);
		           pDC->LineTo(x2,y2);



                  //画方向标识
		         int px=x2,py=y2,a;
		           a=ASK_a(x2,y2,x1,y1);
                   MOVE_TO3(a,&px,&py,10);
		           pDC->SelectObject(&pen3);
                   pDC->Rectangle(px-1,py-1,px+3,py+3);

                 }

           }


	}

    if(P_YUAN_Contacts->data.Find("<不是>")==0) //当前数据带<不是>标签
	{

     RR=P_YUAN_Contacts->data;
     RR.Replace( " ", NULL);
     RR.Replace( "<不是>", NULL);

         if(!RR.IsEmpty())
           {

             aa=YUAN->Find_name_return_ID(RR); //查找是否有一样概念的元

             if(aa!=-1)
                 {
                    tmp2 = YUAN->ID_return_P(aa);

                   //画连接
			
                   x1=tmp->x;
	               y1=tmp->y;

	               x2=tmp2->x;
	               y2=tmp2->y;

                   pDC->SelectObject(&pen4);
                   pDC->MoveTo(x1,y1);
		           pDC->LineTo(x2,y2);


                  //画方向标识
		         int px=x2,py=y2,a;
		           a=ASK_a(x2,y2,x1,y1);
                   MOVE_TO3(a,&px,&py,10);
		           pDC->SelectObject(&pen4);
                   pDC->Rectangle(px-1,py-1,px+3,py+3);


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










    linker_tmp=tmp->linker;

    for(;;)
	{

        x1=YUAN->ID_return_P(linker_tmp->linker_ID) ->x;
	    y1=YUAN->ID_return_P(linker_tmp->linker_ID) ->y;

	    x2=tmp->x;
	    y2=tmp->y;

        if(linker_tmp->linker_ID!=0)
		{
         //画连接
			

         pDC->SelectObject(&pen1);
         pDC->MoveTo(x1,y1);
		 pDC->LineTo(x2,y2);
          

/*
		 //画被选择的线
         if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1)
		 {
          if(tmp->ID==select_linker_ID_2 && linker_tmp->linker_ID==select_linker_ID_1)
		  {
 

           pDC->SelectObject(&pen2);
           pDC->MoveTo(x1,y1); 
           pDC->LineTo(x2,y2); 
           
		  }
		 }
*/
         //画方向标识
		 int px=x2,py=y2,a;
		 a=ASK_a(x2,y2,x1,y1);
         MOVE_TO3(a,&px,&py,10);
		 pDC->SelectObject(&pen2);
         pDC->Rectangle(px-1,py-1,px+3,py+3);

		}


       if(linker_tmp->next==NULL)
	   {
        break;
	   }

       linker_tmp=linker_tmp->next;      

	}







  if(tmp->next==NULL)
  {
    break;
  }

    tmp=tmp->next;


  }



          //画被选择的线
   if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1)
   {
          x1=YUAN->ID_return_P(select_linker_ID_1) ->x;
          y1=YUAN->ID_return_P(select_linker_ID_1) ->y;
          x2=YUAN->ID_return_P(select_linker_ID_2) ->x;
          y2=YUAN->ID_return_P(select_linker_ID_2) ->y;


          pDC->SelectObject(&pen2);
          pDC->MoveTo(x1,y1); 
          pDC->LineTo(x2,y2);


          //画方向标识
          int px=x2,py=y2,a;

          a=ASK_a(x2,y2,x1,y1);
          MOVE_TO3(a,&px,&py,10);

          pDC->Rectangle(px-1,py-1,px+3,py+3);

          if(select_linker_sum==2)
            {
             a=ASK_a(x1,y1,x2,y2);
             MOVE_TO3(a,&px,&py,10);

             pDC->Rectangle(px-1,py-1,px+3,py+3);

            }





   }



//------------------------------------------------

  CString TT;

  tmp=YUAN;

  for(;;) //画元
  {

    Draw_YUAN_2(tmp->x,tmp->y,tmp->state,tmp->E,tmp->Layer,pDC); //画元

   if(show_YUAN_E==TRUE)  //显示元活跃强度值
   {
    pDC->SetTextColor(RGB(0,0,0));

    TT.Format("%0.2f",tmp->E);

    pDC->TextOut(tmp->x-10,tmp->y-24,TT);
   }


   if(show_YUAN_name==TRUE)  //显示元的文本
   {
   /*
    pDC->SetTextColor(RGB(0,128,255));

    TT.Format("%s",tmp->name);

    pDC->TextOut(tmp->x-10,tmp->y-40,TT);

    */

/*

    if(tmp->ID!=0)
	{
	  if(tmp->state==1)	
      Draw_YUAN_name(tmp->x,tmp->y,tmp->E,tmp->name,pDC); //画元的名字

	  else
      Draw_YUAN_name(tmp->x,tmp->y,0,tmp->name,pDC); //画元的名字

	}
*/


    if(tmp->ID!=0)
	{
     Draw_YUAN_name_2(tmp->x,tmp->y,tmp->state,tmp->name,pDC); //画元的名字

	}



	pDC->SetTextColor(RGB(0,0,0));
   }

    if(tmp->next==NULL)
	{
     break;
	}

    tmp=tmp->next;


  }


//------------------------------------------------









  CBrush *brush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //设置透明的填充色
  pDC->SelectObject(brush);



  //标记 被选择的元
  if(P_select_YUAN!=NULL)
    {
     pDC->SelectObject(&pen5);
     pDC->Ellipse(P_select_YUAN->x-15,P_select_YUAN->y-15,P_select_YUAN->x+15,P_select_YUAN->y+15);

    }



}















YUAN_UNIT * CBrainBoxDlg::Get_mouse_down_YUAN(YUAN_UNIT *root, int mouse_x, int mouse_y)  //返回鼠标下面元的指针
{


  YUAN_UNIT *tmp=root;
  YUAN_UNIT *tmp2=NULL;
  bool a=FALSE;

  for(;;)
  {


    a=Touch_box(mouse_x-8,mouse_y-8,mouse_x+8,mouse_y+8,tmp->x,tmp->y);


    if(a==TRUE) 
      {
        tmp2=tmp;

        break;
      }

    if(tmp->next==NULL)  break;

    tmp=tmp->next;


  }



    return tmp2;



}








void CBrainBoxDlg::Select_Linker(int *li,int *lj,int mouse_x,int mouse_y) 
{

int x1,y1,x2,y2;
int xdi=-1,xdj=-1;
int s=0;



  YUAN_UNIT *tmp=YUAN;
  LINK_UNIT *linker_tmp;



  for(;;)
  {

    linker_tmp=tmp->linker;

    for(;;)
	{

        x1=YUAN->ID_return_P(linker_tmp->linker_ID) ->x;
	    y1=YUAN->ID_return_P(linker_tmp->linker_ID) ->y;

	    x2=tmp->x;
	    y2=tmp->y;

            if(linker_tmp->linker_ID!=0)
			{
              s=PLDX(x1,y1,x2,y2,mouse_x,mouse_y,4); 
               if(s==1)
			   {
                  xdi=linker_tmp->linker_ID; 
                  xdj=tmp->ID; 
                  goto END;
			   }
			}


            if(linker_tmp->next==NULL)
	      {
               break;
	      }

            linker_tmp=linker_tmp->next;      

	}







    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  }



END:;

*li=xdi;
*lj=xdj;




}
void CBrainBoxDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

mouse_xy=point;
/*
mouse_xy.x -= 20;
mouse_xy.y -= 20;
*/

	CDialog::OnMouseMove(nFlags, point);
}

void CBrainBoxDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值




/*
 CString Status_Bar_text;



   Status_Bar_text.Format("Ready");
  ((CMainFrame*)GetParent())->SetMessageText(Status_Bar_text);  
*/

 //取消连接选择
 select_linker_ID_1=-1;
 select_linker_ID_2=-1; 

 select_linker_sum=0;


//选择元----------------------------

 
  P_select_YUAN=Get_mouse_down_YUAN(YUAN,point.x,point.y); //返回元的指针



  if(P_select_YUAN!=NULL) //有选择的元
  {
   m_move_YUAN=TRUE;

   mouse_L_Move_YUAN_xy.x=P_select_YUAN->x;
   mouse_L_Move_YUAN_xy.y=P_select_YUAN->y;

   goto selectEND;

  }



//选择连接----------------------------



  Select_Linker(&select_linker_ID_1,&select_linker_ID_2,mouse_xy.x,mouse_xy.y); 

   if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1)
   {
      P_select_YUAN=NULL;

     select_linker_sum=0;

     bool fl;

     //查找元ID2 到 ID1 的连接是否存在 
     fl=YUAN->Find_linker(select_linker_ID_2,select_linker_ID_1);

     if(fl==TRUE)  select_linker_sum=2;
     else   select_linker_sum=1;  



   }




//----------------------------

selectEND:;



	CDialog::OnLButtonDown(nFlags, point);
}

void CBrainBoxDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


 mouse_L_Move_YUAN_xy=0;

 if(m_move_YUAN==TRUE  && P_select_YUAN!=NULL)
 {
  
  int mx=point.x;
  int my=point.y;
 if(mx>800) mx=800;
  if(my>600) my=600;

  YUAN->Set_xy(P_select_YUAN->ID,mx,my);


  //P_select_YUAN=NULL;
  m_move_YUAN=FALSE;



 }



 //----------------------------

	CDialog::OnLButtonUp(nFlags, point);
}

void CBrainBoxDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值



    //------------------

     if(nChar==VK_DELETE)   //按Delete键(46) 删除一个元 或者一个连接
	 {

           if(P_select_YUAN!=NULL && P_select_YUAN->ID!=0) //有选择的元
             {
               YUAN->Del_ID(P_select_YUAN->ID);

			   P_select_YUAN=NULL;

			  
             } 


           if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1) //有选择的连接
		   {
             YUAN->Del_a_link(select_linker_ID_1,select_linker_ID_2);

             select_linker_ID_1=-1;
             select_linker_ID_2=-1; 
			 
		   }


	 }



 

    //------------------

     if(nChar==13)   // 回车
	 {
      ;

     }

    //------------------









	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}










CString CBrainBoxDlg::CString_Extraction_Content(CString text,CString a,CString b)   //字符串提取中间内容
{
  
 CString strOut;


 int len = a.GetLength();

 int nStart=text.Find(a)+len;
 int nEnd=text.Find(b,nStart);

 strOut=text.Mid(nStart,nEnd-nStart);



 return strOut;
}






void CBrainBoxDlg::Load_Memory_File_XML(int flag,CString FileName)
{
 // TODO: 在此添加控件通知处理程序代码

 if(flag==1)
 {
  CFileDialog FileDlg(TRUE);
  FileDlg.m_ofn.lpstrTitle="打开记忆文件";
  FileDlg.m_ofn.lpstrFilter="Brain Box文件(*.xml)\0*.xml\0All Files(*.*)\0*.*\0\0";

	
  if(FileDlg.DoModal() == IDOK )
   {

    FileName=FileDlg.GetPathName();


  }

  else return;

 }

 else if(flag==2)
 {


 }

 else return;
   ///////////////////////////////////////////////////////////////



  FILE *fp;

     errno_t err;//检测文件问题
    //	const char *filename = (LPCTSTR)FileName; //转换类型 重新赋予文件名

    LPCTSTR filename=FileName;  //防止0x73d311c7操作 0x00000004内存不能读

    if((err=fopen_s(&fp,filename,"r")) !=0)
	{

		CString TT;
		TT.Format("%s错误操作，文件不能读!!",filename);

           AfxMessageBox(TT);
           return;

	}



       char ch;
       int nn,i;
	   int end=0;
	   float f;

 int z1,z2;
       int index;


  //当前打开的记忆文件名
  Current_Memory_File_Name = FileName;



       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 


   TEXT_OUT_BOX_CLS();

       YUAN->FreeAll(YUAN);  //清空链表

	   

	   YUAN_UNIT *tmp_YUAN;

	   
       YUAN_SUM=0;  //元的总数为0

     YUAN_ID_X=0;

	 index=0;
 //--------------------------
//读取文件到字符串

 CString FileStr;

 char tc;
	   
 CString Tmpch;
 CString TmpStr;


  while(!feof(fp))
       {
          tc=fgetc(fp);





          Tmpch.Format("%c",tc);

          FileStr += Tmpch;
 


      }


   fclose(fp);









 /*--------------------------*/

 int a_len,b_len,nStart,nEnd;
 nStart=0;

 CString a,b;

 a="<概念 ID";
 b="</概念>";

 CString TmpStr2;
 CString TmpCC;
  CString TmpTT;

 a_len = a.GetLength();
 b_len = b.GetLength();



 while(end!=1)
 {


  nStart=FileStr.Find(a,nStart)+a_len;
  nEnd=FileStr.Find(b,nStart);


  TmpStr2=FileStr.Mid(nStart,nEnd-nStart); //得到一个元数据

  //-------------------------------
/*
    //读取ID编号

      TmpCC=CString_Extraction_Content(TmpStr2,"=\"","\">");   //字符串提取中间内容
       index=atoi(TmpCC);
*/

//TT.Format("index=%d",index);
//AfxMessageBox(TT);
 
            if(index==0)
			{
             tmp_YUAN=YUAN;
			}
			else
			{
             
             YUAN->New();
             tmp_YUAN=YUAN->ID_return_P(index);
             tmp_YUAN->ID=index;
			}



     //读取名称标识-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<名称>","</名称>");   //字符串提取中间内容
      

      tmp_YUAN->name=TmpCC;
//TT.Format("name=%s",TmpCC);
//AfxMessageBox(TT);


    //读取元数据-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<数据域>","</数据域>");   //字符串提取中间内容




//TT.Format("数据域=%s",TmpCC);
//AfxMessageBox(TT);



 int aa_len,bb_len,nnStart,nnEnd;
 nnStart=0;

 CString aa,bb;

 aa="<数据 ID";
 bb="/数据>";

 CString TmpStr3;



 aa_len = aa.GetLength();
 bb_len = bb.GetLength();

 nn=0;

 while(1)
 {


  nnStart=TmpCC.Find(aa,nnStart)+aa_len;
  nnEnd=TmpCC.Find(bb,nnStart);


  TmpStr3=TmpCC.Mid(nnStart,nnEnd-nnStart); //得到一个子数据
  //----------
   //TT.Format("子数据字符串=%s",TmpStr3);
   //AfxMessageBox(TT);

   TmpTT=CString_Extraction_Content(TmpStr3,"权值=\"","\">");   //字符串提取中间内容
   f=atof(TmpTT); //得到权值

 
   TmpTT.Empty();
   TmpTT=CString_Extraction_Content(TmpStr3,"CDATA[","]]>");   //字符串提取中间内容
     //得到子数据
   if(TmpTT.IsEmpty()==1) TmpTT="o^_^o";



  
   //TT.Format("提取权值=%0.2f 提取数据=%s",f,TmpTT);
  // AfxMessageBox(TT);

     if(nn==0) //如果是联系表ROOT
	 {
      tmp_YUAN->Contacts->Set_data(0,TmpTT); //保存到联系表ROOT里
	 }
	 else
	 {
      tmp_YUAN->Contacts->Add(TmpTT,0); //保存到联系表里
	 }

    tmp_YUAN->Contacts->Set_weight(nn,f);//设置权值



  //----------
  nnStart=nnEnd+bb_len; //下一个子数据的开始位置

  if( TmpCC.Find(bb,nnStart)==-1) {break;} //到最后一个子数据退出

  nn++;

 }




    //读取层级-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<层>","</层>");   //字符串提取中间内容
      z1=atoi(TmpCC);

      tmp_YUAN->Layer=z1;

//TT.Format("Layer=%d",z1);
//AfxMessageBox(TT);

    //读取xy-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<x>","</x>");   //字符串提取中间内容
      z1=atoi(TmpCC);

      tmp_YUAN->x=z1;

//TT.Format("x=%d",z1);
//AfxMessageBox(TT);

      TmpCC=CString_Extraction_Content(TmpStr2,"<y>","</y>");   //字符串提取中间内容
      z1=atoi(TmpCC);

      tmp_YUAN->y=z1;

//TT.Format("y=%d",z1);
//AfxMessageBox(TT);

	 //读取激活阈值-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<激活阈值>","</激活阈值>");   //字符串提取中间内容

      f=atof(TmpCC);

      tmp_YUAN->threshold=f;

//TT.Format("threshold=%f",f);
//AfxMessageBox(TT);

     //读取Mark标识-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<标识>","</标识>");   //字符串提取中间内容
      

      tmp_YUAN->Mark=TmpCC;
//TT.Format("Mark=%s",TmpCC);
//AfxMessageBox(TT);


     //读取连接关系-----------------


      TmpCC=CString_Extraction_Content(TmpStr2,"<连接>","</连接>");   //字符串提取中间内容




//TT.Format("连接数据=%s",TmpCC);
//AfxMessageBox(TT);




 nnStart=0;



 aa="<来源 ID";
 bb="/来源>";




 aa_len = aa.GetLength();
 bb_len = bb.GetLength();



 while(1)
 {


  nnStart=TmpCC.Find(aa,nnStart)+aa_len;
  nnEnd=TmpCC.Find(bb,nnStart);


  TmpStr3=TmpCC.Mid(nnStart,nnEnd-nnStart); //得到一个子数据
  //----------

 // if(index==68)
 // {
  //  TT.Format("连接子数据=%s",TmpStr3);
 //   AfxMessageBox(TT);
 // }

   TmpTT=CString_Extraction_Content(TmpStr3,"=\"","\"");   //字符串提取中间内容
   z1=atoi(TmpTT); //得到ID

   TmpTT=CString_Extraction_Content(TmpStr3,">","<");   //字符串提取中间内容
     //得到连接强度
   f=atof(TmpTT);
 // if(index==68)
 // {
  //  TT.Format("提取ID=%d 连接强度=%0.2f",z1,f);
 //   AfxMessageBox(TT);

 // }
   
		   if(z1==0)
		   { 
            tmp_YUAN->linker->Set_weight(0,f);
		   }
		   else
		   {

			 tmp_YUAN->linker->New(z1);
			 tmp_YUAN->linker->ID_return_P(z1)->linker_weight=f;
		   }





  //----------
  nnStart=nnEnd+bb_len; //下一个子数据的开始位置

  if( TmpCC.Find(bb,nnStart)==-1) {break;} //到最后一个子数据退出



 }


  //-------------------------------











  nStart=nEnd+b_len; //下一个元的开始位置




  if( FileStr.Find(b,nStart)==-1) {end=1;break;} //到最后一个元退出



  index++;


 }



}





void CBrainBoxDlg::Load_Memory_File(int flag,CString FileName)
{
	// TODO: 在此添加控件通知处理程序代码

 if(flag==1)
 {
  CFileDialog FileDlg(TRUE);
  FileDlg.m_ofn.lpstrTitle="打开记忆文件";
  FileDlg.m_ofn.lpstrFilter="Brain Box文件(*.bbf)\0*.bbf\0All Files(*.*)\0*.*\0\0";

	
  if(FileDlg.DoModal() == IDOK )
   {

    FileName=FileDlg.GetPathName();


  }

  else return;

 }

 else if(flag==2)
 {


 }

 else return;
   ///////////////////////////////////////////////////////////////



  FILE *fp;

     errno_t err;//检测文件问题
    //	const char *filename = (LPCTSTR)FileName; //转换类型 重新赋予文件名

    LPCTSTR filename=FileName;  //防止0x73d311c7操作 0x00000004内存不能读

    if((err=fopen_s(&fp,filename,"r")) !=0)
	{

		CString TT;
		TT.Format("%s错误操作，文件不能读!!",filename);

           AfxMessageBox(TT);
           return;

	}

  //当前打开的记忆文件名
  Current_Memory_File_Name = FileName;



       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 


   TEXT_OUT_BOX_CLS();

       YUAN->FreeAll(YUAN);  //清空链表

	   int tmp_ID_X;
       char ch;
       int n,i,ctr;
	   int end=0;
	   float f;
	   YUAN_UNIT *tmp_YUAN;

	   
       YUAN_SUM=0;  //元的总数为0

 /*--------------------------*/
 /*读取ID命名*/
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%d",&i);
 tmp_ID_X=i;

 /*--------------------------*/

   //--------------------------
       while(end!=1)
	   {

         /*读取ID编号*/

         while(1)
		 {
          ch=fgetc(fp);
          if(ch=='[')
		  {
           fscanf_s(fp,"%d",&n);
            if(n==0)
			{
             tmp_YUAN=YUAN;
			}
			else
			{
             YUAN_ID_X=n;
             YUAN->New();
             tmp_YUAN=YUAN->ID_return_P(YUAN_ID_X);
             tmp_YUAN->ID=n;
			}

           break;
		  }

          if(ch==EOF)    /*文件结尾 退出循环*/
		  {
           end=1;
           break;
		  }

		 }

         if(end==1) break;

         /*读取层级*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%d",&i);
         tmp_YUAN->Layer=i;



         /*读取坐标X*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%d",&i);
         tmp_YUAN->x=i;


         /*读取坐标Y*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%d",&i);
         tmp_YUAN->y=i;


         /*读取阀值*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%f",&f);
         tmp_YUAN->threshold=f;





         /*读取文本*/
         while(1)     //循环前进判断是否到"="
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         ctr=0;

		 tmp_YUAN->name.Format("");

         while(1)
		 {

          CString tmpch;


          ch=fgetc(fp);  

		   if(ch=='\n')
		   { 
			 if(ctr==0){tmp_YUAN->name="o^_^o";break;}   

			 else  break; 
		   }

           tmpch.Format("%c",ch);

           tmp_YUAN->name+=tmpch;

          ctr++;

		 }
 








         //读取Mark标记
         while(1)     //循环前进判断是否到"="
		 {
          if(fgetc(fp)==61)break;   //61 =
		 }

         ctr=0;

		 tmp_YUAN->Mark.Format("");

         while(1)
		 {

          CString tmpch;


          ch=fgetc(fp);  

		   if(ch=='\n')
		   { 
			 if(ctr==0){tmp_YUAN->Mark="o^_^o";break;}   

			 else  break; 
		   }

           tmpch.Format("%c",ch);

           tmp_YUAN->Mark+=tmpch;

          ctr++;

		 }






        //读取连接者ID编号  连接强度

           while(1)
		   {
            if(fgetc(fp)==61)break;   //61 =
		   }


        while(1)
		 {



           fscanf_s(fp,"%d",&i);



		   if(i==0)
		   { 
              while(1)
			  {
               if(fgetc(fp)==62)break;   //62 >
			  }
             fscanf_s(fp,"%f",&f);
			 tmp_YUAN->linker->Set_weight(0,f);

		   }


		   else
		   {
              while(1)
			  {
               if(fgetc(fp)==62)break;   //62 >
			  }
             fscanf_s(fp,"%f",&f);
			 tmp_YUAN->linker->New(i);
			 tmp_YUAN->linker->ID_return_P(i)->linker_weight=f;

		   }




           if(fgetc(fp)=='\n')break;
		 }



        


		 //tmp_YUAN->Contacts

         //读取 联系表字符串数据
         while(1)     //循环前进判断是否到"="
		 {
          if(fgetc(fp)==61)break;   //61 =
		 }

		 int Contacts_end=0;

     CString TT;
	 int index=0;


     while(1)
	{
         if(Contacts_end==1) break;

         ctr=0;

         TT="";





         while(1) //读字符串
		 {

          CString tmpch;


          ch=fgetc(fp);  



		   if(ch=='\n')//
		   { 
            

              if(index==0) //如果是联系表ROOT
			  {
                if(ctr==0) TT="o^_^o";

                tmp_YUAN->Contacts->Set_data(0,TT); //保存到联系表里
			  }
			  else
			  {
                if(ctr==0) TT="o^_^o";
                tmp_YUAN->Contacts->Add(TT,0); //保存到联系表里
			  }

              Contacts_end=1;
			  break; 



		   }






		   if(ch==36)// 为字符"$"
		   { 

              if(index==0) //如果是联系表ROOT
			  {
                if(ctr==0) TT="o^_^o";

                tmp_YUAN->Contacts->Set_data(0,TT); //保存到联系表里
			  }
			  else
			  {
                if(ctr==0) TT="o^_^o";
                tmp_YUAN->Contacts->Add(TT,0); //保存到联系表里
			  }


			  break; 

		   }







           tmpch.Format("%c",ch);

           TT+=tmpch;

          ctr++;

		 }

           if(Contacts_end==1) break;


             //读权值
             fscanf_s(fp,"%f",&f);
			 tmp_YUAN->Contacts->Set_weight(index,f);//根据链表顺序设置权值


           while(1)
		   {
            if(fgetc(fp)==35)break;   //为字符"#"
			if(fgetc(fp)=='\n'){Contacts_end=1;break;}   //为字符"换行"
		   }


        index++;




	 }
 









	   }
   //--------------------------

   YUAN_ID_X=tmp_ID_X;

   fclose(fp);








}

void CBrainBoxDlg::Save_Memory_File(int flag,CString FileName)
{
	// TODO: 在此添加控件通知处理程序代码


 if(flag==1)
 {
  CFileDialog FileDlg(FALSE);
  FileDlg.m_ofn.lpstrTitle="保存记忆文件";
  FileDlg.m_ofn.lpstrFilter="BrainBox文件(*.bbf)\0*.bbf\0All Files(*.*)\0*.*\0\0";
  FileDlg.m_ofn.lpstrDefExt="bbf";
	
  if(FileDlg.DoModal() == IDOK )
   {

    FileName=FileDlg.GetPathName();







    }

     else return;

 }

 else if(flag==2)
 {


 }

 else return;
   ///////////////////////////////////////////////////////////////

    FILE *fp;
    errno_t err;//检测文件问题
    //	const char *filename = (LPCTSTR)FileName; //转换类型 重新赋予文件名

    LPCTSTR filename=FileName;  //防止0x73d311c7操作 0x00000004内存不能读

    if((err = fopen_s(&fp,filename,"w"))!=0)
	{
		CString TT;
		TT.Format("%s错误操作，文件不能写!!",filename);

           AfxMessageBox(TT);
	 return;
	}


       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 

  //当前打开的记忆文件名
  Current_Memory_File_Name = FileName;



    fprintf(fp,"# Brain Box File #\n\n");         //写入注释



    fprintf(fp,"ID_X=%d\n\n",YUAN_ID_X);   //写入当前ID命名数字





  YUAN_UNIT *tmp=YUAN;
  LINK_UNIT *linker_tmp;


  int i=0;


  for(;;) //遍历所有元
  {






      //--------------------------

        fprintf(fp,"[%d]\n",tmp->ID);       //写入ID编号

        fprintf(fp,"layer=%d\n",tmp->Layer);       //写入层级
                   
        fprintf(fp,"x=%d\n",tmp->x);             //写入坐标
        fprintf(fp,"y=%d\n",tmp->y);

        fprintf(fp,"threshold=%0.2f\n",tmp->threshold); //写入阀值


        fprintf(fp,"name=%s\n",tmp->name);    //写入 名字

        fprintf(fp,"mark=%s\n",tmp->Mark);    //写入 Mark
        //--------------------------

      fprintf(fp,"linker=");

      linker_tmp=tmp->linker; //把当前元的连接root赋予linker_tmp

      for(;;) //遍历所有连接
        {
           //写入连接者ID编号和连接强度
           fprintf(fp,"%d->%0.2f",linker_tmp->linker_ID,linker_tmp->linker_weight);       

           if(linker_tmp->next==NULL)
             {

              break;
             }

           fputc(',',fp);

           linker_tmp=linker_tmp->next;      

        }  //遍历所有连接END

     
     fputc('\n',fp);




/*

  int nn;
  CString Melody_TEXT;
  CString aaa;
  for(nn=0;nn<10;nn++)
     {
      aaa.Format("%d",tmp->Melody[nn]);
      Melody_TEXT+=aaa;
      Melody_TEXT+=" ";
     }
  Melody_TEXT.TrimRight(); //去除右边的空格

        fprintf(fp,"melody=%s\n",Melody_TEXT);    //写入旋律内容









fprintf(fp,"way=%s\n",tmp->Way);    //写入 输入[方法]












fprintf(fp,"way2=%s\n",tmp->Way2);    //写入 输出[方法]

*/


//--------------------------//写入 联系表
CONTACTS_UNIT *Contacts_tmp;

      fprintf(fp,"Contacts=");

      Contacts_tmp=tmp->Contacts; 

	  i=0;
      for(;;) //遍历所有联系表
        {
           
           fprintf(fp,"%s",Contacts_tmp->data);     


           fputc('$',fp);

           fprintf(fp,"%0.2f",Contacts_tmp->weight); 



           if(Contacts_tmp->next==NULL)
             {

              break;
             }

		   else  fputc('#',fp);

           Contacts_tmp=Contacts_tmp->next;   
		   i++;

        }  

     
 fputc('\n',fp);
//--------------------------



	 fputc('\n',fp);

     //--------------------------

    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;


  } //遍历所有元END














    fputc(0x1a,fp);               /*写入EOF*/

    fclose(fp);

  









}










void CBrainBoxDlg::Save_Memory_File_XML(int flag,CString FileName)
{
 // TODO: 在此添加控件通知处理程序代码


 if(flag==1)
 {
  CFileDialog FileDlg(FALSE);
  FileDlg.m_ofn.lpstrTitle="保存记忆文件";
  FileDlg.m_ofn.lpstrFilter="BrainBox文件(*.xml)\0*.xml\0All Files(*.*)\0*.*\0\0";
  FileDlg.m_ofn.lpstrDefExt="xml";
	
  if(FileDlg.DoModal() == IDOK )
   {

    FileName=FileDlg.GetPathName();

   }

     else return;

 }

 else if(flag==2)
 {


 }

 else return;
   ///////////////////////////////////////////////////////////////

    FILE *fp;
    errno_t err;//检测文件问题
    //	const char *filename = (LPCTSTR)FileName; //转换类型 重新赋予文件名

    LPCTSTR filename=FileName;  //防止0x73d311c7操作 0x00000004内存不能读

    if((err = fopen_s(&fp,filename,"w"))!=0)
	{
		CString TT;
		TT.Format("%s错误操作，文件不能写!!",filename);

           AfxMessageBox(TT);
	 return;
	}


       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 

  //当前打开的记忆文件名
  Current_Memory_File_Name = FileName;


    fprintf(fp,"<?xml version=\"1.0\" encoding=\"gb2312\" ?>\n");         //写入xml语言标识

    fprintf(fp,"<!--人工智能AiQi的记忆文件-->\n");         //写入注释
    fprintf(fp,"\n");


    fprintf(fp,"<记忆内容>\n");         //写入头
    fprintf(fp,"\n");




   // fprintf(fp," <计数>%d</计数>\n",YUAN_SUM);   //写入当前ID命名数字
   // fprintf(fp,"\n");




  YUAN_UNIT *tmp=YUAN;
  LINK_UNIT *linker_tmp;


  int i=0;
 int YUAN_index=0;

  for(;;) //遍历所有元
  {



        fprintf(fp," <概念 ID=\"%d\">\n",YUAN_index);       //写入ID编号

      //--------------------------

        fprintf(fp,"   <名称>%s</名称>\n",tmp->name);    //写入 名字




//--------------------------//写入 联系表数据

CONTACTS_UNIT *Contacts_tmp;

      fprintf(fp,"   <数据域>\n");

      Contacts_tmp=tmp->Contacts; 

	  i=0;
      for(;;) //遍历所有联系表
        {
           




           CString XT=Contacts_tmp->data; 

		  // XT.Replace( "<", NULL ); //有网页代码的情况下 防止和XML文件标签冲突
		  // XT.Replace( ">", NULL );







           fprintf(fp,"     <数据 ID=\"%d\" 权值=\"%0.2f\"><![CDATA[%s]]></数据>\n",i,Contacts_tmp->weight,XT);

           if(Contacts_tmp->next==NULL)
             {

              break;
             }



           Contacts_tmp=Contacts_tmp->next;   
		   i++;

        } 


      fprintf(fp,"   </数据域>");
     
 fputc('\n',fp);



        fprintf(fp,"   <层>%d</层>\n",tmp->Layer);       //写入层级
        fprintf(fp,"   <x>%d</x>\n",tmp->x);             //写入坐标
        fprintf(fp,"   <y>%d</y>\n",tmp->y);
        fprintf(fp,"   <激活阈值>%0.2f</激活阈值>\n",tmp->threshold); //写入阀值


        fprintf(fp,"   <标识>%s</标识>\n",tmp->Mark);    //写入 Mark

        //--------------------------//写入 连接者

      fprintf(fp,"   <连接>\n");


      linker_tmp=tmp->linker; //把当前元的连接root赋予linker_tmp

      for(;;) //遍历所有连接
        {
           //写入连接者ID编号和连接强度


           fprintf(fp,"     <来源 ID=\"%d\">%0.2f</来源>\n",linker_tmp->linker_ID,linker_tmp->linker_weight);

           if(linker_tmp->next==NULL)
             {

              break;
             }



           linker_tmp=linker_tmp->next;      

        }  //遍历所有连接END


      fprintf(fp,"   </连接>");

     
     fputc('\n',fp);





//--------------------------

        fprintf(fp," </概念>\n");       //写入ID尾

//--------------------------


	 fputc('\n\n',fp);

     //--------------------------

    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;

	YUAN_index++;


  } //遍历所有元END








    fprintf(fp,"</记忆内容>\n\n");         //写入尾





    //fputc(0x1a,fp);               /*写入EOF*/

    fclose(fp);

  



}








void CBrainBoxDlg::OnNew()
{
	// TODO: 在此添加控件通知处理程序代码



       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 
       YUAN_ID_X=0;


Current_Memory_File_Name = _T("");//当前打开的记忆文件名

 YUAN->FreeAll(YUAN);


//TEXT_OUT_BOX_CLS();

}





void CBrainBoxDlg::OnBnClickedButton_OnSetYuan()
{
	// TODO: 在此添加控件通知处理程序代码

    if(P_select_YUAN!=NULL) //如果有选中的元
	{
          CYuanSetDlg  dlg;

YUAN_RUN_MAIN_Flag=0; //关闭 元运行
          dlg.DoModal();
	}

}

void CBrainBoxDlg::OnBnClickedButton_OnSetYuanLink()
{
	// TODO: 在此添加控件通知处理程序代码

    if(select_linker_ID_1==-1 && select_linker_ID_2==-1) //如果没有有选中的连接
	{
         ;
	}
    else
        {
         CYuanLinkDlg  dlg;

         dlg.DoModal();
        }

}
void CBrainBoxDlg::OnBnClickedButton_OnDel()
{
	// TODO: 在此添加控件通知处理程序代码

    if(P_select_YUAN!=NULL && P_select_YUAN->ID!=0) //有选择的元
      {
        YUAN->Del_ID(P_select_YUAN->ID);

        P_select_YUAN=NULL;
      } 


    if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1) //有选择的连接
	 {
       YUAN->Del_a_link(select_linker_ID_1,select_linker_ID_2);

       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 
			 
	}

}

void CBrainBoxDlg::OnBnClickedButton_OnNewyuan()
{
	// TODO: 在此添加控件通知处理程序代码

  YUAN->New();

  YUAN->Set_Layer(YUAN_ID_X,0);

  //随机数发生器A—B 
  //得到一个随机坐标
  YUAN->Set_xy(YUAN_ID_X,Xrand(93,760),Xrand(140,480));

  YUAN->Set_threshold(YUAN_ID_X,YUAN->ID_return_P(YUAN_ID_X) ->threshold + (float)Xrand(1,1000)/100 ); //浮动值0.01~10;


}






void CBrainBoxDlg::OnBnClickedButton_OnSetYuanState()
{
	// TODO: 在此添加控件通知处理程序代码


    if(P_select_YUAN!=NULL && P_select_YUAN->ID!=0) //有选择的元
      {
        YUAN->Set_state(P_select_YUAN->ID,2);
        YUAN->Add_E_X(P_select_YUAN->ID,200);//增加表达强度效应增加200

      } 





}












void CBrainBoxDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


 YUAN_UNIT *tmp_YUAN=Get_mouse_down_YUAN(YUAN,point.x,point.y);

  if(P_select_YUAN!=NULL) //有选择的元
  {
   if(P_select_YUAN==tmp_YUAN)
     { 
      m_move_YUAN=TRUE;
 
      mouse_R_LineTo_xy.x=tmp_YUAN->x;
      mouse_R_LineTo_xy.y=tmp_YUAN->y;
     }

  }



	CDialog::OnRButtonDown(nFlags, point);
}

void CBrainBoxDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


  mouse_R_LineTo_xy=0;

 if(m_move_YUAN==TRUE  && P_select_YUAN!=NULL)
 {

  YUAN_UNIT *P_select_linker_YUAN=Get_mouse_down_YUAN(YUAN,point.x,point.y); //返回元的指针

  if(P_select_linker_YUAN!=NULL && P_select_linker_YUAN!=P_select_YUAN)
    {
      float fdz=(float)Xrand(1,1000)/100;//浮动值0.01~10
      YUAN->Link(P_select_YUAN->ID,P_select_linker_YUAN->ID,20+fdz);  //连接元
    }

   m_move_YUAN=FALSE; 

 }




	CDialog::OnRButtonUp(nFlags, point);
}




void CBrainBoxDlg::OnBnClickedButton3() //读取记忆文件
{
	// TODO: 在此添加控件通知处理程序代码

 //Load_Memory_File(1,"");
Load_Memory_File_XML(1,"");
}

void CBrainBoxDlg::OnBnClickedButton4()//保存记忆文件
{
	// TODO: 在此添加控件通知处理程序代码
 //Save_Memory_File(1,"");
Save_Memory_File_XML(1,"");
}
