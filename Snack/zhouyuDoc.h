// zhouyuDoc.h : interface of the CZhouyuDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZHOUYUDOC_H__F6777A0E_47F4_456D_8EC8_5A1EE4A798F9__INCLUDED_)
#define AFX_ZHOUYUDOC_H__F6777A0E_47F4_456D_8EC8_5A1EE4A798F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CZhouyuDoc : public CDocument
{
protected: // create from serialization only
	CZhouyuDoc();
	DECLARE_DYNCREATE(CZhouyuDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZhouyuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CZhouyuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CZhouyuDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZHOUYUDOC_H__F6777A0E_47F4_456D_8EC8_5A1EE4A798F9__INCLUDED_)
