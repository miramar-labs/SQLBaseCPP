///////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlsrvr.h	: 	header for class CSqlServer
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994 
//	Version		:	SQLBase++ v1.2
//	Remarks		:
// 

#ifndef CSQLSRVR_H
	#define CSQLSRVR_H

class CSqlServer 
{   
public:   
// construction/destruction...                                    
		CSqlServer(const char* szSvrId = "");
		virtual ~CSqlServer();
	
// connection/disconnection..
		BOOL	isConnected(void) const;
 		void 	connect(const char* szPwd = "");								
 		void	disconnect(void);
	        
// server security..
        void	abortProcess(SQLTPNM nPid);
        void	terminate(void);
        void	getServerInfo(SQLTFLG flags, CString& rBuff);
	        
// database admin.
		void	createDatabase(const char* szDbName);
		int		databaseNames(CStringArray& rArray, const char* szSvrId = "");
		void	deInstallDatabase(const char* szDbName);
		void	deleteDatabase(const char* szDbName);
		int		dirOfDatabases(CStringArray& rList, SQLTSVN nSvr);
		void	installDatabase(const char* szDbName);
		void	shutDownDatabase(const char* szDbName);			
			
// backup & restore..       
		void	backupDatabase(	const char* szDbName, 
								const char* szBkpDir, 
								BOOL bOnLocalNode = TRUE, 
								BOOL bOverWrite = TRUE); 
									
		void	backupLogFiles( const char* szDbName, 
								const char* szBkpDir, 
								BOOL bOnLocalNode = TRUE, 
								BOOL bOverWrite = TRUE); 
									
		void	backupSnapShot( const char* szDbName, 
								const char* szBkpDir, 
								BOOL bOnLocalNode = TRUE, 
								BOOL bOverWrite = TRUE);
									
		void	contRollFwd(const char* szDbName);
			
		void	endRollFwd(const char* szDbName);
			
		SQLTLNG	getNextLog(const char* szDbName);
			
		void	restoreDatabase( const char* szDbName, 
								 const char* szBkpDir, 
								 BOOL bOnLocalNode = TRUE, 
								 BOOL bOverWrite = TRUE);
									 
		void	restoreLogFiles( const char* szDbName, 
								 const char* szBkpDir, 
								 BOOL bOnLocalNode = TRUE, 
								 BOOL bOverWrite = TRUE);
									 
		void	rollForward(const char* szDbName, 
							SQLTRFM mode, 
							const char* datetime = "");
			
		void	restoreSnapShot( const char* szDbName, 
								 const char* szBkpDir, 
								 BOOL bOnLocalNode = TRUE, 
								 BOOL bOverWrite = TRUE);
			
// file & directory access..
        void	closeDir(void);   
            
        void	openDir(const char* szDirName);  
            
        int 	readDirFileNames(CStringArray& rFileNames); 
            
        void	getFile(const char* szSvrFileName, 
        				const char* szLocalFileName); 
            				
        void	putFile(const char* szSvrFileName, 
        				const char* szLocalFileName); 
            				
        void	remoteCloseSrvrFile(SQLTFLH hFile);
            
        SQLTFLH	remoteOpenSrvrFile(	const char* szFileName, 
        							SQLTFMD mode = SQLORDWR);
            
        SQLTLNG	remoteSeekSrvrFile(	SQLTFLH hFile, 
						            SQLTLNG offset, 
						            SQLTWNC origin = 0 );
							            
		SQLTDAL	remoteWriteSrvrFile(SQLTFLH hFile, 
									char* pBuffer, 
									SQLTDAL nBuffLen);
																	            
        SQLTDAL	remoteReadSrvrFile(	SQLTFLH hFile, 
						            char* pBuffer, 
						            SQLTDAL nBuffLen);	
             
        void	remoteDeleteSrvrFile(const char* szFileName);
            			
// miscellaneous..
        void	changeProcessActivityLogFile(const char* szLogFileName, 
        									 SQLTFMD startflag = 0);
protected:                
		SQLTSVH	m_sHandle;
		BOOL	m_bConnected; 
		CString	m_szSvrId;
		CString	m_szPwd;   
		
private:
	// we don't allow these things...
	const CSqlServer& operator=(const CSqlServer&){return *this;}
	CSqlServer(const CSqlServer&){}
};

#include "csqlsrvr.inl"
   
#endif    
