// InstantMessagingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InstantMessaging.h"
#include "InstantMessagingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "ListeningSocket.h"
#include "Debug.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

DWORD WINAPI AddFriendsProc( LPVOID lpParameter );

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstantMessagingDlg dialog

CInstantMessagingDlg::CInstantMessagingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstantMessagingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstantMessagingDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstantMessagingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstantMessagingDlg)
	DDX_Control(pDX, IDC_COMBO_IP, m_comboxIP);
	DDX_Control(pDX, IDC_LIST_FRIENDS, m_listCtrlFriends);
	DDX_Control(pDX, IDC_STATIC_FACE, m_staticFace);
	DDX_Control(pDX, IDC_EDIT_NICKNAME, m_editNickName);
	DDX_Control(pDX, IDC_COMBO_STATE, m_comboxState);
	DDX_Control(pDX, IDC_COMBO_FRIEND, m_comboxFriend);
	DDX_Control(pDX, IDC_BTN_WHITEBOARD, m_btnWhiteBoard);
	DDX_Control(pDX, IDC_BTN_SHARESCREEN, m_btnShareScreen);
	DDX_Control(pDX, IDC_BTN_SENDFILES, m_btnSendFiles);
	DDX_Control(pDX, IDC_BTN_CHATROOM, m_btnChatRoom);
	DDX_Control(pDX, IDC_BTN_ADDFRIEND, m_btnAddFriend);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInstantMessagingDlg, CDialog)
	//{{AFX_MSG_MAP(CInstantMessagingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_CBN_SELCHANGE(IDC_COMBO_STATE, OnSelchangeComboState)
	ON_COMMAND(IDM_STATE, OnState)
	ON_BN_CLICKED(IDC_BTN_ADDFRIEND, OnBtnAddfriend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CHATROOM, OnBtnChatroom)
	ON_COMMAND(IDM_CHATROOM, OnChatroom)
	ON_BN_CLICKED(IDC_BTN_SENDFILES, OnBtnSendfiles)
	ON_COMMAND(IDM_SENDFILES, OnSendfiles)
	ON_COMMAND(IDM_RECEIVEFILES, OnReceivefiles)
	ON_BN_CLICKED(IDB_ADD_SECTION, OnAddSection)
	ON_BN_CLICKED(IDC_BTN_SHARESCREEN, OnBtnSharescreen)
	ON_COMMAND(IDM_SHARESCREEN, OnSharescreen)
	ON_BN_CLICKED(IDC_BTN_WHITEBOARD, OnBtnWhiteboard)
	ON_MESSAGE( WM_SHELLNOTIFY, OnShellNotifyProc )
	ON_MESSAGE( WM_HOTKEY, OnHotkey )
	ON_COMMAND(IDM_WHITEBOARD, OnWhiteboard)

	ON_MESSAGE( MM_WIM_OPEN, WaveInOpen )
	ON_MESSAGE( MM_WIM_DATA, WaveInData )
	ON_MESSAGE( MM_WIM_CLOSE, WaveInClose )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstantMessagingDlg message handlers

