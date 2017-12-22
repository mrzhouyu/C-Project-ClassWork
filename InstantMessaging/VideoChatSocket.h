#if !defined(AFX_VIDEOCHATSOCKET_H__C0D1BAA2_7CC5_4726_9B6B_203F468CB34F__INCLUDED_)
#define AFX_VIDEOCHATSOCKET_H__C0D1BAA2_7CC5_4726_9B6B_203F468CB34F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoChatSocket.h : header file
//

class CVideoChatDlg;

/////////////////////////////////////////////////////////////////////////////
// CVideoChatSocket command target

class CVideoChatSocket : public CSocket
{
// Attributes
private:
	CVideoChatDlg				*m_pVideoChatDlg;		/// ��Ƶ����Ի���ָ��

// Operations
public:
	CVideoChatSocket();
	virtual ~CVideoChatSocket();

	/// ������Ƶ����Ի���ָ��
	void SetVideoChatDlg( CVideoChatDlg *pVideoChatDlg ){ m_pVideoChatDlg = pVideoChatDlg; }

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoChatSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CVideoChatSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCHATSOCKET_H__C0D1BAA2_7CC5_4726_9B6B_203F468CB34F__INCLUDED_)
