//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqltype.h	: 	header for class CSqlType (abstract)
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994   
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:

#ifndef CSQLTYPE_H
	#define CSQLTYPE_H

class CSqlType : public CObject
{
	friend class CSqlCommand;	
	friend class CSqlSelect;   
	
public:	
// The following enum values identify the exact type of a data object :
	enum obj_type{
		csqlInvalid = 0,	// invalid type	
		csqlString,			// string data object (length < 255)  
		csqlLongVarChar,	// long varchar (BLOB) data object
		csqlInt ,			// numeric (integer) data object
		csqlDouble,			// numeric (double) data object
		csqlFloat ,  		// numeric (float) data object
		csqlLong,			// numeric (long) data object	
		csqlULong,			// numeric (unsigned long) data object 		
		csqlUInt,			// numeric (unsigned integer) data object 	
		csqlShort,			// numeric (short) data object	
		csqlUShort,			// numeric (unsigned short) data object	
		csqlDateTime,		// date/time/timestamp data object		
		csqlIntNum,			// internal numeric data object	 
		csqlIntDate			// internal date data object
		}; 
						
// Run-time info: gets the above type enum for a CSqlType object...
	obj_type csqlObjType() const;

protected:
// pure virtuals to be implemented in derived classes...
	virtual DWORD	dataLength() = 0; 
	virtual SQLTDAP	dataBuffer() = 0;
	
// type info..
			SQLTPDT		m_BindType;  	               
            obj_type	m_ObjType;
            
// construction/destruction...
	CSqlType(SQLTPDT b_type, obj_type o_type = csqlInvalid);
	virtual ~CSqlType(){}
};           

#include "csqltype.inl"
	   
#endif  
