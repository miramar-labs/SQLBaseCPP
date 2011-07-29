///////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994    
//
//	csqlcur.h	: 	header for class CSqlCursor
//
//	Author		:	Aaron Cody
//	Date		:	24th January 1994    
//	Version		:	SQLBase++ v1.2	       
//	Remarks		:   use-counting scheme modified - the primary goal is now
//					that there be no dangling db connections left open after the 
//					last instance of a particular cursor object is destroyed.
//    

#ifndef CSQLCUR_H
	#define CSQLCUR_H

#include "csqlexep.h"
	
class CConnectionRep;

class CSqlCursor 
{   
	
public:  
// construction/destruction
		CSqlCursor(const char* szDbName); 
		CSqlCursor(const CSqlCursor& a);
		virtual ~CSqlCursor();  
		
// connection/disconnection..
		BOOL	isConnected(void) const;
 		void 	connect(void);								
 		void 	connectWithNoRecovery(void);			
 		BOOL	disconnect(BOOL bOverride = FALSE); 
				      
// result set & restriction modes...
		void	closeResultSet(const char* szResSetName);
		void	dropResultSet(const char* szResSetName);
		void 	resultSetPosition(int nRow);						
        void	restartRestrictAndResSetModes(const char* szResSetName);
        void	stopRestrictionMode(void);
        void	startRestrictAndResSetModes(void);
        void	startRestrictionMode(void);
        void	undoResultSet(void);
            
// transaction control..
        void	commit(void);
        void	rollback(void);
            
// stored commands..
        void	dropStoredCmd(const char* szCmdName);
        void	getCompiledCmd(const char* szCmdName);
        void	storeCompiledCmd(const char* szCmdName, const char* szCmd);
            
// environment..
		SQLTDPV	getDbParamValue(SQLTPTY param);
		CString	getDbParamString(SQLTPTY param);
		void	setDbParamValue(SQLTPTY param, SQLTDPV val);
		void	setDbParamString(SQLTPTY param, const char* szVal);
		void	setInputMessageSize(SQLTDAL nSize);
		void	setOutputMessageSize(SQLTDAL nSize);
		void	setCachePages(SQLTNPG nPages);
		void	getStatistics(void);
			
// bulk execute mode..
		BOOL	inBulkExecMode(void) const;
		void	bulkExecMode(BOOL bOnOrOff);       
		void	bulkExecFlush(void);
			
// miscellaneous..
		SQLTCTY	getCmdType(void);
		void	getExecutionPlan(CString& rPlan, int nMaxSize = 1000);
		SQLTROW	getNumSQLBaseRows(const char* szTableName);
		void	setCursorName(const char* szName); 
		CString	getCursorName(void) const;
		void	setIsolationLevel(SQLTILV level);
		void	setTimeout(SQLTTIV timeout); 
		void	releaseCurrentLogFile(void); 

// this object as an SQLBase cursor		
        operator SQLTCUR() const;

// statistics        
        SQLTSTC	m_nVirtualReads;
        SQLTSTC	m_nVirtualWrites;
        SQLTSTC	m_nPhysicalReads;
        SQLTSTC	m_nPhysicalWrites; 
        
// assignment..        
		const CSqlCursor& operator=(const CSqlCursor& rCmd);
        
protected:
		CConnectionRep*	m_pRep;  
		CSqlCursor();
};

////////////////////////////////////////////////////////////////////////
//
//	PRIVATE CLASS : CConnectionRep
//
//	Remarks:	An object of this class models a physical database connection.
//				Copies of a particular cursor object share this connection-rep.
//				When the rep's use count reaches zero, it will self destruct, 
//				triggering a check to see if it is still connected and if so, 
//				will disconnect - hence no dangling db connections...

class CConnectionRep{
private:
	friend class CSqlCursor;
	friend class CSqlCommand;
	
// cursor-specific data...
	int 		m_nUseCount;
	BOOL		m_bConnected;
	SQLTCUR		m_cur;
	CString		m_szDbName;
	BOOL		m_bInBulkExecMode;
	CString		m_szCursorName;	    
	
// _ctor/~ctor..
	CConnectionRep();  
	virtual ~CConnectionRep(); 

// inc/dec ..
	void	increment();
	void	decrement();
	}; 
			
#include "csqlcur.inl"

#endif	
