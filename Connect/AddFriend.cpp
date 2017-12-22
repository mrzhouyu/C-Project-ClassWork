// AddFriend.cpp : implementation file
//

#include "stdafx.h"
#include "zyijst.h"
#include "AddFriend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddFriend dialog


AddFriend::AddFriend(CWnd* pParent /*=NULL*/)
	: CDialog(AddFriend::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddFriend)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AddFriend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddFriend)
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddFriend, CDialog)
	//{{AFX_MSG_MAP(AddFriend)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddFriend message handlers
