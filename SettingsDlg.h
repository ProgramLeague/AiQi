#pragma once


// CSettingsDlg 对话框

class CSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingsDlg();

// 对话框数据
	enum { IDD = IDD_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//BOOL check1;
	//BOOL check2;
	//BOOL check3;
	BOOL check4;
	BOOL check5;
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton2();
	BOOL check6;
	BOOL check7;
};
