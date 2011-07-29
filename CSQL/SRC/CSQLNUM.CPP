#include "stdincs.h"
#include "csqltype.h"
#include "csqlnum.h"       

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlNumber 
  
const CSqlNumber& CSqlNumber::operator=(const CSqlNumber& rNum2)
{
	if (&rNum2 != this){
		m_data = rNum2.m_data;	
		}
	return *this;
}

DWORD CSqlNumber::dataLength()
{           
	DWORD bytes;
	
	switch(m_BindType){
		case SQLPSIN:
	    	bytes = sizeof(int);
	    	break;
		case SQLPDOU:
	    	bytes = sizeof(double);
	    	break;
		case SQLPFLT:
	    	bytes = sizeof(float);
	    	break;
		case SQLPSLO:
	    	bytes = sizeof(long);
	    	break;
		case SQLPUIN:
	    	bytes = sizeof(unsigned int);
	    	break;
		case SQLPULO:
	    	bytes = sizeof(unsigned long);
	    	break;
		case SQLPSSH:
	    	bytes = sizeof(short);
	    	break;
		case SQLPUSH:
	    	bytes = sizeof(unsigned short);
	    	break;
		default:
			TRACE0("unknown numeric bind type..!\n");
			ASSERT(FALSE);
			break;
	}
	return bytes;	
}
	
SQLTDAP	CSqlNumber::dataBuffer()
{
	SQLTDAP bp;     	
	
	switch(m_BindType){ 
		case SQLPSIN:
	    	bp = (SQLTDAP)&m_data.Int;
	    	break;
		case SQLPDOU:
	    	bp = (SQLTDAP)&m_data.Double;
	    	break;
		case SQLPFLT:
	    	bp = (SQLTDAP)&m_data.Float;
	    	break;
		case SQLPSLO:
	    	bp = (SQLTDAP)&m_data.Long;
	    	break;
		case SQLPUIN:
	    	bp = (SQLTDAP)&m_data.UInt;
	    	break;
		case SQLPULO:
	    	bp = (SQLTDAP)&m_data.ULong;
	    	break;
		case SQLPSSH:
	    	bp = (SQLTDAP)&m_data.Short;
	    	break;
		case SQLPUSH:
	    	bp = (SQLTDAP)&m_data.UShort;
	    	break;
		default:
			TRACE0("unknown numeric bind type..!\n");
			ASSERT(FALSE);
			break;
	}
	return bp;	
}
