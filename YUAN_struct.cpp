#include "stdafx.h"
#include "YUAN_struct.h"


YUAN_UNIT *YUAN;

int YUAN_ID_X=0;                     //��¼������ID�仯
int YUAN_SUM=0;                      //��¼Ԫ������
int YUAN_Layer_SUM[8];             //��¼ÿ��Ԫ������
int YUAN_CONTACTS_SUM=0;            //��¼Ԫ����ϵ������


int A_time_max=200;                  //Ԫ���������ʱ��
int Wait_Start_Time_MAX=2;     //Ԫ�ȴ�����ʱ��
float LE=0.1f;                       //����ǿ�ȵ�����ֵ,ѧϰЧ��
float WL=0.1f;                       //����ǿ�������ӵ�  ԪFֵ�ı���
float fag_add=0.02f;             //Ԫƣ��ֵ���ӵ���ֵ
float fag_minus=0.01f;           //Ԫƣ��ֵ���ٵ���ֵ
float E_minus=0.1f;                  // ��Ӧǿ��˥��
int Learn_Ready_Time_MAX=0;      //ѧϰǿ��׼��ʱ��
float Forgot_Weight=0;           //������

///////////////////////////////////////////////////////////////////



void YUAN_UNIT::Init()
{
 int n;

 load_YUAN_config_file("config/YUAN.txt");       //��ȡYUAN�����ļ�


 this->ID=0;
 this->data=0;
 this->x=-10;
 this->y=-10;
 this->name="��";

 this->next=NULL;

 this->state=0;
 this->threshold=50;

 this->E=0;
 this->E_X=0;

 this->A_time=0;

 this->Wait_Start_Time=Wait_Start_Time_MAX;

 this->fag=0;

 this->Layer=0;

 this->Mark="��";



 this->linker=new LINK_UNIT;  //�����ڴ�
 this->linker->Init();


 this->Contacts=new CONTACTS_UNIT;  //�����ڴ�
 this->Contacts->Init();

 //��¼ÿ��Ԫ������
   for(n=0;n<8;n++)
   {
	YUAN_Layer_SUM[n]=0;
   }


}



void YUAN_UNIT::New()  //����һ���µ�Ԫ
{
  YUAN_UNIT *tmp=this;



  for(;;)
  {
    if(tmp->next==NULL)
	{

      YUAN_UNIT *tmp2= new YUAN_UNIT;  //�����ڴ�

      tmp->next=tmp2;


      YUAN_ID_X++; //��¼������ID�仯
	  YUAN_SUM++;

      tmp2->ID=YUAN_ID_X;
      tmp2->data=0;
      tmp2->x=10;
      tmp2->y=10;
      tmp2->name.Format("�¸���%d",YUAN_ID_X);
      tmp2->next=NULL;

      tmp2->state=0;
      tmp2->threshold=50;

      tmp2->E=0;
      tmp2->E_X=0;

      tmp2->A_time=0;

      tmp2->Wait_Start_Time=Wait_Start_Time_MAX;

      tmp2->fag=0;

	  tmp2->Layer=0;

	  tmp2->Learn_Ready_Time=0;//ѧϰ׼��ʱ��


	  tmp2->Mark="��";



	  tmp2->linker=new LINK_UNIT;  //�����ڴ�
      tmp2->linker->Init();


	  tmp2->Contacts=new CONTACTS_UNIT;  //�����ڴ�
	  tmp2->Contacts->Init();

     break;
	}
    tmp=tmp->next;

  }




}




void YUAN_UNIT::Set_xy(int ID,int x,int y)
{
  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {
    tmp->x=x;
    tmp->y=y; 
  }



}


void YUAN_UNIT::Set_data(int ID,int data)
{

  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {
   	tmp->data=data;  
  }



}



void YUAN_UNIT::Set_threshold(int ID,float threshold)
{

  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {
   	tmp->threshold=threshold;  
  }



}



void YUAN_UNIT::Set_name(int ID,CString name)
{
  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {
   	tmp->name=name;  
  }


}







void YUAN_UNIT::Set_E_X(int ID,float E_X)
{
  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {
   	tmp->E_X=E_X;  
  }


}


void YUAN_UNIT::Add_E_X(int ID,float E_X)
{
  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {
   	tmp->E_X+=E_X;  
  }


}



