//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlstr.h	: 	header for class CSqlString
//    
//	Author		:	Aaron Cody
//	Date		:	4th January 1994    
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:

#ifndef CSQLSTR_H
	#define CSQLSTR_H

class CSqlString : public CSqlType
{
	friend class CSqlSelect;
	friend class CSqlCommand; 
	
public:     
// construction/destruction... 
	// from an MFC CString object..
	CSqlString(const CString& rStr); 
    
    // copy _ctor..     
	CSqlString(const CSqlString& rString); 
	
	// default _ctor..
	CSqlString(const char* pStr = "");
	                                    
	virtual ~CSqlString(){} 

// conversions..
	operator const char*() const; 

// assignment..
	const CSqlString& operator=(const CSqlString& rAnother);
	 
private: 
	CString	m_data;	
	
	// pure virtual implementations..
	virtual DWORD	dataLength(); 
	virtual SQLTDAP	dataBuffer();
};    

#include "csqlstr.inl" 

#endif        
