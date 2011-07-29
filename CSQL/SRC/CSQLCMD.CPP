#include "stdincs.h" 
#include "csqlcur.h"
#include "csqlexep.h"

#include "csqltype.h"
	#include "csqlnum.h"
	#include "csqllvc.h"
	#include "csqlstr.h"
	#include "csqldtm.h"
	#include "csqlidat.h"
	#include "csqlinum.h"    

#include "csqlcmd.h"

// private helper (used for reading/writing huge long varchars)
static UINT _CSqlCalcSize(DWORD cbTotal, const void FAR* lpStart);

const DWORD CSqlCommand::lvcMaxBlockWrite = 32767; 	// 32k

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlCommand
CSqlCommand::CSqlCommand(CSqlCursor& rCur, const char* szCmd)
	:m_pCursor(NULL), m_bBound(FALSE),
	m_bCompiled(FALSE), m_nBindsNeeded(0),
	m_bExecuted(FALSE), m_pBinds(new CObArray)
{
	associateWith(rCur);

	if (strlen(szCmd))
		associateWith(szCmd);
}

CSqlCommand::CSqlCommand(CSqlCursor& rCur, const UINT nId)
	:m_pCursor(NULL), m_bBound(FALSE),
	m_bCompiled(FALSE), m_nBindsNeeded(0),
	m_bExecuted(FALSE), m_pBinds(new CObArray)
{
	associateWith(rCur);
	associateWith(nId); 
}

CSqlCommand::~CSqlCommand()
{   
	// free all internally allocated memory 
	if (m_pCursor)
		delete m_pCursor; 

    // kill the bind array & its contents..
	if (m_pBinds){		
		deleteAllBinds(); 
		delete m_pBinds;  
		m_pBinds = NULL;
	}
}

BOOL CSqlCommand::compile(void)
{
	ASSERT(m_pCursor->isConnected());

	if (m_szCmdStr.IsEmpty()){
		TRACE0("no command string to compile !\n");
		return FALSE;
		}

	if (!m_bCompiled){
		TRACE0("compiling...\n");

		if(::sqlcom(*m_pCursor, (SQLTDAP)(const char*)m_szCmdStr, 0)){
			cleanUp();
			THROW(new CSqlCsrException(*m_pCursor));
			}

		// get number of binds...
		if(::sqlnbv(*m_pCursor, &m_nBindsNeeded)){
			cleanUp();
			THROW(new CSqlCsrException(*m_pCursor));
			}
			
		if (m_nBindsNeeded == 0)
			m_bBound = TRUE;	
		} 
		
	return (m_bCompiled = TRUE);
}

BOOL CSqlCommand::bind(void)
{  
	ASSERT(m_pCursor->isConnected());
	
	if (!m_bCompiled){
		TRACE0("can't bind until compiled\n");
		return FALSE;
		}
	
	if (m_pBinds->GetSize() < m_nBindsNeeded){
		TRACE0("can't bind - too few binds !\n");		
		return FALSE;
		}

#ifdef _DEBUG
	if (m_bBound)
		TRACE0("already bound...\n");
	else
		TRACE0("binding...\n");		
#endif	
	
	if (!m_bBound){
		
		// first make sure we're cleared from any previous binds..
		if(::sqlcbv(*m_pCursor)){
			cleanUp();
			THROW(new CSqlCsrException(*m_pCursor));
			}
		
		ASSERT_VALID(m_pBinds);
			
		for (int j = 0 ; j < m_nBindsNeeded ; j++){ 
		    
		    CSqlType* pItem = (CSqlType*)m_pBinds->GetAt(j);
		    
    		switch(pItem->m_ObjType){  
    			case CSqlType::csqlInt: 
    				TRACE2("int bind[%d] = %d\n", j, (int)*(CSqlNumber*)pItem); 
    				break;
    			case CSqlType::csqlShort: 
    				TRACE2("short bind[%d] = %hd\n", j, (short)*(CSqlNumber*)pItem); 
    				break;
    			case CSqlType::csqlUInt:
   					TRACE2("unsigned int bind[%d] = %u\n", j, (unsigned int)*(CSqlNumber*)pItem); 
    				break;    
    			case CSqlType::csqlUShort:
    				TRACE2("unsigned short bind[%d] = %hu\n", j, (unsigned short)*(CSqlNumber*)pItem); 
    				break;    
    			case CSqlType::csqlDouble:
					TRACE2("double bind[%d] = %lf\n", j, (double)*(CSqlNumber*)pItem);    	
					break;
    			case CSqlType::csqlFloat:
					TRACE2("float bind[%d] = %f\n", j, (float)*(CSqlNumber*)pItem);    	
					break;
				case CSqlType::csqlLong:
					TRACE2("long bind[%d] = %ld\n", j, (long)*(CSqlNumber*)pItem);    	
					break;
				case CSqlType::csqlULong:	
					TRACE2("unsigned long bind[%d] = %lu\n", j, (unsigned long)*(CSqlNumber*)pItem);    	
					break; 
				case CSqlType::csqlString:
					TRACE2("string bind[%d] = %s\n", j, (const char *)*(CSqlString*)pItem);						
					break; 
				case CSqlType::csqlIntNum:
					TRACE1("internal numeric bind[%d]\n", j);
					break;    
				case CSqlType::csqlIntDate:
					TRACE1("internal date bind[%d]\n", j);
					break;  
				case CSqlType::csqlDateTime:
					TRACE2("date/time bind[%d] = %s\n", j, (const char *)(((CSqlDateTime*)pItem)->asSqlTimeStr()));						
					break; 
				case CSqlType::csqlLongVarChar: 
					TRACE1("long varchar bind[%d]\n", j);
					continue;	// will do it separately..					
				default:
					TRACE1("unknown bind[%d] !\n", j); 
					ASSERT(FALSE);
					break;
				}			    			
		    
			SQLTDAP buff = pItem->dataBuffer();
			
			SQLTDAL len =  (SQLTDAL)pItem->dataLength();
			
		    SQLTPDT type = pItem->m_BindType;
		    
		    ASSERT(::AfxIsValidAddress(buff, len));
		    
			if(::sqlbnn(*m_pCursor, j+1, buff, len, 0, type)){
				cleanUp();
				THROW(new CSqlCsrException(*m_pCursor));
				}
				
			}// bind loop..
			
		}// if !bound       

	return (m_bBound = TRUE);		
}       

