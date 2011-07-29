#include "stdincs.h"
#include "csqltype.h"
#include "csqldtm.h"

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlDateTime  

CSqlDateTime::CSqlDateTime(int hour, int mins, int sec, unsigned int msecs)
	:CSqlType(SQLPSTR, CSqlType::csqlDateTime), m_subType(csqlTimeOnly)
{   
	// do some parameter validation...
	ASSERT((hour >= 0) && (hour <= 23));
	ASSERT((mins >= 0) && (mins < 60));
	ASSERT((sec >= 0) && (sec < 60));
	
	// convert to a valid SQL time string...(hh.mi.ss.tttttt)
	char* pBuff = m_SqlTime.GetBufferSetLength(15 + 1);
	
	wsprintf(pBuff, "%02d.%02d.%02d.%06u", hour, mins, sec, msecs);
	
	m_SqlTime.ReleaseBuffer();
}	

CSqlDateTime::CSqlDateTime(int year, int month, int day)
	:CSqlType(SQLPSTR, CSqlType::csqlDateTime), 
	m_subType(csqlDateOnly)
{
	// do some rough parameter validation...
	// (some invalid dates may still get by..eg 31st Feb 1972 ...but
	// SQLBase will tell you that the date is not a valid date...)
	ASSERT((year >= 1899) && (year <= 9999));
	ASSERT((month >= 1) && (month <= 12));
	ASSERT((day >= 1) && (day < 32));
                                   
	// convert to a valid SQL date string...(yyyy-mm-dd)  
	char* pBuff = m_SqlTime.GetBufferSetLength(10+1);
	
	wsprintf(pBuff, "%04d-%02d-%02d", year, month, day);
	
	m_SqlTime.ReleaseBuffer(); 
}	

CSqlDateTime::CSqlDateTime(int year, int month, int day, 		
	int hour, int mins, int sec, unsigned int msecs)
	:CSqlType(SQLPSTR, CSqlType::csqlDateTime), 
	m_subType(csqlTimeStamp)
{ 
	// do some parameter validation...
	ASSERT((hour >= 0) && (hour <= 23));
	ASSERT((mins >= 0) && (mins < 60));
	ASSERT((sec >= 0) && (sec < 60));
	// do some more rough parameter validation...
	// (some invalid dates may still get by..eg 31st Feb 1972 ...but
	// SQLBase will tell you that the date is not a valid date...)
	ASSERT((year >= 1899) && (year <= 9999));
	ASSERT((month >= 1) && (month <= 12));
	ASSERT((day >= 1) && (day < 32));

	// convert to a valid SQL timestamp string...(yyyy-mm-dd-hh.mi.ss.tttttt)
	char* pBuff = m_SqlTime.GetBufferSetLength(26 + 1);
	
	wsprintf(pBuff, "%04d-%02d-%02d-%02d.%02d.%02d.%06u", year, month, day, hour, mins, sec, msecs);	
	
	m_SqlTime.ReleaseBuffer();
}	

CSqlDateTime::CSqlDateTime(const CTime& mfcTime)
	:CSqlType(SQLPSTR, CSqlType::csqlDateTime),
	m_subType(csqlTimeStamp)
{ 
	// constructs a CSqlDateTime object from an MFC CTime object..
	// NOTE: CTime is not compatible with DLL's ...(see MFC notes)
	int yyyy, mm, dd, hh, mi, ss;
	
	// the lowest valid SQLBase date is 1899-12-30                             
	VERIFY((yyyy = mfcTime.GetYear()) >= 1899);
	
	mm = mfcTime.GetMonth();
		                             
	dd = mfcTime.GetDay();
	
#ifdef _DEBUG                         
	// just make sure we don't go lower than 1899-12-30
	if (yyyy == 1899)
		ASSERT((mm == 12) && (dd == 30));
#endif	                                               
    
    // get the time part ...
	hh = mfcTime.GetHour();
	
	mi = mfcTime.GetMinute(); 
	
	ss = mfcTime.GetSecond();

	// convert to a valid SQLBase string..
	char* pBuff = m_SqlTime.GetBufferSetLength(26 + 1);
	
	wsprintf(pBuff, "%04d-%02d-%02d-%02d.%02d.%02d.%06u", 
					yyyy, mm, 
					dd, hh, 
					mi, ss, 
					0);	
	
	m_SqlTime.ReleaseBuffer();
}

const CSqlDateTime& CSqlDateTime::operator=(const CSqlDateTime& rAnother)
{
	// assignment operator ...
	if (&rAnother != this){
		m_SqlTime = rAnother.m_SqlTime; 
		m_subType = rAnother.m_subType;
		}
	return *this;
}

CSqlDateTime::CSqlDateTime()
	:CSqlType(SQLPSTR, CSqlType::csqlDateTime),
	m_subType(csqlTimeStamp)
{ 
	// default _ctor .. just has to put the object in a 
	// consistent state.
	// We set it to the lowest valid SQLBase date...
	char* pBuff = m_SqlTime.GetBufferSetLength(26 + 1);
	
	wsprintf(pBuff, "%04d-%02d-%02d-%02d.%02d.%02d.%06u", 1899, 12, 30, 0, 0, 0, 0);	
	
	m_SqlTime.ReleaseBuffer();
}	
