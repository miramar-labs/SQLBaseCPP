///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlRow
//                            
inline int CSqlRow::numColumns(void) const 
{return GetSize();}

inline 	CSqlType* CSqlRow::getColumn(int nIndex) const
	{return (CSqlType*)GetAt(nIndex);}   

inline CSqlType* CSqlRow::operator[](int nIndex) const
	{return (CSqlType*)CObArray::operator[](nIndex);}

