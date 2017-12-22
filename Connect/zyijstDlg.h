// zyijstDlg.h : header file
//

#if !defined(AFX_ZYIJSTDLG_H__1D8A7A7D_C174_4F02_9014_EBCBEB215875__INCLUDED_)
#define AFX_ZYIJSTDLG_H__1D8A7A7D_C174_4F02_9014_EBCBEB215875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZyijstDlg dialog

class CZyijstDlg : public CDialog
{
// Construction
public:
	CZyijstDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZyijstDlg)
	enum { IDD = IDD_ZYIJST_DIALOG };
	CListBox	m_FriendList1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyijstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZyijstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnStartBTN();
	afx_msg void OnHidebtn();
	afx_msg void OnAddBTN();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZYIJSTDLG_H__1D8A7A7D_C174_4F02_9014_EBCBEB215875__INCLUDED_)
