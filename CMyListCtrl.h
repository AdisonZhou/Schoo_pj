#if !defined(AFX_CLASSLISTWND_H__7AC2BB02_A52A_11D6_94B5_0050FC20D215__INCLUDED_)
#define AFX_CLASSLISTWND_H__7AC2BB02_A52A_11D6_94B5_0050FC20D215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassListWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassListWnd window

class CClassListWnd : public CListCtrl
{
	// Construction
public:
	CClassListWnd();

	// Attributes
public:
	UINT temp=0;
		 
	CPalette m_pal;
	CBitmap m_bitmap;
	int m_cxBitmap, m_cyBitmap;

	BOOL SetBkImage(LPCTSTR lpszResourceName);
	BOOL SetBkImage(UINT nIDResource);
	int m_nHighlight;
	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CClassListWnd)
		//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CClassListWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClassListWnd)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSLISTWND_H__7AC2BB02_A52A_11D6_94B5_0050FC20D215__INCLUDED_)

