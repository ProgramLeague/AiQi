#if !defined(AFX_YUANLINKDLG_H__75574D45_66C6_4EE6_A55D_E276A66E285E__INCLUDED_)
#define AFX_YUANLINKDLG_H__75574D45_66C6_4EE6_A55D_E276A66E285E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YuanLinkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYuanLinkDlg dialog

class CYuanLinkDlg : public CDialog
{
// Construction
public:
	CYuanLinkDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CYuanLinkDlg)
	enum { IDD = IDD_YuanLinkDlg };
    CString select_linker_ID1_text;
	float	m_weight;
	CString	select_linker_ID2_text;
	float	m_weight2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYuanLinkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CYuanLinkDlg)
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YUANLINKDLG_H__75574D45_66C6_4EE6_A55D_E276A66E285E__INCLUDED_)
