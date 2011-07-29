//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 5 : 
//	This example demonstrates the following :
//	1. 	connection to a database
//	2. 	creating a table with DATE, TIME & DATETIME SQLBase columns 
//	3. 	creating CSqlDateTime objects to represent date, time and datetime values - 
//	4.  inserting the values into the table
//	5.  creating an internal date object from an MFC CTime object, adding a number 
//		of days to it then converting to a picture string..
//	6. 	inserting more values...
//	7.  fetching them all back..
//	8.	associating the creator object with a new command statement to drop the table.
//	9.	the usual simple exception handling strategy & automatic disconnection.

//	#include <csql.h>

CSqlCursor	con1("demo");

	TRY{
			
		CSqlCommand myCreator(con1, "create table test(a date, b time, c datetime)"); 
		
		CSqlCommand myInsertor(con1, "insert into test(a, b, c) values (:1, :2, :3)"); 
			
		CSqlSelect mySelector(con1, "select * from test"); 
	
		// connect to demo...
		con1.connect();
		
		// no binds so compile & execute in one step..
		myCreator.compileAndExecute(); 
		
		myInsertor.compile();
		
		CSqlDateTime v1(1966, 9, 18); 				// y-m-d  			.. date only
		
		CSqlDateTime v2(6, 30, 21, 0);				// h-m-s-ms 		.. time only..
		
		CTime v3(1993, 12, 18, 13, 47, 49);			// MFC time object
		
		myInsertor << v1 << v2 << v3;
		
		myInsertor.bind();
		
		myInsertor.execute(); 	// all done... 
		
		// some sums...
		CSqlInternalDate id1(v3); 
		
		CSqlInternalDate id2 = id1 + 20;     // add 20 days to the MFC object
		
		CString szid2 = id2.asPictureStr("Mon.dd.yyyy");
		
		// now for some date sums...
		CSqlInternalDate idate("18th September 1966", "DD   MON       YYYY");
				                   
		idate += 5;	// add 5 days to the internal date..
		
		myInsertor.replaceBind(0, idate + 3);		// add another 3 days...

		myInsertor.bind();
		
		myInsertor.execute(); 	// all done... 
		
		// now let's do some fetching.......
	    mySelector.compileAndExecute();

	    CSqlRow*  pRow;
	    
	    while (mySelector.fetchRow(pRow)){
	    
    		CString szDate = pRow->dateTimeColumn(0)->asSqlTimeStr();  
    		 
    		CString szTime = pRow->dateTimeColumn(1)->asSqlTimeStr();
    		
    		CString szDateTime = pRow->dateTimeColumn(2)->asSqlTimeStr(); 
    		  
    		TRACE1("date = %s\n", (const char*)szDate);   
    		TRACE1("time = %s\n", (const char*)szTime);
    		TRACE1("timestamp = %s\n", (const char*)szDateTime);
    		}	             

		// associate the creator with a new command to drop the table..		
		myCreator.associateWith("drop table test");
		
		myCreator.compileAndExecute(); 		
        
        // all done...
		// the cursor object will disconnect automatically as we exit scope...
		}	 
	CATCH(CSqlCsrException, e){ 
	
    	csqlSeeWhatHappened(e);   
	 
		// try rolling back cursor..
	    TRY{
		    
    		con1.rollback();
	    		
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

