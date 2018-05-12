// IdicChasenDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "IdicChasen.h"
#include "IdicChasenDlg.h"

#include <shfolder.h>
#include "IdicChasenVer.h"
#include "IdicChasenDef.h"
#include "Common.h"
#include "ConvKCode.h"
#include "Html.h"
#include "IdicChasenProc.h"
#include "NotesDlg.h"
#include "ProgressDlg.h"
#include "FindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenDlg ダイアログ

CIdicChasenDlg::CIdicChasenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIdicChasenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIdicChasenDlg)
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bInitDialog = TRUE;
}

void CIdicChasenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIdicChasenDlg)
	DDX_Control(pDX, IDC_BUTTON5, m_IconButton5);
	DDX_Control(pDX, IDC_BUTTON6, m_IconButton6);
	DDX_Control(pDX, IDC_BUTTON7, m_IconButton7);
	DDX_Control(pDX, IDC_BUTTON8, m_IconButton8);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIdicChasenDlg, CDialog)
	//{{AFX_MSG_MAP(CIdicChasenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, OnDropdownCombo1)
	ON_EN_SETFOCUS(IDC_EDIT15, OnSetfocusEdit15)
	ON_EN_KILLFOCUS(IDC_EDIT15, OnKillfocusEdit15)
	ON_EN_SETFOCUS(IDC_EDIT16, OnSetfocusEdit16)
	ON_EN_KILLFOCUS(IDC_EDIT16, OnKillfocusEdit16)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnColumnclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList1)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
//	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenDlg メッセージ ハンドラ

