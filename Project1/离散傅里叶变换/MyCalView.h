// MyCalView.h : interface of the CMyCalView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCALVIEW_H__F15EAE7D_D82E_4E11_84AA_63AFA50A46A0__INCLUDED_)
#define AFX_MYCALVIEW_H__F15EAE7D_D82E_4E11_84AA_63AFA50A46A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyCalView : public CView
{
protected: // create from serialization only
	CMyCalView();
	DECLARE_DYNCREATE(CMyCalView)

// Attributes
public:
	CMyCalDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCalView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyCalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCalView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyCalView.cpp
inline CMyCalDoc* CMyCalView::GetDocument()
   { return (CMyCalDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCALVIEW_H__F15EAE7D_D82E_4E11_84AA_63AFA50A46A0__INCLUDED_)
