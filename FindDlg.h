#if !defined(AFX_FINDDLG_H__4DA832E2_5930_4AF5_98A1_447EE82E7BDA__INCLUDED_)
#define AFX_FINDDLG_H__4DA832E2_5930_4AF5_98A1_447EE82E7BDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CFindDlg ダイアログ

class CFindDlg : public CDialog
{
// コンストラクション
public:
	CFindDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CFindDlg)
	enum { IDD = IDD_FIND_DIALOG };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFindDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CStringArray* m_pSaFindKey;
	CString m_strFindKey;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CFindDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FINDDLG_H__4DA832E2_5930_4AF5_98A1_447EE82E7BDA__INCLUDED_)
