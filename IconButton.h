#if !defined(AFX_ICONBUTTON_H__F3C057CB_A771_4844_AEFA_654494271022__INCLUDED_)
#define AFX_ICONBUTTON_H__F3C057CB_A771_4844_AEFA_654494271022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IconButton.h : ヘッダー ファイル
//

#include "UxTheme.h"

/////////////////////////////////////////////////////////////////////////////
// CIconButton ウィンドウ

class CIconButton : public CButton
{
// コンストラクション
public:
	CIconButton();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CIconButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CIconButton();
	HTHEME m_hTheme;
protected:
	BOOL m_bDrawItem;
	BOOL m_bInWindow;
	HICON m_hIcon;
	CImageList m_ImageList;

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CIconButton)
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ICONBUTTON_H__F3C057CB_A771_4844_AEFA_654494271022__INCLUDED_)
