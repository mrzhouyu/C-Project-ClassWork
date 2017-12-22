// MyCalDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MyCal.h"
#include "MyCalDialog.h"
#include "MyTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define DOT 9

#define AND 5
#define OR	6
#define XOR 7


/////////////////////////////////////////////////////////////////////////////
// CMyCalDialog dialog


CMyCalDialog::CMyCalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCalDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyCalDialog)	
	m_strValue = "";	
	//}}AFX_DATA_INIT

}


void CMyCalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCalDialog)
	DDX_Text(pDX, IDC_EDIT_VALUE, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyCalDialog, CDialog)
	//{{AFX_MSG_MAP(CMyCalDialog)
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON_A, OnButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, OnButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, OnButtonC)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, OnButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, OnButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, OnButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_AC, OnButtonAc)
	ON_BN_CLICKED(IDC_BUTTON_BK, OnButtonBk)
	ON_BN_CLICKED(IDC_RADIO_HEX, OnRadioHex)
	ON_BN_CLICKED(IDC_RADIO_DEC, OnRadioDec)
	ON_BN_CLICKED(IDC_RADIO_BIN, OnRadioBin)
	ON_BN_CLICKED(IDC_RADIO_OCT, OnRadioOct)
	ON_BN_CLICKED(IDC_BUTTON_0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, OnButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_AND, OnButtonAnd)
	ON_BN_CLICKED(IDC_BUTTON_OR, OnButtonOr)
	ON_BN_CLICKED(IDC_BUTTON_XOR, OnButtonXor)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTOND, OnButtond)
	ON_BN_CLICKED(IDC_BUTTONE, OnButtone)
	ON_BN_CLICKED(IDC_BUTTONF, OnButtonf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCalDialog message handlers
CString  CMyCalDialog::LogicOperate(int iData1,int iData2,int iCalMode)
{
	CString str1,str2,str;
	CMyTool t;
	int i,j,k,l;
	str  = "";
	str1 = "";
	str2 = "";
	str1 = t.Dec2Str(BIN,iData1);
	str2 = t.Dec2Str(BIN,iData2);
	i = str1.GetLength();
	j = str2.GetLength();

	l = i;
	if(i>j)
	{
		for(k=0;k<i-j;k++)
		{
			str += "0";
		}
		str += str2;
		str2  = str;
	}
	else if(i<j)
	{
		for(k=0;k<j-i;k++)
		{
			str += "0";
		}
		str += str1;
		str1  = str;
		l = j;
	}
	
	str = "";
	switch(iCalMode)
	{
		case AND:for(k=0;k<l;k++)
				 {
					 if(str1.GetAt(k)=='0'||str2.GetAt(k)=='0') str +="0";
					 else str +="1";
				 }
				break;
		case OR:
				for(k=0;k<l;k++)
				 {
					 if(str1.GetAt(k)=='0'&&str2.GetAt(k)=='0') str +="0";
					 else str +="1";
				 }
				break;
		case XOR:
				for(k=0;k<l;k++)
				 {
					 if(str1.GetAt(k)==str2.GetAt(k)) str +="0";
					 else str +="1";
				 }
				break;
	}
	return str;    
}



void CMyCalDialog::OnButton0() 
{
	// TODO: Add your control notification handler code here
	if(m_strValue.GetLength()==1&&m_strValue.GetAt(0)=='0') return;
	*pstrData += "0";
	m_strValue += "0";
	UpdateData(FALSE);
}


void CMyCalDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
	*pstrData += "1";
	m_strValue += "1";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "2";
	m_strValue += "2";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
		*pstrData += "3";
	m_strValue += "3";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "4";
	m_strValue += "4";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "5";
	m_strValue += "5";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "6";
	m_strValue += "6";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "7";
	m_strValue += "7";
	UpdateData(FALSE);	
}

void CMyCalDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "8";
	m_strValue += "8";
	UpdateData(FALSE);	
}

void CMyCalDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "9";
	m_strValue += "9";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonA() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "A";
	m_strValue += "A";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonB() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "B";
	m_strValue += "B";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonC() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "C";
	m_strValue += "C";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtond() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "D";
	m_strValue += "D";
	UpdateData(FALSE);	
}

void CMyCalDialog::OnButtone() 
{
	// TODO: Add your control notification handler code here
    *pstrData += "E";
	m_strValue += "E";
	UpdateData(FALSE);	
}

void CMyCalDialog::OnButtonf() 
{
	// TODO: Add your control notification handler code here
	*pstrData += "F";
	m_strValue += "F";
	UpdateData(FALSE);
}


