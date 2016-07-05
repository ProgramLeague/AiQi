// YuanLinkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AiQi.h"

#include "YUAN_struct.h"
#include "YUAN_system.h"
#include "YuanLinkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CYuanLinkDlg dialog


CYuanLinkDlg::CYuanLinkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYuanLinkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYuanLinkDlg)
    select_linker_ID1_text= _T("");
	m_weight =  0.0f;
	select_linker_ID2_text = _T("");
	m_weight2 = 0.0f;
	//}}AFX_DATA_INIT
}


void CYuanLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYuanLinkDlg)
	DDX_Text(pDX, IDC_YuanLinkDlg_EDIT1, select_linker_ID1_text);
	DDX_Text(pDX, IDC_YuanLinkDlg_EDIT3, m_weight);
	DDX_Text(pDX, IDC_YuanLinkDlg_EDIT2, select_linker_ID2_text);
	DDX_Text(pDX, IDC_YuanLinkDlg_EDIT4, m_weight2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYuanLinkDlg, CDialog)
	//{{AFX_MSG_MAP(CYuanLinkDlg)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYuanLinkDlg message handlers

void CYuanLinkDlg::OnOK() 
{
	// TODO: Add extra validation here

  UpdateData();

  YUAN->Set_linker_weight(select_linker_ID_1,select_linker_ID_2,m_weight);

  if(select_linker_sum==2)
  YUAN->Set_linker_weight(select_linker_ID_2,select_linker_ID_1,m_weight2);

  UpdateData(FALSE);

	
	CDialog::OnOK();
}

int CYuanLinkDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

    //初始化连接1
	if(select_linker_sum==1)
	{
     select_linker_ID1_text.Format("连接: %d -> %d",select_linker_ID_1,select_linker_ID_2); 

     m_weight = YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2);

     select_linker_ID2_text.Format("连接: %d -> %d 无",select_linker_ID_2,select_linker_ID_1); 

	}

    //初始化连接2
	if(select_linker_sum==2)
	{
     select_linker_ID1_text.Format("连接: %d -> %d",select_linker_ID_1,select_linker_ID_2); 

     m_weight = YUAN->Get_linker_weight(select_linker_ID_1,select_linker_ID_2);


     select_linker_ID2_text.Format("连接: %d -> %d",select_linker_ID_2,select_linker_ID_1); 

	 m_weight2 = YUAN->Get_linker_weight(select_linker_ID_2,select_linker_ID_1);
		
	}


	return 0;
}

void CYuanLinkDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here

	if(select_linker_sum==1)
	 ((CEdit*)GetDlgItem(IDC_YuanLinkDlg_EDIT4))-> EnableWindow(FALSE); //SetReadOnly(TRUE);
	
}
