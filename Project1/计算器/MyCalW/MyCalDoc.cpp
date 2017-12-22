// MyCalDoc.cpp : implementation of the CMyCalDoc class
//

#include "stdafx.h"
#include "MyCal.h"

#include "MyCalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCalDoc

IMPLEMENT_DYNCREATE(CMyCalDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyCalDoc, CDocument)
	//{{AFX_MSG_MAP(CMyCalDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCalDoc construction/destruction

CMyCalDoc::CMyCalDoc()
{
	// TODO: add one-time construction code here

}

CMyCalDoc::~CMyCalDoc()
{
}

BOOL CMyCalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyCalDoc serialization

void CMyCalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyCalDoc diagnostics

#ifdef _DEBUG
void CMyCalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCalDoc commands