BOOL CSqlCommand::bindWithNull(int nBind, BOOL bNullData)
{   
	// support for non-sqlbase databases.....
	// apply this to selected binds  (:nBind)
	ASSERT(m_pCursor->isConnected());
	
	if (!m_bCompiled){
		TRACE0("can't bind until compiled\n");
		return FALSE;
		}
	
	ASSERT_VALID(m_pBinds);
	
	ASSERT((nBind <= (numBinds() + 1)) && (nBind > 0));
	
	TRACE2("binding :%d as %sNULL...\n", nBind, bNullData ? "" : "NON-");
	
	SQLTNUL	nli = bNullData ? -1 : 0;
		
	CSqlType* pItem = (CSqlType*)m_pBinds->GetAt(nBind - 1);
		    
	SQLTPDT type = pItem->m_BindType;
	
	ASSERT(type != SQLPBUF);	
		    
	SQLTDAP buff = pItem->dataBuffer();
			
	SQLTDAL len =  (SQLTDAL)pItem->dataLength();
	
    ASSERT(::AfxIsValidAddress(buff, len)); 
		
	if(::sqlbnu(*m_pCursor, nBind, buff, len, 0, type, nli)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}       
		
	return TRUE;		
}       

BOOL CSqlCommand::compileAndExecute(void)
{
	// don't use this if you have binds !
	ASSERT(m_pCursor->isConnected());
	
	if (m_szCmdStr.IsEmpty()){
		TRACE0("no command string to compile & execute!\n");
		return FALSE;
		}

	TRACE0("compiling & executing...\n"); 
		
	if(::sqlcex(*m_pCursor, (SQLTDAP)(const char*)m_szCmdStr, 0)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
	
	return (m_bCompiled = m_bExecuted = TRUE);
}

BOOL CSqlCommand::execute(void)
{   
	ASSERT(m_pCursor->isConnected());
	
	if (!(m_bCompiled && m_bBound)){
		TRACE0("can't execute until compiled and bound\n");
		return FALSE;
		}            
		
	TRACE0("executing...\n");
	
	writeAnyLongVarChars();	
	
	if(::sqlexe(*m_pCursor)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
		
	return (m_bExecuted = TRUE);
}
     
void CSqlCommand::associateWith(const char* szNewCmd)
{
	// reset old binds...
	deleteAllBinds();
	// set the string  
	m_szCmdStr = szNewCmd; 
	// update the member flags..
	m_bCompiled = m_bBound = m_bExecuted = FALSE;
}

void CSqlCommand::associateWith(const UINT nId)
{
	// reset old binds...
	deleteAllBinds();
	// set the string  
	VERIFY(m_szCmdStr.LoadString(nId)); 
	// update the member flags..
	m_bCompiled = m_bBound = m_bExecuted = FALSE;
}

void CSqlCommand::associateWith(CSqlCursor& rNewCursor)
{
	// this function must increment the use count of the new cursor
	// and decrement the use count of the old...
	delete m_pCursor;

	m_pCursor = new CSqlCursor(rNewCursor);	// invokes copy _ctor
	
	 // update object's state..
	m_bCompiled = m_bBound = m_bExecuted = FALSE;      
}

void CSqlCommand::deleteAllBinds()
{ 
	ASSERT_VALID(m_pBinds);
	
	for (int i = 0; i < m_pBinds->GetSize() ; i++){
	
		delete (CSqlType*)m_pBinds->GetAt(i);            
		}
		
	m_pBinds->RemoveAll(); 
	
	m_bBound = m_bExecuted = FALSE;
	
	ASSERT(m_pBinds->GetSize() == 0);		
}

CSqlCommand& CSqlCommand::operator<<(const CSqlString &rString)
{   
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	
	if (numBinds() == m_nBindsNeeded){
	    TRACE0("ignoring extra bind\n");
	    return *this;
		}

    int nIndex = m_pBinds->Add(new CSqlString(rString));
    	
    m_bBound = m_bExecuted = FALSE; 
    	
	return *this;
}

CSqlCommand& CSqlCommand::operator<<(const CSqlNumber &rNumber)
{                       
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	
	if (numBinds() == m_nBindsNeeded){
	    TRACE0("ignoring extra bind\n");
	    return *this;
		}
		                 
    int nIndex = m_pBinds->Add(new CSqlNumber(rNumber));        
    	
    m_bBound = m_bExecuted = FALSE;
    	
	return *this;
}

CSqlCommand& CSqlCommand::operator<<(const CSqlInternalNumber &rNumber)
{   
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	
	if (numBinds() == m_nBindsNeeded){
	    TRACE0("ignoring extra bind\n");
	    return *this;
		}
		                 
    int nIndex = m_pBinds->Add(new CSqlInternalNumber(rNumber));        
    	
    m_bBound = m_bExecuted = FALSE;
    	
	return *this;
}

CSqlCommand& CSqlCommand::operator<<(const CSqlInternalDate &rDate)
{   
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	
	if (numBinds() == m_nBindsNeeded){
	    TRACE0("ignoring extra bind\n");
	    return *this;
		}
		                 
    int nIndex = m_pBinds->Add(new CSqlInternalDate(rDate));        
    	
    m_bBound = m_bExecuted = FALSE;
    	
	return *this;
}

CSqlCommand& CSqlCommand::operator<<(const CSqlLongVarChar &rBuff)
{   
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	
	if (numBinds() == m_nBindsNeeded){
	    TRACE0("ignoring extra bind\n");
	    return *this;
		}
		                 
    int nIndex = m_pBinds->Add(new CSqlLongVarChar(rBuff));        
    	
    m_bBound = m_bExecuted = FALSE;
    	
	return *this;
}

CSqlCommand& CSqlCommand::operator<<(const CSqlDateTime &rDateTime)
{   
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	  
	if (numBinds() == m_nBindsNeeded){
	    TRACE0("ignoring extra bind\n");
	    return *this;
		}
		                 
    int nIndex = m_pBinds->Add(new CSqlDateTime(rDateTime));        
    	
    m_bBound = m_bExecuted = FALSE;
    	
	return *this;
}
  
void	CSqlCommand::replaceBind(int nIndex, const CSqlString& rData)
{	
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	ASSERT((nIndex >= 0) && (nIndex <= m_pBinds->GetUpperBound()));
	
	delete (CSqlString*)m_pBinds->GetAt(nIndex);	
	
	m_pBinds->SetAt(nIndex, new CSqlString(rData));
	
	m_bBound = m_bExecuted = FALSE;
}

void	CSqlCommand::replaceBind(int nIndex, const CSqlNumber& rData)
{	                    
	ASSERT(m_bCompiled); 
	ASSERT_VALID(m_pBinds);
	ASSERT((nIndex >= 0) && (nIndex <= m_pBinds->GetUpperBound()));
	
	delete (CSqlNumber*)m_pBinds->GetAt(nIndex);	
	
	m_pBinds->SetAt(nIndex, new CSqlNumber(rData));
	
	m_bBound = m_bExecuted = FALSE;
}

void	CSqlCommand::replaceBind(int nIndex, const CSqlDateTime& rData)
{	                    
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	ASSERT((nIndex >= 0) && (nIndex <= m_pBinds->GetUpperBound()));
	
	delete (CSqlDateTime*)m_pBinds->GetAt(nIndex);	
	
	m_pBinds->SetAt(nIndex, new CSqlDateTime(rData));   
	
	m_bBound = m_bExecuted = FALSE;
}

void	CSqlCommand::replaceBind(int nIndex, const CSqlLongVarChar& rData)
{	                    
	ASSERT(m_bCompiled);
	ASSERT_VALID(m_pBinds);
	ASSERT((nIndex >= 0) && (nIndex <= m_pBinds->GetUpperBound()));
	
	delete (CSqlLongVarChar*)m_pBinds->GetAt(nIndex);	
	
	m_pBinds->SetAt(nIndex, new CSqlLongVarChar(rData));  
	
	m_bBound = m_bExecuted = FALSE;
}

void	CSqlCommand::replaceBind(int nIndex, const CSqlInternalNumber& rData)
{	                    
	ASSERT(m_bCompiled);   
	ASSERT_VALID(m_pBinds);
	ASSERT((nIndex >= 0) && (nIndex <= m_pBinds->GetUpperBound()));
	
	delete (CSqlInternalNumber*)m_pBinds->GetAt(nIndex);
	
	m_pBinds->SetAt(nIndex, new CSqlInternalNumber(rData));
	
	m_bBound = m_bExecuted = FALSE;
}

void	CSqlCommand::replaceBind(int nIndex, const CSqlInternalDate& rData)
{	                    
	ASSERT(m_bCompiled); 
	ASSERT_VALID(m_pBinds);
	ASSERT((nIndex >= 0) && (nIndex <= m_pBinds->GetUpperBound()));
	
	delete (CSqlInternalDate*)m_pBinds->GetAt(nIndex);
	
	m_pBinds->SetAt(nIndex, new CSqlInternalDate(rData));
	
	m_bBound = m_bExecuted = FALSE;
}

//////////////////////////////////////////////////////////////////////
//
//	PRIVATE helper

void CSqlCommand::writeAnyLongVarChars(void)
{	
	ASSERT_VALID(m_pBinds);
	
	// special case...
	for (int j = 0 ; j < m_nBindsNeeded ; j++){ 
		    
	    CSqlType* pItem = (CSqlType*)m_pBinds->GetAt(j);
		    
	    SQLTPDT type = pItem->m_BindType;
		
		if (type == SQLPBUF){   
		    DWORD dwBytesToWrite = pItem->dataLength(); 
		    
			TRACE2("writing long varchar bind[%d] - %ld bytes\n", j, dwBytesToWrite);
			
			if (::sqlbln(*m_pCursor, j+1)){
				cleanUp();
				THROW(new CSqlCsrException(*m_pCursor));
				}  
				
			// write it out in chunks ....(max 32k bytes..
			// see CSqlCommand::lvcMaxBlockWrite)   
			SQLTDAP pData = pItem->dataBuffer(); 	// locks down internal buffer
			
			while(dwBytesToWrite > 0){
				UINT nWrite = _CSqlCalcSize(dwBytesToWrite, pData);
				
				ASSERT(nWrite);
				ASSERT(::AfxIsValidAddress(pData, nWrite));
				
				if (::sqlwlo(*m_pCursor, (SQLTDAP)pData, (SQLTDAL)nWrite)){
					cleanUp();							
					THROW(new CSqlCsrException(*m_pCursor)); 
					}
				
				dwBytesToWrite -= nWrite;
				
				pData = ((BYTE __huge*)pData) + nWrite;
				 
				}// while more bytes to write..
			
			// end long operation..
			if (::sqlelo(*m_pCursor)){
				cleanUp();
				THROW(new CSqlCsrException(*m_pCursor));
				}
				
			}// if SQLPBUFF	
						
		}// bind loop   
		
	return;		
}

// protected...
CSqlCommand::CSqlCommand()
	:m_pCursor(NULL), m_bBound(FALSE),
	m_bCompiled(FALSE), m_nBindsNeeded(0),
	m_bExecuted(FALSE), m_pBinds(NULL)
{}

void CSqlCommand::cleanUp(void)
{   
	// we usually call this before throwing an exception...
	
	// We have to take extra measures to clean up before throwing
	// an exception as the MFC does not unwind the stack properly..

	// this routine tries to emulate the true destruction sequence
	// that should normally be carried out by the compiler.

	// NOTE that the cursor object does not get free'd - this results
	// in a memory leak. We cannot free it in here because it is needed
	// by the _ctor of the exception object as we subsequently prepare to 
	// throw an exception...
				
	// zap the SQL string.    
    m_szCmdStr.Empty();
    
    // kill the bind array & its contents..
	if (m_pBinds){		
		deleteAllBinds(); 
		delete m_pBinds;  
		m_pBinds = NULL;
	}
}

// helper for writing long varchars that span segment boundaries..
static UINT _CSqlCalcSize(DWORD cbTotal, const void FAR* lpStart)
{
	// return size to write (32K max unless limited by segment bounds)
	DWORD cb = 0x10000L - _AFX_FP_OFF(lpStart);
	if (cb > cbTotal)
		cb = cbTotal;
	return (cb > CSqlCommand::lvcMaxBlockWrite) ? 
			(UINT)CSqlCommand::lvcMaxBlockWrite 
			: (UINT)cb;
}

