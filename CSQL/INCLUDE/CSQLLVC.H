//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqllvc.h	: 	header for class CSqlLongVarChar
// 
//	Author		:	Aaron Cody
//	Date		:	4th January 1994   
//	Version		:	SQLBase++ v1.2	  
//  Remarks		:     
//

#ifndef CSQLLVC_H
	#define CSQLLVC_H

class CBufferRep;	// fwd declaration of private internal class

class CSqlLongVarChar : public CSqlType
{
	friend class CSqlCommand;
	friend class CSqlSelect;
	
public:     
// construction/destruction..
	// with external buffer....(no memory allocated by this object)
	CSqlLongVarChar(LPBYTE lpBytes, DWORD dwBytes);
	
	// with internal buffer ...(open file read into internal buffer)
	CSqlLongVarChar(CFile& rFile); 

	// smart copy _ctor 			                               
	CSqlLongVarChar(const CSqlLongVarChar& rLvc);	
	
	// def _ctor..
	CSqlLongVarChar();	
	
	virtual ~CSqlLongVarChar();

// conversions..
	void	toFile(CFile& rFile); 		// dumps out to a file...
	operator LPBYTE(); 

	
// buffer functions..
	DWORD	bufferLength() const; 		// bytes allocated (internal or external)
	LPBYTE	bufferPointer(); 			// pointer to bytes (internal or external) 

// smart assignment..
	const CSqlLongVarChar& operator=(const CSqlLongVarChar& rStr);
	
private:
	// pure virtual implementations..
	virtual DWORD	dataLength();
	virtual SQLTDAP	dataBuffer();
    
    // for externally allocated buffers..
	LPBYTE	m_lpExternalBuffer;			 
	DWORD	m_dwExternalAllocLength;
	
	// for internally allocated buffer..
	CBufferRep*	m_pRep;		  
	BOOL		m_bAllocInternal;
};   

class CBufferRep	// set up like this to emulate a private nested class..
{
private:
	friend class CSqlLongVarChar; 
	friend class CSqlSelect;
	// data..
	LPBYTE	m_lpInternalBuffer;		
	DWORD	m_dwInternalAllocLength;
	int 	m_nUseCount;
    	
	// construction/destruction..   
    CBufferRep();              
	virtual ~CBufferRep();                  
    
	// functions. 
	void	increment();
	void	decrement();   
	DWORD	growByteBuffer(DWORD dwNewSize);   // (>= 0 bytes)
};

#include "csqllvc.inl"

#endif        
