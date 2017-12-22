#if !defined(AFX_VideoChatDlg_H__BDDF4F60_77BB_477E_BF73_FAD24B363849__INCLUDED_)
#define AFX_VideoChatDlg_H__BDDF4F60_77BB_477E_BF73_FAD24B363849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoChatDlg.h : header file
//

#include "VideoChatSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoChatDlg dialog

class CInstantMessagingDlg;

class CVideoChatDlg : public CDialog
{
// Construction
public:
	CVideoChatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoChatDlg)
	enum { IDD = IDD_VIDEOCHAT };
	CStatic	m_staticSelf;
	CStatic	m_staticFriend;
	CButton	m_btnTrump;
	CButton	m_btnMike;
	CButton	m_btnSetting;
	CButton	m_btnSelf;
	//}}AFX_DATA
	
private:
	/// ��ʼ������
	void Init();
	
private:
	CInstantMessagingDlg	*m_pMainDlg;		/// ���Ի���
	USER					m_userChat;			/// ��������USER
	BOOL					m_bConnect;			/// �Ƿ���������Ƶ����
	BOOL					m_bDeny;			/// �ܾ���Ƶ

	CDC						m_dcMem;			/// ������󴰿ڵ��ڴ�dc
	CBitmap					m_bitmap;			/// ������󴰿ڵ��ڴ�bitmap

	BOOL					m_bReceiveAudio;	/// ��������
	BOOL					m_bRecord;			/// ¼��

	HWAVEOUT				m_hWaveOut;
	PWAVEHDR				m_pWaveHdr1;
	WAVEFORMATEX			m_WaveForm;

	CArray< char *, char *>	m_arrAudioBuffer;	/// ��Ƶ������
	int						m_nReceive;			/// ���յ������
	int						m_nPlay;			/// ���ŵ������
	BOOL					m_bPlaying;			/// ���ڲ�����Ƶ

	CStringList				m_lstVideoData;		/// ������Ƶ����

	DWORD					m_dwRecordAudioTickTime;	
												/// ¼����Ƶʱ���Ͷ˵�ʱ��
	DWORD					m_dwPlayAudioTickTime;
												/// ������Ƶʱ��ʱ��

	CVideoChatSocket		m_VideoChatSocket;
												/// �շ����ݵ��׽���
	BOOL					m_bReceiveFinished;	/// ��Ƶ���ݽ������

	BYTE					*m_pAudioData;		/// �������Ƶ����
	DWORD					m_dwAudioDataSize;	/// ������Ƶ���ݵĴ�С

private:
	/// �����Լ�����Ƶ����
	void SetSelfPicture( const BITMAPINFO bmpInfo, unsigned char *pData, DWORD dwBufferSize );

	// ������Ϣ
	void SendCommand( CONTROLCOMMAND command );

	/// ���յ���Ƶ���ݣ���������
	void SaveAudioData( char *pData, DWORD dwDataLength );

	/// ���º��ѵ���Ƶ���ڻ���
	void UpdateFriendVideoPicture( BYTE *pData, DWORD dwDataLength );

	/// �������
	void ReceiveFinished();

public:
	/// ������������IP
	LPCSTR GetChatIP(){ return m_userChat.strIP; }
	
	/// ��������Ķ���
	void SetChatUser( const USER userChat );

	/// ��������״̬
	void SetConnect( BOOL bConnect ){ m_bConnect = bConnect; }

	/// �õ�����״̬
	BOOL GetConnect(){ return m_bConnect; }

	/// �ܾ���Ƶ
	void DenyVideoChat();

	/// �û��Ͽ�����Ƶ����
	void Disconnect();

	BOOL GetReceiveAudio(){ return m_bReceiveAudio; }
	BOOL GetRecord(){ return m_bRecord; }

	/// ������Ƶ����Ƶ����
	void OnReceive();

	/// �����Լ��Ļ��沢��������
	void UpdateVideoPicture( DWORD dwTickCount,
							const BITMAPINFO bmpInfo, 
							unsigned char *pData, 
							DWORD dwBufferSize );

	/// ������������
	void SendAudioData( DWORD dwTickCount, char *pAudioData, DWORD dwBufferSize );

	///	���ӵ�������
	void ConnectToServer();

	/// ���ӿͻ��˵�socket
	void AttachClientSocket( SOCKET hSocket, CVideoChatDlg *pVidelChatDlg );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoChatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoChatDlg)
	afx_msg void OnOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetting();
	afx_msg void OnSelf();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMike();
	afx_msg void OnTrump();
	afx_msg void WaveOutOpen( WPARAM wParam, LPARAM lParam ) ;
	afx_msg void WaveOutDone( WPARAM wParam, LPARAM lParam ) ;
	afx_msg void WaveOutClose( WPARAM wParam, LPARAM lParam ) ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VideoChatDlg_H__BDDF4F60_77BB_477E_BF73_FAD24B363849__INCLUDED_)
