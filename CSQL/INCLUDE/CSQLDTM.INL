///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlDateTime
// 
inline CSqlDateTime::sub_type CSqlDateTime::csqlSubType(void) const 
{return m_subType;}

inline CSqlDateTime::CSqlDateTime(const CSqlDateTime& rDtm)
	:CSqlType(rDtm.m_BindType, rDtm.m_ObjType), 
	m_SqlTime(rDtm.m_SqlTime), m_subType(rDtm.m_subType)
	{}

inline CString CSqlDateTime::asSqlTimeStr() const 
	{ASSERT(!m_SqlTime.IsEmpty());return m_SqlTime;}

inline DWORD CSqlDateTime::dataLength()
	{return m_SqlTime.GetLength() + 1;} 

inline SQLTDAP CSqlDateTime::dataBuffer()
	{return (SQLTDAP)(const char*)m_SqlTime;}

