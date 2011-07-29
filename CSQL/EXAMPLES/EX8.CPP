//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 8
//	This example demonstrates the 'smart-command' class
//	1. the first smart command creates a table
//	2. the second smart command is used to pipe two bitmaps into a long varchar column.
//	3. the first smart command is re-associated with another command that drops the table.

#include <csql.h>  
#include "csqlscmd.h"

void main()
{
   CSqlCursor	con1("demo");

	TRY{

		CFile		firstBitmap("c:\\csql\\examples\\dump\\walogo.bmp");
		CFile		secondBitmap("c:\\csql\\examples\\dump\\winaps.bmp");

		CSqlSmartCommand myCreator(con1, "create table test(a long varchar)"); 
		
		CSqlSmartCommand myInsertor(con1, "insert into test(a) values (:1)"); 
		
	  	myInsertor << firstBitmap << secondBitmap;

		// all done...2 rows inserted...
		
		// associate the creator with a new command to drop the table..		
		myCreator.associateWith("drop table test");
		
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
	