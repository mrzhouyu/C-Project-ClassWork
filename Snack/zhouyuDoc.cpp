// zhouyuDoc.cpp : implementation of the CZhouyuDoc class
//

#include "stdafx.h"
#include "zhouyu.h"

#include "zhouyuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZhouyuDoc

IMPLEMENT_DYNCREATE(CZhouyuDoc, CDocument)

BEGIN_MESSAGE_MAP(CZhouyuDoc, CDocument)
	//{{AFX_MSG_MAP(CZhouyuDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZhouyuDoc construction/destruction

CZhouyuDoc::CZhouyuDoc()
{
	// TODO: add one-time construction code here

}

CZhouyuDoc::~CZhouyuDoc()
{
}

BOOL CZhouyuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CZhouyuDoc serialization

void CZhouyuDoc::Serialize(CArchive& ar)
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
// CZhouyuDoc diagnostics

#ifdef _DEBUG
void CZhouyuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CZhouyuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZhouyuDoc commands
