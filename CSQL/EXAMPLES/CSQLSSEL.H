///////////////////////////////////////////////////////////////////////
//
//	csqlssel.h	: 	header for class CSqlSmartSelect
//
//	Author		:	Aaron Cody 
//	Version		:	SQLBase++ 1.2
//	Date		:	5th Januaray 1994   
//	Remarks		:   Automates the compile-bind-execute cycle...for selection objects
//					You must define CSQLCMD_VBASE in the project makefile if you are
//					using this class...(see tech. notes).  
//   

#ifndef CSQLSSEL_H
	#define CSQLSSEL_H

#ifndef CSQLCMD_VBASE
	#error please define CSQLCMD_VBASE in the project makefile..
#endif	

//	Warning 4250 tells us that CSqlSmartSelect inherits Bind, Execute & 
//	CompileAndExecute from CSqlSelect because of dominance - this is intended, 
//	so we disable this message...
#pragma warning(disable : 4250)	

class CSqlSmartSelect :public CSqlSmartCommand,  public CSqlSelect
{
public:     
	// construction/destruction..
	CSqlSmartSelect(CSqlCursor& rCur, const char* szCmd = "");  
	CSqlSmartSelect(CSqlCursor& rCur, const UINT nId);    
	virtual ~CSqlSmartSelect(){}  
	
	// ambiguity resolutions..
	virtual void	associateWith(CSqlCursor& rNewCursor);
	virtual void	associateWith(const char* szCmd);
	virtual void	associateWith(const UINT nId);
	
};                          

/////////////////////////////////////////////////////////////////////////////
//
//	Inlines...

inline void	CSqlSmartSelect::associateWith(CSqlCursor& rNewCursor) 
		{emptySelectBuffers();CSqlSmartCommand::associateWith(rNewCursor);}
inline void	CSqlSmartSelect::associateWith(const char* szCmd) 
		{emptySelectBuffers();CSqlSmartCommand::associateWith(szCmd);}
inline void	CSqlSmartSelect::associateWith(const UINT nId) 
		{emptySelectBuffers();CSqlSmartCommand::associateWith(nId);}

#endif	