BOOL CInstantMessagingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	/// ��ʼ������
	Init();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInstantMessagingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	/// ��С���͵����رհ�ťʱ�Ĵ���
	else if( nID == SC_MINIMIZE )
	{
		this->ShowWindow( SW_HIDE);
	}
	else if( nID == SC_CLOSE )
	{
		OnCancel();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInstantMessagingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CInstantMessagingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/// ��Enter��Escʱ�����˳�����
void CInstantMessagingDlg::OnOk() 
{	
}

void CInstantMessagingDlg::OnCancel() 
{
	if( IDOK == MessageBox( "Ҫ�˳���", "�˳�", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{
		/// �������û�����������Ϣ
		SendOffLineMessage();

		/// �����������Ƶ
		if( m_bConnectCamera )
		{
			capPreview( m_hWndVideo, FALSE );
			capDriverDisconnect( m_hWndVideo );
		}

		/// ɾ���û��б�����к���
		m_listCtrlFriends.DeleteAllUsers();

		/// �رռ����׽���
		m_pLisSocket->Close();
		delete [] m_pLisSocket;
		m_pLisSocket = NULL;

		/// �ر�¼��
		waveInReset( m_hWaveIn );
		waveInClose( m_hWaveIn );

		/// ɾ��¼��������
		delete [] m_pBuffer1;
		delete [] m_pBuffer2;
		delete [] m_pWaveHdr1;
		delete [] m_pWaveHdr2;

		if( m_pVideoChatListenSocket )
		{
			m_pVideoChatListenSocket->Close();
			delete [] m_pVideoChatListenSocket;
			m_pVideoChatListenSocket = NULL;
		}

		DestroyWindow();
	}
}

void CInstantMessagingDlg::OnDestroy() 
{
	/// ɾ�������̽�����ͼ��
	::Shell_NotifyIcon( NIM_DELETE, &m_nid );	

	CDialog::OnDestroy();
}

void CInstantMessagingDlg::OnHotkey( WPARAM wParam, LPARAM lParam )
{
	if( 0 != m_arrMessageArrive.GetSize() )
	{
		OnChat( m_arrMessageArrive.GetAt( m_nTrayShowIndex ) );
		return;
	}
	if( this->IsWindowVisible() )
	{
		ShowWindow( SW_HIDE );
	}
	else
	{
		ShowWindow( SW_SHOW );
		::SetForegroundWindow( m_hWnd );
	}
}

void CInstantMessagingDlg::OnShellNotifyProc( WPARAM wParam, LPARAM lParam )
{
	if( lParam == WM_LBUTTONDBLCLK )
	{
		/// ���û����Ϣ������ʾ���
		if( 0 == m_arrMessageArrive.GetSize() )
		{
			::AfxGetApp()->m_pMainWnd->ShowWindow( SW_SHOW );
			::SetForegroundWindow( m_hWnd );
		}
		else
		{
			OnChat( m_arrMessageArrive.GetAt( m_nTrayShowIndex ) );
		}
	}
	else if( lParam == WM_RBUTTONUP )
	{
		
		CMenu menu;
		menu.LoadMenu( IDR_MENU1 );
		CMenu *pSubMenu;
		pSubMenu = menu.GetSubMenu( 0 );
		pSubMenu->ModifyMenu( IDM_STATE, MF_BYCOMMAND, IDM_STATE, STATE_ONLINE == m_wState ? "����" : "����" );
		if( STATE_OFFLINE == m_wState )
		{
			pSubMenu->DeleteMenu( IDM_CHATROOM, MF_BYCOMMAND );
		}
		CPoint mouse;
		GetCursorPos( &mouse );
		SetForegroundWindow();
		pSubMenu->TrackPopupMenu( 0, mouse.x, mouse.y, this );
	}
}

void CInstantMessagingDlg::Init()
{
	/// �����û��б��������Ի���
	m_listCtrlFriends.SetMainDlg( this );

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	/// ����������ʾ����ͼ��
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );

	/// �����ڷ��ڶ���
	SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

	/// ע���ȼ����ȼ���Ϣ������CONFIG_FILE�ļ���
	m_wVirtualKeyCode	= ::GetPrivateProfileInt( "HOTKEY", "wVirtualKeyCode", DEFAULT_VIRTUALKEYCODE, strPath );
	m_wModifiers		= ::GetPrivateProfileInt( "HOTKEY", "wModifiers", DEFAULT_MODIFIERS, strPath );
	WORD wModifiers		= m_wModifiers & HOTKEYF_SHIFT ? MOD_SHIFT : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_CONTROL ? MOD_CONTROL : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_ALT ? MOD_ALT : 0;
	::RegisterHotKey( m_hWnd, IDHOTKEY, wModifiers, m_wVirtualKeyCode );

	m_bAutoAddFriends	= ::GetPrivateProfileInt( "SETTING", "bAUTOADDFRIENDS", DEFAULT_AUTOADDFRIENDS, strPath );

	/// �����û��ĳ�ʼ������
	m_wFace		= ::GetPrivateProfileInt( "USERDATA", "wFace", DEFAULT_FACE, strPath );
	m_wState	= ::GetPrivateProfileInt( "USERDATA", "wState", DEFAULT_STATE, strPath );
	::GetPrivateProfileString( "USERDATA", "strNickName", DEFAULT_NICKNAME,
					m_strNickName.GetBuffer( MAXNICKNAMELENGTH ), MAXNICKNAMELENGTH, strPath );
	m_bmpFace.LoadBitmap( IDB_BITMAP1 + m_wFace );
	m_staticFace.SetBitmap( ( HBITMAP )m_bmpFace ); 
	m_comboxState.SetCurSel( m_wState );
	m_editNickName.SetWindowText( m_strNickName );
	m_strNickName.ReleaseBuffer();
	if( m_strNickName.GetLength() > MAXNICKNAMELENGTH )
	{
		m_strNickName = m_strNickName.Left( MAXNICKNAMELENGTH );
	}
	
	/// �����Ƿ�������ͷ
	m_bCamera			= FALSE;
	m_bConnectCamera	= FALSE;
	m_hWndVideo			= capCreateCaptureWindow( NULL, WS_CHILD, 0, 0, 1, 1, m_hWnd, IDD_CAPTUREVIDEO );
	if( capDriverConnect( m_hWndVideo, 0 ) )
	{
		m_bCamera = TRUE;
		capDriverDisconnect( m_hWndVideo );
	}

	/// ������С����������
	HICON hIcon				= AfxGetApp()->LoadIcon( m_wState == STATE_ONLINE ? IDR_MAINFRAME : IDI_OFFLINE );
	m_nid.hIcon				= hIcon;
	m_nid.hWnd				= m_hWnd;
	m_nid.cbSize			= sizeof( NOTIFYICONDATA );
	m_nid.uCallbackMessage	= WM_SHELLNOTIFY;
	m_nid.uFlags			= NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uID				= IDR_MENU1;
	sprintf( m_nid.szTip, "��ʱ�������" );
	Shell_NotifyIcon( NIM_ADD, &m_nid );

	/// ���������ϵ�˵�ͼ��
	m_btnAddFriend.setBmp( IDB_ADDFRIEND_NORMAL, 
						   IDB_ADDFRIEND_HOVER, 
						   IDB_ADDFRIEND_DOWN, 
						   IDB_ADDFRIEND_DISABLE );

	/// ���������ҵ�ͼ��
	m_btnChatRoom.setBmp( IDB_CHATROOM_NORMAL, 
						  IDB_CHATROOM_HOVER, 
						  IDB_CHATROOM_DOWN, 
						  IDB_CHATROOM_DISABLE );

	/// ���÷����ļ���ͼ��
	m_btnSendFiles.setBmp( IDB_SENDFILES_NORMAL, 
						   IDB_SENDFILES_HOVER, 
						   IDB_SENDFILES_DOWN, 
						   IDB_SENDFILES_DISABLE );

	/// ���ù�����Ļ��ͼ��
	m_btnShareScreen.setBmp( IDB_SHARESCREEN_NORMAL, 
						     IDB_SHARESCREEN_HOVER, 
							 IDB_SHARESCREEN_DOWN, 
							 IDB_SHARESCREEN_DISABLE );

	/// ���ðװ��ͼ��
	m_btnWhiteBoard.setBmp( IDB_WHITEBOARD_NORMAL, 
							IDB_WHITEBOARD_HOVER, 
							IDB_WHITEBOARD_DOWN, 
							IDB_WHITEBOARD_DISABLE );

	/// ������ʷ��ϵ�˼�¼
	int	nCount = ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
	CString strIndex;
	CString strHistoryIP;
	for( int nIndex = 1; nIndex <= nCount; nIndex++ )
	{
		strIndex.Format( "%d", nIndex );
		::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
		m_comboxFriend.AddString( strHistoryIP );
		strHistoryIP.ReleaseBuffer();
	}

	/// ��ʼ���û��б��
	m_listCtrlFriends.InsertColumn( 0, "", LVCFMT_LEFT, -1 );

	/// ��ʼ����Ӻ��ѵ�UDP�׽���
	m_pLisSocket = new CListeningSocket( this );
	m_pLisSocket->Create( DEFAULT_PORT, SOCK_DGRAM );

	/// ��������û���socket
	m_pSocket.Create( 0, SOCK_DGRAM );

	/// �õ��Լ���IP
	char szHostName[128]; 
	if( gethostname( szHostName, 128 ) == 0 ) 
	{
		struct hostent * pHost;	 
		pHost = gethostbyname( szHostName );   
		for( int i = 0; pHost != NULL && pHost->h_addr_list[ i ] != NULL; i++ )   
		{ 
			LPCSTR pszIP = inet_ntoa( *( struct in_addr * )pHost->h_addr_list[ i ] ); 
			m_strlstIP.AddTail( pszIP );
			m_comboxIP.AddString( pszIP );
		}
		m_strlstIP.AddTail( "127.0.0.1" );
		m_strlstIP.AddTail( "127.1" );
	}
	
	m_comboxIP.SetCurSel( 0 );

	/// ����С���������IPת��Ϊunsigned long������
	POSITION pos, posHead, posTail;
	posHead = m_strlstIP.GetHeadPosition();
	posTail = m_strlstIP.GetTailPosition();
	for( pos = posHead; pos < posTail; )
	{
		CString strNumIP;
		strNumIP.Format( "%u", htonl( inet_addr( m_strlstIP.GetNext( pos ) ) ) );
		m_strlstIP.AddTail( strNumIP ) ;
	}

	/// ���ö�ʱ�������ڼ����ϵ���Ƿ񱣳ֽ���
	if( STATE_ONLINE == m_wState )
	{
		SetTimer( TIMER_CONNECT, DEFAULT_REFRESH_TIME, NULL ); 
	}

	/// ����imagelist���������̵���ʾ
	m_imageListMA.Create( 16, 16, ILC_COLOR24 | ILC_MASK, 0, 0 );
	m_nTrayShowIndex = 0;

	/// ��ʼ��¼��
	m_pBuffer1 = new char[ AUDIO_BUFFER_SIZE ];
	m_pBuffer2 = new char[ AUDIO_BUFFER_SIZE ];

	m_WaveForm.wFormatTag		= WAVE_FORMAT_PCM;
	m_WaveForm.nChannels		= 1;
	m_WaveForm.nSamplesPerSec	= 11025;
	m_WaveForm.nAvgBytesPerSec	= 11025;
	m_WaveForm.nBlockAlign		= 1;
	m_WaveForm.wBitsPerSample	= 8;
	m_WaveForm.cbSize			= 0;

	waveInOpen( &m_hWaveIn, WAVE_MAPPER, &m_WaveForm, ( DWORD )m_hWnd, 0, CALLBACK_WINDOW );

	m_pWaveHdr1 = ( PWAVEHDR )new char[ sizeof( WAVEHDR ) ];
	m_pWaveHdr2 = ( PWAVEHDR )new char[ sizeof( WAVEHDR ) ];

	m_pWaveHdr1->lpData          = m_pBuffer1 ;
	m_pWaveHdr1->dwBufferLength  = AUDIO_BUFFER_SIZE ;
	m_pWaveHdr1->dwBytesRecorded = 0 ;
	m_pWaveHdr1->dwUser          = 0 ;
	m_pWaveHdr1->dwFlags         = 0 ;
	m_pWaveHdr1->dwLoops         = 1 ;
	m_pWaveHdr1->lpNext          = NULL ;
	m_pWaveHdr1->reserved        = 0 ;

	waveInPrepareHeader( m_hWaveIn, m_pWaveHdr1, sizeof( WAVEHDR ) );

	m_pWaveHdr2->lpData          = m_pBuffer2 ;
	m_pWaveHdr2->dwBufferLength  = AUDIO_BUFFER_SIZE ;
	m_pWaveHdr2->dwBytesRecorded = 0 ;
	m_pWaveHdr2->dwUser          = 0 ;
	m_pWaveHdr2->dwFlags         = 0 ;
	m_pWaveHdr2->dwLoops         = 1 ;
	m_pWaveHdr2->lpNext          = NULL ;
	m_pWaveHdr2->reserved        = 0 ;

	waveInPrepareHeader( m_hWaveIn, m_pWaveHdr2, sizeof( WAVEHDR ) );

	/// ��ʼ��
	m_dwTickTime = 0;

	/// �ж��Ƿ�ע��richtx32.ocx
	HKEY hKey;
	if( RegOpenKeyEx( HKEY_CLASSES_ROOT, "RICHTEXT.RichtextCtrl\\CLSID", 0, KEY_READ, &hKey ) != ERROR_SUCCESS ) 
	{
		HINSTANCE hLib = LoadLibrary( "RICHTX32.OCX" );
		
		/// �ؼ�������
		if( !hLib )
		{
			MessageBox( "RICHTX32.OCX�ؼ�δ�ҵ�" );
		}
		else
		{
			//��ȡע�ắ��DllRegisterServer��ַ
			FARPROC lpDllEntryPoint;
			lpDllEntryPoint = GetProcAddress( hLib, "DllRegisterServer" );
			
			/// ע��richtx32.ocx�ؼ�
			lpDllEntryPoint();
		}
	}

	/// ��Ƶ����socket��Ϊ��
	m_pVideoChatListenSocket = NULL;
}

void CInstantMessagingDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	::PostMessage( m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );	
	CDialog::OnLButtonDown(nFlags, point);
}


void CInstantMessagingDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu( IDR_MENU1 );
	CMenu *pSubMenu;
	pSubMenu = menu.GetSubMenu( 0 );
	pSubMenu->ModifyMenu( IDM_STATE, MF_BYCOMMAND, IDM_STATE, m_wState == STATE_ONLINE ? "����" : "����" );
	if( STATE_OFFLINE == m_wState )
	{
		pSubMenu->DeleteMenu( IDM_CHATROOM, MF_BYCOMMAND );
	}
	ClientToScreen( &point );
	SetForegroundWindow();
	pSubMenu->TrackPopupMenu( 0, point.x, point.y, this );
	CDialog::OnRButtonUp(nFlags, point);
}

void CInstantMessagingDlg::OnExit() 
{
	OnCancel();
}

void CInstantMessagingDlg::OnSetting() 
{
	CDialogSetting dlgSetting;
	dlgSetting.SetMainDlg( this );
	dlgSetting.DoModal();
}

void CInstantMessagingDlg::SetNickName( const CString strNickName )
{
	m_strNickName = strNickName;
	if( m_strNickName.IsEmpty() )
	{
		m_strNickName = DEFAULT_NICKNAME;
	}
	m_editNickName.SetWindowText( m_strNickName );

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;
	::WritePrivateProfileString( "USERDATA", "strNickName", m_strNickName, strPath );
	UpdateData( FALSE );
}

void CInstantMessagingDlg::SetFace( WORD wFace )
{
	m_wFace = wFace;
	m_bmpFace.DeleteObject();
	m_bmpFace.LoadBitmap( IDB_BITMAP1 + m_wFace );
	m_staticFace.SetBitmap( ( HBITMAP )m_bmpFace );

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strFace;
	strFace.Format( "%d", m_wFace );

	::WritePrivateProfileString( "USERDATA", "wFace", strFace, strPath );
	UpdateData( FALSE );
}

void CInstantMessagingDlg::SetAutoAddFriends( BOOL bAutoAddFriends )
{
	m_bAutoAddFriends = bAutoAddFriends;

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strAutoAddFriendse;
	strAutoAddFriendse.Format( "%d", m_bAutoAddFriends );

	::WritePrivateProfileString( "SETTING", "bAUTOADDFRIENDS", strAutoAddFriendse, strPath );
	UpdateData( FALSE );
}

void CInstantMessagingDlg::SetHotKey( WORD wVirtualKeyCode, WORD wModifiers )
{
	m_wVirtualKeyCode	= wVirtualKeyCode;
	m_wModifiers		= wModifiers;
	::UnregisterHotKey( m_hWnd, IDHOTKEY );
	wModifiers			= m_wModifiers & HOTKEYF_SHIFT ? MOD_SHIFT : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_CONTROL ? MOD_CONTROL : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_ALT ? MOD_ALT : 0;
	::RegisterHotKey( m_hWnd, IDHOTKEY, wModifiers, m_wVirtualKeyCode );

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;
	
	CString strVirtualKeyCode;
	CString strModifiers;
	strVirtualKeyCode.Format( "%d", m_wVirtualKeyCode );
	strModifiers.Format( "%d", m_wModifiers );

	::WritePrivateProfileString( "HOTKEY", "wVirtualKeyCode", strVirtualKeyCode, strPath );
	::WritePrivateProfileString( "HOTKEY", "wModifiers", strModifiers, strPath );
}

