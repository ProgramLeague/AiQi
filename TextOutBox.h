#ifndef _TEXT_OUT_BOX
#define _TEXT_OUT_BOX

#define TextOutBox_String_SUM 19






extern int hs;  //����


class TEXT_OUT_BOX
{ 

 public:

 int x;
 int y;

 unsigned long  TextColor;

 CString text;


};




extern TEXT_OUT_BOX TextOutBox[ TextOutBox_String_SUM ];



void TEXT_OUT_BOX_SAY(CString text); //�������� ѹ������
void TEXT_OUT_BOX_SAY_2(CString text,int flag); //�������� ѹ������


void TEXT_OUT_BOX_INIT();
void TEXT_OUT_BOX_OutAll(int X,int Y,int Size,int Spacing,CDC *pDC);
void TEXT_OUT_BOX_CLS();

void TextOut_SongTi(int x, int y,int size,unsigned long color,CString TT,CDC *pDC); //���������





#endif
