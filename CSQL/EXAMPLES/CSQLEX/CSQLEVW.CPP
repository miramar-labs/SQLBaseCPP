// csqlevw.cpp : implementation of the CCsqlexView class    
//

#include "stdafx.h"
#include "csqlex.h"

#include "csqledoc.h"                  
#include "csqlevw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCsqlexView

IMPLEMENT_DYNCREATE(CCsqlexView, CView)

BEGIN_MESSAGE_MAP(CCsqlexView, CView)
	//{{AFX_MSG_MAP(CCsqlexView)
	ON_COMMAND(IDM_EX1, OnEx1)
	ON_COMMAND(IDM_EX2, OnEx2)
	ON_COMMAND(IDM_EX3, OnEx3)
	ON_COMMAND(IDM_EX4, OnEx4)
	ON_COMMAND(IDM_EX5, OnEx5)
	ON_COMMAND(IDM_EX6, OnEx6)    
	ON_COMMAND(ID_EX7, OnEx7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCsqlexView construction/destruction

CCsqlexView::CCsqlexView()
{
	// TODO: add construction code here                       
}

CCsqlexView::~CCsqlexView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCsqlexView drawing

void CCsqlexView::OnDraw(CDC* pDC)
{
	CCsqlexDoc* pDoc = GetDocument();

	// TODO: add draw code here
}



/////////////////////////////////////////////////////////////////////////////
// CCsqlexView diagnostics

#ifdef _DEBUG
void CCsqlexView::AssertValid() const
{
	CView::AssertValid();
}

void CCsqlexView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCsqlexDoc* CCsqlexView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCsqlexDoc)));
	return (CCsqlexDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCsqlexView message handlers

void CCsqlexView::OnEx1()
{
TRACE0("example 1\n");
#include "..\ex1.cpp"
}

void CCsqlexView::OnEx2()
{                     
TRACE0("example 2\n");
#include "..\ex2.cpp"
}

void CCsqlexView::OnEx3()
{                     
TRACE0("example 3\n");
#include "..\ex3.cpp"
}

void CCsqlexView::OnEx4()
{                     
TRACE0("example 4\n");
#include "..\ex4.cpp"
}

void CCsqlexView::OnEx5()
{                     
TRACE0("example 5\n");
#include "..\ex5.cpp"
}

void CCsqlexView::OnEx6()
{                     
TRACE0("example 6\n");
#include "..\ex6.cpp"
}

void CCsqlexView::OnEx7()
{
TRACE0("example 7\n");
#include "..\ex7.cpp"
}
