//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlinum.h	: 	header for class CSqlInternalNumber
//	        
//	Author		:	Aaron Cody
//	Date		:	4th January 1994  
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:

#ifndef CSQLINUM_H
	#define CSQLINUM_H

class CSqlInternalNumber : public CSqlType
{
	friend class CSqlCommand;
	friend class CSqlSelect; 
	
public:     
// construction/destruction..
	// from an existing CSqlNumber object...
	CSqlInternalNumber(const CSqlNumber& rNumber);   
	
	// copy _ctor..	
	CSqlInternalNumber(const CSqlInternalNumber& rIntNumber);	              
	
	// def _ctor...
	CSqlInternalNumber();	
	
	virtual ~CSqlInternalNumber(){}   
	 	
 // conversion to string, according to a given format string
 	CString	asPictureStr(const char* szFmt);
	
// transform this object into another internal numeric given a numeric string..
	BOOL fromString(const char* szNumericStr);
	 	
// extended add/subtract/multiply/divide
	friend CSqlInternalNumber operator+(const CSqlInternalNumber& a, const CSqlInternalNumber& b);
	friend CSqlInternalNumber operator-(const CSqlInternalNumber& a, const CSqlInternalNumber& b);
	friend CSqlInternalNumber operator*(const CSqlInternalNumber& a, const CSqlInternalNumber& b);
	friend CSqlInternalNumber operator/(const CSqlInternalNumber& a, const CSqlInternalNumber& b); 

// assignment..
	const CSqlInternalNumber& operator=(const CSqlInternalNumber& rStr);
	 
private:   
	char	m_internal[SQLSNUM];	// internal SQLBase rep.
	SQLTAPI	m_nIntNumLen;         	// rep length
				
	// pure virtual implementations..
	virtual DWORD	dataLength();
	virtual SQLTDAP	dataBuffer();      
};

#include "csqlinum.inl"

#endif
