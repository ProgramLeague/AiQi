

#include "stdafx.h"
#include "Contacts_Struct.h"







///////////////////////////////////////////////////////////////////



void CONTACTS_UNIT::Init() //root
{
 this->ID = 0;
 this->weight = 60;
 this->data = "新数据（该数据未编辑）";
 this->next = NULL;
}






void CONTACTS_UNIT::New(CString data)
{
  CONTACTS_UNIT *tmp=this;



  for(;;)
  {
    if(tmp->next==NULL)
	{

      CONTACTS_UNIT *tmp2= new CONTACTS_UNIT;  //分配内存

      tmp->next=tmp2;


      tmp2->ID=0;
      tmp2->weight = 60;
      tmp2->data = data;
      tmp2->next=NULL;

     break;
	}
    tmp=tmp->next;

  }




}




void CONTACTS_UNIT::Set_data(CString data)
{
  CONTACTS_UNIT *tmp=data_return_P(data);


  if(tmp!=NULL)
  {
   	tmp->data=data;  
  }


}


/*
void CONTACTS_UNIT::Set_data(int ID,CString data) //可以为链表root赋值
{
  CONTACTS_UNIT *tmp=this;


  if(tmp->next==NULL && ID==0)
  {
      tmp->ID=ID;
      tmp->data = data;
      tmp->next=NULL;

  }

  else
  {
   for(;;)
   {
    if(tmp->next==NULL)
	{

      CONTACTS_UNIT *tmp2= new CONTACTS_UNIT;  //分配内存

      tmp->next=tmp2;


      tmp2->ID=ID;
      tmp2->data = data;
      tmp2->next=NULL;

     break;
	}
    tmp=tmp->next;

   }
  }


}

*/


void CONTACTS_UNIT::Set_data(int index,CString data)//根据链表顺序设置数据
{
  CONTACTS_UNIT *tmp=this;

  int n=0;

   for(;;)
   {
    if(n==index)
      {
       tmp->ID=index;
       tmp->data=data;
       break;
      }

    if(tmp->next==NULL)
	{
         break;
	}
    tmp=tmp->next;

    n++;

   }



}







void CONTACTS_UNIT::Add(CString data,float weight)
{
  CONTACTS_UNIT *tmp=this;
  int ID=  this->Get_Sum();





   for(;;)
   {
    if(tmp->next==NULL)
	{

      CONTACTS_UNIT *tmp2= new CONTACTS_UNIT;  //分配内存

      tmp->next=tmp2;


      tmp2->ID=ID;
	  tmp2->weight = weight;
      tmp2->data = data;
      tmp2->next=NULL;

     break;
	}
    tmp=tmp->next;

   }
  


}








CString CONTACTS_UNIT::Get_n_data(int n)//根据链表顺序得到数据
{
  CONTACTS_UNIT *tmp=this;
  CString data;

  data.Empty();

  int i=0;

   for(;;)
   {
    if(i==n)
      {
        data=tmp->data;
       break;
      }

    if(tmp->next==NULL)
	{
         break;
	}
    tmp=tmp->next;

    i++;

   }

 return data;

}






float CONTACTS_UNIT::Get_n_weight(int n)//根据链表顺序得到数据权值
{
  CONTACTS_UNIT *tmp=this;
  float weight=0;



  int i=0;

   for(;;)
   {
    if(i==n)
      {
        weight=tmp->weight;
       break;
      }

    if(tmp->next==NULL)
	{
         break;
	}
    tmp=tmp->next;

    i++;

   }

 return weight;

}





void CONTACTS_UNIT::Set_weight(int index,float weight)//根据链表顺序设置权值
{
  CONTACTS_UNIT *tmp=this;

int n=0;

   for(;;)
   {
    if(n==index)
      {
       tmp->weight=weight;

       break;
      }

    if(tmp->next==NULL)
	{
         break;
	}
    tmp=tmp->next;


   n++;


   }



}





void CONTACTS_UNIT::Set_weight_ADD(int index,float ADD)//根据链表顺序设置权值增量
{
  CONTACTS_UNIT *tmp=this;

int n=0;

   for(;;)
   {
    if(n==index)
      {
       tmp->weight+=ADD;

       break;
      }

    if(tmp->next==NULL)
	{
         break;
	}
    tmp=tmp->next;


   n++;


   }



}




CONTACTS_UNIT *CONTACTS_UNIT::ID_return_P(int ID)
{
  CONTACTS_UNIT *tmp=this;
  CONTACTS_UNIT *tmp2=NULL;

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






CONTACTS_UNIT *CONTACTS_UNIT::data_return_P(CString data)
{
  CONTACTS_UNIT *tmp=this;
  CONTACTS_UNIT *tmp2=NULL;

  for(;;)
  {
    


    if(tmp->data==data) 
      {
       tmp2=tmp;

       break;
      }

    if(tmp->next==NULL)  { tmp2=NULL;  break;  }

    tmp=tmp->next;

  }

 return  tmp2;


}









void CONTACTS_UNIT::Del(int ID)
{
  CONTACTS_UNIT *tmp=this;

  CONTACTS_UNIT *p,*q;

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

         delete q; 

         break;
	}
    tmp=tmp->next;

  }




}



void CONTACTS_UNIT::Del(CString data)
{
  CONTACTS_UNIT *tmp=this;

  CONTACTS_UNIT *p,*q;

  for(;;)
  {

    if(tmp->next==NULL) break;

    p=tmp; q=tmp->next;

    if(q->data==data)
	{
          
         if(q->next==NULL)
           {
            p->next=NULL;
           }
 
         else{
              p->next=q->next;
             }

         delete q; 

         break;
	}
    tmp=tmp->next;

  }




}







void CONTACTS_UNIT::Del_All_Child()
{


  CONTACTS_UNIT *p=this;
  CONTACTS_UNIT *q,*s;


 s=p->next;


 for(;;)
 {
	 
  if(s==NULL) { break;}
  q=s->next;


  delete s;



  s=q;
 }

p->next=NULL;



}





void CONTACTS_UNIT::FreeAll()
{

  CONTACTS_UNIT *p=this;
  CONTACTS_UNIT *s;
 
for(;;)
{
 if(p->next==NULL) break;

 s=p->next;
 
 delete p;

 p=s;
}




}


/*

void CONTACTS_UNIT::FreeAll()
{
  CONTACTS_UNIT *tmp=this;

  for(;;)
  {

    if(tmp->next==NULL) break;

   tmp->Del(tmp->next->ID);


  }

}

*/









int CONTACTS_UNIT::Get_Sum()
{
  CONTACTS_UNIT *tmp=this;

  int l=0;

  for(;;)
  {
    l++;

    if(tmp->next==NULL)
	{


         break;
	}
    tmp=tmp->next;

  }


 return l;

}



int CONTACTS_UNIT::Find_Data_Return_N(CString data)
{
  CONTACTS_UNIT *tmp=this;

  int n=-1;
  int index=0;

  for(;;)
  {
    


    if(tmp->data==data) 
      {
       n=-2;
       break;
      }

    if(tmp->next==NULL)
	{

         break;
	}

    tmp=tmp->next;

    index++;

  }


 if(n==-2) n=index;

 return  n;





}