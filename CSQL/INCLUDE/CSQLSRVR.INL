///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlServer
// 
inline CSqlServer::~CSqlServer()
{if (m_bConnected) disconnect();}

inline BOOL	CSqlServer::isConnected(void) const
{return m_bConnected;}

inline void	CSqlServer::deInstallDatabase(const char* szDbName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlded(m_sHandle, (SQLTDAP)szDbName, 0))
	THROW(new CSqlException(rcd));} 

inline void	CSqlServer::deleteDatabase(const char* szDbName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqldel(m_sHandle, (SQLTDAP)szDbName, 0))
	THROW(new CSqlException(rcd));} 
	
inline void	CSqlServer::installDatabase(const char* szDbName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlind(m_sHandle, (SQLTDAP)szDbName, 0))
	THROW(new CSqlException(rcd));} 
	
inline void	CSqlServer::shutDownDatabase(const char* szDbName)
{SQLTRCD rcd;
if (rcd = ::sqlsdn((SQLTDAP)szDbName, 0))
	THROW(new CSqlException(rcd));} 

inline void	CSqlServer::contRollFwd(const char* szDbName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlcrf(m_sHandle, (SQLTDAP)szDbName, 0))
	THROW(new CSqlException(rcd));} 
	
inline void	CSqlServer::endRollFwd(const char* szDbName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlenr(m_sHandle, (SQLTDAP)szDbName, 0))
	THROW(new CSqlException(rcd));}  
	
// file & directory access..
inline void	CSqlServer::closeDir(void)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqldrc(m_sHandle))
	THROW(new CSqlException(rcd));}
 
inline void	CSqlServer::openDir(const char* szDirName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqldro(m_sHandle, (SQLTDAP)szDirName))
	THROW(new CSqlException(rcd));} 

inline void	CSqlServer::getFile(const char* szSvrFileName, const char* szLocalFileName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlfgt(m_sHandle,(SQLTDAP)szSvrFileName, 
(SQLTDAP)szLocalFileName))
	THROW(new CSqlException(rcd));} 
 
inline void	CSqlServer::putFile(const char* szSvrFileName, const char* szLocalFileName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlfpt(m_sHandle,(SQLTDAP)szSvrFileName, 
(SQLTDAP)szLocalFileName))
	THROW(new CSqlException(rcd));}
 
inline void	CSqlServer::remoteCloseSrvrFile(SQLTFLH nFileHandle)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlmcl(m_sHandle, nFileHandle))
	THROW(new CSqlException(rcd));}
 
inline void	CSqlServer::remoteDeleteSrvrFile(const char* szFileName)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlmdl(m_sHandle, (SQLTDAP)szFileName))
	THROW(new CSqlException(rcd));} 

inline void	CSqlServer::changeProcessActivityLogFile(const char* szLogFileName, SQLTFMD startflag)
{ASSERT(m_bConnected);SQLTRCD rcd;
if (rcd = ::sqlclf(m_sHandle, (SQLTDAP)szLogFileName, startflag))
	THROW(new CSqlException(rcd));} 