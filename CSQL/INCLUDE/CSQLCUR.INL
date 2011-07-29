///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlCursor
// 
inline CSqlCursor::~CSqlCursor()
{m_pRep->decrement();}

inline BOOL CSqlCursor::isConnected(void) const
{return m_pRep->m_bConnected;}

inline BOOL CSqlCursor::inBulkExecMode(void) const
{return m_pRep->m_bInBulkExecMode;}

inline CString CSqlCursor::getCursorName(void) const
{return m_pRep->m_szCursorName;}

inline CSqlCursor::operator SQLTCUR() const 
{return m_pRep->m_cur;}

inline void CSqlCursor::closeResultSet(const char* szResSetName)
{ASSERT(isConnected());
	if (::sqlcrs(*this, (SQLTDAP)szResSetName, 0))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::closeResultSet(#%d) - ok..\n", (int)*this);}

inline void CSqlCursor::dropResultSet(const char* szResSetName)
{ASSERT(isConnected());
	if (::sqldrs(*this, (SQLTDAP)szResSetName, 0))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::dropResultSet(#%d) - ok..\n", (int)*this);}

inline void CSqlCursor::resultSetPosition(int nRow)
{ASSERT(isConnected());
	if (::sqlprs(*this, (SQLTROW)nRow))
		THROW(new CSqlCsrException(*this));}
						
inline void CSqlCursor::restartRestrictAndResSetModes(const char* szResSetName)
{ASSERT(isConnected());
	if (::sqlrrs(*this, (SQLTDAP)szResSetName, 0))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::restartRestrictAndResSetModes(#%d) - ok..\n", (int)*this);}

inline void CSqlCursor::stopRestrictionMode(void)
{ASSERT(isConnected());
	if (::sqlspr(*this))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::stopRestrictionMode(#%d) - ok..\n", (int)*this);} 

inline void CSqlCursor::startRestrictAndResSetModes(void)
{ASSERT(isConnected());
	if (::sqlsrs(*this))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::startRestrictAndResSetModes(#%d) - ok..\n", (int)*this);}

inline void CSqlCursor::startRestrictionMode(void)
{ASSERT(isConnected());
	if (::sqlstr(*this))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::startRestrictionMode(#%d) - ok..\n", (int)*this);}

inline void CSqlCursor::undoResultSet(void)
{ASSERT(isConnected());
	if (::sqlurs(*this))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::undoResultSet(#%d) - ok..\n", (int)*this);} 

inline void CSqlCursor::commit(void)
{ASSERT(isConnected());
	if (::sqlcmt(*this)) 
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::commit(#%d) - ok..\n", (int)*this);} 

inline void CSqlCursor::rollback(void)
{ASSERT(isConnected());
	if (::sqlrbk(*this)) 
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::rollback(#%d) - ok..\n", (int)*this);}
            
inline void CSqlCursor::dropStoredCmd(const char* szCmdName)
{ASSERT(isConnected());
	if (::sqldst(*this, (SQLTDAP)szCmdName, 0))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::dropStoredCmd(#%d) - ok..\n", (int)*this);}  

inline void CSqlCursor::getCompiledCmd(const char* szCmdName)
{ASSERT(isConnected());
	if (::sqlret(*this, (SQLTDAP)szCmdName, 0))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::getCompiledCmd(#%d) - ok..\n", (int)*this);}  

inline void CSqlCursor::storeCompiledCmd(const char* szCmdName, const char* szCmd)
{ASSERT(isConnected());
	if (::sqlsto(*this, (SQLTDAP)szCmdName, 0, (SQLTDAP)szCmd, 0))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::storeCompiledCmd(#%d) - ok..\n", (int)*this);}  

inline void CSqlCursor::setInputMessageSize(SQLTDAL nSize)
{ASSERT(isConnected());
	if (::sqlims(*this, nSize))
		THROW(new CSqlCsrException(*this));} 

inline void CSqlCursor::setOutputMessageSize(SQLTDAL nSize)
{ASSERT(isConnected());
	if (::sqloms(*this, nSize))
		THROW(new CSqlCsrException(*this));} 

inline void CSqlCursor::setCachePages(SQLTNPG nPages)
{if (::sqlscp(nPages))
		THROW(new CSqlCsrException(*this));} 

inline void CSqlCursor::getStatistics(void)
{ASSERT(isConnected());
	if (::sqlsta(*this, &m_nVirtualReads, &m_nVirtualWrites, &m_nPhysicalReads, &m_nPhysicalWrites)) 
		THROW(new CSqlCsrException(*this));}

inline void CSqlCursor::bulkExecMode(BOOL bOn)
{ASSERT(isConnected());
	if (::sqlblk(*this, (SQLTFLG)bOn)) 
		THROW(new CSqlCsrException(*this));
	m_pRep->m_bInBulkExecMode = bOn;
	TRACE2("CSqlCursor::BulkExecMode(#%d) - %s..\n", (int)*this, bOn ? "on":"off");}
 
inline void CSqlCursor::bulkExecFlush()
{ASSERT(isConnected());
	if (::sqlbef(*this))
		THROW(new CSqlCsrException(*this));
	TRACE1("CSqlCursor::BulkExecFlush(#%d) - ok..\n", (int)*this);}

inline void CSqlCursor::setIsolationLevel(SQLTILV level)
{ASSERT(isConnected());
	if (::sqlsil(*this, level))
		THROW(new CSqlCsrException(*this));}

inline void CSqlCursor::setTimeout(SQLTTIV timeout)
{ASSERT(isConnected());
	if (::sqltio(*this, timeout))
		THROW(new CSqlCsrException(*this));}

inline void CSqlCursor::releaseCurrentLogFile()
{ASSERT(isConnected());
	if (::sqlrel(*this))
		THROW(new CSqlCsrException(*this));} 

///////////////////////////////////////////////////////////////////
//
// PRIVATE CLASS INLINES : CConnectionRep
//
inline CConnectionRep::CConnectionRep()
 :m_nUseCount(1), m_bConnected(FALSE),
  m_cur(0), m_bInBulkExecMode(FALSE)
 {}  

inline CConnectionRep::~CConnectionRep()
{
	if (m_bConnected){
		VERIFY((::sqldis(m_cur)) == 0);  
		TRACE1("dangling database connection #(%d) broken ok\n", (int)m_cur);
		}
}

inline void	CConnectionRep::increment()
{++m_nUseCount;}

inline void	CConnectionRep::decrement()
{if (--m_nUseCount == 0) 
	delete this;}