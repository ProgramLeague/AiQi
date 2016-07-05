

#include "stdafx.h"
#include "TextOutBox.h"

#include "MyColor.h"


TEXT_OUT_BOX TextOutBox[ TextOutBox_String_SUM ];



int hs=0;



///////////////////////////////////////////////////////////////////

void TEXT_OUT_BOX_INIT()
{
 for(int n=0;n<TextOutBox_String_SUM;n++)
 {
  TextOutBox[n].text=_T(" ");

  TextOutBox[n].TextColor = 0;

 }



}






void TextOut_SongTi(int x, int y,int size,unsigned long color,CString TT,CDC *pDC) //输出宋体字
{



  CFont font,*oldfont;

  font.CreatePointFont(size+100,"宋体",NULL);

  oldfont=pDC->SelectObject(&font);

 

  pDC->SetTextColor(color);
  pDC->SetBkMode(TRANSPARENT);

  pDC->TextOut(x,y,TT);

  pDC->SelectObject(oldfont);
 

}




void TEXT_OUT_BOX_OutAll(int X,int Y,int Size,int Spacing,CDC *pDC)
{
  int x=X,y=Y;
  int n;


  for(n=0;n<TextOutBox_String_SUM;n++)
    {


     TextOut_SongTi(x, y,Size, TextOutBox[n].TextColor,TextOutBox[n].text,pDC); //输出宋体字

     y+=Spacing;

    }


}









void TEXT_OUT_BOX_SAY(CString text, unsigned long  TextColor) //数据输入 压入数组
{

 int n;

 if(hs<TextOutBox_String_SUM-1)
   {
    TextOutBox[hs].text=text;

    TextOutBox[hs].TextColor=TextColor;
    hs++;  
    
 
   }

 else 
   {
  //  hs=TextOutBox_String_SUM-1;



      for(n=0;n<TextOutBox_String_SUM-1;n++)
         {

          TextOutBox[n].text=TextOutBox[n+1].text;

          TextOutBox[n].TextColor=TextOutBox[n+1].TextColor;
         }




      TextOutBox[hs].text=text;

      TextOutBox[hs].TextColor=TextColor;

   }



}







void TEXT_OUT_BOX_SAY_2(CString text,int flag) //数据输入 压入数组
{
  CString SYS_text;
  CString AI_text;
  CString Ren_text;

  CTime time = CTime::GetCurrentTime();
  CString TTime = time.Format("%H:%M:%S");






  SYS_text.Format("系统： %s ",TTime);
  AI_text.Format("电脑： %s ",TTime);
  Ren_text.Format("我： %s ",TTime);




         if(flag==0) {  TEXT_OUT_BOX_SAY(SYS_text,BLUE); }
    else if(flag==1) {  TEXT_OUT_BOX_SAY(AI_text,BLUE); }
    else if(flag==2) {  TEXT_OUT_BOX_SAY(Ren_text,BLUE); }
    else  {  TEXT_OUT_BOX_SAY(" ",BLACK);  }


  CString tmp_text(" ");
  tmp_text+=text;
  TEXT_OUT_BOX_SAY(tmp_text,BLACK); 



  //空行
  TEXT_OUT_BOX_SAY("",WHITE); 


}








void TEXT_OUT_BOX_CLS()
{
 for(int n=0;n< TextOutBox_String_SUM-1 ;n++)
 {
  TextOutBox[n].text=_T(" ");

 }

 hs=0;

}







