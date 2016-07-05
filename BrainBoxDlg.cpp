// BrainBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AiQi.h"
#include "BrainBoxDlg.h"

#include "YUAN_struct.h"
#include "YUAN_system.h"

#include "YuanSetDlg.h" //�ҵĶԻ�������
#include "YuanLinkDlg.h" //�ҵĶԻ�������

#include "TextOutBox.h" //�������

#include "MyColor.h" //��ɫ����


// CBrainBoxDlg �Ի���

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


// CBrainBoxDlg ��Ϣ�������

void CBrainBoxDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ





    if(nIDEvent==2) //2�Ŷ�ʱ���������; ��ʾ���
      {






      //���°�ť״̬
      if(P_select_YUAN==NULL) //�����ѡ�е�Ԫ
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


	  if(BST_CHECKED==((CButton*)GetDlgItem(IDC_BRAINBOX_CHECK1))->GetCheck()) //�ж�Check�Ƿ�ѡ��
	  {
       show_YUAN_E=1;
	  }

	  else
		  show_YUAN_E=0;



       if(select_linker_ID_1==-1 && select_linker_ID_2==-1) //���û����ѡ�е�����
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



       //ˢ����ʾ��Ļ
       OnPaint();
 
      }


	CDialog::OnTimer(nIDEvent);
}

void CBrainBoxDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()





CDC *pDC=GetDC();



//˫������ʾ///////////////////////////////////////////

int nWidth=800,nHeight=620;

  CString TT;
  YUAN_UNIT *tmp=YUAN;

CDC MemDC; //����һ����ʾ�豸����
CBitmap MemBitmap;//����һ��λͼ����
MemDC.CreateCompatibleDC(NULL);//��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight); //���潨��һ������Ļ��ʾ���ݵ�λͼ�����ڵĴ�С
CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap); //��λͼѡ�뵽�ڴ���ʾ�豸��


MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));

//��ͼ------------------------------------------------


  CPen pen1,pen2,pen3;

  pen1.CreatePen(PS_SOLID,1,RGB(0,0,0));
  pen2.CreatePen(PS_DOT,1,RGB(190,190,190)); 
  pen3.CreatePen(PS_SOLID,1,RGB(180,180,180));



  if(YUAN_RUN_MAIN_Flag==1) //���� Ԫ����  ��ֹ���ݹ�����ʾ��������
  //������Ԫ
  Draw_All_YUAN(&MemDC);




  //��ʾ���׼������������
   if( mouse_R_LineTo_xy.x!=0 &&  mouse_R_LineTo_xy.y!=0)
   {
     MemDC.SelectObject(&pen2);
     MemDC.MoveTo(mouse_R_LineTo_xy);
     MemDC.LineTo(mouse_xy);
	 MemDC.SelectObject(&pen1);
   }

  //��ʾ����϶�Բ����ʾ
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


 
   TT.Format("ID=%d  threshold=%0.2f  x=%d  y=%d  �ַ�=%s  state=%d  A_time=%d",tmp->ID,tmp->threshold,tmp->x,tmp->y,tmp->name,tmp->state,tmp->A_time);

   MemDC.TextOut(px,py,TT);

    if(tmp->next==NULL)
	{

     break;
	}

    tmp=tmp->next;

    py+=18;

  }







//��ʾѡ���Ԫ��ID���
if(P_select_YUAN!=NULL)
   TT.Format("select_YUAN=%d",P_select_YUAN->ID);
else
   TT.Format("select_YUAN=û��");

   MemDC.TextOut(580,0,TT);


//��ʾ��ѡ�������

   TT.Format("linker= %d to %d  w=%0.2f",select_linker_ID_1,select_linker_ID_2,YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2) );
   MemDC.TextOut(580,20,TT);





 }


















/////��ʾ��Ϣ/////////////////

CString YUAN_Data_Text;

//����
  CPen pen4;
  pen4.CreatePen(PS_SOLID,1,RGB(242,242,242)); 

          MemDC.SelectObject(&pen4);
          MemDC.MoveTo(0,595); 
          MemDC.LineTo(800,595);


YUAN_Data_Text.Format("%d,%d ",mouse_xy.x,mouse_xy.y); //��ʾ����
  TextOut_SongTi(740,600, 14,RGB(232,232,232),YUAN_Data_Text,&MemDC);





       //��ѡ���Ԫ
       if(P_select_YUAN!=NULL) 
         {

           YUAN_Data_Text.Format("����ID��%d  ���ƣ�%s  ״̬��%d  ��ֵ��%0.2f  ƣ��ֵ��%0.2f  ��Ծǿ��ֵ��%0.2f",P_select_YUAN->ID,P_select_YUAN->name,P_select_YUAN->state,P_select_YUAN->threshold,P_select_YUAN->fag,P_select_YUAN->E);
		     
             TextOut_SongTi(4,600, 14,DARKGRAY,YUAN_Data_Text,&MemDC);

         }








   //ѡ������


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


              YUAN_Data_Text.Format("��ȡ�������ӣ������ӣ�%d -> %d  ǿ�ȣ�%0.2f + %0.2f��  ",select_linker_ID_1,select_linker_ID_2,YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2), cE);
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





              YUAN_Data_Text.Format("��ȡ˫�����ӣ������ӣ�%d -> %d  ǿ�ȣ�%0.2f + %0.2f�� �����ӣ�%d -> %d  ǿ�ȣ�%0.2f + %0.2f��  ",select_linker_ID_1,select_linker_ID_2,YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2) , cE ,select_linker_ID_2,select_linker_ID_1,YUAN->Get_linker_weight(select_linker_ID_2,select_linker_ID_1) ,dE);
             





             }







          TextOut_SongTi(4,600, 14,DARKGRAY,YUAN_Data_Text,&MemDC);

         }






