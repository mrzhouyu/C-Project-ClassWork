#if !defined(AFX_MYCALDIALOG_H__E39F822C_75C5_406C_8A5B_31370EFB5579__INCLUDED_)
#define AFX_MYCALDIALOG_H__E39F822C_75C5_406C_8A5B_31370EFB5579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCalDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyCalDialog dialog

class CMyCalDialog : public CDialog
{
// Construction
public:
	CMyCalDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyCalDialog)
	enum { IDD = IDD_CAL_DIALOG };
	CString	m_strValue;
	//}}AFX_DATA
	CString  CMyCalDialog::LogicOperate(int iData1,int iData2,int iCalMode);
private:
	CString m_strData[2];
	CString* pstrData;
	int m_iCalMode,m_iSystem;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCalDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyCalDialog)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButtonA();
	afx_msg void OnButtonB();
	afx_msg void OnButtonC();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonSub();
	afx_msg void OnButtonMul();
	afx_msg void OnButtonDiv();
	afx_msg void OnButtonAc();
	afx_msg void OnButtonBk();
	afx_msg void OnRadioHex();
	afx_msg void OnRadioDec();
	afx_msg void OnRadioBin();
	afx_msg void OnRadioOct();
	afx_msg void OnButton0();
	afx_msg void OnButtonEqual();
	afx_msg void OnButtonAnd();
	afx_msg void OnButtonOr();
	afx_msg void OnButtonXor();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButtond();
	afx_msg void OnButtone();
	afx_msg void OnButtonf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCALDIALOG_H__E39F822C_75C5_406C_8A5B_31370EFB5579__INCLUDED_)