BOOL CIdicChasenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	static const char* pszFuncName = "OnInitDialog";
	// キャプション タイトル
	SetWindowText(StrFormat(DNAME_IDICCHASEN " Ver.%d.%d", THIS_VER / 100, THIS_VER % 100));
	// 変数宣言
	int i;
	// アプリケーションオブジェクト
	try {
		// 変数の初期化
		m_strTrue = "True";
		m_strFalse = "False";
		m_strSwShowNormal ="ShowNormal";
		m_strSwShowMinimized ="ShowMinimized";
		m_strSwShowMaximized ="ShowMaximized";
		m_strMale ="Male";
		m_strFemale ="Female";
		m_strDefaultTimeDiff = "+0900";
		m_nBirthPrefecture = CB_ERR;
		m_nLastSortCol = -1;
		m_nLastTopIdx = -1;
		m_nLastFindItemIdx = -1;
		// OS のバージョン
		m_OSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&m_OSVI);
		// データフォルダ
		CString strAppDataDir = GetShFolderPath(CSIDL_APPDATA | CSIDL_FLAG_CREATE);
		if (strAppDataDir.Right(1) == "\\")
			strAppDataDir = strAppDataDir.Left(strAppDataDir.GetLength() - 1);
		m_strDataDir = strAppDataDir + "\\" DNAME_IDICCHASEN;
		if (! CFile::GetStatus(m_strDataDir, m_FileStatus))
			if (! CreateDirectory(m_strDataDir, NULL)) {
				MessageBox(StrFormat(ERRMSG_DETAIL, pszFuncName, "CreateDirectory", (LPCTSTR)GetLastErrorMessage()), NULL, MB_ICONSTOP);
				return TRUE;
			}
		// ファイルパス
		m_strProfileFPath = m_strDataDir + "\\" FNAME_PROFILE;
		m_strFindKeyFPath = m_strDataDir + "\\" FINDKEY_FNAME;
		// バージョンアップ
		VerCheck0();
		// リストコントロール
		CListCtrl* pListCtrl1 = (CListCtrl *)GetDlgItem(IDC_LIST1);
		CListCtrl* pListCtrl2 = (CListCtrl *)GetDlgItem(IDC_LIST2);
		// デフォルトの Rect
		GetWindowRect(&m_RectDlg);
		pListCtrl1->GetWindowRect(&m_RectListCtrl1);
		pListCtrl2->GetWindowRect(&m_RectListCtrl2);
		// LastStatus
		LoadLastStatus();
		// 検索キー
		if (CFile::GetStatus(m_strFindKeyFPath, m_FileStatus)) {
			CString strLine;
			CStdioFile StdioFile(m_strFindKeyFPath, CFile::modeRead);
			while (StdioFile.ReadString(strLine))
				m_SaFindKey.Add(strLine);
			StdioFile.Close();
			if (m_SaFindKey.GetSize() > HISTORY_COUNT)
				m_SaFindKey.SetSize(HISTORY_COUNT);
		}
		// コンボボックス
		SetBirthPrefectureComboRect();
		// ボタン
		for (i = 0; i < 4; i ++)
			((CButton*)GetDlgItem(IDC_BUTTON5 + i))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1 + i));
		// リストコントロール
		LOGFONT LfCtrl;
		pListCtrl1->GetFont()->GetLogFont(&LfCtrl);
		LfCtrl.lfHeight = -85;
		m_FontListBox.CreatePointFontIndirect(&LfCtrl);
		pListCtrl1->SetFont(&m_FontListBox);
		pListCtrl2->SetFont(&m_FontListBox);
		int nDlgWidth = m_RectDlg.Width();
		pListCtrl1->InsertColumn(0, "順位", LVCFMT_LEFT, 49 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(0, "姓名", LVCFMT_LEFT, 88 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(1, "生年月日 年齢", LVCFMT_CENTER, 92 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(2, "血液型", LVCFMT_CENTER, 50 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(3, "恋愛", LVCFMT_RIGHT, 37 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(4, "友人", LVCFMT_RIGHT, 37 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(5, "家族", LVCFMT_RIGHT, 37 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(6, "金銭", LVCFMT_RIGHT, 37 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(7, "師弟", LVCFMT_RIGHT, 37 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(8, "ﾋﾞｼﾞﾈｽ", LVCFMT_RIGHT, 50 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(9, "ﾗｲﾊﾞﾙ", LVCFMT_RIGHT, 46 * nDlgWidth / 640);
		pListCtrl2->InsertColumn(10, "合計", LVCFMT_RIGHT, 37 * nDlgWidth / 640);
		// ツールヒント
		EnableToolTips();
		// バージョンアップ
		VerCheck1();
		// InitDialog 完了
		m_bInitDialog = FALSE;
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	catch (CFileException* pEx) {
		MessageBox(StrFormat(ERRMSG_FILEEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	// フック
	m_hHook = SetWindowsHookEx( WH_GETMESSAGE, GetMsgProc, NULL, GetCurrentThreadId() );
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CIdicChasenDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CIdicChasenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIdicChasenDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	if (m_hHook)
		UnhookWindowsHookEx( m_hHook );
}

void CIdicChasenDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	CDialog::OnOK();
}

void CIdicChasenDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	static const char* pszFuncName = "OnCancel";
	// 変数宣言
	int i;
	int imax;
	try {
		// LastStatus
		SaveLastStatus();
		// 検索キー
		CStringBuffer strWrText;
		for (i = 0, imax = m_SaFindKey.GetSize(); i < imax; i ++)
			strWrText += m_SaFindKey[i] + '\n';
		CStdioFile StdioFile(m_strFindKeyFPath, CFile::modeCreate | CFile::modeWrite);
		StdioFile.WriteString(strWrText);
		StdioFile.Close();
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	catch (CFileException* pEx) {
		MessageBox(StrFormat(ERRMSG_FILEEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	
	CDialog::OnCancel();
}

HBRUSH CIdicChasenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: この位置で DC のアトリビュートを変更してください
	int nID = pWnd->GetDlgCtrlID();
	if (! m_IconButton5.m_hTheme  &&  nID >= IDC_GROUPBOX1  &&  nID <= IDC_GROUPBOX12)
		pDC->SetTextColor(RGB(0, 0, 255));
	
	// TODO: デフォルトのブラシが望みのものでない場合には、違うブラシを返してください
	return hbr;
}

void CIdicChasenDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	if (! m_bInitDialog  &&  nType != SIZE_MINIMIZED) {
		DlgSizeCtlMove();
		((CListCtrl *)GetDlgItem(IDC_LIST1))->DeleteAllItems();
		SetRank();
	}
}

void CIdicChasenDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (m_nLastTopIdx != -1) {
		CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
		if (pListCtrl->GetItemCount()  &&  pListCtrl->GetTopIndex() != m_nLastTopIdx) {
			((CListCtrl *)GetDlgItem(IDC_LIST1))->DeleteAllItems();
			SetRank();
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CIdicChasenDlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT nID =pNMHDR->idFrom;
	if (pTTT->uFlags & TTF_IDISHWND)
	{
		// idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
		if(nID)
		{
			pTTT->lpszText = MAKEINTRESOURCE(nID);
			pTTT->hinst = AfxGetResourceHandle();
			return(TRUE);
		}
	}
	return(FALSE);
}

void CIdicChasenDlg::OnButton1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CFileDialog FileDialog(TRUE, "exe", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "EXE Files (*.exe)|*.exe||", this);
	if (FileDialog.DoModal() == IDOK) {
		m_strChasenFPath = FileDialog.GetPathName();
		SetCtrlParm();
	}
}

void CIdicChasenDlg::OnButton2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files (*.*)|*.*||", this);
	if (FileDialog.DoModal() == IDOK) {
		m_strIdicFPath = FileDialog.GetPathName();
		SetCtrlParm();
	}
}

void CIdicChasenDlg::OnButton3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	static const char* pszFuncName = "OnButton3";
	// 変数宣言
	int i;
	int j;
	int k;
	int imax;
	int nSleepCount;
	// メインウィンドウ
	CRect RectIdicChasen;
	GetWindowRect(&RectIdicChasen);
	try {
		// コントロール
		GetCtrlParm();
		if (! m_bDaily) {
			// 全データ削除
			m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
			m_MstpIdicName.RemoveAll();
#endif
			ClearRank();
			((CListCtrl *)GetDlgItem(IDC_LIST2))->DeleteAllItems();
			m_nLastSortCol = -1;
		}
		// 注意
		if (! m_bDaily  &&  ! m_bExeNotes) {
			CNotesDlg NotesDlg;
			NotesDlg.DoModal();
			m_bExeNotes = NotesDlg.m_bExeNotes;
		}
		// コントロール
		if (GetFNameFromFPath(m_strIdicFPath).CompareNoCase("i-dic") != 0) {
			MessageBox(StrFormat("%s: 「I-dic（アイドル人名辞書）」の辞書ファイルのファイル名が i-dic でありません。", pszFuncName), NULL, MB_ICONSTOP);
			return;
		}
		if (! m_bBirthDate) {
			MessageBox(StrFormat(ERRMSG_NOINPUT, pszFuncName, "生年月日"), NULL, MB_ICONSTOP);
			return;
		}
		if (! m_bBirthTimeUnknown  &&  ! m_bBirthTime) {
			MessageBox(StrFormat(ERRMSG_NOINPUT, pszFuncName, "出生時"), NULL, MB_ICONSTOP);
			return;
		}
		if (! m_bBirthTimeUnknown  &&  ! m_bBirthLongLat) {
			MessageBox(StrFormat(ERRMSG_NOINPUT, pszFuncName, "出生地"), NULL, MB_ICONSTOP);
			return;
		}
		if (! m_bBirthTimeUnknown  &&  ! m_bTimeDiff) {
			MessageBox(StrFormat(ERRMSG_NOINPUT, pszFuncName, "世界時との時差"), NULL, MB_ICONSTOP);
			return;
		}
		// ファイル
		if (! CFile::GetStatus(m_strIdicFPath, m_FileStatus)) {
			MessageBox(StrFormat(ERRMSG_NOTFOUND, pszFuncName, m_strIdicFPath), NULL, MB_ICONSTOP);
			return;
		}
		// 色
		COLORREF crGraphBack;
		COLORREF crBack;
		if (! m_bDaily) {
			// チャート占星術の「設定」の「色」の「色１」、「色２」
			CDWordArray DwaChasenBk;
			DwaChasenBk.Add(0xf8d8a8);
			DwaChasenBk.Add(0xa8f8f8);
			HKEY Hkey;
			if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\chasen", 0, KEY_ALL_ACCESS, &Hkey) == ERROR_SUCCESS) {
				char szData[16300];
				DWORD cbData;
				LONG nError;
				for (i = 0; i < 2; i ++) {
					cbData = 16300;
					if (RegQueryValueEx(Hkey, "Cl" + IToA(i), NULL, NULL, (LPBYTE)szData, &cbData) == ERROR_SUCCESS)
						if (szData[0] == '$')
						{
							sscanf(szData, "$%x", &DwaChasenBk[i]);
							TRACE("%x\n", DwaChasenBk[i]);
						}
						else
							if (strcmp(szData, "clBlack") == 0)
								DwaChasenBk[i] = 0x000000;
							else if (strcmp(szData, "clMaroon") == 0)
								DwaChasenBk[i] = 0x000080;
							else if (strcmp(szData, "clGreen") == 0)
								DwaChasenBk[i] = 0x008000;
							else if (strcmp(szData, "clOlive") == 0)
								DwaChasenBk[i] = 0x008080;
							else if (strcmp(szData, "clNavy") == 0)
								DwaChasenBk[i] = 0x800000;
							else if (strcmp(szData, "clPurple") == 0)
								DwaChasenBk[i] = 0x800080;
							else if (strcmp(szData, "clTeal") == 0)
								DwaChasenBk[i] = 0x808000;
							else if (strcmp(szData, "clSilver") == 0)
								DwaChasenBk[i] = 0xC0C0C0;
							else if (strcmp(szData, "clGray") == 0)
								DwaChasenBk[i] = 0x808080;
							else if (strcmp(szData, "clRed") == 0)
								DwaChasenBk[i] = 0x0000FF;
							else if (strcmp(szData, "clLime") == 0)
								DwaChasenBk[i] = 0x00FF00;
							else if (strcmp(szData, "clYellow") == 0)
								DwaChasenBk[i] = 0x00FFFF;
							else if (strcmp(szData, "clBlue") == 0)
								DwaChasenBk[i] = 0xFF0000;
							else if (strcmp(szData, "clFuchsia") == 0)
								DwaChasenBk[i] = 0xFF00FF;
							else if (strcmp(szData, "clAqua") == 0)
								DwaChasenBk[i] = 0xFFFF00;
							else if (strcmp(szData, "clWhite") == 0)
								DwaChasenBk[i] = 0xFFFFFF;
				}
				if ((nError = RegCloseKey(Hkey)) != ERROR_SUCCESS) {
					MessageBox(StrFormat(ERRMSG_DETAIL, pszFuncName, "RegCloseKey", (LPCTSTR)GetLastErrorMessage(nError)), NULL, MB_ICONSTOP);
					return;
				}
			}
			// 現在の色数での色の取得
			CDC* pDC = GetDC();
			COLORREF crDlg = pDC->GetPixel(0, 0);
			pDC->SetPixel(0, 0, DwaChasenBk[1]);
			crGraphBack = pDC->GetPixel(0, 0);
			pDC->SetPixel(0, 0, DwaChasenBk[0]);
			crBack = pDC->GetPixel(0, 0);
			pDC->SetPixel(0, 0, crDlg);
			ReleaseDC(pDC);
		}
		// チャート占星術の実行
		if (ExecChasen(0, m_strName, m_nSex, m_DtBirth, m_bBirthTimeUnknown))
			return;
		// 日運
		if (m_bDaily) {
			// 日運ボタン
			static const LPARAM lParamDailyPoint = 220 << 16 | 45;
			m_pWndChasen->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, lParamDailyPoint);
			m_pWndChasen->PostMessage(WM_LBUTTONUP, 0, lParamDailyPoint);
			return;
		}
		// プログレスバー
		CProgressDlg ProgressDlg;
		ProgressDlg.m_pIdicChasenDlg = this;
		ProgressDlg.m_lpszDocument = "I-dic 読み込み処理";
		ProgressDlg.Create(IDD_PROGRESS_DIALOG);
		CRect RectProgressDlg;
		ProgressDlg.GetWindowRect(&RectProgressDlg);
		ProgressDlg.MoveWindow(RectProgressDlg.left, m_RectMainPanel.bottom, RectProgressDlg.Width(), RectProgressDlg.Height());
		ProgressDlg.ShowWindow(SW_SHOW);
		ProgressDlg.UpdateWindow();
		ProgressDlg.SetForegroundWindow();
		ProgressDlg.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		// メインウィンドウ
		CRect RectDesktop;
		GetDesktopWindow()->GetWindowRect(&RectDesktop);
		MoveWindow(RectDesktop.right, RectDesktop.bottom, RectIdicChasen.Width(), RectIdicChasen.Height());
		// I-dic 読み込み
		CString strLine;
		int nStrIdx0;
		int nStrIdx1;
#ifdef YAHOOIDIC
		int nIndex;
#endif
		CString strField;
		int nField;
		CAffinity Affinity;
		int nYear;
		int nMonth;
		BOOL bErr;
		CStdioFile StdioFileIdic(m_strIdicFPath, CFile::modeRead);
		ProgressDlg.SetRange(10 * StdioFileIdic.GetLength());
		while (StdioFileIdic.ReadString(strLine)) {
			nStrIdx0 = 0;
			bErr = FALSE;
			for (i = 0; i <= 8; i ++) {
				if ((nStrIdx1 = strLine.Find('\t', nStrIdx0)) == -1) {
					bErr = TRUE;
					break;
				}
				switch (i) {
				case 5:
				case 6:
				case 7:
					if (nStrIdx0 == nStrIdx1) {
						bErr = TRUE;
						break;
					}
				case 1:
				case 2:
				case 8:
					strField = strLine.Mid(nStrIdx0, nStrIdx1 - nStrIdx0);
					switch (i) {
					case 2:
					case 5:
					case 6:
					case 7:
						nField = atoi(strField);
					}
					switch (i) {
					case 1:
						Affinity.m_strName = strField;
#ifdef YAHOOIDIC
						if ((nIndex = strField.Find(' ')) != -1  &&  nIndex >= 2  &&  _ismbblead(strField[nIndex - 2])  &&  _ismbblead(strField[nIndex + 1]))
							strField.Delete(nIndex);
						m_MstpIdicName[strField] = (void *)0;
#endif
						break;
					case 2:
						Affinity.m_nGenre = nField;
						break;
					case 5:
						nYear = nField;
						break;
					case 6:
						nMonth = nField;
						break;
					case 7:
						if (nYear > 1899  ||  nYear == 1899  &&  nMonth == 12  &&  nField >= 30)
							Affinity.m_DtBirth.SetDate(nYear, nMonth, nField);
						else
							bErr = TRUE;
						break;
					case 8:
						Affinity.m_strBloodType = strField;
					}
				}
				if (bErr)
					break;
				nStrIdx0 = nStrIdx1 + 1;
			}
			if (! bErr)
				m_AffinityArray.Add(Affinity);
			if (m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT  ||  m_OSVI.dwMinorVersion > 0)
				ProgressDlg.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			ProgressDlg.SetStep((strLine.GetLength() + sizeof('\n')) * 10);
			ProgressDlg.StepIt();
			if (ProgressDlg.m_bStopReq) {
				MoveWindow(&RectIdicChasen);
				ClipCursor(NULL);
				EndChasen(m_pWndChasen);
				ProgressDlg.Destroy();
				MessageBox("I-dic 読み込み処理を中止しました。");
				m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
				m_MstpIdicName.RemoveAll();
#endif
				return;
			}
		}
		StdioFileIdic.Close();
		// 相性ボタン
		static const LPARAM lParamAffinityPoint = 270 << 16 | 45;
		m_pWndChasen->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, lParamAffinityPoint);
		m_pWndChasen->PostMessage(WM_LBUTTONUP, 0, lParamAffinityPoint);
		// メインパネルウィンドウ
		CWnd* pWndMainPanel1;
		nSleepCount = 0;
		while ((pWndMainPanel1 = m_pWndChasen->ChildWindowFromPoint(PointMainPanel)) == m_pWndMainPanel0) {
			if (nSleepCount ++ == 50) {
				MoveWindow(&RectIdicChasen);
				ClipCursor(NULL);
				EndChasen(m_pWndChasen);
				ProgressDlg.Destroy();
				MessageBox(StrFormat(ERRMSG_TIMEOUT, pszFuncName, "ChildWindowFromPoint", "メインパネル2"), NULL, MB_ICONSTOP);
				m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
				m_MstpIdicName.RemoveAll();
#endif
				return;
			}
			Sleep(100);
		}
		// 相手の生年月日ウィンドウ
		static const POINT PointPartnerBirth = {150, 275};
		CWnd* pWndPartnerBirth = pWndMainPanel1->ChildWindowFromPoint(PointPartnerBirth);
		// 相手の生年月日の年、月、日入力ウィンドウ
		static const POINT PointPartnerBirthYear = {95, 60};
		static const POINT PointPartnerBirthMonth = {150, 60};
		static const POINT PointPartnerBirthDay = {200, 60};
		CWnd* pWndPartnerBirthYear = pWndPartnerBirth->ChildWindowFromPoint(PointPartnerBirthYear);
		CWnd* pWndPartnerBirthMonth = pWndPartnerBirth->ChildWindowFromPoint(PointPartnerBirthMonth);
		CWnd* pWndPartnerBirthDay = pWndPartnerBirth->ChildWindowFromPoint(PointPartnerBirthDay);
		// 判定ボタン
		static const POINT PointJudgment = {310, 295};
		CWnd* pWndJudgment = pWndMainPanel1->ChildWindowFromPoint(PointJudgment);
		// クリアボタン
		static const POINT PointClear = {310, 350};
		CWnd* pWndClear = pWndMainPanel1->ChildWindowFromPoint(PointClear);
		// デバイスコンテキスト
		CDC* pDCMainPanel1 = pWndMainPanel1->GetDC();
		// メモリデバイスコンテキスト
		CDC MemoryDC;
		MemoryDC.CreateCompatibleDC(pDCMainPanel1);
		CBitmap Bitmap;
		Bitmap.CreateCompatibleBitmap(pDCMainPanel1, 240, 1);
		MemoryDC.SelectObject(&Bitmap);
		// プログレスバー
		ProgressDlg.SetDocument("アイドル相性判定処理");
		ProgressDlg.SetRange(10 * m_AffinityArray.GetSize());
		ProgressDlg.SetStep(10);
		// ウィンドウ
		if (m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT  ||  m_OSVI.dwMinorVersion > 0)
			ProgressDlg.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		else
			m_pWndChasen->SetForegroundWindow();
		// 相性判定
		COLORREF cr;
		COLORREF crGraphLine = RGB(0, 0, 0);
		int nKeyCount;
		BOOL bTimeout;
		int nTotal;
		for (i = 0, imax = m_AffinityArray.GetSize(); i < imax; i ++) {
			// 判定
			nKeyCount = 0;
			while (1) {
				// 相手の生年月日の入力
				if (nKeyCount) {
					pWndPartnerBirthDay->PostMessage(WM_SETFOCUS);
					pWndPartnerBirthYear->PostMessage(WM_SETFOCUS);
				}
				PostWndText(pWndPartnerBirthYear, IToA(m_AffinityArray[i].m_DtBirth.GetYear()));
				if (nKeyCount)
					pWndPartnerBirthMonth->PostMessage(WM_SETFOCUS);
				PostWndText(pWndPartnerBirthMonth, IToA(m_AffinityArray[i].m_DtBirth.GetMonth()));
				if (nKeyCount)
					pWndPartnerBirthDay->PostMessage(WM_SETFOCUS);
				PostWndText(pWndPartnerBirthDay, IToA(m_AffinityArray[i].m_DtBirth.GetDay()));
				// 判定の入力
				pWndJudgment->PostMessage(WM_KEYDOWN, VK_SPACE, 0x39 << 16 | 0x0001);
				pWndJudgment->PostMessage(WM_KEYUP, VK_SPACE, 0xc0000000 | 0x39 << 16 | 0x0001);
				// 描画待ち
				nSleepCount = 0;
				bTimeout = FALSE;
				while (pDCMainPanel1->GetPixel(239, 233) != crGraphBack) {
					if (nSleepCount ++ == 100) {
						bTimeout = TRUE;
						break;
					}
					Sleep(1);
				}
				if (! bTimeout)
					break;
				if (nKeyCount ++ == 10) {
					MoveWindow(&RectIdicChasen);
					ClipCursor(NULL);
					MemoryDC.DeleteDC();
					pWndMainPanel1->ReleaseDC(pDCMainPanel1);
					EndChasen(m_pWndChasen);
					ProgressDlg.Destroy();
					MessageBox(StrFormat(ERRMSG_TIMEOUT, pszFuncName, "GetPixel", "crGraphBack"), NULL, MB_ICONSTOP);
					m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
					m_MstpIdicName.RemoveAll();
#endif
					return;
				}
			}
			// 判定値
			nTotal = 0;
			for (j = 0; j < 7; j ++) {
				// ビットマップのコピー
				MemoryDC.BitBlt(0, 0, 240, 1, pDCMainPanel1, 106, 22 + 31 * j, SRCCOPY);
				for (k = 0; k < 100; k ++) {
					cr = MemoryDC.GetPixel(k * 240 / 100, 0);
					if (cr == crGraphBack  ||  cr == crGraphLine)
						break;
				}
				nTotal += m_AffinityArray[i].m_pnAffinity[j] = k;
			}
			m_AffinityArray[i].m_pnAffinity[7] = nTotal;
			// クリア
			nKeyCount = 0;
			while (1) {
				// クリアの入力
				pWndClear->PostMessage(WM_KEYDOWN, VK_SPACE, 0x39 << 16 | 0x0001);
				pWndClear->PostMessage(WM_KEYUP, VK_SPACE, 0xc0000000 | 0x39 << 16 | 0x0001);
				// 描画待ち
				nSleepCount = 0;
				bTimeout = FALSE;
				while (pDCMainPanel1->GetPixel(239, 233) != crBack) {
					if (nSleepCount ++ == 100) {
						bTimeout = TRUE;
						break;
					}
					Sleep(1);
				}
				if (! bTimeout)
					break;
				if (nKeyCount ++ == 10) {
					MoveWindow(&RectIdicChasen);
					ClipCursor(NULL);
					MemoryDC.DeleteDC();
					pWndMainPanel1->ReleaseDC(pDCMainPanel1);
					EndChasen(m_pWndChasen);
					ProgressDlg.Destroy();
					MessageBox(StrFormat(ERRMSG_TIMEOUT, pszFuncName, "GetPixel", "crBack"), NULL, MB_ICONSTOP);
					m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
					m_MstpIdicName.RemoveAll();
#endif
					return;
				}
			}
			ProgressDlg.StepIt();
			if (ProgressDlg.m_bStopReq) {
				MoveWindow(&RectIdicChasen);
				ClipCursor(NULL);
				MemoryDC.DeleteDC();
				pWndMainPanel1->ReleaseDC(pDCMainPanel1);
				EndChasen(m_pWndChasen);
				ProgressDlg.Destroy();
				MessageBox("アイドル相性判定処理を中止しました。");
				m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
				m_MstpIdicName.RemoveAll();
#endif
				return;
			}
		}
		// リソースの解放
		MemoryDC.DeleteDC();
		pWndMainPanel1->ReleaseDC(pDCMainPanel1);
		EndChasen(m_pWndChasen);
		ProgressDlg.Destroy();
		ClipCursor(NULL);
		// リストコントロール
		SetList();
	}
	catch (CMemoryException* pEx) {
		ClipCursor(NULL);
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	catch (CFileException* pEx) {
		ClipCursor(NULL);
		MessageBox(StrFormat(ERRMSG_FILEEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	// メインウィンドウ
	MoveWindow(&RectIdicChasen);
}

void CIdicChasenDlg::OnButton4()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CDlProgressDlg DlProgressDlg;
	DlProgressDlg.m_pIdicChasenDlg = this;
	DlProgressDlg.Create(IDD_DLPROGRESS_DIALOG);
	DlProgressDlg.ShowWindow(SW_SHOW);
	DlProgressDlg.UpdateWindow();

	CString strPath;
	CMapStringToPtr MstpCategory;

	m_MstpYahooTVPeopleName.RemoveAll();
	m_SaYahooTVPeopleName.RemoveAll();

	m_MstpYahooTVPeopleName["叶美香"] = (void *)0;	//33
	m_MstpYahooTVPeopleName["三倉佳奈"] = (void *)0;	//108
	m_MstpYahooTVPeopleName["大江麻理子"] = (void *)0;	//136
	m_MstpYahooTVPeopleName["木内美帆"] = (void *)0;	//218

	MstpCategory[strPath] = (void *)0;

//	MstpCategory["アーティスト"] = (void *)0;
//	MstpCategory["アイドル"] = (void *)0;
	MstpCategory["アナウンサー"] = (void *)0;
//	MstpCategory["ウェブログ"] = (void *)0;
//	MstpCategory["お笑い"] = (void *)0;
	MstpCategory["グラビアアイドル"] = (void *)0;
//	MstpCategory["子役"] = (void *)0;
//	MstpCategory["声優"] = (void *)0;
//	MstpCategory["バーチャルタレント"] = (void *)0;
	MstpCategory["俳優、女優"] = (void *)0;
	MstpCategory["モデル"] = (void *)0;
//	MstpCategory["ものまね"] = (void *)0;
//	MstpCategory["ラジオタレント"] = (void *)0;
//	MstpCategory["レースクイーン"] = (void *)0;
//	MstpCategory["その他"] = (void *)0;

//	MstpCategory["地域別"] = (void *)0;
	MstpCategory["女性"] = (void *)0;
	MstpCategory["男性"] = (void *)0;
//	MstpCategory["リンク集と総合情報"] = (void *)0;
//	MstpCategory["海外女優"] = (void *)0;
//	MstpCategory["海外男優"] = (void *)0;
//	MstpCategory["韓国俳優、女優"] = (void *)0;
	MstpCategory["国内女優"] = (void *)0;
	MstpCategory["国内男優"] = (void *)0;
//	MstpCategory["ファッション"] = (void *)0;
//	MstpCategory["モデル事務所"] = (void *)0;

	BOOL bError = FALSE;
	do {
		strPath = "芸能人、タレント";
		if (GetNameList(pszUrl0, strPath, MstpCategory, DlProgressDlg) != 0) {
			bError = TRUE;
			break;
		}
		strPath = "芸能人、タレント/アーティスト/ジャパニーズポップス";
		if (GetNameList(pszUrl1, strPath, MstpCategory, DlProgressDlg) != 0) {
			bError = TRUE;
			break;
		}
		MessageBox("最新の Yahoo! 芸能、タレント名のダウンロードが完了しました。", NULL);
	} while (0);
	if (bError) {
		m_MstpYahooTVPeopleName.RemoveAll();
		m_SaYahooTVPeopleName.RemoveAll();
	}

	OnCheck5();

	DlProgressDlg.Destroy();
}

void CIdicChasenDlg::OnButton5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	AfxGetApp()->WinHelp(0);
}

void CIdicChasenDlg::OnButton6() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	static const char* pszFuncName = "OnButton6";
	try {
		if (m_AffinityArray.GetSize() == 0) {
			MessageBox(StrFormat(ERRMSG_NOTFOUND, pszFuncName, "実行結果"), NULL, MB_ICONSTOP);
			return;
		}
		CFindDlg FindDlg;
		FindDlg.m_pSaFindKey = &m_SaFindKey;
		if (FindDlg.DoModal() == IDOK) {
			CString strFindKey(FindDlg.m_strFindKey);
			CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
			LVFINDINFO LVFindInfo;
			LVFindInfo.flags = LVFI_STRING;
			LVFindInfo.psz = strFindKey.GetBuffer(16);
			int nItemIdx = pListCtrl->FindItem(&LVFindInfo);
			strFindKey.ReleaseBuffer();
			if (nItemIdx == -1) {
				MessageBox(StrFormat(ERRMSG_NOTFOUND, pszFuncName, strFindKey), NULL, MB_ICONSTOP);
				return;
			}
			pListCtrl->EnsureVisible(nItemIdx, FALSE);
		}
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
}

void CIdicChasenDlg::OnButton7() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	static const char* pszFuncName = "OnButton7";
	int i;
	try {
		CFileDialog FileDialog(TRUE, "csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "CSV Files (*.csv)|*.csv||", this);
		if (FileDialog.DoModal() == IDOK) {
			// 全データ削除
			m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
			m_MstpIdicName.RemoveAll();
#endif
			ClearRank();
			((CListCtrl *)GetDlgItem(IDC_LIST2))->DeleteAllItems();
			m_nLastSortCol = -1;
			// プログレスバー
			CProgressDlg ProgressDlg;
			ProgressDlg.m_pIdicChasenDlg = this;
			ProgressDlg.m_lpszDocument = "CSV、INI ファイル読み込み処理";
			ProgressDlg.Create(IDD_PROGRESS_DIALOG);
			ProgressDlg.CenterWindow();
			ProgressDlg.ShowWindow(SW_SHOW);
			ProgressDlg.UpdateWindow();
			// CSV ファイル読み込み
			CString strFPath(FileDialog.GetPathName());
			CString strLine;
			int nStrIdx0;
			int nStrIdx1;
			int nStrIdx2;
#ifdef YAHOOIDIC
			int nIndex;
#endif
			CString strField;
			int nTotal;
			CAffinity Affinity;
			BOOL bErr;
			CStdioFile StdioFile(strFPath, CFile::modeRead);
			ProgressDlg.SetRange(10 * StdioFile.GetLength());
			while (StdioFile.ReadString(strLine)) {
				nStrIdx0 = 0;
				nTotal = 0;
				bErr = FALSE;
				for (i = 0; i < 11; i ++) {
					if (strLine.Mid(nStrIdx0, 1) == "\"") {
						nStrIdx0 ++;
						if ((nStrIdx1 = strLine.Find('"', nStrIdx0)) == -1) {
							bErr = TRUE;
							break;
						}
						nStrIdx2 = nStrIdx1 + 2;
					} else {
						if ((nStrIdx1 = strLine.Find(',', nStrIdx0)) == -1) {
							if (i == 10) {
								nStrIdx1 = strLine.GetLength();
							} else {
								bErr = TRUE;
								break;
							}
						}
						nStrIdx2 = nStrIdx1 + 1;
					}
					CString s = strLine.Mid(nStrIdx0, nStrIdx1 - nStrIdx0);
					strField = strLine.Mid(nStrIdx0, nStrIdx1 - nStrIdx0);
					switch (i) {
					case 0:
						Affinity.m_strName = strField;
#ifdef YAHOOIDIC
						if ((nIndex = strField.Find(' ')) != -1  &&  nIndex >= 2  &&  _ismbblead(strField[nIndex - 2])  &&  _ismbblead(strField[nIndex + 1]))
							strField.Delete(nIndex);
						m_MstpIdicName[strField] = (void *)0;
#endif
						break;
					case 1:
						Affinity.m_nGenre = atoi(strField);
						break;
					case 2:
						if (! Affinity.m_DtBirth.ParseDateTime(strField))
							bErr = TRUE;
						break;
					case 3:
						Affinity.m_strBloodType = strField;
						break;
					default:
						nTotal += Affinity.m_pnAffinity[i - 4] = atoi(strField);
					}
					if (bErr)
						break;
					nStrIdx0 = nStrIdx2;
				}
				if (bErr) {
					MessageBox(StrFormat(ERRMSG, pszFuncName, "ファイルフォーマット"), NULL, MB_ICONSTOP);
					break;
				}
				Affinity.m_pnAffinity[7] = nTotal;
				m_AffinityArray.Add(Affinity);
				ProgressDlg.SetStep((strLine.GetLength() + sizeof('\n')) * 10);
				ProgressDlg.StepIt();
				if (ProgressDlg.m_bStopReq) {
					ProgressDlg.Destroy();
					MessageBox("CSV、INI ファイル読み込み処理を中止しました。");
					m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
					m_MstpIdicName.RemoveAll();
#endif
					return;
				}
			}
			StdioFile.Close();
			// LastStatus
			strFPath = strFPath.Left(strFPath.ReverseFind('.') + 1) + "ini";
			if (CFile::GetStatus(strFPath, m_FileStatus)) {
				LoadLastStatus(strFPath);

				// バージョンアップ
				VerCheck1();
			}
			ProgressDlg.Destroy();
			// リストコントロール
			SetList();
		}
	}
	catch (CFileException* pEx) {
		MessageBox(StrFormat(ERRMSG_FILEEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
}

void CIdicChasenDlg::OnButton8()
{
	static const char* pszFuncName = "OnButton8";
	try {
		if (m_AffinityArray.GetSize() == 0) {
			MessageBox(StrFormat(ERRMSG_NOTFOUND, pszFuncName, "実行結果"), NULL, MB_ICONSTOP);
			return;
		}
		// プログレスバー
		CProgressDlg ProgressDlg;
		ProgressDlg.m_pIdicChasenDlg = this;
		ProgressDlg.m_lpszDocument = "CSV、INI ファイル書き出し処理";
		ProgressDlg.Create(IDD_PROGRESS_DIALOG);
		ProgressDlg.SetRange(10 * m_AffinityArray.GetSize());
		ProgressDlg.CenterWindow();
		ProgressDlg.ShowWindow(SW_SHOW);
		ProgressDlg.UpdateWindow();
		// CSV ファイル書き出し処理
		CFileDialog FileDialog(FALSE, "csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "CSV Files (*.csv)|*.csv||", this);
		if (FileDialog.DoModal() == IDOK) {
			CString strFPath(FileDialog.GetPathName());
			CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeWrite);
			for (int i = 0, imax = m_AffinityArray.GetSize(); i < imax; i ++) {
				CAffinity& Affinity = m_AffinityArray[i];
				StdioFile.WriteString(
					StrFormat(
						"\"%s\",%d,%s,\"%s\",%d,%d,%d,%d,%d,%d,%d\n",
						Affinity.m_strName,
						Affinity.m_nGenre,
						Affinity.m_DtBirth.Format("%Y/%m/%d"),
						Affinity.m_strBloodType,
						Affinity.m_pnAffinity[0],
						Affinity.m_pnAffinity[1],
						Affinity.m_pnAffinity[2],
						Affinity.m_pnAffinity[3],
						Affinity.m_pnAffinity[4],
						Affinity.m_pnAffinity[5],
						Affinity.m_pnAffinity[6]
					)
				);
				ProgressDlg.StepIt();
				if (ProgressDlg.m_bStopReq) {
					ProgressDlg.Destroy();
					MessageBox("CSV、INI ファイル書き出し処理を中止しました。");
					StdioFile.Close();
					DeleteFile(FileDialog.GetPathName());
					return;
				}
			}
			StdioFile.Close();
			// LastStatus
			SaveLastStatus(strFPath.Left(strFPath.ReverseFind('.') + 1) + "ini");
		}
		ProgressDlg.Destroy();
	}
	catch (CFileException* pEx) {
		MessageBox(StrFormat(ERRMSG_FILEEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
}

void CIdicChasenDlg::OnCheck1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	BOOL bBirthTime = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck() == 0;
	GetDlgItem(IDC_RADIO3)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_RADIO4)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT7)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT8)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_COMBO1)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_RADIO5)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_RADIO6)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT9)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_TEXT1)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT10)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_TEXT2)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_RADIO7)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_RADIO8)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT11)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_TEXT3)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT12)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_TEXT4)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_GROUPBOX7)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_RADIO9)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_RADIO10)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT13)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_TEXT5)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_EDIT14)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_TEXT6)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_CHECK2)->EnableWindow(bBirthTime);
	GetDlgItem(IDC_GROUPBOX8)->EnableWindow(bBirthTime);
}

