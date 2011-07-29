#include "stdincs.h"
#include "csqlcur.h"
#include "csqlexep.h"


#include "csqltype.h"
	#include "csqlnum.h"
	#include "csqllvc.h"
	#include "csqlstr.h"
	#include "csqldtm.h"
	#include "csqlidat.h"
	#include "csqlinum.h"    

#include "csqlcmd.h" 
#include "csqlrow.h"
#include "csqlsel.h"  

#define MAX_LEN_COLFULLNAME 500
#define	MAX_LEN_HEADING		31
#define LABEL_LEN 			300

const DWORD CSqlCommand::lvcMaxBlockRead = 16384; 	// 16k

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlSelect    

CSqlSelect::CSqlSelect(CSqlCursor& rCur, const char* szCmd)
	:CSqlCommand(rCur, szCmd), m_lvcBlockReadSize(lvcMaxBlockRead),
	m_pSelectBuffs(new CSqlRow), m_bBuffersSet(FALSE){}

CSqlSelect::CSqlSelect(CSqlCursor& rCur, const UINT nId)
	:CSqlCommand(rCur, nId), m_lvcBlockReadSize(lvcMaxBlockRead),
	m_pSelectBuffs(new CSqlRow), m_bBuffersSet(FALSE){}

CSqlSelect::~CSqlSelect()
{  
	cleanUp(); 
} 
                              
BOOL CSqlSelect::bind(void)
{
	// we have to set select buffers before we bind.. 
	setSelectBuffers();
	return CSqlCommand::bind();
}

BOOL CSqlSelect::execute(void)
{
	// if they haven't already been set, we have to set 
	// the select buffers first...
	if (!m_bBuffersSet)
		setSelectBuffers(); 
	return CSqlCommand::execute();
}

void CSqlSelect::associateWith(const char* szNewCmd)
{   
	// we have some resetting to do as well...
	emptySelectBuffers();
	CSqlCommand::associateWith(szNewCmd);
}

void CSqlSelect::associateWith(const UINT nId)
{   
	// we have some resetting to do as well...
	emptySelectBuffers();
	CSqlCommand::associateWith(nId);
}

void CSqlSelect::operator>>(CSqlCommand* pInsertor)
{
	TRACE2("piping select(#%d) into insert(#%d)..\n", (SQLTCUR)*m_pCursor, (SQLTCUR)*(pInsertor->getCursor()));
	if (::sqlcpy(*m_pCursor,
			(SQLTDAP)(const char*)getCmdString(), 0,
			(SQLTCUR)*(pInsertor->getCursor()),
			(SQLTDAP)(const char*)pInsertor->getCmdString(), 0)){
		cleanUp();
		pInsertor->deleteAllBinds();
		THROW(new CSqlCsrException(*m_pCursor , *(pInsertor->getCursor())));
		}
}

void CSqlSelect::operator>>(CSqlCommand& rInsertor)
{
	TRACE2("piping select(#%d) into insert(#%d)..\n", (SQLTCUR)*m_pCursor, (SQLTCUR)*(rInsertor.getCursor()));
	if (::sqlcpy(*m_pCursor, (SQLTDAP)(const char*)getCmdString(), 0,
			(SQLTCUR)*(rInsertor.getCursor()),
			(SQLTDAP)(const char*)rInsertor.getCmdString(), 0)){
		cleanUp();
		rInsertor.deleteAllBinds();
		THROW(new CSqlCsrException(*m_pCursor , *(rInsertor.getCursor())));
		}
}


