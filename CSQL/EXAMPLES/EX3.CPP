//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 3
//	This example demonstrates the following :
//	1. 	connection to a database
//	2. 	creating a table with CHAR and LONG VARCHAR columns 
//	3. 	the usual compile/bind/execute cycle...
//	4. 	inserting string values into the CHAR column (both constant & bind vars.)
//	5. 	inserting a bitmap file into the LONG VARCHAR column.
//	6. 	inserting an external byte buffer into the LONG VARCHAR column.
//	7. 	a select-all on the table
//	8. 	fetching the bitmap from the LONG VARCHAR column and dumping it out to
//	   	another file..            
//	9.	associating the creator object with a new command statement to drop the table.
//	10.	the usual simple exception handling strategy & automatic disconnection.

// 	#include <csql.h>

CSqlCursor	con1("demo");
			
	TRY{

		CSqlCommand myCreator(con1, "create table test(a char(50), b long varchar)"); 
				
		CSqlCommand myInsertor(con1, "insert into test(a, b) values (:1, :2)"); 
				
		CSqlSelect mySelector(con1, "select * from test"); 

		// connect to demo...
		con1.connect();
		
		// no binds so compile & execute in one step..
		myCreator.compileAndExecute(); 
		
		// put some bind variables into the insertor object..
		CString	aString("c:\\csql\\examples\\dump\\acopy.bmp"); 
		
		CFile 	aBitmap("c:\\csql\\examples\\dump\\walogo.bmp", CFile::modeRead);  
		
		myInsertor.compile();
		
	  	myInsertor << aString << aBitmap;

		myInsertor.bind();
		
		myInsertor.execute(); 	// all done... 
		
		// insert another row of data...
		
		// allocate an 'external' buffer (ie external to the object)
		char aBuffer[1000]; 
		
		memset(aBuffer, 0, sizeof(aBuffer));
		 
		CSqlLongVarChar	anExternalBuffer((LPBYTE)aBuffer, sizeof(aBuffer)); 
		
		strcpy(aBuffer, "some meaningful text.....");	
		
		myInsertor.replaceBind(0, "c:\\csql\\examples\\dump\\buffer.txt");

		myInsertor.replaceBind(1, anExternalBuffer);

		myInsertor.bind();
		
		myInsertor.execute(); 	// all done... 	
		
		// now let's do some fetching.......
	    mySelector.compileAndExecute();
	    
	    CSqlRow*  pRow;
	    
	    while (mySelector.fetchRow(pRow)){
	    
    		CString szFilename = pRow->stringColumn(0);   
    		
    		// create a new file and dump the bitmap out to it...
    		CFile aCopy(szFilename, 
    					CFile::modeCreate|CFile::modeWrite);   
    		
    		pRow->longVarCharColumn(1)->toFile(aCopy);
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

