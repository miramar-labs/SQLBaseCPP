#include "stdincs.h" 
#include "csqlcur.h"
#include "csqlexep.h"
#include "csqlsrvr.h"

#define	DBNAMES_BUFFLEN	1000
#define MAX_SVRINFOLEN	6000
#define MAX_FILENAMELEN	20
 
/////////////////////////////////////////////////////////////////////////////
//
//	CSqlServer 
//

CSqlServer::CSqlServer(const char* szSvrId)
 :m_bConnected(FALSE), m_sHandle(0),
 m_szSvrId(szSvrId)
{}

void CSqlServer::connect(const char* szPwd)
{   
	 SQLTRCD ret;
	 
	 if (!m_bConnected){
	 
	 	ret = ::sqlcsv( &m_sHandle,
	     	(SQLTDAP)(const char*)m_szSvrId, 
	     	(SQLTDAP)szPwd ); 
	 	
	 	if ((m_bConnected = (ret == 0)))
	  	m_szPwd = szPwd;
	 	}
	 
	 TRACE2("CSqlServer::connect(#%d) %s\n", (int)m_sHandle, m_bConnected ? "ok" : "bad");
	 
	 if (!m_bConnected)
	 	THROW(new CSqlException(ret));
}
       	
void CSqlServer::disconnect()
{   
	 SQLTAPI ret;
	 
	 if (m_bConnected){
	 
	  ret = ::sqldsv(m_sHandle);
	 
	 	m_bConnected = (ret != 0);
	 	}
	 
	 TRACE2("CSqlServer::disconnect(#%d) %s\n", (int)m_sHandle, !m_bConnected ? "ok" : "bad");
	 
	 if (m_bConnected)
	 	THROW(new CSqlException(ret));
} 
   
// server security..  

void CSqlServer::abortProcess(SQLTPNM nPid)
{   
	 SQLTRCD rcd;   
	 
	 ASSERT(m_bConnected);
	 
	 if(rcd = ::sqlsab(m_sHandle, nPid))
	 	THROW(new CSqlException(rcd));	
	 TRACE2("CSqlServer::abortProcess(#%d) - pid %d\n", (int)m_sHandle, (int)nPid);  
}

void CSqlServer::terminate(void)
{   
	 SQLTRCD rcd;   
	 
	 ASSERT(m_bConnected);
	 
	 if(rcd = ::sqlstm(m_sHandle))
	 	THROW(new CSqlException(rcd));
	 TRACE1("CSqlServer::terminate(#%d) - ok\n", (int)m_sHandle); 	
}  

void CSqlServer::getServerInfo(SQLTFLG flags, CString& rBuff)
{   
	 SQLTDAL len; 
	 SQLTRCD rcd;
	 ASSERT(m_bConnected);    
	 if(rcd = ::sqlgsi(m_sHandle, flags, (SQLTDAP)rBuff.GetBufferSetLength(MAX_SVRINFOLEN), MAX_SVRINFOLEN, &len))
	 	THROW(new CSqlException(rcd));
	 	
	 if (len <= MAX_SVRINFOLEN)
	 	rBuff.ReleaseBuffer(len);	// truncate to actual size..
	 else{// didn't get it all..try again...
	 	if(rcd = ::sqlgsi(m_sHandle, flags, (SQLTDAP)rBuff.GetBufferSetLength(len), len, &len))
	  	THROW(new CSqlException(rcd));
	 	rBuff.ReleaseBuffer();
	 	}
}
   
// database admin.
void CSqlServer::createDatabase(const char* szDbName)
{      
	 ASSERT(m_bConnected);
	 
	 SQLTRCD rcd = ::sqlcre(m_sHandle, (SQLTDAP)szDbName, 0); 
	 
	 TRACE1("CSqlServer::createDatabase - %s\n", (rcd == 0) ? "ok":"bad"); 
	 
	 if (rcd)
	 	THROW(new CSqlException(rcd));
}

