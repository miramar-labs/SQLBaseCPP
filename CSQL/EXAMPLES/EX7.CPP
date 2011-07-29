//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 7
//	This example demonstrates the following :
//	1. 	connection to a local server
//	2. 	getting a list of databases 
//	3.  backing up one of them  
//	4.  deinstalling & deleting it...
//	5.  creating & installing a new database
//	6.  restoring the backed-up database            
//	7.  disconnecting from the server
//	8.	the usual simple exception handling strategy
//
// #include <csql.h>

	CSqlServer		srvr;
	CStringArray  	dbNames;
	
 	TRY{
 		    
		// connect to srvr...
		srvr.connect();
		
		if (srvr.databaseNames(dbNames)){
		    // we have at least one name in the array...
		    
		    // back up the first one...
		    srvr.backupSnapShot(dbNames[0], "backup");
			
			// deinstall it now...	
			srvr.deInstallDatabase(dbNames[0]);	    
			
			// delete it...
			srvr.deleteDatabase(dbNames[0]);	  
			
			// create a new database....
		    srvr.createDatabase("Mette");
		    
		    // install it....
		    srvr.installDatabase("Mette");
		    
		    // restore the old one anyway..  
			srvr.restoreSnapShot(dbNames[0], "backup");
			}
		}	 
	CATCH(CSqlException, e){  
		// take a look at whatever it was that went wrong...
		csqlSeeWhatHappened(e);                             
		
		// try resoring the original database...
		TRY{ 
		
			srvr.restoreSnapShot(dbNames[0], "backup"); 
			
		}CATCH(CSqlException, e){
		    // oh dear !
			csqlSeeWhatHappened(e);  
			::AfxMessageBox("unable to restore database !", MB_OK);
			THROW_LAST();	
				
		}END_CATCH						
		
	}END_CATCH 
