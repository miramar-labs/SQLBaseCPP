///////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlexep.h	: 	header for class CSqlException & CSqlCsrException
//
//	Author		:	Aaron Cody
//	Date		:	1st May 1994  
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:	The MFC runtime class mechanism had to be hacked in order
//					to get these two classes into a DLL - I had to expand the usual
//					MFC macros and explicitly make the runtime class structures FAR.
//					Otherwise the application cannot catch these objects !
//					I think this is a bug with the MFC. Anyway, the hack works, and
//					will hopefully be made redundant when the compiler gets a proper
//					implementation of exception handling & RTTI.
//   

#ifndef CSQLEXCP_H
	#define CSQLEXCP_H

// fwd. dec's
class CSqlCursor;
class CSqlException;

class CSqlException : public CException
{   
//DECLARE_DYNAMIC(CSqlException)
public: 
	static CRuntimeClass _far classCSqlException;  	// hack !
	virtual CRuntimeClass* GetRuntimeClass() const;
 	
public:             
// construction/destruction
			CSqlException(SQLTRCD rcd);
	virtual ~CSqlException(){} 

// error information
	CString	errorMessage(void) const;						
	CString	fullErrorMessage(void) const;					
	CString errorReason(void) const;					
	CString errorRemedy(void) const;					
	
// this object as an SQLBase error return code
	operator SQLTRCD() const;
	
protected:
	CSqlException();  		// default _ctor
	SQLTRCD	m_rcd;			// SQLBase rcd
	
private:
	// not implemented for this class
	const CSqlException& operator=(const CSqlException& rCmd){return *this;}
	CSqlException(const CSqlException& rCmd){}
};
                          
class CSqlCsrException : public CSqlException
{
//DECLARE_DYNAMIC(CSqlCsrException)
public: 
	static CRuntimeClass _far classCSqlCsrException;    // hack !
	virtual CRuntimeClass* GetRuntimeClass() const;

public:
// construction/destruction
			CSqlCsrException(const CSqlCursor& rCur); 
			CSqlCsrException(const CSqlCursor& rCur1, const CSqlCursor& rCur2);
	virtual ~CSqlCsrException(){}

// standard error information
	SQLTEPO	errorPosition(void) const;			
	SQLTRBF	rollbackFlag(void) const;			
	SQLTRCD translateErrorCode(void) const;			
	SQLTXER	externalError(CString &rMsg) const;	
	
// bulk-execute mode errors..
	BOOL	enumBulkExecErrors(SQLTBIR nSeqNo);
	BOOL	enumNonSQLBaseBulkExecErrors(SQLTBIR nSeqNo);

// bulk-exec mode data members
    SQLTBIR	m_nBulkExecErrorRow;
    SQLTRBF	m_nBulkExecRollbackFlag;
	CString	m_szNonSQLBaseErrMsg;
    SQLTXER	m_nNonSQLBaseRcd;

// 2nd cursor query..
    BOOL	toggleCursors();
    
protected:
	SQLTRCD	m_rcd2;		// second cursor 
	int		m_nCurs;  
private:
	// not implemented for this class
	CSqlCsrException(const CSqlCsrException&){}
	const CSqlCsrException& operator=(const CSqlCsrException&){return *this;}
};

#include "csqlexep.inl" 

#endif	
