#if !defined(AFX_PROGRESSDLG_H__69F3FF3F_DC08_4D54_838E_C26F0C964133__INCLUDED_)
#define AFX_PROGRESSDLG_H__69F3FF3F_DC08_4D54_838E_C26F0C964133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : ヘッダー ファイル
//

class CIdicChasenDlg;

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg ダイアログ

class CProgressDlg : public CDialog
{
// コンストラクション
public:
	CProgressDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS_DIALOG };
	CProgressCtrl	m_ProgressCtrl1;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void SetDocument(LPCTSTR lpszDocument);
	void SetRange(int nUpper);
	void StepIt();
	void SetStep(int nStep);
	void Destroy();
	CIdicChasenDlg* m_pIdicChasenDlg;
	LPCTSTR m_lpszDocument;
	BOOL m_bStopReq;
protected:
	CProgressCtrl* m_pProgressCtrl;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CProgressDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PROGRESSDLG_H__69F3FF3F_DC08_4D54_838E_C26F0C964133__INCLUDED_)
