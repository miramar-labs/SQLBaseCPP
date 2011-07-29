// csqlex.h : main header file for the CSQLEX application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCsqlexApp:
// See csqlex.cpp for the implementation of this class
//

//class CCsqlexApp : public CWinApp
class CCsqlexApp : public CSqlWinApp
{
public:
	CCsqlexApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CCsqlexApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
