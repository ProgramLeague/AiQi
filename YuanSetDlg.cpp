// YuanSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AiQi.h"
#include "YuanSetDlg.h"
#include "YUAN_struct.h"
#include "YUAN_system.h"
#include "Contacts_Struct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CYuanSetDlg dialog


CYuanSetDlg::CYuanSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYuanSetDlg::IDD, pParent)


	, nItem(0)
	, nSubItem(0)
	, nItem_0(0)
	, nSubItem_0(0)
	, ListControl_ID_X(0)
	, m_x_hang(0)
	, m_x_lie(0)
	, m_List_Control_edited(0)
	, m_Mark(_T(""))
{



	//{{AFX_DATA_INIT(CYuanSetDlg)
	m_ID = P_select_YUAN->ID;
	m_text = P_select_YUAN->name;
	m_threshold = P_select_YUAN->threshold;
	m_Layer = P_select_YUAN->Layer;
    m_Mark = P_select_YUAN->Mark;


	//}}AFX_DATA_INIT

nItem_0=-100;
 nSubItem_0=-100;

 SetRect(&m_RECT_List_Control_edited,0,0,0,0);
 SetRect(&m_RECT_List_Control_edited0,0,0,0,0);



}


void CYuanSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYuanSetDlg)
	DDX_Text(pDX, IDC_YuanSetDlg_EDIT1, m_ID);
	DDX_Text(pDX, IDC_YuanSetDlg_EDIT5, m_text);
	DDX_Text(pDX, IDC_YuanSetDlg_EDIT4, m_threshold);
	DDX_Text(pDX, IDC_YuanSetDlg_EDIT6, m_Layer);
	//}}AFX_DATA_MAP


	DDX_Control(pDX, IDC_LISTBOX_Contacts2, m_ListBox_Contacts2);
	DDX_Text(pDX, IDC_EDIT1, m_x_hang);
	DDX_Text(pDX, IDC_EDIT3, m_x_lie);
	DDX_Text(pDX, IDC_YuanSetDlg_EDIT7, m_Mark);
}


BEGIN_MESSAGE_MAP(CYuanSetDlg, CDialog)
	//{{AFX_MSG_MAP(CYuanSetDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CYuanSetDlg::OnBnClickedButton1)
	ON_WM_CREATE()

	ON_BN_CLICKED(IDC_BUTTON3, &CYuanSetDlg::OnBnClickedButton3)
	//ON_WM_LBUTTONDOWN()
	//ON_LBN_SELCHANGE(IDC_LISTBOX_Contacts, &CYuanSetDlg::OnLbnSelchangeListboxContacts)

	ON_NOTIFY(NM_CLICK, IDC_LISTBOX_Contacts2, &CYuanSetDlg::OnNMClickListboxContacts2)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYuanSetDlg message handlers



BOOL CYuanSetDlg::OnInitDialog() //��ʼ������
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��




 //��ȡѡ��Ԫ����ϵ�� ��ʼ��
  CONTACTS_UNIT *tmp=P_select_YUAN->Contacts;




//����listctrl �����չ���
LONG lStyle;
lStyle = GetWindowLong(m_ListBox_Contacts2.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
lStyle |= LVS_REPORT; //����style
SetWindowLong(m_ListBox_Contacts2.m_hWnd, GWL_STYLE, lStyle);//����style

DWORD dwStyle = m_ListBox_Contacts2.GetExtendedStyle();
dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
m_ListBox_Contacts2.SetExtendedStyle(dwStyle); //������չ���





//���� ��
m_ListBox_Contacts2.InsertColumn( 0, "ID", LVCFMT_LEFT, 40 );//������ 
m_ListBox_Contacts2.InsertColumn(1,"����",LVCFMT_LEFT,310);
m_ListBox_Contacts2.InsertColumn(2,"Ȩֵ",LVCFMT_LEFT,60);





 //��ȡѡ��Ԫ����ϵ�� ��ʼ��listctrl
  CONTACTS_UNIT *tmp2=P_select_YUAN->Contacts;
  int hang=0;
  CString TT;

  for(;;)
  {
    //�������
    TT.Format("%d",tmp2->ID);
    m_ListBox_Contacts2.InsertItem(hang,TT);//������

    m_ListBox_Contacts2.SetItemText( hang,1, tmp2->data);//��������
    TT.Format("%.2f",tmp2->weight);
    m_ListBox_Contacts2.SetItemText( hang,2, TT);//��������

    if(tmp2->next==NULL)
	{
         break;
	}


    tmp2=tmp2->next;
	hang++;

  }


  ListControl_ID_X=hang;//��¼ID����



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}