void CIdicChasenDlg::OnCheck3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	BOOL bDaily = ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck() == 1;
	GetDlgItem(IDC_CHECK4)->EnableWindow(! bDaily);
	GetDlgItem(IDC_GROUPBOX10)->EnableWindow(! bDaily);
	GetDlgItem(IDC_CHECK5)->EnableWindow(! bDaily  &&  m_MstpYahooTVPeopleName.GetCount());
	GetDlgItem(IDC_BUTTON4)->EnableWindow(! bDaily);
	GetDlgItem(IDC_GROUPBOX9)->EnableWindow(! bDaily);
	GetDlgItem(IDC_EDIT15)->EnableWindow(! bDaily);
	GetDlgItem(IDC_TEXT7)->EnableWindow(! bDaily);
	GetDlgItem(IDC_EDIT16)->EnableWindow(! bDaily);
	GetDlgItem(IDC_GROUPBOX11)->EnableWindow(! bDaily);
	GetDlgItem(IDC_CHECK6)->EnableWindow(! bDaily);
	GetDlgItem(IDC_CHECK7)->EnableWindow(! bDaily);
	GetDlgItem(IDC_CHECK8)->EnableWindow(! bDaily);
	GetDlgItem(IDC_CHECK9)->EnableWindow(! bDaily);
	GetDlgItem(IDC_GROUPBOX12)->EnableWindow(! bDaily);
}

