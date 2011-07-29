//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlnum.h	: 	header for class CSqlNumber
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994  
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:

#ifndef CSQLNUM_H
	#define CSQLNUM_H

class CSqlNumber : public CSqlType
{ 
	friend class CSqlCommand;
	friend class CSqlSelect;
	
public:   
// construction/destruction...	
	// from standard C++ numeric types...
	CSqlNumber(short sVal);             
	CSqlNumber(unsigned short usVal);
	CSqlNumber(long lVal);
	CSqlNumber(unsigned long ulVal); 
	CSqlNumber(double dVal);
	CSqlNumber(float fVal); 
	CSqlNumber(int nVal);
	CSqlNumber(unsigned int uiVal);
	                                        
	// copy _ctor..	                                        
	CSqlNumber(const CSqlNumber& rNumber);	
	
	// default _ctor..
	CSqlNumber();
	 
	virtual ~CSqlNumber(){}   
    
// assignment..
	const CSqlNumber& operator=(const CSqlNumber& rAnother);
    
// conversion back to C++ types....
	operator short() const;
	operator unsigned short() const;
	operator double() const;
	operator float() const;
	operator long() const;
	operator unsigned long() const;
	operator int() const;
	operator unsigned int() const;  
	
private:          
    // data..
	union _numericData{
			short 			Short;
			unsigned short 	UShort;
			float			Float;
			double			Double;
			long			Long;
			unsigned long	ULong;
			int				Int;   
			unsigned int	UInt;
	}m_data;
			
	// pure virtual implementations..
	virtual DWORD	dataLength(); 
	virtual SQLTDAP	dataBuffer();  
};       

#include "csqlnum.inl"

#endif    
