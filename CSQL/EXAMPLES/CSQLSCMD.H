///////////////////////////////////////////////////////////////////////
//
//	csqlscmd.h	: 	header for class CSqlSmartCommand
//
//	Author		:	Aaron Cody 
//	Version		:	SQLBase++ 1.2
//	Date		:	5th January 1994   
//	Remarks		:   Automates the compile-bind-execute cycle... 
//					You only need to define CSQLCMD_VBASE if you are using 
//					the CSqlSmartSelect class as well.
//

#ifndef CSQLSCMD_H
	#define CSQLSCMD_H

#ifdef CSQLCMD_VBASE	
class CSqlSmartCommand : public virtual CSqlCommand
#else                                              
class CSqlSmartCommand : public CSqlCommand
#endif
{
public:     
	// construction/destruction..
	CSqlSmartCommand(CSqlCursor& rCur, const char* szCmd = "");  
	CSqlSmartCommand(CSqlCursor& rCur, const UINT nId);    
	virtual ~CSqlSmartCommand(){}
	
	// overrides...
	virtual void		associateWith(CSqlCursor& rNewCursor);
	virtual void		associateWith(const char* szCmd);
	virtual void		associateWith(const UINT nId);	
	CSqlSmartCommand& 	operator<<(const CSqlString &rData);
	CSqlSmartCommand& 	operator<<(const CSqlNumber &rData);
	CSqlSmartCommand& 	operator<<(const CSqlDateTime &rData);
	CSqlSmartCommand& 	operator<<(const CSqlLongVarChar &rData);	
	CSqlSmartCommand& 	operator<<(const CSqlInternalNumber &rData);	 
	CSqlSmartCommand& 	operator<<(const CSqlInternalDate &rData);	 
	void				replaceBind(int nIndex, const CSqlString& rData);
	void				replaceBind(int nIndex, const CSqlNumber& rData);
	void				replaceBind(int nIndex, const CSqlDateTime& rData);
	void				replaceBind(int nIndex, const CSqlLongVarChar& rData);
	void				replaceBind(int nIndex, const CSqlInternalNumber& rData);  
	void				replaceBind(int nIndex, const CSqlInternalDate& rData);

protected:
	// just for derived classes
	CSqlSmartCommand(){}
};                          

#endif	
