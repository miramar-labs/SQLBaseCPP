///////////////////////////////////////////////////////////////////
//
// CLASS INLINES : CSqlCommand
// 
inline int CSqlCommand::bindsRequired(void) const
{ASSERT(m_bCompiled);return m_nBindsNeeded;}

inline int CSqlCommand::numBinds(void) const
{return m_pBinds->GetSize();}

inline CSqlType& CSqlCommand::getBind(int nIndex) const
{return *(CSqlType*)m_pBinds->GetAt(nIndex);}

inline CSqlType& CSqlCommand::operator[](int nIndex) const
{return getBind(nIndex);}

inline 	CString	CSqlCommand::getCmdString(void) const 
{return m_szCmdStr;}

inline CSqlCursor* CSqlCommand::getCursor(void) const
{return m_pCursor;}

