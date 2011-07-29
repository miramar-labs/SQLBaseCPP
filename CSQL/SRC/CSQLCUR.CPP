#include "stdincs.h"
#include "csqlcur.h"   
#include "csqlexep.h"



/////////////////////////////////////////////////////////////////////////////
//
//	CSqlCursor

CSqlCursor::CSqlCursor(const char* szDbName)
	: m_nVirtualReads(0), m_nVirtualWrites(0),
	m_nPhysicalReads(0), m_nPhysicalWrites(0),
	m_pRep(new CConnectionRep())
{
	ASSERT(strlen(szDbName));
	m_pRep->m_szDbName = szDbName;
}

// copy _ctor 
CSqlCursor::CSqlCursor(const CSqlCursor& a)
	:m_nVirtualReads(a.m_nVirtualReads), 
	m_nVirtualWrites(a.m_nVirtualWrites),
	m_nPhysicalReads(a.m_nPhysicalReads), 
	m_nPhysicalWrites(a.m_nPhysicalWrites)
{
	a.m_pRep->increment();
	m_pRep = a.m_pRep;                         
}  	

void CSqlCursor::connect()
{   
	SQLTAPI	ret;

	if (!isConnected()){
	
		ret = ::sqlcnc(&m_pRep->m_cur, (SQLTDAP)(const char*)m_pRep->m_szDbName, 0);
	
		m_pRep->m_bConnected = (ret == 0);
		
		} 

	 TRACE2("CSqlCursor::connect(#%d) %s\n", (int)*this,
    							isConnected() ? "ok" : "bad");
	
	// throw an exception if connect failed...	
	if(!isConnected())
		THROW(new CSqlException(ret));
}

void CSqlCursor::connectWithNoRecovery()
{ 
	SQLTAPI	ret;  
	
	if (!isConnected()){
	
	 	ret = ::sqlcnr(&m_pRep->m_cur, (SQLTDAP)(const char*)m_pRep->m_szDbName, 0);  
		
		m_pRep->m_bConnected = (ret == 0); 
		}                          
		
    TRACE2("CSqlCursor::connectWithNoRecovery(#%d) %s\n", 
    		(int)*this, 
    		isConnected() ? "ok" : "bad");
	
	// throw an exception if connect failed...		
	if(!isConnected())
		THROW(new CSqlException(ret));
}    

BOOL CSqlCursor::disconnect(BOOL bOverride)
{    
	SQLTAPI ret;
	    
	if (isConnected()){
	 	if (m_pRep->m_nUseCount != 0){
	 		// in use !
	 		if (bOverride)
				VERIFY((ret = ::sqldis(*this)) == 0);  
			else{
				TRACE1("can't disconnect (#%d) - cursor in use !\n", (int)*this);
				return FALSE;				
				}				
			}        
		else{
			// not in use..just disconnect...
			VERIFY((ret = ::sqldis(*this)) == 0);  
			}
		}		                          
	
	// we should always be disconnected when we reach here...
	
	(m_pRep->m_bConnected) = !(ret == 0);
		
    TRACE2("CSqlCursor::disconnect(#%d) %s\n", 
    	(int)*this, 
    	isConnected() ? "bad" : "ok");
    
    // throw an exception if disconnect failed...	
	if(isConnected())
		THROW(new CSqlException(ret));

	return TRUE;			
}

SQLTCTY CSqlCursor::getCmdType()
{
	SQLTCTY cty;
	
	ASSERT(isConnected());
	
	if (::sqlcty(*this, &cty)) 
		THROW(new CSqlCsrException(*this));
	return cty;
}

void CSqlCursor::getExecutionPlan(CString& rPlan, int nMaxSize)
{
	ASSERT(isConnected());
	if (::sqlexp(*this, (SQLTDAP)rPlan.GetBufferSetLength(nMaxSize), (SQLTDAL)nMaxSize))
		THROW(new CSqlCsrException(*this));
	rPlan.ReleaseBuffer();		
}

SQLTROW	CSqlCursor::getNumSQLBaseRows(const char* szTableName)
{
	SQLTROW rows; 
	ASSERT(isConnected());
	if (::sqlgnr(*this, (SQLTDAP)szTableName, 0, &rows)) 
		THROW(new CSqlCsrException(*this));
	return rows;
}

void CSqlCursor::setCursorName(const char* szName)
{   
	ASSERT(isConnected());
	if (::sqlscn(*this, (SQLTDAP)szName, 0)) 
		THROW(new CSqlCsrException(*this));
	m_pRep->m_szCursorName = szName;
}

SQLTDPV	CSqlCursor::getDbParamValue(SQLTPTY param)
{
	// use *this with param set to ANY valid database
	// param value (see C API ref pg262) that is NOT
	// in the list for GetDbParamString()...
	SQLTDPV	val;
	ASSERT(isConnected());
	if (::sqlget(*this, param, (SQLTDAP)&val, NULL))
			THROW(new CSqlCsrException(*this));
	return val;
}

CString	CSqlCursor::getDbParamString(SQLTPTY param)
{	
	// use *this with param set to one of :
	// SQLPALG, SQLPDBD, SQLPDBN, SQLPDDB, SQLPDDR, SQLPDPW,
	// SQLPDUS, SQLPEXE, SQLPISO, SQLPLDR, SQLPLDV, SQLPLRD,
	// SQLPPWD, SQLPVER
	
	char 	szBuff[SQLMFNL];
	SQLTDAL len;
	ASSERT(isConnected());
	if (::sqlget(*this, param, (SQLTDAP)szBuff, &len)) 
		THROW(new CSqlCsrException(*this));
	szBuff[len]=0;	
	return szBuff;
}

void CSqlCursor::setDbParamValue(SQLTPTY param, SQLTDPV val)
{
	// use *this with param set to ANY valid database
	// param value (see C API ref pg358) that is NOT
	// in the list for GetDbParamString()... 
	ASSERT(isConnected());
	if (::sqlset(*this, param, (SQLTDAP)&val, NULL)) 
		THROW(new CSqlCsrException(*this));
}

void CSqlCursor::setDbParamString(SQLTPTY param, const char* szVal)
{
	// use *this with param set to one of :
	// SQLPALG, SQLPDBD, SQLPDBN, SQLPDDB, SQLPDDR, SQLPDPW,
	// SQLPDUS, SQLPEXE, SQLPISO, SQLPLDR, SQLPLDV, SQLPLRD,
	// SQLPPWD, SQLPVER 
	ASSERT(isConnected());
	if (::sqlset(*this, param, (SQLTDAP)szVal, 0)) 
		THROW(new CSqlCsrException(*this));
}                                                                           

// protected..
CSqlCursor::CSqlCursor()
	: m_nVirtualReads(0), m_nVirtualWrites(0),
	m_nPhysicalReads(0), m_nPhysicalWrites(0),
	m_pRep(NULL)
	{}

const CSqlCursor& CSqlCursor::operator=(const CSqlCursor& rCur)
{                
	if (&rCur != this){    
		m_pRep->decrement();   

		rCur.m_pRep->increment();
		
		m_pRep = rCur.m_pRep; 
		
		m_nVirtualReads = rCur.m_nVirtualReads;
        m_nVirtualWrites = rCur.m_nVirtualWrites;
        m_nPhysicalReads = rCur.m_nPhysicalReads;
        m_nPhysicalWrites = rCur.m_nPhysicalWrites;		
		}
	TRACE0("CSqlCursor::operator= called\n");		    
	return *this;
}