void CYuanSetDlg::OnOK() //ȷ������
{
 // TODO: Add extra validation here





//����ListControl����Ϣ
P_select_YUAN->Contacts->Del_All_Child(); //ɾ�������ӽڵ���Ϣ ������

CString str,str2;
int MaxHang = m_ListBox_Contacts2.GetItemCount(); //�õ�����
int MaxLie =2;


//str=m_ListBox_Contacts2.GetItemText(i,j);  //i���У�j����
  str=m_ListBox_Contacts2.GetItemText(0,1);  //i���У�j���� 
  P_select_YUAN->Contacts->Set_data(0,str); //0�� ���浽��ϵ��root��

str=m_ListBox_Contacts2.GetItemText(0,2);  //i���У�j����
P_select_YUAN->Contacts->Set_weight(0,float(_tstof(str)));

for(int index=1; index < MaxHang; index++)
{
//��ȡListControl 0�е���Ϣ
str=m_ListBox_Contacts2.GetItemText(index,1);  //i���У�j����  ��ȡ����
str2=m_ListBox_Contacts2.GetItemText(index,2);  //i���У�j����  ��ȡȨֵ

P_select_YUAN->Contacts->Add(str,float(_tstof(str2))); //���浽��ϵ����


}






 //����������Ϣ
 UpdateData();

 YUAN->Set_Layer(m_ID,m_Layer);

 YUAN->Set_threshold(m_ID,m_threshold);


 if(m_text.IsEmpty()) m_text.Format("����%d",m_ID);

 YUAN->Set_name(m_ID,m_text);


 if(m_Mark.IsEmpty()) m_Mark="��";

 YUAN->Set_Mark(m_ID,m_Mark);


 UpdateData(FALSE);





 CDialog::OnOK();
}






void CYuanSetDlg::OnBnClickedButton1() //����һ����ϵ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������




ListControl_ID_X++;

int index = m_ListBox_Contacts2.GetItemCount(); //�õ�����

CString TT;
//TT.Format("%d",index);
TT.Format("%d",ListControl_ID_X);

m_ListBox_Contacts2.InsertItem(index,TT);//������  ����ID
m_ListBox_Contacts2.SetItemText( index,1, "�����ݣ�������δ�༭��");//�������� ����
m_ListBox_Contacts2.SetItemText( index,2, "0");//�������� Ȩֵ


 UpdateData(0);

}











void CYuanSetDlg::OnBnClickedButton3()  //ɾ��������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������



int nChoice=m_ListBox_Contacts2.GetNextItem(-1,LVNI_SELECTED);//���ѡ����.



if(nChoice!=-1)//������ѡ����ʱ
{
	if(nChoice==0)
      AfxMessageBox(_T("��һ�����ݲ���ɾ����ֻ�ܱ༭")); 


	else
	{
	 m_ListBox_Contacts2.DeleteItem(nChoice);//ɾ����.�� 

     m_List_Control_edited=0;
   ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_X),SW_HIDE);

	}
} 
else
{         
	AfxMessageBox(_T("��û��ѡ�����е���Ŀ���޷�ɾ�����ݣ����Ƚ���ѡ��")); 
} 







UpdateData(0);




}










//ͨ��ListControl�к��еõ���Ŀ���������
CString CYuanSetDlg::GetListControlItemText(HWND hWnd, int nItem, int nSubItem)
{
 LVITEM lvi;
 memset(&lvi, 0, sizeof(LVITEM));
 lvi.iSubItem = nSubItem;
 CString str;
 int nLen = 128;
 int nRes;

  nLen *= 2;
  lvi.cchTextMax = nLen;
  lvi.pszText = str.GetBufferSetLength(nLen);
  nRes = (int)::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)nItem,(LPARAM)&lvi);


  str.ReleaseBuffer();


 return str;

}



