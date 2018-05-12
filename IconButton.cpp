// IconButton.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "IconButton.h"

#define WM_THEMECHANGED	0x031A

#define BP_PUSHBUTTON	0x00000001

#define PBS_NORMAL		0x00000001
#define PBS_HOT			0x00000002
#define PBS_PRESSED		0x00000003
#define PBS_DISABLED	0x00000004
#define PBS_DEFAULTED	0x00000005

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIconButton

CIconButton::CIconButton()
{
	m_bDrawItem = TRUE;
	m_bInWindow = FALSE;
	m_hTheme =
	m_hIcon =
		NULL;
}

CIconButton::~CIconButton()
{
}


BEGIN_MESSAGE_MAP(CIconButton, CButton)
	//{{AFX_MSG_MAP(CIconButton)
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_THEMECHANGED, OnThemeChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconButton メッセージ ハンドラ

void CIconButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: 指定されたアイテムを描画するためのコードを追加してください

	if (m_bDrawItem) {
		if (IsThemeActive())
			m_hTheme = OpenThemeData(m_hWnd, L"BUTTON");
		if (m_hTheme)
			m_ImageList.Create(32, 32, ILC_COLOR, 0, 1);
		else
			SetButtonStyle(BS_PUSHBUTTON);
		m_bDrawItem = FALSE;
	}
	if (m_hTheme) {
		HICON hIcon = GetIcon();
		if (hIcon != m_hIcon) {
			if (m_hIcon)
				m_ImageList.Replace(0, hIcon);
			else
				m_ImageList.Add(hIcon);
			m_hIcon = hIcon;
		}

		UINT nState = lpDrawItemStruct->itemState;
		HDC hDC = lpDrawItemStruct->hDC;
		RECT* prcItem = &lpDrawItemStruct->rcItem;

		BOOL bDisabled = nState & ODS_DISABLED;
		BOOL bSelected = nState & ODS_SELECTED;
		BOOL bFocus = nState & ODS_FOCUS;

		int iStateId;
		if (bDisabled)
			iStateId = PBS_DISABLED;
		else if (bSelected)
			iStateId = PBS_PRESSED;
		else if (bFocus || m_bInWindow)
			iStateId = PBS_HOT;
		else
			iStateId = PBS_NORMAL;

		DrawThemeBackground(m_hTheme, hDC, BP_PUSHBUTTON, iStateId, prcItem, 0);

		if (bFocus) {
			RECT rcFocus = {prcItem->left + 4, prcItem->top + 4, prcItem->right - 4, prcItem->bottom - 4};
			DrawFocusRect(hDC, &rcFocus);
		}

		if (hIcon) {
			RECT rcContent;
			GetThemeBackgroundContentRect(m_hTheme, hDC, BP_PUSHBUTTON, iStateId, prcItem, &rcContent);
			int nX = (rcContent.left + rcContent.right) / 2 - 16;
			int nY = (rcContent.top + rcContent.bottom) / 2 - 16 + 1;
/*
			if (iStateId == PBS_PRESSED) {
				nX ++;
//				nY ++;
			}
*/
//			RECT rcImage = {nX, nY, nX + 32, nY + 32};
//			DrawThemeIcon(m_hTheme, hDC, BP_PUSHBUTTON, iStateId, &rcImage, m_ImageList.m_hImageList, 0);
//			DrawIconEx(hDC, rcImage.left, rcImage.top, hIcon, 32, 32, 0, NULL, DI_NORMAL);
			UINT fuFlags = DST_ICON;
			if (iStateId == PBS_DISABLED)
				fuFlags |= DSS_DISABLED;
			DrawState(hDC, NULL, NULL, (LPARAM)hIcon, 0, nX, nY, 0, 0, fuFlags);
		}
	}
}

void CIconButton::OnDestroy() 
{
	CButton::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	if (m_hTheme)
		CloseThemeData(m_hTheme);
}

void CIconButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (! m_bInWindow  &&  m_hTheme) {
		m_bInWindow = TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		if (_TrackMouseEvent(&tme))
			Invalidate();
	}
	
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CIconButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bInWindow = FALSE;
	Invalidate();

	return 0;
}

LRESULT CIconButton::OnThemeChanged(WPARAM wParam, LPARAM lParam)
{
	if (m_hTheme)
		CloseThemeData(m_hTheme);
	m_hTheme = NULL;
	m_ImageList.DeleteImageList();
	SetButtonStyle(BS_OWNERDRAW);
	m_bDrawItem = TRUE;

	return 0;
}
