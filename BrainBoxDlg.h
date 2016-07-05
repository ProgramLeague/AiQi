#pragma once

#include "YUAN_struct.h"	// Added by ClassView
// CBrainBoxDlg 对话框

class CBrainBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CBrainBoxDlg)

public:
	CBrainBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBrainBoxDlg();

// 对话框数据
	enum { IDD = IDD_BRAINBOX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);



public:

	HICON hIcon; //窗口图标


	CPoint mouse_R_LineTo_xy; //显示鼠标准备建立的连接
	CPoint mouse_L_Move_YUAN_xy;
	CPoint mouse_xy;

	bool m_move_YUAN;


	YUAN_UNIT * Get_mouse_down_YUAN(YUAN_UNIT *root,int mouse_x,int mouse_y);
	void Select_Linker(int *li,int *lj,int mouse_x,int mouse_y);

CString CString_Extraction_Content(CString text,CString a,CString b);   //字符串提取中间内容

void Load_Memory_File(int flag,CString FileName);
void Load_Memory_File_XML(int flag,CString FileName);
void Save_Memory_File(int flag,CString FileName);
void Save_Memory_File_XML(int flag,CString FileName);

void Draw_YUAN(int x, int y,int state,int Layer,CDC *pDC); //画元
void Draw_YUAN_2(int x, int y,int state,float E,int Layer,CDC *pDC); //画元

void Draw_YUAN_name(int x, int y,float F,CString TT,CDC *pDC); //画元的名字
void Draw_YUAN_name_2(int x, int y,int state,CString TT,CDC *pDC); //画元的名字
void CBrainBoxDlg::Draw_All_YUAN(CDC *pDC); //画所有元

afx_msg void OnMouseMove(UINT nFlags, CPoint point);
afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


afx_msg void OnNew();

afx_msg void OnBnClickedButton_OnSetYuan();
afx_msg void OnBnClickedButton_OnSetYuanLink();
afx_msg void OnBnClickedButton_OnDel();
afx_msg void OnBnClickedButton_OnNewyuan();
afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
afx_msg void OnBnClickedButton_OnSetYuanState();
afx_msg void OnBnClickedButton3();
afx_msg void OnBnClickedButton4();
BOOL BrainBox_Check1;
};









