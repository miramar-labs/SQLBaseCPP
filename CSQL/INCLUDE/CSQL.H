///////////////////////////////////////////////////////////////////////
//
//	csql.h	: 	General header for SQLBase++ class library
//
//	Author	:	Aaron Cody
//	Date	:	28th January 1994    
//	Version:	SQLBase++ v1.2	       
//	Remarks	:   Library now comes in two forms : static & DLL		
//
#ifndef CSQL_H
	#define CSQL_H 

#ifdef RC_INVOKED  
// resource compiler active....
// just the standard MFC & Windows include file
#include <afxwin.h> 	// checks if RC.EXE is running....

#else 
// resource compiler not active....
// standard includes plus our additional stuff...
//#include <afx.h>		// DON'T INCLUDE AFXWIN.H HERE !
#include <afxwin.h>
#include <afxext.h>     // MFC extensions (including VB)
#include <afxcoll.h>    // MFC collection classes
#include <stdlib.h> 	// C Run-time lib
#include <direct.h>     // C Run-time lib

// 'sql.h' generates a lot of these annoying warnings.
#pragma warning(disable:4040)

extern "C" {           	// SQLBase C/API headers..
#include <sql.h> 
#include <sqlsrv.h>
}     

#include "csqlcur.h"    
#include "csqlexep.h"
#include "csqlsrvr.h"

#include "csqltype.h"
	#include "csqlnum.h"
	#include "csqllvc.h"
	#include "csqlstr.h"
	#include "csqldtm.h"
	#include "csqlidat.h"
	#include "csqlinum.h"    

#include "csqlrow.h"
#include "csqlcmd.h"    
#include "csqlsel.h"

// SQLBase++ class headers..
#ifndef _AFXDLL
	// static library 
	#include "csqlwapp.h"
#else                
	// MFC Extension DLL
	#include "csqldll.h"
#endif		

#endif	// RC_INVOKED

#endif	// CSQL_H

