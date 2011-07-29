#include "stdincs.h"
#include "csqltype.h"
	#include "csqldtm.h"
	
#include "csqlidat.h"   

#define LEN_DATESTRING 50

///////////////////////////////////////////////////////////////////
//
//	CSqlInternalDate friends

CSqlInternalDate operator+(const CSqlInternalDate& a, int days)
{  
	CSqlInternalDate result;
	  
	VERIFY((result.m_nIntDTLen = ::sqlxda(  (SQLTNMP)result.m_internal, 
											(SQLTNMP)a.m_internal,
											(SQLTNML)a.m_nIntDTLen,
											(SQLTDAY)days)) > 0);
	return result;									 
	}

CSqlInternalDate operator+(int days, const CSqlInternalDate& a)
{  
	CSqlInternalDate result;
	  
	VERIFY((result.m_nIntDTLen = ::sqlxda(  (SQLTNMP)result.m_internal, 
											(SQLTNMP)a.m_internal,
											(SQLTNML)a.m_nIntDTLen,
											(SQLTDAY)days)) > 0);
	return result;									 
	}

///////////////////////////////////////////////////////////////////
//
//	CSqlInternalDate...  

CSqlInternalDate& CSqlInternalDate::operator+=(int days)
{   
	VERIFY((m_nIntDTLen = ::sqlxda( (SQLTNMP)m_internal, 
									(SQLTNMP)m_internal,
									(SQLTNML)m_nIntDTLen,
									(SQLTDAY)days)) > 0);
	return *this;									 
	}

const CSqlInternalDate& CSqlInternalDate::operator=(const CSqlInternalDate& rDate)
{
	// assignment operator...
	if (&rDate != this){
		m_nIntDTLen = rDate.m_nIntDTLen;
		strncpy(m_internal, rDate.m_internal, sizeof(m_internal));
	}
	return *this;
}

CSqlInternalDate::CSqlInternalDate(const CSqlDateTime& rDateTime)   
	:CSqlType(SQLPDAT, csqlIntDate), m_nIntDTLen(0) 
{
	// from an existing CSqlDateTime object...       
	
	CString szInput = rDateTime.asSqlTimeStr(); 
	// the datetime object's string rep. could be in three forms...
	// we need to use the correct format string...
	CString szFmt;

	switch(rDateTime.csqlSubType()){
		case CSqlDateTime::csqlDateOnly:                   
			szFmt = "yyyy-mm-dd";
			break;
		case CSqlDateTime::csqlTimeOnly:
			szFmt = "hh.mi.ss.999999";
			break;
		default:
			szFmt = "yyyy-mm-dd-hh.mi.ss.999999";
			break;
		}
	
	VERIFY(::sqlxpd((SQLTNMP)m_internal, 
					(SQLTNML PTR)&m_nIntDTLen,
					(SQLTDAP)(const char*)szInput,
					(SQLTDAP)(const char*)szFmt,
					0) == 0);
}

CSqlInternalDate::CSqlInternalDate()   
	:CSqlType(SQLPDAT, csqlIntDate), m_nIntDTLen(0) 
{
	// default _ctor
	// should just put the object in a consistent state..
	// init. with the lowest valid SQLBase date... 
	
	VERIFY(::sqlxpd((SQLTNMP)m_internal, 
				(SQLTNML PTR)&m_nIntDTLen,
				(SQLTDAP)(const char*)"1899-12-30",
				(SQLTDAP)(const char*)"yyyy-mm-dd",
				0) == 0);
}

CSqlInternalDate::CSqlInternalDate(const CSqlInternalDate& a)  
	:CSqlType(a.m_BindType, a.m_ObjType)
{ 
	// copy _ctor
	m_nIntDTLen = a.m_nIntDTLen;
	strncpy(m_internal, a.m_internal, sizeof(m_internal));
}

CSqlInternalDate::CSqlInternalDate(const CString& rInput, const CString& rFmt)
	:CSqlType(SQLPDAT, csqlIntDate), m_nIntDTLen(0) 
{   
	// construct an internal date object from an arbitrary input string, whose
	// format is described by a picture string...
	ASSERT(!rFmt.IsEmpty());
	
	VERIFY(::sqlxpd((SQLTNMP)m_internal, 
					(SQLTNML PTR)&m_nIntDTLen,
					(SQLTDAP)(const char*)rInput,
					(SQLTDAP)(const char*)rFmt,
					0) == 0);
}

CString	CSqlInternalDate::asPictureStr(const CString& rFmt)
{   
	// convert the internal date to a string according to the supplied
	// (non-empty) picture format string...
	// will truncate beyond 50 chars max....
	char temp[LEN_DATESTRING];    	

	ASSERT(!rFmt.IsEmpty());
	
	VERIFY(::sqlxdp((SQLTDAP)temp, 
					(SQLTDAL)sizeof(temp), 
					(SQLTNMP)m_internal,
					(SQLTNML)m_nIntDTLen,
					(SQLTDAP)(const char*)rFmt,
					0) == 0); 
	return temp;					
}     