void CMyCalDialog::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	m_iCalMode = ADD;
	pstrData = &m_strData[1];
	m_strValue  = "";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonSub() 
{
	// TODO: Add your control notification handler code here
	m_iCalMode = SUB;
	pstrData = &m_strData[1];
	m_strValue  = "";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonMul() 
{
	// TODO: Add your control notification handler code here
	m_iCalMode = MUL;
	pstrData = &m_strData[1];
		m_strValue  = "";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonDiv() 
{
	// TODO: Add your control notification handler code here
	m_iCalMode = DIV;
	pstrData = &m_strData[1];
	m_strValue  = "";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonAc() 
{
	// TODO: Add your control notification handler code here
	m_strData[0] = "";
	m_strData[1] = "";
	pstrData = &m_strData[0];
	m_strValue  = "";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonBk() 
{
	// TODO: Add your control notification handler code here
	if(pstrData->GetLength==0) return;
	pstrData->Delete(pstrData->GetLength()-1,1);
	m_strValue.Delete(m_strValue.GetLength()-1,1);
	UpdateData(FALSE);
}

void CMyCalDialog::OnRadioHex() 
{
	// TODO: Add your control notification handler code here
	m_iSystem = HEX;
    GetDlgItem(IDC_BUTTON_0)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_1)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_2)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_3)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_4)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_5)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_6)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE); 
	//to do ........
	GetDlgItem(IDC_BUTTON_A)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_B)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_C)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTOND)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTONE)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTONF)->EnableWindow(TRUE); 
	//to do .......
}

void CMyCalDialog::OnRadioDec() 
{
	// TODO: Add your control notification handler code here
	m_iSystem = DEC;
	GetDlgItem(IDC_BUTTON_0)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_1)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_2)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_3)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_4)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_5)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE); 
	//to do........
	GetDlgItem(IDC_BUTTON_A)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_B)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_C)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTOND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTONE)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTONF)->EnableWindow(FALSE);
	//to do ......
}

void CMyCalDialog::OnRadioBin() 
{
	// TODO: Add your control notification handler code here
	m_iSystem = BIN;
	GetDlgItem(IDC_BUTTON_1)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_0)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_2)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_3)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_4)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_5)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_6)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE); 
	//to do........
	GetDlgItem(IDC_BUTTON_A)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_B)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_C)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTOND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTONE)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTONF)->EnableWindow(FALSE); 
	//to do ......
}

void CMyCalDialog::OnRadioOct() 
{
	// TODO: Add your control notification handler code here
	m_iSystem = OCT;
	GetDlgItem(IDC_BUTTON_0)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_1)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_2)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_3)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_4)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_5)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_6)->EnableWindow(TRUE); 
	//to do........
	//	GetDlgItem(IDC_BUTTON_7)->EnableWindow(TRUE); 
	//	GetDlgItem(IDC_BUTTON_8)->EnableWindow(TRUE); 
	//  GetDlgItem(IDC_BUTTON_9)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_A)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_B)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_C)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTOND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTONE)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTONF)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE); 
	//to do ......
}



void CMyCalDialog::OnButtonEqual() 
{
	// TODO: Add your control notification handler code here
	CMyTool t;
	CString str;
	int i,j;
	switch(m_iSystem)
	{
		case HEX:i = t.Str2Dec(HEX,m_strData[0]);j = t.Str2Dec(HEX,m_strData[1]);break;
		case DEC:i = t.Str2Dec(DEC,m_strData[0]);j = t.Str2Dec(DEC,m_strData[1]);break;
		case OCT:i = t.Str2Dec(OCT,m_strData[0]);j = t.Str2Dec(OCT,m_strData[1]);break;
		case BIN:i = t.Str2Dec(BIN,m_strData[0]);j = t.Str2Dec(BIN,m_strData[1]);break;
	}
	str.Empty();
	switch(m_iCalMode)
	{
		case ADD:i += j;break;
		case SUB:i -= j;break;
		case MUL:i *= j;break;
		case DIV:i /= j;break;
		case AND:str = LogicOperate(i,j,AND);i=t.Str2Dec(BIN,str);break;
		case OR:str = LogicOperate(i,j,OR);i=t.Str2Dec(BIN,str);break;
		case XOR:str = LogicOperate(i,j,XOR);i=t.Str2Dec(BIN,str);break;
	}
	m_strValue  = "";
	m_strValue = t.Dec2Str(m_iSystem,i);	
	UpdateData(FALSE);

	m_strData[0] = "";
	m_strData[1] = "";
	pstrData = &m_strData[0];
	m_strValue  = "";
}

void CMyCalDialog::OnButtonAnd() 
{
	// TODO: Add your control notification handler code here
	m_iCalMode = AND;
	pstrData = &m_strData[1];
	m_strValue  = "";
	UpdateData(FALSE);
}

void CMyCalDialog::OnButtonOr() 
{
	// TODO: Add your control notification handler code here
	m_iCalMode = OR;
	pstrData = &m_strData[1];
	m_strValue  = "";
	UpdateData(FALSE);
}



void CMyCalDialog::OnButtonXor() 
{
	// TODO: Add your control notification handler code here
	m_iCalMode = XOR;
	pstrData = &m_strData[1];
	m_strValue  = "";
	UpdateData(FALSE);
}

BOOL CMyCalDialog::OnInitDialog()   //重载该函数，实现初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_RADIO_DEC))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_HEX))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_OCT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_BIN))->SetCheck(FALSE);
	GetDlgItem(IDC_BUTTON_A)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_B)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_C)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTOND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONF)->EnableWindow(FALSE);
	m_strData[0] = "";
	m_strData[1] = "";
	m_iCalMode = 0;
	m_iSystem = DEC;
	pstrData = m_strData;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}






