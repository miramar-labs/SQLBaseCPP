///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlInternalDate
//
inline DWORD CSqlInternalDate::dataLength()
	{return sizeof(m_internal);} 

inline SQLTDAP CSqlInternalDate::dataBuffer()
	{return (SQLTDAP)&m_internal;};    

