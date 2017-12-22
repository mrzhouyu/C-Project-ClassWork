#if !defined(AFX_SHARESCREENCLIENTDLG_H__0159A38F_FFF7_4D90_A7E9_375665173D32__INCLUDED_)
#define AFX_SHARESCREENCLIENTDLG_H__0159A38F_FFF7_4D90_A7E9_375665173D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShareScreenClientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShareScreenClientDlg dialog

class CInstantMessagingDlg;
class CShareScreenClientSocket;

class CShareScreenClientDlg : public CDialog
{
// Construction
public:
	CShareScreenClientDlg(CWnd* pParent = NULL);   // standard constructor

private:
	/// ��ʼ��
	void Init();

	/// �������ؼ���λ��
	void SetPosition();

	/// ��ָ��IP��PORT����ָ���û�������
	void SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT uPort, const USER *pUser );

	/// �������ر�
	void ServerClosed();

	/// ���߳�������Ļ
	void Kicked();

	/// ������Ļ����
	void ReceiveScreenData( BYTE *pReceivedData );

private:
	CInstantMessagingDlg	*m_pMainDlg;					/// ���Ի���
	CImageList				m_imageList;					/// ͷ��ͼ���б�
	CShareScreenClientSocket
							*m_pSSCSocket;					/// ������Ļ�ͻ���socket
	CString					m_strServerIP;					/// ������IP

	int						m_nServerScreenCX;				/// ��������Ļ�Ŀ�
	int						m_nServerScreenCY;				/// ��������Ļ�ĸ�

public:
	/// ������������
	void OnReceive();

	/// ���ض�Ӧ�ķ�����IP
	CString GetServerIP(){ return m_strServerIP; }

	/// ͬ���������
	void AcceptAddRequest( const USER userServer );

// Dialog Data
	//{{AFX_DATA(CShareScreenClientDlg)
	enum { IDD = IDD_SHARESCREEN_CLIENT };
	CScrollBar	m_sbHorizontal;
	CScrollBar	m_sbVertical;
	CStatic	m_staticScreen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareScreenClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShareScreenClientDlg)
	afx_msg void OnOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHARESCREENCLIENTDLG_H__0159A38F_FFF7_4D90_A7E9_375665173D32__INCLUDED_)
