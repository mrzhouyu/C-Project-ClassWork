#if !defined(AFX_SHARESCREENSERVERDLG_H__C65D2BB7_71EA_4568_AC91_13588D9954B4__INCLUDED_)
#define AFX_SHARESCREENSERVERDLG_H__C65D2BB7_71EA_4568_AC91_13588D9954B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShareScreenServerDlg.h : header file
//

#include "AdvButton.h"

/////////////////////////////////////////////////////////////////////////////
// CShareScreenServerDlg dialog

class CInstantMessagingDlg;
class CShareScreenServerSocket;

class CShareScreenServerDlg : public CDialog
{
// Construction
public:
	CShareScreenServerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShareScreenServerDlg)
	enum { IDD = IDD_SHARESCREEN_SERVER };
	CEdit	m_editInformation;
	CListCtrl	m_listCtrlOutOfShareScreen;
	CListCtrl	m_listCtrlInShareScreen;
	CAdvButton	m_btnDeleteFriends;
	CAdvButton	m_btnAddFriends;
	//}}AFX_DATA
	
private:
	/// ��ʼ������
	void Init();

	/// ��ָ��IP��PORT����ָ���û�������
	void SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT nPort, const USER *pUser );

	/// ������Ļ����û�
	void AddUserToShareScreen( const USER user );

	/// �Ƴ��û�
	void DelUserFromShareScreen( const USER user );

	/// ������Ӻ�ɾ����ť
	void UpdateButtons();

	/// �õ���Ļ��dib���ݲ�ѹ��
	void GetScreenDIB( BYTE *&pDIB, DWORD &dwDIBLength );

	/// ����Ѵ�������ĳߴ�
	void SendDIMToFriends( const USER user );

	/// ����Ѵ�������ͼ��
	void SendScreenToFriends();
		
private:
	CInstantMessagingDlg	*m_pMainDlg;		/// ���Ի���
	CImageList				m_imageList;		/// ͷ��ͼ���б�
	CArray< USER, USER >	m_arrFriendsInShareScreen;	
												/// ������Ļ�еĺ����б�
	CArray< USER, USER >	m_arrFriendsOutOfShareScreen;
												/// ���ڹ�����Ļ�еĺ����б�
	CShareScreenServerSocket	
							*m_pSSSSocket;		/// �����ҷ�����socket

	HBITMAP hbmp ;

public:
	/// ������������
	void OnReceive();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareScreenServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShareScreenServerDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnAddfriends();
	afx_msg void OnDelfriends();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHARESCREENSERVERDLG_H__C65D2BB7_71EA_4568_AC91_13588D9954B4__INCLUDED_)
