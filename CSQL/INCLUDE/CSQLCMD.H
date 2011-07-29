///////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlcmd.h	: 	header for class CSqlCommand
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994 
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:     
// 

#ifndef CSQLCMD_H
	#define CSQLCMD_H
	
class CSqlCommand 
{
public:     
// construction/destruction..
	CSqlCommand(CSqlCursor& rCur, const char* szCmd = "");  
	CSqlCommand(CSqlCursor& rCur, const UINT nId);    
	virtual ~CSqlCommand();
	
// compile/bind/execute..
			BOOL	compile(void);
	virtual BOOL	bind(void);     
	virtual BOOL 	execute(void);
	virtual BOOL	compileAndExecute(void);     
			BOOL	bindWithNull(int nBind, BOOL bNullData);
	
	CString			getCmdString(void) const;
	CSqlCursor*		getCursor(void) const;
	
	virtual void	associateWith(CSqlCursor& rNewCursor);
	virtual void	associateWith(const char* rCmd);
	virtual void	associateWith(const UINT nId);	
	
// binds...
	void	deleteAllBinds(void); 
	int		numBinds(void) const;  
	int		bindsRequired(void) const;
			
// associate bind data... 
	CSqlCommand& operator<<(const CSqlString &rString);
	CSqlCommand& operator<<(const CSqlNumber &rNumber);
	CSqlCommand& operator<<(const CSqlDateTime &rDateTime);
	CSqlCommand& operator<<(const CSqlLongVarChar &rLVChar);	
	CSqlCommand& operator<<(const CSqlInternalNumber &rNumber);	 
	CSqlCommand& operator<<(const CSqlInternalDate &rDate);	 
		
// replace bind at index..
	void	replaceBind(int nIndex, const CSqlString& rData);
	void	replaceBind(int nIndex, const CSqlNumber& rData);
	void	replaceBind(int nIndex, const CSqlDateTime& rData);
	void	replaceBind(int nIndex, const CSqlLongVarChar& rData);
	void	replaceBind(int nIndex, const CSqlInternalNumber& rData);  
	void	replaceBind(int nIndex, const CSqlInternalDate& rData);
			
// get bind at index..
	CSqlType& getBind(int nIndex) const;
	CSqlType& operator[](int nIndex) const;
    
// long varchar read/write block size..
    static const DWORD lvcMaxBlockWrite; 	// 32k
    static const DWORD lvcMaxBlockRead; 	// 16k

protected:

	CSqlCursor*	m_pCursor;
	CString		m_szCmdStr;     
	CObArray*	m_pBinds;		
	BOOL		m_bBound;
	BOOL		m_bCompiled;
	BOOL		m_bExecuted;
	SQLTNBV		m_nBindsNeeded;

				CSqlCommand();				
	void		writeAnyLongVarChars(void);
 	void		cleanUp(void);

private:
	// not implemented for this class..
	const CSqlCommand& operator=(const CSqlCommand&){return *this;}
	CSqlCommand(const CSqlCommand&){}
};

#include "csqlcmd.inl" 

#endif