BOOL CInstantMessagingDlg::PreTranslateMessage(MSG* pMsg) 
{
	/// ˫���������öԻ���
	if( WM_LBUTTONDBLCLK == pMsg->message ) 
	{   
		if( GetDlgItem( IDC_EDIT_NICKNAME )->m_hWnd == pMsg->hwnd 
			|| m_hWnd == pMsg->hwnd ) 
		{ 
			OnSetting();
			return TRUE;
		} 
	}

	/// ����IP��Ͽ�del��
	else if( ::GetParent( pMsg->hwnd ) == m_comboxFriend.m_hWnd 
		&& pMsg->message == WM_KEYDOWN )
	{
		switch( pMsg->wParam )       
		{                         
        case VK_DELETE:
			if( m_comboxFriend.GetDroppedState() )
			{
				if( CB_ERR != m_comboxFriend.GetCurSel() )
				{
					CString strCurSel;
					m_comboxFriend.GetLBText( m_comboxFriend.GetCurSel(), strCurSel );
					DeleteHistory( m_comboxFriend.GetCurSel(), strCurSel );
				}
			}
			break;
		case VK_RETURN:
			OnBtnAddfriend();
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/// ����״̬������
void CInstantMessagingDlg::OnSelchangeComboState() 
{
	int nState = m_comboxState.GetCurSel();
	if( nState == m_wState )
	{
		return;
	}
	m_wState = nState;

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strState;
	strState.Format( "%d", m_wState );

	::WritePrivateProfileString( "USERDATA", "wState", strState, strPath );

	/// ��������ߣ���ɾ��������ϵ�ˣ�����������֪ͨ
	if( STATE_OFFLINE == m_wState )
	{
		SendOffLineMessage();
		m_arrFriends.RemoveAll();
		m_listCtrlFriends.DeleteAllItems();
		KillTimer( TIMER_CONNECT );
	}
	else if( STATE_ONLINE == m_wState )
	{
		SetTimer( TIMER_CONNECT, DEFAULT_REFRESH_TIME, NULL ); 
	}
	
	/// ������������ͼ��
	SetState();
}

void CInstantMessagingDlg::SetState()
{
	/// ���ĳ�������������ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon( m_wState == STATE_ONLINE ? IDR_MAINFRAME : IDI_OFFLINE );
	m_nid.hIcon	= hIcon;
	Shell_NotifyIcon( NIM_MODIFY, &m_nid );
}

void CInstantMessagingDlg::OnState() 
{
	m_wState = m_wState == STATE_ONLINE ? STATE_OFFLINE : STATE_ONLINE;
	m_comboxState.SetCurSel( m_wState );
	UpdateData( FALSE );
	SetState();

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strState;
	strState.Format( "%d", m_wState );

	::WritePrivateProfileString( "USERDATA", "wState", strState, strPath );
}

void CInstantMessagingDlg::OnBtnAddfriend() 
{
	/// ���������״̬��������Ӻ���
	if( STATE_OFFLINE == m_wState )
	{
		return;
	}

	CString strFriendIP;
	m_comboxFriend.GetWindowText( strFriendIP );

	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER user;
		user = m_arrFriends.GetAt( nIndex );
		if( user.strIP == strFriendIP )
		{
			MessageBox( "������Ӵ�IPΪ��ϵ�ˣ�", "�����ϵ��" );
			return;
		}
	}

	/// �жϵ�ַ�Ƿ�Ϸ�
	if( inet_addr( strFriendIP ) == INADDR_NONE || strFriendIP.IsEmpty() )
	{
		return;
	}

	/// �ж�IP�Ƿ����Լ�IP
	if( m_strlstIP.Find( strFriendIP ) )
	{
		MessageBox( "��������Լ�Ϊ��ϵ�ˣ�", "�����ϵ��" );
		return;
	}

	/// ����Ϊ�㲥��ַ
	if( strFriendIP.Right( 3 ) == "255" )
	{
		return;
	}

	/// �������ݰ�
	DATAPACKET dataPacket;
	dataPacket.command = REQUEST_ADD;
	
	/// ����������û��ṹ
	USER user;
	user.bHasCamera	= m_bCamera;
	user.nFace		= m_wFace;
	memcpy( user.strName, m_strNickName.GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
	m_strNickName.ReleaseBuffer();
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &user, sizeof( USER ) );

	/// ��������
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, strFriendIP );

	delete pSendData;
}

void CInstantMessagingDlg::OnListeningReceive()
{
	/// ��������
	CString strFriendIP;
	UINT uPort;
	char szReceive[ MAXDATAPACKETLENGTH ];
	m_pLisSocket->ReceiveFrom( szReceive, MAXDATAPACKETLENGTH, strFriendIP, uPort );

	/// ���������״̬�������κδ���
	if( STATE_OFFLINE == m_wState )
	{
		return;
	}

	/// װ�����ݰ�
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );
	USER user;
	CString strData;

	/// ����������в�ͬ�Ĵ���
	switch( dataPacket.command )
	{
	case REQUEST_ADD:												/// �����Ϊ��ϵ��
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		AddRequest( user );
		break;
	case REQUEST_DENY:												/// �ܾ���Ϊ��ϵ��
		MessageBox( "������ " + strFriendIP + " �ĺ��Ѿܾ�����������", "������", 
			MB_OK | MB_ICONINFORMATION);
		break;
	case REQUEST_ALLOW:												/// �����Ϊ��ϵ��
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		AddFriend( user );
		break;
	case OFFLINE:													/// ����
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		DeleteFriend( user );
		break;
	case REQUEST_KEEPCONNECT:										/// ���󱣳ֽ���
		KeepConnect( strFriendIP );
		break;
	case RESPONSE_KEEPCONNECT:										/// ��Ӧ���ֽ���
		m_strlstKeepConnent.RemoveAt( m_strlstKeepConnent.Find( strFriendIP ) );
		break;
	case CHATROOM_ADDREQUEST:										/// ���������ҵ�����
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		OnAddToChatRoomRequest( user );
		break;
	case CHAT_PREPARE_MESSAGE:										/// ���췢�͵���Ϣ��Ϣ
		PrepareChatMessage( szReceive, strFriendIP );
		break;
	case CHAT_MESSAGE:												/// ���췢�͵���Ϣ
		ReceiveChatMessage( szReceive, strFriendIP );
		break;
	case CHAT_RECEIVE:												/// ��ʼ����������Ϣ������
		SendChatMessage( szReceive, strFriendIP );
		break;
	case SENDFILES_NOTIFY:											/// ���ļ���������֪ͨ
		SendFilesResponse( szReceive, strFriendIP );
		break;
	case SENDFILES_DENY:											/// �ܾ������ļ�
		OnBtnSendfiles();
		memcpy( strData.GetBuffer( dataPacket.dwLength ), 
			szReceive + sizeof( DATAPACKET ),
			dataPacket.dwLength );
		strData.ReleaseBuffer( -1 );
		m_dlgSendFilesServer.DenyReceiveFile( strData, strFriendIP );
		break;
	case SHARESCREEN_ADDREQUEST:									/// ������Ļ�������
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		OnAddToShareScreenRequest( user );
		break;
	case WHITEBOARD_ADDREQUEST:										/// �װ��������
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		OnAddToWhiteBoardRequest( user );
		break;
	case VIDEOCHAT_VIDEO_ADDREQUEST:								/// ��Ƶ����
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		OnAddToVideoChatRequest( user );
		break;
	case VIDEOCHAT_VIDEO_ADDREQUEST_DENY:							/// �ܾ���Ƶ����
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		DenyAddToVideoChatRequest( user );
		break;
	case VIDEOCHAT_VIDEO_ADDREQUEST_ALLOW:							/// ������Ƶ����
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		AllowAddToVideoChatRequest( user );
		break;
	case VIDEOCHAT_VIDEO_DISCONNECT:								/// �Ͽ���Ƶ����
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		UserDisconnectFromVideoChat( user );
		break;
	default:
		break;
	}
}

void CInstantMessagingDlg::AddRequest( const USER user )
{
	/// �ж��Ƿ��Լ����Լ�
	CString strUserIP( user.strIP );
	if( -1 != strUserIP.Find( "127.0.0" ) )
	{
		return;
	}

	/// �ж��Ƿ��Ѿ���Ϊ��ϵ��
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER userTemp = m_arrFriends.GetAt( nIndex );
		if( 0 == strcmp( userTemp.strIP, user.strIP ) )
		{
			return;
		}
	}

	/// �ж�֮ǰ������ͬIP������
	if( m_strlstRequest.Find( user.strIP ) )
	{
		return;
	}
	m_strlstRequest.AddTail( user.strIP );

	/// ��ʾ�Ƿ��Ϊ����
	CString strPrompt;
	strPrompt.Format( "���� %s �ĺ��� %s �������Ϊ����\n��ͬ����", user.strIP, user.strName );

	/// �ܾ�����
	if( !m_bAutoAddFriends && IDCANCEL == MessageBox( strPrompt, "����", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		DATAPACKET dataPacket;
		dataPacket.command = REQUEST_DENY;
		
		/// ����ռ�
		UINT uDataLength = sizeof( DATAPACKET );
		BYTE *pSendData = new BYTE[ uDataLength ];
		memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
		
		/// ���;ܾ�����
		m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );

		delete pSendData;

		/// �������б���ɾ������IP
		m_strlstRequest.RemoveAt( m_strlstRequest.Find( user.strIP ) );
		return;
	}
	
	/// �����Ϊ����
	DATAPACKET dataPacket;
	dataPacket.command	= REQUEST_ALLOW;
	dataPacket.dwLength = sizeof( USER );
	
	USER mySelf;
	mySelf.bHasCamera	= m_bCamera;
	mySelf.nFace		= m_wFace;
	memcpy( mySelf.strName, m_strNickName.GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
	m_strNickName.ReleaseBuffer();
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &mySelf, sizeof( USER ) );
	
	/// ���;ܾ�����
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
	
	delete pSendData;

	/// �������б���ɾ������IP
	m_strlstRequest.RemoveAt( m_strlstRequest.Find( user.strIP ) );
	AddFriend( user );
}

