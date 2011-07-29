///////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlwapp.h	: 	header for class CSqlWinApp        
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994 
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:	NOT for use with the _AFXDLL version of the library.  
//

#ifndef CSQLWAPP_H
	#define CSQLWAPP_H

#ifdef _AFXDLL
	#error("Do NOT use CSqlWinApp if you are using _AFXDLL")
#endif
	
class CSqlWinApp : public CWinApp 
{
public:
	// construction/destruction
			CSqlWinApp();
	virtual	~CSqlWinApp();
	
private:
	SQLTPFP	m_pfCallback;
};

// GLOBALS			
// a utility for examining exceptions thrown in this app...
void csqlSeeWhatHappened(CSqlException* e);

int __export FAR PASCAL YieldProc();

#endif	
