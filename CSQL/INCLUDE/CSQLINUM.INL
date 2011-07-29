///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlInternalNumber
// 
inline CSqlInternalNumber::CSqlInternalNumber()
	:CSqlType(SQLPNUM, csqlIntNum), m_nIntNumLen(0)
	{fromString("0");}

inline DWORD CSqlInternalNumber::dataLength()
	{return sizeof(m_internal);} 

inline SQLTDAP CSqlInternalNumber::dataBuffer()
	{return (SQLTDAP)&m_internal;};    
                         
