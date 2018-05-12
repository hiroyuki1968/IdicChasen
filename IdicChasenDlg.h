// IdicChasenDlg.h : ヘッダー ファイル
//

#if !defined(AFX_IDICCHASENDLG_H__2A4512AC_EC98_4501_B9E8_B3E9F872177A__INCLUDED_)
#define AFX_IDICCHASENDLG_H__2A4512AC_EC98_4501_B9E8_B3E9F872177A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxinet.h>
#include "IdicChasenDef.h"
#include "StringBuffer.h"
#include "IconButton.h"
#include "Affinity.h"
#include "DlProgressDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenDlg ダイアログ

class CIdicChasenDlg : public CDialog
{
// 構築
public:
	CIdicChasenDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CIdicChasenDlg)
	enum { IDD = IDD_IDICCHASEN_DIALOG };
	CIconButton	m_IconButton5;
	CIconButton	m_IconButton6;
	CIconButton	m_IconButton7;
	CIconButton	m_IconButton8;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CIdicChasenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void UpdateList();
	CString m_strDir;
	HHOOK m_hHook;
	CAffinityArray m_AffinityArray;
	int m_nLastSortDir;
protected:
	void DlgSizeCtlMove();
	void SetBirthPrefectureComboRect();
	void GetCtrlParm();
	void SetCtrlParm();
	void SetRank();
	void ClearRank();
	void SetList();
	int ExecChasen(int nMode, const CString& strName, int nSex, const COleDateTime& DtBirth, int bBirthTimeUnknown);
	void EndChasen(CWnd* pWndChasen);
	void ListCtrlSort(int nCol);
	int GetNameList(LPCTSTR pstrURL, CString& strPath, CMapStringToPtr& MstpCategory, CDlProgressDlg& DlProgressDlg);
	int DlText(LPCTSTR pstrServer, LPCTSTR pstrObjectName, INTERNET_PORT nPort, CStringBuffer& strText, CString& strErrMsg);
	void LoadLastStatus(LPCTSTR lpszLastStatusIniFPath = NULL);
	void SaveLastStatus(LPCTSTR lpszLastStatusIniFPath = NULL);
	void VerCheck0();
	void VerCheck1();
	OSVERSIONINFO m_OSVI;
	BOOL m_bInitDialog;
	CFileStatus m_FileStatus;
	CString m_strEmpty;
	CString m_strTrue;
	CString m_strFalse;
	CString m_strSwShowNormal;
	CString m_strSwShowMinimized;
	CString m_strSwShowMaximized;
	CString m_strPfAppGeneral;
	CString m_strMale;
	CString m_strFemale;
	CString m_strDefaultTimeDiff;
	CString m_strDataDir;
	CString m_strProfileFPath;
	CString m_strFindKeyFPath;
	CFont m_FontListBox;
	int m_nPreVer;
	CString m_strChasenFPath;
	CString m_strIdicFPath;
	CString m_strName;
	int m_nSex;
	BOOL m_bBirthDate;
	BOOL m_bBirthTimeUnknown;
	BOOL m_bBirthTime;
	COleDateTime m_DtBirth;
	int m_nBirthPrefecture;
	CString m_strBirthPrefecture;
	BOOL m_bBirthLongLat;
	int m_nBirthLongEW;
	int m_nBirthLatNS;
	int m_nBirthLongDeg;
	int m_nBirthLongMin;
	int m_nBirthLatDeg;
	int m_nBirthLatMin;
	BOOL m_bTimeDiff;
	int m_nTimeDiffHour;
	int m_nTimeDiffMinute;
	BOOL m_bSummerTime;
	BOOL m_bDaily;
	BOOL m_bOppositeSex;
	BOOL m_bYahoo;
	int m_nMinAge;
	int m_nMaxAge;
	BOOL m_bBloodTypeA;
	BOOL m_bBloodTypeB;
	BOOL m_bBloodTypeO;
	BOOL m_bBloodTypeAB;
	BOOL m_bExeNotes;
	CStringArray m_SaFindKey;
	CRect m_RectDlg;
	CRect m_RectListCtrl1;
	CRect m_RectListCtrl2;
	COLORREF m_crDefaultChasenBk1;
	COLORREF m_crDefaultChasenBk2;
	CString m_strDefaultChasenBkColor1;
	CString m_strDefaultChasenBkColor2;
	CWnd* m_pWndChasen;
	CWnd* m_pWndMainPanel0;
	CRect m_RectMainPanel;
	int m_nLastSortCol;
	int m_nLastTopIdx;
	CString m_strLastFindKey;
	int m_nLastFindItemIdx;
	CMapStringToPtr m_MstpYahooTVPeopleName;
	CStringArray m_SaYahooTVPeopleName;
#ifdef YAHOOOLD
	CMapStringToPtr m_MstpOldYahooTVPeopleName;
#endif
#ifdef YAHOOIDIC
	CMapStringToPtr m_MstpIdicName;
#endif
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CIdicChasenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnCheck1();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDropdownCombo1();
	afx_msg void OnSetfocusEdit15();
	afx_msg void OnKillfocusEdit15();
	afx_msg void OnSetfocusEdit16();
	afx_msg void OnKillfocusEdit16();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_IDICCHASENDLG_H__2A4512AC_EC98_4501_B9E8_B3E9F872177A__INCLUDED_)
