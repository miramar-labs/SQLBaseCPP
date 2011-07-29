///////////////////////////////////////////////////////////////////////
//  COPYRIGHT (C) GUPTA TECHNOLOGIES, INC. 1993-1994
//
//	csqlsel.h	: header for class CSqlSelect
//
//	Author		:	Aaron Cody
//	Date		:	4th January 1994 
//	Version		:	SQLBase++ v1.2	  
//	Remarks		:	Some users may wish to use the CSqlSmartSelect class. This
//					requires that CSqlCommand be treated as a virtual base.
//					In this case you should define CSQLCMD_VBASE in the project
//					makefile when you rebuild the library. (see tech. notes).
//
#ifndef CSQLSEL_H
	#define CSQLSEL_H
	
#ifdef CSQLCMD_VBASE
	#pragma message("treating CSqlCommand as a virtual base")
	class CSqlSelect : public virtual CSqlCommand
#else
	class CSqlSelect : public CSqlCommand
#endif
{ 
public:     
// construction/destruction..
	CSqlSelect(CSqlCursor& rCur, const char* szCmd = "");
	CSqlSelect(CSqlCursor& rCur, const UINT nId);    
	virtual ~CSqlSelect();
	
// data pipes..
	void	operator>>(CSqlCommand* pInsertor);
	void	operator>>(CSqlCommand& rInsertor);
	
// virtual overrides..
	virtual BOOL	bind(void);     
	virtual BOOL 	execute(void); 
	virtual BOOL	compileAndExecute(void);         
	virtual void	associateWith(CSqlCursor& rNewCursor);
	virtual void	associateWith(const char* szCmd);
	virtual void	associateWith(const UINT nId);	

// fetching result sets...   
	enum		fetchCode {	endOfFetch, 
							fetchOk, 
							updateSinceLastFetch, 
							deleteSinceLastFetch }; 
							
	fetchCode	fetchRow(CSqlRow*& rpRow);  
	
// miscellaneous select information..
	SQLTNSI		numSelectItems(void);   				
	SQLTROW		numRowsAffected(void);				
	CString		getColumnLabel(SQLTSLC nColNum);	
	CString		fullColumnName(SQLTSLC nCol);			
	void		describeColumn(SQLTSLC nCol);	
			
// long varchar read/write block size
	DWORD		m_lvcBlockReadSize;		
	
// set by DescribeColumn()....
	SQLTSLC		m_nLastColDescribed;    // the column # this data describes..
	CString		m_szHeading; 			// column heading 
	CString		m_szLabel;				// column label
	SQLTDDT		m_ddt;  				// database data type
	SQLTDDL		m_ddl;					// database data length
	SQLTDDT		m_edt;					// external data type
	SQLTDDL		m_edl; 					// external data length
	SQLTPRE		m_precision;			// numeric precision
	SQLTSCA		m_scale;				// numeric scale
	
protected: 
	CSqlRow*	m_pSelectBuffs;
    BOOL		m_bBuffersSet;
    int			m_nColumns;
    int			m_nRows;  
    SQLTCDL 	m_cvl; 
    SQLTFSC 	m_fsc;
    
    void 		setSelectBuffers(void);
    void		emptySelectBuffers(void);
    void		fetchAnyLongVarChars(void); 
    void 		cleanUp(void);
	SQLTFSC		getFetchItemStatus(SQLTSLC nCol);	    
	SQLTCDL		getFetchItemLen(SQLTSLC nCol);	    
    
private:
	// not implemented for this class..
	const CSqlSelect& operator=(const CSqlSelect&){return *this;}
	CSqlSelect(const CSqlSelect&){}
};

#endif	
