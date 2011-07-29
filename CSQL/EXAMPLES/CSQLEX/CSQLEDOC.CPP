// csqledoc.cpp : implementation of the CCsqlexDoc class
//

#include "stdafx.h"
#include "csqlex.h"

#include "csqledoc.h"          

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCsqlexDoc

IMPLEMENT_DYNCREATE(CCsqlexDoc, CDocument)

BEGIN_MESSAGE_MAP(CCsqlexDoc, CDocument)
	//{{AFX_MSG_MAP(CCsqlexDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCsqlexDoc construction/destruction

CCsqlexDoc::CCsqlexDoc()
{
	// TODO: add one-time construction code here
}

CCsqlexDoc::~CCsqlexDoc()
{
}

BOOL CCsqlexDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCsqlexDoc serialization

void CCsqlexDoc::Serialize(CArchive& ar)
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
// CCsqlexDoc diagnostics

#ifdef _DEBUG
void CCsqlexDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCsqlexDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCsqlexDoc commands
