// DlProgressDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "idicchasen.h"
#include "DlProgressDlg.h"

#include "IdicChasenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlProgressDlg ダイアログ


CDlProgressDlg::CDlProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlProgressDlg)
	m_strEdit1 = _T("");
	//}}AFX_DATA_INIT
}


void CDlProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlProgressDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CDlProgressDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlProgressDlg メッセージ ハンドラ

BOOL CDlProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	// 変数の初期化
	m_bStopReq = FALSE;
	// マウスカーソル
	AfxGetApp()->DoWaitCursor(1);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlProgressDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
//	CDialog::OnCancel();
}

HBRUSH CDlProgressDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: この位置で DC のアトリビュートを変更してください
	if (! m_pIdicChasenDlg->m_IconButton5.m_hTheme  &&  pWnd->GetDlgCtrlID() == IDC_GROUPBOX1)
		pDC->SetTextColor(RGB(0, 0, 255));
	
	// TODO: デフォルトのブラシが望みのものでない場合には、違うブラシを返してください
	return hbr;
}

void CDlProgressDlg::OnButton1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bStopReq = TRUE;
}

void CDlProgressDlg::Destroy()
{
	// マウスカーソル
	AfxGetApp()->DoWaitCursor(0);

	EndDialog(IDCANCEL);
	DestroyWindow();
}
