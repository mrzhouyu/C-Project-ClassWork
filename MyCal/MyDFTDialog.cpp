// MyDFTDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MyCal.h"
#include "MyDFTDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "MyTool.h"

/////////////////////////////////////////////////////////////////////////////
// CMyDFTDialog dialog


CMyDFTDialog::CMyDFTDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDFTDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDFTDialog)
	m_strValue = _T("");
	//}}AFX_DATA_INIT
}


void CMyDFTDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDFTDialog)
	DDX_Text(pDX, IDC_DATA_INPUT, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDFTDialog, CDialog)
	//{{AFX_MSG_MAP(CMyDFTDialog)
	ON_BN_CLICKED(IDC_BUTTON_DFT, OnButtonDft)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDFTDialog message handlers

void CMyDFTDialog::OnButtonDft() 
{
	// TODO: Add your control notification handler code here
	int i,j;
	CString str;
	double ddata[50];
	str.Empty();
	PoltSpectrum();
	if(m_strValue.GetLength()==0) return;
	i = 0;
	j = 0;
	for(;;)
	{
		switch(m_strValue.GetAt(i))
		{
			case '0': str += "0";break;
			case '1': str += "1";break;
			case '2': str += "2";break;
			case '3': str += "3";break;
			case '4': str += "4";break;
			case '5': str += "5";break;
			case '6': str += "6";break;
			case '7': str += "7";break;
			case '8': str += "8";break;
			case '9': str += "9";break;
			case '.': str += ".";break;
			case ' ': if(str.GetLength!=0) ddata[j] = atof(str);j++;str.Empty();break;
			default:m_strValue="input error";UpdateData(FALSE);return;
		}
		i++;
		if(i==m_strValue.GetLength()) break;
	}
	m_iDftn = j;
	
}

void CMyDFTDialog::PoltSpectrum(void)
{
	GetWindowRect(&m_rect);	
	CDC *pDC;
	pDC = GetDC();

	int  x,y;
	x= m_rect.right - m_rect.left;
	y = m_rect.bottom - m_rect.top;

	m_rect.left = 10;
	m_rect.top = 100;
	m_rect.bottom = y - 35;
	m_rect.right = 3*x/4 - 35;
	pDC->Rectangle(m_rect);

	m_iWidth = m_rect.right - m_rect.left - 40;
	m_iHigh = m_rect.bottom-m_rect.top -40;

	pDC->MoveTo(m_rect.left+10,m_rect.bottom-20);
	pDC->LineTo(m_rect.right-10,m_rect.bottom-20);	

	pDC->MoveTo(m_rect.left+20,m_rect.top+10);
	pDC->LineTo(m_rect.left+20,m_rect.bottom-10);
	
}