int	CSqlServer::databaseNames(CStringArray& rList, const char* szSvrId)
{
	 SQLTRCD 	rcd;              
	 char		szBuff[DBNAMES_BUFFLEN]; // hope it's big enough..!!
	 
	 CString szUseSvr = (strlen(szSvrId) == 0) ? m_szSvrId : szSvrId;
	           
	 if(rcd = ::sqldbn( (SQLTDAP)(const char*)szUseSvr, 
	        (SQLTDAP)szBuff, sizeof(szBuff) ) )
	 	THROW(new CSqlException(rcd));          
	 
	 BOOL 	bMore  = TRUE;
	 int 	j 	= 0;
	 char* 	p 	= szBuff;
	 
	 ASSERT(rList.GetSize() == 0); // make sure of this before you call
	 
	 // form the string list...	
	 while (bMore){
	  	switch(szBuff[j]){
	  		case '\0':
			   	{
			   	bMore = (szBuff[j+1] != '\0');   // all done....
			   	CString szName(p, (&szBuff[j] - p));
			   	rList.Add(szName);
			   	p = &szBuff[j] + 1;
			   	j++;
			   	}
	   			break;
	  		default:
		   	j++;
		   	ASSERT(j < sizeof(szBuff));  // bang !
		   	break;   	
		  	}
	 	}
	 return rList.GetSize(); 
} 

int CSqlServer::readDirFileNames(CStringArray& rList)
{
	 ASSERT(m_bConnected); 
	 
	 char name[MAX_FILENAMELEN];
	 
	 ASSERT(rList.GetSize() == 0);
	 
	 while (!::sqldrr(m_sHandle, (SQLTDAP)name))
	  rList.Add(name);
	  
	 return rList.GetSize(); 	
}  


int	CSqlServer::dirOfDatabases(CStringArray& rList, SQLTSVN nSvr)
{   
	 // "use sqldbn instead of this function" !! quote C API ref pg 206
	 // ...so why does it exist at all ?????
	 SQLTRCD 	rcd;              
	 char		szBuff[DBNAMES_BUFFLEN]; // hope it's big enough..!!
	 
	 if(rcd = ::sqldir( (SQLTSVN)nSvr, 
	        (SQLTDAP)szBuff, sizeof(szBuff) ) )
	 	THROW(new CSqlException(rcd));          
	 
	 BOOL 	bMore  = TRUE;
	 int 	j 	= 0;
	 char* 	p 	= szBuff;
	 
	 ASSERT(rList.GetSize() == 0); // make sure of this before you call
	 
	 // form the string list...	
	 while (bMore){
	  	switch(szBuff[j]){
	  		case '\0':
			   	{
			   	bMore = (szBuff[j+1] != '\0');   // all done....
			   	CString szName(p, (&szBuff[j] - p));
			   	rList.Add(szName);
			   	p = &szBuff[j] + 1;
			   	j++;
			   	}
			   	break;
	  		default:
			   	j++;
			   	ASSERT(j < sizeof(szBuff));  // bang !
			   	break;   	
	  		}
	 	}
	 return rList.GetSize(); 
}

// backup & restore..    
void CSqlServer::backupDatabase(const char* szDbName, const char* szBkpDir, 
 BOOL bOnLocalNode, BOOL bOverWrite)
{
	 // set db param SQLPLBM before calling this...
	 SQLTRCD rcd;
	 
	 if (_mkdir(szBkpDir) == 0)	// just in case it doesn't exist
	 	TRACE1("created directory %s\n", szBkpDir);
	 	
	 TRACE0("CSqlServer::backupDatabase..backing up..\n"); 
	 
	 ASSERT(m_bConnected);
 	
	 if (rcd = ::sqlbdb( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	(SQLTDAP)szBkpDir, 0,
	     	(SQLTBOO)bOnLocalNode,
	     	(SQLTBOO)bOverWrite))
	 	THROW(new CSqlException(rcd)); 	
}
 
void CSqlServer::backupLogFiles(const char* szDbName, const char* szBkpDir, 
 BOOL bOnLocalNode, BOOL bOverWrite)
{
	 // set db param SQLPLBM before calling this...
	 SQLTRCD rcd;
	 
	 if (_mkdir(szBkpDir) == 0)	// just in case it doesn't exist
	 	TRACE1("created directory %s\n", szBkpDir);
	 
	 TRACE0("CSqlServer::backupLogFiles..backing up.."); 
	 
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlblf( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	(SQLTDAP)szBkpDir, 0,
	     	(SQLTBOO)bOnLocalNode,
	     	(SQLTBOO)bOverWrite))
	 	THROW(new CSqlException(rcd));
	 	
	 TRACE0("done\n");     	
}
 
