// zhouyuView.h : interface of the CZhouyuView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZHOUYUVIEW_H__A1578BD0_24E1_4B2F_84FF_DE7788DF05EA__INCLUDED_)
#define AFX_ZHOUYUVIEW_H__A1578BD0_24E1_4B2F_84FF_DE7788DF05EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CZhouyuView : public CView
{
protected: // create from serialization only
	CZhouyuView();
	DECLARE_DYNCREATE(CZhouyuView)

// Attributes
public:
	CZhouyuDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZhouyuView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void oninit();
	virtual ~CZhouyuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CZhouyuView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnStart();
	afx_msg void OnPause();
	afx_msg void OnContinue();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in zhouyuView.cpp
inline CZhouyuDoc* CZhouyuView::GetDocument()
   { return (CZhouyuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZHOUYUVIEW_H__A1578BD0_24E1_4B2F_84FF_DE7788DF05EA__INCLUDED_)
