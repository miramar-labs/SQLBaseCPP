#include "stdincs.h"
#include "csqlcur.h"
#include "csqlexep.h"


//IMPLEMENT_DYNAMIC(CSqlException, CException)
static char BASED_CODE _lpszCSqlException[] = "CSqlException";
CRuntimeClass _far CSqlException::classCSqlException = { 
	_lpszCSqlException, sizeof(CSqlException), 0xFFFF, NULL, 
		RUNTIME_CLASS(CException), NULL }; 
static AFX_CLASSINIT _init_CSqlException(&CSqlException::classCSqlException); 
CRuntimeClass* CSqlException::GetRuntimeClass() const
	{ return &CSqlException::classCSqlException; }

//IMPLEMENT_DYNAMIC(CSqlCsrException, CSqlException)  
static char BASED_CODE _lpszCSqlCsrException[] = "CSqlCsrException";
CRuntimeClass _far CSqlCsrException::classCSqlCsrException = { 
	_lpszCSqlCsrException, sizeof(CSqlCsrException), 0xFFFF, NULL, 
		RUNTIME_CLASS(CSqlException), NULL }; 
static AFX_CLASSINIT _init_CSqlCsrException(&CSqlCsrException::classCSqlCsrException); 
CRuntimeClass* CSqlCsrException::GetRuntimeClass() const
	{ return &CSqlCsrException::classCSqlCsrException; }

CString	CSqlException::fullErrorMessage(void) const
{
	CString	szFer;
	
	SQLTAPI	ret = ::sqlfer(m_rcd, 
		(SQLTDAP)szFer.GetBufferSetLength(SQLMXER));
	
	szFer.ReleaseBuffer();
	
	if (ret)
		szFer = "No error message available";
		
	TRACE1("full error message : %s\n", szFer.Left(250));
		
	return szFer;
}

CString	CSqlException::errorMessage(void) const
{
	CString	szErr;  

	SQLTAPI	ret = ::sqlerr(m_rcd, 
		(SQLTDAP)szErr.GetBufferSetLength(SQLMXER));

	szErr.ReleaseBuffer();
		
	if (ret)
		szErr = "No error message available";
		
	TRACE1("error message : %s\n", szErr.Left(250));
		
	return szErr;
}

CString CSqlException::errorReason(void) const
{
	CString	szRsn;
	SQLTDAL	len; 

	SQLTAPI	ret = ::sqletx( m_rcd, SQLXREA,
							(SQLTDAP)szRsn.GetBufferSetLength(SQLMETX),
							SQLMETX, &len);
	
	if (ret)
		szRsn = "No reason information available";
	else
		szRsn.ReleaseBuffer(len);

	TRACE1("error reason : %s\n", szRsn.Left(250));
		
	return szRsn;
}

CString CSqlException::errorRemedy(void) const
{
	CString	szRmd;
	SQLTDAL	len; 

	SQLTAPI	ret = ::sqletx( m_rcd, SQLXREM,
							(SQLTDAP)szRmd.GetBufferSetLength(SQLMETX),
							SQLMETX, &len);
	
	if (ret)
		szRmd = "No remedy information available";
	else
		szRmd.ReleaseBuffer(len);

	TRACE1("error remedy : %s\n", szRmd.Left(250));
		
	return szRmd;
}

////////////////////////////////////////////////////////////////////////
//	CSqlCsrException...

#define MAX_NONSQLERRMSG	1000

BOOL CSqlCsrException::toggleCursors()
{                      
	// switches the cursor context of this exception..
	// if TWO cursors this swaps them so you can examine the other..returns TRUE
	// if ONE cursor..no swap, FALSE returned.
	
	if (m_nCurs != 1){
		SQLTRCD temp = m_rcd;
		m_rcd = m_rcd2;
		m_rcd2 = temp;
		return TRUE;
		}
	return FALSE;		
}

CSqlCsrException::CSqlCsrException(const CSqlCursor& rCur)
	:m_nCurs(1)
{   
	// single cursor exception
	VERIFY(::sqlrcd(rCur, &m_rcd) == 0);
}

CSqlCsrException::CSqlCsrException(const CSqlCursor& rCur1, const CSqlCursor& rCur2)
	:m_nCurs(2)
{                        
	// double-cursor exception
	VERIFY(::sqlrcd(rCur1, &m_rcd) == 0);
	VERIFY(::sqlrcd(rCur2, &m_rcd2) == 0);
}

SQLTEPO CSqlCsrException::errorPosition(void) const
{ 
	SQLTEPO epo;
	SQLTAPI	ret = ::sqlepo(m_rcd, &epo);
	
	if (ret)
		TRACE0("::sqlepo failed !\n");
	else
		TRACE1("error position : %d\n", epo);
		
	return epo;
}				        

SQLTRBF CSqlCsrException::rollbackFlag(void) const
{ 
	// get the rollback flag...  
	SQLTRBF rbf;
	SQLTAPI	ret = ::sqlrbf(m_rcd, &rbf); 
	
	if (ret)
		TRACE0("::sqlrbf failed !\n");
	else
		TRACE1("rollback flag : %d\n", rbf);
		
	return rbf;
}				        

SQLTRCD CSqlCsrException::translateErrorCode(void) const
{
	SQLTRCD trcd;
	SQLTAPI	ret = ::sqltec(m_rcd, &trcd); 
	
	if (ret)
		TRACE0("::sqltec failed !\n");
	else
		TRACE1("translated error code : %d\n", trcd);
		
	return trcd;
}	
	
SQLTXER	CSqlCsrException::externalError(CString& rMsg) const
{
	SQLTDAL len = 0;
	SQLTXER xerr = 0; 
	
	SQLTAPI	ret = ::sqlxer(	m_rcd, &xerr, 
		(SQLTDAP)rMsg.GetBufferSetLength(SQLMXER), &len);  
		
	if (ret){
		rMsg.ReleaseBuffer(len);
		TRACE0("::sqlxer failed !\n");
		}
	else {
		TRACE1("extended error code : %d\n", xerr);
		TRACE1("extended error message : %s\n", rMsg.Left(250));
		}
		
	return xerr;
}
	

BOOL CSqlCsrException::enumBulkExecErrors(SQLTBIR nSeqNo)
{
	SQLTRCD	rcd;
			
	VERIFY(::sqlber(m_rcd, 
					&rcd, 
					&m_nBulkExecErrorRow, 
					&m_nBulkExecRollbackFlag, 
					nSeqNo) == 0);

	if (rcd)
		m_rcd = rcd; 
				
	return (rcd != 0);
}             

BOOL CSqlCsrException::enumNonSQLBaseBulkExecErrors(SQLTBIR nSeqNo)
{	                                               
	SQLTDAL len;
			
	VERIFY(::sqlbbr(m_rcd,
					&m_nNonSQLBaseRcd, 
					(SQLTDAP)m_szNonSQLBaseErrMsg.GetBufferSetLength(MAX_NONSQLERRMSG),
					(SQLTDAL PTR)&len,
					&m_nBulkExecErrorRow, 
					&m_nBulkExecRollbackFlag, 
					nSeqNo) == 0);

	 ASSERT(len <= MAX_NONSQLERRMSG);

	 m_szNonSQLBaseErrMsg.ReleaseBuffer(len);

	return ((m_nNonSQLBaseRcd != 0) && (m_nBulkExecErrorRow > 0));
}



