// MyWaveDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MyCal.h"
#include "MyWaveDialog.h"

#include "MyTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWaveDialog dialog


CMyWaveDialog::CMyWaveDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyWaveDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyWaveDialog)
	m_strValue = _T("");
	//}}AFX_DATA_INIT
}


void CMyWaveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyWaveDialog)
	DDX_Text(pDX, IDC_EDIT_VALUE, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyWaveDialog, CDialog)
	//{{AFX_MSG_MAP(CMyWaveDialog)
	ON_BN_CLICKED(IDC_BUTTON_SIN, OnButtonSin)
	ON_BN_CLICKED(IDC_BUTTON_COS, OnButtonCos)
	ON_BN_CLICKED(IDC_RADIO_DEG, OnRadioDeg)
	ON_BN_CLICKED(IDC_RADIO_RAD, OnRadioRad)
	ON_BN_CLICKED(IDC_BUTTON_PLOT, OnButtonPlot)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, OnButton9)
	ON_EN_CHANGE(IDC_EDIT_VALUE, OnChangeEditValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWaveDialog message handlers

BOOL CMyWaveDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_RADIO_DEG))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_RAD))->SetCheck(FALSE);
	m_iUnit = 0;
	m_iTimer = 0;
	m_iPenMode = 0;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyWaveDialog::OnButtonSin() 
{
	// TODO: Add your control notification handler code here	
	CMyTool t;
	float l;
	l = (float)t.GetSinX(atoi(m_strValue))/10000;
	m_strValue.Empty();
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButtonCos() 
{
	// TODO: Add your control notification handler code here
	CMyTool t;
	float l;
	l = (float)t.GetCosX(atoi(m_strValue))/10000;
	m_strValue.Empty();
	UpdateData(FALSE);
}

void CMyWaveDialog::OnRadioDeg() 
{
	// TODO: Add your control notification handler code here
	m_iUnit = 0;
	
}

void CMyWaveDialog::OnRadioRad() 
{
	// TODO: Add your control notification handler code here
	m_iUnit = 1;
}

void CMyWaveDialog::OnButtonPlot() 
{
	// TODO: Add your control notification handler code here
	SetTimer(0,2000,NULL);
	SetTimer(1,50,NULL); 

	GetWindowRect(&m_rect);	
	CDC *pDC;
	pDC = GetDC();
	int  x,y;
	x= m_rect.right - m_rect.left;
	y = m_rect.bottom - m_rect.top;
 
	m_rect.left = 10;
	m_rect.top = 10;
	m_rect.bottom = y - 35;
	m_rect.right = 3*x/4 - 35;
	pDC->Rectangle(m_rect);

	m_iWidth = m_rect.right - m_rect.left - 40;
	m_iHigh = m_rect.bottom-m_rect.top -40;

	pDC->MoveTo(m_rect.left+10,(m_rect.bottom-m_rect.top)/2);
	pDC->LineTo(m_rect.right-10,(m_rect.bottom-m_rect.top)/2);
   
	int i;
	for(i=0;i<m_iWidth;i+=m_iWidth/4)
	{
		pDC->MoveTo(m_rect.left+20+i,(m_rect.bottom-m_rect.top)/2);
		pDC->LineTo(m_rect.left+20+i,(m_rect.bottom-m_rect.top)/2-10);
	pDC->TextOut(m_rect.left+10+m_iWidth/4,(m_rect.bottom-m_rect.top)/2+10,"1/2¦Ð");
		pDC->TextOut(m_rect.left+10+m_iWidth/2,(m_rect.bottom-m_rect.top)/2+10,"¦Ð");
		pDC->TextOut(m_rect.left+10+3*m_iWidth/4,(m_rect.bottom-m_rect.top)/2+10,"3/4¦Ð");
		pDC->TextOut(m_rect.left+10+m_iWidth,(m_rect.bottom-m_rect.top)/2+10,"2¦Ð");

	}

	pDC->MoveTo(m_rect.left+20,m_rect.top+10);
	pDC->LineTo(m_rect.left+20,m_rect.bottom-10);

	for(i=0;i<m_iHigh/2;i+=m_iHigh/4)
	{
		pDC->MoveTo(m_rect.left+20,(m_rect.bottom-m_rect.top)-i);
		pDC->LineTo(m_rect.left+30,(m_rect.bottom-m_rect.top)-i);
		pDC->MoveTo(m_rect.left+20,(m_rect.bottom-m_rect.top)/3-i);
		pDC->LineTo(m_rect.left+30,(m_rect.bottom-m_rect.top)/3-i);
	pDC->TextOut(m_rect.left+20,(m_rect.bottom-m_rect.top)/2-m_iHigh/2,"1");
		pDC->TextOut(m_rect.left+30,(m_rect.bottom-m_rect.top)/2-m_iHigh/4,"0.5");

		pDC->TextOut(m_rect.left+20,(m_rect.bottom-m_rect.top)/2+m_iHigh/2,"-1");
		pDC->TextOut(m_rect.left+30,(m_rect.bottom-m_rect.top)/2+m_iHigh/4,"-0.5");
	}

}

void CMyWaveDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(1==nIDEvent)
	{
		KillTimer(1);		
		CMyTool t;	
		CDC *pDC;
		CPen pen;
		pDC = GetDC();

		switch(m_iPenMode)
		{
			case 0:pen.CreatePen(PS_SOLID,0,RGB(0,0,255));break;
			case 1:pen.CreatePen(PS_SOLID,0,RGB(0,255,0));break; 
			case 2:pen.CreatePen(PS_SOLID,0,RGB(255,0,0));break;
		}
		pDC->SelectObject(&pen);
		m_iX1 = m_rect.left + 20 + m_iTimer*m_iWidth/48;
		m_iY1 = (m_rect.bottom-m_rect.top)/2 + t.GetSinX(m_iTimer*75/10)*m_iHigh/20000;
		
		if(m_iTimer==0)
		{
			m_iX0 = m_iX1;
			m_iY0 = m_iY1;
		}
		else
		{
			pDC->MoveTo(m_iX0,m_iY0);
			pDC->LineTo(m_iX1,m_iY1);
			m_iX0 = m_iX1;
			m_iY0 = m_iY1;
		}
		SetTimer(1,50,NULL);
		m_iTimer++;
		m_iTimer %= 49;
	}

	if(0==nIDEvent)
	{
		KillTimer(0);	
		m_iPenMode++; 
		m_iPenMode%= 3;		
		SetTimer(0,2000,NULL);	
	}

	CDialog::OnTimer(nIDEvent);
}

void CMyWaveDialog::OnButton0() 
{
	// TODO: Add your control notification handler code here

	m_strValue += "0";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "1";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "2";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "3";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "4";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "5";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "6";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "7";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "8";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
	m_strValue += "9";
	UpdateData(FALSE);
}

void CMyWaveDialog::OnChangeEditValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
