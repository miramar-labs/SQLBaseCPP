#include "stdincs.h"
#include "csqlcur.h"
#include "csqlexep.h"


#include "csqltype.h"
	#include "csqlnum.h"
	#include "csqlinum.h"    

#define MAX_NUMERICDIGITS 30   

///////////////////////////////////////////////////////////////////
//
//	CSqlInternalNumber friends

CSqlInternalNumber operator+(const CSqlInternalNumber& a, const CSqlInternalNumber& b)
{
	CSqlInternalNumber result;
	   
	VERIFY((result.m_nIntNumLen = ::sqlxad( (SQLTNMP)result.m_internal, 
											(SQLTNMP)a.m_internal,
											(SQLTNML)a.m_nIntNumLen,
											(SQLTNMP)b.m_internal,
											(SQLTNML)b.m_nIntNumLen )) > 0);
	return result;									 
	}

CSqlInternalNumber operator-(const CSqlInternalNumber& a, const CSqlInternalNumber& b)
{
	CSqlInternalNumber result;
	   
	VERIFY((result.m_nIntNumLen = ::sqlxsb( (SQLTNMP)result.m_internal, 
											(SQLTNMP)a.m_internal,
											(SQLTNML)a.m_nIntNumLen,
											(SQLTNMP)b.m_internal,
											(SQLTNML)b.m_nIntNumLen )) > 0);
	return result;									 
	}

CSqlInternalNumber operator*(const CSqlInternalNumber& a, const CSqlInternalNumber& b)
{
	CSqlInternalNumber result;
	   
	VERIFY((result.m_nIntNumLen = ::sqlxml( (SQLTNMP)result.m_internal, 
											(SQLTNMP)a.m_internal,
											(SQLTNML)a.m_nIntNumLen,
											(SQLTNMP)b.m_internal,
											(SQLTNML)b.m_nIntNumLen )) > 0);
	return result;									 
	}

CSqlInternalNumber operator/(const CSqlInternalNumber& a, const CSqlInternalNumber& b)
{
	CSqlInternalNumber result;
	   
	VERIFY((result.m_nIntNumLen = ::sqlxdv( (SQLTNMP)result.m_internal, 
											(SQLTNMP)a.m_internal,
											(SQLTNML)a.m_nIntNumLen,
											(SQLTNMP)b.m_internal,
											(SQLTNML)b.m_nIntNumLen )) > 0);
	return result;									 
	}

///////////////////////////////////////////////////////////////////
//
//	CSqlInternalNumber...

const CSqlInternalNumber& CSqlInternalNumber::operator=(const CSqlInternalNumber& rAnother)
{                   
	// assignment operator...
	if (&rAnother != this){
		m_nIntNumLen = rAnother.m_nIntNumLen;
		strncpy(m_internal, rAnother.m_internal, sizeof(m_internal));
	}
	return *this;
}

CSqlInternalNumber::CSqlInternalNumber(const CSqlInternalNumber& a) 
	:CSqlType(a.m_BindType, a.m_ObjType)
{  
	// copy _ctor...
	m_nIntNumLen = a.m_nIntNumLen;
	strncpy(m_internal, a.m_internal, sizeof(m_internal));
}

CSqlInternalNumber::CSqlInternalNumber(const CSqlNumber& a)
	:CSqlType(SQLPNUM, csqlIntNum), m_nIntNumLen(0) 
{
	// convert number to internal form....
	// first we need it as a string....
	char temp[MAX_NUMERICDIGITS];
		
	switch(a.csqlObjType()){                    
		case CSqlType::csqlInt:
			wsprintf(temp, "%d", (int)a);
			break;	
		case CSqlType::csqlDouble:
		   	_gcvt((double)a, SQLMPRE, temp);
	    	break;
		case CSqlType::csqlFloat:
		    _gcvt((float)a, SQLMPRE, temp);
	    	break;
		case CSqlType::csqlLong:
		    wsprintf(temp, "%li", (long)a);
	    	break;			
	    case CSqlType::csqlUInt:
		    wsprintf(temp, "%u", (unsigned int)a);
	    	break;
		case CSqlType::csqlULong:
		   	wsprintf(temp, "%lu", (unsigned long)a);
	    	break;
		case CSqlType::csqlShort:
		   	wsprintf(temp, "%d", (short)a);
	    	break;
		case CSqlType::csqlUShort:
		   	wsprintf(temp, "%u", (unsigned short)a);
	    	break;
		default:
			TRACE0("unknown numeric data type..!\n");
			ASSERT(FALSE);	// serious error....        
			break;
		}
			
	// now convert...		
	VERIFY((m_nIntNumLen = ::sqlxcn((SQLTNMP)m_internal, 
									(SQLTDAP)temp, 
									0)) > 0); 
}
 
BOOL CSqlInternalNumber::fromString(const char* szNumericStr)
{   
	// Transform this internal numeric object into another, given
	// a valid numeric string....
	// NB: This would be a class _ctor except that it introduces ambiguities
	// between CSqlString & CSqlInternalDate with CSqlCommand::operator>>
	ASSERT(strlen(szNumericStr) != 0);
	
	int nLen;
	char temp[SQLSNUM];
	
	nLen = ::sqlxcn((SQLTNMP)temp, (SQLTDAP)szNumericStr, 0);
	
	if (nLen > 0){  
		m_nIntNumLen = nLen;
		strncpy(m_internal, temp, sizeof(m_internal)); 
		return TRUE;
		}
	else{
		TRACE0("invalid string passed to CSqlInternalNumber::fromString()\n");
		return FALSE;
	}		 
}
                                             
CString	CSqlInternalNumber::asPictureStr(const char* szFmt)
{   
	// convert internal form to string using the picture format string..
	char	temp[MAX_NUMERICDIGITS];
	                                                                    
	ASSERT(strlen(szFmt) != 0);
		                                                                    
	VERIFY(::sqlxnp((SQLTDAP)temp, (SQLTDAL)sizeof(temp), 
					(SQLTNMP)m_internal,
					(SQLTNML)m_nIntNumLen,
					(SQLTDAP)szFmt,
					0) == 0); 
	return temp;					
}     
	
	
