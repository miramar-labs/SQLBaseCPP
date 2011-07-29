//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 6
//				****** IMPORTANT : run 'ex6.wts' over demo from SqlTalk first...*******
//	This example demonstrates the following :
//	1. 	connection to a database
//	2. 	piping the results of a select into an insert...
//	3.	the usual simple exception handling strategy & automatic disconnection.

//	#include <csql.h>  

CSqlCursor	con1("demo");
		
CSqlCursor	con2("demo");

	TRY{
		CSqlSelect mySelector(con1, "select e_year, candidate from elections where winOrLose = 'W'"); 
			
		CSqlCommand myInsertor(con2, "insert into winners(e_year, candidate) values (:1, :2)"); 
	
		// connect to demo...
		con1.connect(); 
		
		con2.connect();
		
		// pipe the select into the insertor
		mySelector >> myInsertor; 
		
		// change the select to look at table 'winners'....
		mySelector.associateWith("select * from winners");

		mySelector.compileAndExecute();
				
		// fetch the piped values back....
		CSqlRow*	pRow;
		
	    while (mySelector.fetchRow(pRow)){
	    
    		short nYear = pRow->numericColumn(0); 
    		 
    		CString szCandidate = pRow->stringColumn(1);
    		  
    		TRACE("%s won in %d\n", (const char*)szCandidate, nYear);
    		}	             

		// the cursor objects will disconnect automatically as we exit scope...   
		}	 
	CATCH(CSqlCsrException, e){ 
	
    	csqlSeeWhatHappened(e);   
	 
		// try rolling back cursor..
	    TRY{
		    
    		con1.rollback();
			con2.rollback();
	    		
		}CATCH(CSqlCsrException, e){    
			
			// rollback failed...
			::AfxMessageBox("Rollback failed...", MB_OK); 
				 
			// could try to perform further recovery...
			// we just throw it on to the MFC..
			THROW_LAST();                      
				
		}END_CATCH
			
	}AND_CATCH(CSqlException, e){ 
	 
		// simple exception..just display info in message boxes...
		csqlSeeWhatHappened(e); 
		                           
	}END_CATCH

