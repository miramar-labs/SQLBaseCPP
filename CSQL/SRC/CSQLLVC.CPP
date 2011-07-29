#include "stdincs.h"
#include "csqltype.h"
#include "csqllvc.h"

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlLongVarChar  
//

// external buffer _ctor..
CSqlLongVarChar::CSqlLongVarChar(LPBYTE lpByte, DWORD dwBytes)
	:CSqlType(SQLPBUF, csqlLongVarChar), 
	m_dwExternalAllocLength(dwBytes), 
	m_lpExternalBuffer(lpByte), 
	m_pRep(NULL),
	m_bAllocInternal(FALSE)
{}	

// from file _ctor ...(internal buffer)
CSqlLongVarChar::CSqlLongVarChar(CFile& rFile)  
	:CSqlType(SQLPBUF, csqlLongVarChar), 
	m_dwExternalAllocLength(0), 
	m_lpExternalBuffer(NULL), 
	m_pRep(new CBufferRep),
	m_bAllocInternal(TRUE)
{   
	// Here we read the file into internally allocated memory....
	ASSERT(rFile.m_hFile != CFile::hFileNull);  // file must exist 
	 
	TRY{
		m_pRep->growByteBuffer(rFile.GetLength()); 
		
		rFile.ReadHuge(bufferPointer(), bufferLength());
		
	}CATCH(CFileException, e){
	
		TRACE0("file-error reading data into long varchar object\n");
		
	}AND_CATCH(CMemoryException, e){ 
	
		TRACE0("memory-error reading data into long varchar object\n"); 
		
	}END_CATCH
}	

void CSqlLongVarChar::toFile(CFile& rFile)
{
	// the file must exist......                     
	ASSERT(rFile.m_hFile != CFile::hFileNull); 
	
	TRY{
		rFile.WriteHuge(bufferPointer(), bufferLength());

	}CATCH(CFileException, e){
	
		TRACE0("error writing BLOB to file\n");
		
		THROW_LAST() // user may want to process this one further...
		
	}END_CATCH		
} 

CSqlLongVarChar::CSqlLongVarChar(const CSqlLongVarChar& rLvc) 
	:CSqlType(rLvc.m_BindType, rLvc.m_ObjType)
{	
	// copy _ctor (smart .. uses use-counting scheme)
	// should init. all the data members of this new object
	// and leave it in a consistent state..
	
	// 1. general data members...
	m_bAllocInternal = rLvc.m_bAllocInternal;
	
	// 2. external buffer data members..
	m_dwExternalAllocLength = rLvc.m_dwExternalAllocLength;
	m_lpExternalBuffer = rLvc.m_lpExternalBuffer;
	
	// 3. internal buffer data members...
	if (rLvc.m_bAllocInternal){
		// source object IS using it's rep, so increment the use count first..
		ASSERT(rLvc.m_pRep);
		rLvc.m_pRep->increment();	
		}
		
	m_pRep = rLvc.m_pRep;	// we share the rep by copying the pointer...
} 

const CSqlLongVarChar& CSqlLongVarChar::operator=(const CSqlLongVarChar& rLvc)
{
	// smart assignment .. like the copy _ctor it uses the buffer rep. scheme. 
	// This operator has to do a few more things than the copy _ctor....      
	// For example consider two CSqlLongVarChar objects A & B and the assignment
	// A = B;
	// case 1:
	//	A and B are both using their rep. objects and rep A == rep B (ie both objects
	//  are associated with the same internal buffer). In this case there is nothing
	//  to do.
	// case 2:
	//	A and B are both using their reps but rep A != rep B (ie the objects are 
	//  associated with different internal buffers). In this case, A should decrement
	//  the use count of its current rep object (and free up the memory & rep object if
	//  it reached zero), THEN take on B's rep object (after incrementing its use count)
	//  as in case 3.
	// case 3:
	//	A is not using its rep object but B is. In this case A NULL's out its external
	//  buffer member data and copies over B's rep object (after incrementing its use
	//  count).
	// case 4:
	// 	A is using its rep but B is not. In this case A should decrement its current
	//  rep's use count (freeing up the memory & deleting the rep object if it reaches 
	//  zero), THEN NULL out its rep member data (setting m_bAllocInternal to FALSE) and
	//  copy over B's external member data.
	// case 5: 
	//	Niether A or B are using their rep's. Just copy over the external buffer data
	//  members.
	
	if (&rLvc != this){    
		if (rLvc.m_bAllocInternal == TRUE){
			// B is using it's rep..                  
			if (m_bAllocInternal){
				// A and B using reps
				if (m_pRep != rLvc.m_pRep){
					// different reps ... case 2
					ASSERT(m_pRep);
					m_pRep->decrement();
					// now take on B's rep (inc. its use-count first)..
					ASSERT(rLvc.m_pRep);
					rLvc.m_pRep->increment();
					m_pRep = rLvc.m_pRep;
					}					     
				// fall thru' to case 1 (nothing to do)					
				}
			else{
				// A not using rep, B using rep... case 3
				m_lpExternalBuffer = NULL;
				m_dwExternalAllocLength = 0;
				ASSERT(rLvc.m_pRep);
				rLvc.m_pRep->increment();
				m_pRep = rLvc.m_pRep;
				m_bAllocInternal = TRUE;  
				}
			}
		else{                    
			// B not using it's rep...
			if (m_bAllocInternal){
				// A using rep, B not ... case 4
				ASSERT(m_pRep);
				m_pRep->decrement();
				// now take on B's external members..
				m_lpExternalBuffer = rLvc.m_lpExternalBuffer;
				m_dwExternalAllocLength = rLvc.m_dwExternalAllocLength;
				m_bAllocInternal = FALSE;
				}
			else{                              
				// neither A or B using rep ... case 5
				m_lpExternalBuffer = rLvc.m_lpExternalBuffer;
				m_dwExternalAllocLength = rLvc.m_dwExternalAllocLength;
				}				
			}

		}// if B != A
					
	return *this;
}
	
