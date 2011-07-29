#include <csql.h>	
#include "csqlscmd.h"	

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlSmartCommand     

CSqlSmartCommand::CSqlSmartCommand(CSqlCursor& rCur, const char* szCmd) 
	:CSqlCommand(rCur, szCmd)
{             
	if (!rCur.isConnected())
		rCur.connect();
	if (strlen(szCmd) != 0){
		compile();
		if (m_nBindsNeeded == 0)
			execute();     
		}
}
CSqlSmartCommand::CSqlSmartCommand(CSqlCursor& rCur, const UINT nId)
	:CSqlCommand(rCur, nId)
{             
	if (!rCur.isConnected())
		rCur.connect();
	compile();
	if (m_nBindsNeeded == 0)
		execute();     
}

void CSqlSmartCommand::associateWith(const char* szNewCmd)
{  
	CSqlCommand::associateWith(szNewCmd);
	compile();
	if (m_nBindsNeeded == 0)
		execute();             
	else
		m_bBound = m_bExecuted = FALSE;
}

void CSqlSmartCommand::associateWith(const UINT nId)
{
	CSqlCommand::associateWith(nId);
	compile();
	if (m_nBindsNeeded == 0)
		execute();             
	else
		m_bBound = m_bExecuted = FALSE;
}

void CSqlSmartCommand::associateWith(CSqlCursor& rNewCursor)
{
	CSqlCommand::associateWith(rNewCursor);
	compile();
	if (m_nBindsNeeded == 0)
		execute();             
	else
		m_bBound = m_bExecuted = FALSE;
}

CSqlSmartCommand& CSqlSmartCommand::operator<<(const CSqlString &rData)
{   
	ASSERT(m_nBindsNeeded);
	CSqlCommand::operator<<(rData); 
	
	if (numBinds() == m_nBindsNeeded){   
	    bind();
	    execute();  
	    deleteAllBinds();   
	    m_bExecuted = TRUE;
	    return *this;
		}                            
		
	return *this;
}

CSqlSmartCommand& CSqlSmartCommand::operator<<(const CSqlNumber &rData)
{   
	ASSERT(m_nBindsNeeded);
	
	CSqlCommand::operator<<(rData); 
	
	if (numBinds() == m_nBindsNeeded){   
	    bind();
	    execute();  
	    deleteAllBinds();
	    m_bExecuted = TRUE;
	    return *this;
		}                            
		
	return *this;
} 

CSqlSmartCommand& CSqlSmartCommand::operator<<(const CSqlDateTime &rData)
{   
	ASSERT(m_nBindsNeeded);
	
	CSqlCommand::operator<<(rData); 
	
	if (numBinds() == m_nBindsNeeded){   
	    bind();
	    execute();  
	    deleteAllBinds();
	    m_bExecuted = TRUE;
	    return *this;
		}                            
		
	return *this;
} 

CSqlSmartCommand& CSqlSmartCommand::operator<<(const CSqlLongVarChar &rData)
{   
	ASSERT(m_nBindsNeeded);
	
	CSqlCommand::operator<<(rData); 
	
	if (numBinds() == m_nBindsNeeded){   
	    bind();
	    execute();  
	    deleteAllBinds();
	    m_bExecuted = TRUE;
	    return *this;
		}                            
		
	return *this;
}

CSqlSmartCommand& CSqlSmartCommand::operator<<(const CSqlInternalNumber &rData)
{   
	ASSERT(m_nBindsNeeded);
	
	CSqlCommand::operator<<(rData); 
	
	if (numBinds() == m_nBindsNeeded){   
	    bind();
	    execute();  
	    deleteAllBinds();
	    m_bExecuted = TRUE;
	    return *this;
		}                            
		
	return *this;
}

CSqlSmartCommand& CSqlSmartCommand::operator<<(const CSqlInternalDate &rData)
{   
	ASSERT(m_nBindsNeeded);
	
	CSqlCommand::operator<<(rData); 
	
	if (numBinds() == m_nBindsNeeded){   
	    bind();
	    execute();  
	    deleteAllBinds();
	    m_bExecuted = TRUE;
	    return *this;
		}                            
		
	return *this;
}
  
void CSqlSmartCommand::replaceBind(int nIndex, const CSqlString& rData)
{	
	CSqlCommand::replaceBind(nIndex, rData);
	bind();
	execute();
}

void CSqlSmartCommand::replaceBind(int nIndex, const CSqlNumber& rData)
{	
	CSqlCommand::replaceBind(nIndex, rData);
	bind();
	execute();
}

void CSqlSmartCommand::replaceBind(int nIndex, const CSqlDateTime& rData)
{	
	CSqlCommand::replaceBind(nIndex, rData);
	bind();
	execute();
}

void CSqlSmartCommand::replaceBind(int nIndex, const CSqlLongVarChar& rData)
{	
	CSqlCommand::replaceBind(nIndex, rData);
	bind();
	execute();
}

void CSqlSmartCommand::replaceBind(int nIndex, const CSqlInternalNumber& rData)
{	
	CSqlCommand::replaceBind(nIndex, rData);
	bind();
	execute();
}

void CSqlSmartCommand::replaceBind(int nIndex, const CSqlInternalDate& rData)
{	
	CSqlCommand::replaceBind(nIndex, rData);
	bind();
	execute();
}
