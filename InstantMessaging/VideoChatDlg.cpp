// VideoChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "VideoChatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "InstantMessagingDlg.h"
#include "Debug.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoChatDlg dialog


CVideoChatDlg::CVideoChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoChatDlg)
	//}}AFX_DATA_INIT

	m_bReceiveAudio			= FALSE;
	m_bRecord				= FALSE;
	m_bPlaying				= FALSE;
	m_bReceiveFinished		= TRUE;
	m_pAudioData			= NULL;
}


void CVideoChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoChatDlg)
	DDX_Control(pDX, IDS_SELF, m_staticSelf);
	DDX_Control(pDX, IDS_FRIEND, m_staticFriend);
	DDX_Control(pDX, IDC_TRUMP, m_btnTrump);
	DDX_Control(pDX, IDC_MIKE, m_btnMike);
	DDX_Control(pDX, IDB_SETTING, m_btnSetting);
	DDX_Control(pDX, IDB_SELF, m_btnSelf);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoChatDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoChatDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDB_SETTING, OnSetting)
	ON_BN_CLICKED(IDB_SELF, OnSelf)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIKE, OnMike)
	ON_BN_CLICKED(IDC_TRUMP, OnTrump)
	ON_MESSAGE( MM_WOM_OPEN, WaveOutOpen )
	ON_MESSAGE( MM_WOM_DONE, WaveOutDone )
	ON_MESSAGE( MM_WOM_CLOSE, WaveOutClose )
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoChatDlg message handlers

void CVideoChatDlg::OnOk() 
{
}

