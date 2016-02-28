// vcardDoc.h : interface of the CVcardDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VCARDDOC_H__7B8A01D9_D69E_4019_9E77_FF260563FB72__INCLUDED_)
#define AFX_VCARDDOC_H__7B8A01D9_D69E_4019_9E77_FF260563FB72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVcardDoc : public CDocument
{
protected: // create from serialization only
	CVcardDoc();
	DECLARE_DYNCREATE(CVcardDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVcardDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString file_path;
	virtual ~CVcardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVcardDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCARDDOC_H__7B8A01D9_D69E_4019_9E77_FF260563FB72__INCLUDED_)
