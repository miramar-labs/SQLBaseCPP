// csqlevw.h : interface of the CCsqlexView class
//
/////////////////////////////////////////////////////////////////////////////

class CCsqlexView : public CView
{
protected: // create from serialization only
	CCsqlexView();
	DECLARE_DYNCREATE(CCsqlexView)

// Attributes
public:
	CCsqlexDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CCsqlexView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CCsqlexView)
	afx_msg void OnEx1();
	afx_msg void OnEx2();
	afx_msg void OnEx3();
	afx_msg void OnEx4();
	afx_msg void OnEx5();
	afx_msg void OnEx6();
	afx_msg void OnEx7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in csqlevw.cpp
inline CCsqlexDoc* CCsqlexView::GetDocument()
   { return (CCsqlexDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
