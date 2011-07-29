#include <csql.h>	
#include "csqlscmd.h"	
#include "csqlssel.h"

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlSmartSelect     

CSqlSmartSelect::CSqlSmartSelect(CSqlCursor& rCur, const char* szCmd) 
	:CSqlSelect(rCur, szCmd), CSqlCommand(rCur, szCmd)
{                                                       
	if (!rCur.isConnected())
		rCur.connect();
	if (strlen(szCmd) != 0){
		compile();
		if (m_nBindsNeeded == 0)
			execute();     
		}
}
                              
CSqlSmartSelect::CSqlSmartSelect(CSqlCursor& rCur, const UINT nId)
	:CSqlSelect(rCur, nId), CSqlCommand(rCur, nId)
{             
	if (!rCur.isConnected())
		rCur.connect();
	compile();
	if (m_nBindsNeeded == 0)
		execute();     
}


  
