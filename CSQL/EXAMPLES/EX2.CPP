//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 2
//	This example demonstrates the following :
//	1. connection to a database
//	2. creating a table with various SQLBase numeric column types
//	3. inserting values into the table
//	4. fetching them back
//	5. example of associating a command with another statement....
//	

//	#include <csql.h>

CSqlCursor	con1("demo");

	TRY{
			
		CSqlCommand myCreator(con1, "create table numeric(a number , b dec, c int,"
									"d smallint, e double precision, f float,"
									"g real)"); 
				
		CSqlCommand myInsertor(con1, "insert into numeric(a, b, c, d, e, f, g) "
									 "values (:1, :2, :3, :4, :5, :6, :7)"); 
				
		CSqlSelect 	mySelector(con1, "select * from numeric");     
	
		   	
		// connect to the database..
		con1.connect();
		
		// create the table...
		myCreator.compileAndExecute();

		// insert values into the table....		
		myInsertor.compile();
		
	  	myInsertor << 11 << 22 << 33 << 44 << 55 << 66 << 77;
        
		myInsertor.bind();
			
		myInsertor.execute();	// 1st row inserted  
		
        // insert more values.. this time demonstrating binding program variables..
        
        myInsertor.deleteAllBinds();	// reset the object's previous bind data..

		// nb: all of these C++ types will result in the construction of
		//     a CSqlNumber object...at this stage you don't need to worry too
		//	   much about things like 'is it ok to put an int into a NUMBER column..?'
		//	   because SQLBase will do any conversions on the data if it needs to 
		//	   (if it can) before inserting - obviously you need to think about
		//	   overflow etc...eg if you try inserting an unsigned long into a SMALLINT
		//	   column, SQLBase will not be able to do any last minute conversions and
		//	   may complain (or just insert garbage).
        int				v1 = 12345;
        double 			v2 = 12.34567;
        float			v3 = -1.234567;
        short			v4 = -123;
        long			v5 = 9876543;
        unsigned int	v6 = 54321;
        unsigned long	v7 = 3987654321;

        myInsertor << v1 << v2 << v3 << v4 << v5 << v6 << v7;

		myInsertor.bind();
			
		myInsertor.execute();	// 2nd row inserted  
        
        // okay..now let's fetch them all back..
        // nb: when fetching data back you have to match the SQLBase
        // column types to C++ types properly...
        
        mySelector.compileAndExecute();
                
	    CSqlRow*  pRow;
	    
	    while (mySelector.fetchRow(pRow)){
				    
			// nb: NUMBER columns come back as C++ double's ... 	    
    		double 	vv1 = pRow->numericColumn(0);	
    		                                                        
			// nb: DECIMAL/DEC columns come back as C++ double's ... 	    
    		double 	vv2 = pRow->numericColumn(1);	

			// nb: INTEGER columns come back as C++ long's ...(see note *) 	    
    		long 	vv3 = pRow->numericColumn(2);	
    		                                                        
			// nb: SMALLINT columns come back as C++ short's ...	    
    		short 	vv4 = pRow->numericColumn(3);	

			// nb: DOUBLE PRECISION columns come back as C++ double's ...	    
    		double 	vv5 = pRow->numericColumn(4);	

			// nb: FLOAT columns come back as C++ double's ..    
    		double 	vv6 = pRow->numericColumn(5);	

			// nb: REAL columns come back as C++ float's ...    
    		float 	vv7 = pRow->numericColumn(6);	
    		
    		}	             
        
        // finally we show how to associate a command object with another
        // SQL statement (in this case to drop the table)...        
		myCreator.associateWith("drop table numeric");                
		
		myCreator.compileAndExecute();
				                                            
		// all done...
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