//------------------------------------------------

pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY); //���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ

MemDC.SelectObject(pOldBit); //��ͼ��ɺ������
MemBitmap.DeleteObject();
MemDC.DeleteDC(); 














}

int CBrainBoxDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������


  hIcon=AfxGetApp()->LoadIcon(IDI_BrainBox);  //���崰��ͼ��
  CBrainBoxDlg::SendMessage(WM_SETICON,ICON_SMALL,(LPARAM)hIcon);  //������Ϣ���Ĵ���ͼ��



 SetTimer(2,100,NULL);  //��Ļ��ʾ 



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










void CBrainBoxDlg::Draw_YUAN(int x, int y,int state,int Layer,CDC *pDC) //��Ԫ
{

  int dx;

  CBitmap bitmap;   //����ͼλ����
  bitmap.LoadBitmap(IDB_BMP_YUAN);  //����ͼλ���� ID

  CDC dcMemory;  //����CDC����
  dcMemory.CreateCompatibleDC(pDC);  //������pDC���ݵ��ڴ��豸����
  dcMemory.SelectObject(&bitmap);  //��ͼλѡ���ڴ��豸������

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
   pDC->BitBlt(x-8,y-8,16,16,&dcMemory,dx,0,SRCCOPY);  //���ڴ��豸�������Ƶ���ǰ�豸������
  }
  else if(state==1)
  {
   pDC->BitBlt(x-8,y-8,16,16,&dcMemory,dx+16,0,SRCCOPY);  //���ڴ��豸�������Ƶ���ǰ�豸������
  }


}







void CBrainBoxDlg::Draw_YUAN_2(int x, int y,int state,float E,int Layer,CDC *pDC) //��Ԫ
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



void CBrainBoxDlg::Draw_YUAN_name(int x, int y,float F,CString TT,CDC *pDC) //��Ԫ������
{

  int size=(int)F+100;

  CFont font,*oldfont;

  font.CreatePointFont(size,"����",NULL);

  oldfont=pDC->SelectObject(&font);

 

  pDC->SetTextColor(RGB(0,0,255));
  pDC->SetBkMode(TRANSPARENT);

  pDC->TextOut(x-10,y-40-(int)(F/10),TT);

  pDC->SelectObject(oldfont);
 

}


