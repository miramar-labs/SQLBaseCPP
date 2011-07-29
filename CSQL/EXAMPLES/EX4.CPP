//	Author:		Aaron Cody
//	Date:		21-8-93
//	Comments:   Example 4
//	This example demonstrates the following :
//	1. 	connection to a database
//	2. 	creating a table with numeric SQLBase columns 
//	3. 	creating & doing math on internal numeric's
//	4. 	inserting internal numerics into the table 
//	5.  fetching them back..also as internal numbers & converting to picture string
//	6.	associating the creator object with a new command statement to drop the table.
//	7.	the usual simple exception handling strategy & automatic disconnection.

//	#include <csql.h> 

CSqlCursor	con1("demo");

	TRY {
			
		CSqlCommand myCreator(con1, "create table numeric(a number)"); 
				
		CSqlCommand myInsertor(con1, "insert into numeric(a) values (:1)"); 
				
		CSqlSelect mySelector(con1, "select * from numeric"); 

		// connect to demo...
		con1.connect();
		
		// no binds so compile & execute in one step..
		myCreator.compileAndExecute(); 
		
		myInsertor.compile();

		// do some maths...
		CSqlInternalNumber 	v6; 
		
		v6.fromString("123.45678");
		
		CString szV6 = v6.asPictureStr("999.9999999");
				
		CSqlInternalNumber 	v1(19.5);
		CSqlInternalNumber 	v2(2.5);
		CSqlInternalNumber 	v3(2);
		CSqlInternalNumber 	v4(4);
		CSqlInternalNumber 	v5(1);
        
        v6 = v3 * v4;
        
        szV6 = v6.asPictureStr("9.9999999");
        
		myInsertor << (v1 + v2) / (v3 * v4 - v5);
		
		myInsertor.bind();
		
		myInsertor.execute(); 	// all done...   
		
		// now let's do some fetching.......
	    mySelector.compileAndExecute();
	    
	    CSqlRow*  pRow;
	    
	    while (mySelector.fetchRow(pRow)){
	    
    		double val = pRow->numericColumn(0);   
    		
    		CSqlInternalNumber inum = pRow->internalNumericColumn(0);
    		
    		szV6 = inum.asPictureStr("9.999999999");
    		
    		TRACE("result = %f, %s\n", val, (const char*)szV6);
    		}	             

		// associate the creator with a new command to drop the table..		
		myCreator.associateWith("drop table numeric");
		
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
	