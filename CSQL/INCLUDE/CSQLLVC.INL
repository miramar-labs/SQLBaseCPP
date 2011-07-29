///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlLongVarChar
//   
inline DWORD CSqlLongVarChar::bufferLength() const
	{return m_bAllocInternal ? (m_pRep->m_dwInternalAllocLength) : m_dwExternalAllocLength;}   

inline LPBYTE CSqlLongVarChar::bufferPointer()
{   
	// returns a pointer to the internal or external buffer, depending on which
	// is being used.
	// NOTE:
	// internal buffer:	may return NULL if attached to 0 bytes.
	// external buffer:	never NULL
	return m_bAllocInternal ? m_pRep->m_lpInternalBuffer : m_lpExternalBuffer;
}   

inline DWORD CSqlLongVarChar::dataLength()
	{return bufferLength();} 
	
inline SQLTDAP CSqlLongVarChar::dataBuffer()
	{return (SQLTDAP)bufferPointer();} 
	
inline CSqlLongVarChar::operator LPBYTE()	
	{ASSERT(m_ObjType == csqlLongVarChar);
	return (LPBYTE)bufferPointer();} 
	
///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CBufferRep
//
inline void	CBufferRep::increment()
{
	++m_nUseCount;
}

inline void	CBufferRep::decrement()
{
	if (--m_nUseCount == 0){
		// self destruct 
		delete this; 
	}
}
	