void CSqlSelect::setSelectBuffers(void)
{
	// get number of columns...
	m_nColumns = (int)numSelectItems();

	m_pSelectBuffs->SetSize(m_nColumns);   		// fix our array size..

	//for each column item.....
	for (int i = 0; i < m_nColumns; i++){

		 describeColumn(i+1);

		 // Here we attempt to map the incoming database type
		 // to an appropriate program CSqlType object
		 CSqlType* pData;

		 // branch on the database data type (can be one of 6..[ch6 p259])

		 switch(m_ddt){
			case SQLDCHR:
				// Character....(fixed column width)
				switch(m_edt){
					case SQLECHR:
					case SQLEVAR:
						// need string length (column width)
						// & then grow the string's buffer...
						pData = new CSqlString("");
						(((CSqlString*)pData)->m_data).GetBufferSetLength(m_ddl);
						break;
					default:
						TRACE0("unknown fixed string type\n");
						ASSERT(FALSE);      // serious error !!
						break;
	    			}
	    		break;
	    		
			case SQLDNUM:              
				// Numeric.... 
				switch(m_edt){
					case SQLESMA: // 2 byte signed SMALLINT 
						pData = new CSqlNumber((short)0);    // (C++ short)
						break; 
						
					case SQLEINT:	// 4 byte signed INTEGER 
						pData = new CSqlNumber((long)0);	// (C++ long)
						break;    
						
					case SQLEFLO:	// 4 or 8 bytes FLOAT 
						pData = (m_edl == 4) ? 
							new CSqlNumber((float)0) :
							new CSqlNumber((double)0);  // (C++ float or double)
						break;
						
					case SQLEDEC:	//8 byte DECIMAL 
						pData = new CSqlNumber((double)0); // (C++ double)    
						break;
						
					default:
						TRACE0("unknown numeric type\n");
						ASSERT(FALSE);      // serious error !!
						break;													
					}
				break;
				
			case SQLDLON:
				// Long .... 
				switch(m_edt){
					case SQLELON:	// LONGVAR char 
						pData = new CSqlLongVarChar;
						// we don't need to do sqlssb()...
						break;
					default:
						TRACE0("unknown long type\n");
						ASSERT(FALSE);      // serious error !!
					}						
				break;  
				
   			case SQLDDTE:      
   				// DATE only...
   				pData = new CSqlDateTime(1899, 12, 30);
   				break; 
   			
   			case SQLDDAT:                                      
   				// DATETIME ...
   				pData = new CSqlDateTime(1899, 12, 30, 0, 0);
   				break; 
   			
   			case SQLDTIM:                              
   				// TIME only ...
   				pData = new CSqlDateTime(0, 0, 0, 0);
   				break; 
   				
			default:
				TRACE0("unknown datbase data type\n");
				ASSERT(FALSE);           // serious error !!!
				break;
			}
	    
	    m_pSelectBuffs->SetAt(i, pData);   // store it...
	    
	    // now set the select buffers for this column...(unless it's a long varchar)
	    
	    if (pData->m_ObjType != CSqlType::csqlLongVarChar){ 
	    	// if not a long varchar..set select buffers...
	    	if(::sqlssb(*m_pCursor, 
	    					i+1,
	    					pData->m_BindType,
	    					pData->dataBuffer(),
	    					(SQLTPDL)pData->dataLength(),
	    					m_scale,
	    					&m_cvl,
	    					&m_fsc)){
				cleanUp();	    					
				THROW(new CSqlCsrException(*m_pCursor));	    				 
				}
			}// if not a long varchar....
			
		}// main column loop
			
	m_bBuffersSet = TRUE;
}

void CSqlSelect::associateWith(CSqlCursor& rNewCursor)
{
	emptySelectBuffers();
	CSqlCommand::associateWith(rNewCursor);
}

void CSqlSelect::emptySelectBuffers(void)
{
	// kill off each select object........
	int nSize = m_pSelectBuffs->GetSize();

	if (nSize > 0){
		for (int i = 0; i < nSize ; i++)
			delete (CSqlType*)m_pSelectBuffs->GetAt(i);

		// remove array pointers...
		m_pSelectBuffs->RemoveAll();
	}

	m_bBuffersSet = FALSE;
}

BOOL CSqlSelect::compileAndExecute(void)
{
	// don't use this if you have binds !

	BOOL bOk = CSqlCommand::compileAndExecute();
    
    if (!bOk)
    	return FALSE;
    	
	if (!m_bBuffersSet)
		setSelectBuffers();

	return (m_bExecuted = TRUE);
}
   