void YUAN_UNIT::Set_state(int ID,int state)
{
  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {
    if(state==1)
	{
   	  tmp->state=1; 
	  //tmp->A_time=A_time_max; //Ԫ������ʱʱ��
	}
    else if(state==0)
	{
   	  tmp->state=0; 
	 // tmp->A_time=0;
	}

    else if(state==2)
	{
   	  tmp->state=2; 

	}

  }


}



void YUAN_UNIT::Set_Layer(int ID,int Layer)
{

  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {

    if(Layer<=8)
   	tmp->Layer=Layer;
	
	else
    tmp->Layer=0;
  }



}




void YUAN_UNIT::Del_a_link(int ID1,int ID2)  //ɾ��ԪID1 �� ID2 ������
{

  YUAN_UNIT *tmp2=ID_return_P(ID2);

  if(tmp2!=NULL)
  {
   tmp2->linker->Del_Linker(ID1);	  
  }
  


}




void YUAN_UNIT::Linker_Weight_Change(int ID1,int ID2,float Change)  //�仯 ԪID1 �� ID2 ������Ȩֵ
{

  YUAN_UNIT *tmp2=ID_return_P(ID2);

  if(tmp2!=NULL)
  {
   tmp2->linker->Weight_Change(ID1,Change);	  
  }
  


}




void YUAN_UNIT::Del_ID_all_link(int ID) //ɾ��ID���У����⣩����
{
  YUAN_UNIT *tmp=this;


  for(;;)  //��������Ԫ
  {
    
    tmp->linker->Del_Linker(ID);

    if(tmp->next==NULL)  break;

    tmp=tmp->next;

  }



}






void YUAN_UNIT::Del_ID(int ID)
{
  YUAN_UNIT *tmp=this;
  YUAN_UNIT *tmp2=this;

  YUAN_UNIT *p,*q;

  for(;;)
  {

    if(tmp->next==NULL) break;

    p=tmp; q=tmp->next;

    if(q->ID==ID)
	{
          
         if(q->next==NULL)
           {
            p->next=NULL;
           }
 
         else{
              p->next=q->next;
             }

        tmp2->Del_ID_all_link(ID);
		// q->linker->FreeAll(q->linker);

        tmp2->Contacts->FreeAll(); //�ͷ�������ϵ��

          delete q;

		  YUAN_SUM--;

         break;
	}
    tmp=tmp->next;

  }




}





YUAN_UNIT *YUAN_UNIT::n_return_P(int n)
{
  YUAN_UNIT *tmp=this;
  YUAN_UNIT *tmp2=NULL;

  int m=0;

  for(;;)
  {
    


    if(m==n) 
      {
       tmp2=tmp;

       break;
      }

    if(tmp->next==NULL)  { tmp2=NULL;  break;  }

    tmp=tmp->next;

    m++;

  }

 return  tmp2;


}



YUAN_UNIT *YUAN_UNIT::name_return_P(CString name)
{
  YUAN_UNIT *tmp=this;
  YUAN_UNIT *tmp2=NULL;

  for(;;)
  {
    


    if(tmp->name==name) 
      {
       tmp2=tmp;

       break;
      }

    if(tmp->next==NULL)  { tmp2=NULL;  break;  }

    tmp=tmp->next;

  }

 return  tmp2;


}



YUAN_UNIT *YUAN_UNIT::ID_return_P(int ID)
{
  YUAN_UNIT *tmp=this;
  YUAN_UNIT *tmp2=NULL;

  for(;;)
  {
    


    if(tmp->ID==ID) 
      {
       tmp2=tmp;

       break;
      }

    if(tmp->next==NULL)  { tmp2=NULL;  break;  }

    tmp=tmp->next;

  }

 return  tmp2;


}







int YUAN_UNIT::Find_name_return_ID(CString name)
{
  int s=-1;

  YUAN_UNIT *tmp=this;

  if(name.IsEmpty()) {return s;}


  for(;;)
  {
    


    if(tmp->name==name) 
      {
       s=tmp->ID;

       break;
      }

    if(tmp->next==NULL)  {  break;  }

    tmp=tmp->next;

  }





  return s;
}