void CIdicChasenDlg::OnCheck4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateList();
}

void CIdicChasenDlg::OnCheck5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateList();
}

void CIdicChasenDlg::OnCheck6() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateList();
}

void CIdicChasenDlg::OnCheck7() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateList();
}

void CIdicChasenDlg::OnCheck8() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateList();
}

void CIdicChasenDlg::OnCheck9() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateList();
}

void CIdicChasenDlg::OnSelchangeCombo1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetCtrlParm();

	m_bBirthLongLat = TRUE;

	m_nBirthLongEW = m_nBirthLatNS = 0;

	int nBirthPrefecture = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCurSel();
	m_nBirthLongDeg = ppnPrefectureLongLat[nBirthPrefecture][0];
	m_nBirthLongMin = ppnPrefectureLongLat[nBirthPrefecture][1];
	m_nBirthLatDeg = ppnPrefectureLongLat[nBirthPrefecture][2];
	m_nBirthLatMin = ppnPrefectureLongLat[nBirthPrefecture][3];

	SetCtrlParm();
}

void CIdicChasenDlg::OnDropdownCombo1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetBirthPrefectureComboRect();
}

void CIdicChasenDlg::OnSetfocusEdit15() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetCtrlParm();
}

void CIdicChasenDlg::OnKillfocusEdit15() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nMinAge = m_nMinAge;
	GetCtrlParm();
	if (m_nMinAge != nMinAge)
		OnCheck4();
}

void CIdicChasenDlg::OnSetfocusEdit16() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetCtrlParm();
}

void CIdicChasenDlg::OnKillfocusEdit16() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nMaxAge = m_nMaxAge;
	GetCtrlParm();
	if (m_nMaxAge != nMaxAge)
		OnCheck4();
}

void CIdicChasenDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ListCtrlSort(pNMListView->iSubItem);
	
	*pResult = 0;
}

void CIdicChasenDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
	if (pListCtrl->GetItemCount() == 0)
		return;
	GetCtrlParm();
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CAffinity& Affinity = m_AffinityArray[pListCtrl->GetItemData(pNMListView->iItem)];
	if (ExecChasen(1, Affinity.m_strName, Affinity.m_nGenre - 1, Affinity.m_DtBirth, TRUE))
		return;
	static const LPARAM lParamFortunePoint = 170 << 16 | 45;
	m_pWndChasen->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, lParamFortunePoint);
	m_pWndChasen->PostMessage(WM_LBUTTONUP, 0, lParamFortunePoint);
	
	*pResult = 0;
}

void CIdicChasenDlg::DlgSizeCtlMove()
{
	// 変数宣言
	CWnd* pWnd;
	// オフセット
	CRect Rect;
	GetWindowRect(&Rect);
	int nWidthOffset = __max(0, Rect.Width() - m_RectDlg.Width());
	int nHeightOffset = __max(0, Rect.Height() - m_RectDlg.Height());
	// 順位表示リストコントロール
	pWnd = GetDlgItem(IDC_LIST1);
	pWnd->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	Rect.bottom = Rect.top + m_RectListCtrl1.Height() + nHeightOffset;
	pWnd->MoveWindow(&Rect);
	// 相性表示リストコントロール
	pWnd = GetDlgItem(IDC_LIST2);
	pWnd->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	Rect.right = Rect.left + m_RectListCtrl2.Width() + nWidthOffset;
	Rect.bottom = Rect.top + m_RectListCtrl2.Height() + nHeightOffset;
	pWnd->MoveWindow(&Rect);
	// ダイアログ
	GetWindowRect(&Rect);
	BOOL bReSize = FALSE;
	if (Rect.Width() < m_RectDlg.Width()) {
		Rect.right = Rect.left +  m_RectDlg.Width();
		bReSize = TRUE;
	}
	if (Rect.Height() < m_RectDlg.Height()) {
		Rect.bottom = Rect.top +  m_RectDlg.Height();
		bReSize = TRUE;
	}
	if (bReSize)
		MoveWindow(&Rect);
}

void CIdicChasenDlg::SetBirthPrefectureComboRect()
{
	CRect RectDesktop;
	GetDesktopWindow()->GetWindowRect(&RectDesktop);
	CWnd* pWnd = GetDlgItem(IDC_COMBO1);
	CRect Rect;
	pWnd->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	Rect.bottom = Rect.top + RectDesktop.Height();
	pWnd->MoveWindow(&Rect);
}

