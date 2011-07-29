///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlException
// 
inline CSqlException::CSqlException(SQLTRCD rcd)
:m_rcd(rcd){}      

inline CSqlException::CSqlException()
:m_rcd(0){}

inline CSqlException::operator SQLTRCD() const
{return m_rcd;}