void CInstantMessagingDlg::AddFriend( const USER user )
{
	m_listCtrlFriends.AddUser( user );
	m_arrFriends.Add( user );

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	/// ��ȡ��ʷ��ϵ�˼�¼
	BOOL bExistFriendHistory = FALSE;

	int	nCount		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
	int	nMax		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nMax", 0, strPath );
	int	nCurrent	= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCurrent", 1, strPath );
	CString strIndex;
	CString strHistoryIP;

	/// �ж��Ƿ���ڼ�¼
	for( int nIndex = 1; nIndex <= nCount; nIndex++ )
	{
		strIndex.Format( "%d", nIndex );
		::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
		if( !strHistoryIP.Compare( user.strIP ) )
		{
			bExistFriendHistory = TRUE;
			break;
		}
		strHistoryIP.ReleaseBuffer();
	}
	
	/// ��ʷ��¼��û�д�IP
	if( !bExistFriendHistory )
	{
		/// ��ǰ�ܼ�¼��С������¼��
		if( nCount < nMax )
		{
			strIndex.Format( "%d", ++nCount );
			::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, user.strIP, strPath );
			::WritePrivateProfileString( "HISTORYFRIENDS", "nCount", strIndex, strPath );
		}

		/// ��ǰ�ܼ�¼����������¼��
		else
		{
			strIndex.Format( "%d", ++nCurrent );
			::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, user.strIP, strPath );
			::WritePrivateProfileString( "HISTORYFRIENDS", "nCurrent", strIndex, strPath );
		}

		/// ����������ʷ��¼��Ͽ�
		int	nCount = ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
		CString strIndex;
		CString strHistoryIP;
		m_comboxFriend.ResetContent();
		for( int nIndex = 1; nIndex <= nCount; nIndex++ )
		{
			strIndex.Format( "%d", nIndex );
			::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
				strHistoryIP.GetBuffer( 16 ), 16, strPath );
			m_comboxFriend.AddString( strHistoryIP );
			strHistoryIP.ReleaseBuffer();
		}
	}
}

void CInstantMessagingDlg::SendOffLineMessage()
{
	DATAPACKET dataPacket;
	dataPacket.command = OFFLINE;
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	
	
	/// ȫ����������֪ͨ
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER user = m_arrFriends.GetAt( nIndex );
		m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
	}	
	
	delete pSendData;
}

void CInstantMessagingDlg::DeleteFriend( const USER user )
{
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER userDel = m_arrFriends.GetAt( nIndex );
		if( 0 == strcmp( userDel.strIP, user.strIP ) )
		{
			m_listCtrlFriends.DeleteUser( nIndex );
			m_arrFriends.RemoveAt( nIndex );
			break;
		}
	}
}

void CInstantMessagingDlg::OnTimer(UINT nIDEvent) 
{
	/// ���ֽ���
	if( TIMER_CONNECT == nIDEvent )	
	{
		/// ɾ��û�л�Ӧ����ϵ��
		for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
		{
			USER userDel = m_arrFriends.GetAt( nIndex );
			if( m_strlstKeepConnent.Find( userDel.strIP ) )
			{
				m_listCtrlFriends.DeleteUser( nIndex );
				m_arrFriends.RemoveAt( nIndex );
				nIndex--;
			}
		}
		m_strlstKeepConnent.RemoveAll();
		
		/// �ֱ��ͱ������ӵ���Ϣ�������͹���IP���뵽m_strlstKeepConnent
		for( nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
		{
			USER user = m_arrFriends.GetAt( nIndex );
			
			DATAPACKET dataPacket;
			dataPacket.command = REQUEST_KEEPCONNECT;
			
			/// ����ռ�
			UINT uDataLength = sizeof( DATAPACKET );
			BYTE *pSendData = new BYTE[ uDataLength ];
			memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
			
			m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
			
			delete pSendData;
			
			m_strlstKeepConnent.AddTail( user.strIP );
		}
	}

	/// ������ʾ
	else if( TIMER_TRAYSHOW == nIDEvent )
	{
		/// ��ʾm_nTrayShowIndexͼ��
		static BOOL bShow = TRUE;
		if( m_nTrayShowIndex >= m_arrMessageArrive.GetSize() )
		{
			m_nTrayShowIndex = 0;
		}

		CBitmap bitmap32;
		CBitmap bitmap16;
		HBITMAP hBitmap;
		bitmap32.LoadBitmap( IDB_BITMAP1 + m_arrFriends.GetAt( m_arrMessageArrive.GetAt( m_nTrayShowIndex ) ).nFace );
		hBitmap = ( HBITMAP )::CopyImage( ( HBITMAP )bitmap32, IMAGE_BITMAP, 16, 16, LR_COPYDELETEORG );
		bitmap16.Attach( hBitmap );
		m_imageListMA.Add( &bitmap16, FACEBGCOLOR );
		bitmap16.DeleteObject();
		bitmap32.DeleteObject();
		::DeleteObject( hBitmap );

		/// ���ĳ�������������ͼ��
		HICON hIcon = m_imageListMA.ExtractIcon( 0 );
		m_imageListMA.Remove( 0 );
		if( bShow )
		{
			m_nid.hIcon	= hIcon;
			m_nTrayShowIndex++;
			if( m_nTrayShowIndex >= m_arrMessageArrive.GetSize() )
			{
				m_nTrayShowIndex = 0;
			}
		}
		else
		{
			m_nid.hIcon = NULL;
		}
		bShow = !bShow;
		Shell_NotifyIcon( NIM_MODIFY, &m_nid );
	}

	CDialog::OnTimer(nIDEvent);
}

void CInstantMessagingDlg::KeepConnect( CString strIP )
{
	DATAPACKET dataPacket;
	dataPacket.command = RESPONSE_KEEPCONNECT;
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, strIP );
	
	delete pSendData;
}

void CInstantMessagingDlg::DeleteFriend( int nIndex )
{
	USER user = m_arrFriends.GetAt( nIndex );

	CString strPrompt;
	strPrompt.Format( "Ҫɾ�� %s �ĺ��� %s ��", user.strIP, user.strName );

	/// ��ʾ�Ƿ�ɾ��
	if( IDCANCEL == MessageBox( strPrompt, "ɾ������", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{
		return;
	}

	DATAPACKET dataPacket;
	dataPacket.command = OFFLINE;
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );

	delete pSendData;
	
	m_listCtrlFriends.DeleteUser( nIndex );
	m_arrFriends.RemoveAt( nIndex );
}

void CInstantMessagingDlg::SendFriendMessage( const USER user, CONTROLCOMMAND command )
{
	DATAPACKET dataPacket;
	dataPacket.command = command;
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &user, sizeof( USER ) );
	
	/// ������������
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
	
	delete pSendData;
}

void CInstantMessagingDlg::OnBtnChatroom() 
{
	if( !m_dlgCRServer )
	{
		/// GetDesktopWindow()Ϊ���Ի���
		m_dlgCRServer.Create( IDD_CHATROOM_SERVER, GetDesktopWindow() );
		m_dlgCRServer.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		::SetForegroundWindow( m_dlgCRServer.m_hWnd );
		m_dlgCRServer.FlashWindow( TRUE );
	}
}

void CInstantMessagingDlg::OnChatroom() 
{
	OnBtnChatroom();
}