CSqlSelect::fetchCode CSqlSelect::fetchRow(CSqlRow*& rpRow)
{
	// returns :(see enum CSqlSelect::fetcCodes)
	// zero ==> no more rows
	// 1	==> fetch ok ... more follows
	// 2	==> update since last fetch
	// 3 	==> delete since last fetch   
	
	// are we ready to fetch ?.... 
	if (!m_bBuffersSet){
		TRACE0("can't fetch before buffers set !\n");
		return endOfFetch;
		}
	
	if (!m_bExecuted){
		TRACE0("can't fetch before executed !\n");
		return endOfFetch;
		}
	
	fetchCode eRet; 	// my return status flag
	
	// do the fetch...
	SQLTRCD ret = ::sqlfet(*m_pCursor);

	switch(ret){
		case 0:
			fetchAnyLongVarChars();
			TRACE0("fetched row ok..\n");    
			eRet =  fetchOk;  
			break;
		case 1:
			TRACE1("end of fetch ..(%ld) rows\n", numRowsAffected());
			eRet =  endOfFetch;
			emptySelectBuffers(); 	// nothing was fetched so empty out
			break;
		case 2:
			fetchAnyLongVarChars();
			TRACE0("update performed since last fetch..!\n");
			eRet = updateSinceLastFetch;
			break;
		case 3:
			fetchAnyLongVarChars();
			TRACE0("delete performed since last fetch..!\n");
			eRet = deleteSinceLastFetch;
			break;
		default:
			cleanUp();
			THROW(new CSqlCsrException(*m_pCursor)); // fetch error
			break;
		}

	// vaild ref to pointer until next fetch..
	rpRow = m_pSelectBuffs;

	return eRet;
}

void CSqlSelect::describeColumn(SQLTSLC nCol)
{
	ASSERT(m_pCursor->isConnected());

	// check logic ...
	ASSERT(m_pCursor->getDbParamValue(SQLPDIS) == SQLDELY);

	SQLTCHL len;

	m_nLastColDescribed = nCol;

	// get database data info..	
	if(::sqldes(*m_pCursor, nCol, 
				&m_ddt, &m_ddl, 
				(SQLTCHP)m_szHeading.GetBufferSetLength(MAX_LEN_HEADING), &len,
				&m_precision, &m_scale)){
		cleanUp();				
		THROW(new CSqlCsrException(*m_pCursor));
		}
	
	// get external info...
	if(::sqldsc(*m_pCursor, nCol, 
				&m_edt, &m_edl, 
				(SQLTCHP)m_szHeading.GetBufferSetLength(MAX_LEN_HEADING), &len,
				&m_precision, &m_scale)){
		cleanUp();				
		THROW(new CSqlCsrException(*m_pCursor)); 
		}
		
	m_szHeading.ReleaseBuffer(len);
}

