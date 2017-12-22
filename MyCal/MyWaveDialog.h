#if !defined(AFX_MYWAVEDIALOG_H__E1B3A541_44F3_42D1_AB5F_A8E956B88042__INCLUDED_)
#define AFX_MYWAVEDIALOG_H__E1B3A541_44F3_42D1_AB5F_A8E956B88042__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyWaveDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyWaveDialog dialog

class CMyWaveDialog : public CDialog
{
// Construction
public:
	CMyWaveDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyWaveDialog)
	enum { IDD = IDD_WAVE_DIAL };
	CString	m_strValue;
	//}}AFX_DATA
    int m_iUnit;
	int m_iWidth;
	int m_iHigh;
	int m_iTimer;
	int m_iX0;
	int m_iX1;
	int m_iY0;
	int m_iY1;
	int m_iPenMode;
	CRect m_rect;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWaveDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyWaveDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSin();
	afx_msg void OnButtonCos();
	afx_msg void OnRadioDeg();
	afx_msg void OnRadioRad();
	afx_msg void OnButtonPlot();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton0();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWAVEDIALOG_H__E1B3A541_44F3_42D1_AB5F_A8E956B88042__INCLUDED_)