void CInstantMessagingDlg::OnAddToChatRoomRequest( const USER userServer )
{
	if( 0 != m_arrCRClient.GetSize() )
	{
		return;
	}
	/// �ж�֮ǰ������ͬIP������
	if( m_strlstChatRoomRequest.Find( userServer.strIP ) )
	{
		return;
	}
	m_strlstChatRoomRequest.AddTail( userServer.strIP );

	/// ��ʾ�Ƿ����������
	CString strPrompt;
	strPrompt.Format( "���� %s �ĺ��� %s ����������������\n��ͬ����", userServer.strIP, userServer.strName );

	/// �ܾ�����
	if( IDCANCEL == MessageBox( strPrompt, "������", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		/// ����������;ܾ����������ҵ�����
		SendUserCommandToIP( CHATROOM_ADDREQUEST_DENY, userServer.strIP, CHATROOM_SERVER_PORT, NULL );
		
		/// �������б���ɾ������IP
		m_strlstChatRoomRequest.RemoveAt( m_strlstChatRoomRequest.Find( userServer.strIP ) );
		return;
	}

	/// ���������ҿͻ��˲�������б�
	CChatRoomClientDlg *pCRClientDlg = new CChatRoomClientDlg();
	pCRClientDlg->Create( IDD_CHATROOM_CLIENT, GetDesktopWindow() );
	pCRClientDlg->AcceptAddRequest( userServer );
	pCRClientDlg->ShowWindow( SW_SHOW );
	m_arrCRClient.Add( pCRClientDlg );

	/// �������б���ɾ������IP
	m_strlstChatRoomRequest.RemoveAt( m_strlstChatRoomRequest.Find( userServer.strIP ) );
}

void CInstantMessagingDlg::OnAddToShareScreenRequest( const USER userServer )
{
	/// ����Ѿ����������Ļ�������ٹ��������˵���Ļ
	if( m_dlgSSClient )
	{
		return;
	}

	/// �ж�֮ǰ������ͬIP������
	if( m_strlstShareScreenRequest.Find( userServer.strIP ) )
	{
		return;
	}
	m_strlstShareScreenRequest.AddTail( userServer.strIP );

	/// ��ʾ�Ƿ���빲����Ļ
	CString strPrompt;
	strPrompt.Format( "���� %s �ĺ��� %s �������Ta����Ļ\n��ͬ����", userServer.strIP, userServer.strName );

	/// �ܾ�����
	if( IDCANCEL == MessageBox( strPrompt, "������Ļ", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		/// ����������;ܾ����빲����Ļ������
		SendUserCommandToIP( SHARESCREEN_ADDREQUEST_DENY, userServer.strIP, SHARESCREENSERVER_PORT, NULL );
		
		/// �������б���ɾ������IP
		m_strlstShareScreenRequest.RemoveAt( m_strlstShareScreenRequest.Find( userServer.strIP ) );
		return;
	}

	/// ����������Ļ�ͻ��˲�������б�
	m_dlgSSClient.Create( IDD_SHARESCREEN_CLIENT, GetDesktopWindow() );
	m_dlgSSClient.AcceptAddRequest( userServer );
	m_dlgSSClient.ShowWindow( SW_SHOW );

	/// �������б���ɾ������IP
	m_strlstShareScreenRequest.RemoveAt( m_strlstShareScreenRequest.Find( userServer.strIP ) );
}

void CInstantMessagingDlg::OnAddToWhiteBoardRequest( const USER userServer )
{
	/// ����Ѿ�����װ壬�����ٹ��������˵İװ�
	if( m_dlgWhiteBoardClient )
	{
		return;
	}

	/// �ж�֮ǰ������ͬIP������
	if( m_strlstWhiteBoardRequest.Find( userServer.strIP ) )
	{
		return;
	}
	m_strlstWhiteBoardRequest.AddTail( userServer.strIP );

	/// ��ʾ�Ƿ����װ�
	CString strPrompt;
	strPrompt.Format( "���� %s �ĺ��� %s ����������װ�\n��ͬ����", userServer.strIP, userServer.strName );

	/// �ܾ�����
	if( IDCANCEL == MessageBox( strPrompt, "�װ�", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		/// ����������;ܾ�����װ������
		SendUserCommandToIP( WHITEBOARD_ADDREQUEST_DENY, userServer.strIP, WHITEBOARD_SERVER_PORT, NULL );
		
		/// �������б���ɾ������IP
		m_strlstWhiteBoardRequest.RemoveAt( m_strlstWhiteBoardRequest.Find( userServer.strIP ) );
		return;
	}

	/// �����װ�ͻ��˲�������б�
	m_dlgWhiteBoardClient.Create( IDD_WHITEBOARD_CLIENT, GetDesktopWindow() );
	m_dlgWhiteBoardClient.AcceptAddRequest( userServer );
	m_dlgWhiteBoardClient.ShowWindow( SW_SHOW );

	/// �������б���ɾ������IP
	m_strlstWhiteBoardRequest.RemoveAt( m_strlstWhiteBoardRequest.Find( userServer.strIP ) );
}

void CInstantMessagingDlg::OnAddToVideoChatRequest( const USER user )
{
	/// �ж�֮ǰ�Ƿ�����ͬIP������
	if( m_strlstVideoChatRequest.Find( user.strIP ) )
	{
		return;
	}
	m_strlstVideoChatRequest.AddTail( user.strIP );

	/// ��������
	::PlaySound( "audio.wav", NULL, SND_FILENAME | SND_ASYNC);

	/// ��ʾ�Ƿ������Ƶ����
	CString strPrompt;
	strPrompt.Format( "���� %s �ĺ��� %s ��������Ƶ����\n��ͬ����", user.strIP, user.strName );

	/// �ܾ�����
	if( IDCANCEL == MessageBox( strPrompt, "��Ƶ����", MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONQUESTION ) )
	{
		/// ����������;ܾ�������Ƶ���������
		SendUserCommandToIP( VIDEOCHAT_VIDEO_ADDREQUEST_DENY, user.strIP, DEFAULT_PORT, NULL );
		
		/// �������б���ɾ������IP
		m_strlstVideoChatRequest.RemoveAt( m_strlstVideoChatRequest.Find( user.strIP ) );
		return;
	}

	/// ��������������������Ƶ���������
	SendUserCommandToIP( VIDEOCHAT_VIDEO_ADDREQUEST_ALLOW, user.strIP, DEFAULT_PORT, NULL );

	/// �����Ƿ��Ѿ�����user����Ƶ���촰��
	for( int nIndex = 0; nIndex < m_arrVideoChatDlg.GetSize(); nIndex++ )
	{
		/// �Ѿ��д򿪵Ĵ���
		if( 0 == strcmp( user.strIP, m_arrVideoChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			::SetForegroundWindow( m_arrVideoChatDlg.GetAt( nIndex )->m_hWnd );
			m_arrVideoChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
			break;
		}
	}
	
	/// ���û�д򿪵Ĵ���
	if( nIndex == m_arrVideoChatDlg.GetSize() )
	{	
		/// �����´���
		CVideoChatDlg *pVideoChatDlg = new CVideoChatDlg( this );
		
		/// GetDesktopWindow()Ϊ���Ի���
		pVideoChatDlg->Create( IDD_VIDEOCHAT, GetDesktopWindow() );
		pVideoChatDlg->SetChatUser( user );
		pVideoChatDlg->ConnectToServer();
		pVideoChatDlg->ShowWindow( SW_SHOW );
		m_arrVideoChatDlg.Add( pVideoChatDlg );
	}

	/// ���û����������Ƶ����������Ƶ
	if( !m_bConnectCamera )
	{
		if( capDriverConnect( m_hWndVideo, 0 ) )
		{
			/// ������Ƶ�Ĵ�С
			BITMAPINFO bmpInfo;
			capGetVideoFormat( m_hWndVideo, &bmpInfo, sizeof( BITMAPINFO ) );
			bmpInfo.bmiHeader.biBitCount	= 24;
			bmpInfo.bmiHeader.biWidth		= VIDEOCHAT_VIDEO_WIDTH;
			bmpInfo.bmiHeader.biHeight		= VIDEOCHAT_VIDEO_HEIGHT;
			bmpInfo.bmiHeader.biSizeImage	= bmpInfo.bmiHeader.biWidth * bmpInfo.bmiHeader.biHeight * bmpInfo.bmiHeader.biBitCount / 8;
			capSetVideoFormat( m_hWndVideo, &bmpInfo, sizeof( BITMAPINFO ) );

			CAPDRIVERCAPS caps;
			capDriverGetCaps( m_hWndVideo, sizeof( caps ), &caps );
			
			if( caps.fHasOverlay )
			{
				capOverlay( m_hWndVideo, TRUE );
			}
			
			CAPTUREPARMS params;
			capCaptureGetSetup( m_hWndVideo, &params, sizeof( params ) );
			params.fYield			= TRUE;
			params.fAbortLeftMouse	= FALSE;
			params.fAbortRightMouse	= FALSE;
			params.fLimitEnabled	= FALSE;
			params.vKeyAbort		= FALSE;
			params.fCaptureAudio	= TRUE;
			capCaptureSetSetup( m_hWndVideo, &params, sizeof( params ) );
			
			capSetCallbackOnVideoStream( m_hWndVideo, EncodeCallback );
			capCaptureSequenceNoFile( m_hWndVideo );
			
			/// ��������Ƶ
			m_bConnectCamera = TRUE;
		}
	}

	/// ��ʼ��Ƶ
	waveInStart( m_hWaveIn );

	/// �õ�¼����ʱ��
	if( 0 == m_dwTickTime )
	{
		m_dwTickTime = ::GetTickCount();
	}

	/// �������б���ɾ������IP
	m_strlstVideoChatRequest.RemoveAt( m_strlstVideoChatRequest.Find( user.strIP ) );
}

/// ��ָ��IP��PORT����ָ������
void CInstantMessagingDlg::SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT uPort, const USER *pUser )
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
	m_pLisSocket->SendTo( pSendData, uDataLength, uPort, szIP );

	delete pSendData;
}

/// �����ҿͻ��˹ر�
void CInstantMessagingDlg::DelCRClientFromList( LPCSTR szIP )
{
	for( int nIndex = 0; nIndex < m_arrCRClient.GetSize(); nIndex++ )
	{
		CChatRoomClientDlg *pCRClientDlg = ( CChatRoomClientDlg * )m_arrCRClient.GetAt( nIndex );

		if( 0 == strcmp( pCRClientDlg->GetServerIP(), szIP ) )
		{
			/// ���б����Ƴ�
			m_arrCRClient.RemoveAt( nIndex );
			break;
		}
	}
}

/// ������Ϣ����ʱ���պ���
void CInstantMessagingDlg::OnChat( UINT nIndex )
{
	int nUserIndex = nIndex;
	USER userChat = m_arrFriends.GetAt( nIndex );
	
	/// �����Ƿ��Ѿ�����userChat�����촰��
	for( nIndex = 0; nIndex < m_arrChatDlg.GetSize(); nIndex++ )
	{
		/// �Ѿ��д򿪵Ĵ���
		if( 0 == strcmp( userChat.strIP, m_arrChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			::SetForegroundWindow( m_arrChatDlg.GetAt( nIndex )->m_hWnd );
			m_arrChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
			return;
		}
	}
	
	/// �����´���
	CChatDlg *pChatDlg = new CChatDlg( this );

	/// GetDesktopWindow()Ϊ���Ի���
	pChatDlg->Create( IDD_CHAT, GetDesktopWindow() );
	pChatDlg->SetChatUser( userChat );
	pChatDlg->ShowWindow( SW_SHOW );
	m_arrChatDlg.Add( pChatDlg );

	/// ����Ϣ���б���
	CMapStringToString *pMapTimeAndMessage;
	if( m_mapIPToChat.Lookup( userChat.strIP, ( CObject*& )pMapTimeAndMessage ) )
	{
		POSITION pos = pMapTimeAndMessage->GetStartPosition();
		while( 0 != pos )
		{
			CString strTime;
			CString strMessage;
			pMapTimeAndMessage->GetNextAssoc( pos, strTime, strMessage );
			pChatDlg->ReceiveMessage( strTime, strMessage );
		}
		
		/// ���б���ɾ�����յ�����Ϣ
		pMapTimeAndMessage->RemoveAll();
		delete pMapTimeAndMessage;
		m_mapIPToChat.RemoveKey( userChat.strIP );
		
		/// ������ɾ����̬��ʾ����Ӧͼ��
		for( nIndex = 0; nIndex < m_arrMessageArrive.GetSize(); nIndex++ )
		{
			if( m_arrMessageArrive.GetAt( nIndex ) == nUserIndex )
			{
				m_arrMessageArrive.RemoveAt( nIndex );

				/// ���������û������ͼ�꣬��ԭͼ�겢�ر�timer
				if( 0 == m_arrMessageArrive.GetSize() )
				{
					KillTimer( TIMER_TRAYSHOW );
					SetState();
				}
				break;
			}
		}
	}
}	

void CInstantMessagingDlg::OnCloseChatDlg( LPCSTR szIP )
{
	/// �����Ѿ�����szIP�����촰��
	for( int nIndex = 0; nIndex < m_arrChatDlg.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( szIP, m_arrChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			m_arrChatDlg.RemoveAt( nIndex );
			return;
		}
	}
}


/// ����ʷ��¼��ɾ��ָ����¼
void CInstantMessagingDlg::DeleteHistory( int nIndex, const CString strHistory )
{
	/// ����������ʷ��¼��Ͽ�
	m_comboxFriend.DeleteString( nIndex );

	/// �����ļ�·��
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	int	nCount		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
	int	nMax		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nMax", 0, strPath );
	int	nCurrent	= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCurrent", 1, strPath );

	CString strIndex;
	CString strHistoryIP;
	for( nIndex = 1; nIndex <= nCount; nIndex++ )
	{
		strIndex.Format( "%d", nIndex );
		::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
		strHistoryIP.ReleaseBuffer();
		if( strHistory == strHistoryIP )
		{
			if( nCurrent >= nIndex )
			{
				if( 1 == nCurrent )
				{
					nCurrent = 2;
				}
				strIndex.Format( "%d", nCurrent - 1 );
				::WritePrivateProfileString( "HISTORYFRIENDS", "nCurrent", strIndex, strPath );
			}
			for( int nIndex1 = nIndex + 1; nIndex1 <= nCount; nIndex1++ )
			{
				strIndex.Format( "%d", nIndex1 );
				::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
				strHistoryIP.ReleaseBuffer();
				strIndex.Format( "%d", nIndex1 - 1 );
				::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, strHistoryIP, strPath );
			}
			strIndex.Format( "%d", nIndex1 - 1 );
			::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, NULL, strPath );
			break;
		}
	}
	strIndex.Format( "%d", nCount - 1 );
	::WritePrivateProfileString( "HISTORYFRIENDS", "nCount", strIndex, strPath );
}

/// ����������Ϣ
void CInstantMessagingDlg::SendPreChatMessage( const USER userChat, CString strTime, CString strSend )
{
	DATAPACKET dataPacket;
	CHATPACKETINFO chatPacketInfo;

	/// ������Ϣ�ĳ���
	DWORD dwSendLength = strSend.GetLength();

	/// ������Ϣ��Ϣ
	dataPacket.command	= CHAT_PREPARE_MESSAGE;
	dataPacket.dwLength	= dwSendLength;

	UINT uDataLength = sizeof( DATAPACKET ) + 10;
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), strTime.GetBuffer( 10 ), 10 );
	strTime.ReleaseBuffer( -1 );

	/// ��������
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, userChat.strIP );

	delete pSendData;

	/// ֮ǰ��δ���������Ϣ
	CString strBeforeSend;
	if( m_mapSendChatMessage.Lookup( userChat.strIP, strBeforeSend ) )
	{
		
	}

	/// ��Ҫ���͵���Ϣ���浽m_mapSendChatMessage
	m_mapSendChatMessage.SetAt( userChat.strIP, strSend );
}

