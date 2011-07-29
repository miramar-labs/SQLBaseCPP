//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 9
//	This example demonstrates the 'smart-select' class
//	1. a smart command is used to create a table
//	2. another smart command is used to insert two rows into it.
//	3. a smart selector is used to select one of the rows.
//	4. the row is fetched.
//	5. the first smart command is re-associated with a command to drop the table.

#include <csql.h>
#include "csqlscmd.h"
#include "csqlssel.h"

void main()
{
   CSqlCursor	con1("demo");

	TRY{

		CSqlSmartCommand myCreator(con1, "create table test(a char(50), b integer)");
		
		CSqlSmartCommand myInsertor(con1, "insert into test(a, b) values (:1, :2)"); 
		
	  	myInsertor << "Some junk...." << 3;

		myInsertor << "Some more junk....." << 2;
				
		// all done...2 rows inserted...

		// now let's check it by doing some fetching.......
		CSqlSmartSelect mySelector(con1, "select a from test where b = :1"); 
        
        mySelector << 2;
        
	    CSqlRow*  pRow;
	    
	    while (mySelector.fetchRow(pRow)){

    		CString szText = pRow->stringColumn(0);  
    		 
    		}	             

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
}