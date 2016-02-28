// vcard.h : main header file for the VCARD application
//

#if !defined(AFX_VCARD_H__CE353924_3C66_4946_A097_347D03C272FA__INCLUDED_)
#define AFX_VCARD_H__CE353924_3C66_4946_A097_347D03C272FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVcardApp:
// See vcard.cpp for the implementation of this class
//

class CVcardApp : public CWinApp
{
public:
	CVcardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVcardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVcardApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCARD_H__CE353924_3C66_4946_A097_347D03C272FA__INCLUDED_)
