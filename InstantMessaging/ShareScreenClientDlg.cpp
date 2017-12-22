// ShareScreenClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "ShareScreenClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShareScreenClientDlg dialog

#include "InstantMessagingDlg.h"
#include "ShareScreenClientSocket.h"

CShareScreenClientDlg::CShareScreenClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShareScreenClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShareScreenClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShareScreenClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareScreenClientDlg)
	DDX_Control(pDX, IDS_SCREEN, m_staticScreen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareScreenClientDlg, CDialog)
	//{{AFX_MSG_MAP(CShareScreenClientDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareScreenClientDlg message handlers

BOOL CShareScreenClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/// ��ʼ��
	Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/// ��ʼ��
void CShareScreenClientDlg::Init()
{
	/// ��ȡ���Ի���
	m_pMainDlg = ( CInstantMessagingDlg * )::AfxGetMainWnd();

	SetPosition();

	/// ��ʼ��UDP�׽���
	m_pSSCSocket = new CShareScreenClientSocket( this );
	m_pSSCSocket->Create( SHARESCREENCLIENT_PORT, SOCK_DGRAM );

	/// ���÷�������Ļ�Ŀ����
	m_nServerScreenCX = 0;
	m_nServerScreenCY = 0;
}

/// �������ؼ���λ��
void CShareScreenClientDlg::SetPosition()
{
}


void CShareScreenClientDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	SetPosition();
}

void CShareScreenClientDlg::OnOk() 
{
}

void CShareScreenClientDlg::OnCancel() 
{	
	if( IDOK == MessageBox( "Ҫ�رչ�����Ļ��", "�ر�", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{	
		/// �رչ�����Ļ��USER
		USER userSelf;
		userSelf.bHasCamera	= m_pMainDlg->HasCamera();
		userSelf.nFace		= m_pMainDlg->GetFace();
		memcpy( userSelf.strName, m_pMainDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
		
		SendUserCommandToIP( SHARESCREEN_CLIENT_CLOSED, m_strServerIP, SHARESCREENSERVER_PORT, &userSelf );

		/// �ر�UDP�׽���
		m_pSSCSocket->Close();
		delete [] m_pSSCSocket;
		m_pSSCSocket = NULL;

		DestroyWindow();
	}
}

/// ��UDP�н�������
void CShareScreenClientDlg::OnReceive()
{
	/// ��������
	CString strIP;
	UINT uPort;
	BYTE *szReceive;
	DWORD dwReceivDataLength = MAXDATAPACKETLENGTH;
	if( 0 != m_nServerScreenCX && 0 != m_nServerScreenCY )
	{
		WORD wBitCount = SHARESCREEN_BITCOUNT;
		DWORD dwPaletteSize = 0;
		if( wBitCount <= 8 )
		{
			dwPaletteSize = ( 1 << wBitCount ) * sizeof( RGBQUAD );
		}
		DWORD dwBmBitsSize	= ( ( m_nServerScreenCX * wBitCount + 31 ) / 32 ) * 4 * m_nServerScreenCY ;
		dwReceivDataLength = sizeof( DATAPACKET ) 
			+ sizeof( BITMAPINFOHEADER ) 
			+ dwPaletteSize 
			+ dwBmBitsSize;
	}
	szReceive = new BYTE[ dwReceivDataLength ];
	
	m_pSSCSocket->ReceiveFrom( szReceive, dwReceivDataLength, strIP, uPort );

	/// װ�����ݰ�
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );

	/// ����������в�ͬ�Ĵ���
	switch( dataPacket.command )
	{
	case SHARESCREEN_SERVER_CLOSED:							/// ������Ļ�������ر�
		ServerClosed();
		break;
	case SHARESCREEN_CLIENT_KICKED:							/// �ͻ��˱���
		Kicked();
		break;
	case SHARESCREEN_SERVER_SCREEN_DIM:						/// ��������Ļ�ߴ�
		memcpy( &m_nServerScreenCX, szReceive + sizeof( DATAPACKET ), sizeof( int ) );
		memcpy( &m_nServerScreenCY, szReceive + sizeof( DATAPACKET ) + sizeof( int ), sizeof( int ) );
		break;
	case SHARESCREEN_SERVER_SCREEN:							///	������Ļ����������Ļ����
		ReceiveScreenData( szReceive );
		break;
	default:
		break;
	}

	delete [] szReceive;
}

/// ��ָ��IP��PORT����ָ������
void CShareScreenClientDlg::SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT uPort, const USER *pUser )
{
	DATAPACKET dataPacket;
	dataPacket.command	= command;
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET );
	if( pUser )
	{
		uDataLength += sizeof( USER );
	}
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	if( pUser )
	{
		memcpy( pSendData + sizeof( DATAPACKET ), pUser, sizeof( USER ) );
	}
	
	/// ��������
	m_pSSCSocket->SendTo( pSendData, uDataLength, uPort, szIP );

	delete pSendData;
}

