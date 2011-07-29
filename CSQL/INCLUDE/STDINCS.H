//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994 
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:	  
//

#ifndef STDINCS_H
	#define STDINCS_H
// in case MFC not already included...	
#include <afxwin.h>         // MFC
#include <afxext.h>         // MFC extensions (including VB)
#include <afxcoll.h>

#include <stdlib.h> 	// C Run-time libs
#include <direct.h>

// 'sql.h' generates a lot of these annoying warnings.
#pragma warning(disable:4040)

extern "C" {
#include <sql.h> 
#include <sqlsrv.h>
#include "windowsx.h"
}       

#endif
                    