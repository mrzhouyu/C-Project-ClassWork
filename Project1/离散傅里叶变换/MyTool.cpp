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