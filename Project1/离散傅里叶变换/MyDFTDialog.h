#if !defined(AFX_MYDFTDIALOG_H__E205D613_26F7_4D6B_AD72_B188ACD5C3E2__INCLUDED_)
#define AFX_MYDFTDIALOG_H__E205D613_26F7_4D6B_AD72_B188ACD5C3E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDFTDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDFTDialog dialog

class CMyDFTDialog : public CDialog
{
// Construction
public:
	CMyDFTDialog(CWnd* pParent = NULL);   // standard constructor
   
// Dialog Data
	//{{AFX_DATA(CMyDFTDialog)
	enum { IDD = IDD_DFT_DIAL };
	CString	m_strValue;
	//}}AFX_DATA

	void PoltSpectrum(void); 
	int m_iDftn;
	
	int m_iWidth;
	int m_iHigh;
	int m_iX0;
	int m_iX1;
	int m_iY0;
	int m_iY1;
	int m_iPenMode;
	CRect m_rect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDFTDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDFTDialog)
	afx_msg void OnButtonDft();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDFTDIALOG_H__E205D613_26F7_4D6B_AD72_B188ACD5C3E2__INCLUDED_)
