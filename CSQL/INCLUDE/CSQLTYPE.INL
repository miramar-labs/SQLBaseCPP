///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlType
// 
inline CSqlType::obj_type CSqlType::csqlObjType() const
	{return m_ObjType;}    

inline 	CSqlType::CSqlType(SQLTPDT b_type, obj_type o_type)
	:m_BindType(b_type), m_ObjType(o_type){}

