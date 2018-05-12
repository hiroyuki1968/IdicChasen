// IdicChasen.h : IDICCHASEN アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_IDICCHASEN_H__99B66FE4_1E3E_448D_82DC_4E2FEA0E812A__INCLUDED_)
#define AFX_IDICCHASEN_H__99B66FE4_1E3E_448D_82DC_4E2FEA0E812A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

#include "IdicChasenDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp:
// このクラスの動作の定義に関しては IdicChasen.cpp ファイルを参照してください。
//

class CIdicChasenApp : public CWinApp
{
public:
	CIdicChasenApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CIdicChasenApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CIdicChasenDlg* m_pIdicChasenDlg;
protected:
	int ReadProductCode(CStringBuffer& strProductCode);
	CString m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CIdicChasenApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_IDICCHASEN_H__99B66FE4_1E3E_448D_82DC_4E2FEA0E812A__INCLUDED_)
