// ProgressDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "IdicChasen.h"
#include "ProgressDlg.h"

#include "Common.h"
#include "IdicChasenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg ダイアログ


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg メッセージ ハンドラ

BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	// 変数の初期化
	m_bStopReq = FALSE;
	// 処理内容
	GetDlgItem(IDC_TEXT1)->SetWindowText(m_lpszDocument);
	// マウスカーソル
	AfxGetApp()->DoWaitCursor(1);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CProgressDlg::OnCancel()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
//	CDialog::OnCancel();
}

HBRUSH CProgressDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: この位置で DC のアトリビュートを変更してください
	if (! m_pIdicChasenDlg->m_IconButton5.m_hTheme  &&  pWnd->GetDlgCtrlID() == IDC_GROUPBOX1)
		pDC->SetTextColor(RGB(0, 0, 255));
	
	// TODO: デフォルトのブラシが望みのものでない場合には、違うブラシを返してください
	return hbr;
}

void CProgressDlg::OnButton1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bStopReq = TRUE;
}

void CProgressDlg::SetDocument(LPCTSTR lpszDocument)
{
	GetDlgItem(IDC_TEXT1)->SetWindowText(lpszDocument);
}

void CProgressDlg::SetRange(int nUpper)
{
	m_ProgressCtrl1.SetRange32(0, nUpper);
}

void CProgressDlg::StepIt()
{
	m_ProgressCtrl1.StepIt();
	PumpWaitingMessages();
}

void CProgressDlg::SetStep(int nStep)
{
	m_ProgressCtrl1.SetStep(nStep);
}

void CProgressDlg::Destroy()
{
	// マウスカーソル
	AfxGetApp()->DoWaitCursor(0);

	EndDialog(IDCANCEL);
	DestroyWindow();
}
