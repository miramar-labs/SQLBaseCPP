// csqladoc.cpp : implementation of the CCsqlafxDoc class
//

#include "stdafx.h"
#include "csqlafx.h"

#include "csqladoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCsqlafxDoc

IMPLEMENT_DYNCREATE(CCsqlafxDoc, CDocument)

BEGIN_MESSAGE_MAP(CCsqlafxDoc, CDocument)
	//{{AFX_MSG_MAP(CCsqlafxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCsqlafxDoc construction/destruction

CCsqlafxDoc::CCsqlafxDoc()
{
	// TODO: add one-time construction code here
}

CCsqlafxDoc::~CCsqlafxDoc()
{
}

BOOL CCsqlafxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCsqlafxDoc serialization

void CCsqlafxDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


/////////////////////////////////////////////////////////////////////////////
// CCsqlafxDoc diagnostics

#ifdef _DEBUG
void CCsqlafxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCsqlafxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCsqlafxDoc commands
