#include "stdincs.h"
#include "csqltype.h"
#include "csqlstr.h"

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlString  

const CSqlString& CSqlString::operator=(const CSqlString& rStr2)
{
	if (&rStr2 != this){
		m_data = rStr2.m_data;	
		}
	return *this;
}


