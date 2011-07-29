// csqledoc.h : interface of the CCsqlexDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CCsqlexDoc : public CDocument
{
protected: // create from serialization only
	CCsqlexDoc();
	DECLARE_DYNCREATE(CCsqlexDoc)

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CCsqlexDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CCsqlexDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
