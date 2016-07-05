#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_YUANSETDLG_H__D2F6C879_F172_46F4_A7C7_22ABED091CC5__INCLUDED_)
#define AFX_YUANSETDLG_H__D2F6C879_F172_46F4_A7C7_22ABED091CC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YuanSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYuanSetDlg dialog

class CYuanSetDlg : public CDialog
{
// Construction
public:
	CYuanSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CYuanSetDlg)
	enum { IDD = IDD_YuanSetDlg };
	int		m_ID;
	CString	m_text;
	float	m_threshold;
	int		m_Layer;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYuanSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CYuanSetDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	CListBox m_ListBox_Contacts;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton3();
	CString m_edit_Contacts;
	//afx_msg void OnLbnSelchangeListboxContacts();
	CListCtrl m_ListBox_Contacts2;
	afx_msg void OnNMClickListboxContacts2(NMHDR *pNMHDR, LRESULT *pResult);
	int nItem;
	int nSubItem;

	int nItem_0;
	int nSubItem_0;

public:

    //通过ListControl行和列得到项目里面的数据
    CString GetListControlItemText(HWND hWnd, int nItem, int nSubItem);

    //自定义的SetListControlCell()函数，用来实现ListControl插入数据用的
    void SetListControlCell(HWND hWnd1, CString value, int nRow, int nCol);

    virtual BOOL PreTranslateMessage(MSG* pMsg);
	int ListControl_ID_X;
	int m_x_hang;
	int m_x_lie;
	int m_List_Control_edited;
	RECT m_RECT_List_Control_edited;
	RECT m_RECT_List_Control_edited0;

	CPoint mouse_xy;


	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	CString m_Mark;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YUANSETDLG_H__D2F6C879_F172_46F4_A7C7_22ABED091CC5__INCLUDED_)
