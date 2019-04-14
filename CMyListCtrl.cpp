// ClassListWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CMyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassListWnd

CClassListWnd::CClassListWnd()
{
	m_nHighlight = 0;
}

CClassListWnd::~CClassListWnd()
{
}


BEGIN_MESSAGE_MAP(CClassListWnd, CListCtrl)
	//{{AFX_MSG_MAP(CClassListWnd)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
//	ON_WM_LBUTTONDBLCLK()
//	ON_WM_RBUTTONDBLCLK()
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
   // ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CClassListWnd::OnNMCustomdraw)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassListWnd message handlers

BOOL CClassListWnd::SetBkImage(UINT nIDResource)
{
	temp = nIDResource;
	return SetBkImage((LPCTSTR)nIDResource);
}

BOOL CClassListWnd::SetBkImage(LPCTSTR lpszResourceName)
{
	// If this is not the first call then Delete GDI objects
	if (m_bitmap.m_hObject != NULL)		m_bitmap.DeleteObject();
	if (m_pal.m_hObject != NULL)		m_pal.DeleteObject();


	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), lpszResourceName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hBmp == NULL) 		return FALSE;

	m_bitmap.Attach(hBmp);
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	m_cxBitmap = bm.bmWidth;
	m_cyBitmap = bm.bmHeight;

	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	m_bitmap.GetObject(sizeof(ds), &ds);

	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;

	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL);			// Desktop DC
	if (nColors > 256)
		m_pal.CreateHalftonePalette(&dc);
	else
	{
		// Create the palette

		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		memDC.SelectObject(&m_bitmap);
		::GetDIBColorTable(memDC, 0, nColors, pRGB);

		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for (int i = 0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		m_pal.CreatePalette(pLP);

		delete[] pLP;
		delete[] pRGB;
	}
	Invalidate();

	return TRUE;
}

void CClassListWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bitmap.m_hObject != NULL)  InvalidateRect(NULL);
	
		//SetBkImage((LPCTSTR)temp);
	
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CClassListWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bitmap.m_hObject != NULL)  InvalidateRect(NULL);

		//SetBkImage((LPCTSTR)temp);
	
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CClassListWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bitmap.m_hObject != NULL)		return TRUE;

	return CListCtrl::OnEraseBkgnd(pDC);
}

void CClassListWnd::OnPaletteChanged(CWnd* pFocusWnd)
{
	CListCtrl::OnPaletteChanged(pFocusWnd);

	// TODO: Add your message handler code here
	if (pFocusWnd == this)		return;

	OnQueryNewPalette();
}

BOOL CClassListWnd::OnQueryNewPalette()
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	if (dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL)
	{
		dc.SelectPalette(&m_pal, FALSE);
		BOOL result = dc.RealizePalette();
		if (result)  Invalidate();
		return result;
	}

	return CListCtrl::OnQueryNewPalette();
}

