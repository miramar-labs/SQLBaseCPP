#include "stdincs.h"
#include "csqltype.h" 
	#include "csqlnum.h"
	#include "csqllvc.h"
	#include "csqlstr.h"
	#include "csqldtm.h"
	#include "csqlidat.h"
	#include "csqlinum.h"    

#include "csqlrow.h"

/////////////////////////////////////////////////////////////////////////////
//
//	CSqlRow

CSqlLongVarChar* CSqlRow::longVarCharColumn(int nIndex) const 
	{
	CSqlType* pOb = getColumn(nIndex);
	
	ASSERT(pOb->csqlObjType() == CSqlType::csqlLongVarChar);
	
	return (CSqlLongVarChar*)pOb;
	}  
	
CSqlDateTime* CSqlRow::dateTimeColumn(int nIndex) const 
	{
	CSqlType* pOb = getColumn(nIndex);
	
	ASSERT(pOb->csqlObjType() == CSqlType::csqlDateTime);
	
	return (CSqlDateTime*)pOb;
	}
			
CSqlNumber&	CSqlRow::numericColumn(int nIndex) const 
    { 
   	CSqlType* pOb = getColumn(nIndex);
   	
#ifdef _DEBUG
	CSqlType::obj_type tp = pOb->csqlObjType();
	ASSERT((tp >= CSqlType::csqlInt) && (tp <= CSqlType::csqlUShort));     
#endif
	
	return *(CSqlNumber*)pOb;
    }
    
CSqlString&	CSqlRow::stringColumn(int nIndex) const 
    {
    CSqlType* pOb = getColumn(nIndex);

	ASSERT(pOb->csqlObjType() == CSqlType::csqlString);     
	
	return *(CSqlString*)pOb;
   }

CSqlInternalDate CSqlRow::internalDateColumn(int nIndex) const
    {  
    CSqlType* pOb = getColumn(nIndex);

	ASSERT(pOb->csqlObjType() == CSqlType::csqlDateTime);     
	
	CSqlDateTime& rDateTime = *(CSqlDateTime*)pOb; 
	
	// construct one on the fly...
	CSqlInternalDate idate(rDateTime);
	
	return idate;
    }

CSqlInternalNumber CSqlRow::internalNumericColumn(int nIndex) const
	{    
    CSqlType* pOb = getColumn(nIndex);

#ifdef _DEBUG
	CSqlType::obj_type tp = pOb->csqlObjType();
	ASSERT((tp >= CSqlType::csqlInt) && (tp <= CSqlType::csqlUShort));     
#endif
	
	CSqlNumber& rNumber = *(CSqlNumber*)pOb; 
	
	// construct one on the fly...
	CSqlInternalNumber inum(rNumber);
	
	return inum;
	}