//�����NM_CLICK��Ӧ�����û����ListControl�κ�λ��ʱ���ͻ��Ӧ����һ��Edit Box���������޸�����
void CYuanSetDlg::OnNMClickListboxContacts2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������


 Invalidate();
 HWND hWnd1 = ::GetDlgItem (m_hWnd, IDC_LISTBOX_Contacts2);
 LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
 RECT rect;      //get the row number
 nItem = temp->iItem;     //get the column number
 nSubItem = temp->iSubItem;





 m_x_hang=nItem; 
 m_x_lie=nSubItem;


 Invalidate();






  CString str = GetListControlItemText(hWnd1,nItem  ,nSubItem);
  RECT rect1,rect2; // this macro is used to retrieve the Rectanle
  // of the selected SubItem
  ListView_GetSubItemRect(hWnd1,temp->iItem,  temp->iSubItem,LVIR_BOUNDS,&rect);
  //Get the Rectange of the listControl
  ::GetWindowRect(temp->hdr.hwndFrom,&rect1);
  //Get the Rectange of the Dialog
  ::GetWindowRect(m_hWnd,&rect2);
  int x=rect1.left-rect2.left;
  int y=rect1.top-rect2.top;

 UpdateData(0);

 //�༭��IDC_EDIT_X������
 m_RECT_List_Control_edited.left=rect.left+x    +5;
 m_RECT_List_Control_edited.top= rect.top+4  +208;
 m_RECT_List_Control_edited.right= rect.right-rect.left - 3;
 m_RECT_List_Control_edited.bottom= rect.bottom-rect.top -1 ;



if(!Touch_box(m_RECT_List_Control_edited0.left,m_RECT_List_Control_edited0.top,m_RECT_List_Control_edited0.right,m_RECT_List_Control_edited0.bottom,mouse_xy.x,mouse_xy.y))
{

   if(m_List_Control_edited==1)//�༭�� IDC_EDIT_X
    {

    CString str;
   //get the text from the EditBox
   GetDlgItemText(IDC_EDIT_X,str);

   //m_ListBox_Contacts2.SetItemText( nItem_0,nSubItem_0, str);//��������

   SetListControlCell(::GetDlgItem (m_hWnd,IDC_LISTBOX_Contacts2),str,nItem_0,nSubItem_0);
   ::SendDlgItemMessage(m_hWnd,IDC_EDIT_X,WM_KILLFOCUS,0,0);
   ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_X),SW_HIDE);

    Invalidate();//�ػ�

     m_List_Control_edited=0;

    return;
  }


}








 if(nSubItem == 0 || nSubItem == -1 || nItem == -1)
   return;
  //Retrieve the text of the selected subItem
  //from the list












  if(nItem != -1)
  //::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT_X),   HWND_TOP,rect.left+x,rect.top+4,   rect.right-rect.left - 3,          rect.bottom-rect.top -1,NULL);
  ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_X),SW_SHOW);
  ::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_X));

  //Draw a Rectangle around the SubItem ����ʾ����
  //::Rectangle(::GetDC(temp->hdr.hwndFrom), rect.left  ,rect.top-1,rect.right  ,rect.bottom);
  ::Rectangle(::GetDC(temp->hdr.hwndFrom), rect.left -2 ,rect.top-1,rect.right +3 ,rect.bottom);
















   //���ö�̬�༭���С��λ��
   //::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT_X),   HWND_TOP,          rect.left+x    +4,     rect.top+4  +157 ,   rect.right-rect.left - 3,          rect.bottom-rect.top -1   ,        NULL);
     ::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT_X),   HWND_TOP,          m_RECT_List_Control_edited.left,     m_RECT_List_Control_edited.top ,   m_RECT_List_Control_edited.right,         m_RECT_List_Control_edited.bottom  ,        NULL);

