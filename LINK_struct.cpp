

#include "stdafx.h"
#include "LINK_struct.h"







///////////////////////////////////////////////////////////////////



void LINK_UNIT::Init()
{

 this->linker_ID=0;
 this->linker_weight=50;
 this->next=NULL;
}





LINK_UNIT *LINK_UNIT::ID_return_P(int ID)
{
  LINK_UNIT *tmp=this;
  LINK_UNIT *tmp2=NULL;

  for(;;)
  {
    


    if(tmp->linker_ID==ID) 
      {
       tmp2=tmp;

       break;
      }

    if(tmp->next==NULL)  { tmp2=NULL;  break;  }

    tmp=tmp->next;

  }

 return  tmp2;


}





void LINK_UNIT::New(int linker_ID)
{
  LINK_UNIT *tmp=this;



  for(;;)
  {
    if(tmp->next==NULL)
	{

      LINK_UNIT *tmp2= new LINK_UNIT;  //分配内存

      tmp->next=tmp2;


      tmp2->linker_ID=linker_ID;
      tmp2->linker_weight=0;
      tmp2->next=NULL;

     break;
	}
    tmp=tmp->next;

  }




}


float LINK_UNIT::Get_weight(int linker_ID)
{
  LINK_UNIT *tmp=ID_return_P(linker_ID);


  if(tmp!=NULL)
  {
   return(tmp->linker_weight);  
  }

  else return(0);

}




void LINK_UNIT::Set_weight(int linker_ID,float linker_weight)
{
  LINK_UNIT *tmp=ID_return_P(linker_ID);


  if(tmp!=NULL)
  {
   	tmp->linker_weight=linker_weight;  
  }



}




void LINK_UNIT::Set_weight_ADD(int linker_ID,float ADD)
{
  LINK_UNIT *tmp=ID_return_P(linker_ID);


  if(tmp!=NULL)
  {
   	tmp->linker_weight += ADD;  
  }



}





void LINK_UNIT::Weight_Change(int linker_ID,float Change)
{
  LINK_UNIT *tmp=ID_return_P(linker_ID);
  float old_weight;

  if(tmp!=NULL)
  {
    old_weight=linker_weight;

    tmp->linker_weight += Change;  //加减变化

      if(tmp->linker_weight>=0 && old_weight<=0)
        {
         tmp->linker_weight=0;
        }
      if(tmp->linker_weight<=0 && old_weight>=0)
        {
         tmp->linker_weight=0; 
        }

      if(tmp->linker_weight==0)
        {
         this->Del_Linker(linker_ID);
        }
 

  }



}

void LINK_UNIT::Del_Linker(int linker_ID)
{
  LINK_UNIT *tmp=this;

  LINK_UNIT *p,*q;

  for(;;)
  {

    if(tmp->next==NULL) break;

    p=tmp; q=tmp->next;

    if(q->linker_ID==linker_ID)
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


/*

void LINK_UNIT::FreeAll()
{
  LINK_UNIT *tmp=this;
  LINK_UNIT *tmp2;

  for(;;)
  {
    tmp2=tmp;

    tmp=tmp->next;

     delete tmp2;

    if(tmp==NULL) break;

  }


}


*/


void LINK_UNIT::FreeAll()
{
  LINK_UNIT *tmp=this;

  for(;;)
  {

    if(tmp->next==NULL) break;

   tmp->Del_Linker(tmp->next->linker_ID);


  }

}




bool LINK_UNIT::Find_linker_ID(int linker_ID)
{

  LINK_UNIT *tmp=ID_return_P(linker_ID);


  if(tmp!=NULL)
  {
   return TRUE;
  }

  else 
  {
   return FALSE;
  }

}
