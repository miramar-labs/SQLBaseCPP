//	Author:		Aaron Cody
//	Date:		2-2-94
//	Comments:   Example 1
//				Note how we catch more the derived exception class first..
//
//	This example demonstrates the following :
//	1. connection to a database
//	2. creating a table with various SQLBase column types
//	3. inserting various kinds of data into the table (also using 'binds') 
//	4. example of replacing binds , re-binding & re-executing to insert another row. 
//	5. example of associating a command with another statement....
//	4. disconnecting from the database

//  #include <csql.h>

// create a cursor object and specify the database 'demo.dbs'
CSqlCursor	con1("demo");

	TRY{
		// create a command object to do the table-creating..associating it with the
		// cursor and a vaild SQL statement...	
		// Now we are ready to operate on the database 
	
		CSqlCommand myCreator(con1, "create table employee("
								"empno int not NULL,"
								"soc_sec_no char (11),"
								"lname varchar (25),"
								"fname char (10),"
								"mname char (10),"
								"deptno smallint,"
								"hiredate date,"
								"interview_comments long varchar)");
			                                                                            
		// Now for the data insertion, create another command object (note: we could use 
		// the command object we already have..just by associating it with the insert 
		// statement string that follows..)
		CSqlCommand myInsertor(con1, "insert into employee(empno, soc_sec_no, lname, "
									  "fname, mname, deptno, hiredate, interview_comments"
									  ") values (:1, :2, :3, :4, :5, :6, :7, :8)"); 
		
	    		                                         
		// try connecting to the database (demo)...
		con1.connect();
		
		// the table-creator doesn't involve binds, so we can compile and execute
		// in one go..
		myCreator.compileAndExecute();
		                                     
		myInsertor.compile();
		                                                  
		// Now we insert some values into the table...
		int				a = 1;
		CString			soc_sec = "8797-7827";
		CFile 			aFile("c:\\csql\\examples\\ex6.wts", CFile::modeRead);
		CSqlDateTime	aDate(1966, 9, 18);
		
		// associate the values....(in the right column order)
	  	myInsertor << a << soc_sec << "Cody" << "Aaron" << "marmaduke";     
	  	myInsertor << 3 << aDate << aFile;
        
		// bind the data...
		myInsertor.bind();
		
		// do the insert...	
		myInsertor.execute(); 
		
		// change one of the values..this causes the object to become 'un-bound'..
		myInsertor.replaceBind(4, "John");
        
        // rebind
		myInsertor.bind();
		
		// do the insert again...	
		myInsertor.execute(); 
		
		// associate the creator object with another SQL statement..
		myCreator.associateWith("drop table employee");
		
		// drop the table....		
		myCreator.compileAndExecute();
		
		// all done.. (the cursor will disconnect automatically)
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