/// ��ӷ��������Լ����û��б��
void CShareScreenClientDlg::AcceptAddRequest(  const USER userServer )
{
	/// ���÷�����IP
	m_strServerIP = userServer.strIP;

	/// �Լ���USER
	USER userSelf;
	userSelf.bHasCamera	= m_pMainDlg->HasCamera();
	userSelf.nFace		= m_pMainDlg->GetFace();
	memcpy( userSelf.strName, m_pMainDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );

	/// ����������빲����Ļ
	SendUserCommandToIP( SHARESCREEN_ADDREQUEST_ALLOW, m_strServerIP, SHARESCREENSERVER_PORT, &userSelf );
}

/// ���߳�������Ļ
void CShareScreenClientDlg::Kicked()
{
	/// �ر�UDP�׽���
	m_pSSCSocket->Close();

	/// ��ʾ
	MessageBox( "�㱻�������߳����˹�����Ļ��", "������Ļ" );

	/// �رնԻ���
	DestroyWindow();
}

/// �������ر�
void CShareScreenClientDlg::ServerClosed()
{
	/// �ر�UDP�׽���
	m_pSSCSocket->Close();

	/// ��ʾ
	MessageBox( "�����߹ر��˹�����Ļ��", "������Ļ" );

	/// �رնԻ���
	DestroyWindow();
}

/// ������Ļ����
void CShareScreenClientDlg::ReceiveScreenData( BYTE *pReceivedData )
{
	DATAPACKET dataPacket;
	memcpy( &dataPacket, pReceivedData, sizeof( DATAPACKET ) );

	/// ����ͼ��ı�����
	WORD wBitCount = SHARESCREEN_BITCOUNT;
	DWORD dwPaletteSize = 0;
	if( wBitCount <= 8 )
	{
		dwPaletteSize = ( 1 << wBitCount ) * sizeof( RGBQUAD );
	}
	DWORD dwBmBitsSize	= ( ( m_nServerScreenCX * wBitCount + 31 ) / 32 ) * 4 * m_nServerScreenCY ;
	DWORD dwBmpLength	= sizeof( BITMAPINFOHEADER ) + dwPaletteSize + dwBmBitsSize;

	BYTE *pBI = new BYTE[ dwBmpLength ];

	/// ���ݱ�ѹ����
	if( dwBmpLength > dataPacket.dwLength )
	{
		DWORD dwPBILength;
		uncompress( pBI, &dwPBILength, pReceivedData + sizeof( DATAPACKET ), dataPacket.dwLength );
	}
	else
	{
		memcpy( pBI, pReceivedData + sizeof( DATAPACKET ), dataPacket.dwLength );
	}

	m_nServerScreenCX = ( ( BITMAPINFOHEADER * )pBI )->biWidth;
	m_nServerScreenCY = ( ( BITMAPINFOHEADER * )pBI )->biHeight;

	HDC hDC			= ::GetDC( NULL );
	HBITMAP hBitmap	= ::CreateCompatibleBitmap( hDC, m_nServerScreenCX, m_nServerScreenCY );
	::SelectObject( hDC, hBitmap );

	::SetDIBits( hDC, hBitmap, 0, m_nServerScreenCY, 
		( LPSTR )pBI + sizeof( BITMAPINFOHEADER ) + dwPaletteSize, 
		( BITMAPINFO * )pBI, DIB_RGB_COLORS );

	HBITMAP hOldBitmap = m_staticScreen.SetBitmap( hBitmap );

	::DeleteObject( hOldBitmap );
	::ReleaseDC( NULL, hDC );

	/// ɾ��������ڴ�
	delete pBI;
}