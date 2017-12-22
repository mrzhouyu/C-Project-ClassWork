// MyTool.h: interface for the CMyTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTOOL_H__2CAD834A_DC50_41E7_A6A2_41C9E358C3F7__INCLUDED_)
#define AFX_MYTOOL_H__2CAD834A_DC50_41E7_A6A2_41C9E358C3F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyTool  
{
public:
	int Str2Dec(int iSystem,CString str);
	CString Dec2Str(int iSystem,int iData);

	double GetDFTnR(int iDFTn,int iTn,double* pData);
	double GetDFTnX(int iDFTn,int iTn,double* pData);
	double GetAmplitu(double dData1,double dData2);
	int GetCosX(int iData);	
	int GetSinX(int iData);	


//	CString m_str;
//	int m_iData;
	CMyTool();
	virtual ~CMyTool();
};

#endif // !defined(AFX_MYTOOL_H__2CAD834A_DC50_41E7_A6A2_41C9E358C3F7__INCLUDED_)
