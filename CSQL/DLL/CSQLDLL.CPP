/////////////////////////////////////////////////////////////////////////////
// Initialization of MFC Extension DLL   
#include "stdincs.h" 
#include "csqlcur.h"
#include "csqlexep.h"
#include "csqldll.h"
#include "afxdllx.h"    	// standard MFC Extension DLL routines        

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;      
#endif

//static AFX_EXTENSION_MODULE NEAR extensionDLL = { NULL, &CSqlException::classCSqlException };  
static AFX_EXTENSION_MODULE NEAR extensionDLL = { NULL, NULL };  
					
extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR)
{
	// Extension DLL one-time initialization - do not allocate memory here,
	//   use the TRACE or ASSERT macros or call MessageBox  
	AfxInitExtensionModule(extensionDLL, hInstance); 
	return 1;   // ok   
}

// Exported DLL initialization is run in context of running application
extern "C" extern void AFX_EXPORT InitCSqlDll()
{
	// create a new CDynLinkLibrary for this app
	new CSqlDynLinkLibrary(extensionDLL); 
}

////////////////////////////////////////////////////////////////
//
//	CSqlDynLinkLibrary
//
CSqlDynLinkLibrary::CSqlDynLinkLibrary(AFX_EXTENSION_MODULE& state)
	:CDynLinkLibrary(state)
{
	// init SQLAPIW.DLL for the new calling app.
	SQLTAPI ret = ::sqlini((SQLTPFP)YieldProc);
#ifdef _DEBUG	
	if (ret)
		TRACE0("can't initialize SQL API interface\n");
	else
		TRACE0("SQL API interface initialized ok\n"); 		  
#endif
}

CSqlDynLinkLibrary::~CSqlDynLinkLibrary()
{
	// frees SQLAPIW.DLL resources for the dying app.   
	SQLTAPI ret = ::sqldon(); 

#ifdef _DEBUG	
	if (ret)
		TRACE0("can't free SQL API DLL resources\n");
	else
		TRACE0("SQL API interface resources freed ok\n"); 		  
#endif	 		  
}

//////////////////////////////////////////////////////////////////////////
//
//	Globals 
//
extern "C" void AFX_EXPORT csqlSeeWhatHappened(CSqlException* e)
{
	if (AfxMessageBox(e->errorMessage(), MB_OKCANCEL) == IDOK){
		if (AfxMessageBox(e->errorReason(), MB_OKCANCEL) == IDOK){
	    	AfxMessageBox(e->errorRemedy(), MB_OK);
	    	}
		}  
		
	if (e->IsKindOf(RUNTIME_CLASS(CSqlCsrException))){		
		// look at the 2nd cursor too if we have one.... 				    	
		if (((CSqlCsrException*)e)->toggleCursors()){
		
			if (AfxMessageBox(e->errorMessage(), MB_OKCANCEL) == IDOK){
				if (AfxMessageBox(e->errorReason(), MB_OKCANCEL) == IDOK){
			    	AfxMessageBox(e->errorRemedy(), MB_OK);
			    	}
				}
										    	
			((CSqlCsrException*)e)->toggleCursors(); // then put it back...
			}// if toggled ok..
			  
		}// if cursor-type exception			
}

extern "C" int AFX_EXPORT YieldProc()
{
	MSG msg;

  	while(::PeekMessage( &msg, NULL, 0, 0, TRUE ) ){
    	::TranslateMessage( &msg );
    	::DispatchMessage( &msg );
  	}
  	return 0;
}


