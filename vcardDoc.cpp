// vcardDoc.cpp : implementation of the CVcardDoc class
//

#include "stdafx.h"
#include "vcard.h"

#include "vcardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVcardDoc

IMPLEMENT_DYNCREATE(CVcardDoc, CDocument)

BEGIN_MESSAGE_MAP(CVcardDoc, CDocument)
	//{{AFX_MSG_MAP(CVcardDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVcardDoc construction/destruction

CVcardDoc::CVcardDoc()
{
	// TODO: add one-time construction code here
    file_path = "";
}

CVcardDoc::~CVcardDoc()
{
}

BOOL CVcardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
  
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVcardDoc serialization

void CVcardDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CVcardDoc diagnostics

#ifdef _DEBUG
void CVcardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVcardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVcardDoc commands

BOOL CVcardDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	file_path = lpszPathName;  //获取文件名
	return TRUE;
}