void CVideoChatDlg::OnCancel() 
{	
	if( IDOK == MessageBox( "Ҫ�ر���Ƶ������", "�ر�", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{
		/// �������Ի���ĺ���
		m_pMainDlg->CloseVideoChatDlg( m_userChat );
	
		/// �ָ���ʼֵ
		m_bReceiveAudio			= FALSE;
		m_bRecord				= FALSE;
		m_bPlaying				= FALSE;

		/// ɾ���ڴ�dc��bitmap
		m_bitmap.DeleteObject();
		m_dcMem.DeleteDC();

		/// ɾ��������ڴ�
		for( int nIndex = 0; nIndex < m_arrAudioBuffer.GetSize(); nIndex++ )
		{
			char *pAudioBuffer = m_arrAudioBuffer.GetAt( nIndex );
			delete [] pAudioBuffer;
			m_arrAudioBuffer.RemoveAt( nIndex );
			nIndex--;
		}
		waveOutPause( m_hWaveOut );
		waveOutUnprepareHeader( m_hWaveOut, m_pWaveHdr1, sizeof ( WAVEHDR ) ) ;
		waveOutClose( m_hWaveOut ) ;
		delete [] m_pWaveHdr1;

		/// ɾ���������Ƶ����
		m_lstVideoData.RemoveAll();
		
		m_VideoChatSocket.Close();
		
		if( !m_pAudioData )
		{
			delete [] m_pAudioData;
			m_pAudioData = NULL;
		}

		DestroyWindow();
		delete this;
	}
}

BOOL CVideoChatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/// ��ʼ������
	Init();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/// ��ʼ������
void CVideoChatDlg::Init()
{
	/// ��ȡ���Ի���
	m_pMainDlg = ( CInstantMessagingDlg * )::AfxGetMainWnd();

	/// ������Ƶ���ڵĴ�С
	m_staticFriend.SetWindowPos( NULL, 0, 0, VIDEOCHAT_VIDEOWND_WIDTH, VIDEOCHAT_VIDEOWND_HEIGHT,
		SWP_NOMOVE | SWP_NOZORDER );
	m_staticSelf.SetWindowPos( NULL, 0, 0, VIDEOCHAT_VIDEOWND_WIDTH, VIDEOCHAT_VIDEOWND_HEIGHT,
		SWP_NOMOVE | SWP_NOZORDER );

	/// û����������Ƶ�������
	m_bConnect	= FALSE;
	m_bDeny		= FALSE;

	/// �����ڴ�dc
	CDC *pDC = m_staticFriend.GetDC();
	CRect rectFriend;
	m_staticFriend.GetClientRect( &rectFriend );
	m_dcMem.CreateCompatibleDC( pDC );
	m_bitmap.CreateCompatibleBitmap( pDC, rectFriend.Width(), rectFriend.Height() );
	m_dcMem.SelectObject( &m_bitmap );
	m_dcMem.FillSolidRect( rectFriend, RGB( 128, 128, 128 ) );
	ReleaseDC( pDC );

	/// ��ʼ������
	m_WaveForm.wFormatTag		= WAVE_FORMAT_PCM;
	m_WaveForm.nChannels		= 1;
	m_WaveForm.nSamplesPerSec	= 11025;
	m_WaveForm.nAvgBytesPerSec	= 11025;
	m_WaveForm.nBlockAlign		= 1;
	m_WaveForm.wBitsPerSample	= 8;
	m_WaveForm.cbSize			= 0;
	waveOutOpen( &m_hWaveOut, WAVE_MAPPER, &m_WaveForm, ( DWORD )m_hWnd, 0, CALLBACK_WINDOW );

	m_pWaveHdr1 = ( PWAVEHDR )new char[ sizeof( WAVEHDR ) ];
	m_pWaveHdr1->dwBufferLength  = AUDIO_BUFFER_SIZE;
	m_pWaveHdr1->dwBytesRecorded = 0;
	m_pWaveHdr1->dwUser          = 0;
	m_pWaveHdr1->dwFlags         = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	m_pWaveHdr1->dwLoops         = 1;
	m_pWaveHdr1->lpNext          = NULL;
	m_pWaveHdr1->reserved        = 0;

	/// ������Ƶ���ݵĻ�����
	for( int nIndex = 0; nIndex < AUDIO_BUFFER_BLOCK; nIndex++ )
	{
		char *pAudioBuffer = new char[ AUDIO_BUFFER_SIZE + sizeof( DWORD ) ];
		m_arrAudioBuffer.Add( pAudioBuffer );
	}
	m_nReceive	= 0;
	m_nPlay		= 0;

	/// ��ʼ��
	m_dwRecordAudioTickTime	= 0;
	m_dwPlayAudioTickTime	= 0;

	/// ����timer
	SetTimer( TIMER_VIDEOCHAT, DEFALUT_VIDEOCHAT_REFRESH, NULL );
}

/// ��������Ķ���
void CVideoChatDlg::SetChatUser( const USER userChat )
{
	memcpy( &m_userChat, &userChat, sizeof( USER ) );
	
	/// ���ñ���
	CString strTitle;
	strTitle.Format( "��Ƶ���� - %s", m_userChat.strName );
	SetWindowText( strTitle );
}

void CVideoChatDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );	
	CDialog::OnLButtonDown(nFlags, point);
}

void CVideoChatDlg::OnSetting() 
{
	CString strText;
	m_btnSetting.GetWindowText( strText );
	strText = strText == "�ء���" ? "������" : "�ء���" ;
	m_btnSetting.SetWindowText( strText );
}

void CVideoChatDlg::OnSelf() 
{
	CString strText;
	m_btnSelf.GetWindowText( strText );

	CRect rect;
	GetWindowRect( &rect );
	CRect rectFriend;
	m_staticFriend.GetWindowRect( &rectFriend );
	CRect rectSelf;
	m_staticSelf.GetWindowRect( &rectSelf );

	int nSpace = rectSelf.left - rectFriend.right;

	/// ����
	if( strText == "<<<" )
	{
		strText = ">>>";
		m_btnSelf.SetWindowText( strText );
		SetWindowPos( NULL, 0, 0, rect.Width() - rectSelf.Width() - nSpace, rect.Height(), SWP_NOMOVE | SWP_NOZORDER );
	}
	else
	{
		strText = "<<<";
		m_btnSelf.SetWindowText( strText );
		SetWindowPos( NULL, 0, 0, rect.Width() + rectSelf.Width() + nSpace, rect.Height(), SWP_NOMOVE | SWP_NOZORDER );
	}
}