CSqlLongVarChar::~CSqlLongVarChar()
{
	// the CBufferRep::Decrement() member is responsible for freeing
	// any associated memory....
	if (m_bAllocInternal)
		m_pRep->decrement();
}

// default _ctor uses internal buffer rep attached to zero bytes by default.
CSqlLongVarChar::CSqlLongVarChar()   
	:CSqlType(SQLPBUF, csqlLongVarChar), 
	m_dwExternalAllocLength(0), m_lpExternalBuffer(NULL), 
	m_pRep(new CBufferRep),
	m_bAllocInternal(TRUE)
{}	

//////////////////////////////////////////////////////////////////////////////////////
//
//	CBufferRep : PRIVATE CLASS
//
//	This is a buffer - rep. class. A CLongVarChar object contains one of these objects
//	if it is associated with an internal buffer. Copies of a CSqlLongVarChar object
//  SHARE the same buffer rep. object. Each time a new copy of the CSqlLongVarChar
//  object is made (ie by the copy _ctor), only the rep.'s use count is incremented, no
//  memory is duplicated. Each time one of the CSqlLongVarChar copies is destroyed (ie
//	by its destructor), the rep.'s use count is decremented...and only when it reaches
//  zero does the rep object attempt to free it's memory.
//  I say 'attempt' because it is ok for the object to be attatched to zero bytes of
//  memory - in this case there is no memory to free...
//	Note the useage of the Windows 3.1 extended Macro API's (from windowsx.h) :
//		GlobalAllocPtr()
//		GlobalReAllocPtr()
//		GlobalFreePtr()
//

// destructor...
CBufferRep::~CBufferRep()
{
	if (m_lpInternalBuffer != NULL){ 
		// attached to >0 bytes... 
		ASSERT(m_dwInternalAllocLength != 0);
		VERIFY(GlobalFreePtr(m_lpInternalBuffer) == NULL);
		}
}

// default _ctor
CBufferRep::CBufferRep() 
	:m_lpInternalBuffer(NULL), 
	m_dwInternalAllocLength(0), 
	m_nUseCount(1) 
{}

DWORD CBufferRep::growByteBuffer(DWORD dwNewSize)
{
	// This routine allows you to grow/shrink the rep's internal buffer.
	// You can shrink the buffer to zero bytes, in which case, the pointer
	// will be NULL, and the alloc length will be zero.
	// Any memory errors are reported by throwing an MFC CMemoryException object..
	        
	if (m_lpInternalBuffer == NULL){
		// no memory attatched to rep yet...
		if ((m_lpInternalBuffer = (LPBYTE)GlobalAllocPtr(GHND, dwNewSize))== NULL)
			AfxThrowMemoryException();	// error! 
		// all is ok...
		m_dwInternalAllocLength = dwNewSize;
		}
	else{
		// memory has previously been attatched to this rep, so we are re-allocing..
		if (dwNewSize == 0){ 
		    // shrinking to zero !...just free the memory.. 
		    // (don't touch the use count)
			if(GlobalFreePtr(m_lpInternalBuffer) != NULL)
				AfxThrowMemoryException();	//error!
			// all is ok...				
            m_lpInternalBuffer = NULL;
            m_dwInternalAllocLength = 0;
			}
		else {
			// growing/shrinking to a non-zero value... 
			LPBYTE lpNewBuff;
			if((lpNewBuff = (LPBYTE)GlobalReAllocPtr(m_lpInternalBuffer, dwNewSize, GMEM_MOVEABLE)) == NULL)
				AfxThrowMemoryException();	//error!
			// all is ok...				
			m_lpInternalBuffer = lpNewBuff;	
			m_dwInternalAllocLength = dwNewSize;
			}				
		}
		
	return m_dwInternalAllocLength;
}   
