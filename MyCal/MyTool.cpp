// MyTool.cpp: implementation of the CMyTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCal.h"
#include "MyTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "math.h"

int c_iTableCosA15[24]  = {10000,9659,8660,7071,5000,2588,0,-2588,-5000,-7071,-8660,-9659,
 		-10000,-9659,-8660,-7071,-5000,-2588,0,2588,5000,7071,8660,9659};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyTool::CMyTool()
{

}

CMyTool::~CMyTool()
{

}

int CMyTool::Str2Dec(int iSystem,CString str)
{
	int i,j,l;
	int k,m;
	i = str.GetLength();
	if(i==0) return 0;
	
	k = 0;
	if(iSystem==16)
	{	
		for(j=0;j<i;j++)
		{
			switch(str.GetAt(j))
			{
				case 'A': m = 10;break;
				case 'B': m = 11;break;
				case 'C': m = 12;break;
				case 'D': m = 13;break;
				case 'E': m = 14;break;
				case 'F': m = 15;break;
				default: m = str.GetAt(0) - 0x30;
			}
			
			for(l=0;l<i-j-1;l++)
			{
				 m *= iSystem; 
			}
			k += m;			
		}		
	}
	else 
	{		
		for(j=0;j<i;j++)
		{
			m = str.GetAt(j) - 0x30;
			for(l=0;l<i-j-1;l++)
			{
				 m *= iSystem; 
			}
			k += m; 			
		}
	}
	return k;	
}

CString CMyTool:: Dec2Str(int iSystem,int iData)
{
	CString str;
	int i;
	str = "";
	i= 0;
	while(1)
	{	
		switch(iData%iSystem)
		{
			case 0: str += "0";break;
			case 1: str += "1";break;
			case 2: str += "2";break;
			case 3: str += "3";break;
			case 4: str += "4";break;
			case 5: str += "5";break;
			case 6: str += "6";break;
			case 7: str += "7";break;
			case 8: str += "8";break;
			case 9: str += "9";break;
			case 10: str += "A";break;
			case 11: str += "B";break;
			case 12: str += "C";break;
			case 13: str += "D";break;
			case 14: str += "E";break;
			case 15: str += "F";break;
		}
		if(iData<iSystem) break;
		iData /= iSystem;		
	}	
	str.MakeReverse();
	return str;
}

int CMyTool::GetCosX(int iData)
{

	int i;
	iData %= 360;
	i = (iData/15)%24; //360度分24点
		
	return c_iTableCosA15[i] + (c_iTableCosA15[(i+1)%24]-c_iTableCosA15[i%24])*(iData-i*15)/15;
}

int CMyTool::GetSinX(int iData)
{
	iData += 90;		
		int i;
	iData %= 360;
	i = (iData/15)%24; //360度分24点
		
	return c_iTableCosA15[i] + (c_iTableCosA15[(i+1)%24]-c_iTableCosA15[i%24])*(iData-i*15)/15;
}

double CMyTool::GetDFTnR(int iDFTn,int iTn,double* pData)
{
	int i;
	double dl;
	if(iDFTn<1||iTn>iDFTn) return 0;
	dl = 0;
	for(i=0;i<iDFTn;i++)
	{
		dl += pData[i]*cos(i*360*iTn/iDFTn);
	}
	return dl/iDFTn;
}

double CMyTool::GetDFTnX(int iDFTn,int iTn,double* pData)
{
	int i;
	double dl;
	if(iDFTn<1||iTn>iDFTn) return 0;
	dl = 0;
	for(i=0;i<iDFTn;i++)
	{
		dl += pData[i]*sin(i*360*iTn/iDFTn);
	}
	return dl/iDFTn;
}

double CMyTool:: GetAmplitu(double dData1,double dData2)
{
	return sqrt(dData1*dData1+dData2*dData2);
}