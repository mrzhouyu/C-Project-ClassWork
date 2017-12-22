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

int CMyTool::GetCosX(int iData)
{


		int i;
	iData %= 180;
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
