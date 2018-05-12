#if !defined(AFX_NOTESDLG_H__18964110_C028_4CCF_9990_CBFD34705547__INCLUDED_)
#define AFX_NOTESDLG_H__18964110_C028_4CCF_9990_CBFD34705547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NotesDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CNotesDlg ダイアログ

class CNotesDlg : public CDialog
{
// コンストラクション
public:
	CNotesDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CNotesDlg)
	enum { IDD = IDD_NOTES_DIALOG };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CNotesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL m_bExeNotes;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CNotesDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_NOTESDLG_H__18964110_C028_4CCF_9990_CBFD34705547__INCLUDED_)