//  GetDlgItem(IDC_EDIT_X)->MoveWindow( 100,10, 200, 40 );


  //Set the listItem text in the EditBox 
  ::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT_X),str); 


m_List_Control_edited=1;//�༭��
m_RECT_List_Control_edited0 = m_RECT_List_Control_edited;


 nItem_0=nItem;
 nSubItem_0=nSubItem;

	*pResult = 0;
}







//�Զ����SetListControlCell()����������ʵ��ListControl���������õ�
void CYuanSetDlg::SetListControlCell(HWND hWnd1, CString value, int nRow, int nCol)
{
 //TCHAR szString [256];
 TCHAR szString [1024];
 wsprintf(szString,value ,0);
 //Fill the LVITEM structure with the 
 //values given as parameters.
 LVITEM lvItem;
 lvItem.mask = LVIF_TEXT;
 lvItem.iItem = nRow;
 lvItem.pszText = szString;
 lvItem.iSubItem = nCol;

 if(nCol >0)  //set the value of listItem
    ::SendMessage(hWnd1,LVM_SETITEM, (WPARAM)0,(WPARAM)&lvItem);
 
 else //Insert the value into List
    ListView_InsertItem(hWnd1,&lvItem);

}




//�Զ���ļ�����Ӧ����
BOOL CYuanSetDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���





 if(pMsg->message == WM_KEYDOWN)
  {
     



     if(pMsg->wParam==27)  //����ESC
 
	   {



	   }


     else if(pMsg->wParam==VK_RETURN)  //���˻س���
 
	   {

         CWnd* pwndCtrl = GetFocus();
         // get the control ID which is 
         // presently having the focus


         int ctrl_ID = pwndCtrl->GetDlgCtrlID();
         CString str;


         switch (ctrl_ID)
         { 
          //if the control is the EditBox 
          case IDC_EDIT_X:
          //get the text from the EditBox
             GetDlgItemText(IDC_EDIT_X,str);
             //set the value in the listContorl with the
             //specified Item & SubItem values
             SetListControlCell(::GetDlgItem (m_hWnd,IDC_LISTBOX_Contacts2),str,nItem,nSubItem);
             ::SendDlgItemMessage(m_hWnd,IDC_EDIT_X,WM_KILLFOCUS,0,0);
             ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_X),SW_HIDE);
                   break; 

          default:
                   break;
 

         }




         return   TRUE;   //Ϊ�˲��ûس��˳�����
	   }


  }














	return CDialog::PreTranslateMessage(pMsg);
}






void CYuanSetDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


    mouse_xy=point;

	CDialog::OnMouseMove(nFlags, point);
}







void CYuanSetDlg::OnLButtonDown(UINT nFlags, CPoint point)//����������
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


  //if(m_RECT_List_Control_edited ! = m_RECT_List_Control_edited0)
if(!Touch_box(m_RECT_List_Control_edited0.left,m_RECT_List_Control_edited0.top,m_RECT_List_Control_edited0.right,m_RECT_List_Control_edited0.bottom,mouse_xy.x,mouse_xy.y))
{

   if(m_List_Control_edited==1)//�༭�� IDC_EDIT_X
    {

    CString str;
   //get the text from the EditBox
   GetDlgItemText(IDC_EDIT_X,str);

   //m_ListBox_Contacts2.SetItemText( nItem_0,nSubItem_0, str);//��������


   SetListControlCell(::GetDlgItem (m_hWnd,IDC_LISTBOX_Contacts2),str,nItem_0,nSubItem_0);

   ::SendDlgItemMessage(m_hWnd,IDC_EDIT_X,WM_KILLFOCUS,0,0);
   ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_X),SW_HIDE);
 



  }
     m_List_Control_edited=0;

	     

UpdateData(0);


Invalidate();//�ػ�

}



 

	CDialog::OnLButtonDown(nFlags, point);
}

void CYuanSetDlg::OnDestroy()
{
	CDialog::OnDestroy();

	YUAN_RUN_MAIN_Flag=1; //���� Ԫ����

	// TODO: �ڴ˴������Ϣ����������
}
