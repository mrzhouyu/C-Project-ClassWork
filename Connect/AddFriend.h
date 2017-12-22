#if !defined(AFX_ADDFRIEND_H__51644523_B57B_4FAE_B7DF_E14E62A7FD2C__INCLUDED_)
#define AFX_ADDFRIEND_H__51644523_B57B_4FAE_B7DF_E14E62A7FD2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddFriend.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddFriend dialog

class AddFriend : public CDialog
{
// Construction
public:
	AddFriend(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddFriend)
	enum { IDD = IDD_DIALOG1 };
	CIPAddressCtrl	m_IPAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddFriend)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddFriend)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFRIEND_H__51644523_B57B_4FAE_B7DF_E14E62A7FD2C__INCLUDED_)