void CIdicChasenDlg::GetCtrlParm()
{
	static const char* pszFuncName = "GetCtrlParm";
	try {
		// chasen
		GetDlgItem(IDC_EDIT1)->GetWindowText(m_strChasenFPath);
		// I-dic
		GetDlgItem(IDC_EDIT2)->GetWindowText(m_strIdicFPath);
		// 名前
		GetDlgItem(IDC_EDIT3)->GetWindowText(m_strName);
		// 性別
		m_nSex = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) - IDC_RADIO1;
		// 誕生日、出生時
		CString strBirthYear;
		CString strBirthMonth;
		CString strBirthDay;
		CString strBirthHour;
		CString strBirthMin;
		int nBirthYear;
		int nBirthMonth;
		int nBirthDay;
		int nBirthHour = 0;
		int nBirthMin = 0;
		if (! (m_bBirthTimeUnknown = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck() == 1)) {
			int nBirthAMPM = GetCheckedRadioButton(IDC_RADIO3, IDC_RADIO4) - IDC_RADIO3;
			GetDlgItem(IDC_EDIT7)->GetWindowText(strBirthHour);
			GetDlgItem(IDC_EDIT8)->GetWindowText(strBirthMin);
			if (m_bBirthTime = strBirthHour.GetLength() && strBirthMin.GetLength()) {
				nBirthHour = (nBirthAMPM ? 12 : 0) + atoi(strBirthHour);
				nBirthMin = atoi(strBirthMin);
			}
		}
		GetDlgItem(IDC_EDIT4)->GetWindowText(strBirthYear);
		GetDlgItem(IDC_EDIT5)->GetWindowText(strBirthMonth);
		GetDlgItem(IDC_EDIT6)->GetWindowText(strBirthDay);
		if (m_bBirthDate = strBirthYear.GetLength() && strBirthMonth.GetLength() && strBirthDay.GetLength()) {
			nBirthYear = atoi(strBirthYear);
			nBirthMonth = atoi(strBirthMonth);
			nBirthDay = atoi(strBirthDay);
			m_DtBirth.SetDateTime(nBirthYear, nBirthMonth, nBirthDay, nBirthHour, nBirthMin, 0);
		}
		// 出生地
		CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
		if ((m_nBirthPrefecture = pComboBox->GetCurSel()) == CB_ERR)
			pComboBox->GetWindowText(m_strBirthPrefecture);
		else
			pComboBox->GetLBText(m_nBirthPrefecture, m_strBirthPrefecture);
		CString strBirthLongDeg;
		CString strBirthLongMin;
		CString strBirthLatDeg;
		CString strBirthLatMin;
		GetDlgItem(IDC_EDIT9)->GetWindowText(strBirthLongDeg);
		GetDlgItem(IDC_EDIT10)->GetWindowText(strBirthLongMin);
		GetDlgItem(IDC_EDIT11)->GetWindowText(strBirthLatDeg);
		GetDlgItem(IDC_EDIT12)->GetWindowText(strBirthLatMin);
		if (m_bBirthLongLat = strBirthLongDeg.GetLength() && strBirthLongMin.GetLength() && strBirthLatDeg.GetLength() && strBirthLatMin.GetLength()) {
			m_nBirthLongEW = GetCheckedRadioButton(IDC_RADIO5, IDC_RADIO6) - IDC_RADIO5;
			m_nBirthLatNS = GetCheckedRadioButton(IDC_RADIO7, IDC_RADIO8) - IDC_RADIO7;
			m_nBirthLongDeg = atoi(strBirthLongDeg);
			m_nBirthLongMin = atoi(strBirthLongMin);
			m_nBirthLatDeg = atoi(strBirthLatDeg);
			m_nBirthLatMin = atoi(strBirthLatMin);
		}
		// 時差
		CString strTimeDiffHour;
		CString strTimeDiffMinute;
		GetDlgItem(IDC_EDIT13)->GetWindowText(strTimeDiffHour);
		GetDlgItem(IDC_EDIT14)->GetWindowText(strTimeDiffMinute);
		if (m_bTimeDiff = strTimeDiffHour.GetLength() && strTimeDiffMinute.GetLength()) {
			m_nTimeDiffHour = GetCheckedRadioButton(IDC_RADIO9, IDC_RADIO10) == IDC_RADIO9 ? 1 : -1;
			m_nTimeDiffHour *= atoi(strTimeDiffHour);
			m_nTimeDiffMinute = atoi(strTimeDiffMinute);
			m_bSummerTime = ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck() == 1;
		}
		// 日運
		m_bDaily = ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck() == 1;
		// ｱｲﾄﾞﾙの性別
		m_bOppositeSex = ((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck() == 1;
		// ｱｲﾄﾞﾙの名前
		m_bYahoo = ((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck() == 1;
		// ｱｲﾄﾞﾙの年齢
		CString strMinAge;
		CString strMaxAge;
		GetDlgItem(IDC_EDIT15)->GetWindowText(strMinAge);
		GetDlgItem(IDC_EDIT16)->GetWindowText(strMaxAge);
		m_nMinAge = atoi(strMinAge);
		m_nMaxAge = atoi(strMaxAge);
		if (m_nMaxAge == 0)
			m_nMaxAge = 255;
		// ｱｲﾄﾞﾙの血液型
		m_bBloodTypeA = ((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck() == 1;
		m_bBloodTypeB = ((CButton *)GetDlgItem(IDC_CHECK7))->GetCheck() == 1;
		m_bBloodTypeO = ((CButton *)GetDlgItem(IDC_CHECK8))->GetCheck() == 1;
		m_bBloodTypeAB = ((CButton *)GetDlgItem(IDC_CHECK9))->GetCheck() == 1;
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
}

void CIdicChasenDlg::SetCtrlParm()
{
	static const char* pszFuncName = "SetCtrlParm";
	try {
		// chasen
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_strChasenFPath);
		// I-dic
		GetDlgItem(IDC_EDIT2)->SetWindowText(m_strIdicFPath);
		// 名前
		GetDlgItem(IDC_EDIT3)->SetWindowText(m_strName);
		// 性別
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1 + m_nSex);
		// 誕生日、出生時
		((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(m_bBirthTimeUnknown ? 1 : 0);
		int nBirthAMPM = 0;
		CString strBirthYear;
		CString strBirthMonth;
		CString strBirthDay;
		CString strBirthHour;
		CString strBirthMin;
		if (m_bBirthDate) {
			strBirthYear = IToA(m_DtBirth.GetYear());
			strBirthMonth = StrFormat("%02d", m_DtBirth.GetMonth());
			strBirthDay = StrFormat("%02d", m_DtBirth.GetDay());
			if (! m_bBirthTimeUnknown  &&  m_bBirthTime) {
				int nBirthHour = m_DtBirth.GetHour();
				nBirthAMPM = nBirthHour < 12 ? 0 : 1;
				strBirthHour = StrFormat("%d", nBirthHour - (nBirthAMPM ? 12 : 0));
				strBirthMin = StrFormat("%02d", m_DtBirth.GetMinute());
			}
		}
		CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO3 + nBirthAMPM);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strBirthYear);
		GetDlgItem(IDC_EDIT5)->SetWindowText(strBirthMonth);
		GetDlgItem(IDC_EDIT6)->SetWindowText(strBirthDay);
		GetDlgItem(IDC_EDIT7)->SetWindowText(strBirthHour);
		GetDlgItem(IDC_EDIT8)->SetWindowText(strBirthMin);
		OnCheck1();
		// 出生地
		if (m_strBirthPrefecture.GetLength()) {
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
			if (m_nBirthPrefecture == CB_ERR) {
				if ((m_nBirthPrefecture = pComboBox->SelectString(-1, m_strBirthPrefecture)) == CB_ERR)
					pComboBox->SetWindowText(m_strBirthPrefecture);
			} else
				pComboBox->SetCurSel(m_nBirthPrefecture);
		}
		int nBirthLongEW = 0;
		int nBirthLatNS = 0;
		CString strBirthLongDeg;
		CString strBirthLongMin;
		CString strBirthLatDeg;
		CString strBirthLatMin;
		if (m_bBirthLongLat) {
			nBirthLongEW = m_nBirthLongEW;
			nBirthLatNS = m_nBirthLatNS;
			strBirthLongDeg = IToA(m_nBirthLongDeg);
			strBirthLongMin = StrFormat("%02d",m_nBirthLongMin);
			strBirthLatDeg = IToA(m_nBirthLatDeg);
			strBirthLatMin = StrFormat("%02d",m_nBirthLatMin);
		}
		CheckRadioButton(IDC_RADIO5, IDC_RADIO6, IDC_RADIO5 + nBirthLongEW);
		CheckRadioButton(IDC_RADIO7, IDC_RADIO8, IDC_RADIO7 + nBirthLatNS);
		GetDlgItem(IDC_EDIT9)->SetWindowText(strBirthLongDeg);
		GetDlgItem(IDC_EDIT10)->SetWindowText(strBirthLongMin);
		GetDlgItem(IDC_EDIT11)->SetWindowText(strBirthLatDeg);
		GetDlgItem(IDC_EDIT12)->SetWindowText(strBirthLatMin);
		// 時差
		int nTimeDiffSign = 0;
		CString strTimeDiffHour;
		CString strTimeDiffMin;
		if (m_bTimeDiff) {
			nTimeDiffSign = m_nTimeDiffHour >= 0 ? 0 : 1;
			strTimeDiffHour = IToA(abs(m_nTimeDiffHour));
			strTimeDiffMin = StrFormat("%02d", m_nTimeDiffMinute);
		}
		CheckRadioButton(IDC_RADIO9, IDC_RADIO10, IDC_RADIO9 + nTimeDiffSign);
		GetDlgItem(IDC_EDIT13)->SetWindowText(strTimeDiffHour);
		GetDlgItem(IDC_EDIT14)->SetWindowText(strTimeDiffMin);
		((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(m_bSummerTime ? 1 : 0);
		// 日運
		((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(m_bDaily ? 1 : 0);
		OnCheck3();
		// ｱｲﾄﾞﾙの性別
		((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(m_bOppositeSex ? 1 : 0);
		// ｱｲﾄﾞﾙの名前
		((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(m_bYahoo ? 1 : 0);
		// ｱｲﾄﾞﾙの年齢
		GetDlgItem(IDC_EDIT15)->SetWindowText(IToA(m_nMinAge));
		GetDlgItem(IDC_EDIT16)->SetWindowText(IToA(m_nMaxAge));
		// ｱｲﾄﾞﾙの血液型
		((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(m_bBloodTypeA ? 1 : 0);
		((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(m_bBloodTypeB ? 1 : 0);
		((CButton *)GetDlgItem(IDC_CHECK8))->SetCheck(m_bBloodTypeO ? 1 : 0);
		((CButton *)GetDlgItem(IDC_CHECK9))->SetCheck(m_bBloodTypeAB ? 1 : 0);
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
}

int CIdicChasenDlg::ExecChasen(int nMode, const CString& strName, int nSex, const COleDateTime& DtBirth, int bBirthTimeUnknown)
{
	static const char* pszFuncName = "ExecChasen";
	// 変数宣言
	int i;
	int imax;
	int nSleepCount;
	try {
		// コントロール
		if (GetFNameFromFPath(m_strChasenFPath).CompareNoCase("chasen.exe") != 0) {
			MessageBox(StrFormat("%s: 「チャート占星術」の実行ファイルのファイル名が chasen.exe でありません。", pszFuncName), NULL, MB_ICONSTOP);
			return -1;
		}
		// ファイル
		if (! CFile::GetStatus(m_strChasenFPath, m_FileStatus)) {
			MessageBox(StrFormat(ERRMSG_NOTFOUND, pszFuncName, m_strChasenFPath), NULL, MB_ICONSTOP);
			return -1;
		}
		// チャート占星術
		static const char* pszChasenWndName = "チャート占星術";
		static const char* pszChasenClassName = "TForm1";
		// チャート占星術が既に実行されているか
		while (FindWindow(pszChasenClassName, pszChasenWndName) != NULL) {
			MessageBox(StrFormat("%s: チャート占星術が既に実行されています。", pszFuncName), NULL, MB_ICONSTOP);
			return -1;
		}
		// チャート占星術の実行
		CString strChasenDPath(GetDPathFromFPath(m_strChasenFPath));
		HINSTANCE hError;
		if ((int)(hError = ShellExecute(m_hWnd, "open", m_strChasenFPath, NULL, strChasenDPath, SW_SHOWNORMAL)) <= 32) {
			MessageBox(StrFormat(ERRMSG_DETAIL, pszFuncName, "ShellExecute", (LPCTSTR)GetShellExecuteErrorText(hError)), NULL, MB_ICONSTOP);
			return -1;
		}
		nSleepCount = 0;
		while ((m_pWndChasen = FindWindow(pszChasenClassName, pszChasenWndName)) == NULL) {
			if (nSleepCount ++ == 300) {
				MessageBox(StrFormat(ERRMSG_TIMEOUT, pszFuncName, "FindWindow", pszChasenWndName), NULL, MB_ICONSTOP);
				return -1;
			}
			Sleep(100);
		}
		if (nMode == 0  &&  ! m_bDaily) {
			m_pWndChasen->ModifyStyle(WS_MINIMIZEBOX, 0);
			m_pWndChasen->SetForegroundWindow();
			if (m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT  ||  m_OSVI.dwMinorVersion > 0)
				m_pWndChasen->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		nSleepCount = 0;
		while (! m_pWndChasen->IsWindowVisible()) {
			if (nSleepCount ++ == 300) {
				EndChasen(m_pWndChasen);
				MessageBox(StrFormat(ERRMSG_TIMEOUT, pszFuncName, "IsWindowVisible", pszChasenWndName), NULL, MB_ICONSTOP);
				return -1;
			}
			Sleep(100);
		}
		// メインパネルウィンドウ
		m_pWndMainPanel0 = m_pWndChasen->ChildWindowFromPoint(PointMainPanel);
		m_pWndMainPanel0->GetWindowRect(&m_RectMainPanel);
		// 新規入力ボタン
		static const LPARAM lParamNewInputPoint = 25 << 16 | 45;
		m_pWndChasen->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, lParamNewInputPoint);
		m_pWndChasen->PostMessage(WM_LBUTTONUP, 0, lParamNewInputPoint);
		// 新規入力ウィンドウ
		static const char* pszNewInputWndName = "新規入力";
		CWnd* pWndNewInput;
		nSleepCount = 0;
		while ((pWndNewInput = FindWindow("TForm3", pszNewInputWndName)) == NULL) {
			if (nSleepCount ++ == 50) {
				EndChasen(m_pWndChasen);
				MessageBox(StrFormat(ERRMSG_TIMEOUT, pszFuncName, "FindWindow", pszNewInputWndName), NULL, MB_ICONSTOP);
				return -1;
			}
			Sleep(100);
		}
		nSleepCount = 0;
		while (! pWndNewInput->IsWindowVisible()) {
			if (nSleepCount ++ == 50) {
				MessageBox(StrFormat(ERRMSG_TIMEOUT, pszFuncName, "IsWindowVisible", pszNewInputWndName), NULL, MB_ICONSTOP);
				EndChasen(m_pWndChasen);
				return -1;
			}
			Sleep(100);
		}
		// 名前入力ウィンドウ
		static const POINT PointName = {190, 25};
		CWnd* pWndName = pWndNewInput->ChildWindowFromPoint(PointName);
		// 名前の入力
		PostWndText(pWndName, strName);
		// 性別
		if (nSex) {
			// 性別ウィンドウ
			static const POINT PointSex = {45, 55};
			CWnd* pWndSex = pWndNewInput->ChildWindowFromPoint(PointSex);
			// 女性ウィンドウ
			static const POINT PointFemale = {35, 75};
			CWnd* pWndFemale = pWndSex->ChildWindowFromPoint(PointFemale);
			// 女性の入力
			pWndFemale->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON);
			pWndFemale->PostMessage(WM_LBUTTONUP);
		}
		// 生年月日ウィンドウ
		static const POINT PointBirthDate = {200, 55};
		CWnd* pWndBirthDate = pWndNewInput->ChildWindowFromPoint(PointBirthDate);
		// 生年月日の年、月、日入力ウィンドウ
		static const POINT PointBirthYear = {95, 60};
		static const POINT PointBirthMonth = {150, 60};
		static const POINT PointBirthDay = {195, 60};
		CWnd* pWndBirthYear = pWndBirthDate->ChildWindowFromPoint(PointBirthYear);
		CWnd* pWndBirthMonth = pWndBirthDate->ChildWindowFromPoint(PointBirthMonth);
		CWnd* pWndBirthDay = pWndBirthDate->ChildWindowFromPoint(PointBirthDay);
		// 生年月日の入力
		PostWndText(pWndBirthYear, IToA(DtBirth.GetYear()));
		PostWndText(pWndBirthMonth, IToA(DtBirth.GetMonth()));
		PostWndText(pWndBirthDay, IToA(DtBirth.GetDay()));
		// 出生時ウィンドウ
		static const POINT PointBirthTime = {425, 55};
		CWnd* pWndBirthTime = pWndNewInput->ChildWindowFromPoint(PointBirthTime);
		// 午前午後不明ウィンドウ
		static const POINT PointBirthAMPMnknown = {35, 60};
		CWnd* pWndBirthAMPMUnknown = pWndBirthTime->ChildWindowFromPoint(PointBirthAMPMnknown);
		if (! bBirthTimeUnknown) {
			int nBirthHour = DtBirth.GetHour();
			int nBirthMinute = DtBirth.GetMinute();
			if (nBirthHour >= 12) {
				nBirthHour -= 12;
				// 午後ウィンドウ
				static const POINT PointBirthPM = {30, 45};
				CWnd* pWndBirthPM = pWndBirthAMPMUnknown->ChildWindowFromPoint(PointBirthPM);
				// 午後の入力
				pWndBirthPM->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON);
				pWndBirthPM->PostMessage(WM_LBUTTONUP);
			}
			// 出生時の時、分入力ウィンドウ
			static const POINT PointBirthHour = {85, 60};
			static const POINT PointBirthMinute = {135, 60};
			CWnd* pWndBirthHour = pWndBirthTime->ChildWindowFromPoint(PointBirthHour);
			CWnd* pWndBirthMinute = pWndBirthTime->ChildWindowFromPoint(PointBirthMinute);
			// 出生時の入力
			PostWndText(pWndBirthHour, IToA(nBirthHour));
			PostWndText(pWndBirthMinute, StrFormat("%02d", nBirthMinute));
			// 出生地ウィンドウ
			static const POINT PointBirthPlace = {175, 170};
			CWnd* pWndBirthPlace = pWndNewInput->ChildWindowFromPoint(PointBirthPlace);
			// 出生県ウィンドウ
			static const POINT PointBirthPrefectureComboBox = {125, 40};
			CWnd* pWndBirthPrefectureComboBox = pWndBirthPlace->ChildWindowFromPoint(PointBirthPrefectureComboBox);
			CWnd* pWndBirthPrefectureEdit = pWndBirthPrefectureComboBox->GetWindow(GW_CHILD);
			// 出生県の入力
			if (m_nBirthPrefecture == CB_ERR) {
				PostWndText(pWndBirthPrefectureEdit, m_strBirthPrefecture);
			} else {
				for (i = 0, imax = m_nBirthPrefecture + 1; i < imax; i ++) {
					pWndBirthPrefectureEdit->PostMessage(WM_KEYDOWN, VK_DOWN, 0x01000000 | 0x50 << 16 | 0x0001);
					pWndBirthPrefectureEdit->PostMessage(WM_KEYUP, VK_DOWN, 0xc1000000 | 0x50 << 16 | 0x0001);
				}
			}
			if (m_nBirthLongEW) {
				// 東経西経ウィンドウ
				static const POINT PointBirthLongEW = {175, 40};
				CWnd* pWndBirthLongEW = pWndBirthPlace->ChildWindowFromPoint(PointBirthLongEW);
				// 西経ウィンドウ
				static const POINT PointBirthLongW = {40, 35};
				CWnd* pWndBirthLongW = pWndBirthLongEW->ChildWindowFromPoint(PointBirthLongW);
				// 西経の入力
				pWndBirthLongW->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON);
				pWndBirthLongW->PostMessage(WM_LBUTTONUP);
			}
			if (m_nBirthLatNS) {
				// 北緯南緯ウィンドウ
				static const POINT PointBirthLatNS = {175, 85};
				CWnd* pWndBirthLatNS = pWndBirthPlace->ChildWindowFromPoint(PointBirthLatNS);
				// 南緯ウィンドウ
				static const POINT PointBirthLatS = {40, 35};
				CWnd* pWndBirthLatS = pWndBirthLatNS->ChildWindowFromPoint(PointBirthLatS);
				// 南緯の入力
				pWndBirthLatS->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON);
				pWndBirthLatS->PostMessage(WM_LBUTTONUP);
			}
			// 経度、緯度入力ウィンドウ
			static const POINT PointBirthLongDeg = {225, 40};
			static const POINT PointBirthLongMin = {275, 40};
			static const POINT PointBirthLatDeg = {230, 90};
			static const POINT PointBirthLatMin = {275, 90};
			CWnd* pWndBirthLongDeg = pWndBirthPlace->ChildWindowFromPoint(PointBirthLongDeg);
			CWnd* pWndBirthLongMin = pWndBirthPlace->ChildWindowFromPoint(PointBirthLongMin);
			CWnd* pWndBirthLatDeg = pWndBirthPlace->ChildWindowFromPoint(PointBirthLatDeg);
			CWnd* pWndBirthLatMin = pWndBirthPlace->ChildWindowFromPoint(PointBirthLatMin);
			// 経度、緯度の入力
			pWndBirthLongDeg->PostMessage(WM_SETFOCUS);
			PostWndText(pWndBirthLongDeg, IToA(m_nBirthLongDeg));
			pWndBirthLongMin->PostMessage(WM_SETFOCUS);
			PostWndText(pWndBirthLongMin, StrFormat("%02d", m_nBirthLongMin));
			pWndBirthLatDeg->PostMessage(WM_SETFOCUS);
			PostWndText(pWndBirthLatDeg, IToA(m_nBirthLatDeg));
			pWndBirthLatMin->PostMessage(WM_SETFOCUS);
			PostWndText(pWndBirthLatMin, StrFormat("%02d", m_nBirthLatMin));
			// 時差ウィンドウ
			static const POINT PointTimeDiff = {415, 170};
			CWnd* pWndTimeDiff = pWndNewInput->ChildWindowFromPoint(PointTimeDiff);
			if (m_nTimeDiffHour < 0) {
				// プラスマイナスウィンドウ
				static const POINT PointTimeDiffPlusMinus = {25, 40};
				CWnd* pWndTimeDiffPlusMinus = pWndTimeDiff->ChildWindowFromPoint(PointTimeDiffPlusMinus);
				// マイナスウィンドウ
				static const POINT PointTimeDiffMinus = {20, 35};
				CWnd* pWndTimeDiffMinus = pWndTimeDiffPlusMinus->ChildWindowFromPoint(PointTimeDiffMinus);
				// マイナスの入力
				pWndTimeDiffMinus->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON);
				pWndTimeDiffMinus->PostMessage(WM_LBUTTONUP);
			}
			// 時差の時間、分入力ウィンドウ
			static const POINT PointTimeDiffHour = {60, 40};
			static const POINT PointTimeDiffMinute = {135, 40};
			CWnd* pWndTimeDiffHour = pWndTimeDiff->ChildWindowFromPoint(PointTimeDiffHour);
			CWnd* pWndTimeDiffMinute = pWndTimeDiff->ChildWindowFromPoint(PointTimeDiffMinute);
			// 時差の入力
			pWndTimeDiffHour->PostMessage(WM_SETFOCUS);
			PostWndText(pWndTimeDiffHour, IToA(abs(m_nTimeDiffHour)));
			pWndTimeDiffMinute->PostMessage(WM_SETFOCUS);
			PostWndText(pWndTimeDiffMinute, StrFormat("%02d", m_nTimeDiffMinute));
			if (m_bSummerTime) {
				// サマータイムウィンドウ
				static const POINT PointSummerTime = {55, 90};
				CWnd* pWndSummerTime = pWndTimeDiff->ChildWindowFromPoint(PointSummerTime);
				// サマータイムの入力
				pWndSummerTime->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON);
				pWndSummerTime->PostMessage(WM_LBUTTONUP);
			}
		} else {
			// 不明ウィンドウ
			static const POINT PointBirthTimeUnknown = {30, 70};
			CWnd* pWndBirthTimeUnknown = pWndBirthAMPMUnknown->ChildWindowFromPoint(PointBirthTimeUnknown);
			// 不明の入力
			pWndBirthTimeUnknown->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON);
			pWndBirthTimeUnknown->PostMessage(WM_LBUTTONUP);
		}
		// OK ウィンドウ
		static const POINT PointOK = {370, 310};
		CWnd* pWndOK = pWndNewInput->ChildWindowFromPoint(PointOK);
		// OK の入力
		pWndOK->PostMessage(WM_KEYDOWN, VK_SPACE, 0x39 << 16 | 0x0001);
		pWndOK->PostMessage(WM_KEYUP, VK_SPACE, 0xc0000000 | 0x39 << 16 | 0x0001);
	}
	catch (CMemoryException* pEx) {
		ClipCursor(NULL);
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
		return -1;
	}

	return 0;
}

void CIdicChasenDlg::SetRank()
{
	CListCtrl* pListCtrl1 = (CListCtrl *)GetDlgItem(IDC_LIST1);
	CListCtrl* pListCtrl2 = (CListCtrl *)GetDlgItem(IDC_LIST2);
	m_nLastTopIdx = pListCtrl2->GetTopIndex();
	int nIdx;
	int nPreIdx;
	BOOL bEq;
	for (int i = 0, imax = pListCtrl2->GetCountPerPage(); i < imax; i ++) {
		nIdx = m_nLastTopIdx + i;
		if (nIdx >= pListCtrl2->GetItemCount())
			break;
		CAffinity& Affinity = m_AffinityArray[pListCtrl2->GetItemData(nIdx)];
		nPreIdx = nIdx;
		while (-- nPreIdx >= 0) {
			CAffinity& AffinityPre = m_AffinityArray[pListCtrl2->GetItemData(nPreIdx)];
			switch (m_nLastSortCol) {
			case 0:
				bEq = AffinityPre.m_strName == Affinity.m_strName;
				break;
			case 1:
				bEq = AffinityPre.m_DtBirth == Affinity.m_DtBirth;
				break;
			case 2:
				bEq = AffinityPre.m_strBloodType == Affinity.m_strBloodType;
				break;
			default:
				bEq = AffinityPre.m_pnAffinity[m_nLastSortCol - 3] == Affinity.m_pnAffinity[m_nLastSortCol - 3];
			}
			if (! bEq)
				break;
		}
		pListCtrl1->InsertItem(i, IToA(nPreIdx + 2));
	}
	SetTimer(1, 200, NULL);
}

void CIdicChasenDlg::ClearRank()
{
	if (m_nLastTopIdx != -1) {
		KillTimer(1);
		((CListCtrl *)GetDlgItem(IDC_LIST1))->DeleteAllItems();
	}
}

void CIdicChasenDlg::SetList()
{
	// 変数宣言
	int i;
	int j;
	int imax;
	// プログレスバー
	CProgressDlg ProgressDlg;
	ProgressDlg.m_pIdicChasenDlg = this;
	ProgressDlg.m_lpszDocument = "リストコントロールのデータセット処理";
	ProgressDlg.Create(IDD_PROGRESS_DIALOG);
	ProgressDlg.SetRange(10 * m_AffinityArray.GetSize());
	ProgressDlg.CenterWindow();
	ProgressDlg.ShowWindow(SW_SHOW);
	ProgressDlg.UpdateWindow();
	// データのセット
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
	int nAffinityArrayIdx;
	int nGenre;
	CString strName;
	COleDateTime DtBirth;
	CString strBloodType;
	COleDateTime DtNow(COleDateTime::GetCurrentTime());
	COleDateTime DtToday(DtNow.GetYear(), DtNow.GetMonth(), DtNow.GetDay(), 0, 0, 0);
	COleDateTime DtThisYearBirth;
	int nAge;
	int nIndex;
	void* pValue;
	for (i = 0, imax = m_AffinityArray.GetSize(); i < imax; i ++) {
		nAffinityArrayIdx = pListCtrl->GetItemCount();
		CAffinity& Affinity = m_AffinityArray[i];
		nGenre = Affinity.m_nGenre;
		strName = Affinity.m_strName;
		if (m_bYahoo  &&  (nIndex = strName.Find(' ')) != -1  &&  nIndex >= 2  &&  _ismbblead(strName[nIndex - 2])  &&  _ismbblead(strName[nIndex + 1]))
			strName.Delete(nIndex);
		DtBirth = Affinity.m_DtBirth;
		strBloodType = Affinity.m_strBloodType;
		if (DtThisYearBirth.SetDate(DtToday.GetYear(), DtBirth.GetMonth(), DtBirth.GetDay()) == 1)
			if (DtBirth.GetMonth() == 2  &&  DtBirth.GetDay() == 29)
				DtThisYearBirth.SetDate(DtToday.GetYear(), 3, 1);
		nAge = (DtToday.GetYear() - DtBirth.GetYear()) - (DtToday >= DtThisYearBirth ? 0 : 1);
		if (
			(! m_bOppositeSex  ||  (m_nSex == 0  &&  nGenre == 2  ||  m_nSex == 1  &&  nGenre == 1))
			&&  (! m_bYahoo  ||  m_MstpYahooTVPeopleName.Lookup(strName, pValue))
			&&  nAge >= m_nMinAge  &&  nAge <= m_nMaxAge
			&&  (
				m_bBloodTypeA  &&  m_bBloodTypeB  &&  m_bBloodTypeO  &&  m_bBloodTypeAB
				||  m_bBloodTypeA  &&  strBloodType == "A"
				||  m_bBloodTypeB  &&  strBloodType == "B"
				||  m_bBloodTypeO  &&  strBloodType == "O"
				||  m_bBloodTypeAB  &&  strBloodType == "AB"
			)
		) {
			pListCtrl->InsertItem(nAffinityArrayIdx, Affinity.m_strName);
			pListCtrl->SetItemText(nAffinityArrayIdx, 1, StrFormat("%s  %2d", DtBirth.Format("%y/%m/%d"), nAge));
			pListCtrl->SetItemText(nAffinityArrayIdx, 2, strBloodType);
			for (j = 0; j < 8; j ++)
				pListCtrl->SetItemText(nAffinityArrayIdx, 3 + j, IToA(Affinity.m_pnAffinity[j]));
			pListCtrl->SetItemData(nAffinityArrayIdx, i);
		}
		ProgressDlg.StepIt();
		if (ProgressDlg.m_bStopReq) {
			ProgressDlg.Destroy();
			MessageBox("リストコントロールのデータセット処理を中止しました。");
			m_AffinityArray.RemoveAll();
#ifdef YAHOOIDIC
			m_MstpIdicName.RemoveAll();
#endif
			((CListCtrl *)GetDlgItem(IDC_LIST2))->DeleteAllItems();
			m_nLastSortCol = -1;
			return;
		}
	}
	ProgressDlg.Destroy();
	// ソート
	ListCtrlSort(0);
	ListCtrlSort(9);
	ListCtrlSort(8);
	ListCtrlSort(7);
	ListCtrlSort(6);
	ListCtrlSort(5);
	ListCtrlSort(4);
	ListCtrlSort(3);
	ListCtrlSort(10);
}

void CIdicChasenDlg::UpdateList()
{
	if (m_AffinityArray.GetSize() > 0) {
		ClearRank();
		((CListCtrl *)GetDlgItem(IDC_LIST2))->DeleteAllItems();
		GetCtrlParm();
		SetList();
	}
}

void CIdicChasenDlg::EndChasen(CWnd* m_pWndChasen)
{
	static const LPARAM lParamAffinityPoint = 515 << 16 | 45;
	m_pWndChasen->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, lParamAffinityPoint);
	m_pWndChasen->PostMessage(WM_LBUTTONUP, 0, lParamAffinityPoint);
}

void CIdicChasenDlg::ListCtrlSort(int nCol)
{
	ClearRank();
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
	if (nCol == m_nLastSortCol)
		m_nLastSortDir *= -1;
	else
		m_nLastSortDir = 1;
	pListCtrl->SortItems(CompareFunc, nCol);
	m_nLastSortCol = nCol;
	SetRank();
}

int CIdicChasenDlg::GetNameList(LPCTSTR pstrURL, CString& strPath, CMapStringToPtr& MstpCategory, CDlProgressDlg& DlProgressDlg)
{
	static const char* pszFuncName = "GetNameList";

	int nRv = 0;

	int i;
	DWORD dwServiceType;
	CString strServerName;
	CString strObject;
	INTERNET_PORT nPort;
	CStringBuffer strHtml;
	CString strErrMsg;
	int nIndex0;
	int nIndex1;
	int nIndex2;
	int nIndex3;
	CHtmlTokenizer HtmlTokenizer;
	CString strCmd;
	BOOL bA = FALSE;
	CString strTag;
	CStringBuffer strValue;
	void* pValue;

	do {
		DlProgressDlg.m_strEdit1 = strPath;
		DlProgressDlg.UpdateData(FALSE);
		PumpWaitingMessages();
		if (DlProgressDlg.m_bStopReq) {
			MessageBox("最新の Yahoo! 芸能人、タレント名のダウンロード処理を中止しました。");
			nRv = -2;
			break;
		}

		if (! AfxParseURL(pstrURL, dwServiceType, strServerName, strObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP) {
			MessageBox(StrFormat(ERRMSG, pszFuncName, "AfxParseURL"), NULL, MB_ICONSTOP);
			nRv = -1;
			break;
		}
		if (DlText(strServerName, strObject, nPort, strHtml, strErrMsg)) {
			MessageBox(StrFormat("%s: %s", pszFuncName, strErrMsg), NULL, MB_ICONSTOP);
			nRv = -1;
			break;
		}

		nIndex0 = strHtml.Find("<!---登録サイト -->");
		nIndex1 = strHtml.Find("<!---/登録サイト -->", nIndex0);
		static const char* ppszNameSep[] = {
			" (",
			" -",
			"（",//1
			"の海の家",//25
			"・叶美香",//33
			"、三倉佳奈",//108
			"・大江麻理子",//136
			"－",//139
			" web site",//140
			"研究室",//203
			"のふわっとした瞬間",//205
			"のページ",//208
			"のHP",//210
			"ホームページ",//211
			"ファンサイト",//213
			"の部屋",//216
			"オフィシャル",//217
			"のホームページ",//220
			" ファンクラブ",//222
			"ちゃん広場",//223
			"HP",//224
			"FanSite",//226
			"公式",//228
			"プロフェッショナル",//230
			"を偲ぶ会",//240
			"　",//242
			"ファン同盟支部",//248
			"さん資料館",//250
			" 私設",//254
			" official web site",//255
			"私設",//256
			"さん私設ファンサイト",//334
			"と愉快な仲間たち＆tengai club",//258
			"研究所",//260
			" 魂鳴り止まず",//265
			"と近所の柴犬",//272
			"同盟",//275
			" 応援サイト",//276
			" Official Web Site",//279
			"の不思議の国へようこそ",//280
			"スペシャルサイト",//284
			NULL
		};
		HtmlTokenizer.SetHtml(strHtml);
		HtmlTokenizer.m_nHtmlPtr = nIndex0;
		while (HtmlTokenizer.m_nHtmlPtr < nIndex1) {
			HtmlTokenizer.HtmlTok();
			if (HtmlTokenizer.IsTagCmd()) {
				strCmd = HtmlTokenizer.GetTagCmd();
				bA = strCmd.CompareNoCase("a") == 0;
			} else
				if (bA) {
					bA = FALSE;
					strTag = HtmlTokenizer.m_strTag;
					nIndex3 = -1;
					for (i = 0; ppszNameSep[i]; i ++) {
						nIndex2 = strTag.Find(ppszNameSep[i]);
						if (nIndex2 != -1  &&  (nIndex2 < nIndex3  ||  nIndex3 == -1))
							nIndex3 = nIndex2;
					}
					if (nIndex3 != -1) {
						strTag.Delete(nIndex3, strTag.GetLength() - nIndex3);
						strTag.TrimRight();
					}
#ifdef YAHOOIDIC
					if (! m_MstpIdicName.Lookup(strTag, pValue)) {
#endif
#ifdef YAHOOOLD
						if (! m_MstpOldYahooTVPeopleName.Lookup(strTag, pValue)) {
#endif
							m_MstpYahooTVPeopleName[strTag] = (void *)0;
							m_SaYahooTVPeopleName.Add(strTag);
#ifdef YAHOOOLD
						}
#endif
#ifdef YAHOOIDIC
					}
#endif
				}
		}
		nIndex0 = strHtml.Find("<!---カテゴリ -->");
		nIndex1 = strHtml.Find("<!---/カテゴリ -->", nIndex0);
		HtmlTokenizer.m_nHtmlPtr = nIndex0;
		while (HtmlTokenizer.m_nHtmlPtr < nIndex1) {
			HtmlTokenizer.HtmlTok();
			if (HtmlTokenizer.IsTagCmd()) {
				strCmd = HtmlTokenizer.GetTagCmd();
				if (strCmd.CompareNoCase("a") == 0) {
					if (HtmlTokenizer.FindTagAttr("href", strValue) == 2)
						bA = TRUE;
				} else if (strCmd.CompareNoCase("hr") == 0)
					break;
			} else
				if (bA) {
					bA = FALSE;
					strTag = HtmlTokenizer.m_strTag;
					if ((nIndex2 = strTag.Find(' ')) != -1)
						strTag.Delete(nIndex2, strTag.GetLength() - nIndex2);
					if (MstpCategory.Lookup(strTag, pValue)) {
						MstpCategory[strTag] = (void *)0;
						if (GetNameList(StrQTrim(strValue), strPath + '/' + strTag, MstpCategory, DlProgressDlg)) {
							nRv = -1;
							break;
						}
					}
						
				}
		}
		if (nRv)
			break;
	} while (0);

	return nRv;
}

int CIdicChasenDlg::DlText(LPCTSTR pstrServer, LPCTSTR pstrObjectName, INTERNET_PORT nPort, CStringBuffer& strText, CString& strErrMsg)
{
	int nRv = 0;

	strText.Empty();
	strErrMsg.Empty();

	// HTTP
	CInternetSession Session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	do {
		try
		{
			pServer = Session.GetHttpConnection(pstrServer, nPort);

			pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, pstrObjectName);

			pFile->SendRequest();

			DWORD dwStatusCode;
			if (pFile->QueryInfoStatusCode(dwStatusCode) == 0) {
				strErrMsg = GetLastErrorMessage();
				nRv = -1;
				break;
			}

			if (dwStatusCode != HTTP_STATUS_OK) {
				strErrMsg = GetHttpStatusText(dwStatusCode);
				nRv = -1;
				break;
			}

			TCHAR sz[4096 + 1];
			UINT nRdLen;
			while (nRdLen = pFile->Read(sz, 4096)) {
				sz[nRdLen] = '\0';
				strText += sz;
			}
		}
		catch (CException* pEx) {
			strErrMsg = GetExceptionErrorMessage(pEx);
			nRv = -1;
			pEx->Delete();
		}

		EucToSJis(strText, strText.GetBuffer(strText.GetLength()));
		strText.ReleaseBuffer();
	} while (0);
	if (pFile) {
		pFile->Close();
		delete pFile;
	}
	if (pServer) {
		pServer->Close();
		delete pServer;
	}
	Session.Close();

	return nRv;
}

void CIdicChasenDlg::LoadLastStatus(LPCTSTR lpszLastStatusIniFPath)
{
	static const char* pszFuncName = "LoadLastStatus";
	// 変数宣言
	int i;
	try {
		CString strShowCmd;
		int nWidth;
		int nHeight;
		CString strSex;
		CString strBirthDateTime;
		CString strBirthLong;
		CString strBirthLat;
		CString strTimeDiff;
		int pnPfDefault[] = {
			0,
			NULL,
			m_RectDlg.Width(),
			m_RectDlg.Height(),
			NULL,
			NULL,
			NULL,
			NULL,

			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,

			NULL,
			0,
			255,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		};
		CString* ppstrPfDefault[] = {
			NULL,
			&m_strSwShowNormal,
			NULL,
			NULL,
			&m_strEmpty,
			&m_strEmpty,
			&m_strEmpty,
			&m_strMale,

			&m_strEmpty,
			&m_strEmpty,
			&m_strEmpty,
			&m_strEmpty,
			&m_strDefaultTimeDiff,
			&m_strFalse,
			&m_strFalse,
			&m_strTrue,

			&m_strFalse,
			NULL,
			NULL,
			&m_strTrue,
			&m_strTrue,
			&m_strTrue,
			&m_strTrue,
			&m_strFalse
		};
		int* ppnPfValue[] = {
			&m_nPreVer,
			NULL,
			&nWidth,
			&nHeight,
			NULL,
			NULL,
			NULL,
			NULL,

			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,

			NULL,
			&m_nMinAge,
			&m_nMaxAge,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		};
		CString* ppstrPfValue[] = {
			NULL,
			&strShowCmd,
			NULL,
			NULL,
			&m_strChasenFPath,
			&m_strIdicFPath,
			&m_strName,
			&strSex,

			&strBirthDateTime,
			&m_strBirthPrefecture,
			&strBirthLong,
			&strBirthLat,
			&strTimeDiff,
			NULL,
			NULL,
			NULL,

			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		};
		BOOL* ppbPfValue[] = {
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,

			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			&m_bSummerTime,
			&m_bDaily,
			&m_bOppositeSex,

			&m_bYahoo,
			NULL,
			NULL,
			&m_bBloodTypeA,
			&m_bBloodTypeB,
			&m_bBloodTypeO,
			&m_bBloodTypeAB,
			&m_bExeNotes
		};
		CString strProfileFPath = lpszLastStatusIniFPath ? lpszLastStatusIniFPath : m_strProfileFPath;
		CStringBuffer strProfileString;
		for (i = 0; ppszPfKey[i]; i ++) {
			if (ppstrPfDefault[i]) {
				GetPrivateProfileStringEx(pszPfAppGeneral, ppszPfKey[i], *ppstrPfDefault[i], strProfileString, strProfileFPath);
				if (ppstrPfValue[i])
					*ppstrPfValue[i] = strProfileString;
				else
					*ppbPfValue[i] = strProfileString.CompareNoCase(m_strTrue) == 0;
			} else
				*ppnPfValue[i] = GetPrivateProfileInt(pszPfAppGeneral, ppszPfKey[i], pnPfDefault[i], strProfileFPath);
		}
		// 性別
		m_nSex = strSex.CompareNoCase(m_strMale) == 0 ? 0 : 1;
		// 誕生日、出生時
		m_bBirthTimeUnknown = strBirthDateTime.GetLength() <= 10;
		m_bBirthTime = ! m_bBirthTimeUnknown;
		if (m_bBirthDate = strBirthDateTime.GetLength())
			m_DtBirth.ParseDateTime(strBirthDateTime);
		// 出生地
		char chBirthLongEW;
		char chBIrthLatNS;
		m_bBirthLongLat = sscanf(strBirthLong, "%d%*2s%d%*2s%c", &m_nBirthLongDeg, &m_nBirthLongMin, &chBirthLongEW) == 3  &&  sscanf(strBirthLat, "%d%*2s%d%*2s%c", &m_nBirthLatDeg, &m_nBirthLatMin, &chBIrthLatNS) == 3;
		m_nBirthLongEW = chBirthLongEW == 'E' ? 0 : 1;
		m_nBirthLatNS = chBIrthLatNS == 'N' ? 0 : 1;
		// 時差
		m_bTimeDiff = TRUE;
		sscanf(strTimeDiff, "%3d%d", &m_nTimeDiffHour, &m_nTimeDiffMinute);
		// Yahoo! 芸能人、タレント名
		m_MstpYahooTVPeopleName.RemoveAll();
		m_SaYahooTVPeopleName.RemoveAll();
#ifdef YAHOOOLD
		m_MstpOldYahooTVPeopleName.RemoveAll();
#endif
		GetPrivateProfileStringEx(pszPfAppGeneral, PF_KEY_YAHOOTVPEOPLE, "", strProfileString, strProfileFPath);
		int nSepIdx0 = -1;
		int nSepIdx1;
		CString strData;
#ifdef YAHOOIDIC
		void* pValue;
#endif
		if (strProfileString.GetLength())
			while (1) {
				if ((nSepIdx1 = strProfileString.Find(',', nSepIdx0 + 1)) == -1)
					strData = strProfileString.Mid(nSepIdx0 + 1);
				else
					strData = strProfileString.Mid(nSepIdx0 + 1, nSepIdx1 - nSepIdx0 - 1);
#ifdef YAHOOIDIC
				if (! m_MstpIdicName.Lookup(strData, pValue)) {
#endif
					m_MstpYahooTVPeopleName[strData] = (void *)0;
					m_SaYahooTVPeopleName.Add(strData);
#ifdef YAHOOOLD
					m_MstpOldYahooTVPeopleName[strData] = (void *)0;
#endif
#ifdef YAHOOIDIC
				}
#endif
				if (nSepIdx1 == -1)
					break;
				nSepIdx0 = nSepIdx1;
			}
		// コントロール
		SetCtrlParm();
		// ダイアログの Rect
		if (lpszLastStatusIniFPath == NULL) {
			WINDOWPLACEMENT WindowPlacement;
			GetWindowPlacement(&WindowPlacement);
			WindowPlacement.rcNormalPosition.right = WindowPlacement.rcNormalPosition.left + nWidth;
			WindowPlacement.rcNormalPosition.bottom = WindowPlacement.rcNormalPosition.top + nHeight;
			SetWindowPlacement(&WindowPlacement);
			CenterWindow();
			GetWindowPlacement(&WindowPlacement);
			if (strShowCmd.CompareNoCase(m_strSwShowNormal) == 0)
				WindowPlacement.showCmd = SW_SHOWNORMAL;
			else if (strShowCmd.CompareNoCase(m_strSwShowMinimized) == 0)
				WindowPlacement.showCmd = SW_SHOWMINIMIZED;
			else if (strShowCmd.CompareNoCase(m_strSwShowMaximized) == 0)
				WindowPlacement.showCmd = SW_SHOWMAXIMIZED;
			SetWindowPlacement(&WindowPlacement);
			UpdateWindow();
			DlgSizeCtlMove();
		}
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	catch (COleException* pEx) {
		MessageBox(StrFormat(ERRMSG_OLEEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
}

void CIdicChasenDlg::SaveLastStatus(LPCTSTR lpszLastStatusIniFPath)
{
	static const char* pszFuncName = "SaveLastStatus";
	// 変数宣言
	int i;
	int imax;
	do {
		try {
			// ウィンドウの表示状態
			WINDOWPLACEMENT WindowPlacement;
			GetWindowPlacement(&WindowPlacement);
			CString strShowCmd;
			switch (WindowPlacement.showCmd) {
			case SW_SHOWMINIMIZED:
				strShowCmd = m_strSwShowMinimized;
				break;
			case SW_SHOWMAXIMIZED:
				strShowCmd = m_strSwShowMaximized;
				break;
			default:
				strShowCmd = m_strSwShowNormal;
			}
			// ウィンドウの幅と高さ
			int nWidth = WindowPlacement.rcNormalPosition.right - WindowPlacement.rcNormalPosition.left;
			int nHeight = WindowPlacement.rcNormalPosition.bottom - WindowPlacement.rcNormalPosition.top;
			// コントロール
			GetCtrlParm();
			// 性別
			CString strSex = m_nSex == 0 ? m_strMale : m_strFemale;
			// 誕生日、出生時
			CString strBirthDateTime;
			if (m_bBirthDate) {
				strBirthDateTime = m_DtBirth.Format("%Y/%m/%d");
				if (! m_bBirthTimeUnknown  &&  m_bBirthTime)
					strBirthDateTime += m_DtBirth.Format(" %H:%M");
			}
			// 出生地
			CString strBirthLong;
			CString strBirthLat;
			if (m_bBirthLongLat) {
				strBirthLong = StrFormat("%d°%d′%c", m_nBirthLongDeg, m_nBirthLongMin, m_nBirthLongEW == 0 ? 'E' : 'W');
				strBirthLat = StrFormat("%d°%d′%c", m_nBirthLatDeg, m_nBirthLatMin, m_nBirthLatNS == 0 ? 'N' : 'S');
			}
			// 時差
			CString strTimeDiff(m_strDefaultTimeDiff);
			if (m_bTimeDiff)
				strTimeDiff = StrFormat("%+03d%02d", m_nTimeDiffHour, m_nTimeDiffMinute);
			// Ini
			CStringBuffer strFile;
			int pnPfValue[] = {
				THIS_VER,
				NULL,
				nWidth,
				nHeight,
				NULL,
				NULL,
				NULL,
				NULL,

				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,

				NULL,
				m_nMinAge,
				m_nMaxAge,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL
			};
			CString* ppstrPfValue[] = {
				NULL,
				&strShowCmd,
				NULL,
				NULL,
				&m_strChasenFPath,
				&m_strIdicFPath,
				&m_strName,
				&strSex,

				&strBirthDateTime,
				&m_strBirthPrefecture,
				&strBirthLong,
				&strBirthLat,
				&strTimeDiff,
				NULL,
				NULL,
				NULL,

				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL
			};
			BOOL* ppbPfValue[] = {
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,

				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				&m_bSummerTime,
				&m_bDaily,
				&m_bOppositeSex,

				&m_bYahoo,
				NULL,
				NULL,
				&m_bBloodTypeA,
				&m_bBloodTypeB,
				&m_bBloodTypeO,
				&m_bBloodTypeAB,
				&m_bExeNotes
			};
			CString strPfValue;
			BOOL bError = FALSE;
			for (i = 0; ppszPfKey[i]; i ++) {
				if (ppstrPfValue[i])
					strPfValue = *ppstrPfValue[i];
				else if (ppbPfValue[i])
					strPfValue = *ppbPfValue[i] ? m_strTrue : m_strFalse;
				else
					strPfValue = IToA(pnPfValue[i]);
				SetPrivateProfileStringEx(pszPfAppGeneral, ppszPfKey[i], strPfValue, strFile);
			}
			if (bError)
				break;
			// Yahoo! 芸能人、タレント名
			CStringBuffer strList;
/*
			CString strKey;
			void* pValue;
			POSITION pos = m_MstpYahooTVPeopleName.GetStartPosition();
			while (pos) {
				m_MstpYahooTVPeopleName.GetNextAssoc(pos, strKey, pValue);
				if (strList.GetLength())
					strList += ',';
				strList += strKey;
			}
*/
			for (i = 0, imax = m_SaYahooTVPeopleName.GetSize(); i < imax; i ++) {
				if (strList.GetLength())
					strList += ',';
				strList += m_SaYahooTVPeopleName[i];
			}
#ifdef WRITEFILE
			CStringBuffer strWrText;
			for (i = 0, imax = m_SaYahooTVPeopleName.GetSize(); i < imax; i ++)
				strWrText += m_SaYahooTVPeopleName[i] + '\n';
			CString strDPath;
			GetCurrentDirectory(MAX_PATH, strDPath.GetBuffer(MAX_PATH));
			strDPath.ReleaseBuffer();
			CString strFPath;
			strFPath.Format("%s\\IdicChasen.txt", strDPath);
			CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeWrite);
			StdioFile.WriteString(strWrText);
			StdioFile.Close();
#endif
			SetPrivateProfileStringEx(pszPfAppGeneral, PF_KEY_YAHOOTVPEOPLE, strList, strFile);
			WritePrivateProfile(strFile, lpszLastStatusIniFPath ? lpszLastStatusIniFPath : m_strProfileFPath);
		}
		catch (CMemoryException* pEx) {
			MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
			pEx->Delete();
		}
		catch (COleException* pEx) {
			MessageBox(StrFormat(ERRMSG_OLEEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
			pEx->Delete();
		}
	} while (0);
}

void CIdicChasenDlg::VerCheck0()
{
	CString strProgramFilesDir = GetShFolderPath(CSIDL_PROGRAM_FILES);
	if (strProgramFilesDir.Right(1) == "\\")
		strProgramFilesDir = strProgramFilesDir.Left(strProgramFilesDir.GetLength() - 1);

	CString strOldDefaultHkunDir = strProgramFilesDir + "\\" OLD_DNAME_HKUN;
	CString strOldDefaultDir = strOldDefaultHkunDir + "\\" DNAME_IDICCHASEN;

	if (CFile::GetStatus(strOldDefaultDir, m_FileStatus)) {
		CString* pstrDir[] = {&strOldDefaultDir, &m_strDir, NULL};

		CString strOldProfileFPath;
		CString strOldFindKeyFPath;

		for (int i = 0; pstrDir[i]; i ++)
			if (pstrDir[i]->CompareNoCase(m_strDataDir)) {
				strOldProfileFPath = *pstrDir[i] + "\\" FNAME_PROFILE;
				strOldFindKeyFPath = *pstrDir[i] + "\\" FINDKEY_FNAME;
				CopyFile(strOldProfileFPath, m_strProfileFPath, TRUE);
				CopyFile(strOldFindKeyFPath, m_strFindKeyFPath, TRUE);
				DeleteFile(strOldProfileFPath);
				DeleteFile(strOldFindKeyFPath);
			}

		RemoveDirectory(strOldDefaultDir);
		RemoveDirectory(strOldDefaultHkunDir);
	}
}

void CIdicChasenDlg::VerCheck1()
{
	if (m_nPreVer < 116)
		m_bExeNotes = FALSE;
}
