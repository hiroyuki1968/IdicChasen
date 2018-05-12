// FindDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "idicchasen.h"
#include "FindDlg.h"

#include "IdicChasenDef.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDlg ダイアログ


CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDlg メッセージ ハンドラ

BOOL CFindDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	// 検索キー
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
	for (int i = 0, imax = m_pSaFindKey->GetSize(); i < imax; i ++)
		pComboBox->AddString(m_pSaFindKey->GetAt(i));
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CFindDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	const static char* pszFuncName = "CFindDlg.OnOK";
	try {
		// 検索キー
		CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
		int nFindKey;
		if ((nFindKey = pComboBox->GetCurSel()) == CB_ERR)
			pComboBox->GetWindowText(m_strFindKey);
		else
			pComboBox->GetLBText(nFindKey, m_strFindKey);
		// 検索キー履歴
		if (nFindKey != CB_ERR  ||  (nFindKey = pComboBox->FindStringExact(-1, m_strFindKey)) != CB_ERR)
			m_pSaFindKey->RemoveAt(nFindKey);
		m_pSaFindKey->InsertAt(0, m_strFindKey);
		if (m_pSaFindKey->GetSize() > HISTORY_COUNT)
			m_pSaFindKey->SetSize(HISTORY_COUNT);
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	
	CDialog::OnOK();
}