int YUAN_UNIT::Find_max_E_ID()
{
  int s=-1;

  YUAN_UNIT *tmp=this;

  float e=0;

  for(;;)
  {
    


    if(tmp->E > e) 
      {
       e=tmp->E;
       s=tmp->ID;
       

        
      }

    if(tmp->next==NULL)  {  break;  }

    tmp=tmp->next;

  }


  if(e>0) return s;


  else return -1;
}



YUAN_UNIT *YUAN_UNIT::Find_max_E_YUAN_P(float threshold,int mix_layer)
{
  YUAN_UNIT *tmp=this;
  YUAN_UNIT *tmp2=NULL;

  float e=0;

  for(;;)
  {
    

    if(tmp->state==1 && tmp->E>=threshold)
    {
     if(tmp->E > e && tmp->Layer>=mix_layer)
	 {


        tmp2=tmp;
        e=tmp->E;
  
	 }
    
	}


    if(tmp->next==NULL)  {   break;  }

    tmp=tmp->next;

  }

 return  tmp2;


}






YUAN_UNIT *YUAN_UNIT::Find_layer_max_E_YUAN_P(float threshold,int Layer)
{
  YUAN_UNIT *tmp=this;
  YUAN_UNIT *tmp2=NULL;

  float e=0;

  for(;;)
  {
    

    if(tmp->state==1 && tmp->E>=threshold && tmp->Layer==Layer)
    {
     if(tmp->E > e )
	 {


        tmp2=tmp;
        e=tmp->E;
  
	 }
    
	}


    if(tmp->next==NULL)  {   break;  }

    tmp=tmp->next;

  }

 return  tmp2;


}



bool YUAN_UNIT::Find_linker(int ID1,int ID2)  //����ԪID1 �� ID2 �������Ƿ����
{
  YUAN_UNIT *tmp1=ID_return_P(ID1);
  YUAN_UNIT *tmp2=ID_return_P(ID2);

  if(tmp2==NULL || tmp1==NULL )
  {
   return FALSE;	  
  }

  else
  {
   return  tmp2->linker->Find_linker_ID(ID1);

  }

}







bool YUAN_UNIT::Find_ID(int ID)
{
  YUAN_UNIT *tmp=ID_return_P(ID);

  if(tmp==NULL) return FALSE;

  else return TRUE;

}





void YUAN_UNIT::Link(int ID_1,int ID_2,float weight)  //����Ԫ
{
  if(Find_ID(ID_1)==TRUE && Find_ID(ID_2)==TRUE)
    {
	  YUAN_UNIT *tmp2=this->ID_return_P(ID_2);

	  if(tmp2->linker->Find_linker_ID(ID_1)==FALSE) //�鿴�Ƿ����
	  {

       tmp2->linker->New(ID_1);

	   tmp2->linker->Set_weight(ID_1,weight);

	  }

	  else
	  {

	  }



    }

}





float YUAN_UNIT::Get_linker_weight(int ID1,int ID2)  //�õ�ԪID1 �� ID2 ������ǿ��
{

  YUAN_UNIT *tmp2=ID_return_P(ID2);

  if(tmp2!=NULL)
  {
   return( tmp2->linker->Get_weight(ID1) );	  
  }
  
  else return(0);

}




void YUAN_UNIT::Set_linker_weight(int ID_1,int ID_2,float weight)  //��������ǿ��
{
  if(Find_ID(ID_1)==TRUE && Find_ID(ID_2)==TRUE) //�鿴Ԫ�Ƿ����
    {
	  YUAN_UNIT *tmp2=this->ID_return_P(ID_2);

	  if(tmp2->linker->Find_linker_ID(ID_1)==TRUE) //�鿴�����Ƿ����
	  {

	   tmp2->linker->Set_weight(ID_1,weight);

	  }




    }

}



void YUAN_UNIT::Set_linker_weight_ADD(int ID_1,int ID_2,float ADD)  //��������ǿ����ֵ���ֵ
{
  if(Find_ID(ID_1)==TRUE && Find_ID(ID_2)==TRUE) //�鿴Ԫ�Ƿ����
    {
	  YUAN_UNIT *tmp2=this->ID_return_P(ID_2);

	  if(tmp2->linker->Find_linker_ID(ID_1)==TRUE) //�鿴�����Ƿ����
	  {

	   tmp2->linker->Set_weight_ADD(ID_1,ADD);

	  }




    }

}





