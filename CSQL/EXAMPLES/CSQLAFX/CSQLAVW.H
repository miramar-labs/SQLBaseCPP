// csqlavw.h : interface of the CCsqlafxView class   
//
/////////////////////////////////////////////////////////////////////////////

class CCsqlafxView : public CView
{
protected: // create from serialization only
	CCsqlafxView();
	DECLARE_DYNCREATE(CCsqlafxView)

// Attributes
public:
	CCsqlafxDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CCsqlafxView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CCsqlafxView)
	afx_msg void OnEx1();
	afx_msg void OnEx2();
	afx_msg void OnEx3();
	afx_msg void OnEx4();
	afx_msg void OnEx5();
	afx_msg void OnEx6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in csqlavw.cpp
inline CCsqlafxDoc* CCsqlafxView::GetDocument()
   { return (CCsqlafxDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