void CClassListWnd::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	int nItem = lpDrawItemStruct->itemID;
	CImageList* pImageList;

	// Save dc state
	int nSavedDC = pDC->SaveDC();

	// Get item image and state info
	LV_ITEM lvi;
	lvi.mask = LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.stateMask = 0xFFFF;		// get all state flags
	GetItem(&lvi);

	// Should the item be highlighted
	BOOL bHighlight = ((lvi.state & LVIS_DROPHILITED) || ((lvi.state & LVIS_SELECTED) && ((GetFocus() == this) ||
		(GetStyle() & LVS_SHOWSELALWAYS))));

	// Get rectangles for drawing
	CRect rcBounds, rcLabel, rcIcon;
	GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
	GetItemRect(nItem, rcLabel, LVIR_LABEL);
	GetItemRect(nItem, rcIcon, LVIR_ICON);
	CRect rcCol(rcBounds);

	CString sLabel = GetItemText(nItem, 0);

	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = pDC->GetTextExtent(_T(" "), 1).cx * 2;

	CRect rcHighlight;
	CRect rcClient;
	int nExt;
	switch (m_nHighlight)
	{
	case 0:
		nExt = pDC->GetOutputTextExtent(sLabel).cx + offset;
		rcHighlight = rcLabel;
		//		if( rcLabel.left + nExt 

		if (m_bitmap.m_hObject != NULL)
		{
			CDC tempDC;
			tempDC.CreateCompatibleDC(pDC);
			tempDC.SelectObject(&m_bitmap);

			GetClientRect(&rcClient);

			CRgn rgnBitmap;
			CRect rcTmpBmp(rcItem);

			rcTmpBmp.right = rcClient.right;

			// We also need to check whether it is the last item
			// The update region has to be extended to the bottom if it is
			if (nItem == GetItemCount() - 1)
				rcTmpBmp.bottom = rcClient.bottom;

			rgnBitmap.CreateRectRgnIndirect(&rcTmpBmp);
			pDC->SelectClipRgn(&rgnBitmap);
			rgnBitmap.DeleteObject();

			if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL)
			{
				pDC->SelectPalette(&m_pal, FALSE);
				pDC->RealizePalette();
			}

			CRect rcFirstItem;
			GetItemRect(0, rcFirstItem, LVIR_BOUNDS);

			for (int i = rcFirstItem.left; i < rcTmpBmp.right; i += m_cxBitmap)
				for (int j = rcFirstItem.top; j < rcTmpBmp.bottom; j += m_cyBitmap)
					pDC->BitBlt(i, j, m_cxBitmap, m_cyBitmap, &tempDC, 0, 0, SRCCOPY);

		}
	}
	// Draw the background color
	if (bHighlight)
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else if (m_bitmap.m_hObject == NULL)
		pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_WINDOW)));



	// Set clip region
	rcCol.right = rcCol.left + GetColumnWidth(0);
	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rcCol);
	pDC->SelectClipRgn(&rgn);
	rgn.DeleteObject();

	// Draw state icon
	if (lvi.state & LVIS_STATEIMAGEMASK)
	{
		int nImage = ((lvi.state & LVIS_STATEIMAGEMASK) >> 12) - 1;
		pImageList = GetImageList(LVSIL_STATE);
		if (pImageList)
		{
			pImageList->Draw(pDC, nImage,
				CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT);
		}
	}

	// Draw normal and overlay icon
	pImageList = GetImageList(LVSIL_SMALL);
	if (pImageList)
	{
		UINT nOvlImageMask = lvi.state & LVIS_OVERLAYMASK;
		pImageList->Draw(pDC, lvi.iImage,
			CPoint(rcIcon.left, rcIcon.top),
			(bHighlight ? ILD_BLEND50 : 0) | ILD_TRANSPARENT | nOvlImageMask);
	}



	// Draw item label - Column 0
	rcLabel.left += offset / 2;
	rcLabel.right -= offset;

	pDC->DrawText(sLabel, -1, rcLabel, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP
		| DT_VCENTER | DT_END_ELLIPSIS);


	// Draw labels for remaining columns
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;

	if (m_nHighlight == 0)		// Highlight only first column
	{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
	}

	rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right :
		rcBounds.right;
	rgn.CreateRectRgnIndirect(&rcBounds);
	pDC->SelectClipRgn(&rgn);

	for (int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)
	{
		rcCol.left = rcCol.right;
		rcCol.right += lvc.cx;

		// Draw the background if needed&& m_nHighlight == HIGHLIGHT_NORMAL
		if (m_bitmap.m_hObject == NULL)
			pDC->FillRect(rcCol, &CBrush(::GetSysColor(COLOR_WINDOW)));

		sLabel = GetItemText(nItem, nColumn);
		if (sLabel.GetLength() == 0)
			continue;


		// Get the text justification
		UINT nJustify = DT_LEFT;
		switch (lvc.fmt & LVCFMT_JUSTIFYMASK)
		{
		case LVCFMT_RIGHT:
			nJustify = DT_RIGHT;
			break;
		case LVCFMT_CENTER:
			nJustify = DT_CENTER;
			break;
		default:
			break;
		}

		rcLabel = rcCol;
		rcLabel.left += offset;
		rcLabel.right -= offset;

		pDC->DrawText(sLabel, -1, rcLabel, nJustify | DT_SINGLELINE
			| DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
	}

	// Draw focus rectangle if item has focus
	if (lvi.state & LVIS_FOCUSED && (GetFocus() == this))
		pDC->DrawFocusRect(rcHighlight);


	// Restore dc
	pDC->RestoreDC(nSavedDC);

}



//void CClassListWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CListCtrl::OnLButtonDblClk(nFlags, point);
//}


//void CClassListWnd::OnRButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CListCtrl::OnRButtonDblClk(nFlags, point);
//}


void CClassListWnd::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = 0;

	//指定列表项绘制前后发送消息   
	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		//奇数行   
		if (pLVCD->nmcd.dwItemSpec % 2)
			pLVCD->clrTextBk = RGB(255, 255, 128);
		//偶数行   
		else
			pLVCD->clrTextBk = RGB(128, 255, 255);
		//继续   
		*pResult = CDRF_DODEFAULT;
	}
}
