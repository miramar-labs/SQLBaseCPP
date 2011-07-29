#include "stdincs.h" 
#include "csqlcur.h"
#include "csqlexep.h"
#include "csqlwapp.h"


//	Derive your SQL apps. from this class..

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlWinApp

CSqlWinApp::CSqlWinApp()
	:m_pfCallback(YieldProc)
{                            
	SQLTAPI ret = ::sqlini((SQLTPFP)m_pfCallback);
	
#ifdef _DEBUG	
	if (ret)
		TRACE0("can't initialize SQL API interface\n");
	else
		TRACE0("SQL API interface initialized ok\n"); 		  
#endif	 		  
}

CSqlWinApp::~CSqlWinApp()
{
	SQLTAPI ret = ::sqldon(); 
	
#ifdef _DEBUG	
	if (ret)
		TRACE0("can't free SQL API DLL resources\n");
	else
		TRACE0("SQL API interface resources freed ok\n"); 		  
#endif	 		  
	 		  
}


/////////////////////////////////////////////////////////////////////////////////////
// global utility..
void csqlSeeWhatHappened(CSqlException* e)
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

////////////////////////////////////////////////////////////
//
//	Yield Procedure..

int __export FAR PASCAL YieldProc()
{
	MSG msg;

  	while(::PeekMessage( &msg, NULL, 0, 0, TRUE ) ){
    	::TranslateMessage( &msg );
    	::DispatchMessage( &msg );
  	}
  	return 0;
}
