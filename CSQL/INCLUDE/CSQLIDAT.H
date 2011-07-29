//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlidat.h	: 	header for class CSqlInternalDate
//	   
//	Author		:	Aaron Cody
//	Date		:	4th January 1994  
//	Version		:	SQLBase++ v1.2  
//	Remarks		:	
//
   
#ifndef CSQLIDAT_H
	#define CSQLIDAT_H

// Fwd declaration..
class CSqlDateTime;

class CSqlInternalDate : public CSqlType
{ 
	friend class CSqlCommand;
	friend class CSqlSelect;
	  
public: 
// construction/destruction..
    // from an existing CSqlDateTime object...
	CSqlInternalDate(const CSqlDateTime& rDateTime);           
	
	// from an arbirary input string & corresponding format picture string ...
   	CSqlInternalDate(const CString& rInputStr, const CString& rFmtStr);       
   	
   	// copy _ctor					 
	CSqlInternalDate(const CSqlInternalDate& rIDate); 
	
	// default _ctor..
	CSqlInternalDate();

	virtual ~CSqlInternalDate(){}

 // conv.to picture string..(from internal rep.)
 	CString	asPictureStr(const CString& rFmt);
	 	
// extended date addition (a number of days...)  
	friend CSqlInternalDate operator+(const CSqlInternalDate& a, int nDays);
	friend CSqlInternalDate operator+(int nDays, const CSqlInternalDate& a);
	CSqlInternalDate& operator+=(int nDays);		

// assignment.. 
	const CSqlInternalDate& operator=(const CSqlInternalDate& rStr);
	
private:         
	char	m_internal[SQLSDAT];	// internal SQLBase rep.
	SQLTAPI	m_nIntDTLen;          	// rep length
				
	// pure virtual implementations..
	virtual DWORD	dataLength();
	virtual SQLTDAP	dataBuffer();    
}; 

#include "csqlidat.inl"

#endif