/// �û��Ͽ�����Ƶ����
void CVideoChatDlg::Disconnect()
{
	m_bDeny = TRUE;
	SetConnect( FALSE );

	/// ���ڴ�dc��д��
	CRect rectFriend;
	m_staticFriend.GetClientRect( &rectFriend );
	m_dcMem.SetTextColor( RGB( 255, 0, 0 ) );
	m_dcMem.SetBkMode( TRANSPARENT );
	CString strText( "�Է��Ͽ�����Ƶ����" );
	m_dcMem.DrawText( strText, rectFriend, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	/// ��������������Ƶ����
	m_staticFriend.ShowWindow( SW_HIDE );
}


void CVideoChatDlg::OnMike()
{
	m_bRecord = m_btnMike.GetCheck();
}

void CVideoChatDlg::OnTrump()
{
	m_bReceiveAudio = m_btnTrump.GetCheck();

	/// ������Ƶ����
	if( m_bReceiveAudio )
	{
		/// ����׷�Ͻ���
		if( m_nReceive == m_nPlay )
		{
			m_bPlaying = FALSE;
			return;
		}
		m_bPlaying				= TRUE;
		char *pPlayData			= m_arrAudioBuffer.GetAt( m_nPlay );
		memcpy( &m_dwRecordAudioTickTime, ( BYTE * )pPlayData, sizeof( DWORD ) );
		m_dwPlayAudioTickTime	= ::GetTickCount();
		m_pWaveHdr1->lpData		= pPlayData + sizeof( DWORD );
		waveOutPrepareHeader( m_hWaveOut, m_pWaveHdr1, sizeof( WAVEHDR ) );
		waveOutWrite( m_hWaveOut, m_pWaveHdr1, sizeof( WAVEHDR ) ) ;
		m_nPlay = ( m_nPlay + 1 ) % AUDIO_BUFFER_BLOCK;
	}
	else
	{
		m_bPlaying = FALSE;
	}
}

void CVideoChatDlg::WaveOutOpen( WPARAM wParam, LPARAM lParam )
{
	return;
}

void CVideoChatDlg::WaveOutDone( WPARAM wParam, LPARAM lParam )
{
	if( m_bReceiveAudio )
	{
		/// ����׷�Ͻ���
		if( m_nReceive == m_nPlay )
		{
			m_bPlaying = FALSE;
			return;
		}
		m_bPlaying				= TRUE;
		char *pPlayData			= m_arrAudioBuffer.GetAt( m_nPlay );
		memcpy( &m_dwRecordAudioTickTime, ( BYTE * )pPlayData, sizeof( DWORD ) );
		m_dwPlayAudioTickTime	= ::GetTickCount();
		m_pWaveHdr1->lpData		= pPlayData + sizeof( DWORD );
		waveOutPrepareHeader( m_hWaveOut, m_pWaveHdr1, sizeof( WAVEHDR ) );
		waveOutWrite( m_hWaveOut, m_pWaveHdr1, sizeof( WAVEHDR ) ) ;
		m_nPlay = ( m_nPlay + 1 ) % AUDIO_BUFFER_BLOCK;
	}
	return;
}

void CVideoChatDlg::WaveOutClose( WPARAM wParam, LPARAM lParam )
{
	return;
}

/// �ܾ���Ƶ
void CVideoChatDlg::DenyVideoChat()
{
	m_bDeny = TRUE;
	
	/// ���ڴ�dc��д��
	CRect rectFriend;
	m_staticFriend.GetClientRect( &rectFriend );
	m_dcMem.SetTextColor( RGB( 255, 0, 0 ) );
	m_dcMem.SetBkMode( TRANSPARENT );
	CString strText( "�ܾ���Ƶ����" );
	m_dcMem.DrawText( strText, rectFriend, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	/// ��������������Ƶ����
	m_staticFriend.ShowWindow( SW_HIDE );
}

void CVideoChatDlg::OnPaint() 
{
	CPaintDC dc(this);
	
	if( m_bDeny )
	{
		CRect rectFriend;
		m_staticFriend.GetWindowRect( &rectFriend );
		ScreenToClient( rectFriend );
		dc.BitBlt( rectFriend.left, rectFriend.top, rectFriend.Width(), rectFriend.Height(),
			&m_dcMem, 0, 0, SRCCOPY );
	}
}

/// �����Լ�����Ƶ����
void CVideoChatDlg::SetSelfPicture( const BITMAPINFO bmpInfo, 
									unsigned char *pData, 
									DWORD dwBufferSize )
{
	BYTE *pRGBData = new BYTE[ bmpInfo.bmiHeader.biSizeImage ];
	YUY2_RGB( pData, pRGBData, bmpInfo.bmiHeader.biSizeImage * 4 / 6 );

	CDC *pDC = m_staticSelf.GetDC();
	CRect rectSelf;
	m_staticSelf.GetClientRect( &rectSelf );
	rectSelf.DeflateRect( 2, 2 );
	
	HBITMAP hBitmap = ::CreateDIBitmap( pDC->m_hDC, &( bmpInfo.bmiHeader ), CBM_INIT, pRGBData,
		&bmpInfo, DIB_RGB_COLORS );

	delete [] pRGBData;

	HDC dcMem = ::CreateCompatibleDC( pDC->m_hDC );
	::SelectObject( dcMem, hBitmap );

	CString strText;
	m_btnSetting.GetWindowText( strText );
	if( strText == "�ء���" )
	{
		/// �õ���Ƶ����Ŀ��볤
		int nPictureWidth	= bmpInfo.bmiHeader.biWidth;
		int nPictureHeight	= -bmpInfo.bmiHeader.biHeight;

		/// ������Ƶ�����Դ���볤��
		int nX, nY, nWidth, nHeight;

		/// �Լ���Ƶ�������ݵ�����Ƶ����
		if( nPictureHeight < rectSelf.Height() && nPictureWidth < rectSelf.Width() )
		{
			nX		= rectSelf.left + ( rectSelf.Width() - nPictureWidth ) / 2;
			nY		= rectSelf.top + ( rectSelf.Height() - nPictureHeight ) / 2;
			nWidth	= nPictureWidth;
			nHeight	= nPictureHeight;
		}

		/// ��Ƶ���ڵĸ��п���
		else if( ( float )rectSelf.Height() / rectSelf.Width() > ( float )nPictureHeight / nPictureWidth )
		{
			nX		= rectSelf.left;
			nWidth	= rectSelf.Width();
			nHeight	= nWidth * nPictureHeight / nPictureWidth;
			nY		= rectSelf.top + ( rectSelf.Height() - nHeight ) / 2;
		}

		/// ��Ƶ���ڵĳ��п�������һ��
		else
		{
			nY		= rectSelf.top;
			nHeight	= rectSelf.Height();
			nWidth	= nHeight * nPictureWidth / nPictureHeight;
			nX		= rectSelf.left + ( rectSelf.Width() - nWidth ) / 2;
		}

		::StretchBlt( pDC->m_hDC, 
			nX, nY, nWidth, nHeight,
			dcMem,
			0, 0, bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight,
			SRCCOPY );
	}
	else
	{
		pDC->FillSolidRect( rectSelf, RGB( 128, 128, 128 ) );
	}
	
	::DeleteObject( hBitmap );
	::DeleteObject( dcMem );
	ReleaseDC( pDC );
}

/// ���º��ѵ���Ƶ���ڻ���
void CVideoChatDlg::UpdateFriendVideoPicture( BYTE *pVideoReceiveData, DWORD dwDataLength )
{
	CDebug debug( "UpdateFriendVideoPicture" );

	CString strVideoData( ( LPCTSTR )pVideoReceiveData, dwDataLength );
	m_lstVideoData.AddTail( strVideoData );

	CString strData;
	BITMAPINFO bmpInfo;
	BYTE *pRGBData;


	/// ���û�в�����Ƶ����ֱ����ͼ
	if( !m_bPlaying )
	{
		strData = m_lstVideoData.GetHead();
		m_lstVideoData.RemoveHead();
		BYTE *pVideoData = ( BYTE * )strData.GetBuffer( strData.GetLength() );
		memcpy( &bmpInfo, pVideoData + sizeof( DWORD ), sizeof( BITMAPINFO ) );
		pRGBData = new BYTE[ bmpInfo.bmiHeader.biSizeImage ];
		YUY2_RGB( pVideoData + sizeof( DWORD ) + sizeof( BITMAPINFO ), 
				pRGBData, 
				bmpInfo.bmiHeader.biSizeImage * 4 / 6 );
		strData.ReleaseBuffer( -1 );
	}
	
	/// ���ڲ�����Ƶ����Ҫ����Ƶ���ݽ��д���
	else
	{
		DWORD dwStandardVideoTime = ::GetTickCount() - m_dwPlayAudioTickTime + m_dwRecordAudioTickTime;
		
		DWORD dwVideoTime;
		BOOL bSmallerThanStandardVideoTime	= FALSE;

		/// ѭ���ж�ÿ����Ƶʱ�����׼����ʱ��ľ���
		int nVideoDataCount = m_lstVideoData.GetCount();
		for( int nIndex = 0; nIndex < nVideoDataCount; nIndex++ )
		{
			strData = m_lstVideoData.GetHead();
			BYTE *pVideoData = ( BYTE * )strData.GetBuffer( strData.GetLength() );
			memcpy( &dwVideoTime, pVideoData, sizeof( DWORD ) );
			
			/// �����Ƶʱ�����׼ʱ����Ȼ���ڵ��Ѿ�����һ��С�ڵ�
			if( ( dwVideoTime > dwStandardVideoTime && bSmallerThanStandardVideoTime ) ||
				dwVideoTime == dwStandardVideoTime )
			{
				m_lstVideoData.RemoveHead();
				memcpy( &bmpInfo, pVideoData + sizeof( DWORD ), sizeof( BITMAPINFO ) );
				pRGBData = new BYTE[ bmpInfo.bmiHeader.biSizeImage ];
				YUY2_RGB( pVideoData + sizeof( DWORD ) + sizeof( BITMAPINFO ), 
						pRGBData, 
						bmpInfo.bmiHeader.biSizeImage * 4 / 6 );
				strData.ReleaseBuffer( -1 );
				break;
			}

			/// �����Ƶʱ��С�ڱ�׼ʱ�䣬������Ƶ����
			else if( dwVideoTime < dwStandardVideoTime )
			{
				bSmallerThanStandardVideoTime = TRUE;
				m_lstVideoData.RemoveHead();
				strData.ReleaseBuffer( -1 );
				continue;
			}

			/// �����Ƶʱ����ڱ�׼ʱ�䣬��������ֱ�ӷ���
			else if( dwVideoTime > dwStandardVideoTime )
			{
				strData.ReleaseBuffer( -1 );
				return;
			}
		}
	}

	CDC *pDC = m_staticFriend.GetDC();
	CRect rectFriend;
	m_staticFriend.GetClientRect( &rectFriend );
	rectFriend.DeflateRect( 2, 2 );
	
	HBITMAP hBitmap = ::CreateDIBitmap( pDC->m_hDC, &( bmpInfo.bmiHeader ), CBM_INIT, 
		pRGBData,
		&bmpInfo, DIB_RGB_COLORS );

	delete [] pRGBData;
	pRGBData = NULL;

	HDC dcMem = ::CreateCompatibleDC( pDC->m_hDC );
	::SelectObject( dcMem, hBitmap );
	
	/// �õ���Ƶ����Ŀ��볤
	int nPictureWidth	= bmpInfo.bmiHeader.biWidth;
	int nPictureHeight	= -bmpInfo.bmiHeader.biHeight;
	
	/// ������Ƶ�����Դ���볤��
	int nX, nY, nWidth, nHeight;
	
	/// �Լ���Ƶ�������ݵ�����Ƶ����
	if( nPictureHeight < rectFriend.Height() && nPictureWidth < rectFriend.Width() )
	{
		nX		= rectFriend.left + ( rectFriend.Width() - nPictureWidth ) / 2;
		nY		= rectFriend.top + ( rectFriend.Height() - nPictureHeight ) / 2;
		nWidth	= nPictureWidth;
		nHeight	= nPictureHeight;
	}
	
	/// ��Ƶ���ڵĸ��п���
	else if( ( float )rectFriend.Height() / rectFriend.Width() > ( float )nPictureHeight / nPictureWidth )
	{
		nX		= rectFriend.left;
		nWidth	= rectFriend.Width();
		nHeight	= nWidth * nPictureHeight / nPictureWidth;
		nY		= rectFriend.top + ( rectFriend.Height() - nHeight ) / 2;
	}
	
	/// ��Ƶ���ڵĳ��п�������һ��
	else
	{
		nY		= rectFriend.top;
		nHeight	= rectFriend.Height();
		nWidth	= nHeight * nPictureWidth / nPictureHeight;
		nX		= rectFriend.left + ( rectFriend.Width() - nWidth ) / 2;
	}
	
	::StretchBlt( pDC->m_hDC, 
		nX, nY, nWidth, nHeight,
		dcMem,
		0, 0, bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight,
		SRCCOPY );

	::DeleteObject( hBitmap );
	::DeleteObject( dcMem );
	ReleaseDC( pDC );
}

/// ���յ���Ƶ���ݣ���������
void CVideoChatDlg::SaveAudioData( char *pData, DWORD dwDataLength )
{
	CDebug debug( "SaveAudioData" );

	/// ������յ�����Ƶ����
	char *pSaveData = m_arrAudioBuffer.GetAt( m_nReceive );
	memcpy( pSaveData, pData, dwDataLength );

	/// �µĽ��������
	m_nReceive = ( m_nReceive + 1 ) % AUDIO_BUFFER_BLOCK;

	/// ����׷�ϲ��ţ�������ǰ��
	if( m_nReceive == m_nPlay )
	{
		m_nPlay = ( m_nPlay + 1 ) % AUDIO_BUFFER_BLOCK;
	}
	if( !m_bPlaying && m_bReceiveAudio )
	{
		m_bPlaying				= TRUE;
		char *pPlayData			= m_arrAudioBuffer.GetAt( m_nPlay );
		memcpy( &m_dwRecordAudioTickTime, ( BYTE * )pPlayData, sizeof( DWORD ) );
		m_dwPlayAudioTickTime	= ::GetTickCount();
		m_pWaveHdr1->lpData		= pPlayData + sizeof( DWORD );
		waveOutPrepareHeader( m_hWaveOut, m_pWaveHdr1, sizeof( WAVEHDR ) );
		waveOutWrite( m_hWaveOut, m_pWaveHdr1, sizeof( WAVEHDR ) ) ;
		m_nPlay = ( m_nPlay + 1 ) % AUDIO_BUFFER_BLOCK;
	}
}

/// ������Ƶ����Ƶ����
void CVideoChatDlg::OnReceive()
{
	BYTE pTempData[ sizeof( DATAPACKET ) ];
	BYTE *pReceiveData;
	BYTE *pTempReceive;
	DWORD dwReceiveLength	= 0;
	DWORD dwReceiveCount	= 0;
	DWORD dwDataLength		= 0;
	DATAPACKET dataPacket;
	
	/// ѭ����������
	do
	{
		if( 0 == dwReceiveCount )
		{
			dwReceiveLength = m_VideoChatSocket.Receive( pTempData, sizeof( DATAPACKET ) );
			dwReceiveCount	+= dwReceiveLength;
			memcpy( &dataPacket, pTempData, sizeof( DATAPACKET ) );
			dwDataLength	= dataPacket.dwLength - sizeof( DATAPACKET );
			pReceiveData	= new BYTE[ dwDataLength ];
			pTempReceive	= pReceiveData;
		}
		else
		{
			dwReceiveLength = m_VideoChatSocket.Receive( pTempReceive, dwDataLength );
			dwReceiveCount	+= dwReceiveLength;
			dwDataLength	-= dwReceiveLength;
			pTempReceive	+= dwReceiveLength;
		}
	}while( dwReceiveCount < dataPacket.dwLength );

	/// ����������в�ͬ�Ĵ���
	switch( dataPacket.command )
	{
	case VIDEOCHAT_VIDEO_PICTURE:								/// ��Ƶ��������
		UpdateFriendVideoPicture( pReceiveData, dataPacket.dwLength - sizeof( DATAPACKET ) );
		SendCommand( VIDEOCHAT_VIDEO_RECEIVE_FINISHED );
		break;
	case VIDEOCHAT_AUDIO_DATA:									/// ��Ƶ����
		SaveAudioData( ( char * )pReceiveData, dataPacket.dwLength - sizeof( DATAPACKET ) );
		SendCommand( VIDEOCHAT_VIDEO_RECEIVE_FINISHED );
		break;
	case VIDEOCHAT_VIDEO_RECEIVE_FINISHED:						/// ��Ƶ���ݽ������
		ReceiveFinished();
		break;
	default:
		break;
	}

	delete [] pReceiveData;
}


/// �����Լ��Ļ��沢��������
void CVideoChatDlg::UpdateVideoPicture( DWORD dwTickCount,
									   const BITMAPINFO bmpInfo, 
									   unsigned char *pData, 
									   DWORD dwBufferSize )
{
	/// �����Լ��Ļ���
	SetSelfPicture( bmpInfo, pData, dwBufferSize );

	/// ���������
	if( m_bConnect && m_bReceiveFinished )
	{
		CDebug debug( "SendVideoPicture" );

		/// ���ý�����ϱ�־ΪFALSE
		m_bReceiveFinished = FALSE;

		/// �����µ���Ƶ���ݱ�������
		DWORD dwDataSize = sizeof( DATAPACKET ) + sizeof( DWORD ) + sizeof( BITMAPINFO ) + dwBufferSize;

		BYTE *pVideoSendData = new BYTE[ dwDataSize ];
	
		/// ���ݰ�
		DATAPACKET dataPacket;
		dataPacket.command		= VIDEOCHAT_VIDEO_PICTURE;
		dataPacket.dwLength		= dwDataSize;

		memcpy( pVideoSendData, &dataPacket, sizeof( DATAPACKET ) );
		memcpy( pVideoSendData + sizeof( DATAPACKET ), &dwTickCount, sizeof( DWORD ) );
		memcpy( pVideoSendData + sizeof( DATAPACKET ) + sizeof( DWORD ), &bmpInfo, sizeof( BITMAPINFO ) );
		memcpy( pVideoSendData + sizeof( DATAPACKET ) + sizeof( DWORD ) + sizeof( BITMAPINFO ),
			pData,
			dwBufferSize );
		
		/// ѭ����������
		BYTE *pSendData			= pVideoSendData;
		DWORD dwSendDataLength	= dwDataSize;
		DWORD dwCountSendLength	= 0;
		int nSendLength			= 0;
		do
		{
			nSendLength			= m_VideoChatSocket.Send( pSendData, dwSendDataLength );
			dwCountSendLength	+= nSendLength;
			dwSendDataLength	-= nSendLength;
			pSendData			+= nSendLength;
		}while( dwCountSendLength < dwDataSize );
		
		delete [] pVideoSendData;
	}
}

/// ������������
void CVideoChatDlg::SendAudioData( DWORD dwTickCount, char *pAudioData, DWORD dwBufferSize )
{
	/// �����Ƶ�������϶�������Է�������Ƶ
	if( m_bConnect && m_bRecord )
	{	
		/// ��������Ƶ���ݵĴ�С
		DWORD dwDataSize = sizeof( DATAPACKET ) + sizeof( DWORD ) + dwBufferSize;
		
		BYTE *pVideoSendData = new BYTE[ dwDataSize ];
		
		/// ���ݰ�
		DATAPACKET dataPacket;
		dataPacket.command		= VIDEOCHAT_AUDIO_DATA;
		dataPacket.dwLength		= dwDataSize;
		
		memcpy( pVideoSendData, &dataPacket, sizeof( DATAPACKET ) );
		memcpy( pVideoSendData + sizeof( DATAPACKET ), &dwTickCount, sizeof( DWORD ) );
		memcpy( pVideoSendData + sizeof( DATAPACKET ) + sizeof( DWORD ), pAudioData, dwBufferSize );
		
		/// �����Ƶ���ݷ�����ϣ�����Է�����Ƶ����
		if( m_bReceiveFinished )
		{
			CDebug debug( "SendAudioData" );

			/// ���ý�����ϱ�־ΪFALSE
			m_bReceiveFinished		= FALSE;

			/// ѭ����������
			BYTE *pSendData			= pVideoSendData;
			DWORD dwSendDataLength	= dwDataSize;
			DWORD dwCountSendLength	= 0;
			int nSendLength			= 0;
			do
			{
				nSendLength			= m_VideoChatSocket.Send( pSendData, dwSendDataLength );
				dwCountSendLength	+= nSendLength;
				dwSendDataLength	-= nSendLength;
				pSendData			+= nSendLength;
			}while( dwCountSendLength < dwDataSize );
		}

		/// ������ڷ�����Ƶ���ݣ������Ƶ�������� 
		else
		{
			m_dwAudioDataSize = dwDataSize;
			if( !m_pAudioData )
			{
				m_pAudioData = new BYTE[ m_dwAudioDataSize ];
				memcpy( m_pAudioData, pVideoSendData, m_dwAudioDataSize );
			}
		}

		delete [] pVideoSendData;		
	}
}

///	���ӵ�������
void CVideoChatDlg::ConnectToServer()
{
	CDebug debug( "ConnectToServer" );
	
	/// ���������ϵı�־
	SetConnect( TRUE );
	
	/// ����socket�������������������
	m_VideoChatSocket.SetVideoChatDlg( this );
	m_VideoChatSocket.Create();
	m_VideoChatSocket.Connect( m_userChat.strIP, VIDEOCHAT_PORT );
}

/// ���ӿͻ��˵�socket
void CVideoChatDlg::AttachClientSocket( SOCKET hSocket, CVideoChatDlg *pVidelChatDlg )
{
	CDebug debug( "AttachClientSocket" );
	
	m_VideoChatSocket.Attach( hSocket );
	m_VideoChatSocket.SetVideoChatDlg( pVidelChatDlg );
}

// ������Ϣ
void CVideoChatDlg::SendCommand( CONTROLCOMMAND command )
{
	DATAPACKET dataPacket;
	dataPacket.command		= command;
	dataPacket.dwLength		= sizeof( DATAPACKET );

	UINT uSendDataLength	= sizeof( DATAPACKET );
	BYTE *pSendData			= new BYTE[ uSendDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	m_VideoChatSocket.Send( pSendData, uSendDataLength );
}

/// �������
void CVideoChatDlg::ReceiveFinished()
{
	CDebug debug( "ReceiveFinished" );

	/// ���������Ƶ�Ļ�����Ϊ�գ���û����Ҫ���͵�����
	if( !m_pAudioData )
	{
		m_bReceiveFinished = TRUE;
		return;
	}

	CDebug debug1( "SendAudioData" );

	/// ���ý�����ϱ�־ΪFALSE
	m_bReceiveFinished		= FALSE;
	
	/// ѭ�����ͱ������Ƶ����
	BYTE *pSendData			= m_pAudioData;
	DWORD dwSendDataLength	= m_dwAudioDataSize;
	DWORD dwCountSendLength	= 0;
	int nSendLength			= 0;
	do
	{
		nSendLength			= m_VideoChatSocket.Send( pSendData, dwSendDataLength );
		dwCountSendLength	+= nSendLength;
		dwSendDataLength	-= nSendLength;
		pSendData			+= nSendLength;
	}while( dwCountSendLength < m_dwAudioDataSize );

	/// ������ϣ���������ɾ��
	delete [] m_pAudioData;
	m_pAudioData = NULL;
}
