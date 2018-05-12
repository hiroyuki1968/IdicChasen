#if !defined(AFX_DLPROGRESSDLG_H__B3C840E3_3A64_40BB_960A_15F85AE2739A__INCLUDED_)
#define AFX_DLPROGRESSDLG_H__B3C840E3_3A64_40BB_960A_15F85AE2739A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlProgressDlg.h : ヘッダー ファイル
//

class CIdicChasenDlg;

/////////////////////////////////////////////////////////////////////////////
// CDlProgressDlg ダイアログ

class CDlProgressDlg : public CDialog
{
// コンストラクション
public:
	CDlProgressDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlProgressDlg)
	enum { IDD = IDD_DLPROGRESS_DIALOG };
	CString	m_strEdit1;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void Destroy();
	CIdicChasenDlg* m_pIdicChasenDlg;
	BOOL m_bStopReq;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlProgressDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLPROGRESSDLG_H__B3C840E3_3A64_40BB_960A_15F85AE2739A__INCLUDED_)
