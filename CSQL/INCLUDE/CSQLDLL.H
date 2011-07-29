///////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqldll.h	: 	header for _AFXDLL version of SQLBase++        
//
//	Author		:	Aaron Cody
//	Date		:	2nd February 1994 
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:	For use with the _AFXDLL version of the library.  
//

#ifndef CSQLDLL_H   
	#define CSQLDLL_H   
	
#ifndef _AFXDLL
	#error ("please define _AFXDLL in your project makefile")
#endif	

extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR);
extern "C" extern void AFX_EXPORT InitCSqlDll(); 
extern "C" void AFX_EXPORT csqlSeeWhatHappened(CSqlException* e);
extern "C" int AFX_EXPORT YieldProc();

class CSqlDynLinkLibrary : public CDynLinkLibrary
{
public:
	CSqlDynLinkLibrary(AFX_EXTENSION_MODULE& state);	// calls ::sqlini()
	virtual ~CSqlDynLinkLibrary();						// calls ::sqldon()
};
	
#endif      
