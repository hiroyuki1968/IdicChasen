// IdicChasen.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "IdicChasen.h"
#include "IdicChasenDlg.h"

#include "IdicChasenDef.h"
#include "htmlhelp.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp

BEGIN_MESSAGE_MAP(CIdicChasenApp, CWinApp)
	//{{AFX_MSG_MAP(CIdicChasenApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp クラスの構築

CIdicChasenApp::CIdicChasenApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CIdicChasenApp オブジェクト

CIdicChasenApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp クラスの初期化

BOOL CIdicChasenApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	LoadUxThemeDll();

	// Exe フォルダ
	m_strDir = GetDPathFromFPath(m_pszHelpFilePath);

	// コマンド ライン引数
	BOOL bUninstall = _tcsicmp(m_lpCmdLine, _T("/Uninstall")) == 0;

	// アンインストール
	if (bUninstall) {
		CStringBuffer strProductCode;
		if (ReadProductCode(strProductCode))
			return FALSE;

		HINSTANCE hShellExecute;
		if ((int)(hShellExecute = ShellExecute(NULL, _T("open"), _T("msiexec"), _T("/x ") + strProductCode, NULL, SW_SHOWNORMAL)) <= 32)
			AfxMessageBox(_T("アンインストーラー実行エラー: ") + GetShellExecuteErrorText(hShellExecute), MB_ICONSTOP);
		return FALSE;
	}

	// プログラムの複数起動抑止
	// もし、オープンできれば以前のアプリケーションが起動している
	CString strMutex(MUTEX_INSTANCE);
	HANDLE hPrevMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, strMutex);
	if (hPrevMutex) {
		AfxMessageBox("既に起動しています。", MB_ICONSTOP);
		// クローズ
		CloseHandle(hPrevMutex);
		return FALSE; 
	}
	// 複数起動確認用ミューテックス作成
	m_hExeCheckMutex = CreateMutex(FALSE, 0, strMutex);

	CIdicChasenDlg dlg;
	m_pMainWnd = &dlg;
	m_pIdicChasenDlg = &dlg;
	dlg.m_strDir = m_strDir;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

int CIdicChasenApp::ExitInstance() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	if (m_hExeCheckMutex)
		ReleaseMutex(m_hExeCheckMutex);
	FreeUxThemeDll();
	
	return CWinApp::ExitInstance();
}

void CIdicChasenApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	//ここでOS等のチェックを行うとよい
	//OSVERSIONINFO os_info;
	//os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	//GetVersionEx(&os_info);

	//これは作成したHtmlHelpにより異なる
	//dwDataを変換するコードも必要
	char* szFileName = "IdicChasen.htm";

	CString strHelpPath = m_pszHelpFilePath;
	strHelpPath = strHelpPath.Left(strHelpPath.ReverseFind('.') + 1) + "chm";

	HtmlHelp(NULL, strHelpPath, HH_DISPLAY_TOPIC, (DWORD)szFileName);

// 基本クラスのメンバ関数は呼ばない
//	CWinApp::WinHelp(dwData, nCmd);
}

int CIdicChasenApp::ReadProductCode(CStringBuffer& strProductCode)
{
	int nRv = 0;

	if (ReStrFile(m_strDir + _T("\\") FNAME_PRODUCTCODE, strProductCode))
		nRv = -1;
	else
		strProductCode.TrimRight();

	return nRv;
}

int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CIdicChasenDlg* pIdicChasenDlg = theApp.m_pIdicChasenDlg;

	int nRv = 0;
	COleDateTime Dt0;
	COleDateTime Dt1;
	int n0;
	int n1;

	switch (lParamSort) {
	case 0:
		nRv = pIdicChasenDlg->m_AffinityArray[lParam1].m_strName.Compare(pIdicChasenDlg->m_AffinityArray[lParam2].m_strName);
		break;
	case 1:
		Dt0 = pIdicChasenDlg->m_AffinityArray[lParam1].m_DtBirth;
		Dt1 = pIdicChasenDlg->m_AffinityArray[lParam2].m_DtBirth;
		if (Dt0 < Dt1)
			nRv = -1;
		else if (Dt0 > Dt1)
			nRv = 1;
		break;
	case 2:
		nRv = pIdicChasenDlg->m_AffinityArray[lParam1].m_strBloodType.Compare(pIdicChasenDlg->m_AffinityArray[lParam2].m_strBloodType);
		break;
	default:
		n0 = pIdicChasenDlg->m_AffinityArray[lParam1].m_pnAffinity[lParamSort - 3];
		n1 = pIdicChasenDlg->m_AffinityArray[lParam2].m_pnAffinity[lParamSort - 3];
		if (n0 < n1)
			nRv = 1;
		else if (n0 > n1)
			nRv = -1;
	}

	return nRv * pIdicChasenDlg->m_nLastSortDir;
}

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CIdicChasenDlg* pIdicChasenDlg = theApp.m_pIdicChasenDlg;

	LPMSG lpMsg = (LPMSG) lParam;

	if ( nCode >= 0 && PM_REMOVE == wParam )
	{
		if (lpMsg->message == WM_KEYDOWN)
		{
			HWND hwnd = lpMsg->hwnd;
			HWND hwndParent;
			HWND hwndIdicChasenDlg = pIdicChasenDlg->m_hWnd;
			while ((hwndParent = GetParent(hwnd)) != NULL) {
				if (hwndParent == hwndIdicChasenDlg)
					break;
				hwnd = hwndParent;
			}
			
			int nID = 0;
			if (hwndParent)
				nID = GetDlgCtrlID(lpMsg->hwnd);

			BOOL bNull = FALSE;

			switch (lpMsg->message) {
			case WM_KEYDOWN:
				if (hwndParent == hwndIdicChasenDlg  ||  hwndParent == NULL  &&  hwnd == hwndIdicChasenDlg)
					if (lpMsg->wParam == VK_RETURN)
						if (nID == IDC_EDIT15  ||  nID == IDC_EDIT16) {
							pIdicChasenDlg->UpdateList();
							bNull = TRUE;
						}
			}

			if (bNull) {
				lpMsg->message = WM_NULL;
				lpMsg->lParam  = 0;
				lpMsg->wParam  = 0;
			}
		}
	}

	return CallNextHookEx(pIdicChasenDlg->m_hHook, nCode, wParam, lParam);
}
