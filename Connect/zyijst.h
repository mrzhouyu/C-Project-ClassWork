// zyijst.h : main header file for the ZYIJST application
//

#if !defined(AFX_ZYIJST_H__91B0F367_11B9_4889_BA4B_8E16200D3742__INCLUDED_)
#define AFX_ZYIJST_H__91B0F367_11B9_4889_BA4B_8E16200D3742__INCLUDED_
#define WM_CLIENT_ACCEPT WM_USER+101
#define WM_CLIENT_READCLOSE WM_USER+102

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZyijstApp:
// See zyijst.cpp for the implementation of this class
//

class CZyijstApp : public CWinApp
{
public:
	CZyijstApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZyijstApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZyijstApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZYIJST_H__91B0F367_11B9_4889_BA4B_8E16200D3742__INCLUDED_)
