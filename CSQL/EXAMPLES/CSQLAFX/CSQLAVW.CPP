// csqlavw.cpp : implementation of the CCsqlafxView class        
//
                        
#include "stdafx.h"
#include "csqlafx.h"                 

#include "csqladoc.h"
#include "csqlavw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;     
#endif

/////////////////////////////////////////////////////////////////////////////      
// CCsqlafxView

IMPLEMENT_DYNCREATE(CCsqlafxView, CView)

BEGIN_MESSAGE_MAP(CCsqlafxView, CView)
	//{{AFX_MSG_MAP(CCsqlafxView)
	ON_COMMAND(IDM_EX1, OnEx1)
	ON_COMMAND(IDM_EX2, OnEx2)
	ON_COMMAND(IDM_EX3, OnEx3)
	ON_COMMAND(IDM_EX4, OnEx4)
	ON_COMMAND(IDM_EX5, OnEx5)
	ON_COMMAND(IDM_EX6, OnEx6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCsqlafxView construction/destruction

CCsqlafxView::CCsqlafxView()
{
	// TODO: add construction code here
}

CCsqlafxView::~CCsqlafxView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCsqlafxView drawing

void CCsqlafxView::OnDraw(CDC* pDC)
{
	CCsqlafxDoc* pDoc = GetDocument();

	// TODO: add draw code here
}



/////////////////////////////////////////////////////////////////////////////
// CCsqlafxView diagnostics

#ifdef _DEBUG
void CCsqlafxView::AssertValid() const
{
	CView::AssertValid();
}

void CCsqlafxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCsqlafxDoc* CCsqlafxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCsqlafxDoc)));
	return (CCsqlafxDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCsqlafxView message handlers       

void CCsqlafxView::OnEx1()
{
TRACE0("example 1\n");
#include "..\ex1.cpp"
}

void CCsqlafxView::OnEx2()
{                     
TRACE0("example 2\n");
#include "..\ex2.cpp"
}

void CCsqlafxView::OnEx3()
{                     
TRACE0("example 3\n");
#include "..\ex3.cpp"
}

void CCsqlafxView::OnEx4()
{                     
TRACE0("example 4\n");
#include "..\ex4.cpp"
}

void CCsqlafxView::OnEx5()
{                     
TRACE0("example 5\n");
#include "..\ex5.cpp"
}

void CCsqlafxView::OnEx6()
{                     
TRACE0("example 6\n");
#include "..\ex6.cpp"        
}


