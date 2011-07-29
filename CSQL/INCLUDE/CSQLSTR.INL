///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlString
// 
inline CSqlString::operator const char*() const
	{return (const char*)m_data;} 

inline CSqlString::CSqlString(const CSqlString& rString) 
	:CSqlType(rString.m_BindType, rString.m_ObjType),
	m_data(rString.m_data)
	{} 
	
inline CSqlString::CSqlString(const char * pStr)
	:CSqlType(SQLPSTR, csqlString), m_data(pStr){}       
	
inline CSqlString::CSqlString(const CString& rStr)
	:CSqlType(SQLPSTR, csqlString), m_data(rStr){}       

inline DWORD CSqlString::dataLength() 	
{int len = m_data.GetLength(); 
	return (len < 255) ? len : 254;} 

inline SQLTDAP CSqlString::dataBuffer()
{return (SQLTDAP)(const char*)m_data;}
	
