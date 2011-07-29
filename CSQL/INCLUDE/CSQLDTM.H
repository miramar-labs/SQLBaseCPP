//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
// 	csqldtm.h	: 	header for class CSqlDateTime
// 
//	Author		:	Aaron Cody
//	Date		:	4th January 1994   
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:	
//

#ifndef CSQLDTM_H
	#define CSQLDTM_H

class CSqlDateTime : public CSqlType
{
	friend class CSqlSelect; 
	friend class CSqlCommand;
	
public: 
// construction ...
    // TIME only ... 
	CSqlDateTime(int hour, int mins, int sec, unsigned int msecs);
	
	// DATE only ...
	CSqlDateTime(int year, int month, int day);
	
	// DATETIME ...
	CSqlDateTime(int year, 
				 int month, 
				 int day, 
			  	 int hours, 
				 int mins, 
				 int secs = 0, 
				 unsigned int msecs = 0);      
	
	// from an MFC CTime object (not with DLL's)			 
	CSqlDateTime(const CTime& mfcTime);
    
    // copy _ctor..
	CSqlDateTime(const CSqlDateTime& rDateTime);
	
	// default _ctor..
	CSqlDateTime();
	
	// destructor..				 
	virtual ~CSqlDateTime(){}

    // access members... 
    CString	asSqlTimeStr() const;  
    
    // identification..(DATE only, TIME only or DATETIME..) 
    enum sub_type {csqlDateOnly, csqlTimeOnly, csqlTimeStamp};
    
    sub_type csqlSubType(void) const;
    
	// assignment..
	const CSqlDateTime& operator=(const CSqlDateTime& rDateTime);

private:
    CString		m_SqlTime;	// date/time in string format...
    sub_type	m_subType;
    
	// some pure virtual implementations..
	virtual DWORD	dataLength();
	virtual SQLTDAP	dataBuffer(); 
};  

#include "csqldtm.inl"

#endif       