/// Ϊ����������Ϣ��׼��
void CInstantMessagingDlg::PrepareChatMessage( LPCSTR szReceive, LPCSTR szIP )
{
	LPVOID pData = NULL;

	/// ��һ�ε���Ϣ��û�����꣬����Ϣ�ֵ������һ�ε���Ϣ����
	if( m_mapIPToData.Lookup( szIP, pData ) )
	{
		delete pData;
		m_mapIPToData.RemoveKey( szIP );
		m_mapIPToTime.RemoveKey( szIP );
	}

	/// ��������map������Ϣ
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );

	char szTime[ 10 ];
	memcpy( szTime, szReceive + sizeof( DATAPACKET ), 10 );

	pData = new char[ dataPacket.dwLength ];

	m_mapIPToData.SetAt( szIP, pData );
	m_mapIPToTime.SetAt( szIP, szTime );

	/// ���Ϳ�ʼ�����ļ�������
	CHATPACKETINFO chatPacketInfo;
	chatPacketInfo.nCurrent = 0;
	dataPacket.command = CHAT_RECEIVE;

	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &chatPacketInfo, sizeof( CHATPACKETINFO ) );

	/// ��������
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );

	delete pSendData;
}

/// ����������Ϣ
void CInstantMessagingDlg::ReceiveChatMessage( LPCSTR szReceive, LPCSTR szIP )
{
	CHATPACKETINFO chatPacketInfo;
	memcpy( &chatPacketInfo, szReceive + sizeof( DATAPACKET ), sizeof( CHATPACKETINFO ) );

	LPVOID pData = NULL;

	/// ���ҵ�������ݵĵ�ַ
	if( m_mapIPToData.Lookup( szIP, pData ) )
	{
		memcpy( ( BYTE *)pData + chatPacketInfo.nCurrent * MAXCHATLENGTH,
			szReceive + sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO ),
			chatPacketInfo.nLength );


		/// ���ݽ������
		if( chatPacketInfo.nCurrent + 1 == chatPacketInfo.nTotal )
		{
			/// ��������
			::PlaySound( "msg.wav", NULL, SND_FILENAME | SND_ASYNC);

			/// ���Ҵ����Ƿ��Ѿ���
			for( int nIndex = 0; nIndex < m_arrChatDlg.GetSize(); nIndex++ )
			{
				/// �����Ѿ��򿪣�����Ϣֱ�ӷ��͵����ڽ��ձ༭����
				if( 0 == strcmp( szIP, m_arrChatDlg.GetAt( nIndex )->GetChatIP() ) )
				{
					CString strTime;
					m_mapIPToTime.Lookup( szIP, strTime );
					m_arrChatDlg.GetAt( nIndex )->ReceiveMessage( strTime, ( char * )pData );
					if( ::GetForegroundWindow() != m_arrChatDlg.GetAt( nIndex )->m_hWnd )
					{
						m_arrChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
					}				

					/// ɾ����¼��Ϣ
					delete pData;
					m_mapIPToData.RemoveKey( szIP );
					m_mapIPToTime.RemoveKey( szIP );
					return;
				}
			}
			
			/// ����û�д򿪣�����Ϣ�ӵ���m_mapIPToChat
			CString strTime;
			m_mapIPToTime.Lookup( szIP, strTime );
			
			CMapStringToString *pMapTimeAndMessage;
			if( !m_mapIPToChat.Lookup( szIP, ( CObject*& )pMapTimeAndMessage ) )
			{
				pMapTimeAndMessage = new CMapStringToString();
			}
			pMapTimeAndMessage->SetAt( strTime, ( char * )pData );
			m_mapIPToChat.SetAt( szIP, pMapTimeAndMessage );

			/// ��������ͷ����ʾ
			AddTrayIcon( szIP );

			/// ɾ����¼��Ϣ
			delete pData;
			m_mapIPToData.RemoveKey( szIP );
			m_mapIPToTime.RemoveKey( szIP );
			return;
		}

		/// ����û�����꣬�������ͽ�����Ϣ������
		else
		{
			chatPacketInfo.nCurrent = chatPacketInfo.nCurrent + 1;

			DATAPACKET dataPacket;
			dataPacket.command = CHAT_RECEIVE;
			
			UINT uDataLength = sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO );
			BYTE *pSendData = new BYTE[ uDataLength ];
			memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
			memcpy( pSendData + sizeof( DATAPACKET ), &chatPacketInfo, sizeof( CHATPACKETINFO ) );
			
			/// ��������
			m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
			
			delete pSendData;
		}
	}
}

/// ��ʼ��������
void CInstantMessagingDlg::SendChatMessage( LPCSTR szReceive, LPCSTR szIP )
{
	CHATPACKETINFO chatPacketInfo;
	memcpy( &chatPacketInfo, szReceive + sizeof( DATAPACKET ), sizeof( CHATPACKETINFO ) );

	CString strSend;

	/// ������szIP��Ӧ����Ϣmap
	if( m_mapSendChatMessage.Lookup( szIP, strSend ) )
	{
		/// ������Ϣ�ĳ���
		DWORD dwSendLength = strSend.GetLength();
		
		/// ��������
		int nTotal;
		if( 0 == dwSendLength % MAXCHATLENGTH )
		{
			nTotal = dwSendLength / MAXCHATLENGTH;
		}
		else
		{	
			nTotal = dwSendLength / MAXCHATLENGTH + 1;
		}
		
		/// ���һ�����ĳ���
		int nLastLength = dwSendLength - MAXCHATLENGTH * ( nTotal - 1 );

		DATAPACKET dataPacket;
		dataPacket.command = CHAT_MESSAGE;

		chatPacketInfo.nLength = MAXCHATLENGTH;
		if( chatPacketInfo.nCurrent + 1 == nTotal )
		{
			chatPacketInfo.nLength = nLastLength;
		}
		chatPacketInfo.nTotal = nTotal;
		
		LPCSTR pData = strSend.GetBuffer( strSend.GetLength() );

		/// ��ʼ����ָ���İ�
		UINT uDataLength = sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO ) + chatPacketInfo.nLength;
		BYTE *pSendData = new BYTE[ uDataLength ];
		memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
		memcpy( pSendData + sizeof( DATAPACKET ), &chatPacketInfo, sizeof( CHATPACKETINFO ) );
		memcpy( pSendData + sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO ),
			pData + chatPacketInfo.nCurrent * MAXCHATLENGTH,
			chatPacketInfo.nLength );

		strSend.ReleaseBuffer( -1 );
		
		/// ��������
		m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
		
		delete pSendData;

		/// ���͵������һ����
		if( chatPacketInfo.nCurrent + 1 == nTotal )
		{
			m_mapSendChatMessage.RemoveKey( szIP );
		}
	}
}

/// ��ָ��ip���û���ͷ����뵽���̶�̬��ʾ
void CInstantMessagingDlg::AddTrayIcon( LPCSTR szIP )
{
	/// �õ�szIP��Ӧ�ĺ������
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( szIP, m_arrFriends.GetAt( nIndex ).strIP ) )
		{
			break;
		}
	}

	/// �ж�ͷ���Ƿ��Ѿ���������ʾ
	int nUserIndex = nIndex;
	for( nIndex = 0; nIndex < m_arrMessageArrive.GetSize(); nIndex++ )
	{
		/// �Ѿ���������ʾ�������κδ���
		if( m_arrMessageArrive.GetAt( nIndex ) == nUserIndex )
		{
			return;
		}
	}

	/// ���û���ͷ��û����������ʾ�����ӽ�������
	m_arrMessageArrive.Add( nUserIndex );
	SetTimer( TIMER_TRAYSHOW, 400, NULL );
}

/// �����ļ�
void CInstantMessagingDlg::OnBtnSendfiles() 
{
	if( !m_dlgSendFilesServer )
	{
		/// GetDesktopWindow()Ϊ���Ի���
		m_dlgSendFilesServer.Create( IDD_SENDFILES_SERVER, GetDesktopWindow() );
		m_dlgSendFilesServer.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		if( m_dlgSendFilesServer.IsWindowVisible() )
		{
			::SetForegroundWindow( m_dlgSendFilesServer.m_hWnd );
			m_dlgSendFilesServer.FlashWindow( TRUE );
		}
		else
		{
			m_dlgSendFilesServer.ShowWindow( SW_SHOW );
		}
	}
}

void CInstantMessagingDlg::OnSendfiles() 
{
	OnBtnSendfiles();
}