void CSqlServer::backupSnapShot(const char* szDbName, const char* szBkpDir, 
 BOOL bOnLocalNode, BOOL bOverWrite)
{
	 // set db param SQLPLBM before calling this...
	 SQLTRCD rcd;
	
	 if (_mkdir(szBkpDir) == 0)	// just in case it doesn't exist
	 	TRACE1("created directory %s\n", szBkpDir);
	 
	 TRACE0("CSqlServer::backupSnapShot..backing up.."); 
	 
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlbss( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	(SQLTDAP)szBkpDir, 0,
	     	(SQLTBOO)bOnLocalNode,
	     	(SQLTBOO)bOverWrite))
	 	THROW(new CSqlException(rcd)); 	
	 	
	 TRACE0("done\n");   	
}
 
SQLTLNG	CSqlServer::getNextLog(const char* szDbName)
{
	 SQLTLNG log;
	 SQLTRCD rcd;
	 
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlgnl( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	&log))
	 	THROW(new CSqlException(rcd));
	 return log;     
}

void CSqlServer::restoreDatabase(const char* szDbName, const char* szBkpDir, 
 BOOL bOnLocalNode, BOOL bOverWrite)
{
	 SQLTRCD rcd;
	
	 TRACE0("CSqlServer::restoreDatabase..restoring...."); 
	
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlrdb( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	(SQLTDAP)szBkpDir, 0,
	     	(SQLTBOO)bOnLocalNode,
	     	(SQLTBOO)bOverWrite))
	 	THROW(new CSqlException(rcd));
	 	
	 TRACE0("done\n");   	
}  


void CSqlServer::restoreLogFiles(const char* szDbName, const char* szBkpDir, 
 BOOL bOnLocalNode, BOOL bOverWrite)
{
	 SQLTRCD rcd;
	
	 TRACE0("CSqlServer::restoreLogFiles..restoring...."); 
	
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlrlf( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	(SQLTDAP)szBkpDir, 0,
	     	(SQLTBOO)bOnLocalNode,
	     	(SQLTBOO)bOverWrite))
	 	THROW(new CSqlException(rcd));
	 	
	 TRACE0("done\n");   	
} 
  
void CSqlServer::rollForward(const char* szDbName, SQLTRFM mode, const char* datetime)
{
	 SQLTRCD rcd;
	 
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlrof( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	mode,
	     	(SQLTDAP)datetime,
	     	0))
	 	THROW(new CSqlException(rcd)); 	
}
 
void CSqlServer::restoreSnapShot(const char* szDbName, const char* szBkpDir, 
 BOOL bOnLocalNode, BOOL bOverWrite)
{
	 SQLTRCD rcd;
	 
	 ASSERT(m_bConnected);	
	 
	 if (rcd = ::sqlrss( m_sHandle, 
	     	(SQLTDAP)szDbName, 0, 
	     	(SQLTDAP)szBkpDir, 0,
	     	(SQLTBOO)bOnLocalNode,
	     	(SQLTBOO)bOverWrite))
	 	THROW(new CSqlException(rcd)); 	
} 
  	
SQLTFLH	CSqlServer::remoteOpenSrvrFile(const char* szFileName, SQLTFMD mode)
{
	 SQLTRCD rcd;
	 SQLTFLH fh;
	 
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlmop(m_sHandle, &fh, (SQLTDAP)szFileName, mode))
	 	THROW(new CSqlException(rcd));
	 return fh;
}  

 
SQLTLNG	CSqlServer::remoteSeekSrvrFile(SQLTFLH hFile, SQLTLNG offset, SQLTWNC origin)
{
	 SQLTLNG seekAddr;
	 SQLTRCD rcd;
	
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlmsk(m_sHandle, hFile, offset, origin, &seekAddr))
	 	THROW(new CSqlException(rcd)); 
	 	
	 return seekAddr;
 }  

SQLTDAL	CSqlServer::remoteReadSrvrFile(SQLTFLH hFile, char* pBuffer, SQLTDAL nBuffLen)
{
	 SQLTDAL numRead;
	 SQLTRCD rcd;
	
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlmrd(m_sHandle, hFile, (SQLTDAP)pBuffer, nBuffLen, &numRead))
	 	THROW(new CSqlException(rcd)); 
	 	
	 return numRead;
 }  

SQLTDAL	CSqlServer::remoteWriteSrvrFile(SQLTFLH hFile, char* pBuffer, SQLTDAL nBuffLen)
{
	 SQLTDAL numWritten;
	 SQLTRCD rcd;
	 
	 ASSERT(m_bConnected);
	 	
	 if (rcd = ::sqlmwr(m_sHandle, hFile, (SQLTDAP)pBuffer, nBuffLen, &numWritten))
	 	THROW(new CSqlException(rcd)); 
	 	
	 return numWritten;
 }  
