///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlNumber
// 
inline 	CSqlNumber::CSqlNumber()
	:CSqlType(SQLPSSH, csqlShort)
{m_data.Short = (short)0;}
  
inline CSqlNumber::CSqlNumber(const CSqlNumber& rNumber)
	:CSqlType(rNumber.m_BindType, rNumber.m_ObjType), m_data(rNumber.m_data){}
	
inline CSqlNumber::CSqlNumber(short sVal)
	:CSqlType(SQLPSSH, csqlShort){m_data.Short = sVal;}
	
inline CSqlNumber::CSqlNumber(unsigned short usVal)
	:CSqlType(SQLPUSH, csqlUShort){m_data.UShort = usVal;}
	
inline CSqlNumber::CSqlNumber(float fVal)
	:CSqlType(SQLPFLT, csqlFloat){m_data.Float = fVal;}
	
inline CSqlNumber::CSqlNumber(double dVal)
	:CSqlType(SQLPDOU, csqlDouble){m_data.Double = dVal;}
	
inline CSqlNumber::CSqlNumber(long lVal)
	:CSqlType(SQLPSLO, csqlLong){m_data.Long = lVal;}
	
inline CSqlNumber::CSqlNumber(unsigned long ulVal)
	:CSqlType(SQLPULO, csqlULong){m_data.ULong = ulVal;}
	
inline CSqlNumber::CSqlNumber(int nVal)
	:CSqlType(SQLPSIN, csqlInt){m_data.Int = nVal;}
	
inline CSqlNumber::CSqlNumber(unsigned int uiVal)
	:CSqlType(SQLPUIN, csqlUInt){m_data.UInt = uiVal;}   

inline CSqlNumber::operator short() const 			
	{ASSERT(m_ObjType == csqlShort);
	return m_data.Short;}   
	
inline CSqlNumber::operator unsigned short() const 
	{ASSERT(m_ObjType == csqlUShort);
	return m_data.UShort;}

inline CSqlNumber::operator double() const 		
	{ASSERT(m_ObjType == csqlDouble);
	return m_data.Double;}

inline CSqlNumber::operator float() const 			
	{ASSERT(m_ObjType == csqlFloat);
	return m_data.Float;}

inline CSqlNumber::operator long() const 			
	{ASSERT(m_ObjType == csqlLong);
	return m_data.Long;}

inline CSqlNumber::operator unsigned long() const 	
	{ASSERT(m_ObjType == csqlULong);
	return m_data.ULong;}

inline CSqlNumber::operator int() const 			
	{ASSERT(m_ObjType == csqlInt);
	return m_data.Int;}

inline CSqlNumber::operator unsigned int() const	
	{ASSERT(m_ObjType == csqlUInt);
	return m_data.UInt;} 

