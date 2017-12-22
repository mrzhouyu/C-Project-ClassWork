// zhouyu.h : main header file for the ZHOUYU application
//

#if !defined(AFX_ZHOUYU_H__9E6173B3_8638_49BC_A133_672DE85C849B__INCLUDED_)
#define AFX_ZHOUYU_H__9E6173B3_8638_49BC_A133_672DE85C849B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CZhouyuApp:
// See zhouyu.cpp for the implementation of this class
//

class CZhouyuApp : public CWinApp
{
public:
	CZhouyuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZhouyuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CZhouyuApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZHOUYU_H__9E6173B3_8638_49BC_A133_672DE85C849B__INCLUDED_)
