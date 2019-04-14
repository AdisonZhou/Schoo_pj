#pragma once
#include <afxwin.h>
class CEditTrans :
	public CEdit
{
public:
	CEditTrans();
	~CEditTrans();


	// Attributes
private:
	COLORREF    m_TextColor;
	COLORREF    m_BackColor;
	CBrush        m_Brush;
	// Operations
public:
	void SetTextColor(COLORREF col)
	{
		m_TextColor = col;
		UpdateCtrl();
	}
	void SetBackColor(COLORREF col)
	{
		m_BackColor = col;
		UpdateCtrl();
	}
private:
	void UpdateCtrl();
	// Generated message map functions
protected:
	//{{AFX_MSG(CEditTrans)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

