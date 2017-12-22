// MyCalView.cpp : implementation of the CMyCalView class
//

#include "stdafx.h"
#include "MyCal.h"

#include "MyCalDoc.h"
#include "MyCalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCalView

IMPLEMENT_DYNCREATE(CMyCalView, CView)

BEGIN_MESSAGE_MAP(CMyCalView, CView)
	//{{AFX_MSG_MAP(CMyCalView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCalView construction/destruction

CMyCalView::CMyCalView()
{
	// TODO: add construction code here

}

CMyCalView::~CMyCalView()
{
}

BOOL CMyCalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyCalView drawing

void CMyCalView::OnDraw(CDC* pDC)
{
	CMyCalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->TextOut(10,10,"显示班级学号姓名");
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyCalView printing

BOOL CMyCalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyCalView diagnostics

#ifdef _DEBUG
void CMyCalView::AssertValid() const
{
	CView::AssertValid();
}

void CMyCalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCalDoc* CMyCalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCalDoc)));
	return (CMyCalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCalView message handlers