CString	CSqlSelect::fullColumnName(SQLTSLC nCol) 
{   
	CString szFullName;
	SQLTDAL len;     
	
	ASSERT(m_pCursor->isConnected());
	
	if(::sqlfqn(*m_pCursor, nCol, (SQLTDAP)szFullName.GetBufferSetLength(MAX_LEN_COLFULLNAME), &len)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
		
	szFullName.ReleaseBuffer(len);

	return szFullName;
}

SQLTNSI CSqlSelect::numSelectItems(void)  
{
	SQLTNSI num;
	ASSERT(m_pCursor->isConnected() && m_bCompiled); 
	if(::sqlnsi(*m_pCursor, &num)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
	return num;
} 

SQLTROW CSqlSelect::numRowsAffected(void)  
{                                            
	SQLTROW rows; 
	ASSERT(m_pCursor->isConnected());
	if(::sqlrow(*m_pCursor, &rows)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
	return rows;
}

CString	CSqlSelect::getColumnLabel(SQLTSLC nColNum)
{
	SQLTCHL len;
	CString	label; 
	ASSERT(m_pCursor->isConnected());
	if(::sqllab(*m_pCursor, nColNum, (SQLTCHP)label.GetBufferSetLength(LABEL_LEN), &len)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
	label.ReleaseBuffer(len);	
	return label;
}

SQLTFSC	CSqlSelect::getFetchItemStatus(SQLTSLC nCol) 
{
	SQLTFSC stat; 
	ASSERT(m_pCursor->isConnected());
	if(::sqlgfi(*m_pCursor, nCol, SQLNPTR, &stat)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
	return stat;
}

SQLTCDL	CSqlSelect::getFetchItemLen(SQLTSLC nCol) 
{
	SQLTCDL len; 
	ASSERT(m_pCursor->isConnected());
	if(::sqlgfi(*m_pCursor, nCol, &len, SQLNPTR)){
		cleanUp();
		THROW(new CSqlCsrException(*m_pCursor));
		}
	return len;
}

void CSqlSelect::fetchAnyLongVarChars(void)
{
	for (int c = 0; c < m_pSelectBuffs->GetSize(); c++){
	
		CSqlType* pItem = m_pSelectBuffs->getColumn(c);
		
		if(pItem->m_ObjType == CSqlType::csqlLongVarChar){
			// yes..so read in the data..
			// do it in m_lvcBlockReadSize blocks...
#ifdef _DEBUG
			int nCycles = 0;					
#endif
			SQLTDAL	bytesRead = 1; 
			DWORD	dwDataLength = 0;
			// check that the block size is ok..if not set it to the default				
			if ((m_lvcBlockReadSize == 0) || (m_lvcBlockReadSize > lvcMaxBlockRead))
				m_lvcBlockReadSize = lvcMaxBlockRead;
			
			DWORD dwBytesWanted = m_lvcBlockReadSize;
				
			while(bytesRead){  
				TRY{
					// grow our buffer for the next read... 
					((CSqlLongVarChar*)pItem)->m_pRep->growByteBuffer(dwBytesWanted);
					
                }CATCH(CMemoryException, e){
                	// clean up and abort reading in this long var char...  
                	TRACE2("low memory ! - long varchar object %d trunctated "
                		  "to %ld bytes\n", c+1, dwDataLength); 
					return;  // abort reading long varchars..              		  
                }END_CATCH
				// lock handle to get far pointer to base of buffer...
				SQLTDAP dap = pItem->dataBuffer();   
				
				// we read in chunks of m_lvcBlockReadSize bytes
				// add the offset into the buffer where the next read will 
				// write bytes to... 
				dap = (BYTE __huge*)dap + dwDataLength;
				
				// read bytes to pointer position..
				if (::sqlrlo(*m_pCursor,
							 c+1,
							 (SQLTDAP)dap,
							 (SQLTDAL)m_lvcBlockReadSize,
							 &bytesRead)){
					cleanUp();							 
					THROW(new CSqlCsrException(*m_pCursor)); 
					}
					
				// calculate the actual length of the buffer 	
				dwDataLength += bytesRead;    
				
				// request a bigger chunk next cycle..
				// (it grows m_lvcBlockReadSize bytes each cycle) 				
				dwBytesWanted += m_lvcBlockReadSize;
#ifdef _DEBUG
				nCycles++;					
#endif
				}// while more bytes to read..
					    
#ifdef _DEBUG
				if(nCycles > 10 && (m_lvcBlockReadSize < lvcMaxBlockRead)){
					TRACE2("long varchar bind[%d] read in %d cycles\n", c, nCycles);
					TRACE0("suggestion : increase CSqlSelect::m_lvcBlockReadSize to optimize lvchar fetch !\n");
					}
#endif	
			
			// finally truncate buffer to actual size (dwDataLength bytes) ...   
			TRY{
				((CSqlLongVarChar*)pItem)->m_pRep->growByteBuffer(dwDataLength);
			}CATCH(CMemoryException, e){
            	// clean up and abort reading in this long varchar...  
            	TRACE2("low memory ! - long varchar object %d trunctated "
            		  "to %ld bytes\n", c+1, dwDataLength); 
				return;	// abort reading long varchars..              		  
			}END_CATCH
			
			// end long op.....
			if (::sqlelo(*m_pCursor)){
				cleanUp();
				THROW(new CSqlCsrException(*m_pCursor));
				}	    				
				
			TRACE2("read long varchar column[%d] - %ld bytes\n", c + 1, dwDataLength);	
			}// if long varchar...    
			
		}// column loop 
		
	return;		
}

// protected...
void CSqlSelect::cleanUp(void)
{   
	// we call this before throwing an exception...
	// base class cleanup first...
	CSqlCommand::cleanUp();       
	// now our stuff.. 
	if (m_pSelectBuffs){
		m_szHeading.Empty();
		m_szLabel.Empty();
		emptySelectBuffers();
		delete m_pSelectBuffs;
		m_pSelectBuffs = NULL;
	}
}