void YUAN_UNIT::FreeAll(YUAN_UNIT *root)
{
  YUAN_UNIT *tmp=root;

   tmp->x=-10;
   tmp->y=-10;
   tmp->state=0;
   tmp->threshold=50;
   tmp->name="��";

  for(;;)
  {

    if(tmp->next==NULL) break;

   tmp->Del_ID(tmp->next->ID);


   //tmp=tmp->next;





  }




}









void YUAN_UNIT::Learning()
{


  LINK_UNIT *linker_tmp;







       linker_tmp=this->linker;

       for(;;) //������������
	  {

           //IF��������Ԫ�Ǽ���״̬
           if(YUAN->ID_return_P(linker_tmp->linker_ID) ->state==1)
             {
              linker_tmp->linker_weight +=  LE;  //����ǿ����ѧϰЧ��
              
             }


           if(linker_tmp->next==NULL)
	     {
              break;
	     }

           linker_tmp=linker_tmp->next;      

	 }  //������������END












}







//�õ�ĳID��Ԫ,��������Ԫ����ϵ�������
void YUAN_UNIT::Get_Link_List(int ID,CString *LL,int *sum)
{
  YUAN_UNIT *tmp=this;


  int ID1=ID;
  int ID2=0;

  CString link_list,ns;
  link_list.Empty();

  int link_sum=0;

  for(;;)
  {
    
    ID2=tmp->ID;

    if(ID1!=ID2 && Find_linker(ID1,ID2)==1)
      {
       ns.Format("%d ",ID2);

       link_list += ns;
       link_sum++;

      }


    if(tmp->next==NULL)  {   break;  }

    tmp=tmp->next;

  }





  *LL=link_list;
  *sum=link_sum;


}






void load_YUAN_config_file(char filename[])       //��ȡYUAN�����ļ�
{

 

 FILE *fp;
 errno_t err;//����ļ�����

 int n;
 float f;
 int end=0;

 if((err = fopen_s(&fp,filename,"r")) !=0 )
    {
     AfxMessageBox("config/YUAN.txtû���ҵ�!");

    }

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%d",&n);

 A_time_max=n;  //Ԫ���������ʱ��

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%d",&n);

 Wait_Start_Time_MAX=n;  //Ԫ�ȴ�����ʱ��

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%f",&f);

 LE=f;  //����ǿ�ȵ�����ֵ,ѧϰЧ��

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%f",&f);

 WL=f;  //����ǿ�������ӵ�  ԪFֵ�ı���

  //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61
 }

 fscanf_s(fp,"%f",&f);

 fag_add=f;  //Ԫƣ��ֵ���ӵ���ֵ

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61
 }

 fscanf_s(fp,"%f",&f);

 fag_minus=f;  //Ԫƣ��ֵ���ٵ���ֵ

 //------------------
 while(1)
 {
  if(fgetc(fp)==61)break;   //61
 }

 fscanf_s(fp,"%f",&f);

 E_minus=f;  // ��Ӧǿ��˥��ֵ

 //------------------




 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%d",&n);

 Learn_Ready_Time_MAX=n;   //����ѧϰ

 //------------------



 while(1)
 {
  if(fgetc(fp)==61)break;   /*61 =*/
 }

 fscanf_s(fp,"%f",&f);

 Forgot_Weight=f;   //������
 //------------------


 fclose(fp);

}


















//////////////////////��ϵ�����  ��ʱ����

void YUAN_UNIT::Add_Contacts(CString text)  //���� Ԫ��һ����ϵ������
{
 YUAN_UNIT *tmp=this;

 tmp->Contacts->New(text);


}



void YUAN_UNIT::Del_Contacts(CString text)  //ɾ�� Ԫ��һ����ϵ������
{

 YUAN_UNIT *tmp=this;

 tmp->Contacts->Del(text);
  


}



void YUAN_UNIT::Set_Contacts(CString text)  //�޸� Ԫ��һ����ϵ������
{
 YUAN_UNIT *tmp=this;

 tmp->Contacts->Set_data(text);


}







void YUAN_UNIT::Set_Mark(int ID,CString Mark_Text)
{
  YUAN_UNIT *tmp=ID_return_P(ID);


  if(tmp!=NULL)
  {



   	tmp->Mark=Mark_Text;

  }


}