void CBrainBoxDlg::Draw_YUAN_name_2(int x, int y,int state,CString TT,CDC *pDC) //��Ԫ������
{

  int size=100;

  int x_py;
  int Length=TT.GetLength();
  x_py=x-Length*12/2/2-1;

  CFont font,*oldfont;



  font.CreatePointFont(size,"����",NULL);

  oldfont=pDC->SelectObject(&font);

  if(state==0)
   {

     pDC->SetTextColor(RGB(132,132,132));
     pDC->SetBkMode(TRANSPARENT);

     pDC->TextOut(x_py,y-8,TT);

   }


  else if(state==1)
   {
     //font.CreatePointFont(size+5,"����",NULL);
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

    //������

  tmp=YUAN;

  LINK_UNIT *linker_tmp;

  int x1,y1,x2,y2;

  for(;;) //����Ԫ
  {




   //����Ԫ��ϵ��
   CONTACTS_UNIT *P_YUAN_Contacts;
   CString RR;
   P_YUAN_Contacts=tmp->Contacts;

   for(;;)
   {


             int aa;
             YUAN_UNIT *tmp2=NULL;


    if(P_YUAN_Contacts->data.Find("<��>")==0) //��ǰ���ݴ�<��>��ǩ
	{

     RR=P_YUAN_Contacts->data;
     RR.Replace( " ", NULL);
     RR.Replace( "<��>", NULL);

         if(!RR.IsEmpty())
           {

             aa=YUAN->Find_name_return_ID(RR); //�����Ƿ���һ�������Ԫ

             if(aa!=-1)
                 {
                    tmp2 = YUAN->ID_return_P(aa);

                   //������
			
                   x1=tmp->x;
	               y1=tmp->y;

	               x2=tmp2->x;
	               y2=tmp2->y;

                   pDC->SelectObject(&pen3);
                   pDC->MoveTo(x1,y1);
		           pDC->LineTo(x2,y2);



                  //�������ʶ
		         int px=x2,py=y2,a;
		           a=ASK_a(x2,y2,x1,y1);
                   MOVE_TO3(a,&px,&py,10);
		           pDC->SelectObject(&pen3);
                   pDC->Rectangle(px-1,py-1,px+3,py+3);

                 }

           }


	}




    if(P_YUAN_Contacts->data.Find("<���>")==0) //��ǰ���ݴ�[���]��ǩ
	{

     RR=P_YUAN_Contacts->data;
     RR.Replace( " ", NULL);
     RR.Replace( "<���>", NULL);

         if(!RR.IsEmpty())
           {

             aa=YUAN->Find_name_return_ID(RR); //�����Ƿ���һ�������Ԫ

             if(aa!=-1)
                 {
                    tmp2 = YUAN->ID_return_P(aa);

                   //������
			
                   x1=tmp->x;
	               y1=tmp->y;

	               x2=tmp2->x;
	               y2=tmp2->y;

                   pDC->SelectObject(&pen3);
                   pDC->MoveTo(x1,y1);
		           pDC->LineTo(x2,y2);



                  //�������ʶ
		         int px=x2,py=y2,a;
		           a=ASK_a(x2,y2,x1,y1);
                   MOVE_TO3(a,&px,&py,10);
		           pDC->SelectObject(&pen3);
                   pDC->Rectangle(px-1,py-1,px+3,py+3);

                 }

           }


	}

    if(P_YUAN_Contacts->data.Find("<����>")==0) //��ǰ���ݴ�<����>��ǩ
	{

     RR=P_YUAN_Contacts->data;
     RR.Replace( " ", NULL);
     RR.Replace( "<����>", NULL);

         if(!RR.IsEmpty())
           {

             aa=YUAN->Find_name_return_ID(RR); //�����Ƿ���һ�������Ԫ

             if(aa!=-1)
                 {
                    tmp2 = YUAN->ID_return_P(aa);

                   //������
			
                   x1=tmp->x;
	               y1=tmp->y;

	               x2=tmp2->x;
	               y2=tmp2->y;

                   pDC->SelectObject(&pen4);
                   pDC->MoveTo(x1,y1);
		           pDC->LineTo(x2,y2);


                  //�������ʶ
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

   //������ϵ��end










    linker_tmp=tmp->linker;

    for(;;)
	{

        x1=YUAN->ID_return_P(linker_tmp->linker_ID) ->x;
	    y1=YUAN->ID_return_P(linker_tmp->linker_ID) ->y;

	    x2=tmp->x;
	    y2=tmp->y;

        if(linker_tmp->linker_ID!=0)
		{
         //������
			

         pDC->SelectObject(&pen1);
         pDC->MoveTo(x1,y1);
		 pDC->LineTo(x2,y2);
          

/*
		 //����ѡ�����
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
         //�������ʶ
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



          //����ѡ�����
   if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1)
   {
          x1=YUAN->ID_return_P(select_linker_ID_1) ->x;
          y1=YUAN->ID_return_P(select_linker_ID_1) ->y;
          x2=YUAN->ID_return_P(select_linker_ID_2) ->x;
          y2=YUAN->ID_return_P(select_linker_ID_2) ->y;


          pDC->SelectObject(&pen2);
          pDC->MoveTo(x1,y1); 
          pDC->LineTo(x2,y2);


          //�������ʶ
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

  for(;;) //��Ԫ
  {

    Draw_YUAN_2(tmp->x,tmp->y,tmp->state,tmp->E,tmp->Layer,pDC); //��Ԫ

   if(show_YUAN_E==TRUE)  //��ʾԪ��Ծǿ��ֵ
   {
    pDC->SetTextColor(RGB(0,0,0));

    TT.Format("%0.2f",tmp->E);

    pDC->TextOut(tmp->x-10,tmp->y-24,TT);
   }


   if(show_YUAN_name==TRUE)  //��ʾԪ���ı�
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
      Draw_YUAN_name(tmp->x,tmp->y,tmp->E,tmp->name,pDC); //��Ԫ������

	  else
      Draw_YUAN_name(tmp->x,tmp->y,0,tmp->name,pDC); //��Ԫ������

	}
*/


    if(tmp->ID!=0)
	{
     Draw_YUAN_name_2(tmp->x,tmp->y,tmp->state,tmp->name,pDC); //��Ԫ������

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









  CBrush *brush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //����͸�������ɫ
  pDC->SelectObject(brush);



  //��� ��ѡ���Ԫ
  if(P_select_YUAN!=NULL)
    {
     pDC->SelectObject(&pen5);
     pDC->Ellipse(P_select_YUAN->x-15,P_select_YUAN->y-15,P_select_YUAN->x+15,P_select_YUAN->y+15);

    }



}















YUAN_UNIT * CBrainBoxDlg::Get_mouse_down_YUAN(YUAN_UNIT *root, int mouse_x, int mouse_y)  //�����������Ԫ��ָ��
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

mouse_xy=point;
/*
mouse_xy.x -= 20;
mouse_xy.y -= 20;
*/

	CDialog::OnMouseMove(nFlags, point);
}

void CBrainBoxDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ




/*
 CString Status_Bar_text;



   Status_Bar_text.Format("Ready");
  ((CMainFrame*)GetParent())->SetMessageText(Status_Bar_text);  
*/

 //ȡ������ѡ��
 select_linker_ID_1=-1;
 select_linker_ID_2=-1; 

 select_linker_sum=0;


//ѡ��Ԫ----------------------------

 
  P_select_YUAN=Get_mouse_down_YUAN(YUAN,point.x,point.y); //����Ԫ��ָ��



  if(P_select_YUAN!=NULL) //��ѡ���Ԫ
  {
   m_move_YUAN=TRUE;

   mouse_L_Move_YUAN_xy.x=P_select_YUAN->x;
   mouse_L_Move_YUAN_xy.y=P_select_YUAN->y;

   goto selectEND;

  }



//ѡ������----------------------------



  Select_Linker(&select_linker_ID_1,&select_linker_ID_2,mouse_xy.x,mouse_xy.y); 

   if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1)
   {
      P_select_YUAN=NULL;

     select_linker_sum=0;

     bool fl;

     //����ԪID2 �� ID1 �������Ƿ���� 
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ



    //------------------

     if(nChar==VK_DELETE)   //��Delete��(46) ɾ��һ��Ԫ ����һ������
	 {

           if(P_select_YUAN!=NULL && P_select_YUAN->ID!=0) //��ѡ���Ԫ
             {
               YUAN->Del_ID(P_select_YUAN->ID);

			   P_select_YUAN=NULL;

			  
             } 


           if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1) //��ѡ�������
		   {
             YUAN->Del_a_link(select_linker_ID_1,select_linker_ID_2);

             select_linker_ID_1=-1;
             select_linker_ID_2=-1; 
			 
		   }


	 }



 

    //------------------

     if(nChar==13)   // �س�
	 {
      ;

     }

    //------------------









	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}










CString CBrainBoxDlg::CString_Extraction_Content(CString text,CString a,CString b)   //�ַ�����ȡ�м�����
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
 // TODO: �ڴ���ӿؼ�֪ͨ����������

 if(flag==1)
 {
  CFileDialog FileDlg(TRUE);
  FileDlg.m_ofn.lpstrTitle="�򿪼����ļ�";
  FileDlg.m_ofn.lpstrFilter="Brain Box�ļ�(*.xml)\0*.xml\0All Files(*.*)\0*.*\0\0";

	
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

     errno_t err;//����ļ�����
    //	const char *filename = (LPCTSTR)FileName; //ת������ ���¸����ļ���

    LPCTSTR filename=FileName;  //��ֹ0x73d311c7���� 0x00000004�ڴ治�ܶ�

    if((err=fopen_s(&fp,filename,"r")) !=0)
	{

		CString TT;
		TT.Format("%s����������ļ����ܶ�!!",filename);

           AfxMessageBox(TT);
           return;

	}



       char ch;
       int nn,i;
	   int end=0;
	   float f;

 int z1,z2;
       int index;


  //��ǰ�򿪵ļ����ļ���
  Current_Memory_File_Name = FileName;



       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 


   TEXT_OUT_BOX_CLS();

       YUAN->FreeAll(YUAN);  //�������

	   

	   YUAN_UNIT *tmp_YUAN;

	   
       YUAN_SUM=0;  //Ԫ������Ϊ0

     YUAN_ID_X=0;

	 index=0;
 //--------------------------
//��ȡ�ļ����ַ���

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

 a="<���� ID";
 b="</����>";

 CString TmpStr2;
 CString TmpCC;
  CString TmpTT;

 a_len = a.GetLength();
 b_len = b.GetLength();



 while(end!=1)
 {


  nStart=FileStr.Find(a,nStart)+a_len;
  nEnd=FileStr.Find(b,nStart);


  TmpStr2=FileStr.Mid(nStart,nEnd-nStart); //�õ�һ��Ԫ����

  //-------------------------------
/*
    //��ȡID���

      TmpCC=CString_Extraction_Content(TmpStr2,"=\"","\">");   //�ַ�����ȡ�м�����
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



     //��ȡ���Ʊ�ʶ-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<����>","</����>");   //�ַ�����ȡ�м�����
      

      tmp_YUAN->name=TmpCC;
//TT.Format("name=%s",TmpCC);
//AfxMessageBox(TT);


    //��ȡԪ����-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<������>","</������>");   //�ַ�����ȡ�м�����




//TT.Format("������=%s",TmpCC);
//AfxMessageBox(TT);



 int aa_len,bb_len,nnStart,nnEnd;
 nnStart=0;

 CString aa,bb;

 aa="<���� ID";
 bb="/����>";

 CString TmpStr3;



 aa_len = aa.GetLength();
 bb_len = bb.GetLength();

 nn=0;

 while(1)
 {


  nnStart=TmpCC.Find(aa,nnStart)+aa_len;
  nnEnd=TmpCC.Find(bb,nnStart);


  TmpStr3=TmpCC.Mid(nnStart,nnEnd-nnStart); //�õ�һ��������
  //----------
   //TT.Format("�������ַ���=%s",TmpStr3);
   //AfxMessageBox(TT);

   TmpTT=CString_Extraction_Content(TmpStr3,"Ȩֵ=\"","\">");   //�ַ�����ȡ�м�����
   f=atof(TmpTT); //�õ�Ȩֵ

 
   TmpTT.Empty();
   TmpTT=CString_Extraction_Content(TmpStr3,"CDATA[","]]>");   //�ַ�����ȡ�м�����
     //�õ�������
   if(TmpTT.IsEmpty()==1) TmpTT="o^_^o";



  
   //TT.Format("��ȡȨֵ=%0.2f ��ȡ����=%s",f,TmpTT);
  // AfxMessageBox(TT);

     if(nn==0) //�������ϵ��ROOT
	 {
      tmp_YUAN->Contacts->Set_data(0,TmpTT); //���浽��ϵ��ROOT��
	 }
	 else
	 {
      tmp_YUAN->Contacts->Add(TmpTT,0); //���浽��ϵ����
	 }

    tmp_YUAN->Contacts->Set_weight(nn,f);//����Ȩֵ



  //----------
  nnStart=nnEnd+bb_len; //��һ�������ݵĿ�ʼλ��

  if( TmpCC.Find(bb,nnStart)==-1) {break;} //�����һ���������˳�

  nn++;

 }




    //��ȡ�㼶-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<��>","</��>");   //�ַ�����ȡ�м�����
      z1=atoi(TmpCC);

      tmp_YUAN->Layer=z1;

//TT.Format("Layer=%d",z1);
//AfxMessageBox(TT);

    //��ȡxy-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<x>","</x>");   //�ַ�����ȡ�м�����
      z1=atoi(TmpCC);

      tmp_YUAN->x=z1;

//TT.Format("x=%d",z1);
//AfxMessageBox(TT);

      TmpCC=CString_Extraction_Content(TmpStr2,"<y>","</y>");   //�ַ�����ȡ�м�����
      z1=atoi(TmpCC);

      tmp_YUAN->y=z1;

//TT.Format("y=%d",z1);
//AfxMessageBox(TT);

	 //��ȡ������ֵ-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<������ֵ>","</������ֵ>");   //�ַ�����ȡ�м�����

      f=atof(TmpCC);

      tmp_YUAN->threshold=f;

//TT.Format("threshold=%f",f);
//AfxMessageBox(TT);

     //��ȡMark��ʶ-----------------
      TmpCC=CString_Extraction_Content(TmpStr2,"<��ʶ>","</��ʶ>");   //�ַ�����ȡ�м�����
      

      tmp_YUAN->Mark=TmpCC;
//TT.Format("Mark=%s",TmpCC);
//AfxMessageBox(TT);


     //��ȡ���ӹ�ϵ-----------------


      TmpCC=CString_Extraction_Content(TmpStr2,"<����>","</����>");   //�ַ�����ȡ�м�����




//TT.Format("��������=%s",TmpCC);
//AfxMessageBox(TT);




 nnStart=0;



 aa="<��Դ ID";
 bb="/��Դ>";




 aa_len = aa.GetLength();
 bb_len = bb.GetLength();



 while(1)
 {


  nnStart=TmpCC.Find(aa,nnStart)+aa_len;
  nnEnd=TmpCC.Find(bb,nnStart);


  TmpStr3=TmpCC.Mid(nnStart,nnEnd-nnStart); //�õ�һ��������
  //----------

 // if(index==68)
 // {
  //  TT.Format("����������=%s",TmpStr3);
 //   AfxMessageBox(TT);
 // }

   TmpTT=CString_Extraction_Content(TmpStr3,"=\"","\"");   //�ַ�����ȡ�м�����
   z1=atoi(TmpTT); //�õ�ID

   TmpTT=CString_Extraction_Content(TmpStr3,">","<");   //�ַ�����ȡ�м�����
     //�õ�����ǿ��
   f=atof(TmpTT);
 // if(index==68)
 // {
  //  TT.Format("��ȡID=%d ����ǿ��=%0.2f",z1,f);
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
  nnStart=nnEnd+bb_len; //��һ�������ݵĿ�ʼλ��

  if( TmpCC.Find(bb,nnStart)==-1) {break;} //�����һ���������˳�



 }


  //-------------------------------











  nStart=nEnd+b_len; //��һ��Ԫ�Ŀ�ʼλ��




  if( FileStr.Find(b,nStart)==-1) {end=1;break;} //�����һ��Ԫ�˳�



  index++;


 }



}





void CBrainBoxDlg::Load_Memory_File(int flag,CString FileName)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

 if(flag==1)
 {
  CFileDialog FileDlg(TRUE);
  FileDlg.m_ofn.lpstrTitle="�򿪼����ļ�";
  FileDlg.m_ofn.lpstrFilter="Brain Box�ļ�(*.bbf)\0*.bbf\0All Files(*.*)\0*.*\0\0";

	
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

     errno_t err;//����ļ�����
    //	const char *filename = (LPCTSTR)FileName; //ת������ ���¸����ļ���

    LPCTSTR filename=FileName;  //��ֹ0x73d311c7���� 0x00000004�ڴ治�ܶ�

    if((err=fopen_s(&fp,filename,"r")) !=0)
	{

		CString TT;
		TT.Format("%s����������ļ����ܶ�!!",filename);

           AfxMessageBox(TT);
           return;

	}

  //��ǰ�򿪵ļ����ļ���
  Current_Memory_File_Name = FileName;



       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 


   TEXT_OUT_BOX_CLS();

       YUAN->FreeAll(YUAN);  //�������

	   int tmp_ID_X;
       char ch;
       int n,i,ctr;
	   int end=0;
	   float f;
	   YUAN_UNIT *tmp_YUAN;

	   
       YUAN_SUM=0;  //Ԫ������Ϊ0

 /*--------------------------*/
 /*��ȡID����*/
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

         /*��ȡID���*/

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

          if(ch==EOF)    /*�ļ���β �˳�ѭ��*/
		  {
           end=1;
           break;
		  }

		 }

         if(end==1) break;

         /*��ȡ�㼶*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%d",&i);
         tmp_YUAN->Layer=i;



         /*��ȡ����X*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%d",&i);
         tmp_YUAN->x=i;


         /*��ȡ����Y*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%d",&i);
         tmp_YUAN->y=i;


         /*��ȡ��ֵ*/
         while(1)
		 {
          if(fgetc(fp)==61)break;   /*61 =*/
		 }

         fscanf_s(fp,"%f",&f);
         tmp_YUAN->threshold=f;





         /*��ȡ�ı�*/
         while(1)     //ѭ��ǰ���ж��Ƿ�"="
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
 








         //��ȡMark���
         while(1)     //ѭ��ǰ���ж��Ƿ�"="
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






        //��ȡ������ID���  ����ǿ��

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

         //��ȡ ��ϵ���ַ�������
         while(1)     //ѭ��ǰ���ж��Ƿ�"="
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





         while(1) //���ַ���
		 {

          CString tmpch;


          ch=fgetc(fp);  



		   if(ch=='\n')//
		   { 
            

              if(index==0) //�������ϵ��ROOT
			  {
                if(ctr==0) TT="o^_^o";

                tmp_YUAN->Contacts->Set_data(0,TT); //���浽��ϵ����
			  }
			  else
			  {
                if(ctr==0) TT="o^_^o";
                tmp_YUAN->Contacts->Add(TT,0); //���浽��ϵ����
			  }

              Contacts_end=1;
			  break; 



		   }






		   if(ch==36)// Ϊ�ַ�"$"
		   { 

              if(index==0) //�������ϵ��ROOT
			  {
                if(ctr==0) TT="o^_^o";

                tmp_YUAN->Contacts->Set_data(0,TT); //���浽��ϵ����
			  }
			  else
			  {
                if(ctr==0) TT="o^_^o";
                tmp_YUAN->Contacts->Add(TT,0); //���浽��ϵ����
			  }


			  break; 

		   }







           tmpch.Format("%c",ch);

           TT+=tmpch;

          ctr++;

		 }

           if(Contacts_end==1) break;


             //��Ȩֵ
             fscanf_s(fp,"%f",&f);
			 tmp_YUAN->Contacts->Set_weight(index,f);//��������˳������Ȩֵ


           while(1)
		   {
            if(fgetc(fp)==35)break;   //Ϊ�ַ�"#"
			if(fgetc(fp)=='\n'){Contacts_end=1;break;}   //Ϊ�ַ�"����"
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������


 if(flag==1)
 {
  CFileDialog FileDlg(FALSE);
  FileDlg.m_ofn.lpstrTitle="��������ļ�";
  FileDlg.m_ofn.lpstrFilter="BrainBox�ļ�(*.bbf)\0*.bbf\0All Files(*.*)\0*.*\0\0";
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
    errno_t err;//����ļ�����
    //	const char *filename = (LPCTSTR)FileName; //ת������ ���¸����ļ���

    LPCTSTR filename=FileName;  //��ֹ0x73d311c7���� 0x00000004�ڴ治�ܶ�

    if((err = fopen_s(&fp,filename,"w"))!=0)
	{
		CString TT;
		TT.Format("%s����������ļ�����д!!",filename);

           AfxMessageBox(TT);
	 return;
	}


       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 

  //��ǰ�򿪵ļ����ļ���
  Current_Memory_File_Name = FileName;



    fprintf(fp,"# Brain Box File #\n\n");         //д��ע��



    fprintf(fp,"ID_X=%d\n\n",YUAN_ID_X);   //д�뵱ǰID��������





  YUAN_UNIT *tmp=YUAN;
  LINK_UNIT *linker_tmp;


  int i=0;


  for(;;) //��������Ԫ
  {






      //--------------------------

        fprintf(fp,"[%d]\n",tmp->ID);       //д��ID���

        fprintf(fp,"layer=%d\n",tmp->Layer);       //д��㼶
                   
        fprintf(fp,"x=%d\n",tmp->x);             //д������
        fprintf(fp,"y=%d\n",tmp->y);

        fprintf(fp,"threshold=%0.2f\n",tmp->threshold); //д�뷧ֵ


        fprintf(fp,"name=%s\n",tmp->name);    //д�� ����

        fprintf(fp,"mark=%s\n",tmp->Mark);    //д�� Mark
        //--------------------------

      fprintf(fp,"linker=");

      linker_tmp=tmp->linker; //�ѵ�ǰԪ������root����linker_tmp

      for(;;) //������������
        {
           //д��������ID��ź�����ǿ��
           fprintf(fp,"%d->%0.2f",linker_tmp->linker_ID,linker_tmp->linker_weight);       

           if(linker_tmp->next==NULL)
             {

              break;
             }

           fputc(',',fp);

           linker_tmp=linker_tmp->next;      

        }  //������������END

     
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
  Melody_TEXT.TrimRight(); //ȥ���ұߵĿո�

        fprintf(fp,"melody=%s\n",Melody_TEXT);    //д����������









fprintf(fp,"way=%s\n",tmp->Way);    //д�� ����[����]












fprintf(fp,"way2=%s\n",tmp->Way2);    //д�� ���[����]

*/


//--------------------------//д�� ��ϵ��
CONTACTS_UNIT *Contacts_tmp;

      fprintf(fp,"Contacts=");

      Contacts_tmp=tmp->Contacts; 

	  i=0;
      for(;;) //����������ϵ��
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


  } //��������ԪEND














    fputc(0x1a,fp);               /*д��EOF*/

    fclose(fp);

  









}










void CBrainBoxDlg::Save_Memory_File_XML(int flag,CString FileName)
{
 // TODO: �ڴ���ӿؼ�֪ͨ����������


 if(flag==1)
 {
  CFileDialog FileDlg(FALSE);
  FileDlg.m_ofn.lpstrTitle="��������ļ�";
  FileDlg.m_ofn.lpstrFilter="BrainBox�ļ�(*.xml)\0*.xml\0All Files(*.*)\0*.*\0\0";
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
    errno_t err;//����ļ�����
    //	const char *filename = (LPCTSTR)FileName; //ת������ ���¸����ļ���

    LPCTSTR filename=FileName;  //��ֹ0x73d311c7���� 0x00000004�ڴ治�ܶ�

    if((err = fopen_s(&fp,filename,"w"))!=0)
	{
		CString TT;
		TT.Format("%s����������ļ�����д!!",filename);

           AfxMessageBox(TT);
	 return;
	}


       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 

  //��ǰ�򿪵ļ����ļ���
  Current_Memory_File_Name = FileName;


    fprintf(fp,"<?xml version=\"1.0\" encoding=\"gb2312\" ?>\n");         //д��xml���Ա�ʶ

    fprintf(fp,"<!--�˹�����AiQi�ļ����ļ�-->\n");         //д��ע��
    fprintf(fp,"\n");


    fprintf(fp,"<��������>\n");         //д��ͷ
    fprintf(fp,"\n");




   // fprintf(fp," <����>%d</����>\n",YUAN_SUM);   //д�뵱ǰID��������
   // fprintf(fp,"\n");




  YUAN_UNIT *tmp=YUAN;
  LINK_UNIT *linker_tmp;


  int i=0;
 int YUAN_index=0;

  for(;;) //��������Ԫ
  {



        fprintf(fp," <���� ID=\"%d\">\n",YUAN_index);       //д��ID���

      //--------------------------

        fprintf(fp,"   <����>%s</����>\n",tmp->name);    //д�� ����




//--------------------------//д�� ��ϵ������

CONTACTS_UNIT *Contacts_tmp;

      fprintf(fp,"   <������>\n");

      Contacts_tmp=tmp->Contacts; 

	  i=0;
      for(;;) //����������ϵ��
        {
           




           CString XT=Contacts_tmp->data; 

		  // XT.Replace( "<", NULL ); //����ҳ���������� ��ֹ��XML�ļ���ǩ��ͻ
		  // XT.Replace( ">", NULL );







           fprintf(fp,"     <���� ID=\"%d\" Ȩֵ=\"%0.2f\"><![CDATA[%s]]></����>\n",i,Contacts_tmp->weight,XT);

           if(Contacts_tmp->next==NULL)
             {

              break;
             }



           Contacts_tmp=Contacts_tmp->next;   
		   i++;

        } 


      fprintf(fp,"   </������>");
     
 fputc('\n',fp);



        fprintf(fp,"   <��>%d</��>\n",tmp->Layer);       //д��㼶
        fprintf(fp,"   <x>%d</x>\n",tmp->x);             //д������
        fprintf(fp,"   <y>%d</y>\n",tmp->y);
        fprintf(fp,"   <������ֵ>%0.2f</������ֵ>\n",tmp->threshold); //д�뷧ֵ


        fprintf(fp,"   <��ʶ>%s</��ʶ>\n",tmp->Mark);    //д�� Mark

        //--------------------------//д�� ������

      fprintf(fp,"   <����>\n");


      linker_tmp=tmp->linker; //�ѵ�ǰԪ������root����linker_tmp

      for(;;) //������������
        {
           //д��������ID��ź�����ǿ��


           fprintf(fp,"     <��Դ ID=\"%d\">%0.2f</��Դ>\n",linker_tmp->linker_ID,linker_tmp->linker_weight);

           if(linker_tmp->next==NULL)
             {

              break;
             }



           linker_tmp=linker_tmp->next;      

        }  //������������END


      fprintf(fp,"   </����>");

     
     fputc('\n',fp);





//--------------------------

        fprintf(fp," </����>\n");       //д��IDβ

//--------------------------


	 fputc('\n\n',fp);

     //--------------------------

    if(tmp->next==NULL)
      {
       break;
      }

    tmp=tmp->next;

	YUAN_index++;


  } //��������ԪEND








    fprintf(fp,"</��������>\n\n");         //д��β





    //fputc(0x1a,fp);               /*д��EOF*/

    fclose(fp);

  



}








void CBrainBoxDlg::OnNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������



       P_select_YUAN=NULL;
       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 
       YUAN_ID_X=0;


Current_Memory_File_Name = _T("");//��ǰ�򿪵ļ����ļ���

 YUAN->FreeAll(YUAN);


//TEXT_OUT_BOX_CLS();

}





void CBrainBoxDlg::OnBnClickedButton_OnSetYuan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

    if(P_select_YUAN!=NULL) //�����ѡ�е�Ԫ
	{
          CYuanSetDlg  dlg;

YUAN_RUN_MAIN_Flag=0; //�ر� Ԫ����
          dlg.DoModal();
	}

}

void CBrainBoxDlg::OnBnClickedButton_OnSetYuanLink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

    if(select_linker_ID_1==-1 && select_linker_ID_2==-1) //���û����ѡ�е�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

    if(P_select_YUAN!=NULL && P_select_YUAN->ID!=0) //��ѡ���Ԫ
      {
        YUAN->Del_ID(P_select_YUAN->ID);

        P_select_YUAN=NULL;
      } 


    if(select_linker_ID_1!=-1 && select_linker_ID_2!=-1) //��ѡ�������
	 {
       YUAN->Del_a_link(select_linker_ID_1,select_linker_ID_2);

       select_linker_ID_1=-1;
       select_linker_ID_2=-1; 
			 
	}

}

void CBrainBoxDlg::OnBnClickedButton_OnNewyuan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

  YUAN->New();

  YUAN->Set_Layer(YUAN_ID_X,0);

  //�����������A��B 
  //�õ�һ���������
  YUAN->Set_xy(YUAN_ID_X,Xrand(93,760),Xrand(140,480));

  YUAN->Set_threshold(YUAN_ID_X,YUAN->ID_return_P(YUAN_ID_X) ->threshold + (float)Xrand(1,1000)/100 ); //����ֵ0.01~10;


}






void CBrainBoxDlg::OnBnClickedButton_OnSetYuanState()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


    if(P_select_YUAN!=NULL && P_select_YUAN->ID!=0) //��ѡ���Ԫ
      {
        YUAN->Set_state(P_select_YUAN->ID,2);
        YUAN->Add_E_X(P_select_YUAN->ID,200);//���ӱ��ǿ��ЧӦ����200

      } 





}












void CBrainBoxDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


 YUAN_UNIT *tmp_YUAN=Get_mouse_down_YUAN(YUAN,point.x,point.y);

  if(P_select_YUAN!=NULL) //��ѡ���Ԫ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


  mouse_R_LineTo_xy=0;

 if(m_move_YUAN==TRUE  && P_select_YUAN!=NULL)
 {

  YUAN_UNIT *P_select_linker_YUAN=Get_mouse_down_YUAN(YUAN,point.x,point.y); //����Ԫ��ָ��

  if(P_select_linker_YUAN!=NULL && P_select_linker_YUAN!=P_select_YUAN)
    {
      float fdz=(float)Xrand(1,1000)/100;//����ֵ0.01~10
      YUAN->Link(P_select_YUAN->ID,P_select_linker_YUAN->ID,20+fdz);  //����Ԫ
    }

   m_move_YUAN=FALSE; 

 }




	CDialog::OnRButtonUp(nFlags, point);
}




void CBrainBoxDlg::OnBnClickedButton3() //��ȡ�����ļ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

 //Load_Memory_File(1,"");
Load_Memory_File_XML(1,"");
}

void CBrainBoxDlg::OnBnClickedButton4()//��������ļ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
 //Save_Memory_File(1,"");
Save_Memory_File_XML(1,"");
}