void CInstantMessagingDlg::OnReceivefiles() 
{
	if( !m_dlgSendFilesClient )
	{
		/// GetDesktopWindow()Ϊ���Ի���
		m_dlgSendFilesClient.Create( IDD_SENDFILES_CLIENT, GetDesktopWindow() );
		m_dlgSendFilesClient.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		if( m_dlgSendFilesClient.IsWindowVisible() )
		{
			::SetForegroundWindow( m_dlgSendFilesClient.m_hWnd );
			m_dlgSendFilesClient.FlashWindow( TRUE );
		}
		else
		{
			m_dlgSendFilesClient.ShowWindow( SW_SHOW );
		}
	}
}

/// ��ָ��IP�û����ʹ����ļ���֪ͨ
void CInstantMessagingDlg::SendFilesNotify( LPCSTR szIP, CString strFile, DWORD dwLength )
{
	DATAPACKET dataPacket;
	dataPacket.command = SENDFILES_NOTIFY;
	dataPacket.dwLength = strFile.GetLength();
	
	UINT uDataLength = sizeof( DATAPACKET ) + strFile.GetLength() + sizeof( DWORD );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), 
		strFile.GetBuffer( strFile.GetLength() ), 
		strFile.GetLength() );
	strFile.ReleaseBuffer( -1 );
	memcpy( pSendData + sizeof( DATAPACKET ) + strFile.GetLength(),
		&dwLength,
		sizeof( DWORD ) );
	
	/// ��������
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
	
	delete pSendData;
}

/// ��Ӧ�Ƿ���մ�����ļ�
void CInstantMessagingDlg::SendFilesResponse( LPCSTR szReceive, LPCSTR szIP )
{
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );

	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		/// �ҵ������ļ���USER
		if( 0 == strcmp( szIP, m_arrFriends.GetAt( nIndex ).strIP ) )
		{
			break;
		}
	}

	CString strFile;
	memcpy( strFile.GetBuffer( dataPacket.dwLength ), 
		szReceive + sizeof( DATAPACKET ),
		dataPacket.dwLength );
	strFile.ReleaseBuffer( -1 );
	DWORD dwLength;
	memcpy( &dwLength, szReceive + sizeof( DATAPACKET ) + dataPacket.dwLength,
		sizeof( DWORD ) );

	CString strPromp;
	strPromp.Format( "���� %s �ĺ��� %s ���������ļ� %s\n���Ƿ���գ�", 
		m_arrFriends.GetAt( nIndex ).strIP,
		m_arrFriends.GetAt( nIndex ).strName,
		strFile.Right( strFile.GetLength() - 1 - strFile.ReverseFind( '\\' ) ) );
	if( IDCANCEL == MessageBox( strPromp, "�����ļ�", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		DenyReceiveFile( strFile, szIP );
		return;
	}

	/// �򿪽����ļ��Ի���
	OnReceivefiles();
	
	m_dlgSendFilesClient.ReceiveFileFromIP( strFile, szIP, dwLength );
}

/// �ܾ������ļ�
void CInstantMessagingDlg::DenyReceiveFile( CString strFilePath, LPCSTR szIP )
{
	/// ���;ܾ����յ���Ϣ
	DATAPACKET dataPacket;
	dataPacket.command = SENDFILES_DENY;
	dataPacket.dwLength = strFilePath.GetLength();
	
	UINT uDataLength = sizeof( DATAPACKET ) + strFilePath.GetLength();
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), 
		strFilePath.GetBuffer( strFilePath.GetLength() ), 
		strFilePath.GetLength() );
	strFilePath.ReleaseBuffer( -1 );
	
	/// ��������
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
	
	delete pSendData;
}

/// ��IP�õ�USER
void CInstantMessagingDlg::GetUserFromIP( LPCSTR szIP, USER &user )
{
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( szIP, m_arrFriends.GetAt( nIndex ).strIP ) )
		{
			memcpy( &user, &m_arrFriends.GetAt( nIndex ), sizeof( USER ) );
			break;
		}
	}
}
void CInstantMessagingDlg::OnAddSection() 
{
	/// ���������״̬��������Ӻ���
	if( STATE_OFFLINE == m_wState )
	{
		return;
	}	

	CreateThread( NULL, 0, AddFriendsProc, this, 0, NULL );
}

/// �õ��Լ�IP�б���IP
CString CInstantMessagingDlg::GetComboBoxIP()
{
	CString strIP;
	m_comboxIP.GetWindowText( strIP );
	return strIP;
}

/// ��������û��Ľ��̺���
DWORD WINAPI AddFriendsProc( LPVOID lpParameter )
{
	CInstantMessagingDlg *pDlg = ( CInstantMessagingDlg * )lpParameter;

	/// �������ݰ�
	DATAPACKET dataPacket;
	dataPacket.command = REQUEST_ADD;
	
	/// ����������û��ṹ
	USER user;
	user.bHasCamera	= pDlg->HasCamera();
	user.nFace		= pDlg->GetFace();
	
	/// ����ռ�
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( user.strName, pDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
	pDlg->GetNickName().ReleaseBuffer();
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &user, sizeof( USER ) );

	CString strIP = pDlg->GetComboBoxIP();

	/// �õ�ǰ׺
	CString strPre = strIP.Left( strIP.ReverseFind( '.' ) + 1 );
	
	for( int i = 1 ; i <= 254; i++ )
	{
		CString strAddIP;
		strAddIP.Format( "%s%d", strPre.GetBuffer( strIP.GetLength() ), i );
		strPre.ReleaseBuffer( -1 );
				
		if( strAddIP != strIP )
		{
			/// ��������
			pDlg->m_pSocket.SendTo( pSendData, uDataLength, DEFAULT_PORT, strAddIP );	
		}
		Sleep( 200 );
	}
	
	delete pSendData;
	return 0;
}

void CInstantMessagingDlg::OnBtnSharescreen() 
{
	if( !m_dlgSSServer )
	{
		/// GetDesktopWindow()Ϊ���Ի���
		m_dlgSSServer.Create( IDD_SHARESCREEN_SERVER, GetDesktopWindow() );
		m_dlgSSServer.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		::SetForegroundWindow( m_dlgSSServer.m_hWnd );
		m_dlgSSServer.FlashWindow( TRUE );
	}
}

void CInstantMessagingDlg::OnSharescreen() 
{
	OnBtnSharescreen();
}

void CInstantMessagingDlg::OnBtnWhiteboard() 
{
	if( !m_dlgWhiteBoardServer )
	{
		/// GetDesktopWindow()Ϊ���Ի���
		m_dlgWhiteBoardServer.Create( IDD_WHITEBOARD_SERVER, GetDesktopWindow() );
		m_dlgWhiteBoardServer.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		::SetForegroundWindow( m_dlgWhiteBoardServer.m_hWnd );
		m_dlgWhiteBoardServer.FlashWindow( TRUE );
	}	
}

void CInstantMessagingDlg::OnWhiteboard() 
{
	OnBtnWhiteboard();
}

