//////////////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//  csqlrow.h	: 	header for class CSqlRow   
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994    
//	Version		:	SQLBase++ v1.1	  
//	Remarks		:
//

#ifndef CSQLROW_H
	#define CSQLROW_H

class CSqlRow : public CObArray
{
public: 
// construction/destruction..
			CSqlRow(){}
	virtual ~CSqlRow(){} 
	
// retrieval as specific data object types...
    CSqlNumber&				numericColumn(int nIndex) const;
    CSqlString&				stringColumn(int nIndex) const;
	CSqlLongVarChar* 		longVarCharColumn(int nIndex) const;  
	CSqlDateTime* 			dateTimeColumn(int nIndex) const;  
	CSqlInternalDate		internalDateColumn(int nIndex) const;	
	CSqlInternalNumber		internalNumericColumn(int nIndex) const;	
 
// retrieval as general data object types...    
	CSqlType*	operator[](int nIndex) const; 
	CSqlType* 	getColumn(int nIndex) const;
	
// miscellaneous..
	int	numColumns(void) const;
}; 

#include "csqlrow.inl"

#endif