/// ������Ϣ����ʱ���պ���
void CInstantMessagingDlg::OnVideoChat( UINT nIndex )
{
	int nUserIndex = nIndex;
	USER userChat = m_arrFriends.GetAt( nIndex );
	
	/// �����Ƿ��Ѿ�����userChat����Ƶ���촰��
	for( nIndex = 0; nIndex < m_arrVideoChatDlg.GetSize(); nIndex++ )
	{
		/// �Ѿ��д򿪵Ĵ���
		if( 0 == strcmp( userChat.strIP, m_arrVideoChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			::SetForegroundWindow( m_arrVideoChatDlg.GetAt( nIndex )->m_hWnd );
			m_arrVideoChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
			return;
		}
	}
	
	/// �����´���
	CVideoChatDlg *pVideoChatDlg = new CVideoChatDlg( this );

	/// GetDesktopWindow()Ϊ���Ի���
	pVideoChatDlg->Create( IDD_VIDEOCHAT, GetDesktopWindow() );
	pVideoChatDlg->SetChatUser( userChat );
	pVideoChatDlg->ShowWindow( SW_SHOW );
	m_arrVideoChatDlg.Add( pVideoChatDlg );

	/// ����ѷ�����Ƶ��������
	USER userSelf;
	userSelf.bHasCamera = m_bCamera;
	userSelf.nFace		= m_wFace;
	memcpy( userSelf.strName, m_strNickName.GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
	m_strNickName.ReleaseBuffer( -1 );
	SendUserCommandToIP( VIDEOCHAT_VIDEO_ADDREQUEST, userChat.strIP, DEFAULT_PORT, &userSelf );

	/// �����Ƶ�������socketû�г�ʼ�������ʼ��
	if( !m_pVideoChatListenSocket )
	{
		m_pVideoChatListenSocket = new CVideoChatListenSocket( this );
		m_pVideoChatListenSocket->Create( VIDEOCHAT_PORT );
		m_pVideoChatListenSocket->Listen();
	}

	/// ���û����������Ƶ����������Ƶ
	if( !m_bConnectCamera )
	{
		if( capDriverConnect( m_hWndVideo, 0 ) )
		{
			/// ������Ƶ�Ĵ�С
			BITMAPINFO bmpInfo;
			capGetVideoFormat( m_hWndVideo, &bmpInfo, sizeof( BITMAPINFO ) );
			bmpInfo.bmiHeader.biWidth		= VIDEOCHAT_VIDEO_WIDTH;
			bmpInfo.bmiHeader.biHeight		= VIDEOCHAT_VIDEO_HEIGHT;
			bmpInfo.bmiHeader.biCompression	= 844715353;
			bmpInfo.bmiHeader.biBitCount	= 16;
			bmpInfo.bmiHeader.biSizeImage	= bmpInfo.bmiHeader.biWidth * bmpInfo.bmiHeader.biHeight * bmpInfo.bmiHeader.biBitCount / 8;
			capSetVideoFormat( m_hWndVideo, &bmpInfo, sizeof( BITMAPINFO ) );

			CAPDRIVERCAPS caps;
			capDriverGetCaps( m_hWndVideo, sizeof( caps ), &caps );
			
			if( caps.fHasOverlay )
			{
				capOverlay( m_hWndVideo, TRUE );
			}
			
			CAPTUREPARMS params;
			capCaptureGetSetup( m_hWndVideo, &params, sizeof( params ) );
			params.fYield			= TRUE;
			params.fAbortLeftMouse	= FALSE;
			params.fAbortRightMouse	= FALSE;
			params.fLimitEnabled	= FALSE;
			params.vKeyAbort		= FALSE;
			params.fCaptureAudio	= TRUE;
			capCaptureSetSetup( m_hWndVideo, &params, sizeof( params ) );
			
			capSetCallbackOnVideoStream( m_hWndVideo, EncodeCallback );
			capCaptureSequenceNoFile( m_hWndVideo );
			
			/// ��������Ƶ
			m_bConnectCamera = TRUE;
		}
	}

	/// ��ʼ��Ƶ
	waveInStart( m_hWaveIn );

	/// �õ�¼����ʱ��
	if( 0 == m_dwTickTime )
	{
		m_dwTickTime = ::GetTickCount();
	}
}	

LRESULT WINAPI EncodeCallback( HWND hWnd, LPVIDEOHDR lpVHdr )
{
	if( lpVHdr->dwFlags & VHDR_DONE )
	{
		static CInstantMessagingDlg *pDlgMain = ( CInstantMessagingDlg * ) AfxGetMainWnd();
		
		BITMAPINFO bmpInfo;
		capGetVideoFormat( pDlgMain->m_hWndVideo, &bmpInfo, sizeof( BITMAPINFO ) );
	
		bmpInfo.bmiHeader.biHeight			= -1 * bmpInfo.bmiHeader.biHeight;
		bmpInfo.bmiHeader.biClrImportant	= 0;
		bmpInfo.bmiHeader.biBitCount		= 24;
		bmpInfo.bmiHeader.biClrUsed			= 0;
		bmpInfo.bmiHeader.biCompression		= BI_RGB;
		bmpInfo.bmiHeader.biPlanes			= 1;
		bmpInfo.bmiHeader.biSizeImage		= -1 
			* bmpInfo.bmiHeader.biWidth 
			* bmpInfo.bmiHeader.biHeight 
			* bmpInfo.bmiHeader.biBitCount 
			/ 8;
		
		/// ͨ�����ԶԻ������������Ƶ����Ի�����
		pDlgMain->UpdateVideoPicture( ::GetTickCount(), bmpInfo, lpVHdr->lpData, lpVHdr->dwBufferLength );
	}
	return 1;
}

BYTE _clip255( LONG v )
{
	if( v < 0 ) 
	{
		v = 0;
	}
	else if( v > 255 ) 
	{
		v=255;
	}
	return ( BYTE )v;
}

void YUY2_RGB( BYTE *YUY2buff, BYTE *RGBbuff, DWORD dwSize )
{
	BYTE *orgRGBbuff = RGBbuff;
	for( DWORD count=0; count < dwSize; count+=4 )
	{
		//Y0 U0 Y1 V0
		BYTE Y0	= *YUY2buff;
		BYTE U	= *(++YUY2buff);
		BYTE Y1 = *(++YUY2buff);
		BYTE V	= *(++YUY2buff);
		++YUY2buff;
		
		LONG Y,C,D,E;
		BYTE R,G,B;
		
		Y = Y0;
		C = Y-16;
		D = U-128;
		E = V-128;
		R = _clip255(( 298 * C           + 409 * E + 128) >> 8);
		G = _clip255(( 298 * C - 100 * D - 208 * E + 128) >> 8);
		B = _clip255(( 298 * C + 516 * D           + 128) >> 8);
		
		*(RGBbuff)   = B;           
		*(++RGBbuff) = G;   
		*(++RGBbuff) = R;        
		
		Y = Y1;
		C = Y-16;
		D = U-128;
		E = V-128;
		R = _clip255(( 298 * C           + 409 * E + 128) >> 8);
		G = _clip255(( 298 * C - 100 * D - 208 * E + 128) >> 8);
		B = _clip255(( 298 * C + 516 * D           + 128) >> 8);
		*(++RGBbuff) = B;           
		*(++RGBbuff) = G;   
		*(++RGBbuff) = R;         
		++RGBbuff;	
	}
}

/// user�ܾ���Ƶ
void CInstantMessagingDlg::DenyAddToVideoChatRequest( const USER user )
{
	/// ���ҵ���ܾ������user�Ի���
	for( int nIndex = 0; nIndex < m_arrVideoChatDlg.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( user.strIP, m_arrVideoChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			::SetForegroundWindow( m_arrVideoChatDlg.GetAt( nIndex )->m_hWnd );
			m_arrVideoChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
			m_arrVideoChatDlg.GetAt( nIndex )->DenyVideoChat();
			return;
		}
	}
}

/// ���������Ƶ����
void CInstantMessagingDlg::AllowAddToVideoChatRequest( const USER user )
{
	/// ���ҵ������������user�Ի���
	for( int nIndex = 0; nIndex < m_arrVideoChatDlg.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( user.strIP, m_arrVideoChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			::SetForegroundWindow( m_arrVideoChatDlg.GetAt( nIndex )->m_hWnd );
			m_arrVideoChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
			m_arrVideoChatDlg.GetAt( nIndex )->SetConnect( TRUE );

			return;
		}
	}
}

/// �ر���Ƶ���촰��
void CInstantMessagingDlg::CloseVideoChatDlg( const USER user )
{
	/// ����Ƶ����Ի�����б�Ҫ�رյĶԻ���ɾ��
	for( int nIndex = 0; nIndex < m_arrVideoChatDlg.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( user.strIP, m_arrVideoChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			m_arrVideoChatDlg.RemoveAt( nIndex );
			break;
		}
	}

	/// ��Է����ͶϿ�����Ϣ
	SendUserCommandToIP( VIDEOCHAT_VIDEO_DISCONNECT, user.strIP, DEFAULT_PORT, NULL );

	/// ���û����Ƶ����Ի�����رշ��ͺͽ����̲߳��Ͽ�����Ƶ������
	if( m_arrVideoChatDlg.GetSize() == 0 )
	{
		/// ֹͣ��ȡ��Ƶ
		capSetCallbackOnVideoStream( m_hWndVideo, NULL );
		capCaptureAbort( m_hWndVideo );
		capCaptureStop( m_hWndVideo );

		capDriverDisconnect( m_hWndVideo);

		m_bConnectCamera = FALSE;

		/// ֹͣ¼��
		waveInReset( m_hWaveIn );
		m_dwTickTime = 0;

		/// �ر���Ƶ�������socket
		if( m_pVideoChatListenSocket )
		{
			m_pVideoChatListenSocket->Close();
			delete [] m_pVideoChatListenSocket;
			m_pVideoChatListenSocket = NULL;
		}
	}
}

/// user�Ͽ���Ƶ����
void CInstantMessagingDlg::UserDisconnectFromVideoChat( const USER user )
{
	/// ���ҵ���Ͽ������user�Ի���
	for( int nIndex = 0; nIndex < m_arrVideoChatDlg.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( user.strIP, m_arrVideoChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			::SetForegroundWindow( m_arrVideoChatDlg.GetAt( nIndex )->m_hWnd );
			m_arrVideoChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
			m_arrVideoChatDlg.GetAt( nIndex )->Disconnect();
			return;
		}
	}
}


void CInstantMessagingDlg::WaveInOpen( WPARAM wParam, LPARAM lParam )
{
	waveInAddBuffer( m_hWaveIn, m_pWaveHdr1, sizeof( WAVEHDR ) );
	waveInAddBuffer( m_hWaveIn, m_pWaveHdr2, sizeof( WAVEHDR ) );
	return;
}

void CInstantMessagingDlg::WaveInData( WPARAM wParam, LPARAM lParam )
{
	DWORD dwTickCount = m_dwTickTime;
		
	/// �õ�¼����ʱ��
	m_dwTickTime = ::GetTickCount();

	/// ÿ����Ƶ���ڷ�������
	int nVideoChatDlgIndex = 0;
	for( nVideoChatDlgIndex = 0; nVideoChatDlgIndex < m_arrVideoChatDlg.GetSize(); nVideoChatDlgIndex++ )
	{
		m_arrVideoChatDlg.GetAt( nVideoChatDlgIndex )->SendAudioData( dwTickCount,
																	( ( PWAVEHDR )lParam )->lpData, 
																	( ( PWAVEHDR )lParam )->dwBufferLength );
	}

	/// ����WAVEHDR����ӽ�¼���豸
	waveInAddBuffer( m_hWaveIn, ( PWAVEHDR )lParam, sizeof( WAVEHDR ) );
	return;	
}

void CInstantMessagingDlg::WaveInClose( WPARAM wParam, LPARAM lParam )
{
	waveInUnprepareHeader( m_hWaveIn, m_pWaveHdr1, sizeof( WAVEHDR ) );
	waveInUnprepareHeader( m_hWaveIn, m_pWaveHdr2, sizeof( WAVEHDR ) );
	return;
}

/// ��Ƶ����ʱ���»���
void CInstantMessagingDlg::UpdateVideoPicture( DWORD dwTickCount,
											  const BITMAPINFO bmpInfo, 
											  unsigned char *pData, 
											  DWORD dwBufferSize )
{
	int nVideoChatDlgIndex = 0;
	for( nVideoChatDlgIndex = 0; nVideoChatDlgIndex < m_arrVideoChatDlg.GetSize(); nVideoChatDlgIndex++ )
	{
		m_arrVideoChatDlg.GetAt( nVideoChatDlgIndex )->UpdateVideoPicture( dwTickCount,
																			bmpInfo, 
																			pData, 
																			dwBufferSize );
	}
}

/// ������Ƶ�����socket
void CInstantMessagingDlg::OnAcceptVideoChat()
{
	/// ������Ƶ����sokcet
	CVideoChatSocket videoChatSocket;
	m_pVideoChatListenSocket->Accept( videoChatSocket );
	
	/// �������ϵ�socket������Ƶ����Ի���
	CString strVideoChatIP;
	UINT uPort;
	videoChatSocket.GetPeerName( strVideoChatIP, uPort );
	int nVideoChatDlgIndex = 0;
	for( nVideoChatDlgIndex = 0; nVideoChatDlgIndex < m_arrVideoChatDlg.GetSize(); nVideoChatDlgIndex++ )
	{
		if( strVideoChatIP == m_arrVideoChatDlg.GetAt( nVideoChatDlgIndex )->GetChatIP() )
		{
			m_arrVideoChatDlg.GetAt( nVideoChatDlgIndex )->AttachClientSocket( videoChatSocket.Detach(),
				m_arrVideoChatDlg.GetAt( nVideoChatDlgIndex ) );
		}
	}
}